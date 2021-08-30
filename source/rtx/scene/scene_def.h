/* NAME          : scene_def.h
 * PURPOSE       : Scene base module file.
 * CREATION DATE : 13.08.2021
 * LAST UPDATE   : 13.08.2021
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