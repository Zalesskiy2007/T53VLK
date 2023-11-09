/* FILE NAME   : primitives.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Primitives and primitives' manager handle module.
 */

#ifndef __primitives_h_
#define __primitives_h_

#include "def.h"

#include "material.h"
#include "topology.h"
#include "res_manager.h"

#include "resource.h"
#include "../render.h"

#include <iostream>

/* Project namespace */
namespace mzgl
{
  /* Primitives representation type */
  class prim : public resource
  {
    friend class render;
    
  private:
    prim_type Type {};  // Primitive type
    UINT VA;            // Primitive vertex array
    UINT VBuf;          // Vertex buffer
    UINT IBuf;          // Index buffer
    INT NumOfElements;  // Number of elements for OpenGL
    matr Transform {};  // Primitive transformation matrix
  public:
    material *Mtl {};   // Pointer to material
    vec3
      Min {0},          // Minimal primitive position
      Max {0};          // Maximal primitive position

    /* Primitives default constructor */
    prim( VOID ) : IBuf(0)
    {
    } /* End of 'prim' function */


    /* Primitive creation function.
     * ARGUMENTS:
     *   - pointer to material for primitive:
     *       material *Mat;
     *   - topology base reference:
     *       const topology::base &T;
     * RETURNS:
     *   (prim &) self reference.
     */
    template<class vertex>
      prim & Create( material *Mat, const topology::base<vertex> &T )
      {
        if (!T.V.empty())
        {
         // glGenBuffers(1, &VBuf);
         // glGenVertexArrays(1, &VA);
          /* Vertex data */
         // glBindVertexArray(VA);
          /* Active buffer */
         // glBindBuffer(GL_ARRAY_BUFFER, VBuf);
          /* Merge data */
         // glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * T.V.size(), T.V.data(),// gl_STATIC_DRAW);
          
         // glVertexAttribPointer(0, 3,// gl_FLOAT, FALSE, sizeof(vertex),
                                //(VOID *)0); /* position */
         // glVertexAttribPointer(1, 2,// gl_FLOAT, FALSE, sizeof(vertex),
                               // (VOID *)sizeof(vec3)); /* texture coordinates */
         // glVertexAttribPointer(2, 3,// gl_FLOAT, FALSE, sizeof(vertex),
                               // (VOID *)(sizeof(vec3) + sizeof(vec2))); /* normal */
         // glVertexAttribPointer(3, 4,// gl_FLOAT, FALSE, sizeof(vertex),
                               // (VOID *)(sizeof(vec3) * 2 + sizeof(vec2))); /* color */
         // glVertexAttribPointer(4, 4,// gl_FLOAT, FALSE, sizeof(vertex),
                              //  (VOID *)(sizeof(vec3) * 2 + sizeof(vec2) + sizeof(vec4))); /* gm */
         // glVertexAttribPointer(5, 4,// gl_FLOAT, FALSE, sizeof(vertex),
                              //  (VOID *)(sizeof(vec3) * 2 + sizeof(vec2) + 2 * sizeof(vec4))); /* gw */
           
          /* Include the necessary attributes (layout) */
         // glEnableVertexAttribArray(0);
         // glEnableVertexAttribArray(1);
         // glEnableVertexAttribArray(2);
         // glEnableVertexAttribArray(3);
         // glEnableVertexAttribArray(4);
         // glEnableVertexAttribArray(5);
          /* Close vertax array */ 
         // glBindVertexArray(0);
          }
          if (!T.I.empty())
          {
            /* Index data */
           // glGenBuffers(1, &IBuf);
           // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBuf);
           // glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INT) * T.I.size(), T.I.data(),// gl_STATIC_DRAW);
           // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
            NumOfElements = (INT)T.I.size();
          }
          else
            NumOfElements = (INT)T.V.size();
        
        Type = T.Type;
        Mtl = Mat;
        Transform = matr().Identity();

        return *this;
      } /* End of 'Create' function */
    
    /* Free primitive function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
      if (VA != 0)
      {
        /* Active vertex array */
       // glBindVertexArray(VA);
        /* Unhook buffer */
       // glBindBuffer(GL_ARRAY_BUFFER, 0);
       // glDeleteBuffers(1, &VBuf);
       // glBindVertexArray(0);
       // glDeleteVertexArrays(1, &VA);
      }
      //if (IBuf != 0)
       // glDeleteBuffers(1, &IBuf);
    } /* End of 'Free' function */

  }; /* End of 'prim' class */
  
  /* Primitives manager representation type */
  class primitive_manager : public resource_manager<prim>
  {
  public:
    primitive_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'font_manager' function */

    /* Create primitive function.
     * ARGUMENTS:
     *   - topology base reference:
     *       const topology::base &Tpl;
     *   - material name for primitive:
     *       material *Mat;
     * RETURNS:
     *   (prim *) created primitive interface.
     */
    template<class vertex_type>
      prim * PrimCreate( material *Mat, const topology::base<vertex_type> &Tpl )
      {
        prim *p = resource_manager::Add(prim());

        return &p->Create(Mat, Tpl);
      } /* End of 'PrimCreate' function */
 
    /* Free primitive function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     * RETURNS: None.
     */
    VOID PrimFree( prim *Pr )
    {
      resource_manager::Delete(Pr);
    } /* End of 'PrimFree' function */
  }; /* End of 'primitive_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __primitives_h_ */

/* END OF 'primitives.h' FILE */
