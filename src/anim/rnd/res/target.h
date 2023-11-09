/* FILE NAME   : target.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               target's and target's manager handle module.
 */

#ifndef __target_h_
#define __target_h_

#include "def.h"

#include "texture.h"
#include <iostream>

#include "resource.h"
#include "../render.h"

#define RND_TARGETS 6

/* Project namespace */
namespace mzgl
{
  /* target representation type */
  class target : public resource
  {
    friend class render;
  public:
    std::string Name;          // target name
    UINT TargetId;
    texture* Tex[8];
    UINT RndBufId;
    prim *TargetScreen;

    /* target default constructor */       
    target( VOID )
    {
      Name = "";
    } /* End of 'target' function */

    /* target default constructor */       
    target( std::string &N )
    {
      Name = N;
    } /* End of 'target' function */

    /* Target create function.
     * ARGUMENTS:
     *   - Width:
     *       INT W;
     *   - Height:
     *       INT H;
     * RETURNS:
     *   (target &) self reference.
     */
    target & TargetCreate( INT W, INT H );

    /* Target init function.
     * ARGUMENTS:
     *   - Name:
     *       std::string Name;
     * RETURNS:
     *   (target &) self reference.
     */
    target & TargetInit( std::string Name );

    /* Target resize function.
     * ARGUMENTS:
     *   - Width:
     *       INT W;
     *   - Height:
     *       INT H;
     * RETURNS: None.
     */
    VOID TargetResize( INT W, INT H );

    /* Target start function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID TargetStart( VOID );

    /* Target end function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID TargetEnd( VOID );

    /* Free target function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'target' class */
  
  /* target manager representation type */
  class target_manager : public resource_manager<target, std::string>
  {
  public:
    target_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'font_manager' function */

    /* Target manager create function.
     * ARGUMENTS:
     *   - Name:
     *       std::string Name;
     * RETURNS:
     *   (target *) pointer to target.
     */
    target * TrgCreate( std::string Name )
    {
      target *t = resource_manager::Add(target(Name));

      return &t->TargetInit(Name);
    } /* End of 'TrgCreate' function */

    /* Free target function.
     * ARGUMENTS:
     *   - target pointer:
     *       target *Mtl;
     * RETURNS: None.
     */
    VOID TrgFree( target *Trg )
    {
      resource_manager::Delete(Trg);
    } /* End of 'TrgFree' function */
  }; /* End of 'target_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __target_h_ */

/* END OF 'target.h' FILE */