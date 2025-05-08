cmake_minimum_required(VERSION 3.10.0)
project(InventoryManager VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

file (GLOB_RECURSE InventoryManager_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE InventoryManager_HEADERS CONFIGURE_DEPENDS "include/*.h")

set (InventoryManager_INCLUDE_DIRS "")
foreach (_headerFile ${InventoryManager_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND InventoryManager_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES InventoryManager_INCLUDE_DIRS)

add_executable(InventoryManager ${InventoryManager_SOURCES})
target_include_directories(InventoryManager PRIVATE ${InventoryManager_INCLUDE_DIRS})