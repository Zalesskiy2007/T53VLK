/* FILE NAME   : shader.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Shaders module.
 */

#include "mzgl.h"

#include <fstream>

/* Common includes to all shaders */
extern const CHAR CommonShaderIncludes[];

/* Save text to log file function.
 * ARGUMENTS:
 *   - text 1 to save:
 *       const std::string &Stage;
 *   - text 2 to save:
 *       const std::string &Text;
 * RETURNS: None.
 */
VOID mzgl::shader::Log( const std::string &Stage, const std::string &Text )
{
  std::ofstream(Rnd->Path + "/bin/shaders/~OP{S}30.LOG", std::ios_base::app) <<
    Name << "\n" << Stage << ":\n" << Text << "\n";
} /* End of 'mzgl::shader::Log' function */

/* Text file load to memory function.
 * ARGUMENTS:
 *   - file name:
 *       const std::string &FileName;
 * RETURNS:
 *   (std::string) load text.
 */
std::vector<CHAR> mzgl::shader::LoadTextFile( const std::string &FileName )
{
  std::ifstream file(Rnd->Path + FileName, std::ios::ate | std::ios::binary);

  if (!file.is_open()) 
  {
    throw std::runtime_error("failed to open file!");
  }

  size_t fileSize = (size_t) file.tellg();
  std::vector<char> buffer(fileSize);

  file.seekg(0);
  file.read(buffer.data(), fileSize);

  file.close();

  return buffer;
} /* End of 'mzgl::shader::LoadTextFile' function */

VkShaderModule mzgl::shader::createShaderModule( const std::vector<char> &code ) 
{
  VkShaderModuleCreateInfo createInfo{};

  createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  createInfo.codeSize = code.size();
  createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());

  VkShaderModule shaderModule;

  if (vkCreateShaderModule(Rnd->LogicalDevice, &createInfo, nullptr, &shaderModule) != VK_SUCCESS)
  {
    throw std::runtime_error("failed to create shader module!");
  }

  return shaderModule;
}

/* Load shader function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (mzgl::shader &) self reference.
 */
mzgl::shader & mzgl::shader::Load( VOID )
{
  auto vertShaderCode = LoadTextFile("/bin/shaders/" + Name + "/vert.spv");
  auto fragShaderCode = LoadTextFile("/bin/shaders/" + Name + "/frag.spv");

  vertShaderModule = createShaderModule(vertShaderCode);
  fragShaderModule = createShaderModule(fragShaderCode);

  vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
  vertShaderStageInfo.module = vertShaderModule;
  vertShaderStageInfo.pName = "main";

  fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
  fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
  fragShaderStageInfo.module = fragShaderModule;
  fragShaderStageInfo.pName = "main";

  shaderStages[0] = vertShaderStageInfo;
  shaderStages[1] = fragShaderStageInfo;

  return *this;
} /* End of 'mzgl::shader::Load' function */

/* Free shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::shader::Free( VOID )
{
  vkDestroyShaderModule(Rnd->LogicalDevice, fragShaderModule, nullptr);
  vkDestroyShaderModule(Rnd->LogicalDevice, vertShaderModule, nullptr);
} /* End of 'mzgl::shader::Free' function */

/* Update shader function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::shader::Update( VOID )
{
  if (Rnd->GlobalTime - ReloadTime > 3)
  { 
    ReloadTime = Rnd->GlobalTime;
    Free();
    Load();
  }
} /* End of 'mzgl::shader::Update' function */

static const CHAR CommonShaderIncludes[] =
R"separator(
 
)separator";

/* END OF 'shader.cpp' FILE */
