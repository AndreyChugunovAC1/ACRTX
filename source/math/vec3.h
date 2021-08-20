/* NAME          : vec3.h
 * PURPOSE       : Math vec3 module file.
 * CREATION DATE : 07.08.2021
 * LAST UPDATE   : 11.08.2021
 */

#ifndef __vec3_h_
#define __vec3_h_

#include "acmath_def.h"

/* Math namespace */
namespace acmath
{
  /* 3-component vector class */
  template<typename Type>
    class vec3
    {
    public:
      Type X, Y, Z; // Vector's components

      /* Similar-component and default constructor.
       * ARGUMENTS:
       *   - Component:
       *       const Type A;
       */
      vec3( const Type A = 0 ) :
        X(A), Y(A), Z(A)
      {
      } /* End of 'vec3' function */

      /* Base class constructor 
       * ARGUMENTS:
       *   - All vector's components:
       *       const Type X, Y, Z;
       */
      vec3( const Type X, const Type Y, const Type Z ) :
        X(X), Y(Y), Z(Z)
      {
      } /* End of 'vec3' function */

      /* Vector addition function. 
       * ARGUMENTS:
       *   - Second vector to add:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator+( const vec3<Type> &V ) const
      {
        return vec3<Type>(X + V.X, Y + V.Y, Z + V.Z);
      } /* End of 'operator+' function */

      /* Vector addition function. 
       * ARGUMENTS:
       *   - Second vector to add:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator+=( const vec3<Type> &V )
      {
        X += V.X;
        Y += V.Y;
        Z += V.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Vector subtraction funcion.
       * ARGUMENTS:
       *   - Second vector to substract:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator-( const vec3<Type> &V ) const
      {
        return vec3<Type>(X - V.X, Y - V.Y, Z - V.Z);
      } /* End of 'operator-' function */
 
      /* Vector subtraction funcion.
       * ARGUMENTS:
       *   - Second vector to substract:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator-=( const vec3<Type> &V )
      {
        X -= V.X;
        Y -= V.Y;
        Z -= V.Z;
        return *this;
      } /* End of 'operator-=' function */

      /* Dot product vectors funcion.
       * ARGUMENTS:
       *   - Second vector to product:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (Type) result;
       */
      Type operator&( const vec3<Type> &V ) const
      {
        return X * V.X + Y * V.Y + Z * V.Z;
      } /* End of 'operator&'  function */

      /* Cross product vectors funcion.
       * ARGUMENTS:
       *   - Second vector to product:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (Type) result;
       */
      vec3<Type> operator%( const vec3<Type> &V ) const
      {
        return
          vec3<Type>( Y * V.Z - Z * V.Y,
                     -X * V.Z + Z * V.X,
                      X * V.Y - Y * V.X);
      } /* End of 'operator%'  function */

      /* Component vector product function.
       * ARGUMENTS:
       *   - Second vector to product:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator*( const vec3<Type> &V ) const
      {
        return
          vec3<Type>(X * V.X,
                     Y * V.Y,
                     Z * V.Z);
      } /* End of 'operator*' function */

      /* Component vector product function.
       * ARGUMENTS:
       *   - Second vector to product:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator*=( const vec3<Type> &V )
      {
        X *= V.X;
        Y *= V.Y;
        Z *= V.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Vector to number multiplication function.
       * ARGUMENTS:
       *   - Number to multiply:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator*( const Type N ) const
      {
        return
          vec3<Type>(X * N, Y * N, Z * N);
      } /* End of 'operator*' function */
      
      /* Vector to number multiplication function.
       * ARGUMENTS:
       *   - Number to multiply:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator*=( const Type N )
      {
        X *= N;
        Y *= N;
        Z *= N;
        return *this;
      } /* End of 'operator*' function */

      /* Vector to number division function.
       * ARGUMENTS:
       *   - Number to divide:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator/( const Type N ) const
      {
        if (N != 0)
          return vec3<Type>(X / N, Y / N, Z / N);
        else
          return vec3<Type>(0);
      } /* End of 'operator*' function */
      
      /* Vector to number division function.
       * ARGUMENTS:
       *   - Number to divide:
       *       const vec3<Type> &V;
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> operator/=( const Type N )
      {
        if (N != 0)
        {
          X /= N;
          Y /= N;
          Z /= N;
        }
        else
          X = Y = Z = 0;
        return *this;
      } /* End of 'operator*' function */

      /* Negate vector operation function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3<Type> result vector;
       */
      vec3<Type> operator-( VOID ) const
      {
        return vec3<Type>(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Get vector's length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector's length;
       */
      Type Length( VOID ) const 
      {
        return sqrt(X * X + Y * Y + Z * Z);
      } /* End of 'Length' function */

      /* Get vector's length squared function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector's squared length;
       */
      Type Length2( VOID ) const 
      {
        return X * X + Y * Y + Z * Z;
      } /* End of 'Length2' function */

      /* Vector normalize function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3<Type>) result vector;
       */
      vec3<Type> Normalize() const
      {
        Type Len = sqrt(X * X + Y * Y + Z * Z);

        if (Len == 0)
          return vec3<Type>(0);
        else
          return vec3<Type>(X / Len, Y / Len, Z / Len);
      } /* End of 'Normalize' function */

      /* Clamp vector tgo vector [0, 1] function.
       * ARGFUMENTS: None.
       * RETURNS: 
       *   (vec3<Type>) Clamped vector;
       */
      vec3<Type> Clamp( VOID )
      {
        return vec3<Type>(ClampLow1(X), ClampLow1(Y), ClampLow1(Z));
      } /* End of 'Clamp' function */
    }; /* End of 'vec3' class */
} /* end of 'acmath' namespace */

#endif /* __vec3_h_ */

 /* END OF 'vec3.h' FILE */