[中文](./README.md)/[English](./README.en.md)

![logo](docs/images/logo.png)

# Development kits

Devkits是一个基于CMake构建，依赖Boost库的软件开发基本框架，用于快速新建工程、搭建开发环境。

[![](https://img.shields.io/badge/gitee-@stingliang-blue.svg)](https://gitee.com/stingliang)
[![](https://img.shields.io/badge/github-@stingliang-blue.svg)](https://github.com/stingliang)
[![GitHub All Releases](https://img.shields.io/github/downloads/stingliang/devkits/total.svg)](https://github.com/stingliang/devkits)

## 支持的平台

- Linux
- Windows

## 架构

Devkits基于模块化的编码架构，每一个独立的功能都应该创建一个单独的目录，而主程序既是这些独立功能的组织者。

各个涉及业务的主要功能都不应该直接体现在主程序的源码中，而是独立作为一个库提供给主程序调用。

## 构建框架

本项目使用CMake作为构建工具，由项目根目录下的CMakeLists.txt组织所有模块、第三方库及测试组件的构建。

## 基本模块

- [libdevcore](docs/libdevcore/index.md)

  懒人福音：封装好的日志、通用工具和异常处理。
- 主程序的秘书：初始化模块。
- 随时确保你的代码功能正常：测试模块。

## License

Devkits的开源协议为Apache License 2.0, 详情参见[LICENSE](LICENSE)。