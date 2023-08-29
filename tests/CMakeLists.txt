set(TESTS_NAME ${LIBRARY_NAME}Tests)

add_executable(${TESTS_NAME}
	main.cpp
)

target_compile_features(${TESTS_NAME} PUBLIC cxx_std_20)

target_link_libraries(${TESTS_NAME}
PRIVATE
	${LIBRARY_NAME}
)
