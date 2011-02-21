#include "gpubintools/Common.hpp"
#include "gpubintools/amdil/Operand.hpp"
#include "gpubintools/amdil/Instructions.hpp"


namespace gpubintools
{
namespace amdil
{

Instruction::Instruction()
{
}

Instruction::~Instruction()
{
}

UnaryOperator::UnaryOperator(Operand* dest,
                             Operand* source)
  : dest_(dest),
    source_(source)
{
}

UnaryOperator::~UnaryOperator()
{
}


MovInstruction::MovInstruction(Operand* dest,
                               Operand* source)
  : UnaryOperator(dest, source)
{
}

MovInstruction::~MovInstruction()
{
}


BinaryOperator::BinaryOperator(Operand* dest,
                               Operand* leftSource,
                               Operand* rightSource)
  : dest_(dest),
    leftSource_(leftSource),
    rightSource_(rightSource)
{
}

BinaryOperator::~BinaryOperator()
{
}

IAddInstruction::IAddInstruction(Operand* dest,
                                 Operand* leftSource,
                                 Operand* rightSource)
  : BinaryOperator(dest, leftSource, rightSource)
{
}

IAddInstruction::~IAddInstruction()
{
}


IShlInstruction::IShlInstruction(Operand* dest,
                                 Operand* leftSource,
                                 Operand* rightSource)
  : BinaryOperator(dest, leftSource, rightSource)
{
}

IShlInstruction::~IShlInstruction()
{
}


TertiaryOperator::TertiaryOperator(Operand* dest,
                                   Operand* leftSource,
                                   Operand* middleSource,
                                   Operand* rightSource)
  : dest_(dest),
    leftSource_(leftSource),
    middleSource_(middleSource),
    rightSource_(rightSource)
{
}

TertiaryOperator::~TertiaryOperator()
{
}


IMadInstruction::IMadInstruction(Operand* dest,
                                 Operand* leftSource,
                                 Operand* middleSource,
                                 Operand* rightSource)
  : TertiaryOperator(dest, leftSource, middleSource, rightSource)
{
}

IMadInstruction::~IMadInstruction()
{
}


TerminatorInstruction::TerminatorInstruction()
{
}

TerminatorInstruction::~TerminatorInstruction()
{
}


RetInstruction::RetInstruction()
{
}

RetInstruction::~RetInstruction()
{
}



CallInstruction::CallInstruction(const std::string& target)
  : target_(target)
{
}

CallInstruction::~CallInstruction()
{
}


}
}
