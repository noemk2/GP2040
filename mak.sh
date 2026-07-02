
cd /workspaces/GP2040/GP2040-CE
mkdir -p /workspaces/GP2040/GP2040-CE/build
cd /workspaces/GP2040/GP2040-CE/build

export PICO_SDK_PATH=/workspaces/GP2040/pico/pico-sdk

cmake .. -DGP2040_BOARDCONFIG=MyRP2040
make -j$(nproc)