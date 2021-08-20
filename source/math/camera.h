/* NAME          : camera.h
 * PURPOSE       : Math matrix module file.
 * CREATION DATE : 07.08.2021
 * LAST UPDATE   : 07.08.2021
 */

#ifndef __camera_h_
#define __camera_h_

#include "acmath_def.h"
#include "vec3.h"
#include "matr.h"

/* Math namespace */
namespace acmath
{
  /* Matrix 4x4 class */
  template<typename Type>
    class camera
    {
    public:
      vec3<Type> 
        Loc,    // Camera location
        At,     // Camera at point
        Dir,    // Camera direction
        Up,     // Camera up direction
        Right;  // Camera right direction
      DBL Proj, // Project distance
        W, H;   // View width, height
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
        // Up = NUp.Normalize();
        Dir = (At - Loc).Normalize();
        Right = (Dir % Up).Normalize();
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

      /* Rotate camera (around Y axis direction) functrion.
       * ARGUMENTS:
       *   - Angle of rotation:
       *       const Type Angle;
       * RETURNS: None.
       */
      VOID RotateY( const Type Angle )
      {
        SetLocAt(Loc,
                 (matr<Type>::Translate(-Loc) * 
                  matr<Type>::RotateY(Angle) *
                  matr<Type>::Translate(Loc)).TransformPoint(At));
      } /* End of 'Rotate' function */

      /* Rotate camera centrally (around Y axis direction) functrion.
       * ARGUMENTS:
       *   - Angle of rotation:
       *       const Type Angle;
       * RETURNS: None.
       */
      VOID RotateCenterY( const Type Angle )
      {
        SetLocAt(matr<Type>::RotateY(Angle).TransformPoint(Loc),
                 At);
      } /* End of 'Rotate' function */

      /* Rotate camera (around Y axis direction) functrion.
       * ARGUMENTS:
       *   - Vector of rotation:
       *       const vec3<Type> Vec;
       *   - Angle of rotation:
       *       const Type Angle;
       * RETURNS: None.
       */
      VOID RotateCenterVec( const vec3<Type> Vec, const Type Angle )
      {
        // SetLocAt(Loc,
        //          matr<Type>::RotateVec(Vec, Angle).TransformPoint(At));
      } /* End of 'Rotate' function */

      /* Rotate camera (around X (Right) axis direction) functrion.
       * ARGUMENTS:
       *   - Angle of rotation:
       *       const Type Angle;
       * RETURNS: None.
       */
      VOID RotateX( const Type Angle )
      {
        // SetLocAt(Loc,
        //          (matr<Type>::Translate(-Loc) * 
        //           matr<Type>::RotateVec(Right, Angle) *
        //           matr<Type>::Translate(Loc)).TransformPoint(At));
      } /* End of 'Rotate' function */
    }; /* End of 'matr' class */
} /* end of 'acmath' namespace */

#endif /* __camera_h_ */

/* END OF 'camera.h' FILE */