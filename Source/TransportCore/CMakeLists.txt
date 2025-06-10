ENABLE_TESTING()

SET(TransportCorePrivateHeaders
  Task/Task.h
  Task/TaskManager.h
  Task/TaskListener.h
  Task/Scheduler.h
  Log/Log.h
)

SET(TransportCoreSources
  Task/Task.cc
  Task/TaskManager.cc
  Task/Scheduler.cc
)

SET(TransportCoreTestSources
  Task/TaskManagerTest.cc
)

ADD_LIBRARY(TransportCore ${TransportCorePrivateHeaders} ${TransportCoreSources})
TARGET_LINK_LIBRARIES(TransportCore PRIVATE TX)

ADD_EXECUTABLE(TransportCore_Test ${TransportCoreTestSources})
TARGET_LINK_LIBRARIES(TransportCore_Test TransportCore GTest::gtest_main)
INCLUDE(GoogleTest)
GTEST_DISCOVER_TESTS(TransportCore_Test)
