/* FILE NAME   : font.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               font's and font's manager handle module.
 */

#ifndef __buffer_h_
#define __buffer_h_

#include "def.h"

#include "res_manager.h"
#include "material.h"
#include "primitives.h"
#include "resource.h"
#include "../render.h"

#include <iostream>
#include <vector>

/* Project namespace */
namespace mzgl
{
  /* font representation type */
  class buffer: public resource
  {
    friend class render;
  public:
    std::string Name {};

    std::vector<VkBuffer> uniformBuffers;
    std::vector<VkDeviceMemory> uniformBuffersMemory;
    std::vector<VOID *> uniformBuffersMapped;

    uint32_t Size;

    buffer( std::string &N )
    {
      Name = N;
    } /* End of 'font' function */

    buffer( VOID )
    {
      Name = "";
    } /* End of 'font' function */

    
    buffer & Create( uint32_t bufferSize );
        
    /* Free font function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'font' class */
  
  /* font manager representation type */
  class buffer_manager : public resource_manager<buffer, std::string>
  {
  public:
    buffer_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'font_manager' function */


    buffer * BufferCreate( std::string Name, uint32_t bufferSize )
    {
      buffer * buf = resource_manager::Add(buffer(Name));

      return &buf->Create(bufferSize);
    }    

    /* Free font function.
     * ARGUMENTS:
     *   - font pointer:
     *       font *Mtl;
     * RETURNS: None.
     */
    VOID BufferFree( buffer *Fnt )
    {
      resource_manager::Delete(Fnt);
    } /* End of 'FntFree' function */
  }; /* End of 'font_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __font_h_ */

/* END OF 'font.h' FILE */