# Set up library name
set(TK "TransportKit")

# Set up source directory
set(TK_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${TK_SOURCE_DIR})
add_definitions(-DTK_SOURCE_DIR="${TK_SOURCE_DIR}")

# Set up TK modules
add_subdirectory(Transport)
add_subdirectory(TX)
set(TK_LIBS Transport TX)

# Set up TK files
file(GLOB TK_HEADERS ${TK_SOURCE_DIR}/*.h)
file(GLOB TK_SOURCES ${TK_SOURCE_DIR}/*.cc)

# Set up the TK shared library
add_library(${TK} SHARED ${TK_HEADERS} ${TK_SOURCES})
target_compile_definitions(${TK} PRIVATE -DBUILD_TK -Dfvisibility=hidden)
target_link_libraries(${TK} PRIVATE ${TK_LIBS})

# Set up TK static library
if (TK_STATIC)
  add_library(${TK}_Static STATIC ${TK_HEADERS} ${TK_SOURCES})
  set_target_properties(${TK}_Static PROPERTIES OUTPUT_NAME ${TK})
  target_link_libraries(${TK}_Static PRIVATE ${TK_LIBS})
endif (TK_STATIC)