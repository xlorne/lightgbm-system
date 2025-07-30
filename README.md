# LightGBM C++ 示例工程

本项目演示如何在 C++ 工程中集成和调用 [LightGBM](https://github.com/microsoft/LightGBM) 库，适合 C++ 开发者学习机器学习模型的集成与基本推理流程。

## 目录结构说明
- `src/`：源代码目录（示例主程序、LightGBM 封装）
- `include/`：头文件目录（LightGBM 封装接口）
- `third_party/LightGBM/`：LightGBM 源码及所有扩展（不随仓库提交）
- `CMakeLists.txt`：CMake 构建脚本
- `conanfile.txt`：Conan 依赖配置文件

## 主要内容
- LightGBM C++ API 的简单封装与调用
- 加载模型、推理示例
- CMake 构建与 Conan 依赖管理

## 依赖环境
- C++17 或更高版本编译器
- [CMake](https://cmake.org/) 3.15+
- [Conan](https://conan.io/) 2.x
- libomp  

## 获取 LightGBM 源码

本项目未包含 LightGBM 源码。首次使用前请在 third_party 目录下执行以下命令，下载 LightGBM 及其所有扩展：

```bash
# 下载 LightGBM 及所有子模块（含拓展）
git clone --recurse-submodules https://github.com/microsoft/LightGBM.git third_party/LightGBM
```

或运行脚本：

```bash
bash third_party/lightgbm.sh
```

## 快速开始

1. 安装依赖

   ```bash
   conan install . --output-folder=build --build=missing
   ```

2. 构建项目

   ```bash
   cmake -S . -B build
   cmake --build build
   ```

3. 运行示例

   ```bash
   ./build/lightbgm-system
   ```

## 参考

- [LightGBM 官方文档](https://lightgbm.readthedocs.io/)
- [Conan 官方文档](https://docs.conan.io/)
- [CMake 官方文档](https://cmake.org/cmake/help/latest/)
