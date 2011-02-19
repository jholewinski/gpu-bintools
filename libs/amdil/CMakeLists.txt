#
# Copyright (c) 2011 Justin Holewinski
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#


# Define sources
set(_sources  "AmdIlFile.cpp"
              "AmdIlParser.cpp"
              "Operand.cpp"
              "${CMAKE_CURRENT_BINARY_DIR}/gpubintools/amdil/GeneratedInstructions.cpp")

set(_headers  "${_header_root}/amdil/AmdIlFile.hpp"
              "${_header_root}/amdil/AmdIlParser.hpp"
              "${_header_root}/amdil/Operand.hpp"
              "${CMAKE_CURRENT_BINARY_DIR}/gpubintools/amdil/GeneratedInstructions.hpp")


# Create target to generate AST nodes
file(MAKE_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/gpubintools/amdil")
add_custom_command(OUTPUT   "${CMAKE_CURRENT_BINARY_DIR}/gpubintools/amdil/GeneratedInstructions.cpp" "${CMAKE_CURRENT_BINARY_DIR}/gpubintools/amdil/GeneratedInstructions.hpp"
                   COMMAND  python ${CMAKE_CURRENT_SOURCE_DIR}/../../tools/generate-ast/generate-amdil-ast.py ${CMAKE_CURRENT_BINARY_DIR}/gpubintools/amdil
                   MAIN_DEPENDENCY  ${CMAKE_CURRENT_SOURCE_DIR}/../../tools/generate-ast/generate-amdil-ast.py
                   COMMENT  "Generating AMDIL AST C++ nodes")
include_directories(${CMAKE_CURRENT_BINARY_DIR})


# Include local headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


# Add library target
add_library(gpubintools-amdil STATIC ${_sources} ${_headers})

# Add library install target
install(TARGETS gpubintools-amdil ARCHIVE DESTINATION lib)
