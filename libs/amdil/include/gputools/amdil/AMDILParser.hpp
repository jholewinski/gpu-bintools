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
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE OR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#if !defined(GPUTOOLS_AMDIL_AMDIL_PARSER_HPP_INC)
#define GPUTOOLS_AMDIL_AMDIL_PARSER_HPP_INC 1

#include "gputools/amdil/Common.hpp"

namespace gputools
{
namespace amdil
{

class SourceFile;

/**
 * Parser for AMDIL.
 */
class AMDILParser
{
public:

  /**
   * Constructor.
   */
  AMDILParser();

  /**
   * Destructor.
   */
  ~AMDILParser();

  /**
   * Parses an AMDIL source file and returns a SourceFile pointer for the
   * created AST.
   *
   * @param[in] filename  The name of the AMDIL file on disk.
   *
   * @return A pointer to the AMDIL AST.
   */
  SourceFile* parseFile(const std::string& filename);
  
  /**
   * Parses an AMDIL source stream and returns a SourceFile pointer for the
   * created AST.
   *
   * @param[in] stream  Stream containing the AMDIL source file.
   *
   * @return A pointer to the AMDIL AST.
   */
  SourceFile* parseStream(std::istream& stream);
  
};

}
}

#endif
