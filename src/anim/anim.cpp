/* FILE NAME   : anim.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Animation system module.
 *               Animation module file.
 */

#include "mzgl.h"

std::map<std::string, mzgl::unit * (*)(mzgl::anim *)> mzgl::anim::UnitsNames;

/* Animation render function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::anim::Render(VOID)
{
  /* */
  timer::Response();

  Units.Walk([this](unit* Uni)
    {
      Uni->Response(this);
    });
  /* ... */
  render::FrameStart();
  Units.Walk([this]( unit *Uni )
    {
      Uni->Render(this);
    });

  Units.Walk([this]( unit *Uni )
    {
      Uni->ToDraw(this);
    });

  render::FrameEnd();
} /* End of 'mzgl::anim::Render' function */

/* Window message loop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::anim::Run(VOID)
{
  MSG msg;

  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        /* Displatch message to window */
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
      if (IsInit)
        Render();
    }
  }
} /* End of 'mzgl::anim::Run' function */

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL mzgl::anim::OnCreate(CREATESTRUCT* CS)
{
  SetTimer(win::hWnd, 30, 2, nullptr);
  render::Init();

  return TRUE;
} /* End of 'mzgl::anim::OnCreate' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID mzgl::anim::OnSize(UINT State, INT W, INT H)
{
  render::Resize(W, H);
} /* End of 'mzgl::anim::OnSize' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::anim::OnDestroy(VOID)
{
  render::Close();
} /* End of 'mzgl::anim::OnDestroy' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID mzgl::anim::OnTimer(INT Id)
{
  if (IsInit)
    Render();
} /* End of 'mzgl::anim::OnTimer' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL mzgl::anim::OnEraseBkgnd(HDC hDC)
{
  return TRUE;
} /* End of 'mzgl::anim::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID mzgl::anim::OnPaint(HDC hDC, PAINTSTRUCT* PS)
{
  if (IsInit)
    Render();
} /* End of 'mzgl::anim::OnPaint' function */

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID mzgl::anim::OnMouseWheel(INT X, INT Y, INT Z, UINT Keys)
{
  mzgl::mouse::MouseWheel += Z;
} /* End of 'win::OnMouseWheel' function */

/* Button down of mouse window message handle function.
 * ARGUMENTS:
 *   - flag for double click on mouse:
 *       BOOL IsDoubleClick;
 *   - coordinates of mouse:
 *       INT X, INT Y;
 *   - pressed keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID mzgl::anim::OnButtonDown(BOOL IsDoubleClick, INT X, INT Y, UINT Keys)
{
} /* End of 'mzgl::anim::OnButtonDown' function */

/* Button up of mouse window message handle function.
 * ARGUMENTS:
 *   - coordinates of mouse:
 *       INT X, INT Y;
 *   - pressed keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID mzgl::anim::OnButtonUp(INT X, INT Y, UINT Keys)
{
} /* End of 'mzgl::anim::OnButtonUp' function */

/* Move mouse window message handle function.
 * ARGUMENTS:
 *   - coordinates of mouse:
 *       INT X, INT Y;
 *   - pressed keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID mzgl::anim::OnMouseMove(INT X, INT Y, UINT Keys)
{
} /* End of 'mzgl::anim::OnMouseMove' function */

/* WM_EXITSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::anim::OnExitSizeMove(VOID)
{
} /* End of 'mzgl::anim::OnExitSizeMove' function */

/* WM_ENTERSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::anim::OnEnterSizeMove(VOID)
{
} /* End of 'mzgl::anim::OnEnterSizeMove' function */

/* Window message universal handle function.
 * Should be returned 'DefWindowProc' call result.
 * ARGUMENTS:
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT mzgl::anim::OnMessage(UINT Msg, WPARAM wParam, LPARAM lParam)
{
  switch (Msg)
  {
  case WM_KEYDOWN:
    if (wParam == VK_ESCAPE)
      DestroyWindow(win::hWnd);
    return 0;
  }

  return DefWindowProc(win::hWnd, Msg, wParam, lParam);
} /* End of 'win::OnMessage' function */


/* END OF 'anim.cpp' FILE */