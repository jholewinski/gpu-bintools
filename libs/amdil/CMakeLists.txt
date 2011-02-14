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
set(_sources  "src/AMDILParser.cpp"
              "src/ASTNode.cpp"
              "src/Function.cpp"
              "src/Instruction.cpp"
              "src/SourceFile.cpp")

set(_headers  "include/gputools/amdil/AMDILParser.hpp"
              "include/gputools/amdil/ASTNode.hpp"
              "include/gputools/amdil/Function.hpp"
              "include/gputools/amdil/Instruction.hpp"
              "include/gputools/amdil/SourceFile.hpp")


# Include local headers
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)


# Add library target
add_library(gputools-amdil STATIC ${_sources} ${_headers})

# Add library install target
install(TARGETS gputools-amdil ARCHIVE DESTINATION lib)

# Add header install target
install(DIRECTORY include/gputools/amdil DESTINATION include/gputools)
