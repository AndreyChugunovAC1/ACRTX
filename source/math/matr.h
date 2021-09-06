/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : matr.h
 * PURPOSE     : Raytracing project.
 *               Frame module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 * NOTE        : Module namespace 'mth'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */


#ifndef __matr_h_
#define __matr_h_

#include "math_def.h"
#include "vec3.h"

/* Math namespace */
namespace mth
{
  /* Matrix 4x4 class */
  template<typename Type>
    class matr
    {
    private:
      Type M[4][4] {};  // Matix plane
      // friend class accam;

    public:
      /* Default class constructor. */
      matr( VOID )
      {
      } /* End of 'matr' function */

      /* Base class constructor
       * ARGUMENTS:
       *   - All matrix cells:
       *       const Type
       *         A00, A01, ...,
       *         A10, A11, ...,
       *         ...
       */
      matr( const Type A00, const Type A01, const Type A02, const Type A03,
            const Type A10, const Type A11, const Type A12, const Type A13,
            const Type A20, const Type A21, const Type A22, const Type A23,
            const Type A30, const Type A31, const Type A32, const Type A33 )
      {
        M[0][0] = A00;
        M[0][1] = A01;
        M[0][2] = A02;
        M[0][3] = A03;
        M[1][0] = A10;
        M[1][1] = A11;
        M[1][2] = A12;
        M[1][3] = A13;
        M[2][0] = A20;
        M[2][1] = A21;
        M[2][2] = A22;
        M[2][3] = A23;
        M[3][0] = A30;
        M[3][1] = A31;
        M[3][2] = A32;
        M[3][3] = A33;
      } /* End of 'matr' function */

      /* Matrix multiplication function.
       * ARGUMENTS:
       *   - Second matrix to multiply:
       *       const matr<Type> &M;
       * RETURNS:
       *   (matr<Type>) result matrix;
       */
      matr<Type> operator*( const matr<Type> &M2 ) const
      {
        return
          matr<Type>(
            M[0][0] * M2.M[0][0] + M[0][1] * M2.M[1][0] + M[0][2] * M2.M[2][0] + M[0][3] * M2.M[3][0],
            M[0][0] * M2.M[0][1] + M[0][1] * M2.M[1][1] + M[0][2] * M2.M[2][1] + M[0][3] * M2.M[3][1],
            M[0][0] * M2.M[0][2] + M[0][1] * M2.M[1][2] + M[0][2] * M2.M[2][2] + M[0][3] * M2.M[3][2],
            M[0][0] * M2.M[0][3] + M[0][1] * M2.M[1][3] + M[0][2] * M2.M[2][3] + M[0][3] * M2.M[3][3],

            M[1][0] * M2.M[0][0] + M[1][1] * M2.M[1][0] + M[1][2] * M2.M[2][0] + M[1][3] * M2.M[3][0],
            M[1][0] * M2.M[0][1] + M[1][1] * M2.M[1][1] + M[1][2] * M2.M[2][1] + M[1][3] * M2.M[3][1],
            M[1][0] * M2.M[0][2] + M[1][1] * M2.M[1][2] + M[1][2] * M2.M[2][2] + M[1][3] * M2.M[3][2],
            M[1][0] * M2.M[0][3] + M[1][1] * M2.M[1][3] + M[1][2] * M2.M[2][3] + M[1][3] * M2.M[3][3],

            M[2][0] * M2.M[0][0] + M[2][1] * M2.M[1][0] + M[2][2] * M2.M[2][0] + M[2][3] * M2.M[3][0],
            M[2][0] * M2.M[0][1] + M[2][1] * M2.M[1][1] + M[2][2] * M2.M[2][1] + M[2][3] * M2.M[3][1],
            M[2][0] * M2.M[0][2] + M[2][1] * M2.M[1][2] + M[2][2] * M2.M[2][2] + M[2][3] * M2.M[3][2],
            M[2][0] * M2.M[0][3] + M[2][1] * M2.M[1][3] + M[2][2] * M2.M[2][3] + M[2][3] * M2.M[3][3],

            M[3][0] * M2.M[0][0] + M[3][1] * M2.M[1][0] + M[3][2] * M2.M[2][0] + M[3][3] * M2.M[3][0],
            M[3][0] * M2.M[0][1] + M[3][1] * M2.M[1][1] + M[3][2] * M2.M[2][1] + M[3][3] * M2.M[3][1],
            M[3][0] * M2.M[0][2] + M[3][1] * M2.M[1][2] + M[3][2] * M2.M[2][2] + M[3][3] * M2.M[3][2],
            M[3][0] * M2.M[0][3] + M[3][1] * M2.M[1][3] + M[3][2] * M2.M[2][3] + M[3][3] * M2.M[3][3]
            );
      } /* End of 'operator*' function */

      /* Create rotate around axis x matrix function.
       * ARGUMENTS:
       *   - Angle of rotation in degrees:
       *       const Type Angle;
       * RETURNS:
       *   (matr<Type>) created matrix;
       */
      static matr<Type> RotateX( Type Angle )
      {
        Type c, s;

        Angle = D2R(Angle);
        __asm {
          fninit;
          fld qword ptr Angle;
          fsincos;
          fstp qword ptr c;
          fst qword ptr s;
        }
        return 
          matr<Type>(
            1,  0, 0, 0,
            0,  c, s, 0,
            0, -s, c, 0,
            0,  0, 0, 1
            );
      } /* End of 'RotateX' function */

      /* Create rotate around axis y matrix function.
       * ARGUMENTS:
       *   - Angle of rotation in degrees:
       *       const Type Angle;
       * RETURNS:
       *   (matr<Type>) created matrix;
       */
      static matr<Type> RotateY( Type Angle )
      {
        Type c, s;

        Angle = D2R(Angle);
        __asm {
          fninit;
          fld qword ptr Angle;
          fsincos;
          fstp qword ptr c;
          fst qword ptr s;
        }
        return 
          matr<Type>(
             c, 0, s, 0,
             0, 1, 0, 0,
            -s, 0, c, 0,
             0, 0, 0, 1
            );
      } /* End of 'RotateY' function */

      /* Create rotate around axis z matrix function.
       * ARGUMENTS:
       *   - Angle of rotation in degrees:
       *       const Type Angle;
       * RETURNS:
       *   (matr<Type>) created matrix;
       */
      static matr<Type> RotateZ( Type Angle )
      {
        Type c, s;

        Angle = D2R(Angle);
        __asm {
          fninit;
          fld qword ptr Angle;
          fsincos;
          fstp qword ptr c;
          fst qword ptr s;
        }
        return 
          matr<Type>(
             c, s, 0, 0,
            -s, c, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1
            );
      } /* End of 'RotateZ' function */

      /* Create translate matrix function.
       * ARGUMENTS:
       *   - Vector of translation:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (matr<Type>) created matrix;
       */
      static matr<Type> Translate( const vec3<Type> &V )
      {
        return 
          matr<Type>(
              1,   0,   0, 0,
              0,   1,   0, 0,
              0,   0,   1, 0,
            V.X, V.Y, V.Z, 1
            );
      } /* End of 'RotateX' function */

      /* Transform vector function.
       * ARGUMENTS:
       *   - Vector to transform:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) tranformed vector;
       */
      vec3<Type> TransformVec( const vec3<Type> &V ) const
      {
        return vec3<Type>(
          V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0],
          V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1],
          V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2]
          );
      } /* End of 'TransformVec' function */

      /* Matr rotate around vector create function.
       * ARGUMENTS:
       *   - vector of rotation:
       *       const vec3<Type> &V;
       *   - angle of rotation:
       *       Type A;
       * RETURNS:
       *   (matr<Type>) result matrix;
       */
      static matr<Type> RotateVec( const vec3<Type> &V, Type A )
      {
        A = D2R(A);
        DBL c = cos(A), s = sin(A);

        return 
          matr<Type>(      c + V.X * V.X * (1 - c),   V.X * V.Y * (1 - c) + V.Z * s,   V.X * V.Z * (1 - c) - V.Y * s,   0,  
                     V.Y * V.X * (1 - c) - V.Z * s,         c + V.Y * V.Y * (1 - c),   V.Y * V.Z * (1 - c) + V.X * s,   0,
                     V.Z * V.X * (1 - c) + V.Y * s,   V.Z * V.Y * (1 - c) - V.X * s,   c + V.Z * V.Z * (1 - c)      ,   0,
                                                 0,                               0,                               0,   1);
      } /* End of 'RotateVec' function */

      /* Matr NDC create function.
       * ARGUMENTS:
       *   - new basis, and it's position:
       *       const vec3 & Loc, Dir, Up, Right;
       * RETURNS:
       *   (matr<Type>) result matrix;
       */
      static matr<Type> NDC( const vec3<Type> &L, const vec3<Type> &Dir, 
                             const vec3<Type> &Up,  const vec3<Type> &Right )
      {
        vec3 D = Dir.Normalize(),
             R = Right.Normalize(),
             U = Up.Normalize();
        return 
          matr<Type>(R.X,      U.X,      -D.X,  0,
                     R.Y,      U.Y,      -D.Y,  0,
                     R.Z,      U.Z,      -D.Z,  0,
                     -(L & R), -(L & U), L & D, 1);
      } /* End of 'NDC' function */

      /* Transform point function.
       * ARGUMENTS:
       *   - Vector-point to transform:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) tranformed vector-point;
       */
      vec3<Type> TransformPoint( const vec3<Type> &V ) const
      {
        return vec3<Type>(
          V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0],
          V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1],
          V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]
          );
      } /* End of 'TransformPoint' function */
    }; /* End of 'matr' class */
} /* end of 'acmath' namespace */

#endif /* __matr_h_ */

/* END OF 'matr.h' FILE */