add_executable(mvpr_log_example main.cpp)

include_directories(../MVPRLog/include)

target_link_libraries(mvpr_log_example mvpr_log)