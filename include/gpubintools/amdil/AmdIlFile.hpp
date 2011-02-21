
#if !defined(GPU_BIN_TOOLS_AMDIL_AMDIL_SOURCE_FILE_HPP_INC)
#define GPU_BIN_TOOLS_AMDIL_AMDIL_SOURCE_FILE_HPP_INC 1

namespace gpubintools
{
namespace amdil
{

class Function;
class Instruction;

enum ShaderType
{
  kShaderTypeCompute,
  kShaderTypePixel,
  kShaderTypeVertex,
};

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

  /**
   * Prints a text representation of the AST to a stream.
   *
   * @param[in] stream  The text stream.
   */
  void prettyPrint(std::ostream& stream);

  /**
   * Sets the version number of the AMDIL program.
   *
   * @param[in] type          The shader type.
   * @param[in] versionMajor  The major version number.
   * @param[in] versionMinor  The minor version number.
   */
  void setVersion(ShaderType type,
                  size_t     versionMajor,
                  size_t     versionMinor);
  
private:

  typedef std::list<Instruction*>          InstructionList;
  typedef std::map<std::string, Function*> FunctionMap;
  
  InstructionList instructions_;
  FunctionMap     functions_;
  ShaderType      type_;
  size_t          versionMajor_;
  size_t          versionMinor_;
  
};

}
}

#endif
