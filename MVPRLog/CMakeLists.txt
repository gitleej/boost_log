set(CMAKE_CXX_STANDARD 11)

# 加入boost头文件路径
#INCLUDE_DIRECTORIES(/usr/local/include)
set(BOOST_ROOT C:\\Boost)
set(BOOST_INCLUDEDIR ${BOOST_ROOT}\\include\\boost-1_79\\)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}\\lib)
# 设置boost使用静态链接
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_SHARE_RUNTIME ON)
# 设置需要的boost 组件
set(BOOST_COMPONENTS log atomic filesystem chrono date_time log_setup thread regex json)
# 使用cmake find_package 查找boost库位置
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})

include_directories(./include)

add_library(mvpr_log ./src/MVPRLog.cpp
        src/AbstractLogger.cpp
        src/AbstractLogConfig.cpp
        src/BoostLogger.cpp
        src/BoostLogConfig.cpp
        src/common.cpp)

target_link_libraries(mvpr_log
#        pthread
        ${Boost_LIBRARIES}
        )