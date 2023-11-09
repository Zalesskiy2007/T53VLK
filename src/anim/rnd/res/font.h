/* FILE NAME   : font.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               font's and font's manager handle module.
 */

#ifndef __font_h_
#define __font_h_

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
  /* font_info type*/
  struct font_info
  {
    DWORD LineH, BaseH;
    FLT AdvanceX[256];
  }; /* End of 'font_info' type */
  /* font representation type */
  class font : public resource
  {
    friend class render;
  public:
    std::string Name;          // font name
    font_info inf;
    prim* FntChars[256];
    material *Mtl;

    /* font default constructor */
    font( VOID )
    {
      Name = "";
    } /* End of 'font' function */

    font( std::string &N )
    {
      Name = N;
    } /* End of 'font' function */

    /* Font load function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     * RETURNS:
     *   (font &) self reference.
     */
    mzgl::font & FntLoad( const CHAR *FileName, std::string Name );

    /* Font draw function.
     * ARGUMENTS:
     *   - String to draw:
     *       CHAR *Str;
     * RETURNS: None.
     */
    VOID FntDraw( CHAR *Str );

        
    /* Free font function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'font' class */
  
  /* font manager representation type */
  class font_manager : public resource_manager<font, std::string>
  {
  public:
    font_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'font_manager' function */

    /* Font create function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     * RETURNS:
     *   (font *) pointer to font.
     */
    font * FntCreate( const CHAR *FileName, std::string Name )
    {
      font *fnt = resource_manager::Add(font(Name));
      return &fnt->FntLoad(FileName, Name); 
    } /* End of 'FntCreate' function */

    /* Free font function.
     * ARGUMENTS:
     *   - font pointer:
     *       font *Mtl;
     * RETURNS: None.
     */
    VOID FntFree( font *Fnt )
    {
      resource_manager::Delete(Fnt);
    } /* End of 'FntFree' function */
  }; /* End of 'font_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __font_h_ */

/* END OF 'font.h' FILE */