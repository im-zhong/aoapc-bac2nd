add_executable(test_ch3_program1 program1.cpp)
target_link_libraries(test_ch3_program1 PRIVATE doctest::doctest)

add_executable(test_ch3_program2 program2.cpp)
target_link_libraries(test_ch3_program2 PRIVATE doctest::doctest)

add_executable(test_ch3_program3 program3.cpp)
target_link_libraries(test_ch3_program3 PRIVATE doctest::doctest)

add_executable(test_ch3_program4 program4.cpp)
target_link_libraries(test_ch3_program4 PRIVATE doctest::doctest)

add_executable(test_ch3_example1 example1.cpp)
target_link_libraries(test_ch3_example1 PRIVATE doctest::doctest)

add_executable(test_ch3_example2 example2.cpp)
target_link_libraries(test_ch3_example2 PRIVATE doctest::doctest)

add_executable(test_ch3_example3 example3.cpp)
target_link_libraries(test_ch3_example3 PRIVATE doctest::doctest)

add_executable(test_ch3_example4 example4.cpp)
target_link_libraries(test_ch3_example4 PRIVATE doctest::doctest)
