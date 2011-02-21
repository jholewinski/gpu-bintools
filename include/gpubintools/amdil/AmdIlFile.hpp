
#if !defined(GPU_BIN_TOOLS_AMDIL_AMDIL_SOURCE_FILE_HPP_INC)
#define GPU_BIN_TOOLS_AMDIL_AMDIL_SOURCE_FILE_HPP_INC 1

namespace gpubintools
{
namespace amdil
{

class Function;
class Instruction;

/**
 * An AMDIL source file.
 */
class AmdIlFile
{
public:

  /**
   * Constructor.
   */
  AmdIlFile();

  /**
   * Destructor.
   */
  ~AmdIlFile();


  /**
   * Appends an instruction to the file.
   *
   * @param[in] instr   The Instruction to append.
   */
  void appendInstruction(Instruction* instr);

  /**
   * Defines a new AMDIL function.
   *
   * @param[in] name  The function name.
   *
   * @return The Function instance.
   */
  Function* defineFunction(const std::string& name);
  
private:

  typedef std::list<Instruction*>          InstructionList;
  typedef std::map<std::string, Function*> FunctionMap;
  
  InstructionList instructions_;
  FunctionMap     functions_;
  
};

}
}

#endif
