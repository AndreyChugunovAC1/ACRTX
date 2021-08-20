/* NAME          : scene.cpp
 * PURPOSE       : Scene module file.
 * CREATION DATE : 16.08.2021
 * LAST UPDATE   : 16.08.2021
 */

#include "../../parser/parser.h"
#include "scene.h"

/* Project namespace */
namespace acrtx
{
  /* Read scene from stream in ac1 format function.
   * ARGUMENTS:
   *   - Stream to read from:
   *       std::iostream &Stream;
   *   - Error string:
   *       std::string * const Error;
   * RETURNS:
   *   (BOOL) True if success;
   */
  BOOL scene::ReadFromStream( std::iostream &Stream, std::string * const Error )
  {
    std::string SceneName, Param;

    auto SetError = [Error]( const std::string &Str )
    {
      if (Error != nullptr)
        *Error = Str;
      return FALSE;
    };

    Stream >> SceneName;
    if (!isalpha(SceneName[0]))
    {
      SetError("Scene name must beggins from letter!");
      return FALSE;
    }
    raytracer::Get().ChooseScene(SceneName);
    while ((Stream >> Param, Param) != "!")
    {
      if (Param == "sphere")
      {
        std::string Name;
        sphere *Sp;

        Stream >> Name;
        if ((Sp = raytracer::Get().Spheres.Get(Name)) != nullptr)
          raytracer::Get().Add(Sp);
        else
        {
          error::msg("Sphere with name " + Name + " doesn't exist in scene " + SceneName + " module!");
          return FALSE;
        }
      }
      else if (Param == "light_point")
      {
        std::string Name;
        light_point *Lp;

        Stream >> Name;
        if ((Lp = raytracer::Get().LightPoints.Get(Name)) != nullptr)
          raytracer::Get().Add(Lp);
        else
        {
          error::msg("Light point with name " + Name + " doesn't exist in scene " + SceneName + " module!");
          return FALSE;
        }
      }
      else if (Param == "plane")
      {
        std::string Name;
        plane *Pl;

        Stream >> Name;
        if ((Pl = raytracer::Get().Planes.Get(Name)) != nullptr)
          raytracer::Get().Add(Pl);
        else
        {
          error::msg("Plane with name " + Name + " doesn't exist in scene " + SceneName + " module!");
          return FALSE;
        }
      }
      else
        SetError("Unknown scene parameter in sphere " + SceneName + " module");
    }
    raytracer::Get().DrawScene();
    return TRUE;
  } /* End of 'ReadFromStream' function */
} /* end of 'acrtx' namespace */

/* END OF 'scene.h' FILE */