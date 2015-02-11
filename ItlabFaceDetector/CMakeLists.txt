CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

set(PROJECT_NAME FaceDetector)
project(${PROJECT_NAME})

if (CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -Wall")
endif()

find_package(OpenCV REQUIRED)

set(Lua_LIBS 
		"/usr/local/lib/libluajit.so"
		"/usr/local/lib/libluaT.so"
		"/usr/local/lib/libTH.so"
		"/usr/local/lib/lua/5.1/libtorch.so"
		"/usr/local/lib/lua/5.1/libnn.so"
	)
set(Lua_INCLUDE "/usr/local/include")
include_directories(Lua_INCLUDE)

set(FACEDETECTOR_LIBRARY ${PROJECT_NAME})
set(SOURCE_EXE main.cpp)

set(FACEDETECTOR_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include")
include_directories(${FACEDETECTOR_INCLUDE})

set(LIBRARY_DEPS ${OpenCV_LIBS})
set(LUA_LIBRARY ${Lua_LIBS})

add_executable(main ${SOURCE_EXE})

add_subdirectory(src)
add_subdirectory(samples)

target_link_libraries(main ${LIBRARY_DEPS})
target_link_libraries(main ${FACEDETECTOR_LIBRARY})