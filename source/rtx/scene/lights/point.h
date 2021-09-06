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

#ifndef __point_h_
#define __point_h_

#include "light_def.h"

/* Project namespace */
namespace acrtx
{
  /* Point light representation class */
  class light_point : public light
  {
  private:
    friend class parser;
    vec3 Pos; // Light position

  public:
    /* Base class constructor.
     * ARGUMENTS:
     *   - Light color:
     *       const vec3 &Color;
     *   - Light position:
     *       const vec3 &Pos;
     */
    light_point( const vec3 &Pos = vec3(0), const vec3 &Color = vec3(0.30, 0.47, 0.8) ) :
      Pos(Pos), light(Color)
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
      S->L = Pos - I.P;
      S->D = S->L.Length();
      S->L /= S->D;
    } /* End of 'Light' function */
  }; /* End of 'light' class */ 
} /* end of 'acrtx' namespace */

#endif /* __light_def_h_ */

/* END OF 'light_def.h' FILE */