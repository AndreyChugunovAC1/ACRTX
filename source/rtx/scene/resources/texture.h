/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : texture.h
 * PURPOSE     : Raytracing project.
 *               Texture module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __texture_h_
#define __texture_h_

#include "../../../def.h"

/* Project namespace */
namespace acrtx
{
  /* Matrerial representation class */
  class texture
  {
  public:
    /* Type of texture */
    enum struct type
    {
      procedure,
      image,
      none
    }; /* End of 'texture_type' class */

    /* Type of procedure */
    enum struct proc
    {
      mandelbrot,
      cells,
    }; /* End of 'texture_type' class */

  private:
    // friend class parser;
    type Type;    // Type of texture
    vec3 * Plane; // Plane of image
    proc Proc;

    /* Get texture color by texture coordinates.
     * ARGUMENTS:
     *   - Coordinates:
     *       const DBL X, const DBL Y;
     * RETURNS:
     *   (vec3) Color;
     */
    vec3 Mand( DBL X0, DBL Y0 )
    {
      X0 -= 0.5;
      DBL n = 0;
      DBL X = X0, Y = Y0;
      DBL TmpX;

      // 255 - ...
      // if (X <= 3 && X >= -3 && Y <= 3 && Y >= -3)
        while (n++ < 99 && X * X + Y * Y < 4)
        {
          X = (TmpX = X) * X - Y * Y + X0;
          Y = 2 * TmpX * Y + Y0;
        }
      return (n = sqrt(n / 100), vec3(n * 0.4, n * 0.2, n * 0.9) + vec3(0.1));
    } /* End of 'Mand' function */
  public:
    /* Get texture color by texture coordinates.
     * ARGUMENTS:
     *   - Coordinates:
     *       const DBL X, const DBL Y;
     * RETURNS:
     *   (vec3) Color;
     */
    vec3 Get( const DBL X, const DBL Y )
    {
      if (Type == type::procedure)
        switch(Proc)
        {
        case proc::mandelbrot:
          return Mand(X, Y);
        default:
          return vec3(0);
        }
      else
        return vec3(0);
    } /* End of 'Get' function */

    /* Set proc texture function.
     * ARGUMENTS:
     *   - const std::string &Name;
     * RETUSNS: 
     *   (BOOL) Success of setting.
     */
    BOOL SetProc( const std::string &Name )
    {
      Type = type::procedure;
      if (Name == "mand")
      {
        Proc = proc::mandelbrot;
        return TRUE;
      }
      else
        return FALSE;
    } /* End of 'Set' function */

    /* Base and default class constructor.
     * ARGUMENTS:
     *   - Type of texture:
     *       const type Type;
     *   - Procedure type:
     *       const proc Proc;
     */
    texture( const proc Proc ) :
      Type(type::procedure),
      Proc(Proc)//, Plane({})
    {
    } /* End of 'material' function */

    /* Default class constructor. */
    texture( VOID ) :
      Type(type::none),
      Proc(Proc)//, Plane({})
    {
    } /* End of 'material' function */

    // /* Base and default class constructor.
    //  * ARGUMENTS:
    //  *   - All possible material fields:
    //  *       const vec3 &Ka, &Kd, &Ks;
    //  *       const DBL Kr, Kt;
    //  */
    // texture( const proc Proc ) :
    //   Ka(Ka), Kd(Kd), Ks(Ks), Kr(Kr), Kt(Kt), Ph(Ph)
    // {
    // } /* End of 'material' function */
  }; /* End of 'material' class */
} /* end of 'acrtx' namespace */

#endif /* __texture_h_ */

  /* END OF 'texture.h' FILE */