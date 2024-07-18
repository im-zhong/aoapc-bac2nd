add_executable(test_ch3_program1 program1.cpp)
target_link_libraries(test_ch3_program1 PRIVATE doctest::doctest)

add_executable(test_ch3_program2 program2.cpp)
target_link_libraries(test_ch3_program2 PRIVATE doctest::doctest)

add_executable(test_ch3_program3 program3.cpp)
target_link_libraries(test_ch3_program3 PRIVATE doctest::doctest)

add_executable(test_ch3_program4 program4.cpp)
target_link_libraries(test_ch3_program4 PRIVATE doctest::doctest)
