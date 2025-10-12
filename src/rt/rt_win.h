/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : rt_win.h
 * PURPOSE     : Ray tracing.
 *               Ray tracing window handle module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_win_h_
#define __rt_win_h_

#include "rt_def.h"
#include "frame.h"

#include <time.h>

/* Project namespace */
namespace vart
{
  /* Window handle class */
  class rt_win : public win
  {
  public:
    scene Scene; // Store scene
    frame Frm;   // Render frame
    camera Cam;  // Scene camera

    /* Default constructor */
    rt_win( HINSTANCE hInst ) : win(hInst)
    {
    } /* End of 'rt_win' constructor */

    // Background brush
    HBRUSH hBrBack {};

    // Mouse store coordinates
    INT MouseX = 0, MouseY = 0;

    // Image data
    INT
      ImgW = 0, ImgH = 0,         // Image size
      ImgX = 0, ImgY = 0,         // Image position
      ImgZoom = 1,                // Image zoom factor
      ImgZoomW = 0, ImgZoomH = 0; // Image zoomed size

    /* Update frame image drawing data function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID )
    {
      // Correct image position
    
      // Horizontal
      if (ImgZoomW <= W)
        // inside
        ImgX = (W - ImgZoomW) / 2;
      else
      {
        // shift left border
        if (ImgX + ImgZoomW < W)
          ImgX = W - ImgZoomW;
        // shift right border
        if (ImgX > 0)
          ImgX = 0;
      }
      // Vertical
      if (ImgZoomH <= H)
        // inside
        ImgY = (H - ImgZoomH) / 2;
      else
      {
        // shift top border
        if (ImgY + ImgZoomH < H)
          ImgY = H - ImgZoomH;
        // shift bottom border
        if (ImgY > 0)
          ImgY = 0;
      }

      // Correct scroll bars
      auto scrl =
        [this]( INT ScrollType, INT &ImgPos, INT &ImgSize, INT &WinSize )
        {
          SCROLLINFO ScrollInfo {sizeof(SCROLLINFO), SIF_PAGE | SIF_POS | SIF_RANGE};
    
          if (ImgSize > WinSize)
            SetScrollPos(hWnd, ScrollType, -ImgPos, FALSE);
    
          // Update horizontal/vertical scroll bar data
          if (Frm.W == 0 || Frm.H == 0 || ImgSize <= WinSize)
          {
            // Remove horizontal/vertical scroll bar
            ScrollInfo.nMin = ScrollInfo.nMax = 0;
            SetScrollInfo(hWnd, ScrollType, &ScrollInfo, TRUE);
          }
          else
          {
            GetScrollInfo(hWnd, ScrollType, &ScrollInfo);
            ScrollInfo.nPos = -ImgPos; /// !!!
            ScrollInfo.nMin = 0;
            ScrollInfo.nMax = ImgSize;
            ScrollInfo.nPage = WinSize;
            SetScrollInfo(hWnd, ScrollType, &ScrollInfo, TRUE);
          }
        };
      scrl(SB_HORZ, ImgX, ImgZoomW, W);
      scrl(SB_VERT, ImgY, ImgZoomH, H);
    } /* End of 'Update' function */

    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    BOOL OnCreate( CREATESTRUCT *CS ) override
    {
      // Create background brush
      if (HBITMAP hbm; (hbm = (HBITMAP)LoadImage(NULL, "***.BMP", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)) != nullptr)
      {
        LOGBRUSH logbr;
        logbr.lbStyle = BS_PATTERN;
        logbr.lbColor = DIB_RGB_COLORS;
        logbr.lbHatch = (ULONG_PTR)hbm;
        hBrBack = CreateBrushIndirect(&logbr);
        DeleteObject(hbm);
      }
      else
        hBrBack = nullptr;

      SetTimer(hWnd, 47, 470, nullptr);
      //Frm.Resize(7680, 4320);
      // 4k: 3840 2160; 2k: 2560 1440; 8k: 7680 4320; FHD: 1920 1080
      //Frm.Resize(100, 100);
      Frm.Resize(3840, 2160);
      Cam.Resize(Frm.W, Frm.H);
      ImgZoomW = ImgW = Frm.W;
      ImgZoomH = ImgH = Frm.H;
      Update();
      return TRUE;
    } /* End of 'OnCreate' function */

    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    VOID OnTimer( INT Id ) override
    {
      InvalidateRect(hWnd, nullptr, FALSE);
    } /* End of 'OnTimer' function */

    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID OnDestroy( VOID ) override
    {
      DeleteObject(hBrBack);
      KillTimer(hWnd, 47);
      PostQuitMessage(30);
    } /* End of 'OnDestroy' function */

    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID OnSize( UINT State, INT W, INT H ) override
    {
      if (Frm.W != 0 && Frm.H != 0)
      {
        ImgX = (W - ImgZoomW) / 2;
        ImgY = (H - ImgZoomH) / 2;
        Update();
        InvalidateRect(hWnd, nullptr, FALSE);
      }
    } /* End of 'OnSize' function */

    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    BOOL OnEraseBkgnd( HDC hDC ) override
    {
      return TRUE;
    } /* End of 'OnEraseBkgnd' function */

    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    VOID OnPaint( HDC hDC, PAINTSTRUCT *PS ) override
    {
      SelectObject(hDC, GetStockObject(NULL_PEN));
      if (hBrBack != nullptr)
        SelectObject(hDC, hBrBack);
      else
        SelectObject(hDC, GetStockObject(GRAY_BRUSH));
      if (Frm.W != 0 && Frm.H != 0)
      {
        // Draw left rect
        if (ImgX > 0)
          Rectangle(hDC, 0, ImgY, ImgX + 1, ImgY + ImgZoomH + 1);
        // Draw top rect
        if (ImgY > 0)
          Rectangle(hDC, 0, 0, W + 1, ImgY + 1);
        // Draw right rect
        if (W - ImgX - ImgZoomW  > 0)
          Rectangle(hDC, ImgX + ImgZoomW, ImgY, W + 1, ImgY + ImgZoomH + 1);
        // Draw bottom rect
        if (H - ImgY - ImgZoomH > 0)
          Rectangle(hDC, 0, ImgY + ImgZoomH, W + 1, H + 1);
        Frm.Draw(hDC, ImgX, ImgY, ImgZoomW, ImgZoomH);
      }
      else
        Rectangle(hDC, 0, 0, W + 1, H + 1); 
      // Frm.Draw(hDC, 0, 0, Frm.W, Frm.H);
    } /* End of 'OnPaint' function */ 

    /* WM_MOUSEWHEEL window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse wheel delta value (120 points per rotate):
     *       INT Z;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys ) override
    {
      INT
        OldZoomW = ImgZoomW,
        OldZoomH = ImgZoomH;

      if (Z > 0 && ImgZoom < 13 && (ImgZoom < 0 || (UINT64)ImgW * ImgH * ((ImgZoom + 1) * (ImgZoom + 1)) <= 1000000000LL))
        ImgZoom++, ImgZoom = ImgZoom == 0 ? 1 : ImgZoom;
      else if (Z < 0 && ImgZoom > -12)
        ImgZoom--, ImgZoom = (ImgZoom == 0 || ImgZoom == -1) ? -2 : ImgZoom;
      if (ImgZoom > 0)
        ImgZoomW = ImgW * ImgZoom, ImgZoomH = ImgH * ImgZoom;
      else
        ImgZoomW = ImgW / -ImgZoom, ImgZoomH = ImgH / -ImgZoom;

      if (OldZoomW != ImgZoomW)
        ImgX = -(INT)(((DOUBLE)ImgZoomW * (-ImgX + X) / OldZoomW - X));
      if (OldZoomH != ImgZoomH)
        ImgY = -(INT)(((DOUBLE)ImgZoomH * (-ImgY + Y) / OldZoomH - Y));

      Update();
      InvalidateRect(hWnd, nullptr, FALSE);
    } /* End of 'OnMouseWheel' function */

    /* WM_*BUTTONDOWN window message handle function.
     * ARGUMENTS:
     *   - double click flag:
     *       BOOL IsDoubleClick;
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) override
    {
      if (IsDoubleClick)
        FlipFullScreen();
      SetCapture(hWnd);
      MouseX = X;
      MouseY = Y;

      if (Keys & MK_MBUTTON)
      {
        X -= ImgX;
        Y -= ImgY;
        if (ImgZoom < 0)
        {
          X *= -ImgZoom;
          Y *= -ImgZoom;
        }
        else
        {
          X /= ImgZoom;
          Y /= ImgZoom;
        }
        printf("c: %08X x:%5d y:%5d\n", Frm.GetPixel(X, Y), X, Y);
        ray r = Cam.FrameRay(X + 0.5, Y + 0.5);
        vec3 c = Scene.Trace(r, Scene.Air, 1, 0);

        printf("Render (%d,%d):RGB(%.3f,%.3f,%.3f)\n", X, Y, c.X, c.Y, c.Z);
      }
    } /* End of 'OnButtonDown' function */

    /* WM_*BUTTONUP window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnButtonUp( INT X, INT Y, UINT Keys ) override
    {
      ReleaseCapture();
    } /* End of 'OnButtonUp' function */

    /* WM_MOUSEMOVE window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    VOID OnMouseMove( INT X, INT Y, UINT Keys ) override
    {
      if (Keys & MK_LBUTTON)
      {
        ImgX += X - MouseX;
        ImgY += Y - MouseY;
        MouseX = X;
        MouseY = Y;
        Update();
        InvalidateRect(hWnd, NULL, FALSE);
      }
      if (Keys & MK_RBUTTON)
      {
        X -= ImgX;
        Y -= ImgY;
        if (ImgZoom < 0)
        {
          X *= -ImgZoom;
          Y *= -ImgZoom;
        }
        else
        {
          X /= ImgZoom;
          Y /= ImgZoom;
        }
        printf("c: %08X x:%5d y:%5d\n", Frm.GetPixel(X, Y), X, Y);
      }
    } /* End of 'OnMouseMove' function */

    /* WM_HSCROLL message handle function.
     * ARGUMENTS:
     *   - handle of scroll window or nullptr for window scroll bars:
     *       HWND hWndCtl;
     *   - scrool bar request code (see SB_***):
     *      UINT Code;
     *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
     *      INT Pos;
     * RETURNS: None.
     */
    VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos ) override
    {
      switch (Code)
      {
      case SB_LINEDOWN:
        ImgX--;
        break;
      case SB_LINEUP:
        ImgX++;
        break;
      case SB_PAGEDOWN:
        ImgX -= W;
        break;
      case SB_PAGEUP:
        ImgX += W;
        break;
      case SB_THUMBTRACK:
        ImgX = -Pos;
        break;
      }
      Update();
      InvalidateRect(hWnd, NULL, FALSE);
    } /* End of 'OnHScroll' function */

    /* WM_VSCROLL message handle function.
     * ARGUMENTS:
     *   - handle of scroll window or nullptr for window scroll bars:
     *       HWND hWndCtl;
     *   - scrool bar request code (see SB_***):
     *      UINT Code;
     *   - schroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
     *      INT Pos;
     * RETURNS: None.
     */
    VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos ) override
    {
      switch (Code)
      {
      case SB_LINEDOWN:
        ImgY--;
        break;
      case SB_LINEUP:
        ImgY++;
        break;
      case SB_PAGEDOWN:
        ImgY -= H;
        break;
      case SB_PAGEUP:
        ImgY += H;
        break;
      case SB_THUMBTRACK:
        ImgY = -Pos;
        break;
      }
      Update();
      InvalidateRect(hWnd, NULL, FALSE);
    } /* End of 'OnVScroll' function */

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
    LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam ) override
    {
      switch (Msg)
      {
      case WM_KEYDOWN:
        if (wParam == 'F')
          FlipFullScreen();
        else if (wParam == 'C')
        {
          Frm.Fill(0x00302908);
        }
        else if (wParam == 'R')
        {
          if (!Scene.IsRenderActive)
          {
            Scene.IsRenderActive = TRUE;
            Scene.IsToBeStop = FALSE;
            Scene.IsReadyToFinish = FALSE;
            std::cout << std::endl << "Start render scene" << std::endl;
            std::thread Th;
            Th = std::thread(
              [&]( VOID )
              {
                LONG tt = clock();

                //DBL t = (DBL)tt / CLOCKS_PER_SEC;
                //Cam.SetLocAtUp(vec3(2, 2, 2), vec3(0, 0, 0));
                Scene.Render(Cam, Frm);
                tt = clock() - tt;
                INT Seconds = (INT)((DBL)tt / CLOCKS_PER_SEC);

                std::cout <<
                  std::fixed << (DBL)tt / CLOCKS_PER_SEC <<
                  " :: " << std::setfill('0') << std::setw(2) <<
                                                 Seconds / 60 / 60 <<
                  ":" << std::setfill('0') << std::setw(2) <<
                                                 Seconds / 60 % 60 <<
                  ":" << std::setfill('0') << std::setw(2) <<
                                                 Seconds % 60 << "\r";
                Frm.AutoSaveTGA("CGSG forever!!!",
                  {Seconds / 60 / 60, Seconds / 60 % 60, Seconds % 60});
                InvalidateRect(hWnd, NULL, FALSE);
                UpdateWindow(hWnd);
                Scene.IsRenderActive = FALSE;
                Scene.IsToBeStop = FALSE;
                Scene.IsReadyToFinish = TRUE;
              });
            Th.detach();
          }
        }
        else if (wParam == VK_ESCAPE)
        {
          if (!Scene.IsRenderActive)
            DestroyWindow(hWnd);
          else
            Scene.IsToBeStop = TRUE;
        }
        return 0;
      }
      return DefWindowProc(hWnd, Msg, wParam, lParam);
    } /* End of 'OnMessage' function */
  }; /* End of 'rt_win' class */
} /* End of 'vart' namespace */

#endif /* __rt_win_h_ */

/* END OF 'rt_win.h' FILE */
