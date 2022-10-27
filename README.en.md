[中文](./README.md),[English](./README.en.md)

# Development kits

Devkits is a basic software development framework based on CMake and relying on Boost library, which is used to quickly create new projects and build development environments

## Supported platforms

- Linux
- Windows

## Architecture

Devkits is based on a modular coding architecture. Each independent function should create a separate directory, and the main program is the organizer of these independent functions

The main functions involved in the business should not be directly reflected in the source code of the main program, but independently provided as a library for the main program to call

## Build tool

This project uses CMake as the construction tool. CMakeLists.txt under the project root directory organizes the construction of all modules, third-party libraries and test components

## Basic components

- Gospel of Lazy People: Encapsulated Logs, General Tools and Exception Handling
- Secretary of main program: initialization module
- Always make sure your code functions properly: test modules