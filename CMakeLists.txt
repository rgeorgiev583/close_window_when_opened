project(close_window_when_opened)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBWNCK REQUIRED IMPORTED_TARGET libwnck-3.0)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PkgConfig::LIBWNCK)

install(TARGETS ${PROJECT_NAME})
