/* FILE NAME   : input.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Animation input system module.
 *               Input handle module.
 */

#ifndef __input_h_
#define __input_h_

#include "def.h"

 /* Project namespace */
namespace mzgl
{
  /* Keyboard representation type */
  class keyboard
  {
  public:
    BYTE Keys[256];
    BYTE KeysOld[256];
    BYTE KeysClick[256];

    /* Keyboard response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID KeyboardResponse( VOID )
    {
      INT i;

      GetKeyboardState(Keys);
      for (i = 0; i < 256; i++)
      {
        Keys[i] >>= 7;
        KeysClick[i] = Keys[i] && !KeysOld[i];
      }

      memcpy(KeysOld, Keys, 256);
    } /* End of 'KeyboardResponse' function */
  }; /* End of 'keyboard' class */

  /* Mouse representaion type */
  class mouse
  {
  private:
    HWND &hWnd;  // Window handle
    INT &Wheel;  // Mouse wheel parameter

  public:
    INT Mx, My, Mz, Mdx, Mdy, Mdz;
    INT MouseWheel = 0;

    /* Mouse default constructor */
    mouse( HWND &hWndRef, INT &WheelRef ) : hWnd(hWndRef), Wheel(WheelRef)
    {
    }

    /* Mouse response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID MouseResponse( VOID )
    {
      POINT pt;

      GetCursorPos(&pt);
      ScreenToClient(hWnd, &pt);

      Mdx = pt.x - Mx;
      Mdy = pt.y - My;

      Mx = pt.x;
      My = pt.y;

      Mdz = MouseWheel;
      Mz += MouseWheel;
      MouseWheel = 0;
    } /* End of 'MouseResponse' function */
  }; /* End of 'mouse' class */

  /* Joystick representation type */
  class joystick
  {
  }; /* End of 'joystick' class */

  /* Input system representation type */
  class input : public keyboard, public mouse, public joystick
  {
  public:
    /* Input system default constructor */
    input(HWND& hWndRef, INT& WheelRef) : mouse(hWndRef, WheelRef)
    {
    }
  }; /* End of 'input' class */

} /* end of 'mzgl' namespace */


#endif /* __input_h_ */

/* END OF 'input.h' FILE */