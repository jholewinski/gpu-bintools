
#include "gpubintools/Common.hpp"
#include "gpubintools/amdil/Function.hpp"


namespace gpubintools
{
namespace amdil
{

Function::Function(const std::string& name)
  : name_(name)
{
}

Function::~Function()
{
}

void Function::appendInstruction(Instruction* instr)
{
  instructions_.push_back(instr);
}

}
}
