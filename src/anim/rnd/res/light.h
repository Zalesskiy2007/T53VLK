/* FILE NAME   : light.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               light's and light's manager handle module.
 */

#ifndef __light_h_
#define __light_h_

#include "def.h"

#include "res_manager.h"
#include "texture.h"

#include "resource.h"
#include "../render.h"

#include <iostream>

#define SHADOW_MAP_SIZE 5000

/* Project namespace */
namespace mzgl
{
  /* light representation type */
  class light : public resource
  {
    friend class render;
  public:
    std::string Name;          // light name 
    UINT ShadowFBO;
    texture* ShadowTex;
    matr ShadowMatr;
    vec3 LightDir;
    vec3 LightColor;

    /* light default constructor */
    light( VOID )
    {
      Name = "";
    } /* End of 'light' function */

    /* light default constructor */
    light( std::string &N )
    {
      Name = N ;
    } /* End of 'light' function */

    /* Light init function.
     * ARGUMENTS:
     *   - Name:
     *       std::string Name;
     * RETURNS:
     *   (light &) self reference.
     */
    light & LightInit( std::string Name );

    /* Light shadow function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID LightShadow( VOID );
        
    /* Free light function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'light' class */
  
  /* light manager representation type */
  class light_manager : public resource_manager<light, std::string>
  {
  public:
    light_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'light_manager' function */

    /* Light create function.
     * ARGUMENTS:
     *   - Name:
     *       std::string Name;
     * RETURNS:
     *   (light *) pointer to light.
     */
    light * LghCreate( std::string Name )
    {
      light *l = resource_manager::Add(light(Name));

      return &l->LightInit(Name);
    } /* End of 'LghCreate' function */

    /* Free light function.
     * ARGUMENTS:
     *   - light pointer:
     *       light *Mtl;
     * RETURNS: None.
     */
    VOID LghFree( light *Lgh )
    {
      resource_manager::Delete(Lgh);
    } /* End of 'LghFree' function */
  }; /* End of 'light_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __light_h_ */

/* END OF 'light.h' FILE */