/* NAME          : raytracer.h
 * PURPOSE       : Main raytracer module file.
 * CREATION DATE : 09.08.2021
 * LAST UPDATE   : 09.08.2021
 */

#ifndef __raytracer_h_
#define __raytracer_h_

#include <ctime>

#include "scene/scene.h"
#include "../frame/frame.h"

/* Projec namespace */
namespace acrtx
{
  /* Base raytracer class */
  class raytracer
  {
  private:
    static raytracer Instance;
    frame Frame;
    std::string CurScene;
    // stock<sphere> Spheres;

    std::map<std::string, scene> Scenes;
    camera Cam;

    /* Default class constructor */
    raytracer() :
      CurScene(""), Frame(1200, 1200),
      Cam(1200, 1200)
    {
      Materials.Add("DEFAULT", material());
      Environments.Add("DEFAULT", envi());
    } /* End of 'raytracer' function */

  public:
    // Shapes
    stock<sphere> Spheres;
    stock<plane> Planes;

    // Resources
    stock<material> Materials;
    stock<envi> Environments;

    // Lights
    stock<light_point> LightPoints;

    /* Class destructor */
    ~raytracer( VOID )
    {
    } /* End of '~raytracer' function */

    /* Get instance function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (raytracer &) single tone;
     */
    static raytracer & Get( VOID )
    {
      return Instance;
    } /* End of 'Get' function */

    /* Enter current scene to fill function.
     * ARGUMENTS:
     *   - Name of scene:
     *       const std::string &Name;
     * RETURNS: None.
     */
    VOID ChooseScene( const std::string &Name )
    {
      CurScene = Name;
    } /* End of 'ChooseScene' function */

    /* Add to scene object from stock by name fuction.
     * ARGUMENTS:
     *   - Name of object to add:
     *       const std::string &Name;
     * RETURNS: None.
     */
    template<typename Type>
      VOID Add( Type * const Object )
      {
        Scenes[CurScene].Add(Object);
      } /* End of 'AddSphere' function */

    // /* Add to scene object from stock by name fuction.
    //  * ARGUMENTS:
    //  *   - Name of object to add:
    //  *       const std::string &Name;
    //  * RETURNS: None.
    //  */
    // VOID AddPlane( const std::string &Name )
    // {
    //   Scenes[CurScene].AddShape(Planes.Get(Name));
    // } /* End of 'AddSphere' function */
    // 
    // /* Add to scene object from stock by name fuction.
    //  * ARGUMENTS:
    //  *   - Name of object to add:
    //  *       const std::string &Name;
    //  * RETURNS: None.
    //  */
    // VOID AddPointLight( const std::string &Name )
    // {
    //   Scenes[CurScene].AddLight(LightPoints.Get(Name));
    // } /* End of 'AddPointLight' function */

    /* Draw choosen scene function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID DrawScene( VOID ) // FileName ?
    {
      DBL x {}, y {};
      DBL xp, yp;
      ray R;
      scene Current = Scenes[CurScene];
      if (Scenes.find(CurScene) == Scenes.end())
      {
        error::msg(error::other,
                   "Scene " + CurScene + " does not exist.");
        return;
      }
      // vec3 Color;
      // inter I;


      // Debug ray to center //
      // R.Org = Cam.Loc;
      // x = Frame.W / 2;
      // y = Frame.H / 2;
      // xp = (x - (DBL)Frame.W / 2 + 0.5) * Cam.W / Frame.W;
      // yp = ((DBL)Frame.H / 2 - y + 0.5) * Cam.H / Frame.H;
      // 
      // R.Dir = (Cam.Right * xp + 
      //           Cam.Dir * Cam.Proj + 
      //           Cam.Up * yp).Normalize();
      // Frame.PutPixel((INT)x, (INT)y, Current.Trace(R).Clamp() * 255.0);
      /////////////////////////
      R.Org = Cam.Loc;
      for (x = 0; x < Frame.W; x++)
        for (y = 0; y < Frame.H; y++)
        {
          xp = (x - (DBL)Frame.W / 2 + 0.5) * Cam.W / Frame.W;
          yp = ((DBL)Frame.H / 2 - y + 0.5) * Cam.H / Frame.H;

          R.Dir = (Cam.Right * xp + 
                   Cam.Dir * Cam.Proj + 
                   Cam.Up * yp).Normalize();
          Frame.PutPixel((INT)x, (INT)y, Current.Trace(R).Clamp() * 255.0);
        }
      Frame.SaveTGA(CurScene, 0);
    } /* End of 'DrawScene' function */
  }; /* End of 'raytracer' class */
} /* end of 'acrtx' namespace */

#endif /* __raytracer_h_ */

/* END OF 'raytracer.h' FILE */