/* NAME          : envi.h
 * PURPOSE       : Environment module file.
 * CREATION DATE : 09.08.2021
 * LAST UPDATE   : 11.08.2021
 */

#ifndef __envi_h_
#define __envi_h_

#include "../../../def.h"

/* Project namespace */
namespace acrtx
{
  /* Enviroment representation class */
  class envi
  {
  private:
    friend class scene;
    friend class parser;
    DBL RefK, // Refraction koeficent
      DecK,   // Decay coeficent
      N;      // Refraction angle coeficent

  public:
    /*Base air environment function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (envi) Base air environment;
     */
    static envi Air( VOID )
    {
      return envi();
    } /* End of 'Air' function */

    /* Base and default class constructor.
     * ARGUMENTS:
     *   - All possible envi fields:
     *       const DBL RefK, DecK, N;
     */
    envi( const DBL N = 1.0,
          const DBL RefK = 0, 
          const DBL DecK = 0 ) :
      RefK(RefK), DecK(DecK), N(N)
    {
    } /* End of 'envi' function */

    /* Class destructor */
    ~envi( VOID )
    {
    } /* End of '~envi' function */
  }; /* End of 'envi' class */
} /* end of 'acrtx' namespace */

#endif /* __envi_h_ */

/* END OF 'envi.h' FILE */