cmake_minimum_required(VERSION 3.16.0)

project(File-Editor VERSION 1 LANGUAGES C CXX)

list(APPEND CMAKE_PREFIX_PATH "C:\\Qt\\6.8.0\\mingw_64")

list(APPEND CMAKE_PREFIX_PATH "C:\\opencv-4.11.0")




set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(GNUInstallDirs)

set(CMAKE_AUTOUIC_SEARCH_PATHS ${CMAKE_CURRENT_SOURCE_DIR}/ui)

find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

find_package(OpenCV REQUIRED COMPONENTS)

# Explicitly include header files for MOC processing
file(GLOB SOURCES LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/cpp/*.cpp)
file(GLOB HEADERS LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/hpp/*.h)
file(GLOB UI LIST_DIRECTORIES FALSE CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/ui/*.ui)

qt_add_resources(SOURCES resources/fonts.qrc )

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS} ${UI} ${CMAKE_CURRENT_SOURCE_DIR}/resources/icon.rc)

set_target_properties(${PROJECT_NAME} PROPERTIES WIN32_EXECUTABLE YES)

include_directories(${PROJECT_NAME} ${OpenCV_INCLUDE_DIRS} )

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Gui Qt6::Widgets Qt6::Core ${OpenCV_LIBS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/hpp)
