# 声明要求的CMake最低版本
cmake_minimum_required(VERSION 2.8)

# 声明一个cmake工程
project(HelloSLAM)

# 设置编译模式:断点调试模式
set(CMAKE_BUILD_TYPE "Debug")

# 添加一个可执行程序
# 语法：add_executable(程序名 源代码文件)
add_executable(helloSLAM helloSLAM.cpp)

# 添加一个叫做hello的库，编译后会生成一个libHello.a的文件，这就是我们得到的库
add_library(hello libHelloSLAM.cpp)
# 编译成共享库，而不是静态库，以.so结尾的文件
add_library(hello_shared SHARED libHelloSLAM.cpp)

# 添加可执行程序调用hello库中函数
add_executable(useHello useHello.cpp)
# 将库文件链接到可执行程序上
target_link_libraries(useHello hello_shared)
