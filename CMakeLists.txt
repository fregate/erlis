cmake_minimum_required(VERSION 3.24)

project(ErlangInteractiveShell
	VERSION 2.0
	LANGUAGES CXX
	DESCRIPTION "Erlang Interactive Shell"
)

option(ERLIS_TESTS "Tests" OFF)

set(LIBRARY_NAME erlis)

add_library(${LIBRARY_NAME} STATIC)

target_compile_features(${LIBRARY_NAME} PUBLIC cxx_std_20)

target_sources(${LIBRARY_NAME}
	PUBLIC
		include/erlis/ErlIS.h

	PRIVATE
		src/ErlIS.cpp
)

target_include_directories(${LIBRARY_NAME}
	PUBLIC
		include
)

add_custom_target(piped_erlang_vm ALL
	COMMAND
		erlc ${CMAKE_CURRENT_SOURCE_DIR}/erl/piped.erl
)

if(ERLIS_TESTS)
	add_subdirectory(tests)
endif(ERLIS_TESTS)
