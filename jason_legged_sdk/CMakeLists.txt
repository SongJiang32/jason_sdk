cmake_minimum_required(VERSION 3.1.0)
project(jason_legged_sdk)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")

include_directories(include)  # 指定头文件的搜索路径
link_directories(lib)         # 指定库文件的搜索路径

if(CMAKE_HOST_SYSTEM_PROCESSOR MATCHES "aarch64") 
    set(EXTRA_LIBS libUnitreeMotorSDK_Arm64.so)
else()
    set(EXTRA_LIBS libUnitreeMotorSDK_Linux64.so)
endif()

# demo
add_executable(unitree_GO_M8010_6
    demo/unitree_GO_M8010_6_test.cpp # 指定编译目标，将 demo/unitree_GO_M8010_6_test.cpp 这个源文件编译成一个名为 unitree_GO_M8010_6 的可执行文件
    src/unitree/legControl/legControl.cpp   # 链接器需要 cpp 文件里的具体实现
)
target_link_libraries(unitree_GO_M8010_6 ${EXTRA_LIBS}) # 链接库文件


# 生成动态库,便于其他项目调用
add_library(jason_legged_sdk SHARED
    src/unitree/legControl/legControl.cpp
    # 可以继续添加其它源码文件
)
target_include_directories(jason_legged_sdk PUBLIC include)  # target_include_directories(目标名 可见性 目录路径)，当其他项目或目标链接 jason_legged_sdk 这个库时，编译时都会自动把你的 include 目录加入到编译器的头文件搜索路径。