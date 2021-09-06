/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : shape.cpp
 * PURPOSE     : Raytracing project.
 *               Shape coustructors realization.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
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
    Envi(raytracer::Get().Environments.Get("DEFAULT")),
    Tex(raytracer::Get().Textures.Get("DEFAULT"))
  {
  } /* End of 'shape' function */

  /* Base class constructor.
    * ARGUMENTS:
    *   - Material: 
    *       material * const NMtl;
    *   - Envirobment:
    *       envi * const NEnvi;
    */
  shape::shape( material * const NMtl, envi * const NEnvi, texture * const NTex )
  {
    Mtl =
      NMtl == nullptr ? raytracer::Get().Materials.Get("DEFAULT") : NMtl;
    Envi = 
      NEnvi == nullptr ? raytracer::Get().Environments.Get("DEFAULT") : NEnvi;
    Tex  =
      NTex == nullptr ? raytracer::Get().Textures.Get("DEFAULT") : NTex;
  } /* End of 'shape' function */
} /* end of 'acrtx' namespace */

/* END OF 'shape.cpp' FILE */