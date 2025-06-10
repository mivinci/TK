enable_testing()

set(TRANSPORT_HEADERS
  Log.h
  Result.h
  task/Task.h
  task/TaskManager.h
  task/TaskListener.h
)

set(TRANSPORT_SOURCES
  task/Task.cc
  task/TaskManager.cc
)

set(TRANSPORT_TEST_SOURCES
  task/TaskTest.cc
  task/TaskManagerTest.cc
)

add_library(Transport ${TRANSPORT_HEADERS} ${TRANSPORT_SOURCES})
target_link_libraries(Transport PRIVATE TX)

add_executable(Transport_Test ${TRANSPORT_TEST_SOURCES})
target_link_libraries(Transport_Test Transport GTest::gtest_main)
include(GoogleTest)
gtest_discover_tests(Transport_Test)
