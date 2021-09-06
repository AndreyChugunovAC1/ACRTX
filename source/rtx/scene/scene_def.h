/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : scene.h
 * PURPOSE     : Raytracing project.
 *               Scene module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __scene_def_h_
#define __scene_def_h_

#include "../../def.h"

namespace acrtx
{
  /* Previous shape class declaration*/
  class shape;

  /* Intersection structure */
  class inter
  {
  public:
    DBL T {HUGE_VAL};    // Ray coeficent of intersection
    vec3 N {},           // Normal in intersection point (normalized)
      P {};              // Intersection point
    BOOL IsIn {FALSE};   // Is inside flag
    const shape * Sh {}; // Intersected shape
    INT Extra;           // Extra value
  }; /* End of 'inter' class */

  /* Shade info class */
  class shade 
  {
  public:
    vec3 L, // Direction from intersect point to light
      C;    // Light's color
    DBL D;  // Distance to light source
  }; /* End of 'shade' class */
} /* end of 'acrtx' namespace */

#endif /* __scene_def_h_ */

/* END OF 'scene_def.h' FILE */