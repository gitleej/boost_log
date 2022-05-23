set(SRC_FILES Testsuite.cpp Testsuite.h)

add_executable(test_log_config test_log_config.cpp ${SRC_FILES})
target_link_libraries(test_log_config mvpr_log)

add_executable(test_logger test_logger.cpp ${SRC_FILES})
target_link_libraries(test_logger mvpr_log)

add_executable(test_mvprlog test_mvpr_log.cpp ${SRC_FILES})
target_link_libraries(test_mvprlog mvpr_log)