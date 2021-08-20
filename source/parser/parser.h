/* NAME          : parser.h
 * PURPOSE       : Parser module file.
 * CREATION DATE : 12.08.2021
 * LAST UPDATE   : 12.08.2021
 */

#ifndef __parser_h_
#define __parser_h_

#include <cctype>
#include <cstdio>
#include <cstdlib>

#include "../rtx/raytracer.h"

/* Project namespace */
namespace acrtx
{
  /* Parser stock class */
  class parser
  {
  private:
    /* Lexem type representation struct */
    enum struct lexem_type
    {
      number,
      reserved,
      name
    }; /* End of 'lexem_type' struct */

    /* Lexem type representation struct */
    enum struct reserved
    {
      material,
      environment,
      sphere,
      plane,
      lposition,
      box,
      ldirection,
      scene,
      cycle,
      rotate,
      move,
      // material
      kmambient,
      kmdeffered,
      kmspectral,
      kmreflect,
      kmrefract,
      // environment
      kedecay,
      kerefract,
      kerefindex,
      ///
      radius,
      position,
      normal,
      color,
      direction,
      minbb,
      maxbb,
      endblock,
      kmphong
    }; /* End of 'reserved' struct */

    /* Lexem type representation struct */
    struct lexem
    {
    public:
      lexem_type Type;
      INT Line;

      union
      {
        DBL Num;
        reserved RW;
        CHAR Name[31];
      };

      /* Default class constructor */
      lexem() :
        Num(0.0), Type(lexem_type::number),
        Line(0)
      {
      } /* End of 'lexem' function */

      /* Copying constructor */
      lexem( const lexem &L ) :
        Type(L.Type), Line(L.Line)
      {
        switch(L.Type)
        {
        case lexem_type::name:
          strncpy(Name, L.Name, 30);
          break;
        case lexem_type::reserved:
          RW = L.RW;
          break;
        default:
          Num = L.Num;
          break;
        }
      } /* End of 'lexem' function */

      /* Base class destructor */
      ~lexem()
      {
      } /* End of '~lexem' function */
    }; /* End of 'lexem' struct */

    // std::fstream File;
    // std::fstream File;
    std::vector<lexem> Lexems;
    INT Pos;

    /* Parser error flag enum */
    enum struct parser_error
    {
      ok,
      error,
      end
    }; /* End of 'parser_error' enum */

    /* Read name funcrtion.
     * ARGUMENTS:
     *   - name to read:
     *       std::string * const Name;
     * RETURNS:
     *   (BOOL) Success of reading;
     */
    BOOL ReadName( std::string * const Name )
    {
      if (Lexems[Pos].Type != lexem_type::name)
      {
        error::msg(error::parser, "Expected name at " + std::to_string(Lexems[Pos].Line) + " line.");
        return FALSE;
      }
      *Name = Lexems[Pos++].Name;
      return TRUE;
    } /* End of 'ReadName' function */

    /* Read double function.
     * ARGUMENTS:
     *   - Number to read:
     *       DBL * const Val;
     * RETURNS:
     *   (BOOL) Success of reading;
     */
    BOOL ReadDBL( DBL * const Val )
    {
      if (Lexems[Pos].Type != lexem_type::number)
      {
        error::msg(error::parser,
                   "Expected a number in " + std::to_string(Lexems[Pos].Line) + " line.");
        return FALSE;
      }
      *Val = Lexems[Pos++].Num;
      return TRUE;
    } /* End of 'ReadDbl' function */

    /* Read vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) Success of reading;
     */
    BOOL ReadVec( vec3 * const Vec )
    {
      if (!ReadDBL(&Vec->X) || 
          !ReadDBL(&Vec->Y) || 
          !ReadDBL(&Vec->Z))
        return FALSE;
      return TRUE;
    } /* End of 'ReadVec' function */

    /* Read material function,
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) Success of reading;
     */
    BOOL ReadMaterial( VOID )
    {
      material Mtl;
      std::string Name;

      /* Name reading */
      if (!ReadName(&Name))
        return FALSE;
       
      while (Lexems[Pos].RW != reserved::endblock)
      {
        if (Lexems[Pos].Type != lexem_type::reserved || 
            (Lexems[Pos].RW != reserved::kmambient  && 
             Lexems[Pos].RW != reserved::kmdeffered && 
             Lexems[Pos].RW != reserved::kmspectral && 
             Lexems[Pos].RW != reserved::kmreflect  && 
             Lexems[Pos].RW != reserved::kmrefract  &&
             Lexems[Pos].RW != reserved::kmphong))
        {
          error::msg(error::parser,
                     "Unknown material parameter in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
        switch (Lexems[Pos++].RW)
        {
        case reserved::kmambient:
          if (!ReadVec(&Mtl.Ka))
            return FALSE;
           break;
        case reserved::kmdeffered:
          if (!ReadVec(&Mtl.Kd))
            return FALSE;
          break;
        case reserved::kmspectral:
          if (!ReadVec(&Mtl.Ks))
            return FALSE;
          break;
        case reserved::kmreflect:
          if (!ReadDBL(&Mtl.Kr))
            return FALSE;
          break;
        case reserved::kmrefract:
          if (!ReadDBL(&Mtl.Kt))
            return FALSE;
          break;
        case reserved::kmphong:
          if (!ReadDBL(&Mtl.Ph))
            return FALSE;
          break;
        default:
          error::msg(error::parser, 
                     "Error in scanner in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
      }
      raytracer::Get().Materials.Add(Name, Mtl);
      return TRUE;
    } /* End of 'ReadMaterial' function */

    /* Read environment function,
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) Success of reading;
     */
    BOOL ReadEnvi( VOID )
    {
      envi Envi;
      std::string Name;

      /* Name reading */
      if (!ReadName(&Name))
        return FALSE;
       
      while (Lexems[Pos].RW != reserved::endblock)
      {
        if (Lexems[Pos].Type != lexem_type::reserved || 
            (Lexems[Pos].RW != reserved::kedecay   && 
             Lexems[Pos].RW != reserved::kerefract &&
             Lexems[Pos].RW != reserved::kerefindex))
        {
          error::msg(error::parser,
                     "Unknown environment parameter in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
        switch (Lexems[Pos++].RW)
        {
        case reserved::kedecay:
          if (!ReadDBL(&Envi.DecK))
            return FALSE;
           break;
        case reserved::kerefindex:
          if (!ReadDBL(&Envi.N))
            return FALSE;
          break;
        case reserved::kerefract:
          if (!ReadDBL(&Envi.RefK))
            return FALSE;
          break;
        default:
          error::msg(error::parser, 
                     "Error in scanner in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
      }
      raytracer::Get().Environments.Add(Name, Envi);
      return TRUE;
    } /* End of 'ReadEnvi' function */

    /* Read sphere function,
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) Success of reading;
     */
    BOOL ReadPlane( VOID )
    {
      vec3 P;
      plane Plane;
      std::string Name;

      /* Name reading */
      if (!ReadName(&Name))
        return FALSE;
       
      while (Lexems[Pos].RW != reserved::endblock)
      {
        if (Lexems[Pos].Type != lexem_type::reserved || 
            (Lexems[Pos].RW != reserved::normal   && 
             Lexems[Pos].RW != reserved::position &&
             Lexems[Pos].RW != reserved::material &&
             Lexems[Pos].RW != reserved::environment))
        {
          error::msg(error::parser,
                     "Unknown plane parameter in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
        switch (Lexems[Pos++].RW)
        {
        case reserved::position:
          if (!ReadVec(&P))
            return FALSE;
          break;
        case reserved::normal:
          if (!ReadVec(&Plane.N))
            return FALSE;
          break;
        case reserved::material:
        {
          std::string Mat;
          if (!ReadName(&Mat))
            return FALSE;
          if ((Plane.Mtl = raytracer::Get().Materials.Get(Mat)) == nullptr)
          {
            error::msg(error::parser,
              "Material with name " + Mat + " does not exist. Line: " + std::to_string(Lexems[Pos].Line) + ".");
            return FALSE;
          }
          break;
        }
        case reserved::environment:
        {
          std::string Envi;
          if (!ReadName(&Envi))
            return FALSE;
          if ((Plane.Envi = raytracer::Get().Environments.Get(Envi)) == nullptr)
          {
            error::msg(error::parser,
              "Environment with name " + Envi + " does not exist. Line: " + std::to_string(Lexems[Pos].Line) + ".");
            return FALSE;
          }
          break;
        }
        default:
          error::msg(error::parser, 
                     "Error in scanner in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
      }
      Plane.D = Plane.N.Normalize() & P;
      raytracer::Get().Planes.Add(Name, Plane);
      return TRUE;
    } /* End of 'ReadPlane' function */

    /* Read scene function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) Success of reading;
     */
    BOOL ReadScene( VOID )
    {
      std::string Name, Obj;

      /* Name reading */
      if (!ReadName(&Name))
        return FALSE;
       
      raytracer::Get().ChooseScene(Name);
      while (Lexems[Pos].RW != reserved::endblock)
      {
        if (Lexems[Pos].Type != lexem_type::reserved || 
            (Lexems[Pos].RW != reserved::sphere    && 
             Lexems[Pos].RW != reserved::plane     &&
             Lexems[Pos].RW != reserved::lposition &&
             Lexems[Pos].RW != reserved::ldirection))
        {
          error::msg(error::parser,
                     "Unknown scene parameter in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
        switch (Lexems[Pos++].RW)
        {
        case reserved::lposition:
          if (!ReadName(&Obj))
            return FALSE;
          raytracer::Get().Add(raytracer::Get().LightPoints.Get(Obj));
          break;
        case reserved::ldirection:
          if (!ReadName(&Obj))
            return FALSE;
          // raytracer::Get().Add(raytracer::Get().LightPoints.Get(Obj));
          break;
        case reserved::plane:
          if (!ReadName(&Obj))
            return FALSE;
          raytracer::Get().Add(raytracer::Get().Planes.Get(Obj));
          break;
        case reserved::sphere:
          if (!ReadName(&Obj))
            return FALSE;
          raytracer::Get().Add(raytracer::Get().Spheres.Get(Obj));
          break;
        default:
          error::msg(error::parser, 
                     "Error in scanner in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
      }
      raytracer::Get().DrawScene();
      return TRUE;
    } /* End of 'ReadScene' function */

    /* Read sphere function,
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) Success of reading;
     */
    BOOL ReadSphere( VOID )
    {
      sphere Sph;
      std::string Name;

      /* Name reading */
      if (!ReadName(&Name))
        return FALSE;
       
      while (Lexems[Pos].RW != reserved::endblock)
      {
        if (Lexems[Pos].Type != lexem_type::reserved || 
            (Lexems[Pos].RW != reserved::radius   && 
             Lexems[Pos].RW != reserved::position &&
             Lexems[Pos].RW != reserved::material &&
             Lexems[Pos].RW != reserved::environment))
        {
          error::msg(error::parser,
                     "Unknown sphere parameter in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
        switch (Lexems[Pos++].RW)
        {
        case reserved::radius:
          if (!ReadDBL(&Sph.R))
            return FALSE;
          Sph.R2 = Sph.R * Sph.R;
          break;
        case reserved::position:
          if (!ReadVec(&Sph.C))
            return FALSE;
          break;
        case reserved::material:
        {
          std::string Mat;
          if (!ReadName(&Mat))
            return FALSE;
          if ((Sph.Mtl = raytracer::Get().Materials.Get(Mat)) == nullptr)
          {
            error::msg(error::parser,
              "Material with name " + Mat + " does not exist. Line: " + std::to_string(Lexems[Pos].Line) + ".");
            return FALSE;
          }
          break;
        }
        case reserved::environment:
        {
          std::string Envi;
          if (!ReadName(&Envi))
            return FALSE;
          if ((Sph.Envi = raytracer::Get().Environments.Get(Envi)) == nullptr)
          {
            error::msg(error::parser,
              "Environment with name " + Envi + " does not exist. Line: " + std::to_string(Lexems[Pos].Line) + ".");
            return FALSE;
          }
          break;
        }
        default:
          error::msg(error::parser, 
                     "Error in scanner in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
      }
      raytracer::Get().Spheres.Add(Name, Sph);
      return TRUE;
    } /* End of 'ReadSphere' function */

    /* Read light point function,
     * ARGUMENTS: None.
     * RETURNS:
     *   (BOOL) Success of reading;
     */
    BOOL ReadLightPoint( VOID )
    {
      light_point LP;
      std::string Name;

      /* Name reading */
      if (!ReadName(&Name))
        return FALSE;
       
      while (Lexems[Pos].RW != reserved::endblock)
      {
        if (Lexems[Pos].Type != lexem_type::reserved || 
            (Lexems[Pos].RW != reserved::color    &&
             Lexems[Pos].RW != reserved::position))
        {
          error::msg(error::parser,
                     "Unknown light point parameter in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
        switch (Lexems[Pos++].RW)
        {
        case reserved::position:
          if (!ReadVec(&LP.Pos))
            return FALSE;
          break;
        case reserved::color:
          if (!ReadVec(&LP.Color))
            return FALSE;
          break;
        default:
          error::msg(error::parser, 
                     "Error in scanner in " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
      }
      raytracer::Get().LightPoints.Add(Name, LP);
      return TRUE;
    } /* End of 'ReadSphere' function */

    /* Parser file function. 
     * ARGUMENTS: None.
     * RETURNS: 
     *   (BOOL) Success of parsing.
     */
    BOOL Parser( VOID )
    {
      INT Len = Lexems.size(); 

      for (Pos = 0; Pos < Len; Pos++)
      {
        if (Lexems[Pos].Type != lexem_type::reserved)
        {
          error::msg(error::parser, 
                     "Expected block at " + std::to_string(Lexems[Pos].Line) + " line.");
          return FALSE;
        }
        else
        {
          switch(Lexems[Pos++].RW)
          {
          case reserved::material:
            if (!ReadMaterial())
              return FALSE;
            break;
          case reserved::sphere:
            if (!ReadSphere())
              return FALSE;
            break;
          case reserved::environment:
            if (!ReadEnvi())
              return FALSE;
            break;
          case reserved::plane:
            if (!ReadPlane())
              return FALSE;
            break;
          case reserved::lposition:
            if (!ReadLightPoint())
              return FALSE;
            break;
          case reserved::scene:
            if (!ReadScene())
              return FALSE;
            break;
          default:
            error::msg(error::parser, 
                       "Expected block at " + std::to_string(Lexems[Pos].Line) + " line.");
            return FALSE;
          }
        }
      }
      return TRUE;
    } /* End of 'Parser' function */

    /* Scanner (calls parser at end) file function. 
     * ARGUMENTS:
     *   - File to scan:
     *       std::string &File;
     * RETURNS: None.
     */
    BOOL ScannerParser( const std::string &FileStr )
    {
      INT Pos = 0, 
        StrPos = 1;
      std::string Tmp;
      lexem L;

      while (FileStr[Pos] != '\0')
      {
        Tmp = "";

        while (FileStr[Pos] != '\0' && !isspace(FileStr[Pos]))
          Tmp += FileStr[Pos++];
        L.Line = StrPos;
        while (FileStr[Pos] != '\0' && isspace(FileStr[Pos]))
          if (FileStr[Pos++] == '\n')
            StrPos++;

        // Scanning:
        // If Tmp is digit
        if (Tmp[0] == '-' || isdigit(Tmp[0]))
        {
          BOOL IsDot = FALSE;

          // Check if Tmp is not a 'nan'
          for (INT i = 1, len = Tmp.length(); i < len; i++)
            if (!isdigit(Tmp[i]) && (IsDot == TRUE ? FALSE : (IsDot = TRUE, Tmp[i] != '.')))
            {
              error::msg(error::scanner, "Input number is incorrect in " + std::to_string(StrPos) + " line.");
              return FALSE;
            }
          L.Num = strtod(Tmp.c_str(), nullptr);
          L.Type = lexem_type::number;
        }
        else
        {
          L.Type = lexem_type::reserved;
          // L.Type = lexem_type::name, L.Name = Tmp;
          Tmp == "material"      ? (L.RW = reserved::material)    :
          Tmp == "environment"   ? (L.RW = reserved::environment) :
          Tmp == "sphere"        ? (L.RW = reserved::sphere)      :
          Tmp == "plane"         ? (L.RW = reserved::plane)       :
          Tmp == "box"           ? (L.RW = reserved::box)         :
          Tmp == "plane"         ? (L.RW = reserved::plane)       :
          Tmp == "light_point"   ? (L.RW = reserved::lposition)   :
          Tmp == "light_dir"     ? (L.RW = reserved::ldirection)  :
          Tmp == "ka"            ? (L.RW = reserved::kmambient)   :
          Tmp == "kd"            ? (L.RW = reserved::kmdeffered)  :
          Tmp == "ks"            ? (L.RW = reserved::kmspectral)  :
          Tmp == "ph"            ? (L.RW = reserved::kmphong)     :
          Tmp == "kr"            ? (L.RW = reserved::kmreflect)   :
          Tmp == "kt"            ? (L.RW = reserved::kmrefract)   :
          Tmp == "position"      ? (L.RW = reserved::position)    :
          Tmp == "color"         ? (L.RW = reserved::color)       :
          Tmp == "for"           ? (L.RW = reserved::cycle)       :
          Tmp == "move"          ? (L.RW = reserved::move)        :
          Tmp == "rotate"        ? (L.RW = reserved::rotate)      :
          Tmp == "decay"         ? (L.RW = reserved::kedecay)     :
          Tmp == "refindex"      ? (L.RW = reserved::kerefindex)  :
          Tmp == "refract"       ? (L.RW = reserved::kerefract)   :
          Tmp == "radius"        ? (L.RW = reserved::radius)      :
          Tmp == "maxbb"         ? (L.RW = reserved::maxbb)       :
          Tmp == "minbb"         ? (L.RW = reserved::minbb)       :
          Tmp == "normal"        ? (L.RW = reserved::normal)      :
          Tmp == "scene"         ? (L.RW = reserved::scene)       :
          Tmp == "!"             ? (L.RW = reserved::endblock)    :
            (strncpy(L.Name, Tmp.c_str(), 30), L.Type = lexem_type::name, reserved::endblock);
          if (L.Type == lexem_type::name && Tmp.size() >= 30)
          {
            error::msg(error::scanner, 
              "Name " + Tmp + " is too long (maximum is 30 symbols) at " + std::to_string(L.Line) + " line.");
            return FALSE;
          }
        }
        Lexems.push_back(L);
      }
      return Parser();
    } /* End of 'Scanner' function */

  public:
    ///* Read lexem from string function.
    // * ARGUMENTS: None.
    // * RETURNS: 
    // *   (lexem) Readed lexem.
    // */
    //lexem ReadLexem( VOID )
    //{
    //  lexem L;
    //  std::string S;

    //  S
    //} /* End of 'ReadLexem' function */

    /* Base class & program constructor. */
    parser( VOID )
    {
    } /* End of 'parser' function */

    /* Class destructor. */
    ~parser( VOID )
    {
    } /* End of '~parser' function */

    /* Open file function.
     * ARGUMENTS:
     *   - File name:
     *       std::dtring &FileName;
     * RETURNS: None.
     */
    VOID ParseFile( const std::string &FileName )
    {
      FILE *F;
      // std::fstream F;
      // std::string Tmp;

      if ((F = fopen(FileName.c_str(), "r")) == nullptr)
      {
        error::msg(error::other, "Can not open " + FileName + " file.");
        return;
      }
      INT Ch;
      std::string FileStr;

      while ((Ch = fgetc(F)) != EOF)
        FileStr += Ch;
      fclose(F);
      // std::cout << FileStr;
      ScannerParser(FileStr); // --> Parser ?
      Lexems.clear();
      // Parser();
      // parser_error Err;
      // while ((Err = ParseBlock()) == parser_error::ok);
      // if (Err == parser_error::error)
      // {
      //   error::msg("Parsing of " + FileName + " file stopped.");
      //   return;
      // }
      // else if (Err == parser_error::end)
      // std::cout << "Parsing of file " << FileName << " ended.";
    } /* End of 'ParseFile' function */
  }; /* End of 'parser' class */
} /* end of 'acrtx' namespace */

#endif /* __parser_h_ */

/* END OF 'parser.h' FILE */