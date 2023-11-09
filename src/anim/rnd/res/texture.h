/* FILE NAME   : texture.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               texture's and texture's manager handle module.
 */

#ifndef __texture_h_
#define __texture_h_

#include "def.h"

#include "res_manager.h"

#include "resource.h"
#include "../render.h"

#include <iostream>
#include <wincodec.h>

/* Project namespace */
namespace mzgl
{
  /* texture representation type */
  class texture : public resource
  {
    friend class render;

  public:
    std::string Name;          // texture name
    INT W, H;
    UINT TexId;
    BOOL IsCubeMap;

    // Windows Imaging Component factory
    static IWICImagingFactory2 *WicFactory;

    /* texture default constructor */
    texture( VOID )
    {
      Name = "";
    } /* End of 'texture' function */

    std::vector<DWORD> LoadAll( std::string Name );

    texture( std::string &N )
    {
      Name = N;      
    } /* End of 'texture' function */

    /* Texture add img function.
     * ARGUMENTS:
     *   - Name:
     *       std::string Name;
     *   - Width:
     *       INT W;
     *   - Height:
     *       INT H;
     *   - Components:
     *       INT C;
     *   - Pointer to data:
     *       VOID *ptr;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & AddImg( std::string Name, INT W, INT H, INT C, VOID *ptr );

    /* Texture add fmt function.
     * ARGUMENTS:
     *   - Name:
     *       std::string Name;
     *   - Width:
     *       INT W;
     *   - Height:
     *       INT H;
     *   - Type:
     *       INT// glType;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & AddFmt( std::string Name, INT W, INT H, INT glType );

    /* Texture add cube map function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & AddCubeMap( const CHAR * FileName, std::string Name );

    /* Texture add from file function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     *   - Is cube:
     *       BOOL IsCube;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & AddFromFile( const CHAR *FileName, std::string Name, BOOL IsCube );


    /* Texture add from file function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     *   - Is cube:
     *       BOOL IsCube;
     * RETURNS:
     *   (texture &) self reference.
     */
    texture & AddFromFileAll( std::string FName, std::string Name );

        
    /* Free texture function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'texture' class */
  
  /* texture manager representation type */
  class texture_manager : public resource_manager<texture, std::string>
  {
  public:
    texture_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'font_manager' function */
    /* Texture load function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     *   - Is cube:
     *       BOOL IsC;
     * RETURNS:
     *   (texture *) pointer to texture.
     */
    texture * TxtLoad( const CHAR *FileName, std::string Name, BOOL IsC )
    {
      texture *t = resource_manager::Add(texture(Name));

      return &t->AddFromFile(FileName, Name, IsC);
    } /* End of 'TxtLoad' function */

    /* Texture load function.
     * ARGUMENTS:
     *   - File name:
     *       const CHAR *FileName;
     *   - Name:
     *       std::string Name;
     *   - Is cube:
     *       BOOL IsC;
     * RETURNS:
     *   (texture *) pointer to texture.
     */
    texture * TxtLoadAll( std::string FN, std::string Name )
    {
      texture *t = resource_manager::Add(texture(Name));

      return &t->AddFromFileAll(FN, Name);
    } /* End of 'TxtLoad' function *

    /* Texture load img function.
     * ARGUMENTS:
     *   - Name:
     *       std::string Name;
     *   - Width:
     *       INT W;
     *   - Height:
     *       INT H;
     *   - Components:
     *       INT C;
     *   - Pointer to data:
     *       VOID *ptr;
     * RETURNS:
     *   (texture *) pointer to texture.
     */
    texture * TxtLoadImg( std::string Name, INT W, INT H, INT C, VOID *ptr )
    {
      texture *t = resource_manager::Add(texture(Name));

      return &t->AddImg(Name, W, H, C, ptr);
    } /* End of 'TxtLoadImg' function */

    /* Texture load fmt function.
     * ARGUMENTS:
     *   - Name:
     *       std::string Name;
     *   - Width:
     *       INT W;
     *   - Height:
     *       INT H;
     *   - Type:
     *       INT// glType;
     * RETURNS:
     *   (texture *) pointer to texture.
     */
    texture * TxtLoadFmt( std::string Name, INT W, INT H, INT glType )
    {
      texture *t = resource_manager::Add(texture(Name));

      return &t->AddFmt(Name, W, H, glType);
    } /* End of 'TxtLoadFmt' function */

    /* Free texture function.
     * ARGUMENTS:
     *   - texture pointer:
     *       texture *Mtl;
     * RETURNS: None.
     */
    VOID TxtFree( texture *Txt )
    {
      resource_manager::Delete(Txt);
    } /* End of 'TxtFree' function */
  }; /* End of 'texture_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __texture_h_ */

/* END OF 'texture.h' FILE */