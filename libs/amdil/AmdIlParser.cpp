
#include "gpubintools/Common.hpp"
#include "gpubintools/amdil/AmdIlParser.hpp"
#include "gpubintools/amdil/AmdIlFile.hpp"
#include "gpubintools/amdil/GeneratedInstructions.hpp"
#include "gpubintools/amdil/Operand.hpp"


namespace ba = boost::algorithm;

namespace gpubintools
{
namespace amdil
{

AmdIlParser::AmdIlParser()
{
}

AmdIlParser::~AmdIlParser()
{
}


AmdIlFile* AmdIlParser::parseFile(const std::string& filename)
{
  typedef std::vector<std::string> StringVector;

  AmdIlFile*  file;
  std::string line;
  
  std::ifstream stream(filename.c_str(), std::ios::in | std::ios::binary);
  if(!stream.is_open())
  {
    std::cerr << "Unable to open AMDIL source file: " << filename << std::endl;
    return NULL;
  }

  file = new AmdIlFile();
  
  // AMDIL is a line-oriented language
  while(std::getline(stream, line).good())
  {
    // Trim leading whitespace.
    ba::trim_left(line);

    // Determine if we have a comment on this line.
    size_t commentBegin = line.find_first_of(';');
    if(commentBegin != line.npos)
    {
      // We have a comment, so extract the un-commented sub-string.
      if(commentBegin == 0)
      {
        // Special case:  The line begins with a semi-colon.
        continue;
      }
      else
      {
        // Extract the pre-comment portion.
        line = line.substr(0, commentBegin);
      }
    }

    // Now trim the leading/trailing whitespace.
    ba::trim(line);
    if(line.size() == 0)
    {
      continue;
    }

    std::cout << "****** " << line << std::endl;
    
    // Now we can finally parse the line.
    if(ba::starts_with(line, "dcl"))
    {
      // We have some sort of dcl instruction.
      std::cout << "dcl" << std::endl;
    }
    else if(ba::starts_with(line, "uav"))
    {
      // We have some sort of uav access instruction.
    }
#include "gpubintools/amdil/ParserSupport.inl"
    else
    {
      std::cerr << "FATAL:  Unknown instruction:  " << line << std::endl;
      return NULL;
    }
  }

  return file;
}

Operand* AmdIlParser::parseOperand(const std::string& text)
{
  boost::regex  registerRegEx;
  boost::regex  literalRegEx;
  boost::regex  constantBufferRegEx;
  boost::smatch matches;

  registerRegEx.assign("(r[0-9]+)(\\.[xyzw0_]([xyzw0_][xyzw0_][xyzw0_])?)?");
  literalRegEx.assign("(l[0-9]+)(\\.[xyzw0]([xyzw0][xyzw0][xyzw0])?)?");
  constantBufferRegEx.assign("(cb[0-9]+)\\[([0-9]+)\\](\\.[xyzw0_]([xyzw0_][xyzw0_][xyzw0_])?)?");

  if(boost::regex_match(text, matches, registerRegEx))
  {
    std::string registerText(matches[1].first+1, matches[1].second);
    std::string maskText(matches[2].first, matches[2].second);

    if(maskText.size() > 0)
    {
      // Remove leading period.
      maskText = maskText.substr(1);
    }

    //std::cout << "Register:  " << registerText << "  Mask:  " << maskText << std::endl;
  }
  else if(boost::regex_match(text, matches, literalRegEx))
  {
    std::string literalText(matches[1].first+1, matches[1].second);
    std::string maskText(matches[2].first, matches[2].second);

    if(maskText.size() > 0)
    {
      // Remove leading period.
      maskText = maskText.substr(1);
    }

    //std::cout << "Literal:  " << literalText << "  Mask:  " << maskText << std::endl;
  }
  else if(boost::regex_match(text, matches, constantBufferRegEx))
  {
    std::string indexText(matches[1].first+2, matches[1].second);
    std::string offsetText(matches[2].first, matches[2].second);
    std::string maskText(matches[3].first, matches[3].second);

    if(maskText.size() > 0)
    {
      // Remove leading period.
      maskText = maskText.substr(1);
    }

    //std::cout << "Constant Buffer:  " << indexText << "  Offset:  " << offsetText << "  Mask:  " << maskText << std::endl;
  }
  else
  {
    std::cerr << "Unknown operand type:  " << text << std::endl;
  }
  
  
  return new Operand();
}

}
}
