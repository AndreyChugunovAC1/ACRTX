/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : object.h
 * PURPOSE     : Raytracing project.
 *               Object module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __object_h_
#define __object_h_

#include "triangle.h"
#include "box.h"
#include "shape_def.h"

/* Projec namespace */
namespace acrtx
{
  /* Thor representation class */
  class object : public shape
  {
  private:
    std::vector<triangle> Prim;
    box Bound;

    /* Vertex structure */
    struct vertex
    {
      vec3 P;
      // vec3 N;
    }; /* End of 'vertex' struct */

    /* Count primitive's normals function.
     * ARGUMENTS: 
     *   - vertex massive:
     *       vertex *V;
     *   - Index massive:
     *       const INT * I;
     *   - number of indexes:
     *       const INT &NoofI;
     */
    // VOID CountNorm( vertex *V, const INT *I, const INT &NoofI )
    // {
    //   INT i;
    // 
    //   for (i = 0; i < NoofI; i += 3)
    //   {
    // 
    //     vec3 Norm = ((V[I[i + 1]].P - V[I[i]].P) % (V[I[i + 2]].P - V[I[i]].P)).Normalize();
    // 
    //     V[I[i + 0]].N = (V[I[i + 0]].N + Norm).Normalize();
    //     V[I[i + 1]].N = (V[I[i + 1]].N + Norm).Normalize();
    //     V[I[i + 2]].N = (V[I[i + 2]].N + Norm).Normalize();
    //   }
    // 
    //   for (i = 0; i < NoofI; i++)
    //     V[I[i]].C = V[I[i]].N;
    // } /* End of 'CountNorm' function. */

  public:
    /* Load object from .obj file function. 
     * ARGUMENTS:
     *   - File name to load:
     *       const std::string &FileName;
     * RETURNS:
     *   (BOOL) success flag;
     */
    BOOL Load( const CHAR *FileName )
    {
      vec3 Min, Max;
      INT
        noofv = 0,
        noofi = 0,
        size;
      FILE *F;
      CHAR Buf[1000];
      INT *Ind;
      vertex *V;

      /* Open file */
      // if (fopen_s(FileName, "r") == NULL)
      //   return false;

      F = fopen(FileName, "r");
      if (F == NULL)
        return FALSE;

      /* Count vertex and index quantities */
      while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
      {
        if (Buf[0] == 'v' && Buf[1] == ' ')
          noofv++;
        else if (Buf[0] == 'f' && Buf[1] == ' ')
          noofi++;
      }

      // Memory bulk!
      size = sizeof(vertex) * noofv + sizeof(INT) * (noofi *= 3);
      if ((V = (vertex *)malloc(size)) == NULL)
      {
        fclose(F);
        return FALSE;
      }
      Ind = (INT *)(V + noofv);

      /* Read vertices and facets data */
      rewind(F);
      INT Nv = noofv, Ni = noofi;
      noofv = noofi = 0;
      while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
      {
        if (Buf[0] == 'v' && Buf[1] == ' ')
        {
          DBL x, y, z;

          sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);
          V[noofv++].P = vec3(x, y, z);
        }
        else if (Buf[0] == 'f' && Buf[1] == ' ')
        {
          INT n1, n2, n3;

          /* Read one of possible facet references */
          sscanf(Buf + 2, "%d/%*d/%*d %d/%*d/%*d %d/%*d/%*d", &n1, &n2, &n3) == 3 ||
            sscanf(Buf + 2, "%d//%*d %d//%*d %d//%*d", &n1, &n2, &n3) == 3 ||
            sscanf(Buf + 2, "%d/%*d %d/%*d %d/%*d", &n1, &n2, &n3) == 3 ||
            sscanf(Buf + 2, "%d %d %d", &n1, &n2, &n3);
          n1--;
          n2--;
          n3--;
          Ind[noofi++] = n1;
          Ind[noofi++] = n2;
          Ind[noofi++] = n3;
        }
      }

      for (INT i = 0; i < Ni; i += 3)
        Prim.push_back(triangle(V[Ind[i]].P, V[Ind[i + 1]].P, V[Ind[i + 2]].P));
      if (noofv > 0)
        Min = Max = V[0].P;
      for (INT i = 1; i < Nv; i++)
      {
        Min.X = min(Min.X, V[i].P.X);
        Min.Y = min(Min.Y, V[i].P.Y);
        Min.Z = min(Min.Z, V[i].P.Z);
        Max.X = max(Max.X, V[i].P.X);
        Max.Y = max(Max.Y, V[i].P.Y);
        Max.Z = max(Max.Z, V[i].P.Z);
      }
      Bound = box(Min, Max);
      /* making an auto normalize */
      // CountNorm(V, Ind, noofi);
      /* create primitive */
      // Create(V, noofv, Ind, noofi);

      free(V);
      fclose(F);
      return TRUE;
    } /* End of 'Load' function */

    /* Base class constructor.
     * ARGUMENTS:
     *   - File name to load:
     *       const std::string &FileName;
     *   - Materiaql pointer:
     *       material * const Mtl;
     *   - Environment pointer:
     *       envi * const Envi;
     *   - Texture:
     *       texture * const Tex;
     */
    object( const std::string &FileName,
            material * const Mtl = nullptr,
            envi * const Envi = nullptr,
            texture * const Tex = nullptr) : 
      shape(Mtl, Envi, Tex)
    {
      if (!Load(FileName.c_str()))
        error::msg(error::other,
                   "Can not load object from " + FileName + " File.");
    } /* End of 'triangle' function */

    /* Base class constructor.
     * ARGUMENTS:
     *   - material:
     *       material * const Mtl;
     *   - environment:
     *        envi * const Envi;
     *   - texture:
     *        texture * const Tex;
     */
    object( material * const Mtl = nullptr,
            envi * const Envi  = nullptr,
            texture * const Tex = nullptr) : 
      shape(Mtl, Envi, Tex)
    {
    } /* End of 'triangle' function */

    /* Template intersection function.
     * ARGUMENTS:
     *   - ray to intersect with:
     *       const ray &R;
     *   - intersect info variable:
     *       intr *I;
     * RETURNS:
     *   (BOOL) True, if intersection happened,
     *     False overwise;
     */
    BOOL Intersect( const ray &R, inter * const I ) const final
    {
      if (!Bound.IsIntersect(R))
        return FALSE;
      inter Res, Tmp;
      BOOL InterFlag = FALSE;

      Res.T = _HUGE;
      for (INT i = 0; (UINT)i < Prim.size(); i++)
        if (Prim[i].Intersect(R, &Tmp)/* && Tmp.T > 0*/ && Tmp.T < Res.T)
        {
          Res.Extra = i;
          Res = Tmp;
          InterFlag = TRUE;
        }
      // I->Sh = this;
      *I = Res;
      I->Sh = this;
      return InterFlag;
    } /* End of 'Intersect' function */

    /* Virtual intersection flag function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    BOOL IsIntersect( const ray &R ) const final
    {
      if (!Bound.IsIntersect(R))
        return FALSE;
      for (auto &i : Prim)
        if (i.IsIntersect(R))
          return TRUE;
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
    VOID GetAdvInfo( const ray &R, inter * const I ) const final
    {
      Prim[I->Extra].GetAdvInfo(R, I);
      // I->IsIn = ((I->N & R.Dir) > 0);
    } /* End of 'GetAdvInfo' function */
  }; /* End of 'triangle' class */
} /* end of 'acrtx' namespace */

#endif /* __thor_h_ */

/* END OF 'thor.h' FILE */
