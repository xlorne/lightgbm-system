#!/bin/bash
set -e
echo "==> 清理旧构建..."
rm -rf build
echo "==> 创建构建目录..."
mkdir -p build

echo "==> 使用 Conan 安装依赖到 build/ 目录中..."
conan install . \
  --output-folder=build \
  --build=missing
echo "==> 进入构建目录..."
cd build
echo "==> 使用 CMake 配置工程..."
cmake .. \
  -DCMAKE_TOOLCHAIN_FILE=conan_toolchain.cmake \
  -DCMAKE_BUILD_TYPE=Release
echo "==> 编译项目..."
cmake --build .
echo "✅ 构建完成！"