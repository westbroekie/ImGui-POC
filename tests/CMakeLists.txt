cmake_minimum_required(VERSION 3.25)

add_executable(EngineTests
    test_engine.cpp
)

target_link_libraries(EngineTests PRIVATE engine)

target_link_libraries(EngineTests PRIVATE
    project_sanitizers
    project_warnings
)

add_test(NAME EngineTests COMMAND EngineTests)
