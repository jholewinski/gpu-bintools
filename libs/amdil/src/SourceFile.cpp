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


#include "gputools/amdil/SourceFile.hpp"
#include "gputools/amdil/Function.hpp"


namespace gputools
{
namespace amdil
{

SourceFile::SourceFile(const std::string& name,
                       const std::string& version)
  : name_(name),
    version_(version)
{
}

SourceFile::~SourceFile()
{
}

void SourceFile::addLiteral(const std::string& name,
                            const std::string& val0,
                            const std::string& val1,
                            const std::string& val2,
                            const std::string& val3)
{
  if(literals_.find(name) != literals_.end())
  {
    throw std::runtime_error("Duplicate literal");
  }

  LiteralValue literal;
  literal.first  = val0;
  literal.second = val0;
  literal.third  = val0;
  literal.fourth = val0;
  
  literals_[name] = literal;
}

void SourceFile::addDeclaration(const std::string& decl)
{
  declarations_.push_back(decl);
}

void SourceFile::addFunction(Function* function)
{
  functions_.push_back(function);
}

void SourceFile::print(std::ostream& stream)
{
  // Print version
  stream << version_ << std::endl;
  stream << std::endl;

  // Print declarations
  StringList::const_iterator declIter;
  for(declIter = declarations_.begin(); declIter != declarations_.end(); ++declIter)
  {
    stream << *declIter << std::endl;
  }
}

SourceFile* SourceFile::createSourceFile(const std::string& name,
                                         const std::string& version)
{
  return new SourceFile(name, version);
}

}
}
