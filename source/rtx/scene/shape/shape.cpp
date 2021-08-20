/* NAME          : shape.cpp
 * PURPOSE       : Shape base module file.
 * CREATION DATE : 12.08.2021
 * LAST UPDATE   : 12.08.2021
 */

#include "shape.h"
// Main rtx class for using stocks
#include "../../raytracer.h"
#include "../resources/resources.h"
#include "../../../parser/parser.h"

/* Project namespace */
namespace acrtx
{
  /* Default class constructor */
  shape::shape( VOID ) :
    Mtl(raytracer::Get().Materials.Get("DEFAULT")), 
    Envi(raytracer::Get().Environments.Get("DEFAULT"))
  {
  } /* End of 'shape' function */

  /* Base class constructor.
    * ARGUMENTS:
    *   - Material: 
    *       material * const NMtl;
    *   - Envirobment:
    *       envi * const NEnvi;
    */
  shape::shape( material * const NMtl, envi * const NEnvi )
  {
    Mtl =
      NMtl == nullptr ? raytracer::Get().Materials.Get("DEFAULT") : NMtl;
    Envi = 
      NEnvi == nullptr ? raytracer::Get().Environments.Get("DEFAULT") : NEnvi;
  } /* End of 'shape' function */
} /* end of 'acrtx' namespace */

/* END OF 'shape.cpp' FILE */