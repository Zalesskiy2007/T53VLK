/* FILE NAME   : shader.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               pipelines and pipeline's manager handle module.
 */

#ifndef __pipeline_h_
#define __pipeline_h_

#include "def.h"

#include <fstream>

#include "res_manager.h"

#include "resource.h"
#include "../render.h"

#include "shader.h"
#include "buffer.h"
#include "texture.h"

/* Project namespace */
namespace mzgl
{
  /* pipeline representation type */
  class pipeline : public resource
  {
    friend class render;

  public:
    /* pipeline name */
    std::string Name;
    std::string ShaderName;
    std::string TextureName;

    VkPipelineLayout pipelineLayout;
    VkDescriptorSetLayout descriptorSetLayout;
    VkPipeline Pipeline;

    VkDescriptorPool descriptorPool;
    std::vector<VkDescriptorSet> descriptorSets;

    shader *Shd;
    buffer *Buf; /* 
                 similar like textures(images) need to do buffers:
                  -- array(vector) of pointers to buffers(images);
                  -- do in loop descriptor writes
                  -- apply(update) all buffers
                 */

    texture *Img;
    
    /* pipeline default constructor */
    pipeline( VOID ) : Name {}, ShaderName {}, TextureName {}
    {
    } /* End of 'pipeline' function */

    /* pipeline constructor by name of pipeline */
    pipeline( const std::string &CName, const std::string &TName, const std::string &ShdName ) : Name(CName), ShaderName(ShdName), TextureName(TName)
    {
    } /* End of 'pipeline' function */

    /* Free pipeline function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    pipeline & Create( mzgl::prim_type TypeDraw );

  }; /* End of 'pipeline' class */
  
  /* pipeline manager representation type */
  class pipeline_manager : public resource_manager<pipeline, std::string>
  {
  public:
    pipeline_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'font_manager' function */

    /* Create pipeline function.
     * ARGUMENTS:
     *   - name of pipeline:
     *       const std::string &ShdName;
     * RETURNS:
     *   (pipeline *) created shader interface(pointer).
     */
    pipeline * PipelineCreate( const std::string &CName, const std::string &TName, const std::string &ShdName, mzgl::prim_type TypeDraw)
    {
      pipeline *s = resource_manager::Add(pipeline(CName, TName, ShdName));

      return &s->Create( TypeDraw );
    } /* End of 'ShaderCreate' function */

    /* Free pipeline function.
     * ARGUMENTS:
     *   - shader pointer:
     *       shader *Shd;
     * RETURNS: None.
     */
    VOID PipelineFree( pipeline *Shd )
    {
      resource_manager::Delete(Shd);
    } /* End of 'PipelineFree' function */
  }; /* End of 'pipeline_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __shader_h_ */

/* END OF 'shader.h' FILE */