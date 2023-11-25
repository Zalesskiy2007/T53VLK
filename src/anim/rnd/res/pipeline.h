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

    VkPipelineLayout pipelineLayout;
    VkPipeline Pipeline;

    shader *s;
    
    /* pipeline default constructor */
    pipeline( VOID ) : Name {}
    {
    } /* End of 'pipeline' function */

    /* pipeline constructor by name of pipeline */
    pipeline( const std::string &ShdName ) : Name(ShdName)
    {
    } /* End of 'pipeline' function */

    /* Free pipeline function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    pipeline & Create( VOID );

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
    pipeline * PipelineCreate( const std::string &ShdName )
    {
      pipeline *s = resource_manager::Add(pipeline(ShdName));

      return &s->Create();
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