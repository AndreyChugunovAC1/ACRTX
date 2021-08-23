  /* NAME          : frame.h
 * PURPOSE       : Frame module file.
 * CREATION DATE : 08.08.2021
 * LAST UPDATE   : 11.08.2021
 */

#ifndef __frame_h_
#define __frame_h_

#include <iostream>
#include <filesystem>
#include <fstream>

#include "../def.h"

/* Projec namespace */
namespace acrtx
{
  /* Frame representation class */
  class frame
  {
  private:
    DWORD *Plane; // Frame plane

  public:
    INT W, H;     // Frame size

    /* Basre class constructor.
     * ARGUMENTS:
     *   - Frame's size (width & height):
     *       INT W, H;
     */
    frame( const INT W, const INT H )
    {
      Resize(W, H);
      // std::cout << W << " " << H << std::endl;
    } /* End of 'frame' function*/

    /* Class destructor. */
    ~frame( VOID )
    {
      Resize(0, 0);
    } /* End of '~frame' function*/

    /* Resize plane function.
     * ARGUMENTS:
     *   - New frame's size (width & height):
     *       INT Nw, Nh;
     * RETURNS: None.
     */
    VOID Resize( const INT Nw, const INT Nh )
    {
      // Checking Nw, Nh > 0
      H = Nh < 0 ? 0 : Nh;
      W = Nw < 0 ? 0 : Nw;

      INT Size = W * H;

      if (Plane != nullptr)
        delete[] Plane;
      if (Size == 0)
        Plane = nullptr;
      else
        Plane = new DWORD[Size];
    } /* End of 'Resize' function */

    /* Put pixel to frame function.
     * ARGUMENTS:
     *   - Pixel's coordinates:
     *       INT X, Y;
     *   - Pixel's color:
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( const INT X, const INT Y, const DWORD Color )
    {
      if (Plane != nullptr && 
        X >= 0 && Y >= 0 && X < W && Y < H)
        Plane[X + (H - 1 - Y) * W] = Color;
    } /* End of 'PutPixel' function */

    /* Put pixel to frame function.
     * ARGUMENTS:
     *   - Pixel's coordinates:
     *       INT X, Y;
     *   - Pixel's color:
     *       DWORD Color;
     * RETURNS: None.
     */
    VOID PutPixel( const INT X, const INT Y, const vec3 &Color )
    {
      if (Plane != nullptr && 
        X >= 0 && Y >= 0 && X < W && Y < H)
        Plane[X + (H - 1 - Y) * W] = 
          (((BYTE)(Color.Z)) | 
          (((BYTE)(Color.Y)) << 8) | 
          (((BYTE)(Color.X)) << 16));
    } /* End of 'PutPixel' function */

    /* Put pixel to frame function.
     * ARGUMENTS:
     *   - Pixel's coordinates:
     *       INT X, Y;
     *   - Pixel's color:
     *       BYTE R, G, B;
     * RETURNS: None.
     */
    VOID PutPixel( const INT X, const INT Y, 
      const BYTE R, const BYTE G, const BYTE B )
    {
      if (Plane != nullptr && 
        X >= 0 && Y >= 0 && X < W && Y < H)
        Plane[X + (H - 1 - Y) * W] = 
          (B | (G << 8) | (R << 16));
    } /* End of 'PutPixel' function */

    /* Save frame picture to tga file function.
     * ARGUMENTS:
     *   - Name of file to save:
     *       const std::string &FileName;
     *   - Start work time (for statistics):
     *       DBL StartTime;
     * RETURNS: 
     *   (BOOL) Success of saving.
     */
    BOOL SaveTGA( const std::string &FileName, const DBL StartTime, INT Index = -1 ) const
    {
      // Tga file format structures
      #pragma pack(push, 1)
      /* Base image header, TGA v.1-00, placed at file begin */
      struct tgaFILEHEADER
      {
        BYTE IDLength;     /* Length of ID string placed after header */
        BYTE ColorMapType; /* 1 - for color-mapped images */
 
        /* Image type */
        BYTE ImageType;
 
        /* Color-map (palette) data (ignored if 'ColorMapType' == 0) */
        WORD PaletteStart; /* First palette table (color-map) entry index */
        WORD PaletteSize;  /* Length of palette table in entries */
        BYTE PaletteEntrySize;  /* Length of palette table entry in bytes */
 
        /* Image data */
        WORD X, Y; /* Image origin (lower-left corner) coordinates */
        WORD Width, Height; /* Image size (in pixels) */
        BYTE BitsPerPixel; /* Pixel size in bits */
 
        /* Image description (by bits) */
        BYTE ImageDescr;
      } FHead {};

      /* Image footer, TGA v.2-00, placed at end of file */
      struct tgaFILEFOOTER
      {
        /* Extension area offset from file begin (0 - absent) */
        DWORD ExtensionOffset;
        /* Developer area offset from file begin (0 - absent) */
        DWORD DeveloperOffset;
        /* Signature of TGA - "TRUEVISION-XFILE.\x00",
         * see TGA_EXT_SIGNATURE */
        CHAR Signature[18];
      } FFooter {};

      /* Extension header */
      struct tgaEXTHEADER
      {
        WORD Size;               /* Extension area size */
        CHAR AuthorName[41];     /* Author name */
        /* Author comments: 4 lines by 80 characters with NULLs */
        CHAR AuthorComment[324];
        /* Date/time of last file modification */
        WORD
          StampMonth, StampDay, StampYear,
          StampHour, StampMinute, StampSecond;
        CHAR JobName[41];        /* Name/ID of task, job */
        /* Job time */
        WORD
          JobHour, JobMinute, JobSecond;
        CHAR SoftwareID[41];     /* Software ID */
        WORD VersionNumber;      /* Software version number (* 100) */
        BYTE VersionLetter;      /* Software version letter */
        DWORD KeyColor;          /* Key, background color */
        /* Aspect ration Num./Denom. */
        WORD
          PixelNumerator, PixelDenominator;
        /* Gamma correction Num./Denom. */
        WORD
          GammaNumerator, GammaDenominator;
        /* Offset of color correction table:
         *   WORD Alpha, Red, Green, Blue;    x 256 (2048 bytes)
         *  black - 0, 0, 0, 0; white - 65535, 65535, 65535, 65535 */
        DWORD ColorOffset;
        /* Offset of stamp image: 2 bytes WxH, stamp data (the same
         * to image format, no compressed) */
        DWORD StampOffset;
        /* Offset of raster lines table: 4 bytes offset for every line */
        DWORD ScanOffset;
        /* Type of attributes: 0 - no alpha present */
        BYTE AttributeType;
      } EHead {};
      #pragma pack(pop)

      CHAR Dir[100];

      // Wonderful shit (creates directory if doesn't exist):
      _splitpath(FileName.c_str(), nullptr, Dir, nullptr, nullptr);
      if (Dir[0] != '\0' && !std::filesystem::exists(Dir))
        std::filesystem::create_directories(Dir);
      // End of creating directories

      std::fstream F;
      std::string Name;

      if (Index > -1)
        F.open(Name = FileName + std::to_string(Index) + ".tga", std::fstream::out | std::fstream::binary);
      else
        F.open(Name = FileName + ".tga", std::fstream::out | std::fstream::binary);

      if (!F.is_open())
      {
        error::msg(error::other, "Can not create file " + FileName);
        return FALSE;
      }

      SYSTEMTIME st;
      DBL Time = (clock() - StartTime) / (DBL)CLOCKS_PER_SEC;

      // File head
      FHead.IDLength = 0;
      FHead.ColorMapType = 0;
      FHead.ImageType = 2;
      FHead.X = 0;
      FHead.Y = 0;
      FHead.Width = W;
      FHead.Height = H;
      FHead.BitsPerPixel = 32;
      FHead.ImageDescr = 8;
      
      EHead.Size = sizeof(tgaEXTHEADER);
      strcpy(EHead.AuthorName, "AC1");
      strcpy(EHead.AuthorComment, 
        "This scene is made by ACRTX converter.\n"
        "Creator: Andrey Chugunov.\n"
        "(C) Copyright 2021");

      F.write((CHAR*)&FHead, sizeof FHead);

      // Image data writing
      F.write((CHAR *)Plane, W * H * 4);

      GetSystemTime(&st);
      EHead.StampYear = st.wYear;
      EHead.StampMonth = st.wMonth;
      EHead.StampDay = st.wDay;
      EHead.StampHour = st.wHour;
      EHead.StampMinute = st.wMinute;
      EHead.StampSecond = st.wSecond;
      EHead.JobSecond = (INT)fmod(Time, 60);
      EHead.JobMinute = (INT)(fmod(Time, 3600)) / 60;
      EHead.JobHour = (INT)(Time) / 3600;
      EHead.AttributeType = 1;
      strcpy(EHead.JobName, "ACRTX converter");

      F.write((CHAR*)&EHead, sizeof EHead);

      strcpy(FFooter.Signature, "TRUEVISION-XFILE.");

      F.write((CHAR*)&FFooter, sizeof FFooter);
      F.close();
      std::cout << "Frame " << Name << " was successfully saved.\n";
      return TRUE;
    } /* End of 'SaveTGA' function */
  }; /* End of 'frame' class */
} /* end of 'acrtx' namespace */

#endif /* __frame_h_ */

/* END OF 'frame.h' FILE */