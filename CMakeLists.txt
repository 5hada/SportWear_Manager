cmake_minimum_required(VERSION 3.16)

project(SportWear_Manager VERSION 0.1 LANGUAGES C CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


SET(CMAKE_PREFIX_PATH C:/Qt/6.6.2/mingw_64)

add_subdirectory(external/ElaWidgetTools)

file(GLOB_RECURSE PROJECT_SOURCES
    CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.ui"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.qrc"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/sqlite3/sqlite3.c"
    "${CMAKE_CURRENT_SOURCE_DIR}/external/sqlite3/sqlite3.h"
)

configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/src/database/schema.sql"
    "${CMAKE_CURRENT_BINARY_DIR}/schema.sql"
    COPYONLY
)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_add_executable(SportWear_Manager
    MANUAL_FINALIZATION
    ${PROJECT_SOURCES}
)

target_link_libraries(SportWear_Manager PRIVATE
    Qt6::Widgets
    ElaWidgetTools
)

target_include_directories(SportWear_Manager PRIVATE
    src
    external/ElaWidgetTools
    external/sqlite3
)

set_target_properties(SportWear_Manager PROPERTIES
    WIN32_EXECUTABLE TRUE
)

install(TARGETS SportWear_Manager
    RUNTIME DESTINATION bin
)

qt_finalize_executable(SportWear_Manager)