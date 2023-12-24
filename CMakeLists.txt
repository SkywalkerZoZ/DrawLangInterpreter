cmake_minimum_required(VERSION 3.0.0)
project(DrawLangInterpreter VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(DrawLangInterpreter
    main.cpp
    Lexer.cpp
    Parser.cpp
    Interpreter.cpp
    DrawEngine.cpp
)

# 图形库
if(WIN32)
    target_link_libraries(DrawLangInterpreter PRIVATE gdi32)
endif()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
