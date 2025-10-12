/*************************************************************
 * Copyright (C) 2024
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : main.cpp
 * PURPOSE     : Ray tracing.
 *               Main function module.
 * PROGRAMMER  : CGSG-SummerCamp'2024.
 *               Reznikov Ivan (IR6).
 * LAST UPDATE : 30.07.2024.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "vart.h"

#include "def.h"

/* The main program function.
 * ARGUMENTS:
 *   - handle of application instance:
 *       HINSTANCE hInstance;
 *   - dummy handle of previous application instance (not used):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - show window command parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) Error level for operation system (0 for success).
 */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
                    CHAR *CmdLine, INT ShowCmd )
{
  HWND hCnsWnd = GetConsoleWindow();
  RECT rc;

  AllocConsole();
  SetConsoleTitle("My title");
  GetWindowRect(hCnsWnd, &rc);
  MoveWindow(hCnsWnd, 102, 0, 800, 100, TRUE);
  std::freopen("CONOUT$", "w", stdout);
  system("@chcp 1251 > nul");
  SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0x0C);

  vart::rt_win MyWin(hInstance);

  MyWin.Create("My class name");

   //MyWin.Scene << new vart::plane(vart::vec3(0, -0.3, 0), vart::vec3(0, -1, 0)) << new vart::plane(vart::vec3(3, 0, 0), vart::vec3(-1, 0, 0));

  //MyWin.Scene << new vart::box(vart::vec3(0), vart::vec3(0.3));
  //for (INT i = 0; i < 100; i++)

  //MyWin.Cam.SetLocAtUp(vart::vec3(0, 2, 5), vart::vec3(0));
  /// subtrack Test
  //MyWin.Scene << new csg::subtrack(new vart::box(vart::vec3(1), vart::vec3(2), vart::surface("Black Plastic", vart::vec3(0), vart::vec3(0))),
    //                               new vart::sphere(vart::vec3(1.5), 0.7, vart::surface("Bronze", vart::vec3(0), vart::vec3(0))));

  /// scene test spheres
  /*
  MyWin.Cam.SetLocAtUp(vart::vec3(3, 1.5, 2), vart::vec3(1, -1, 0));
  MyWin.Scene << new vart::box(vart::vec3(-10), vart::vec3(10), vart::surface("Black Plastic", vart::vec3(0.7), vart::vec3(0)));
  for (INT i = 0; i < 30; i++)
    MyWin.Scene << new vart::sphere(vart::vec3::Rnd1() * 2, 0.4, vart::surface("Silver", vart::vec3(0.1), vart::vec3(1)));
  //MyWin.Scene << new vart::plane(vart::vec3(-0.1), vart::vec3(0, -1, 0), vart::surface("Jade", vart::vec3(0), vart::vec3(1)));
  MyWin.Scene << new vart::point(vart::vec3(0), vart::vec3(0.7, 0, 0.4), 20);
  MyWin.Scene << new vart::point(vart::vec3(2.5), vart::vec3(0, 0.3, 0), 20);
  */

  /// Michael scene
  /*
  MyWin.Cam.SetLocAtUp(vart::vec3(20), vart::vec3(0));
  MyWin.Scene << new vart::box(vart::vec3(-5), vart::vec3(5), vart::surface("Silver", vart::vec3(0), vart::vec3(1)))
              << new vart::point(vart::vec3(0), vart::vec3(1), 10)
              //<< new vart::sphere(vart::vec3(2, 2, 2), 1, vart::surface("Black Plastic", vart::vec3(0.5), vart::vec3(0.5)))
              << new vart::point(vart::vec3(0, 30, 0), vart::vec3(0.6, 0.6, 0.6), 10)
              //<< new vart::point(vart::vec3(10, 50, 0), vart::vec3(0.6, 0, 0.6), 10)
              //<< new vart::point(vart::vec3(-10, 50, 0), vart::vec3(0.6, 0, 0), 10)
              << new vart::point(vart::vec3(10, 30, -10), vart::vec3(0.7, 0.3, 0.7), 10)
              << &(*(new vart::plane(vart::vec3(-2.1), vart::vec3(0, -1, 0), vart::surface("Silver", vart::vec3(1), vart::vec3(0))))<< new vart::checker());
  for (INT i = -10; i < 10; i++)
    for (INT j = -10; j < 10; j++)
    {
      if (i + j % 3 == 0)
        MyWin.Scene << new vart::sphere(vart::vec3(i * 4, 5, j * 4) * vart::vec3::Rnd1(), 0.6, vart::surface("Black Plastic", vart::vec3(1), vart::vec3(0.5)));
      else if (i + j % 3 == 1)
        MyWin.Scene << new vart::sphere(vart::vec3(i * 4, 20, j * 4) * vart::vec3::Rnd1(), 0.8, vart::surface("Black Plastic", vart::vec3(0.5), vart::vec3(0.9)));
      else
        MyWin.Scene << new vart::sphere(vart::vec3(i * 4, 10, j * 4) * vart::vec3::Rnd1(), 0.6, vart::surface("Black Plastic", vart::vec3(0.8), vart::vec3(0.5)));
    }
  */

    ///
    MyWin.Cam.SetLocAtUp(vart::vec3(10), vart::vec3(0));

    MyWin.Scene 
                //<< new vart::sphere(vart::vec3(0), 25, vart::surface("Silver", vart::vec3(1), vart::vec3(0.5)))

                << new vart::sphere(vart::vec3(0), 1, vart::surface("Silver", vart::vec3(0), vart::vec3(1)))
                << new vart::point(vart::vec3(0), vart::vec3(0, 0.40, 0.40), 10)

                << new vart::sphere(vart::vec3(-2, 2, 0), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))
                //<< new vart::point(vart::vec3(-2, 2, 0), vart::vec3(0, 0.7, 0), 10)

                << new vart::sphere(vart::vec3(2, 2, 0), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))
                //<< new vart::point(vart::vec3(2, 2, 0), vart::vec3(0, 0.7, 0), 10)

                << new vart::sphere(vart::vec3(-2, 2, 2), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))
                //<< new vart::point(vart::vec3(-2, 2, 2), vart::vec3(0.4, 0, 0), 10)

                << new vart::sphere(vart::vec3(2, 2, -2), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))
                //<< new vart::point(vart::vec3(2, 2, -2), vart::vec3(0.4, 0, 0), 10)

                << new vart::sphere(vart::vec3(-3, 2, 0), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))
                //<< new vart::point(vart::vec3(-2, 2, 0), vart::vec3(0, 0.7, 0), 10)

                << new vart::sphere(vart::vec3(3, 2, 0), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))
                //<< new vart::point(vart::vec3(2, 2, 0), vart::vec3(0, 0.7, 0), 10)

                << new vart::sphere(vart::vec3(-3, 2, 3), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))
                //<< new vart::point(vart::vec3(-2, 2, 2), vart::vec3(0.4, 0, 0), 10)

                << new vart::sphere(vart::vec3(3, 2, -3), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))
                //<< new vart::point(vart::vec3(2, 2, -2), vart::vec3(0.4, 0, 0), 10)

                << new vart::sphere(vart::vec3(4, 2, 4), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))

                << new vart::sphere(vart::vec3(-4, 2, 4), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))

                << new vart::sphere(vart::vec3(4, 2, -4), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))

                << new vart::sphere(vart::vec3(-4, 2, -4), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))

                << new vart::sphere(vart::vec3(6, 2, 6), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))

                << new vart::sphere(vart::vec3(-6, 4, 6), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))

                << new vart::sphere(vart::vec3(6, 4, -6), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))

                << new vart::sphere(vart::vec3(-6, 4, -6), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)))

                << &(*(new vart::plane(vart::vec3(-0.1), vart::vec3(0, -1, 0), vart::surface("Silver", vart::vec3(0.7), vart::vec3(0))))<< new vart::checker())
                << new vart::point(vart::vec3(10, 0, 0), vart::vec3(0.05, 0.1, 0.05), 10);

  //for (INT i = 0; i < 3; i++)
    //MyWin.Scene << new vart::sphere(vart::vec3::Rnd1(), 0.2, vart::surface("Obsidian", vart::vec3(0.6), vart::vec3(0.7)));
  
  //MyWin.Cam.SetLocAtUp(vart::vec3(0, -8, 0), vart::vec3(0));
  
  //for (INT i = 0; i < 100; i++)
    //MyWin.Scene << new vart::sphere(vart::vec3::Rnd1() * 5, 3, vart::surface("Peweter", vart::vec3(0), vart::vec3(0)));
    
  //MyWin.Scene <<  new vart::triangle(vart::vec3(0), vart::vec3(0, 0, 1), vart::vec3(1, 0, 0), vart::surface());
  //MyWin.Scene <<  new vart::sphere(vart::vec3(-2, 0, 0), 1, vart::surface(vart::vec3(0.25, 0.25, 0.25), vart::vec3(0.4, 0.4, 0.4), vart::vec3(0.774597, 0.774597, 0.774597), 76.8, vart::vec3(0), vart::vec3(0.9)));
  //MyWin.Scene <<  new vart::sphere(vart::vec3(0, 1.5, 0), 1, vart::surface(vart::vec3(0.23125,0.23125,0.23125), vart::vec3(0.2775,0.2775,0.2775), vart::vec3(0.773911,0.773911,0.773911), 89.6));

  /*
  MyWin.Scene << new vart::box(vart::vec3(0, -0.1, 0), vart::vec3(1, 1.1, 1), vart::surface("Black Plastic", vart::vec3(0.5), vart::vec3(0.5)));
  MyWin.Scene << new vart::sphere(vart::vec3(0, 1, 0), 1, vart::surface("Silver", vart::vec3(1), vart::vec3(0)));
  MyWin.Scene << new vart::triangle(vart::vec3(1, 0, 0), vart::vec3(1, 1, 0), vart::vec3(1, 0, 1), vart::surface("Silver", vart::vec3(1), vart::vec3(0.4)));
  */

  /// purple easy test
  /*
  MyWin.Cam.SetLocAtUp(vart::vec3(3), vart::vec3(0));
  MyWin.Scene << new vart::sphere(vart::vec3(0, 0, 0), 0.5, vart::surface("Silver", vart::vec3(1), vart::vec3(0)));
  MyWin.Scene << new vart::point(vart::vec3(1, 1, 0), vart::vec3(0, 0.7, 0), 10)
              << &(*(new vart::plane(vart::vec3(-0.1), vart::vec3(0, -1, 0), vart::surface("Silver", vart::vec3(1), vart::vec3(0)))) << new vart::checker());
  */
  /// BEST
  /*
  MyWin.Cam.SetLocAtUp(vart::vec3(5), vart::vec3(0));
  for (INT i = 0; i < 100; i++)
    MyWin.Scene << new vart::sphere(vart::vec3(3, 3, -i) * vart::vec3::Rnd1(), 0.5, vart::surface("Bronze", vart::vec3(0.6), vart::vec3(0.8)));
  MyWin.Scene << new vart::box(vart::vec3(-10), vart::vec3(1, 1.1, 1), vart::surface("Black Plastic", vart::vec3(0.5), vart::vec3(0.5)));
  MyWin.Scene << new vart::quadric(6, 0.3, 7, -3, 1, 0.47, -20, 4, 2, -1, vart::surface("Silver", vart::vec3(0.1), vart::vec3(0.2)));
  MyWin.Scene << new vart::point(vart::vec3(0, 3, 0), vart::vec3(0.7, 0.7, 0.7), 10);
  MyWin.Scene << new vart::dir(vart::vec3(0), vart::vec3(0, 0.7, 0));
  MyWin.Scene << new vart::point(vart::vec3(0, 10, -15), vart::vec3(0.5, 0, 0.4), 10);
  MyWin.Scene << new vart::point(vart::vec3(0, 5, -5), vart::vec3(0.5, 0.6, 0.4), 10);
  MyWin.Scene << new vart::point(vart::vec3(5, 10, -15), vart::vec3(0, 0.7, 0), 10);
  */
  //MyWin.Scene << new vart::plane(vart::vec3(-3, -0.1,-5), vart::vec3(-1, 0, 0), vart::surface("Peweter", vart::vec3(0.2), vart::vec3(0)));
  //MyWin.Scene << new vart::plane(vart::vec3(0, -0.1, 0), vart::vec3(0, -1, 0), vart::surface("Silver", vart::vec3(0.5), vart::vec3(0)));
  //MyWin.Scene << new vart::plane(vart::vec3(-3, -0.1, -5), vart::vec3(0, 0, -1), vart::surface("Polished Bronze", vart::vec3(0.2), vart::vec3(0)));

  //MyWin.Scene << new vart::point(vart::vec3(0), vart::vec3(1, 1, 1), 1);
  
  /*
  MyWin.Scene << new vart::point(vart::vec3(0.3), vart::vec3(0, 0.4, 0), 10);
  MyWin.Scene << new vart::point(vart::vec3(3, 50, 50), vart::vec3(0.4, 0, 0.7), 10);
  */
  //MyWin.Scene << new vart::point(vart::vec3(1, 1, -2), vart::vec3(0.3, 0.3, 0.3), 10);
  /*
  MyWin.Scene << new vart::point(vart::vec3(0, 2, 0), vart::vec3(0.6, 0.6, 0.6), 10);
  MyWin.Scene << new vart::point(vart::vec3(-3, 1.5, 0), vart::vec3(0.6, 0, 0.6), 10);
  for (INT i = -1; i < 1; i++)
    for (INT j = -1; j < 1; j++)
    {
      MyWin.Scene << new v8.0
        art::sphere(vart::vec3(i * 2, 3, -j * 2), 1, vart::surface("Gold", vart::vec3(0), vart::vec3(1)));
      MyWin.Scene << new vart::sphere(vart::vec3(i * 2, 0, -j * 2), 1, vart::surface("Gold", vart::vec3(0.3), vart::vec3(0)));
    }
    */
              //<< new vart::box(vart::vec3(1), vart::vec3(2), vart::surface("Gold", vart::vec3(0.9), vart::vec3(0)))
  //MyWin.Scene << new vart::plane(vart::vec3(-0.2), vart::vec3(0, -1, 0), vart::surface("Pearl", vart::vec3(0), vart::vec3(0)));
  //MyWin.Cam.SetLocAtUp(vart::vec3(0, 2, 5), vart::vec3(0)); 
  //MyWin.Scene << new vart::triangle(vart::vec3(0), vart::vec3(0, 0.5, 0), vart::vec3(0, 0, 0.5));
  //MyWin.Scene << new csg::intersection(new vart::sphere(vart::vec3(0.5), 1),
    //                               new vart::sphere(vart::vec3(0), 1));
  //MyWin.Scene << new csg::merge(new vart::sphere(vart::vec3(0), 1.4),
    //                            new vart::box(vart::vec3(-1), vart::vec3(1)));

  //MyWin.Scene << new vart::sphere(vart::vec3(0), 1) << new vart::sphere(vart::vec3(0.5), 1);

  //MyWin.Scene << new csg::clip(new vart::plane(vart::vec3(-0.2), vart::vec3(1, 0, 0)),
    //                           new vart::box(vart::vec3(-1), vart::vec3(1)));

  //MyWin.Scene <<  new csg::clip(new vart::plane(vart::vec3(-0.2), vart::vec3(0, -1, 0)),
    //                            new vart::triangle(vart::vec3(-0.2), vart::vec3(1, -0.2, 1), vart::vec3(0, -0.2, 1)));
  MyWin.Run();

  if (MyWin.Scene.IsRenderActive)
  {
    MyWin.Scene.IsToBeStop = TRUE;
    std::cout << "\nWait render thread finishing\n";
    while (!MyWin.Scene.IsReadyToFinish)
      ;
    std::cout << "\nAfter waiting\n";
  }
  std::cout << "\nFinish\n";

  return 0;
} /* End of 'WinMain' function */

/* END OF 'main.cpp' FILE */
