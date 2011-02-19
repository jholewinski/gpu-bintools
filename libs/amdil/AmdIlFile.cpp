
#include "gpubintools/Common.hpp"
#include "gpubintools/amdil/AmdIlFile.hpp"


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

}
}
