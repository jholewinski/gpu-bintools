
#include "gpubintools/Common.hpp"
#include "gpubintools/amdil/AmdIlParser.hpp"
#include "gpubintools/amdil/AmdIlFile.hpp"
#include "gpubintools/amdil/Instructions.hpp"
#include "gpubintools/amdil/Operand.hpp"
#include "gpubintools/amdil/Function.hpp"


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


#define UNARY_OPERATOR(text, skip, klass)                               \
  else if(ba::starts_with(line, #text))                                 \
  {                                                                     \
    std::string  rest     = line.substr(skip);                          \
    StringVector operands;                                              \
                                                                        \
    ba::split(operands, rest, boost::is_any_of(","));                   \
                                                                        \
    if(operands.size()   != 2)                                          \
    {                                                                   \
      std::cerr << "unary operators can contain only 2 operands." << std::endl; \
      return NULL;                                                      \
    }                                                                   \
                                                                        \
    ba::trim(operands[0]);                                              \
    ba::trim(operands[1]);                                              \
                                                                        \
    Operand*     dest     = parseOperand(operands[0]);                  \
    Operand*     source0  = parseOperand(operands[1]);                  \
                                                                        \
    Instruction* instr    = new klass(dest, source0);                   \
                                                                        \
    if(function == NULL)                                                \
    {                                                                   \
      file->appendInstruction(instr);                                   \
    }                                                                   \
    else                                                                \
    {                                                                   \
      function->appendInstruction(instr);                               \
    }                                                                   \
  }                                                                     \

#define BINARY_OPERATOR(text, skip, klass)                              \
  else if(ba::starts_with(line, #text))                                 \
  {                                                                     \
    std::string  rest     = line.substr(skip);                          \
    StringVector operands;                                              \
                                                                        \
    ba::split(operands, rest, boost::is_any_of(","));                   \
                                                                        \
    if(operands.size()   != 3)                                          \
    {                                                                   \
      std::cerr << "binary operators can contain only 3 operands." << std::endl; \
      return NULL;                                                      \
    }                                                                   \
                                                                        \
    ba::trim(operands[0]);                                              \
    ba::trim(operands[1]);                                              \
    ba::trim(operands[2]);                                              \
                                                                        \
    Operand*     dest    = parseOperand(operands[0]);                   \
    Operand*     source0 = parseOperand(operands[1]);                   \
    Operand*     source1 = parseOperand(operands[2]);                   \
                                                                        \
    Instruction* instr   = new klass(dest, source0, source1);           \
                                                                        \
    if(function == NULL)                                                \
    {                                                                   \
      file->appendInstruction(instr);                                   \
    }                                                                   \
    else                                                                \
    {                                                                   \
      function->appendInstruction(instr);                               \
    }                                                                   \
  }

#define TERTIARY_OPERATOR(text, skip, klass)                            \
  else if(ba::starts_with(line, #text))                                 \
  {                                                                     \
    std::string  rest     = line.substr(skip);                          \
    StringVector operands;                                              \
                                                                        \
    ba::split(operands, rest, boost::is_any_of(","));                   \
                                                                        \
    if(operands.size()   != 4)                                          \
    {                                                                   \
      std::cerr << "tertiary operators can contain only 4 operands." << std::endl; \
      return NULL;                                                      \
    }                                                                   \
                                                                        \
    ba::trim(operands[0]);                                              \
    ba::trim(operands[1]);                                              \
    ba::trim(operands[2]);                                              \
    ba::trim(operands[3]);                                              \
                                                                        \
    Operand*     dest    = parseOperand(operands[0]);                   \
    Operand*     source0 = parseOperand(operands[1]);                   \
    Operand*     source1 = parseOperand(operands[2]);                   \
    Operand*     source2 = parseOperand(operands[3]);                   \
                                                                        \
    Instruction* instr   = new klass(dest, source0, source1, source2);  \
                                                                        \
    if(function == NULL)                                                \
    {                                                                   \
      file->appendInstruction(instr);                                   \
    }                                                                   \
    else                                                                \
    {                                                                   \
      function->appendInstruction(instr);                               \
    }                                                                   \
  }

AmdIlFile* AmdIlParser::parseFile(const std::string& filename)
{
  typedef std::vector<std::string> StringVector;

  AmdIlFile*  file;
  Function*   function;
  std::string line;
  
  std::ifstream stream(filename.c_str(), std::ios::in | std::ios::binary);
  if(!stream.is_open())
  {
    std::cerr << "Unable to open AMDIL source file: " << filename << std::endl;
    return NULL;
  }

  function = NULL;
  file     = new AmdIlFile();

  bool firstInstr = true;

  
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

    if(firstInstr)
    {
      firstInstr = false;

      boost::regex  versionRegex;
      boost::smatch matches;
      
      versionRegex.assign("il_(cs|vs|ps)_([0-9]+)_([0-9]+)");

      if(boost::regex_match(line, matches, versionRegex))
      {
        std::string shaderType(matches[1].first, matches[1].second);
        std::string versionMajor(matches[2].first, matches[2].second);
        std::string versionMinor(matches[3].first, matches[3].second);

        std::cout << shaderType << " " << versionMajor << " " << versionMinor << std::endl;
      }
      else
      {
        std::cerr << "AMDIL source file must start with a shader version declaration." << std::endl;
        return NULL;
      }

      continue;
    }
    
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
    else if(ba::starts_with(line, "endmain"))
    {
      // We are at the end of the main function.
    }
    else if(ba::starts_with(line, "endfunc"))
    {
      function = NULL;
    }
    else if(ba::starts_with(line, "if_"))
    {
      // @TODO
    }
    else if(ba::starts_with(line, "else"))
    {
      // @TODO
    }
    else if(ba::starts_with(line, "endif"))
    {
      // @TODO
    }
    else if(ba::starts_with(line, "end"))
    {
      // @TODO
    }
    else if(ba::starts_with(line, "ret"))
    {
      Instruction* instr = new RetInstruction();

      if(function == NULL)
      {
        file->appendInstruction(instr);
      }
      else
      {
        function->appendInstruction(instr);
      }
    }
    else if(ba::starts_with(line, "func"))
    {
      std::string  rest = line.substr(4);
      StringVector operands;

      if(function != NULL)
      {
        std::cerr << "Cannot start a function within another function." << std::endl;
        return NULL;
      }
      
      ba::split(operands, rest, boost::is_any_of(","));

      if(operands.size() != 1)
      {
        std::cerr << "function definitions can contain only 1 operand." << std::endl;
        return NULL;
      }

      ba::trim(operands[0]);

      function = file->defineFunction(operands[0]);
    }
    else if(ba::starts_with(line, "call"))
    {
      std::string  rest = line.substr(4);
      StringVector operands;
      
      ba::split(operands, rest, boost::is_any_of(","));

      if(operands.size() != 1)
      {
        std::cerr << "call instructions can contain only 1 operand." << std::endl;
        return NULL;
      }

      ba::trim(operands[0]);

      Instruction* instr = new CallInstruction(operands[0]);

      if(function == NULL)
      {
        file->appendInstruction(instr);
      }
      else
      {
        function->appendInstruction(instr);
      }
    }
    UNARY_OPERATOR(mov, 3, MovInstruction)
      BINARY_OPERATOR(iadd, 4, IAddInstruction)
      BINARY_OPERATOR(ishl, 4, IShlInstruction)
      TERTIARY_OPERATOR(imad, 4, IMadInstruction)
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
