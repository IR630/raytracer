/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : win.cpp
 * PURPOSE     : Raytracing project.
 *               Windows main project module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : Module namespace 'vart'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "vart.h"
#include "win.h"

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL vart::win::OnCreate( CREATESTRUCT *CS )
{
  return TRUE;
} /* End of 'vart::win::OnCreate' function */

/* Flipping fullscreen function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID vart::win::FlipFullScreen( VOID )
{
  static BOOL IsFullScreen = FALSE;
  static RECT SaveRC;

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    // saving old size of window 
    GetWindowRect(hWnd, &SaveRC);

    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top + 201,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'vart::win::FlipFullScreen' function*/

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID vart::win::OnDestroy( VOID )
{
} /* End of 'vart::win::OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID vart::win::OnSize( UINT State, INT W, INT H )
{
} /* End of 'vart::win::OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL vart::win::OnEraseBkgnd( HDC hDC )
{
  return TRUE;
} /* End of 'vart::win::OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID vart::win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
} /* End of 'vart::win::OnPaint' function */ 

/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       UINT Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
VOID vart::win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
  // IsActive = Reason == WA_CLICKACTIVE || Reason == WA_ACTIVE;
} /* End of 'vart::win::OnActivate' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID vart::win::OnTimer( INT Id ) 
{
} /* End of 'vart::win::OnTimer' function */

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
VOID vart::win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  MouseWheel += Z;
} /* End of 'vart::win::OnMouseWheel' function */

/* WM_DROPFILES window message handle function.
 * ARGUMENTS:
 *   - handle to an internal structure describing the dropped files:
 *       HDROP hDrop;
 * RETURNS: None.
 */
VOID vart::win::OnDropFiles( HDROP hDrop )
{
  static CHAR Buf[_MAX_PATH];

  INT n = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
  if (n > 0)
  {
    POINT pt;
    DragQueryPoint(hDrop, &pt);
    ClientToScreen(hWnd, &pt);
    HWND hWndItem = WindowFromPoint(pt);
    ///////////////////////////////////////////////////////////////////
#if 0
    if (hWndItem == /* Check window */ )
    {
      /* for single file: DragQueryFile(hDrop, 0, Buf, sizeof(Buf)); */
      // Handle every file
      for (INT i = 0; i < n; i++)
      {
        DragQueryFile(hDrop, i, Buf, sizeof(Buf));
        /// Handle filename from 'Buf'
        // Can split:
        static CHAR
          Drive[_MAX_DRIVE], Dir[_MAX_DIR],
          FileName[_MAX_FNAME], FileExt[_MAX_EXT];
        _splitpath(Buf, Drive, Dir, FileName, FileExt);
        // . . .
      }
    }
#endif
  }
} /* End of 'vart::win::OnDropFiles' function */

/* WM_NOTIFY window message handle function.
 * ARGUMENTS:
 *   - control identifier:
 *       INT Id;
 *   - notification header depended to control type:
 *       NMHDR *NoteHead;
 * RETURNS:
 *   (LRESULT) return value depended to notification.
 */
LRESULT vart::win::OnNotify( INT Id, NMHDR *NoteHead )
{
  return 0;
} /* End of 'vart::win::OnNotify' function */

/* WM_COMMAND window message handle function.
 * ARGUMENTS:
 *   - item (menu or accelerator) or control window identifier:
 *       INT Id;
 *   - control window handle:
 *       HWND hWndCtl;
 *   - notification: 0 - menu, 1 - accelerator, otherwise -
 *     depended to control (like BM_CLICKED):
 *       UINT CodeNotify;
 * RETURNS: None.
 */
VOID vart::win::OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify )
{
} /* End of 'vart::win::OnCommand' function */

/* WM_DRAWITEM window message handle function.
 * ARGUMENTS:
 *   - control identifier (for menu - 0):
 *       INT Id;
 *   - draw item information structure pointer:
 *       DRAWITEMSTRUCT *DrawItem;
 * RETURNS: None.
 *   (LRESULT) return value depended to notification.
 */
VOID vart::win::OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem )
{
  /*
  if (DrawItem->CtlID == 1) /// sample for check bax draw as button
  {
    UINT Flags = DFCS_BUTTONPUSH;

    if (DrawItem->itemState & ODS_DISABLED)
      Flags |= DFCS_INACTIVE;
    if (DrawItem->itemState & ODS_SELECTED)
      Flags |= DFCS_PUSHED;

    DrawFrameControl(DrawItem->hDC, &DrawItem->rcItem, DFC_BUTTON, Flags);
    InflateRect(&DrawItem->rcItem, -2, -2);
    Flags &= ~DFCS_PUSHED;
    Flags &= ~DFCS_BUTTONPUSH;
    Flags |= DFCS_BUTTONCHECK | DFCS_FLAT;
    if (DrawItem->CtlID == 0) ///
      Flags |= DFCS_CHECKED;
    DrawFrameControl(DrawItem->hDC, &DrawItem->rcItem, DFC_BUTTON, Flags);
  }
  */
} /* End of 'vart::win::OnDrawItem' function */

/* WM_HSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID vart::win::OnHScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'vart::win::OnHScroll' function */

/* WM_VSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID vart::win::OnVScroll( HWND hWndCtl, UINT Code, INT Pos )
{
} /* End of 'vart::win::OnVScroll' function */

/* WM_MENUSELECT window message handle function.
 * ARGUMENTS:
 *   - handle of menu:
 *       HMENU hMenu;
 *   - submenu item ID or submenu index
 *       INT Item;
 *   - handle of popup menu if selected popup submenu:
 *       HMENU hMenuPopup;
 *   - menu item flags (see MF_***):
 *       UINT Flags;
 * RETURNS: None.
 */
VOID vart::win::OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags )
{
} /* End of 'vart::win::OnMenuSelect' function */

/* WM_INITMENUPOPUP window message handle function.
 * ARGUMENTS:
 *   - handle of popup menu:
 *       HMENU hMenu;
 *   - submenu item position:
 *       UINT Item;
 *   - window system menu flag:
 *       BOOL IsSystemMenu;
 * RETURNS: None.
 */
VOID vart::win::OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu )
{
} /* End of 'vart::win::OnInitMenuPopup' function */

/* WM_EXITSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID vart::win::OnExitSizeMove( VOID )
{
} /* End of 'vart::win::OnExitSizeMove' function */

/* WM_ENTERSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID vart::win::OnEnterSizeMove( VOID )
{
} /* End of 'vart::win::OnEnterSizeMove' function */

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
LRESULT vart::win::OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam )
{
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'vart::win::OnMessage' function */

/* Button down function.
 * ARGUMENTS:
 *   - flag is double click:
 *       BOOL IsDoubleClick;
 *   - coordinates:
 *       INT X, Y;
 *   - keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID vart::win::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
{
} /* End of 'vart::win::OnButtonDown' function */

/* Button up function.
 * ARGUMENTS:
 *   - coordinates:
 *       INT X, Y;
 *   - keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID vart::win::OnButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'vart::win::OnButtonUp' function */

/* Mouse move getting coordinates function.
 * ARGUMENTS:
 *   - coordinates:
 *       INT X, Y;
 *   - keys:
 *       UINT Keys;
 * RETURNS: None.
 */
VOID vart::win::OnMouseMove( INT X, INT Y, UINT Keys )
{
} /* End of 'vart::win::OnMouseMove' function */

/* END OF 'win_msg.cpp' FILE */
