#if !defined(GPU_BIN_TOOLS_AMDIL_INSTRUCTIONS_HPP_INC)
#define GPU_BIN_TOOLS_AMDIL_INSTRUCTIONS_HPP_INC 1

namespace gpubintools
{
namespace amdil
{

class Operand;

/**
 * Base class for all AMDIL AST instructions.
 */
class Instruction
{
public:

  /**
   * Constructor.
   */
  Instruction();

  /**
   * Destructor.
   */
   virtual ~Instruction();
};

/**
 * An AMDIL unary operator instruction.
 */
class UnaryOperator : public Instruction
{
public:

  /**
   * Constructor.
   *
   * @param[in] dest    The destination operand.
   * @param[in] source  The source operand.
   */
  UnaryOperator(Operand* dest,
                 Operand* source);

  /**
   * Destructor.
   */
  virtual ~UnaryOperator();


private:

  Operand* dest_;
  Operand* source_;
  
};


/**
 * An AMDIL mov instruction.
 */
class MovInstruction : public UnaryOperator
{
public:

  /**
   * Constructor.
   *
   * @param[in] dest    The destination operand.
   * @param[in] source  The source operand.
   */
  MovInstruction(Operand* dest,
                 Operand* source);

  /**
   * Destructor.
   */
  virtual ~MovInstruction();

};


/**
 * An AMDIL binary operator instruction.
 */
class BinaryOperator : public Instruction
{
public:

  /**
   * Constructor.
   *
   * @param[in] dest        The destination operand.
   * @param[in] leftSource  The left source operand.
   * @param[in] rightSource The right source operand.
   */
  BinaryOperator(Operand* dest,
                 Operand* leftSource,
                 Operand* rightSource);

  /**
   * Destructor.
   */
  virtual ~BinaryOperator();


private:

  Operand* dest_;
  Operand* leftSource_;
  Operand* rightSource_;
  
};


/**
 * An AMDIL iadd instruction.
 */
class IAddInstruction : public BinaryOperator
{
public:

  /**
   * Constructor.
   *
   * @param[in] dest        The destination operand.
   * @param[in] leftSource  The left source operand.
   * @param[in] rightSource The right source operand.
   */
  IAddInstruction(Operand* dest,
                  Operand* leftSource,
                  Operand* rightSource);

  /**
   * Destructor.
   */
  virtual ~IAddInstruction();
  
};

/**
 * An AMDIL ishl instruction.
 */
class IShlInstruction : public BinaryOperator
{
public:

  /**
   * Constructor.
   *
   * @param[in] dest        The destination operand.
   * @param[in] leftSource  The left source operand.
   * @param[in] rightSource The right source operand.
   */
  IShlInstruction(Operand* dest,
                  Operand* leftSource,
                  Operand* rightSource);

  /**
   * Destructor.
   */
  virtual ~IShlInstruction();
  
};


/**
 * An AMDIL tertiary operator instruction.
 */
class TertiaryOperator : public Instruction
{
public:

  /**
   * Constructor.
   *
   * @param[in] dest          The destination operand.
   * @param[in] leftSource    The left source operand.
   * @param[in] middleSource  The middle source operand.
   * @param[in] rightSource   The right source operand.
   */
  TertiaryOperator(Operand* dest,
                   Operand* leftSource,
                   Operand* middleSource,
                   Operand* rightSource);

  /**
   * Destructor.
   */
  virtual ~TertiaryOperator();


private:

  Operand* dest_;
  Operand* leftSource_;
  Operand* middleSource_;
  Operand* rightSource_;
  
};


/**
 * An AMDIL imad operator instruction.
 */
class IMadInstruction : public TertiaryOperator
{
public:

  /**
   * Constructor.
   *
   * @param[in] dest          The destination operand.
   * @param[in] leftSource    The left source operand.
   * @param[in] middleSource  The middle source operand.
   * @param[in] rightSource   The right source operand.
   */
  IMadInstruction(Operand* dest,
                  Operand* leftSource,
                  Operand* middleSource,
                  Operand* rightSource);

  /**
   * Destructor.
   */
  virtual ~IMadInstruction();

};


/**
 * An AMDIL terminator instruction.
 */
class TerminatorInstruction : public Instruction
{
public:

  /**
   * Constructor.
   */
  TerminatorInstruction();

  /**
   * Destructor.
   */
  virtual ~TerminatorInstruction();
  
};

/**
 * An AMDIL ret instruction.
 */
class RetInstruction : public TerminatorInstruction
{
public:

  /**
   * Constructor.
   */
  RetInstruction();

  /**
   * Destructor.
   */
  virtual ~RetInstruction();
  
};


/**
 * An AMDIL call instruction.
 */
class CallInstruction : public Instruction
{
public:

  /**
   * Constructor.
   *
   * @param[in] target  The target name.
   */
  CallInstruction(const std::string& target);

  /**
   * Destructor.
   */
  virtual ~CallInstruction();


private:

  std::string target_;
  
};


}
}

#endif
