/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : main.h
 * PURPOSE     : Raytracing project.
 *               Main file.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "rtx\raytracer.h"

// Single tone declaration
acrtx::raytracer acrtx::raytracer::Instance;

/* Main program function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
INT main( VOID )//INT ArgC, CHAR *ArgV[] )
{
  using namespace acrtx;

  raytracer & R = raytracer::Get();
  // Library:
  R.Materials.Add("MBlue", 
    material(
        vec3(0.08, 0.03, 0.19), 
        vec3(0.08, 0.04, 0.19), 
        vec3(0.06, 0.02, 0.18), 
        10, 0.6, 0.0
      ));
  R.Materials.Add("NMRed", 
    material(
        vec3(0.19, 0.04, 0.03), 
        vec3(0.18, 0.03, 0.04), 
        vec3(0.15, 0.04, 0.06), 
        10, 0.4, 0.2
      ));
  R.Materials.Add("NMGreen", 
    material(
        vec3(0.03, 0.19, 0.03), 
        vec3(0.04, 0.13, 0.04), 
        vec3(0.05, 0.14, 0.06), 
        10, 0.0, 0.0
      ));
  R.Environments.Add("Normal",
    envi());
  R.Thors.Add("Thor1",
    thor(R.Materials.Get("NMRed"), R.Environments.Get("DEFAULT"), R.Textures.Get("DEFAULT"), 2, 2.6, vec3(1), vec3(0, 3, 0)));
  R.Planes.Add("Floor",
    plane(R.Materials.Get("MBlue")));
  R.LightPoints.Add("L1",
    light_point(vec3(3, 5, 7) * 2, vec3(0.4, 0.5, 0.3)));
  R.LightPoints.Add("L3",
    light_point(vec3(-3, 5, -4) * 4, vec3(0.8, 0.3, 0.1)));
  R.LightPoints.Add("L2",
    light_point(vec3(-3, 5, 2) * 4, vec3(0.2, 0.1, 0.5)));
  R.Spheres.Add("S1", sphere(vec3(2, 4, 1), 2, R.Materials.Get("NMGreen")));
  // Settings
  R.Resize(1200, 1200);
  R.GetCamera().SetLocAt(vec3(15, 8, 15), vec3(0, 0, 0));

  // Scene setting
  R.ChooseScene("AC1");
  R.Add(R.Thors.Get("Thor1"));
  R.Add(R.Planes.Get("Floor"));
  R.Add(R.LightPoints.Get("L1"));
  R.Add(R.LightPoints.Get("L2"));
  R.Add(R.LightPoints.Get("L3"));
  // R.Add(R.Spheres.Get("S1"));
 /* for (INT i = 0; i < 18; i++)
  {
    R.GetCamera().RotateAt(vec3(0, 10, 0));
    R.DrawScene();
  }
  for (INT i = 0; i < 18; i++)
  {
    R.GetCamera().RotateAt(vec3(10, 0, 0));
    R.DrawScene();
  }*/
  R.Resize(1200, 1200);
  R.DrawScene();
} /* End of 'main' function */

/* END OF 'main.cpp' FILE */