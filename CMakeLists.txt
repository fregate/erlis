cmake_minimum_required(VERSION 3.24)

project(ErlangInteractiveShell
	VERSION 2.0
	LANGUAGES CXX
	DESCRIPTION "Erlang Interactive Shell"
)

option(ERLIS_TESTS "Tests" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
find_package(Erlang REQUIRED)

set(LIBRARY_NAME erlis)

add_library(${LIBRARY_NAME} STATIC)
target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_20)
target_sources(${LIBRARY_NAME}
	PUBLIC
		include/erlis/ErlIS.h

	PRIVATE
		src/ErlIS.cpp
		src/ei_malloc.cpp
		src/ei_malloc.h
		src/ei_new_format.cpp
		src/ei_new_format.h
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		include
)

target_link_libraries(${LIBRARY_NAME}
	PUBLIC
		Erlang::EI
		Erlang::Erlang
)

if(ERLIS_TESTS)
	add_subdirectory(tests)
endif(ERLIS_TESTS)
