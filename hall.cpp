#include "addons/analog.h"
#include "config.pb.h"
#include "enums.pb.h"
#include "hardware/adc.h"
#include "helper.h"
#include "storagemanager.h"
#include "drivermanager.h"

#include <math.h>
#include <algorithm>

#define ADC_MAX ((1 << 12) - 1)
#define ADC_PIN_OFFSET 26

#define ANALOG_CENTER 0.5f

// ===== PRO TUNING (HALL EFFECT) =====
#define OVERSAMPLE_COUNT 8
#define GAMMA 0.65f

static inline float signf(float v) {
    return (v >= 0.0f) ? 1.0f : -1.0f;
}

static inline float applyGamma(float v) {
    // expand center resolution
    return signf(v) * powf(fabsf(v), GAMMA);
}

static inline uint16_t readADCFiltered(uint8_t channel) {
    uint32_t sum = 0;
    for (int i = 0; i < OVERSAMPLE_COUNT; i++) {
        adc_select_input(channel);
        sum += adc_read();
    }
    return sum / OVERSAMPLE_COUNT;
}

bool AnalogInput::available() {
    return Storage::getInstance().getAddonOptions().analogOptions.enabled;
}

void AnalogInput::setup() {
    const AnalogOptions& opt =
        Storage::getInstance().getAddonOptions().analogOptions;

    for (int i = 0; i < ADC_COUNT; i++) {
        adc_pairs[i].x_pin = (i == 0) ? opt.analogAdc1PinX : opt.analogAdc2PinX;
        adc_pairs[i].y_pin = (i == 0) ? opt.analogAdc1PinY : opt.analogAdc2PinY;

        adc_pairs[i].analog_invert = (i == 0) ? opt.analogAdc1Invert : opt.analogAdc2Invert;
        adc_pairs[i].analog_dpad = (i == 0) ? opt.analogAdc1Mode : opt.analogAdc2Mode;

        adc_pairs[i].auto_calibration = (i == 0) ? opt.auto_calibrate : opt.auto_calibrate2;

        adc_pairs[i].in_deadzone = (i == 0) ? opt.inner_deadzone : opt.inner_deadzone2;
        adc_pairs[i].out_deadzone = (i == 0) ? opt.outer_deadzone : opt.outer_deadzone2;

        adc_pairs[i].ema_option = (i == 0) ? opt.analog_smoothing : opt.analog_smoothing2;
        adc_pairs[i].ema_smoothing = ((i == 0 ? opt.smoothing_factor : opt.smoothing_factor2) / 1000.0f);

        adc_gpio_init(adc_pairs[i].x_pin);
        adc_gpio_init(adc_pairs[i].y_pin);

        adc_select_input(adc_pairs[i].x_pin - ADC_PIN_OFFSET);
        adc_pairs[i].x_center = adc_read();

        adc_select_input(adc_pairs[i].y_pin - ADC_PIN_OFFSET);
        adc_pairs[i].y_center = adc_read();
    }
}

static inline float normalizeRaw(uint16_t v, uint16_t center) {
    float f = (float)v / (float)ADC_MAX;
    float c = (float)center / (float)ADC_MAX;
    return (f - c) * 2.0f; // [-1..1]
}

void AnalogInput::process() {
    Gamepad* gamepad = Storage::getInstance().GetGamepad();

    for (int i = 0; i < ADC_COUNT; i++) {

        if (!isValidPin(adc_pairs[i].x_pin) || !isValidPin(adc_pairs[i].y_pin))
            continue;

        uint16_t rawX = readADCFiltered(adc_pairs[i].x_pin - ADC_PIN_OFFSET);
        uint16_t rawY = readADCFiltered(adc_pairs[i].y_pin - ADC_PIN_OFFSET);

        // ===== normalize to [-1..1]
        float x = normalizeRaw(rawX, adc_pairs[i].x_center);
        float y = normalizeRaw(rawY, adc_pairs[i].y_center);

        // invert support
        if (adc_pairs[i].analog_invert == InvertMode::INVERT_X ||
            adc_pairs[i].analog_invert == InvertMode::INVERT_XY)
            x = -x;

        if (adc_pairs[i].analog_invert == InvertMode::INVERT_Y ||
            adc_pairs[i].analog_invert == InvertMode::INVERT_XY)
            y = -y;

        // ===== GAMMA CURVE (RESOLUTION BOOST CENTER)
        x = applyGamma(x);
        y = applyGamma(y);

        // ===== RADIAL NORMALIZATION (CIRCLE PERFECT)
        float len = sqrtf(x * x + y * y);

        if (len < adc_pairs[i].in_deadzone) {
            x = 0;
            y = 0;
        } else {
            float scaled = (len - adc_pairs[i].in_deadzone) /
                           (adc_pairs[i].out_deadzone - adc_pairs[i].in_deadzone);

            scaled = std::clamp(scaled, 0.0f, 1.0f);

            if (len > 0.00001f) {
                x = (x / len) * scaled;
                y = (y / len) * scaled;
            }
        }

        // ===== back to 0..1
        float outX = x * 0.5f + 0.5f;
        float outY = y * 0.5f + 0.5f;

        outX = std::clamp(outX, 0.0f, 1.0f);
        outY = std::clamp(outY, 0.0f, 1.0f);

        uint16_t finalX = (uint16_t)(outX * 0xFFFF);
        uint16_t finalY = (uint16_t)(outY * 0xFFFF);

        if (adc_pairs[i].analog_dpad == DpadMode::DPAD_MODE_LEFT_ANALOG) {
            gamepad->state.lx = finalX;
            gamepad->state.ly = finalY;
        } else if (adc_pairs[i].analog_dpad == DpadMode::DPAD_MODE_RIGHT_ANALOG) {
            gamepad->state.rx = finalX;
            gamepad->state.ry = finalY;
        }
    }
}