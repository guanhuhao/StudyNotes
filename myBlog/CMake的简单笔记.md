## 杂七杂八
cmake会自动定义几个变量   
> \${PROJECT_SOURCE_DIR}： 当前工程最上层的目录  
> \${PROJECT_BINARY_DIR}：　当前工程的构建目录（本例中新建的build目录）  
> \${CMAKE_CURRENT_LIST_DIR} : 表示当前CMakeLists所在的路径  

cmake指令区分大小写,但变量严格区分大小写  
## 语法
### project
```cmake
project(<PROJECT-NAME> [LANGUAGES] [<language-name>...])  
```
>* PROJECT-NAME: 工程名   
>* 例子：project(apps)   

参数解释：
> name: 工程所要构建的目标名称    
> WIN32/MACOSX_BUNDLE: 目标app运行的平台   
> source1：构建目标App的源文件  

例子:add_executable(func func.cpp)  


## 常用cmake 设置
```
#add_executable(project1 ${src})                        #编译为可执行程序
#add_library(project1 ${src})                           #编译为静态库
#add_library(project1 SHARED ${src})                    #编译为动态链接库

#add_executable(project1 MACOSX_BUNDLE ${src})          #编译为可执行程序 *.app

#add_library(project1 MODULE ${src})                    #编译为程序资源包 *.bundle
#set_target_properties(project1 PROPERTIES BUNDLE TRUE)

#add_library(project1 SHARED ${src})                     #编译为程序资源包 *.framework
#set_target_properties(project1 PROPERTIES FRAMEWORK TRUE)

SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")  # Debug模式下的编译指令
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")         # Release模式下的编译指令

# SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../bin)       #设置可执行文件的输出目录

# SET(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../lib)           #设置库文件的输出目录


# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/bin)   

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../bin) 

# 上面两条语句分别设置了Debug版本和Release版本可执行文件的输出目录,

# 一旦设置上面的属性,在任何环境下生成的可执行文件都将直接放在你所设置的目录.

# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG ${PROJECT_SOURCE_DIR}/../lib)    
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE ${PROJECT_SOURCE_DIR}/../lib) 

# 上面两条语句分别设置了Debug版本和Release版本库文件的输出目录,

# 一旦设置上面的属性,在任何环境下生成的库文件都将直接放在你所设置的目录.
```

## 参考链接
简书CMack官方教程：https://www.jianshu.com/p/6df3857462cd  
常用命令/变量:https://elloop.github.io/tools/2016-04-10/learning-cmake-2-commands  
常用设置:https://blog.csdn.net/nan_feng_yu/article/details/80808773  

