/* NAME          : resources.cpp
 * PURPOSE       : Resources module file.
 * CREATION DATE : 15.08.2021
 * LAST UPDATE   : 15.08.2021
 */

#include "../../../parser/parser.h"
#include "material.h"

/* Project namespace */
namespace acrtx
{ 
  /* Read material from stream in ac1 format function.
   * ARGUMENTS:
   *   - Stream to read from:
   *       std::stream &Stream;
   *   - Error string:
   *       std::string *Error;
   * RETURNS:
   *  (BOOL) Succes of reading;
   */
  BOOL material::ReadFromStream( std::iostream &Stream, std::string * const Error )
  {
    std::string Name, Param;

    auto SetError = [Error]( const std::string &Str ) -> BOOL
    {
      if (Error != nullptr)
        *Error = Str;
      return FALSE;
    }; /* End of 'SetError' function */

    Stream >> Name;
    if (!isalpha(Name[0]))
      return SetError("Material Name must beggins from letter!");
    while ((Stream >> Param, Param) != "!")
    {
      if (Param == "Ka")
      {
        if (!Ka.ReadFromStream(Stream))
          return SetError("Incorrect input of Ka in material " + Name + " module");        
      }
      else if (Param == "Kd")
      {
        if (!Kd.ReadFromStream(Stream))
          return SetError("Incorrect input of Kd in material " + Name + " module");
      }
      else if (Param == "Ks")
      {
        if (!Ks.ReadFromStream(Stream))
          return SetError("Incorrect input of Ks in material " + Name + " module");
      }
      else if (Param == "Ph")
      {
        if (!parser::ReadDBL(&Ph, Stream))
          return SetError("Incorrect input of Ph in material " + Name + " module");
      }
      else if (Param == "Kr")
      {
        if (!parser::ReadDBL(&Kr, Stream))
          return SetError("Incorrect input of Kr in material " + Name + " module");
      }
      else if (Param == "Kt")
      {
        if (!parser::ReadDBL(&Kt, Stream))
          return SetError("Incorrect input of Kt in material " + Name + " module");
      }
      else
        return SetError("Unknown material parameter in sphere " + Name + " module");
    }
    raytracer::Get().Materials.Add(Name, *this);
    return TRUE;
  } /* End of 'ReadFromStream' function*/

  /* Read environment from stream in ac1 format function.
   * ARGUMENTS:
   *   - Stream to read from:
   *       std::stream &Stream;
   *   - Error string:
   *       std::string *Error;
   * RETURNS:
   *  (BOOL) Succes of reading;
   */
  BOOL envi::ReadFromStream( std::iostream &Stream, std::string * const Error = nullptr )
  {
    std::string Name, Param;

    auto SetError = [Error]( const std::string &Str )
    {
      if (Error != nullptr)
        *Error = Str;
      return FALSE;
    }; /* End of 'SetError' function */

    Stream >> Name;
    if (!isalpha(Name[0]))
    {
      SetError("Environment Name must beggins from letter!");
      return FALSE;
    }
    while ((Stream >> Param, Param) != "!")
    {
      if (Param == "decay")
      {
        if (!parser::ReadDBL(&DecK, Stream))
          SetError("Incorrect input of Ka in environment " + Name + " module");        
      }
      else if (Param == "refract")
      {
        if (!parser::ReadDBL(&N, Stream))
          SetError("Incorrect input of Kd in environment " + Name + " module");
      }
      else if (Param == "reflect")
      {
        if (!parser::ReadDBL(&RefK, Stream))
          SetError("Incorrect input of Ks in environment " + Name + " module");
      }
    }
    raytracer::Get().Environments.Add(Name, *this);
    return TRUE;
  } /* End of 'ReadFromStream' function*/
} /* end of 'acrtx' namespace */

  /* END OF 'resources.cpp' FILE */