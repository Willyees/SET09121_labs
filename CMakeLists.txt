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
target_link_libraries(practical_2 sfml_graphics)
set_target_properties(practical_2 PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/$(Configuration))

