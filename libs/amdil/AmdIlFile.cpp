
#include "gpubintools/Common.hpp"
#include "gpubintools/amdil/AmdIlFile.hpp"
#include "gpubintools/amdil/Function.hpp"


namespace gpubintools
{
namespace amdil
{

AmdIlFile::AmdIlFile()
  : type_(kShaderTypeCompute),
    versionMajor_(2),
    versionMinor_(0)
{
}

AmdIlFile::~AmdIlFile()
{
}

void AmdIlFile::appendInstruction(Instruction* instr)
{
  instructions_.push_back(instr);
}

Function* AmdIlFile::defineFunction(const std::string& name)
{
  Function* func = new Function(name);

  functions_[name] = func;

  return func;
}

void AmdIlFile::prettyPrint(std::ostream& stream)
{
  stream << "il_";

  switch(type_)
  {
    case kShaderTypeCompute:
    {
      stream << "cs_";
      break;
    }
    case kShaderTypePixel:
    {
      stream << "ps_";
      break;
    }
    case kShaderTypeVertex:
    {
      stream << "vs_";
      break;
    }
  }

  stream << versionMajor_ << "_" << versionMinor_ << std::endl;

  BOOST_FOREACH(Instruction* instr, instructions_)
  {
  }
}

void AmdIlFile::setVersion(ShaderType type,
                           size_t     versionMajor,
                           size_t     versionMinor)
{
  type_         = type;
  versionMajor_ = versionMajor;
  versionMinor_ = versionMinor;
}

}
}
