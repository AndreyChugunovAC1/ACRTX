/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : material.h
 * PURPOSE     : Raytracing project.
 *               Material module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __material_h_
#define __material_h_

#include "../../../def.h"

/* Project namespace */
namespace acrtx
{
  /* Matrerial representation class */
  class material
  {
  private:
    // friend class parser;
    // friend class scene;
    vec3 Ka, // Ambient coeficent
      Kd,    // Diffuze coeficent
      Ks;    // Spectral coeficent
    DBL Ph,  // Phong koeficent
      Kr,    // Reflection coeficent
      Kt;    // Refraction coeficent

  public:
    /* Base and default class constructor.
     * ARGUMENTS:
     *   - All possible material fields:
     *       const vec3 &Ka, &Kd, &Ks;
     *       const DBL Kr, Kt;
     */
    material( const vec3 &Ka = vec3(0.4, 0.2, 0.9), 
              const vec3 &Kd = vec3(0.5, 0.1, 0.8), 
              const vec3 &Ks = vec3(0.2, 0.3, 0.7),
              const DBL Ph = 1.0,
              const DBL Kr = 0.3, 
              const DBL Kt = 0.1) :
      Ka(Ka), Kd(Kd), Ks(Ks), Kr(Kr), Kt(Kt), Ph(Ph)
    {
    } /* End of 'material' function */

    /* Class destructor */
    ~material( VOID )
    {
    } /* End of '~material' function */

    ///* Get material field by string function.
    // * ARGUMENTS:
    // *   - Name of field:
    // *       const std::string &Field;
    // * RETURNS:
    // *   (VOID *) pointer to field;
    // */
    //VOID * operator[]( const std::string &Field )
    //{
    //  if (Field == "Ka")
    //    return &Ka;
    //  if (Field == "Kd")
    //    return &Kd;
    //  if (Field == "Ks")
    //    return &Ks;
    //  if (Field == "Ph")
    //    return &Ph;
    //  if (Field == "Kr")
    //    return &Kr;
    //  if (Field == "Kt")
    //    return &Kt;
    //  return nullptr;
    //} /* End of 'operator[]' function */
  }; /* End of 'material' class */
} /* end of 'acrtx' namespace */

#endif /* __material_h_ */

  /* END OF 'material.h' FILE */