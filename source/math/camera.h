/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : frame.h
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

#ifndef __camera_h_
#define __camera_h_

#include "math_def.h"
#include "vec3.h"
#include "matr.h"

/* Math namespace */
namespace mth
{
  /* Matrix 4x4 class */
  template<typename Type>
    class camera
    {
    private:
      vec3<Type> 
        Loc,    // Camera location
        At,     // Camera at point
        Dir,    // Camera direction
        Up,     // Camera up direction
        Right;  // Camera right direction
      DBL Proj; // Project distance

    public:
      DBL W, H;  // View width, height
      /* Base class constructor
       * ARGUMENTS:
       *   - Camera location, at point, direction:
       *       const vec3<Type> &NLoc, 
       *       const vec3<Type> &NAt, 
       *       const vec3<Type> &NUp;
       */      
      camera( const INT NW, const INT NH,
              const vec3<Type> &NLoc = vec3<Type>(-6, 3, 10), 
              const vec3<Type> &NAt = vec3<Type>(0, 2, 0), 
              const vec3<Type> &NUp = vec3<Type>(0, 1, 0),
              const Type ProjDist = 1 ) :
        Proj(ProjDist)
      {
        SetLocAtUp(NLoc, NAt, NUp);
        Resize(NW, NH);
      } /* End of 'camera' function */

      /* Resize view size function.
       * ARGUMENTS:
       *   - New Width, height:
       *       const Type NW, NH;
       * RETURNS: None.
       */
      VOID Resize( const INT NW, const INT NH )
      {
        assert(NW > 0 && NH > 0);
        if (NW >= NH)
          W = 1, H = (DBL)NH / NW;
        else
          H = 1, W = (DBL)NW / NH;
      } /* End of 'Resize' function */

      /* Build ray by device coordinates function.
       * ARGUMENTS:
       *   - Coordinates:
       *       DBL Xc, Yc;
       * RETURNS:
       *   (ray<Type>) Built ray;
       */
      ray<Type> BuildRay( const DBL Xc, const DBL Yc )
      {
        return ray<Type>(Loc, 
                     Right * Xc + 
                     Dir * Proj + 
                     Up * Yc);
      } /* End of 'BuildRay' function */

      /* Set camera location function.
       * ARGUMENTS:
       *   - New location:
       *       const vec3<Type> &NLoc;
       * RETURNS: None.
       */
      VOID SetLoc( const vec3<Type> &NLoc )
      {
        SetLocAt(NLoc, At);
      } /* End of 'SetLoc' function */

      /* Set camera at point function.
       * ARGUMENTS:
       *   - New at point:
       *       const vec3<Type> &NAt;
       * RETURNS: None.
       */
      VOID SetAt( const vec3<Type> &NAt )
      {
        SetLocAt(Loc, NAt);
      } /* End of 'SetAt' function */

      /* Set zoom function.
       * ARGUMENTS:
       *   - New zoom:
       *       const DBL Zoom;
       * RETURNS: None.
       */
      VOID SetZoom( const DBL Zoom )
      {
        Proj = Zoom;
        if (Proj <= 0)
          Proj = 1;
      } /* End of 'SetZoom' function */

      /* Set zoom function.
       * ARGUMENTS:
       *   - New zoom:
       *       const DBL Zoom;
       * RETURNS: None.
       */
      VOID MulZoom( const DBL Zoom )
      {
        Proj *= Zoom;
        if (Proj <= 0)
          Proj = 1;
      } /* End of 'SetZoom' function */

      /* Set camera to new location function.
       * ARGUMENTS:
       *   - New location, at point:
       *       const vec3<Type> &NLoc, 
       *       const vec3<Type> &NAt;
       * RETURNS: None.
       */
      VOID SetLocAt( const vec3<Type> &NLoc, 
                     const vec3<Type> &NAt )
      {
        Loc = NLoc;
        At = NAt;
        //Up = (At = Loc)
        Dir = (At - Loc).Normalize();
        Right = (Dir % vec3<Type>(0, 1, 0)).Normalize();
        Up = (Right % Dir).Normalize();
      } /* End of 'SetLocAt' function */

      /* Set camera to new location function.
       * ARGUMENTS:
       *   - New location, at point:
       *       const vec3<Type> &NLoc, 
       *       const vec3<Type> &NAt,
       *        const vec3<Type> &Up;
       * RETURNS: None.
       */
      VOID SetLocAtUp( const vec3<Type> &NLoc, 
                       const vec3<Type> &NAt,
                       const vec3<Type> &NUp )
      {
        Loc = NLoc;
        At = NAt;
        Up = NUp.Normalize();
        Dir = (At - Loc).Normalize();
        Right = (Dir % Up).Normalize();
      } /* End of 'SetLocAtUp' function */

      /* Translate camera functrion.
       * ARGUMENTS:
       *   - Translate vector:
       *       const vec3<Type> &T;
       * RETURNS: None.
       */
      VOID Translate( const vec3<Type> &T )
      {
        SetLocAt(Loc + T, At + T);
      } /* End of 'Translate' function */

      /* Rotate location around center function. 
       * ARGUMENTS:
       *   - Rotate vwctor:
       *       const vec3<Type> &Rotate;
       * RETURNS: None.
       */
      VOID RotateCenterLoc( const vec3<Type> &Rotate )
      {
        SetLocAt((matr<Type>::RotateX(Rotate.X) * 
                  matr<Type>::RotateY(Rotate.Y) *
                  matr<Type>::RotateZ(Rotate.Z)).TransformVec(Loc), At);
      } /* End of 'RotateCenterLoc' function */

      /* Rotate at point around center function. 
       * ARGUMENTS:
       *   - Rotate vwctor:
       *       const vec3<Type> &Rotate;
       * RETURNS: None.
       */
      VOID RotateCenterAt( const vec3<Type> &Rotate )
      {
        SetLocAt(Loc, 
                 (matr<Type>::RotateX(Rotate.X) * 
                  matr<Type>::RotateX(Rotate.Y) *
                  matr<Type>::RotateX(Rotate.Z)).TransformVec(At));
      } /* End of 'RotateCenterLoc' function */

      /* Rotate at point around center function. 
       * ARGUMENTS:
       *   - Rotate vwctor:
       *       const vec3<Type> &Rotate;
       * RETURNS: None.
       */
      VOID RotateAt( const vec3<Type> &Rotate )
      {
        SetLocAt(At + 
                 (matr<Type>::RotateX(Rotate.X) * 
                  matr<Type>::RotateY(Rotate.Y) *
                  matr<Type>::RotateZ(Rotate.Z)).TransformVec(Loc - At), At);
      } /* End of 'RotateAt' function */

      /* Rotate at point around center function. 
       * ARGUMENTS:
       *   - Rotate vwctor:
       *       const vec3<Type> &Rotate;
       * RETURNS: None.
       */
      VOID RotateLoc( const vec3<Type> &Rotate )
      {
        SetLocAt(Loc, Loc + 
                 (matr<Type>::RotateX(Rotate.X) * 
                  matr<Type>::RotateY(Rotate.Y) *
                  matr<Type>::RotateZ(Rotate.Z)).TransformVec(At - Loc));
      } /* End of 'RotateLoc' function */

      /* Move location function. 
       * ARGUMENTS:
       *   - Delta vector:
       *       const vec3<Type> &Delta;
       * RETURNS: None.
       */
      VOID MoveLoc( const vec3<Type> &Delta )
      {
        SetLocAt(Loc + Delta, At);
      } /* End of 'MoveLoc' function */

      /* Move at point function. 
       * ARGUMENTS:
       *   - Delta vector:
       *       const vec3<Type> &Delta;
       * RETURNS: None.
       */
      VOID MoveAt( const vec3<Type> &Delta )
      {
        SetLocAt(Loc, At + Delta);
      } /* End of 'MoveLoc' function */

      ///* Rotate camera (around Y axis direction) functrion.
      // * ARGUMENTS:
      // *   - Angle of rotation:
      // *       const Type Angle;
      // * RETURNS: None.
      // */
      //VOID RotateY( const Type Angle )
      //{
      //  SetLocAt(Loc,
      //           (matr<Type>::Translate(-Loc) * 
      //            matr<Type>::RotateY(Angle) *
      //            matr<Type>::Translate(Loc)).TransformPoint(At));
      //} /* End of 'Rotate' function */

      ///* Rotate camera centrally (around Y axis direction) functrion.
      // * ARGUMENTS:
      // *   - Angle of rotation:
      // *       const Type Angle;
      // * RETURNS: None.
      // */
      //VOID RotateCenterY( const Type Angle )
      //{
      //  SetLocAt(matr<Type>::RotateY(Angle).TransformPoint(Loc),
      //           At);
      //} /* End of 'Rotate' function */

      ///* Rotate camera (around Y axis direction) functrion.
      // * ARGUMENTS:
      // *   - Vector of rotation:
      // *       const vec3<Type> Vec;
      // *   - Angle of rotation:
      // *       const Type Angle;
      // * RETURNS: None.
      // */
      //VOID RotateCenterVec( const vec3<Type> Vec, const Type Angle )
      //{
      //  // SetLocAt(Loc,
      //  //          matr<Type>::RotateVec(Vec, Angle).TransformPoint(At));
      //} /* End of 'Rotate' function */

      ///* Rotate camera (around X (Right) axis direction) functrion.
      // * ARGUMENTS:
      // *   - Angle of rotation:
      // *       const Type Angle;
      // * RETURNS: None.
      // */
      //VOID RotateX( const Type Angle )
      //{
      //  // SetLocAt(Loc,
      //  //          (matr<Type>::Translate(-Loc) * 
      //  //           matr<Type>::RotateVec(Right, Angle) *
      //  //           matr<Type>::Translate(Loc)).TransformPoint(At));
      //} /* End of 'Rotate' function */
    }; /* End of 'matr' class */
} /* end of 'acmath' namespace */

#endif /* __camera_h_ */

/* END OF 'camera.h' FILE */