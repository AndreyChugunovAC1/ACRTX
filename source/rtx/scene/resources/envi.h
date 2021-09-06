/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : envi.h
 * PURPOSE     : Raytracing project.
 *               Light module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
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
    // friend class scene;
    // friend class parser;
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