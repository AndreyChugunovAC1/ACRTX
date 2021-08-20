/* NAME          : shape_def.h
 * PURPOSE       : Shape module file.
 * CREATION DATE : 08.08.2021
 * LAST UPDATE   : 09.08.2021
 */

#ifndef __shape_def_h_
#define __shape_def_h_

#include "../../scene/scene_def.h"
#include "../resources/resources.h"

/* Project namespace */
namespace acrtx
{
  /* Shape representation class */
  class shape
  {
  public:
    material *Mtl; // Shape's material
    envi *Envi;    // Material Refraction, reflection params

    /* Default class constructor */
    shape( VOID );

    /* Base class constructor.
     * ARGUMENTS:
     *   - Material: 
     *       material * const NMtl;
     *   - Envirobment:
     *       envi * const NEnvi;
     */
    shape( material * const NMtl, envi * const NEnvi );
      
    /* Virtual intersection with shape function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     *   - Intersection information:
     *       inter *I;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    virtual BOOL Intersect( const ray &R, inter * const I ) const
    {
      return FALSE;
    } /* End of 'Intersect' function */

    /* Virtual intersection flag function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    virtual BOOL IsIntersect( const ray &R ) const
    {
      return FALSE;
    } /* End of 'IsIntersect' function */

    /* Get advanced intersection info about object function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     *   - Intersection information:
     *       inter *I;
     * RETURNS: None.
     */
    virtual VOID GetAdvInfo( const ray &R, inter * const I ) const
    {
    } /* End of 'GetAdvInfo' function */
  }; /* End of 'shape' class */ 
} /* end of 'acrtx' namespace */

#endif /* __shape_def_h_ */

/* END OF 'shape_def.h' FILE */