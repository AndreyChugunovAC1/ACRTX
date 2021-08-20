/* NAME          : ray.h
 * PURPOSE       : Math ray module file.
 * CREATION DATE : 07.08.2021
 * LAST UPDATE   : 11.08.2021
 */

#ifndef __ray_h_
#define __ray_h_

#include "acmath_def.h"
#include "vec3.h"

/* Math namespace */
namespace acmath
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