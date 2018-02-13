cmake_minimum_required(VERSION 3.9)
# require modern c++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Games_Engineering)

##setup directories ##
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")

# Ouput  all  DLLs  from  all  libs  into  main  build  folder
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})


#### Add  External  Dependencies  ####

add_subdirectory("lib/sfml")

set(SFML_INCS "lib/sfml/include")

link_directories("${CMAKE_BINARY_DIR}/lib/sfml/lib")

####  Practical 1 ####

file(GLOB_RECURSE  SOURCES  practical_1/*.cpp  practical_1/*.h)

add_executable(PRACTICAL_1 ${SOURCES})

target_include_directories(PRACTICAL_1 PRIVATE ${SFML_INCS})

target_link_libraries(PRACTICAL_1 sfml-graphics)


### Practical 2 ###
file(GLOB_RECURSE SOURCES practical_2/*.cpp practical_2/*.h)
add_executable(practical_2 ${SOURCES})
target_include_directories(practical_2 SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(practical_2 sfml-graphics)

add_custom_target(copy_resources ALL COMMAND ${CMAKE_COMMAND}
  -E copy_directory
  "${PROJECT_SOURCE_DIR}/res"
  ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$<CONFIGURATION>/res)
add_dependencies(practical_2 copy_resources)

### Practical 3 ##
file(GLOB_RECURSE SOURCES practical_3/*.cpp practical_3/*.h)
add_executable(practical_3 ${SOURCES})
target_include_directories(practical_3 SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(practical_3 sfml-graphics lib_tile_level_loader lib_maths)
set_target_properties(practical_3 
	 PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY
	 ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))
##Tile loader lib
file(GLOB_RECURSE SOURCE_FILES lib_tile_level_loader/*.cpp lib_tile_level_loader/*.h)
add_library(lib_tile_level_loader STATIC ${SOURCE_FILES})
target_include_directories(lib_tile_level_loader INTERFACE
		"${CMAKE_SOURCE_DIR}/lib_tile_level_loader/" ${SFML_INCS})
target_link_libraries(lib_tile_level_loader sfml-graphics lib_maths)

##Math libs
add_library(lib_maths INTERFACE)
target_sources(lib_maths INTERFACE
	"${CMAKE_SOURCE_DIR}/lib_maths/maths.h" )
target_include_directories(lib_maths INTERFACE "${CMAKE_SOURCE_DIR}/lib_maths"
	SYSTEM INTERFACE ${SFML_INCS})

## Practical_4
file(GLOB_RECURSE SOURCES practical_4/*.h practical_4/*.cpp)
add_executable(practical_4 ${SOURCES})
target_include_directories(practical_4 SYSTEM PRIVATE ${SFML_INCS})
target_link_libraries(practical_4 sfml-graphics)