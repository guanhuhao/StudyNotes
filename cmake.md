# CMake
## 杂七杂八
cmake会自动定义两个变量
>${PROJECT_SOURCE_DIR}： 当前工程最上层的目录
${PROJECT_BINARY_DIR}：　当前工程的构建目录（本例中新建的build目录）
${CMAKE_CURRENT_LIST_DIR} : 表示当前CMakeLists所在的路径

cmake指令不严格区分大小写,但变量严格区分大小写
## 语法
### project
```cmake
project(<PROJECT-NAME> [LANGUAGES] [<language-name>...])
```
>* PROJECT-NAME: 工程名
>* 例子：project(apps)

### include_directories
```cmake
include_directories([AFTER|BEFORE] [SYSTEM] dir1 [dir2 ...])
```
>* AFTER 或者 BEFORE 指定了要添加的路径是添加到原有包含列表之前或之后
>* 若指定 SYSTEM 参数，则
+
把被包含的路径当做系统包含路径来处理
>* 把dir1, [dir2 …]这（些）个路径添加到当前CMakeLists及其子CMakeLists的头文件包含路径中;
>* 例子：include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

### add_executable
```cmake
add_executable(<name> [WIN32] [MACOSX_BUNDLE]
               [EXCLUDE_FROM_ALL]
               source1 [source2 ...])
```
>* name: 工程所要构建的目标名称 
>* WIN32/MACOSX_BUNDLE: 目标app运行的平台  
>* source1：构建目标App的源文件 
>* 例子:add_executable(func func.cpp)


## 参考链接
简书CMack官方教程：https://www.jianshu.com/p/6df3857462cd
常用命令/变量:https://elloop.github.io/tools/2016-04-10/learning-cmake-2-commands
