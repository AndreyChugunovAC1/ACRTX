/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : ray.h
 * PURPOSE     : Raytracing project.
 *               Frame module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */


#ifndef __ray_h_
#define __ray_h_

#include "math_def.h"
#include "vec3.h"

/* Math namespace */
namespace mth
{
  /* Ray representation class */
  template<typename Type>
    class ray
    {
    public:
      vec3<Type> Org, // Ray start position
        Dir;          // Ray direction vector

      /* Base class constructor 
       * ARGUMENTS:
       *   - Ray start position:
       *       const vec3<Type> &Org;
       *   - Ray direction vector:
       *       const vec3<Type> &Dir;
       */
      ray( const vec3<Type> &Org = vec3<Type>(0), 
           const vec3<Type> &Dir = vec3<Type>(0, 0, -1) ) :
        Org(Org), Dir(Dir.Normalize())
      {
      } /* End of 'ray' function */ 

      /* Get point on ray by coeficent function.
       * ARGUMENTS:
       *   - Coeficent on ray:
       *       const Type T;
       * RETURNS:
       *   (vec3<Type>) point on vector;
       */
      vec3<Type> operator()( const Type T ) const
      {
        return Org + Dir * T;
      } /* End of 'operator()' function */
    }; /* End of 'ray' class */
} /* end of 'acmath' namespace */

#endif /* __ray_h_ */

/* END OF 'ray.h' FILE */