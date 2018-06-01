cmake_minimum_required(VERSION 3.0)

project(Modern-Cpp-Cookbook VERSION 0.0.1)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")

# find_package(Boost REQUIRED serialization system)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

# Chapter 1 - Learning Modern Core Language Features
add_executable(Chapter01
  ${CMAKE_SOURCE_DIR}/Chapter01/main.cpp
  ${CMAKE_SOURCE_DIR}/Chapter01/recipe_1_11_1.cpp
  ${CMAKE_SOURCE_DIR}/Chapter01/recipe_1_11_2.cpp)
target_compile_features(Chapter01 PUBLIC cxx_std_17)

# Chapter 2 - Working with Numbers and Strings
add_executable(Chapter02 ${CMAKE_SOURCE_DIR}/Chapter02/main.cpp)
target_compile_features(Chapter02 PUBLIC cxx_std_17)

# Chapter 3 - Exploring Functions
add_executable(Chapter03 ${CMAKE_SOURCE_DIR}/Chapter03/main.cpp)
target_compile_features(Chapter03 PUBLIC cxx_std_17)

# Chapter 4 - Preprocessor and Compilation
add_executable(Chapter04 ${CMAKE_SOURCE_DIR}/Chapter04/main.cpp)
target_compile_features(Chapter04 PUBLIC cxx_std_17)

# Chapter 5 - Standard Library Containers, Algorithms, and Iterators
add_executable(Chapter05 ${CMAKE_SOURCE_DIR}/Chapter05/main.cpp)
target_compile_features(Chapter05 PUBLIC cxx_std_17)

# Chapter 6 - General Purpose Utilities
add_executable(Chapter06 ${CMAKE_SOURCE_DIR}/Chapter06/main.cpp)
target_compile_features(Chapter06 PUBLIC cxx_std_17)

# Chapter 7 - Working with Files and Streams
add_executable(Chapter07 ${CMAKE_SOURCE_DIR}/Chapter07/main.cpp)
target_compile_features(Chapter07 PUBLIC cxx_std_17)
target_link_libraries(Chapter07 PUBLIC stdc++fs)
add_custom_command(
  TARGET Chapter07 PRE_BUILD
  COMMAND cp ${CMAKE_SOURCE_DIR}/Chapter07/sample.plays ${CMAKE_CURRENT_BINARY_DIR})

# Chapter 8 - Leveraging Threading and Concurrency
add_executable(Chapter08 ${CMAKE_SOURCE_DIR}/Chapter08/main.cpp)
target_compile_features(Chapter08 PUBLIC cxx_std_17)
target_link_libraries(Chapter08 PUBLIC Threads::Threads)

# Chapter 9 - Robustness and Performance
add_executable(Chapter09 ${CMAKE_SOURCE_DIR}/Chapter09/main.cpp)
target_compile_features(Chapter09 PUBLIC cxx_std_17)

# Chapter 10 - Implementing Patterns and Idioms
add_executable(Chapter10 ${CMAKE_SOURCE_DIR}/Chapter10/main.cpp ${CMAKE_SOURCE_DIR}/Chapter10/control.cpp)
target_compile_features(Chapter10 PUBLIC cxx_std_17)

# Chapter 11 - Exploring Testing Frameworks

# Create compile database
add_custom_target(compile_commands ALL)

add_custom_command(
  TARGET compile_commands POST_BUILD
  COMMAND touch ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json
  COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_SOURCE_DIR}
  # COMMAND cp ${CMAKE_SOURCE_DIR}/1-Creational/5-Singleton/1-SingletonDatabase/capitals.txt ${CMAKE_CURRENT_BINARY_DIR}
  )

set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES
  # "${CMAKE_CURRENT_BINARY_DIR}/journal.txt"
  )
