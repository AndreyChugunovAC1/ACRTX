/* NAME          : light_def.h
 * PURPOSE       : Light base module file.
 * CREATION DATE : 09.08.2021
 * LAST UPDATE   : 11.08.2021
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