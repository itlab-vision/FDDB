set(target ${FACEDETECTOR_LIBRARY})

FILE(GLOB hdrs "*.h*" "${FACEDETECTOR_INCLUDE}/*.h*")
FILE(GLOB srcs "*.cpp")

add_library(${target} STATIC ${srcs} ${hdrs})
target_link_libraries(${target} ${LIBRARY_DEPS})