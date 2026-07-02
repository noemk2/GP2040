#!/bin/bash

set -e

echo "Actualizando repositorios..."
sudo apt update

echo "Instalando herramientas de compilación ARM..."
sudo apt install -y \
    cmake \
    gcc-arm-none-eabi \
    libnewlib-arm-none-eabi \
    libstdc++-arm-none-eabi-newlib \
    build-essential

echo "Instalando Node.js 18..."
curl -fsSL https://deb.nodesource.com/setup_18.x | sudo -E bash -

sudo apt install -y nodejs

echo ""
echo "Instalación completada."
echo "Versiones instaladas:"
cmake --version | head -n 1
arm-none-eabi-gcc --version | head -n 1
node --version
npm --version
