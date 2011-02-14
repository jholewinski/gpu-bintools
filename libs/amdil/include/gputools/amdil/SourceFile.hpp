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

#if !defined(GPUTOOLS_AMDIL_SOURCE_FILE_HPP_INC)
#define GPUTOOLS_AMDIL_SOURCE_FILE_HPP_INC 1

#include "gputools/amdil/Scope.hpp"

namespace gputools
{
namespace amdil
{

class Function;

/**
 * Representation of a source file containing AMDIL.
 */
class SourceFile : public Scope
{

public:

  /**
   * Adds a literal declaration.
   *
   * @param[in] name  The literal name.
   * @param[in] val0  The first literal value.
   * @param[in] val1  The second literal value.
   * @param[in] val2  The third literal value.
   * @param[in] val3  The fourth literal value.
   */
  void addLiteral(const std::string& name,
                  const std::string& val0,
                  const std::string& val1,
                  const std::string& val2,
                  const std::string& val3);

  /**
   * Adds a generic declaration statement.
   *
   * @param[in] decl  The declaration statement.
   */
  void addDeclaration(const std::string& decl);

  /**
   * Adds a Function to the file.
   *
   * @param[in] function  The Function to add.
   */
  void addFunction(Function* function);
  
  /**
   * Prints the SourceFile to a stream.
   *
   * @param[in] stream  The output stream.
   */
  void print(std::ostream& stream);
  
  /**
   * Creates a new SourceFile node.
   *
   * @param[in] name      The source file name.
   * @param[in] version   The AMDIL version string.
   *
   * @return The created SourceFile node.
   */
  static SourceFile* createSourceFile(const std::string& name,
                                      const std::string& version);
  
protected:

  /**
   * Constructor.
   *
   * @param[in] name      The source file name.
   * @param[in] version   The AMDIL version string.
   */
  SourceFile(const std::string& name,
             const std::string& version);

  /**
   * Destructor.
   */
  virtual ~SourceFile();



private:

  struct LiteralValue
  {
    std::string first;
    std::string second;
    std::string third;
    std::string fourth;
  };

  typedef std::map<std::string, LiteralValue> LiteralMap;
  typedef std::list<std::string>              StringList;
  typedef std::list<Function*>                FunctionList;
  
  std::string  name_;
  std::string  version_;
  LiteralMap   literals_;
  StringList   declarations_;
  FunctionList functions_;
  
};

}
}

#endif
