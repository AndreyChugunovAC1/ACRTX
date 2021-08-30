/* NAME          : raytracer.h
 * PURPOSE       : Main raytracer module file.
 * CREATION DATE : 09.08.2021
 * LAST UPDATE   : 09.08.2021
 */

#ifndef __raytracer_h_
#define __raytracer_h_

#include <ctime>
#include <thread>

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
    std::map<std::string, INT> Indexes;
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
    stock<box> Boxes;
    stock<triangle> Triangles;
    stock<object> Objects;

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

    /* Resize all function.
     * ARGUMENTS:
     *   - New size:
     *       INT W, H;
     * RETURNS: None.
     */
    VOID Resize( const INT W, const INT H )
    {
      Cam.Resize(W, H);
      Frame.Resize(W, H);
    } /* End of 'Resize' function */

    /* Get camera for movement function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (camera) Camera;
     */
    camera & GetCamera( VOID )
    {
      return Cam;
    } /* End of 'GetCamera' function */

    /* Enter current scene to fill function.
     * ARGUMENTS:
     *   - Name of scene:
     *       const std::string &Name;
     * RETURNS: None.
     */
    VOID ChooseScene( const std::string &Name )
    {
      CurScene = Name;
      if (Indexes.find(CurScene) == Indexes.end())
        Indexes[CurScene] = 0;
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
     * RETURNS: 
     *   (BOOL) Success of drawing.
     */
    BOOL DrawScene( VOID ) // FileName ?
    {
      if (Scenes.find(CurScene) == Scenes.end())
      {
        error::msg(error::other,
                   "Scene " + CurScene + " does not exist.");
        return FALSE;
      }
      INT N;
      std::vector<std::thread> Threads(N = std::thread::hardware_concurrency() - 1);

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
      // auto F = [](){};

      for (INT i = 0; i < N; i++)
      {
        Threads[i] = std::thread([this, i, N]( VOID ){
          DBL x {}, y {};
          scene Current = Scenes[CurScene];
          
          // R.Org = Cam.Loc;
          // std::cout << Frame.W << " " << Frame.H << std::endl;
          for (x = i; x < Frame.W; x += N)
            for (y = 0; y < Frame.H; y++)
            {
              // std::cout << x << " " << y << std::endl;
              Frame.PutPixel((INT)x, (INT)y, 
                             Current.Trace(
                               Cam.BuildRay(
                                 (x - (DBL)Frame.W / 2 + 0.5) * Cam.W / Frame.W, 
                                 ((DBL)Frame.H / 2 - y + 0.5) * Cam.H / Frame.H
                               )
                             ).Clamp() * 255.0);
            }
        });
      }
      for (auto &I : Threads)
        I.join();
      return Frame.SaveTGA(CurScene, 0, Indexes[CurScene]++);
    } /* End of 'DrawScene' function */
  }; /* End of 'raytracer' class */
} /* end of 'acrtx' namespace */

#endif /* __raytracer_h_ */

/* END OF 'raytracer.h' FILE */