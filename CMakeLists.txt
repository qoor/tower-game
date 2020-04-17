cmake_minimum_required (VERSION 3.1)

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (PROJECT_SOURCES
	src/main.c
	src/tower.c
	src/tower_game.c

	include/tower.h
	include/tower_game.h
)

add_executable (tower-game ${PROJECT_SOURCES})

target_include_directories (tower-game PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

set_property (TARGET tower-game PROPERTY C_STANDARD 90)
target_compile_options (tower-game PUBLIC -g -Wall -pedantic)

