cmake_minimum_required(VERSION 3.0)

project(Modern-Cpp-Cookbook VERSION 0.0.1)

# list(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/CMakeModules")

# find_package(Boost REQUIRED serialization system)
# find_package(Threads)

add_executable(Chapter01
  ${CMAKE_SOURCE_DIR}/Chapter01/main.cpp
  ${CMAKE_SOURCE_DIR}/Chapter01/recipe_1_11_1.cpp
  ${CMAKE_SOURCE_DIR}/Chapter01/recipe_1_11_2.cpp)
target_compile_features(Chapter01 PUBLIC cxx_std_17)

add_executable(Chapter02 ${CMAKE_SOURCE_DIR}/Chapter02/main.cpp)
target_compile_features(Chapter02 PUBLIC cxx_std_17)

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
