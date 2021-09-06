/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : point.h
 * PURPOSE     : Raytracing project.
 *               Light module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __dir_h_
#define __dir_h_

#include "light_def.h"

/* Project namespace */
namespace acrtx
{
  /* Point light representation class */
  class light_dir : public light
  {
  private:
    friend class parser;
    vec3 Dir; // Light position

  public:
    /* Base class constructor.
     * ARGUMENTS:
     *   - Light color:
     *       const vec3 &Color;
     *   - Light position:
     *       const vec3 &Pos;
     */
    light_dir( const vec3 &Dir = vec3(0), const vec3 &Color = vec3(0.30, 0.47, 0.8) ) :
      Dir(-Dir.Normalize()), light(Color)
    {
    } /* End of 'light_point' function */

    /* Count shade color function.
     * ARGUMENTS:
     *   - Intersection information:
     *       const inter &I;
     *   - Shade information:
     *       shade * const S;
     * RETURNS: None.
     */
    VOID Light( const inter &I, shade * const S ) const final
    {
      S->C = Color;
      S->L = Dir;
      S->D = 1;
      // S->L /= S->D;
    } /* End of 'Light' function */
  }; /* End of 'light' class */ 
} /* end of 'acrtx' namespace */

#endif /* __dir_h_ */

/* END OF 'dir.h' FILE */