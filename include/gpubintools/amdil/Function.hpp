#if !defined(GPU_BIN_TOOLS_AMDIL_FUNCTION_HPP_INC)
#define GPU_BIN_TOOLS_AMDIL_FUNCTION_HPP_INC 1

namespace gpubintools
{
namespace amdil
{

class Instruction;

/**
 * An AMDIL function.
 */
class Function
{
public:

  /**
   * Constructor.
   *
   * @param[in] name  The function name.
   */
  Function(const std::string& name);

  /**
   * Destructor.
   */
  ~Function();

  /**
   * Appends an instruction to the function.
   *
   * @param[in] instr   The Instruction to append.
   */
  void appendInstruction(Instruction* instr);

private:

  typedef std::list<Instruction*> InstructionList;
  
  InstructionList instructions_;
  std::string     name_;
  
};

}
}

#endif
