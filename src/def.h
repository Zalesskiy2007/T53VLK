/*************************************************************
 * Copyright (C) 2023
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

 /* FILE NAME   : def.h
  * PROGRAMMER  : MZ2.
  * LAST UPDATE : 01.09.2023.
  * PURPOSE     : Animation 3D render with OpenGL project.
  *               Default common definition module.
  * NOTE        : Module namespace 'mzgl'.
  *
  * No part of this file may be changed without agreement of
  * Computer Graphics Support Group of 30 Phys-Math Lyceum
  */

#ifndef __def_h_
#define __def_h_

#include <cassert>

#ifndef WIN32
#define WIN32
#include <commondf.h>
#undef WIN32
#else
#include <commondf.h>
#endif /* WIN32 */
#define BOOL bool

  /* Math support */
#include "mth/mth.h"

/* Debug memory allocation support */
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
  __Dummy(VOID)
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;

#endif /* _DEBUG */ 

#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */

/* Base large integer types */
typedef unsigned long long UINT64;
typedef long long INT64;

/* Vulkan includes */
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan.h>

/* Project namespace */
namespace mzgl
{
  /* Math types definitions */
  typedef mth::vec2<FLT> vec2;
  typedef mth::vec3<FLT> vec3;
  typedef mth::vec4<FLT> vec4;
  typedef mth::matr<FLT> matr;
  typedef mth::ray<FLT> ray;
  typedef mth::camera<FLT> camera;

  /* Unstructured data file reader class */
  class rdr
  {
  private:
    // Memory pointer reference
    BYTE *&Ptr;
 
  public:
    /* Class constructor.
      * ARGUMENTS:
      *   - reference to memory pointer:
      *       BYTE *&PtrRef;
      */
    rdr( BYTE *&PtrRef ) : Ptr(PtrRef)
    {
    } /* End of 'rdr' function */
 
    /* Read data function.
      * ARGUMENT:
      *   - read data pointer:
      *       type *Data;
      *   - read data count:
      *       INT Count;
      * RETURNS: None.
      */
    template<typename type>
      VOID operator()( type *Data, const INT Count = 1 )
      {
        if (Count == 1)
          *Data = *(type *)Ptr, Ptr += sizeof(type);
        else
          memcpy(Data, Ptr, sizeof(type) * Count), Ptr += sizeof(type) * Count;
      } /* End of 'operator()' function */
  }; /* End of 'rdr' class */

  /* Read string as DWORD operator.
   * ARGUMENT:
   *   - read data pointer:
   *       const CHAR *Str;
   *   - read data length:
   *       std::size_t Len;
   * RETURNS:
   *   (UINT) read data.
   */
  inline constexpr UINT operator""_dword( const CHAR *Str, std::size_t Len )
  {
    return *(UINT *)Str;
  } /* End of 'operator""_dword' function */
} /* end of 'mzgl' namespace */

#endif /* __def_h_ */

/* END OF 'def.h' FILE */