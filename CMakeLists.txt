//TA ADAM
cmake_minimum_required(VERSION 3.15)
project(HelloWorld VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
include(CTest)
enable_testing()
add_executable(HelloWorld main.cpp)
add_executable(superSearch main.cpp Document.h FileHandler.cpp IndexEntry.cpp IndexHandler.cpp porter2_stemmer.cpp QueryEngine.cpp Tree.h FilterEntry.h)
target_link_libraries(superSearch porter2-stemmer)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

//TA Michael
#cmake_minimum_required(VERSION 3.15)
#project(SearchEngine VERSION 0.1.0)
## filesystem.h require C++17
#set(CMAKE_CXX_STANDARD 17)
#file(COPY sample_data/ DESTINATION sample_data/)
## show compiler output and enable warnings
#set(CMAKE_VERBOSE_MAKEFILE ON)
#add_compile_options(-Wall -Wextra -pedantic)
#add_executable(HelloWorld main.cpp)
#add_executable(RapidJSONExample rapidJSONExample.cpp)
#add_executable(superSearch main.cpp Document.h FileHandler.cpp IndexEntry.cpp IndexHandler.cpp porter2_stemmer.cpp QueryEngine.cpp Tree.h FilterEntry.h)
## this makes sure we also link rapidjson
#target_include_directories(HelloWorld PRIVATE rapidjson/)
#target_include_directories(RapidJSONExample PRIVATE rapidjson/)
#target_include_directories(superSearch PRIVATE rapidjson/)
#set(CMAKE_VERBOSE_MAKEFILE OFF)
