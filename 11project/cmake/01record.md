### demo01

```cmake
cmake_minimum_required (VERSION 2.8)
project (demo01)
# 指定生成目标
add_executable(out.demo01 main.c)
```

将名为 main.c 的源文件编译成一个名称为 Demo 的可执行文件

### demo02

```cmake
cmake_minimum_required(VERSION 2.8)
project(demo02)
# 查找当前目录下的所有源文件 aux_source_directory(. src_dir)
aux_source_directory(./code src_dir)
add_executable(out.demo02 ${src_dir})
```

### demo03 
```cmake
# 能包含模块目录下的头文件
include_directories ("${PROJECT_SOURCE_DIR}/service")
# 模块目录
add_subdirectory (service)
# 可执行文件依赖静态库
add_executable(out.demo03 main.c)
target_link_libraries (out.demo03 lib_service)
```