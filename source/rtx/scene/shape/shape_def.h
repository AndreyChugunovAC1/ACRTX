/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : shape_def.h
 * PURPOSE     : Raytracing project.
 *               Shape module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
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
    texture *Tex;  // Texture for shape

    /* Default class constructor */
    shape( VOID );

    /* Base class constructor.
     * ARGUMENTS:
     *   - Material: 
     *       material * const NMtl;
     *   - Envirobment:
     *       envi * const NEnvi;
     */
    shape( material * const NMtl, envi * const NEnvi, texture * const NTex);
      
    /* Virtual intersection with shape function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     *   - Intersection information:
     *       inter *I;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    virtual BOOL Intersect( const ray &R, inter * const I ) const = 0;
    // {
    //   return FALSE;
    // } /* End of 'Intersect' function */

    /* Virtual intersection flag function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    virtual BOOL IsIntersect( const ray &R ) const = 0;
    // {
    //   return FALSE;
    // } /* End of 'IsIntersect' function */

    /* Get advanced intersection info about object function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     *   - Intersection information:
     *       inter *I;
     * RETURNS: None.
     */
    virtual VOID GetAdvInfo( const ray &R, inter * const I ) const = 0;

    /* Get texture color function. (means get with spec. coords) 
     * ARGUMENTS:
     *   - Point on object:
     *       const vec3 &P;
     * RETURNS:
     *   (vec3) Color;
     */
    virtual vec3 GetTex( const vec3 &P ) const
    {
      return vec3(0);
    } /* End of 'Color' function */
    // {
    // } /* End of 'GetAdvInfo' function */
  }; /* End of 'shape' class */ 
} /* end of 'acrtx' namespace */

#endif /* __shape_def_h_ */

/* END OF 'shape_def.h' FILE */