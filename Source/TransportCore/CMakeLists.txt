SET(TransportCorePublicHeaders
  API/TransportCore.h
  API/TransportCoreBase.h
  API/TransportCoreErrorCode.h
  API/TransportCoreOption.h
)

SET(TransportCorePrivateHeaders
  Log/Log.h
  Task/Scheduler.h
  Task/Task.h
  Task/TaskManager.h
  Global/Global.h
  Global/Option.h
  CDN/HTTPClient.h
  CDN/HTTPRequest.h
  CDN/HTTPLink.h
)

SET(TransportCoreSources
  API/TransportCore.cc
  API/TransportCoreErrorCode.cc
  Task/TaskManager.cc
  Task/Scheduler.cc
  Log/Log.cc
  Global/Global.cc
  CDN/HTTPClient.cc
  CDN/HTTPRequest.cc
  CDN/HTTPLink.cc
  CDN/HTTPHeader.cc
  CDN/HTTPHeader.h
)

SET(TransportCoreTestSources
  API/TransportCoreTest.cc
  Task/TaskManagerTest.cc
  CDN/HTTPLinkTest.cc
)

SET(TransportCoreAllFiles 
  ${TransportCorePublicHeaders}
  ${TransportCorePrivateHeaders}
  ${TransportCoreSources}
  ${TransportCoreTestSources}
)

ADD_LIBRARY(TransportCore
  ${TransportCorePublicHeaders}
  ${TransportCorePrivateHeaders}
  ${TransportCoreSources}
)
TARGET_LINK_LIBRARIES(TransportCore PRIVATE TX ${TK_LIBRARIES})

ADD_EXECUTABLE(TransportCore_Test ${TransportCoreTestSources})
TARGET_LINK_LIBRARIES(TransportCore_Test TransportCore GTest::gtest_main)

SOURCE_GROUP(TREE ${CMAKE_CURRENT_SOURCE_DIR}
  FILES ${TransportCoreAllFiles}
)
