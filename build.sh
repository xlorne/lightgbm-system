#!/bin/bash
set -e

# 检查 LightGBM 源码是否存在，不存在则自动下载
if [ ! -d "third_party/LightGBM/.git" ]; then
  echo "==> 未检测到 third_party/LightGBM，自动下载 LightGBM 及其所有扩展..."
  bash third_party/lightgbm.sh
  mv ./LightGBM ./third_party/LightGBM
fi

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