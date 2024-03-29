[中文](./README.md)/[English](./README.en.md)

![logo](docs/images/logo.png)

# Development kits

Devkits is a basic software development framework based on CMake and relying on Boost library, which is used to quickly create new projects and build development environments.

[![](https://img.shields.io/badge/gitee-@stingliang-blue.svg)](https://gitee.com/stingliang)
[![](https://img.shields.io/badge/github-@stingliang-blue.svg)](https://github.com/stingliang)
[![GitHub All Releases](https://img.shields.io/github/downloads/stingliang/devkits/total.svg)](https://github.com/stingliang/devkits)

## Supported platforms

- Linux
- Windows

## Architecture

Devkits is based on a modular coding architecture. Each independent function should create a separate directory, and the main program is the organizer of these independent functions.

The main functions involved in the business should not be directly reflected in the source code of the main program, but independently provided as a library for the main program to call.

## Build tool

This project uses CMake as the construction tool. CMakeLists.txt under the project root directory organizes the construction of all modules, third-party libraries and test components.

## Basic components

- [libdevcore](docs/libdevcore/index.en.md)

  Gospel of Lazy People: Encapsulated Logs, General Tools and Exception Handling.
- Secretary of main program: initialization module.
- Always make sure your code functions properly: test modules.

## License

All contributions are made under the Apache License 2.0, see [LICENSE](./LICENSE) for details.