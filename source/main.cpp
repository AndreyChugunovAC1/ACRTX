/* NAME          : main.cpp
 * PURPOSE       : Main program file.
 * CREATION DATE : 06.08.2021
 * LAST UPDATE   : 11.08.2021
 */

#include "rtx\raytracer.h"

// Single tone declaration
acrtx::raytracer acrtx::raytracer::Instance;

/* Main program function.
 * ARGUMENTS: 
 *   - Number of console arguments:
 *       INT ArgC;
 *   - String console arguments:
 *       CHAR *ArgV[].
 * RETURNS: None.
 */
INT main( INT ArgC, CHAR *ArgV[] )
{
  using namespace acrtx;

  raytracer & R = raytracer::Get();
  // Library:
  R.Materials.Add("MBlue", 
    material(
        vec3(0.08, 0.03, 0.19), 
        vec3(0.08, 0.04, 0.19), 
        vec3(0.06, 0.02, 0.18), 
        10, 0.6, 0.0
      ));
  R.Materials.Add("NMRed", 
    material(
        vec3(0.19, 0.04, 0.03), 
        vec3(0.18, 0.03, 0.04), 
        vec3(0.15, 0.04, 0.06), 
        10, 0.4, 0.2
      ));
  R.Materials.Add("NMGreen", 
    material(
        vec3(0.03, 0.19, 0.03), 
        vec3(0.04, 0.13, 0.04), 
        vec3(0.05, 0.14, 0.06), 
        10, 0.0, 0.0
      ));
  R.Environments.Add("Normal",
    envi());
  R.Thors.Add("Thor1",
    thor(R.Materials.Get("NMRed"), R.Environments.Get("DEFAULT"), R.Textures.Get("DEFAULT"), 2, 2.6, vec3(1), vec3(0, 3, 0)));
  R.Planes.Add("Floor",
    plane(R.Materials.Get("MBlue")));
  R.LightPoints.Add("L1",
    light_point(vec3(3, 5, 7) * 2, vec3(0.4, 0.5, 0.3)));
  R.LightPoints.Add("L3",
    light_point(vec3(-3, 5, -4) * 4, vec3(0.8, 0.3, 0.1)));
  R.LightPoints.Add("L2",
    light_point(vec3(-3, 5, 2) * 4, vec3(0.2, 0.1, 0.5)));
  R.Spheres.Add("S1", sphere(vec3(2, 4, 1), 2, R.Materials.Get("NMGreen")));
  // Settings
  R.Resize(1200, 1200);
  R.GetCamera().SetLocAt(vec3(15, 8, 15), vec3(0, 0, 0));

  // Scene setting
  R.ChooseScene("AC1");
  R.Add(R.Thors.Get("Thor1"));
  R.Add(R.Planes.Get("Floor"));
  R.Add(R.LightPoints.Get("L1"));
  R.Add(R.LightPoints.Get("L2"));
  R.Add(R.LightPoints.Get("L3"));
  // R.Add(R.Spheres.Get("S1"));
 /* for (INT i = 0; i < 18; i++)
  {
    R.GetCamera().RotateAt(vec3(0, 10, 0));
    R.DrawScene();
  }
  for (INT i = 0; i < 18; i++)
  {
    R.GetCamera().RotateAt(vec3(10, 0, 0));
    R.DrawScene();
  }*/
  R.Resize(1200, 1200);
  R.DrawScene();
} /* End of 'main' function */

//#define ISZERO(A) (abs(A) < 0.001)
//#define LZERO(A) ((A) < -0.001)
//#define UZERO(A) ((A) > 0.001)
//
///* Complex number structire */
//struct cmpl
//{
//  DBL Re, Im;
//
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
//
//  /* Complex number module.
//   * ARGUMENTS: None.
//   * RETURNS: 
//   *   (DBL) Arg;
//   */
//  DBL arg( VOID )
//  {
//    return atan2(Im, Re);
//  } /* End of 'arg' function */
//
//  /* Complex number module.
//   * ARGUMENTS: None.
//   * RETURNS: 
//   *   (DBL) Mod;
//   */
//  DBL mod( VOID )
//  {
//    return sqrt(Re * Re + Im * Im);
//  } /* End of 'mod' function */
//
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
//
//    return cmpl((FLOAT)(N * cos(A)), (FLOAT)(N * sin(A)));
//  } /* End of 'sqrt' function */
//
//  /* Complex sum function.
//   * ARGUMENTS: None.
//   * RETURNS: 
//   *   (cmpl) Sum;
//   */
//  cmpl operator+( const cmpl& A )
//  {
//    return cmpl(Re + A.Re, Im + A.Im);
//  } /* End of 'operator+' function */
//
//  /* Complex sum function.
//   * ARGUMENTS: None.
//   * RETURNS: 
//   *   (cmpl) Sum;
//   */
//  cmpl operator-( const cmpl& A )
//  {
//    return cmpl(Re - A.Re, Im - A.Im);
//  } /* End of 'operator-' function */
//
//  /* Complex sum function.
//   * ARGUMENTS: None.
//   * RETURNS: 
//   *   (cmpl) Sum;
//   */
//  cmpl operator-( VOID )
//  {
//    return cmpl(-Re, -Im);
//  } /* End of 'operator+' function */
//
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
//
//  /* Complex sum function.
//   * ARGUMENTS: None.
//   * RETURNS: 
//   *   (cmpl) Sum;
//   */
//  cmpl operator/( const cmpl& B )
//  {
//    DBL X = B.Re * B.Re + B.Im * B.Im;
//
//    return 
//      cmpl((Re * B.Re + Im * B.Im) / X, (Im * B.Re - Re * B.Im) / X);
//  } /* End of 'operator+' function */
//
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
//
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
//
///* Solutions struct */
//struct solutions
//{
//  INT NOS {};
//  DBL Sols[4] {};
//
//  /* Base constructor */
//  solutions( VOID )
//  {
//    NOS = 0;
//  } /* End of 'solutions' function */
//
//  /* Base constructor */
//  solutions( DBL A )
//  {
//    NOS = 1;
//    Sols[0] = A;
//  } /* End of 'solutions' function */
//
//  /* Base constructor */
//  solutions( DBL A, DBL B )
//  {
//    NOS = 2;
//    Sols[0] = A;
//    Sols[1] = B;
//  } /* End of 'solutions' function */
//
//  /* Base constructor */
//  solutions( DBL A, DBL B, DBL C )
//  {
//    NOS = 3;
//    Sols[0] = A;
//    Sols[1] = B;
//    Sols[2] = C;
//  } /* End of 'solutions' function */
//
//  /* Base constructor */
//  solutions( DBL A, DBL B, DBL C, DBL D )
//  {
//    NOS = 4;
//    Sols[0] = A;
//    Sols[1] = B;
//    Sols[2] = C;
//    Sols[3] = D;
//  } /* End of 'solutions' function */
//
//} /* End of 'solutions' struct */
//
///* Solve 2-power evaluation function.
// * ARGUMENTS:
// *   - koeficents:
// *       DBL a, DBL b, DBL c, DBL d;
// * RETURNS: 
// *   (solutions) all real solutions;
// */
//solutions Solve2( const DBL a, const DBL b, const DBL c )
//{
//  DBL D = b * b - 4 * a * c;
//
//  if (a == 0)
//  {
//    if (b == 0)
//      return solutions();
//    else
//      return solutions(-c / b);
//  }
//  if (D < 0)
//    return solutions();
//  if (D == 0)
//    return solutions(-b / (2 * a));
//  D = sqrt(D);
//  return solutions((-b + D) / (2 * a), (-b - D) / (2 * a));
//} /* End of 'Solve2' functios */
//
///* Solve 4-power evaluation function.
// * ARGUMENTS:
// *   - koeficents:
// *       DBL a, DBL b, DBL c, DBL d;
// * RETURNS: 
// *   (solutions) all real solutions;
// */
//solutions Solve3( DBL a, DBL b, DBL c, DBL d )
//{
//  if (ISZERO(a))
//    return Solve2(b, c, d);
//
//  DBL p((3 * a * c - b * b) / (3 * a * a) / 3), 
//    q((2 * b * b * b - 9 * a * b * c + 27 * a * a * d) / (27 * a * a * a) / 2);
//  DBL D(q * q + p * p * p), Delta = b / (3 * a);
//  //////// cmpl Tmp0(cmpl(-(q / 2.0)) + cmpl(D).root(2));
//
//  if (D == 0)
//  {
//    DBL Cb = cbrt(-q);
//
//    if (q == 0 && p == 0)
//      return solutions(-Delta);
//    return solutions(2 * Cb - Delta, -Cb - Delta);
//  }
//  else if (D > 0)
//  {
//    DBL Sc = sqrt(D);
//
//    return solutions(cbrt(-q + Sc) + cbrt(-q - Sc) - Delta);
//  }
//  DBL Fi, K = 2 * sqrt(-p),
//    Pi = 3.14159265359;
//
//  if (q == 0)
//    Fi = Pi / 2;
//  else
//  {
//    Fi = atan(-sqrt(-D) / q);
//    if (q > 0)
//      Fi += Pi;
//  }
//  Fi /= 3;
//  return solutions(K * cos(Fi) - Delta, 
//                   K * cos(Fi + (2 * Pi / 3)) - Delta, 
//                   K * cos(Fi + (4 * Pi / 3)) - Delta);
//} /* End of 'Solve3' functios */
//
///* Solve 4-power evaluation function.
// * ARGUMENTS:
// *   - koeficents:
// *       DBL a, DBL b, DBL c, DBL d, DBL e;
// * RETURNS: 
// *   (solutions) all real solutions;
// */
//solutions Solve4( DBL a, DBL b, DBL c, DBL d, DBL e )
//{
//  if (a == 0)
//    return Solve3(b, c, d, e);
//  {
//    DBL A = b / a, B = c / a, C = d / a, D = e / a;
//
//    a = A, b = B, c = C, d = D;
//  }
//
//  DBL p = b - 3 * a * a / 8,
//    q = a * a * a / 8 - a * b / 2  + c,
//    r = -3 * a * a * a * a / 256 + a * a * b / 16 - c * a / 4 + d;
//
//  solutions Sol = Solve3(2, -p, -2 * r, r * p - q * q / 4);
//  if (Sol.NOS == 0)
//    return solutions();
//  DBL s = Sol.Sols[0];
//  if (2 * s - p <= 0)
//    return solutions();
//  DBL t1 = sqrt(2 * s - p), t2 = q / (2 * t1);
//
//  INT k = (Sol = Solve2(1, -t1,  t2 + s)).NOS;
//  DBL Sols[4];
//
//  for (INT i = 0; i < Sol.NOS; i++)
//    Sols[i] = Sol.Sols[i];
//
//  Sol = Solve2(1,  t1, -t2 + s);
//  INT Total = k + Sol.NOS;
//  DBL Delta = a / 4;
//  for (INT i = 0; i < Sol.NOS; i++)
//    Sols[i + k] = Sol.Sols[i];
//  if (Total == 0)
//    return solutions();
//  if (Total == 1)
//    return solutions(Sols[0] - Delta);
//  if (Total == 2)
//    return solutions(Sols[0] - Delta, Sols[1] - Delta);
//  if (Total == 3)
//    return solutions(Sols[0] - Delta, Sols[1] - Delta, Sols[2] - Delta);
//  return 
//    solutions(Sols[0] - Delta, Sols[1] - Delta, Sols[2] - Delta, Sols[3] - Delta);
//} /* End of 'Solve4' functios */

/* END OF 'main.cpp' FILE */