

#if !defined(GPU_BIN_TOOLS_AMDIL_AMDIL_PARSER_HPP_INC)
#define GPU_BIN_TOOLS_AMDIL_AMDIL_PARSER_HPP_INC 1

namespace gpubintools
{
namespace amdil
{

class AmdIlFile;
class Operand;

/**
 * Parser for AMDIL source files.
 */
class AmdIlParser
{
public:

  /**
   * Constructor.
   */
  AmdIlParser();

  /**
   * Destructor.
   */
  ~AmdIlParser();

  /**
   * Parses an AMDIL source file.
   *
   * @param[in] filename  The filename to parse.
   *
   * @return The created AmdIlFile instance.
   */
  AmdIlFile* parseFile(const std::string& filename);


private:

  Operand* parseOperand(const std::string& text);
  
};

}
}

#endif
