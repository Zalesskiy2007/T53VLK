/* FILE NAME   : win.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Helpful window functions.
 */

#include "mzgl.h"

 /* Window name */
#define WND_CLASS_NAME "Ray tracing project"

/* Project namespace */
using namespace mzgl;

/* Window message handle function (CALLBACK version).
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - message identifier (see WM_***):
 *       UINT Msg;
 *   - message first parameter ('word' param):
 *       WPARAM wParam;
 *   - message second parameter ('long' param):
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message return code (depended to Msg type).
 */
LRESULT CALLBACK win::WinFunc(HWND hWnd, UINT Msg,
  WPARAM wParam, LPARAM lParam)
{
  win* Win;
  HDC hDC;
  PAINTSTRUCT ps;

  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO*)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    ((MINMAXINFO*)lParam)->ptMinTrackSize.y =
      GetSystemMetrics(SM_CYCAPTION) * 8 +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    ((MINMAXINFO*)lParam)->ptMinTrackSize.x += 300;
    return 0;
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLongPtr(hWnd, 0, (UINT_PTR)((CREATESTRUCT*)lParam)->lpCreateParams);
  default:
    Win = reinterpret_cast<win*>(GetWindowLongPtr(hWnd, 0));
    if (Win != nullptr)
      switch (Msg)
      {
      case WM_CREATE:
        Win->hWnd = hWnd;
        return Win->OnCreate((CREATESTRUCT*)lParam) ? 0 : -1;
      case WM_SIZE:
        Win->W = (INT)(SHORT)LOWORD(lParam);
        Win->H = (INT)(SHORT)HIWORD(lParam);
        Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
        return 0;
      case WM_ACTIVATE:
        Win->IsActive = LOWORD(wParam) != WA_INACTIVE;
        Win->OnActivate((UINT)LOWORD(wParam), (HWND)(lParam), (BOOL)HIWORD(wParam));
        return 0;
      case WM_ERASEBKGND:
        return 0;
      case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        Win->OnPaint(hDC, &ps);

        EndPaint(hWnd, &ps);
        return 0;
      case WM_DRAWITEM:
        Win->OnDrawItem((INT)wParam, (DRAWITEMSTRUCT*)lParam);
        return 0;
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
          (INT)(SHORT)HIWORD(lParam),
          (INT)(SHORT)HIWORD(wParam),
          (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_LBUTTONDBLCLK:
        return 0;
      case WM_LBUTTONDOWN:
      case WM_RBUTTONDOWN:
      case WM_MBUTTONDOWN:
        return 0;
      case WM_LBUTTONUP:
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
        return 0;
      case WM_DROPFILES:
        Win->OnDropFiles((HDROP)wParam);
        return 0;
      case WM_NOTIFY:
        return Win->OnNotify((INT)wParam, (NMHDR*)lParam);
      case WM_COMMAND:
        Win->OnCommand((INT)LOWORD(wParam), (HWND)lParam, (UINT)HIWORD(wParam));
        return 0;
      case WM_MENUSELECT:
        Win->OnMenuSelect((HMENU)lParam,
          (HIWORD(wParam) & MF_POPUP) ? 0L : (INT)LOWORD(wParam),
          (HIWORD(wParam) & MF_POPUP) ?
          GetSubMenu((HMENU)lParam, LOWORD(wParam)) : 0L,
          (UINT)(((SHORT)HIWORD(wParam) == -1) ? 0xFFFFFFFF : HIWORD(wParam)));
        return 0;
      case WM_INITMENUPOPUP:
        Win->OnInitMenuPopup((HMENU)wParam, (UINT)LOWORD(lParam),
          (BOOL)HIWORD(lParam));
        return 0;
      case WM_HSCROLL:
        Win->OnHScroll((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
        return 0;
      case WM_VSCROLL:
        Win->OnVScroll((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
        return 0;
      case WM_ENTERSIZEMOVE:
        Win->OnEnterSizeMove();
        return 0;
      case WM_EXITSIZEMOVE:
        Win->OnExitSizeMove();
        return 0;
      case WM_DESTROY:
        Win->OnDestroy();
        PostQuitMessage(30);
        return 0;
      default:
        return Win->OnMessage(Msg, wParam, lParam);
      }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'win::WinFunc' function */


/* Window constructor */
win::win(HINSTANCE hInst) : hInstance(hInst), hWnd(nullptr), W(0), H(0), IsActive(TRUE), MouseWheel(0), IsFullScreen(FALSE), FullScreenSaveRect({0})
{
} /* End of 'win::win' constructor */

/* Window create handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::CreateWin(VOID)
{
  WNDCLASS wc;
  HWND hWnd;

  std::mutex Mut;
  Mut.lock();
  if (!GetClassInfo(hInstance, WND_CLASS_NAME, &wc))
  {
    wc.style = CS_VREDRAW | CS_HREDRAW;

    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(win*);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(NULL, IDI_INFORMATION);
    wc.lpszMenuName = NULL;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = win::WinFunc;
    wc.lpszClassName = WND_CLASS_NAME;

    if (!RegisterClass(&wc))
        MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
  }

  hWnd =
    CreateWindow(WND_CLASS_NAME,
      "MZ2 CGSG Sr' VULKAN", /* CGSG Jr' Summer Camp 2023 */
      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      nullptr,
      nullptr,
      hInstance,
      reinterpret_cast<VOID*>(this));

  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);
  Mut.unlock();
} /* End of 'win::CreateWin' function */

/* Window message loop function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Run(VOID)
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
      /* Idle... */
    }
  }
} /* End of 'win::Run' function */

/* END OF 'win.cpp' FILE */