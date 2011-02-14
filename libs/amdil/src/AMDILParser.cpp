/*
 * Copyright (c) 2011 Justin Holewinski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */


#include "gputools/amdil/AMDILParser.hpp"


namespace gputools
{
namespace amdil
{

AMDILParser::AMDILParser()
{
}

AMDILParser::~AMDILParser()
{
}

SourceFile* AMDILParser::parseFile(const std::string& filename)
{
  // Open the input file.
  std::ifstream stream(filename.c_str(), std::ios::in | std::ios::binary);
  if(!stream.is_open())
  {
    throw std::runtime_error("Unable to open input file");
  }

  // Parse the stream as an AMDIL file stream.
  SourceFile* source = parseStream(stream);

  // Close the file stream.
  stream.close();

  // Return the AST.
  return source;
}

SourceFile* AMDILParser::parseStream(std::istream& stream)
{
  return NULL;
}

}
}
