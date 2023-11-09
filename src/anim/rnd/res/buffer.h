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

/* Project namespace */
namespace mzgl
{
  /* font representation type */
  class buffer: public resource
  {
    friend class render;
  public:
    std::string Name {};

    INT Size {};
    UINT Id {};
    UINT BindPoint {};

    buffer( std::string &N )
    {
      Name = N;
    } /* End of 'font' function */

    buffer( VOID )
    {
      Name = "";
    } /* End of 'font' function */

    
    buffer & Create( UINT BindP, INT BufferSize, VOID *BufferBits )
    {
     // glGenBuffers(1, &Id);
     // glBindBuffer(GL_SHADER_STORAGE_BUFFER, Id);
     // glBufferData(GL_SHADER_STORAGE_BUFFER, BufferSize, nullptr,// gl_DYNAMIC_COPY);

      if (BufferBits != nullptr)
       // glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, BufferSize, BufferBits);
     // glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);

      Size = BufferSize;
      this->BindPoint = BindP;

      return *this;
    }

    VOID Update( INT BlockOffset, INT BufferSize, VOID *BufferBits )
    {
      if (BlockOffset < 0)
        BlockOffset = 0;

      if (BlockOffset == 0 && BufferSize == 0)
        BufferSize = Size;

      if (BlockOffset + BufferSize >= Size)
        BufferSize = Size - BlockOffset;

     // glBindBuffer(GL_SHADER_STORAGE_BUFFER, Id);
     // glBufferSubData(GL_SHADER_STORAGE_BUFFER, BlockOffset, BufferSize, BufferBits);
     // glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
    }

    VOID Apply( VOID )
    {
     // glBindBufferBase(GL_SHADER_STORAGE_BUFFER, BindPoint, Id);
    }
        
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


    buffer * BufferCreate( std::string Name, UINT BindP, INT BufferSize, VOID *Bits )
    {
      buffer * buf = resource_manager::Add(buffer(Name));

      return &buf->Create(BindP, BufferSize, Bits);
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