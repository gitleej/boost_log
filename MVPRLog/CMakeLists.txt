set(CMAKE_CXX_STANDARD 11)


# 加入boost头文件路径
INCLUDE_DIRECTORIES(/usr/include)
set(BOOST_ROOT /usr)
set(BOOST_INCLUDEDIR ${BOOST_ROOT}/include)
set(BOOST_LIBRARYDIR ${BOOST_ROOT}/lib)
# 设置boost使用静态链接
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_SHARE_RUNTIME ON)
# 设置需要的boost 组件
set(BOOST_COMPONENTS
        log_setup
        log
        atomic
        filesystem
        chrono
        date_time
        thread
        regex
        )
# 使用cmake find_package 查找boost库位置
find_package(Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS})

include_directories(./include)
link_directories(${BOOST_ROOT}/lib/)

add_library(mvpr_log ./src/MVPRLog.cpp
        src/AbstractLogger.cpp
        src/AbstractLogConfig.cpp
        src/BoostLogger.cpp
        src/BoostLogConfig.cpp
        src/common.cpp src/Utils.cpp
        include/Utils.hpp)

message (${Boost_LIBRARIES})

target_link_libraries(mvpr_log
        ${Boost_LIBRARIES}
        pthread
#        boost_log_setup.a boost_log.a boost_atomic.a boost_filesystem.a boost_chrono.a boost_date_time.a boost_thread.a boost_regex.a boost_json.a
        )
# LD_LIBRARY_PATH=/usr/local/lib