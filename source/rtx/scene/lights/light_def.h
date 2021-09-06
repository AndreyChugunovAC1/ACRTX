/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : light_def.h
 * PURPOSE     : Raytracing project.
 *               Light module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */


#ifndef __light_def_h_
#define __light_def_h_

// #include "../../def.h" <-- included in next files:
#include "../../scene/scene_def.h"

/* Project namespace */
namespace acrtx
{
  /* Light representation class */
  class light
  {
  protected:
    friend class parser;
    vec3 Color; // Light source's color

    /* Base class constructor 
     * ARGUMENTS:
     *   - Light color:
     *       const vec3 &Color;
     */
    light( const vec3 &Color ) :
      Color(Color)
    {
    } /* End of 'light' function */

  public:
    /* Default class constructor */
    light( VOID ) :
      Color(vec3(0))
    {
    } /* End of 'light' function */

    /* Virtual count shade color function.
     * ARGUMENTS:
     *   - Intersection information:
     *       const inter &I;
     *   - Shade information:
     *       shade * const S;
     * RETURNS: None.
     */
    virtual VOID Light( const inter &I, shade * const S ) const
    {
    } /* End of 'Light' function */
  }; /* End of 'light' class */ 
} /* end of 'acrtx' namespace */

#endif /* __light_def_h_ */

/* END OF 'light_def.h' FILE */