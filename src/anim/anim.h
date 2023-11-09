/* FILE NAME   : anim.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Animation system module.
 *               Animation handle module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "def.h"

#include <iostream>
#include <map>

#include "stock/stock.h"

#include "rnd/render.h"
#include "input/input.h"
#include "input/timer.h"
#include "../win/win.h"

 /* Project namespace */
namespace mzgl
{
  /* Forward unit class reference */
  class anim;

  /* Unit representation type */
  class unit
  {
  public:
    /* Unit default constructor */
    unit(VOID)
    {
    } /* End of 'unit' constructor */

    /* Unit virtual destructor */
    virtual ~unit(VOID)
    {
    } /* End of 'unit' destructor */

    /* Virtual render function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Render(anim* Ani)
    {
    } /* End of 'Render' function */

    /* Virtual response function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID Response(anim* Ani)
    {
    } /* End of 'Response' function */

    /* Virtual ToDraw function.
     * ARGUMENTS:
     *   - animation context:
     *       anim *Ani;
     * RETURNS: None.
     */
    virtual VOID ToDraw(anim* Ani)
    {
    } /* End of 'ToDraw' function */
  }; /* End of 'unit' class */


  /* Animation representation type */
  class anim : public win, public input, public render
  {
  public:

    /* Single tone constructor for animation */
    anim(HINSTANCE hInst = GetModuleHandle(nullptr)) :
      win(hInst),
      input(win::hWnd, win::MouseWheel),
      render(win::hWnd)
    {
    } /* End of 'anim' constructor */

  public:
    /* Stock of units */
    stock<unit*> Units;

    /* Unit's names map */
    static std::map<std::string, unit * (*)(anim *)> UnitsNames;

  public:
    /* Add new unit by name function.
     * ARGUMENTS:
     *   - reference to unit name:
     *       std::string &UnitName;
     * RETURNS:
     *   (anim &) changed new stock.
     */
    anim& operator<<(const std::string& UnitName)
    {
      if (UnitsNames.find(UnitName) != UnitsNames.end())
      {
        unit* uni = UnitsNames[UnitName](this);

        Units << uni;
      }
      return *this;
    } /* End of 'operator<<' function */

    /* Animation base destructor - delete all units */
    ~anim(VOID)
    {
      Units.Walk([](unit* Uni)
        {
          delete Uni;
        });
    } /* End of '~anim' destructor */

    /* Unit auto registration representation type */
    template<typename unit_type>
    class unit_register
    {
    private:
      /* Create unit (static) function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (unit *) Pointer to created unit.
       */
      static unit* Create( anim *Ani )
      {
        return new unit_type(Ani);
      } /* End of 'Create' function */

    public:
      /* Unit register default constructor */
      unit_register(const std::string& UnitName)
      {
        UnitsNames[UnitName] = Create;
      } /* End of 'unit_register' constructor */
    }; /* End of 'unit_register' class */

    VOID Run(VOID) override;

  private:
    /* Animation render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render(VOID);

    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate(CREATESTRUCT* CS) override;

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize(UINT State, INT W, INT H) override;

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy(VOID) override;

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer(INT Id) override;

    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBkgnd(HDC hDC) override;

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    VOID OnPaint(HDC hDC, PAINTSTRUCT* Ps) override;

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
    VOID OnButtonDown(BOOL IsDoubleClick, INT X, INT Y, UINT Keys) override;

    /* Button up of mouse window message handle function.
     * ARGUMENTS:
     *   - coordinates of mouse:
     *       INT X, INT Y;
     *   - pressed keys:
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonUp(INT X, INT Y, UINT Keys) override;

    /* Move mouse window message handle function.
     * ARGUMENTS:
     *   - coordinates of mouse:
     *       INT X, INT Y;
     *   - pressed keys:
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnMouseMove(INT X, INT Y, UINT Keys) override;

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
    VOID OnMouseWheel(INT X, INT Y, INT Z, UINT Keys) override;

    /* WM_EXITSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnExitSizeMove(VOID) override;

    /* WM_ENTERSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnEnterSizeMove(VOID) override;

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
    LRESULT OnMessage(UINT Msg, WPARAM wParam, LPARAM lParam) override;
  }; /* End of 'anim' class */

} /* end of 'mzgl' namespace */


#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */