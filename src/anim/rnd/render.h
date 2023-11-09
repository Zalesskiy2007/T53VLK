/* FILE NAME   : render.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 31.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Render system module.
 *               Render handle module.
 */

#ifndef __render_h_
#define __render_h_

#include "def.h"

#include "anim/rnd/res/shader.h"
#include "anim/rnd/res/mtl_pattern.h"
#include "anim/rnd/res/material.h"
#include "anim/rnd/res/primitives.h"
#include "anim/rnd/res/font.h"
#include "anim/rnd/res/target.h"
#include "anim/rnd/res/light.h"
#include "anim/rnd/res/model.h"
#include "anim/rnd/res/buffer.h"

#include "anim/input/timer.h"
#include <string>

#include "anim/anim.h"

 /* Project namespace */
namespace mzgl
{
   /* Primitive data representation type */
  struct prim_data
  {
    matr MatrWVP;
    matr MatrW;
    matr MatrWInvTrans;
  }; /* End of 'prim_data' class */

  /* Render representation type */
  class render : public timer, 
    public shader_manager, public material_pattern_manager,
    public material_manager, public primitive_manager, public texture_manager, public font_manager,
    public target_manager, public light_manager, public model_manager, public buffer_manager
  {
  public:
    HWND& hWnd;     // Render reference to window handle
    HDC hDC;        // Render window device context
    HGLRC hGLRC;    // Render OpenGL context handle
  public:
    camera Camera;   // Camera type
    prim_data Prim_data;  // Primitive data 
    target *Trg;
    light *Lgh;

    std::vector<prim *> PrimsToDraw;
    std::vector<matr> MatrsToDraw;
    BOOL IsShading = FALSE;

    /* Path to shader directory */
    std::string Path;

    /* Render default constructor */
    render(HWND& hNewWnd) : hWnd(hNewWnd), timer(),
      shader_manager(*this), material_pattern_manager(*this),
      material_manager(*this), primitive_manager(*this), texture_manager(*this), font_manager(*this),
      target_manager(*this), light_manager(*this), model_manager(*this), buffer_manager(*this)
    {      
    }
    /* Render default destructor */
    ~render(VOID)
    {
    }

    BOOL IsInit;  // Flag for initialization render

    /* Render system initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init(VOID);

    /* Render system close (deinitialization) function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close(VOID);

    /* Render system resize function.
     * ARGUMENTS:
     *   - window new size:
     *       INT W, INT H;
     * RETURNS: None.
     */
    VOID Resize(INT NewW, INT NewH);

    /* Start render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameStart(VOID);

    /* Finish render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameEnd(VOID);

    /* Primitive draw function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     *   - transformation matrix:
     *       const matr &World;
     * RETURNS: None.
     */
    VOID Draw(const prim* Pr, const matr& World = matr().Identity());

    /* Primitive load function.
     * ARGUMENTS:
     *   - Filename:
     *       const CHAR *Fn;
     *   - Material:
     *       material *Mat;
     * RETURNS:
     *   (prim *) created primitive;
     */
    mzgl::topology::base<mzgl::vertex::std> LoadModel( const CHAR *Fn );

  }; /* End of 'render' class */

} /* end of 'mzgl' namespace */

#endif /* __render_h_ */

/* END OF 'render.h' FILE */