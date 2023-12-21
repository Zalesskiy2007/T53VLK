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

    VkImage textureImage;
    VkDeviceMemory textureImageMemory;

    VkImageView textureImageView;
    VkSampler textureSampler;

    // Windows Imaging Component factory
    static IWICImagingFactory2 *WicFactory;

    VOID CreateTextureImageView( VOID );
    
    VOID CreateTextureSampler( VOID );

    /* texture default constructor */
    texture( VOID )
    {
      Name = "";
    } /* End of 'texture' function */

    std::vector<DWORD> LoadAll( std::string Name, INT *tW, INT *tH);

    texture( std::string &N )
    {
      Name = N;      
    } /* End of 'texture' function */

    VOID CreateTextureImage( VOID );
    VOID CreateImage( uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory );

    texture & Create( VOID );
        
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

    texture * TxtLoad( std::string N )
    {
      texture *s = resource_manager::Add(texture(N));

      return &s->Create();
    }

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