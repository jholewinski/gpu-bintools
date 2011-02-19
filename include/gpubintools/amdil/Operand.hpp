
#if !defined(GPU_BIN_TOOLS_AMDIL_OPERAND_HPP_INC)
#define GPU_BIN_TOOLS_AMDIL_OPERAND_HPP_INC 1

namespace gpubintools
{
namespace amdil
{

/**
 * Base class for all AMDIL instructions.
 */
class Operand
{
public:

  /**
   * Constructor.
   */
  Operand();

  /**
   * Destructor.
   */
  virtual ~Operand();
  
};

}
}

#endif
