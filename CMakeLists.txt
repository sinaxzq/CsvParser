cmake_minimum_required(VERSION 3.20)

project(CsvAnalyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

function(enable_strict_warnings target_name)
    if(MSVC)
        target_compile_options(${target_name} PRIVATE /W4 /WX)
    else()
        target_compile_options(${target_name} PRIVATE -Wall -Wextra -Wpedantic -Werror)
    endif()
endfunction()

add_library(CsvAnalyzerCore
    CsvParser.cpp
)

target_include_directories(CsvAnalyzerCore PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

enable_strict_warnings(CsvAnalyzerCore)

add_executable(CsvAnalyzerApp
    main.cpp
)

target_link_libraries(CsvAnalyzerApp PRIVATE
    CsvAnalyzerCore
)

enable_strict_warnings(CsvAnalyzerApp)

add_executable(CsvAnalyzerTests
    CsvParserTests.cpp
)

target_link_libraries(CsvAnalyzerTests PRIVATE
    CsvAnalyzerCore
)

enable_strict_warnings(CsvAnalyzerTests)

enable_testing()

add_test(NAME CsvAnalyzerTests COMMAND CsvAnalyzerTests)