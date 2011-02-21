
#include "gpubintools/Common.hpp"
#include "gpubintools/amdil/AmdIlFile.hpp"
#include "gpubintools/amdil/Function.hpp"


namespace gpubintools
{
namespace amdil
{

AmdIlFile::AmdIlFile()
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

}
}
