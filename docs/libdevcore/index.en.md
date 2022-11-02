# libdevcore

The basic development core library of devkits, libdevccore, is mainly used to provide encapsulation of tools commonly used in software development. It mainly consists of the following contents:

- [Log](./log.en.md)
- Exceptions
- ThreadPool
- Utility

After using the content in libdevcore, you need to add the `devcore` library to the executable dependency, which is represented in `CMakeLists.txt` as follows:

```cmake
add_executable(${app_name} ${app_src})
target_link_libraries(${app_name} devcore)
```

