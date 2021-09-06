/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : thor.h
 * PURPOSE     : Raytracing project.
 *               Shape module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __thor_h_
#define __thor_h_

#include "shape_def.h"

/* Evaluator class */
class evaluator
{
public:
  /* Is zero (with fault) function. 
   * ARGUMENTS: 
   *   - Number:
   *       DBL A;
   * RETURNS:
   *   (BOOL) result;
   */
  static BOOL ISZERO( DBL A ) 
  {
    return abs(A) < 0.0001;
  } /* End of 'ISZERO' function */

  /* Is less than zero (with fault) function. 
   * ARGUMENTS: 
   *   - Number:
   *       DBL A;
   * RETURNS:
   *   (BOOL) result;
   */
  static BOOL LZERO( DBL A ) 
  {
    return A < -0.0001;
  } /* End of 'LZERO' function */

  /* Is less than zero (with fault) function. 
   * ARGUMENTS: 
   *   - Number:
   *       DBL A;
   * RETURNS:
   *   (BOOL) result;
   */
  static BOOL UZERO( DBL A ) 
  {
    return A > 0.0001;
  } /* End of 'UZERO' function */

  ///* Complex number structire */
  //struct cmpl
  //{
  //  DBL Re, Im;

  //  /* Default class constructor */
  //  cmpl( VOID ) :
  //    Re(0), Im(0)
  //  {
  //  } /* End of 'cmpl' function */
  //                  
  //  /* Base class constructor */
  //  cmpl( const DBL Re, const DBL Im = 0 ) :
  //    Re(Re), Im(Im)
  //  {
  //  } /* End of 'cmpl' function */

  //  /* Complex number module.
  //   * ARGUMENTS: None.
  //   * RETURNS: 
  //   *   (DBL) Arg;
  //   */
  //  DBL arg( VOID )
  //  {
  //    return atan2(Im, Re);
  //  } /* End of 'arg' function */

  //  /* Complex number module.
  //   * ARGUMENTS: None.
  //   * RETURNS: 
  //   *   (DBL) Mod;
  //   */
  //  DBL mod( VOID )
  //  {
  //    return sqrt(Re * Re + Im * Im);
  //  } /* End of 'mod' function */

  //  /* Complex square root function.
  //   * ARGUMENTS: None.
  //   * RETURNS: 
  //   *   (cmpl) Root;
  //   */
  //  cmpl root( DBL NS, const INT I = 0 ) 
  //  {
  //    if (NS == 0)
  //      NS = 1;
  //    DBL N = pow(mod(), 1 / NS),
  //      A = (arg() + I * (2.0 * 3.14159265)) / NS;

  //    return cmpl((FLOAT)(N * cos(A)), (FLOAT)(N * sin(A)));
  //  } /* End of 'sqrt' function */

  //  /* Complex sum function.
  //   * ARGUMENTS: None.
  //   * RETURNS: 
  //   *   (cmpl) Sum;
  //   */
  //  cmpl operator+( const cmpl& A )
  //  {
  //    return cmpl(Re + A.Re, Im + A.Im);
  //  } /* End of 'operator+' function */

  //  /* Complex sum function.
  //   * ARGUMENTS: None.
  //   * RETURNS: 
  //   *   (cmpl) Sum;
  //   */
  //  cmpl operator-( const cmpl& A )
  //  {
  //    return cmpl(Re - A.Re, Im - A.Im);
  //  } /* End of 'operator-' function */

  //  /* Complex sum function.
  //   * ARGUMENTS: None.
  //   * RETURNS: 
  //   *   (cmpl) Sum;
  //   */
  //  cmpl operator-( VOID )
  //  {
  //    return cmpl(-Re, -Im);
  //  } /* End of 'operator+' function */

  //  /* Complex div function.
  //   * ARGUMENTS: None.
  //   * RETURNS: 
  //   *   (cmpl) Sum;
  //   */
  //  cmpl operator/( const DBL D )
  //  {
  //    if (D == 0)
  //      return cmpl();
  //    return cmpl(Re / D, Im / D);
  //  } /* End of 'operator+' function */

  //  /* Complex sum function.
  //   * ARGUMENTS: None.
  //   * RETURNS: 
  //   *   (cmpl) Sum;
  //   */
  //  cmpl operator/( const cmpl& B )
  //  {
  //    DBL X = B.Re * B.Re + B.Im * B.Im;

  //    return 
  //      cmpl((Re * B.Re + Im * B.Im) / X, (Im * B.Re - Re * B.Im) / X);
  //  } /* End of 'operator+' function */

  //  /* Operator print to stream functiuon.
  //   * ARGUMENTS:
  //   *   - Out stream:
  //   *       std::ostream &Stream;
  //   * REETURNS:
  //   *   (std::ostream &) reference to this stream;
  //   */
  //  std::ostream & operator<<( std::ostream &Stream )
  //  {
  //    return std::cout << Re <<  " " << Im;
  //  } /* End of 'operator<<' function */

  //  /* Convert function.
  //   * ARGUMENTS: None.
  //   * RETURNS: 
  //   *   (DBL) Real part;
  //   */
  //  operator DBL( VOID )
  //  {
  //    return Re;  
  //  } /* End of 'operator+' function */
  //}; /* End of 'compl' struct */

  /* Solutions struct */
  struct solutions
  {
    INT NOS {};
    DBL Sols[4] {};

    /* Default (0 solutions) constructor */
    solutions( VOID )
    {
      NOS = 0;
    } /* End of 'solutions' function */

    /* 1-solutions constructor. 
     * ARGUENTS:
     *   - 1 solutioons:
     *       DBL A;
     */
    solutions( DBL A )
    {
      NOS = 1;
      Sols[0] = A;
    } /* End of 'solutions' function */

    /* 2-solutions constructor. 
     * ARGUENTS:
     *   - 2 solutioons:
     *       DBL A, DBL B;
     */
    solutions( DBL A, DBL B )
    {
      NOS = 2;
      Sols[0] = A;
      Sols[1] = B;
    } /* End of 'solutions' function */

    /* 3-solutions constructor. 
     * ARGUENTS:
     *   - 3 solutioons:
     *       DBL A, DBL B, DBL C;
     */
    solutions( DBL A, DBL B, DBL C )
    {
      NOS = 3;
      Sols[0] = A;
      Sols[1] = B;
      Sols[2] = C;
    } /* End of 'solutions' function */

    /* 4-solutions constructor. 
     * ARGUENTS:
     *   - 4 solutioons:
     *       DBL A, DBL B, DBL C, DBL D;
     */
    solutions( DBL A, DBL B, DBL C, DBL D )
    {
      NOS = 4;
      Sols[0] = A;
      Sols[1] = B;
      Sols[2] = C;
      Sols[3] = D;
    } /* End of 'solutions' function */
  }; /* End of 'solutions' struct */

  /* Solve 2-power evaluation function.
   * ARGUMENTS:
   *   - koeficents:
   *       DBL a, DBL b, DBL c, DBL d;
   * RETURNS: 
   *   (solutions) all real solutions;
   */
  static solutions Solve2( const DBL a, const DBL b, const DBL c )
  {
    DBL D = b * b - 4 * a * c;

    if (a == 0)
    {
      if (b == 0)
        return solutions();
      else
        return solutions(-c / b);
    }
    if (D < 0)
      return solutions();
    if (D == 0)
      return solutions(-b / (2 * a));
    D = sqrt(D);
    return solutions((-b + D) / (2 * a), (-b - D) / (2 * a));
  } /* End of 'Solve2' functios */

  /* Solve 4-power evaluation function.
   * ARGUMENTS:
   *   - koeficents:
   *       DBL a, DBL b, DBL c, DBL d;
   * RETURNS: 
   *   (solutions) all real solutions;
   */
  static solutions Solve3( DBL a, DBL b, DBL c, DBL d )
  {
    if (ISZERO(a))
      return Solve2(b, c, d);

    DBL p((3 * a * c - b * b) / (3 * a * a) / 3), 
      q((2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a) / 2);
    DBL D(q * q + p * p * p), Delta = b / (3 * a);
    //////// cmpl Tmp0(cmpl(-(q / 2.0)) + cmpl(D).root(2));

    if (D == 0)
    {
      DBL Cb = cbrt(-q);

      if (q == 0 && p == 0)
        return solutions(-Delta);
      return solutions(2 * Cb - Delta, -Cb - Delta);
    }
    else if (D > 0)
    {
      DBL Sc = sqrt(D);

      return solutions(cbrt(-q + Sc) + cbrt(-q - Sc) - Delta);
    }
    DBL Fi, K = 2 * sqrt(-p),
      Pi = 3.14159265359;

    if (q == 0)
      Fi = Pi / 2;
    else
    {
      Fi = atan(-sqrt(-D) / q);
      if (q > 0)
        Fi += Pi;
    }
    Fi /= 3;
    return solutions(K * cos(Fi) - Delta, 
                     K * cos(Fi + (2 * Pi / 3)) - Delta, 
                     K * cos(Fi + (4 * Pi / 3)) - Delta);
  } /* End of 'Solve3' functios */

  /* Solve 4-power evaluation function.
   * ARGUMENTS:
   *   - koeficents:
   *       DBL a, DBL b, DBL c, DBL d, DBL e;
   * RETURNS: 
   *   (solutions) all real solutions;
   */
  static solutions Solve4( DBL a, DBL b, DBL c, DBL d, DBL e )
  {
    if (a == 0)
      return Solve3(b, c, d, e);
    {
      DBL A = b / a, B = c / a, C = d / a, D = e / a;

      a = A, b = B, c = C, d = D;
    }

    DBL p = b - 3 * a * a / 8,
      q = a * a * a / 8 - a * b / 2  + c,
      r = -3 * a * a * a * a / 256 + a * a * b / 16 - c * a / 4 + d;

    solutions Sol = Solve3(2, -p, -2 * r, r * p - q * q / 4);
    if (Sol.NOS == 0)
      return solutions();
    DBL s = Sol.Sols[0];
    if (2 * s - p <= 0)
      return solutions();
    DBL t1 = sqrt(2 * s - p), t2 = q / (2 * t1);

    INT k = (Sol = Solve2(1, -t1,  t2 + s)).NOS;
    DBL Sols[4];

    for (INT i = 0; i < Sol.NOS; i++)
      Sols[i] = Sol.Sols[i];

    Sol = Solve2(1,  t1, -t2 + s);
    INT Total = k + Sol.NOS;
    DBL Delta = a / 4;
    for (INT i = 0; i < Sol.NOS; i++)
      Sols[i + k] = Sol.Sols[i];
    if (Total == 0)
      return solutions();
    if (Total == 1)
      return solutions(Sols[0] - Delta);
    if (Total == 2)
      return solutions(Sols[0] - Delta, Sols[1] - Delta);
    if (Total == 3)
      return solutions(Sols[0] - Delta, Sols[1] - Delta, Sols[2] - Delta);
    return 
      solutions(Sols[0] - Delta, Sols[1] - Delta, Sols[2] - Delta, Sols[3] - Delta);
  } /* End of 'Solve4' functios */
}; /* End of 'evaluator' class */

/* Projec namespace */
namespace acrtx
{
  /* Thor representation class */
  class thor : public shape
  {
  private:
    friend class parser;
    vec3 N, C;  // Triangle's normal
    DBL R1, R2; // Special value for triangle's plane
    matr NDC;

  public:
    /* Base class constructor.
     * ARGUMENTS:
     *   - All triangles vertexes:
     *       
     */
    thor( material * const Mtl,
          envi * const Envi  = nullptr,
          texture * const Tex = nullptr,
          const DBL R1 = 1, 
          const DBL R2 = 0.3, 
          const vec3 &N = vec3(0, 1, 0), 
          const vec3 &C = vec3(0) ) : 
      shape(Mtl, Envi, Tex),
       R1(R1), R2(R2), N(N.Normalize()), C(C)
    {
      vec3 X = C;
      if (X == vec3(0))
        X = vec3(1, 0, 0);
      vec3 Tmp = N % X;

      NDC = matr::NDC(C, Tmp % N, N, Tmp);
    } /* End of 'triangle' function */

    /* Base class constructor.
     * ARGUMENTS:
     *   - All triangles vertexes:
     *       
     */
    thor( const DBL R1 = 1, 
          const DBL R2 = 0.3, 
          const vec3 &N = vec3(0, 1, 0), 
          const vec3 &C = vec3(0),
          material * const Mtl = nullptr,
          envi * const Envi  = nullptr,
          texture * const Tex = nullptr) : 
      shape(Mtl, Envi, Tex),
       R1(R1), R2(R2), N(N.Normalize()), C(C)
    {
      vec3 X = C;
      if (X == vec3(0))
        X = vec3(1, 0, 0);
      vec3 Tmp = N % X;

      NDC = matr::NDC(C, Tmp % N, N, Tmp);
    } /* End of 'triangle' function */

    /* Extra thor ray transform function.
     * ARGUMENTS: 
     *   - ray to transform:
     *       const vec3 &V;
     * RETURNS:
     *   (ray) Transformed ray;
     */
    ray Extra( const ray &V )// , const vec3 &N )
    {
      vec3 X, Y, a = V.Org - C;
      vec3 R = (a % N).Normalize(),
        D = (N % R).Normalize();
      X = vec3(a & D, a & N, 0);
      a = a + V.Dir;
      Y = vec3(a & D, a & N, a & R);
      Y = Y - X;
      return ray(X, Y);
    } /* End of 'Extra' function */

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
      ray Tmp = ray(NDC.TransformPoint(R.Org), NDC.TransformVec(R.Dir));

      DBL R0 = R1 * R1 - R2 * R2;
      DBL a = Tmp.Org.Length2(),
          c = 1,
          b = 2 * (Tmp.Org & Tmp.Dir);

       evaluator::solutions AllT = 
         evaluator::Solve4(
           c * c,
           2 * b * c,
           b * b + 2 * a * c + 2 * c * R0 - 4 * R1 * R1 * Tmp.Dir.X * Tmp.Dir.X - 4 * R1 * R1 * Tmp.Dir.Z * Tmp.Dir.Z,
           2 * a * b + 2 * b * R0 - 8 * R1 * R1 * (Tmp.Dir.X * Tmp.Org.X + Tmp.Dir.Z * Tmp.Org.Z),
           a * a + R0 * R0 + 2 * a * R0 - 4 * R1 * R1 * (Tmp.Org.X * Tmp.Org.X + Tmp.Org.Z * Tmp.Org.Z)
         );
       if (AllT.NOS == 0)
         return FALSE;
       I->T = -1;
       INT i = 0;

       for (i = 0; I->T == -1; i++)
         if (AllT.Sols[i] > 0)
           I->T = AllT.Sols[i];

       for (; i < AllT.NOS; i++)
         if (AllT.Sols[i] > 0 && AllT.Sols[i] < I->T)
           I->T = AllT.Sols[i];
       if (I->T != -1)
       {
         // if (I->T < 0)
         //   std::cout << "AAAAA\n";
         I->Sh = this;
         return TRUE;
       }
       return FALSE;
    } /* End of 'Intersection' function */

    /* Virtual intersection flag function.
     * ARGUMENTS:
     *   - Ray to intersect with:
     *       const ray &R;
     * RETURNS:
     *   (BOOL) Is intersection flag;
     */
    BOOL IsIntersect( const ray &R ) const final
    {
      ray Tmp = ray(NDC.TransformPoint(R.Org), NDC.TransformVec(R.Dir));

      DBL R0 = R1 * R1 - R2 * R2;
      DBL a = Tmp.Org.Length2(),
          c = Tmp.Dir.Length2(),
          b = 2 * (Tmp.Org & Tmp.Dir);

       evaluator::solutions AllT = 
         evaluator::Solve4(
           c * c,
           2 * b * c,
           b * b + 2 * a * c + 2 * c * R0 - 4 * R1 * R1 * Tmp.Dir.X * Tmp.Dir.X - 4 * R1 * R1 * Tmp.Dir.Z * Tmp.Dir.Z,
           2 * a * b + 2 * b * R0 - 8 * R1 * R1 * (Tmp.Dir.X * Tmp.Org.X + Tmp.Dir.Z * Tmp.Org.Z),
           a * a + R0 * R0 + 2 * a * R0 - 4 * R1 * R1 * (Tmp.Org.X * Tmp.Org.X + Tmp.Org.Z * Tmp.Org.Z)
         );
       if (AllT.NOS == 0)
         return FALSE;

       for (INT i = 0; i < AllT.NOS; i++)
         if (AllT.Sols[i] > 0)
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
      I->P = R(I->T);
      vec3 a = I->P - C,
        d = (N % (a % N)).Normalize() * R1;

      I->N = (a - d).Normalize();
      a = R.Org - C;
      d = (N % (a % N)).Normalize() * R1;

      I->IsIn = (a - d).Length2() < R2 * R2;
    } /* End of 'GetAdvInfo' function */
  }; /* End of 'triangle' class */
} /* end of 'acrtx' namespace */

#endif /* __thor_h_ */

/* END OF 'thor.h' FILE */
