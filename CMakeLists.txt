# TODO: Add project name-getting logic
cmake_minimum_required(VERSION 3.25)

set(CMAKE_TOOLCHAIN_FILE C:/vcpkg/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_CXX_STANDARD 17)

project(raekan)

find_package(wxWidgets REQUIRED COMPONENTS net core base)
if(wxWidgets_USE_FILE)
  include(${wxWidgets_USE_FILE})
endif()


set(APP_RESOURCES "${CMAKE_CURRENT_SOURCE_DIR}/resources.rc")
file(GLOB_RECURSE SRC
  CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
)

add_executable(${PROJECT_NAME} ${APP_RESOURCES} ${SRC})

target_link_libraries(${PROJECT_NAME}
  ${wxWidgets_LIBRARIES}
)
set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE TRUE)
