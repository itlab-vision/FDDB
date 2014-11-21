set(target ${FACEDETECTOR_LIBRARY})

FILE(GLOB hdrs "*.h*" "${FACEDETECTOR_INCLUDE}/*.h*")
FILE(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})
target_link_libraries(${target} ${Lua_LIBS})

add_custom_command(
    TARGET ${FACEDETECTOR_LIBRARY}
    POST_BUILD
    COMMAND ln -fns "${CMAKE_SOURCE_DIR}/imgs" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/imgs"
    COMMENT "Adding a symbolic link to images"
)

add_custom_command(
    TARGET ${FACEDETECTOR_LIBRARY}
    POST_BUILD
    COMMAND ln -fns "${CMAKE_SOURCE_DIR}/scripts" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/scripts"
    COMMENT "Adding a symbolic link to scripts"
)

add_custom_command(
    TARGET ${FACEDETECTOR_LIBRARY}
    POST_BUILD
    COMMAND ln -fns "${CMAKE_SOURCE_DIR}/net" "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}/net"
    COMMENT "Adding a symbolic link to nets"
)

message( STATUS "${CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE}")