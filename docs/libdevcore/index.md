# libdevcore

devkits的基础开发核心库libdevcore主要是提供在软件开发过程中常用的工具的封装，主要有以下内容组成：

- [Log](./log.md)
- Exceptions
- ThreadPool
- Utility

使用libdevcore中的内容后，需要在可执行程序依赖中添加`devcore`库，在`CMakeLists.txt`中这样表示:

```cmake
add_executable(${app_name} ${app_src})
target_link_libraries(${app_name} devcore)
```

