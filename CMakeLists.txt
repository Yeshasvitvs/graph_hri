SET(PROJECTNAME graph_hri)
project(${PROJECTNAME})
cmake_minimum_required(VERSION 2.8)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

#find_package(OGDF REQUIRED)
FIND_PACKAGE(TULIP REQUIRED)


#SET(OGDF_DIR "/home/yeshi/OGDF")
INCLUDE_DIRECTORIES(/home/yeshi/OGDF/include ${TulipCoreBuildInclude} ${TulipCoreInclude} ${TulipOGLInclude} ${TulipGUIInclude})
link_directories(/home/yeshi/OGDF/_release)


FILE(GLOB SOURCES "*.cu" "*.cpp" "*.c" "*.h" "*.hpp")
#aux_source_directory(. SRC_LIST)


add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} ${TulipLibs} ${TULIP_LIBRARIES} OGDF COIN pthread)



