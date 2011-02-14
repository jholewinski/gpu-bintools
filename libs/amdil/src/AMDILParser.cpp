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
#include "gputools/amdil/SourceFile.hpp"


namespace ba = boost::algorithm;


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
  SourceFile* source = parseStream(stream, filename);

  // Close the file stream.
  stream.close();

  // Return the AST.
  return source;
}

SourceFile* AMDILParser::parseStream(std::istream&      stream,
                                     const std::string& name)
{
  // AMDIL is a line-based language, so we process input one line
  // at a time.
  SourceFile* sourceFile;
  std::string line;

  // The first line must be the AMDIL version string
  // e.g. il_cs_2_0
  getLineFromStream(stream, line);
  if(line.size() != 9)
  {
    throw std::runtime_error("Malformed AMDIL file:  no version specified.");
  }

  sourceFile = SourceFile::createSourceFile(name, line);
  
  // Now parse all non-empty lines.
  getLineFromStream(stream, line);
  while(line.size() > 0)
  {
    parseLine(stream, line, sourceFile);

    getLineFromStream(stream, line);
  }
  
  return sourceFile;
}

void AMDILParser::parseLine(std::istream& stream,
                            std::string&  line,
                            SourceFile*   sourceFile)
{
  TokenVector tokens;

  tokenizeLine(line, tokens);

  TokenVector::iterator iter;
  for(iter = tokens.begin(); iter != tokens.end(); ++iter)
  {
    (*iter).print(std::cout);
  }
  std::cout << "LINE" << std::endl;
}

void AMDILParser::tokenizeLine(std::string& line,
                               TokenVector& tokens)
{
  std::string::const_iterator charIter;
  
  tokens.clear();

  charIter = line.begin();

  while(charIter != line.end())
  {
    if(*charIter == ';')
    {
      // Start of a comment
      return;
    }
    else if(isIdentChar(*charIter))
    {
      // We have an identifier
      std::string text;

      do
      {
        text += *charIter;
        charIter++;
      } while(isIdentChar(*charIter));

      Token token;
      token.tokenType = kTokenTypeIdentifier;
      token.text      = text;

      tokens.push_back(token);
    }
    else if(*charIter == '(')
    {
      charIter++;

      Token token;
      token.tokenType = kTokenTypeOpenParen;

      tokens.push_back(token);
    }
    else if(*charIter == ')')
    {
      charIter++;

      Token token;
      token.tokenType = kTokenTypeCloseParen;

      tokens.push_back(token);
    }
    else if(*charIter == '[')
    {
      charIter++;

      Token token;
      token.tokenType = kTokenTypeOpenBrace;

      tokens.push_back(token);
    }
    else if(*charIter == ']')
    {
      charIter++;

      Token token;
      token.tokenType = kTokenTypeCloseBrace;

      tokens.push_back(token);
    }
    else if(*charIter == ',')
    {
      charIter++;

      Token token;
      token.tokenType = kTokenTypeComma;

      tokens.push_back(token);
    }
    else if(*charIter == '.')
    {
      charIter++;

      Token token;
      token.tokenType = kTokenTypePeriod;

      tokens.push_back(token);
    }
    else
    {
      charIter++;
    }
  }
}

void AMDILParser::getLineFromStream(std::istream& stream,
                                    std::string&  line)
{
  line.clear();
  
  do
  {
    if(!getline(stream, line).good())
    {
      break;
    }

    ba::trim(line);
    
  } while(line.size() == 0);
}

bool AMDILParser::isIdentChar(char ch)
{
  if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') || ch == '_')
  {
    return true;
  }
  else if((ch >= '0' && ch <= '9') || ch == '-')
  {
    return true;
  }
  else
  {
    return false;
  }
}

void AMDILParser::Token::print(std::ostream& stream)
{
  switch(tokenType)
  {
    case kTokenTypeComma:
    {
      stream << "kTokenTypeComma";
      break;
    }
    case kTokenTypeOpenParen:
    {
      stream << "kTokenTypeOpenParen";
      break;
    }
    case kTokenTypeCloseParen:
    {
      stream << "kTokenTypeCloseParen";
      break;
    }
    case kTokenTypeOpenBrace:
    {
      stream << "kTokenTypeOpenBrace";
      break;
    }
    case kTokenTypeCloseBrace:
    {
      stream << "kTokenTypeCloseBrace";
      break;
    }
    case kTokenTypePeriod:
    {
      stream << "kTokenTypePeriod";
      break;
    }
    case kTokenTypeIdentifier:
    {
      stream << "kTokenTypeIdentifier";
      break;
    }
    case kTokenTypeLiteral:
    {
      stream << "kTokenTypeLiteral";
      break;
    }
    default:
    {
      stream << "Unknown";
      break;
    }
  }

  stream << " - " << text << std::endl;
}

}
}
