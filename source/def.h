/*************************************************************
 * Copyright (C) 2021
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : def.h
 * PURPOSE     : Raytracing project.
 *               Base definitions module.
 * PROGRAMMER  : CGSG-SummerCamp'2021.
 *               Andrey Chugunov.
 * LAST UPDATE : 06.09.2021.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __def_h_
#define __def_h_

#include <iostream>
// #include <memory>
#include <string>
#include <cassert>
#include <vector>
#include <map>

#include <windows.h>

#include "math/math.h"

// DBG memory hooks
#ifndef NDEBUG
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h>
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))

static class __Dummy
{
public:
  /* Class constructor */
  __Dummy( VOID )
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' function */
} __ooppss;

#endif /* _DEBUG */

#ifdef _DEBUG
# ifdef _CRTDBG_MAP_ALLOC
#  define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
# endif /* _CRTDBG_MAP_ALLOC */
#endif /* _DEBUG */

/* Project namespace */
namespace acrtx
{
  typedef mth::vec3<DBL> vec3;
  typedef mth::matr<DBL> matr;
  typedef mth::ray<DBL> ray;
  typedef mth::camera<DBL> camera;

  /* Base project stock template class */
  template<typename entry_type, typename key_type = std::string>
    class stock
    {
    private:
      std::map<key_type, entry_type> Stock; // Entry stock

    public:
      /* Add entry to stock function.
       * ARGUMENTS:
       *   - Stock index value:
       *       const key_type &Index;
       *   - Entry element:
       *       const entry_type &Entry;
       * RETURNS: None.
       */
      VOID Add( const key_type &Index, const entry_type &Entry )
      {
        if (Stock.find(Index) == Stock.end())
          Stock[Index] = Entry;
      } /* End of 'Add' function */

      /* Get entry to stock function.
       * ARGUMENTS:
       *   - Stock index value:
       *       const key_type &Index;
       * RETURNS: None.
       */
      entry_type * Get( const key_type &Index )
      {
        auto i = Stock.find(Index);

        if (i != Stock.end())
          return &i->second;
        return nullptr;
      } /* End of 'Add' function */
    }; /* End of 'stock' class */

  /* Special error class */
  class error
  {
  public:
    /* Error type enum */
    enum error_type
    {
      scanner,
      parser,
      other
    }; /* End of error enum */
    /* Error message function.
     * ARGUMENTS: 
     *   - Message:
     *       const std::string &Msg;
     * RETURNS: None.
     */
    static VOID msg( const error_type Et, const std::string &Msg )
    {
      switch(Et)
      {
      case scanner:
        std::cout << "SCANNER: ";
        break;
      case parser:
        std::cout << "PARSER: ";
        break;
      }
      std::cout << Msg << std::endl;
    } /* End of 'msg' function */
  }; /* End of 'error' class */
} /* end of 'acrtx' namespace */

#endif /* __def_h_ */

/* END OF 'def.h' FILE */
