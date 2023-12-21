/* FILE NAME   : shader.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               VB and vb's manager handle module.
 */

#ifndef __vertex_buffer_h_
#define __vertex_buffer_h_

#include "def.h"

#include <fstream>

#include "res_manager.h"

#include "resource.h"
#include "../render.h"

#include "shader.h"

/* Project namespace */
namespace mzgl
{
  /* vertex_buffer representation type */
  class vertex_buffer : public resource
  {
    friend class render;

  public:
    /* pipeline name */
    std::string Name;

    VkBufferCreateInfo bufferInfo {};

    VkBuffer vertexBuffer;
    VkDeviceMemory vertexBufferMemory;

    VkBuffer indexBuffer;
    VkDeviceMemory indexBufferMemory;

    VkMemoryAllocateInfo allocInfo{};
    VkMemoryRequirements memRequirements;
    uint32_t SizeV, SizeI;
    
    /* pipeline default constructor */
    vertex_buffer( VOID ) : Name {}
    {
    } /* End of 'vertex_buffer' function */

    /* vertex_buffer constructor by name of vertex_buffer */
    vertex_buffer( const std::string &ShdName ) : Name(ShdName)
    {
    } /* End of 'vertex_buffer' function */

    /* Free vertex_buffer function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    vertex_buffer & Create( std::vector<mzgl::vertex::std> &V, std::vector<uint32_t> &I );

    VOID CreateVertexBuffer( std::vector<mzgl::vertex::std> &V );
    VOID CreateIndexBuffer( std::vector<uint32_t> &I );

  }; /* End of 'vertex_buffer' class */
  
  /* vertex_buffer manager representation type */
  class vertex_buffer_manager : public resource_manager<vertex_buffer, std::string>
  {
  public:
    vertex_buffer_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'font_manager' function */

    /* Create vertex_buffer function.
     * ARGUMENTS:
     *   - name of pipeline:
     *       const std::string &ShdName;
     * RETURNS:
     *   (pipeline *) created shader interface(pointer).
     */
    vertex_buffer * VertexBufferCreate( const std::string &ShdName, std::vector<mzgl::vertex::std> &V, std::vector<uint32_t> &I)
    {
      vertex_buffer *s = resource_manager::Add(vertex_buffer(ShdName));

      return &s->Create(V, I);
    } /* End of 'ShaderCreate' function */

    /* Free pipeline function.
     * ARGUMENTS:
     *   - shader pointer:
     *       shader *Shd;
     * RETURNS: None.
     */
    VOID VertexBufferFree( vertex_buffer *Shd )
    {
      resource_manager::Delete(Shd);
    } /* End of 'PipelineFree' function */
  }; /* End of 'pipeline_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __shader_h_ */

/* END OF 'shader.h' FILE */