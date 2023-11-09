/* FILE NAME   : texture.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               texture module.
 */

#include "mzgl.h"
#include <cstdio>

/* Texture add img function.
 * ARGUMENTS:
 *   - Name:
 *       std::string Name;
 *   - Width:
 *       INT W;
 *   - Height:
 *       INT H;
 *   - Components:
 *       INT C;
 *   - Pointer to data:
 *       VOID *ptr;
 * RETURNS:
 *   (texture &) self reference.
 */
mzgl::texture & mzgl::texture::AddImg( std::string Name, INT W, INT H, INT C, VOID *ptr )
{
  INT n;

 // glGenTextures(1, &TexId);
  this->H = H;
  this->W = W;
  this->IsCubeMap = FALSE;
 // glBindTexture(GL_TEXTURE_2D, TexId);
 // glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  
  n = log(W > H ? W : H) / log(2);
  n = n < 1 ? 1 : n;

 // glTexStorage2D(GL_TEXTURE_2D, n, C == 4 ?// gl_RGBA8 : C == 3 ?// gl_RGB8 :// gl_R8, W, H);

 // glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H, C == 4 ?// gl_BGRA : C == 3 ?// gl_BGR :// gl_LUMINANCE ,// gl_UNSIGNED_BYTE, ptr);

 // glGenerateMipmap(GL_TEXTURE_2D);

 // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_MIN_FILTER,// gl_LINEAR_MIPMAP_LINEAR);

 // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_MAG_FILTER,// gl_LINEAR);

 // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_WRAP_S,// gl_REPEAT);
 // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_WRAP_T,// gl_REPEAT);

  return *this;
} /* End of 'AddImg' function */

/* Texture add cube map function.
 * ARGUMENTS:
 *   - File name:
 *       const CHAR *FileName;
 *   - Name:
 *       std::string Name;
 * RETURNS:
 *   (texture &) self reference.
 */
mzgl::texture & mzgl::texture::AddCubeMap( const CHAR *FileName, std::string Name )
{
  FILE *F;

  const CHAR * f[] = {
    "/right.g24",
    "/left.g24",
    "/top.g24",
    "/bottom.g24",
    "/front.g24",
    "/back.g24"
    };
 // glGenTextures(1, &TexId);
 // glBindTexture(GL_TEXTURE_CUBE_MAP, TexId);
  for (INT i = 0; i < 6; i++)
  {
    CHAR Dest[200] = "";
    strcat(Dest, FileName);
    strcat(Dest, f[i]);

    if ((F = fopen(Dest, "rb")) != NULL)
    {                                 
      INT w = 0, h = 0;
      BYTE *mem;

      fread(&w, 2, 1, F);
      fread(&h, 2, 1, F);
      this->W = w;
      this->H = h;
      if ((mem = (BYTE *)malloc(w * h * 3)) != NULL)
      {

        fread(mem, 3, w * h, F);

       // glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 
             0,// gl_RGB, w, h,
             0,// gl_RGB,// gl_UNSIGNED_BYTE, mem);

        free(mem);
      }
      fclose(F);
    }
  }

 // glTexParameteri(GL_TEXTURE_CUBE_MAP,// gl_TEXTURE_MIN_FILTER,// gl_LINEAR);
 // glTexParameteri(GL_TEXTURE_CUBE_MAP,// gl_TEXTURE_MAG_FILTER,// gl_LINEAR);
 // glTexParameteri(GL_TEXTURE_CUBE_MAP,// gl_TEXTURE_WRAP_S,// gl_CLAMP_TO_EDGE);
 // glTexParameteri(GL_TEXTURE_CUBE_MAP,// gl_TEXTURE_WRAP_T,// gl_CLAMP_TO_EDGE);
 // glTexParameteri(GL_TEXTURE_CUBE_MAP,// gl_TEXTURE_WRAP_R,// gl_CLAMP_TO_EDGE);

  return *this;
} /* End of 'AddCubeMap' function */

IWICImagingFactory2 *mzgl::texture::WicFactory = nullptr;

std::vector<DWORD> mzgl::texture::LoadAll( std::string Name )
{
  std::vector<DWORD> Res;

  if (WicFactory == nullptr)
  {
    CoInitialize(nullptr);
    CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&WicFactory));
  }
  // Load through Window Image Component
  if (WicFactory != nullptr)
  {
    IWICBitmapDecoder *Decoder {};
    std::wstring FileNameW {Name.begin(), Name.end()};

    // Create decoder (loader)
    WicFactory->CreateDecoderFromFilename(FileNameW.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &Decoder);
    if (Decoder != nullptr)
    {
      IWICBitmapFrameDecode *Frame {};
      Decoder->GetFrame(0, &Frame);
      UINT fw = 0, fh = 0;

      if (Frame != nullptr)
      {
        Frame->GetSize(&fw, &fh);
        if (fw != 0 && fh != 0)
        {           
          // Converting image format to standard - RGBA with 8-bits per pixel
          IWICFormatConverter *Convert {};
          WicFactory->CreateFormatConverter(&Convert);
          if (Convert != nullptr)
          {
            // Converter initialization
            Convert->Initialize(Frame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);

            // Size checking
            Convert->GetSize(&fw, &fh);
            if (fw != 0 && fh != 0)
            {
              this->W = fw;
              this->H = fh;
              Res.resize((size_t)fw * fh);

              // Copying image pixels to container pixel array
              WICRect Rect {0, 0, static_cast<INT>(fw), static_cast<INT>(fh)};
              Convert->CopyPixels(&Rect, fw * 4, fw * fh * 4, (BYTE *)Res.data());
            }
            Convert->Release();
          }
        }
        Frame->Release();
      }
      Decoder->Release();
    }
  }

  return Res;
}

/* Texture add from file function.
 * ARGUMENTS:
 *   - File name:
 *       const CHAR *FileName;
 *   - Name:
 *       std::string Name;
 *   - Is cube:
 *       BOOL IsCube;
 * RETURNS:
 *   (texture &) self reference.
 */
mzgl::texture & mzgl::texture::AddFromFile( const CHAR *FileName, std::string Name, BOOL IsCube )
{
  FILE *F;

  IsCubeMap = IsCube;
  if (!IsCube)
  {
    if ((F = fopen(FileName, "rb")) != NULL)
    {
      INT w = 0, h = 0;
      BYTE *mem;

      fread(&w, 2, 1, F);
      fread(&h, 2, 1, F);
      if ((mem = (BYTE *)malloc(w * h * 3)) != NULL)
      {

        fread(mem, 3, w * h, F);

        AddImg(Name, w, h, 3, mem);

        free(mem);
      }
      fclose(F);
    }
  }
  else
  {
    AddCubeMap(FileName, Name);
  }
  return *this;
} /* End of 'AddFromFile' function */


/* Texture add from file function.
 * ARGUMENTS:
 *   - File name:
 *       const CHAR *FileName;
 *   - Name:
 *       std::string Name;
 *   - Is cube:
 *       BOOL IsCube;
 * RETURNS:
 *   (texture &) self reference.
 */
mzgl::texture & mzgl::texture::AddFromFileAll( std::string FName, std::string Name )
{
  std::vector<DWORD> mem = LoadAll(FName);

  AddImg(Name, W, H, 4, mem.data());

  return *this;
} /* End of 'AddFromFile' function */

/* Texture add fmt function.
 * ARGUMENTS:
 *   - Name:
 *       std::string Name;
 *   - Width:
 *       INT W;
 *   - Height:
 *       INT H;
 *   - Type:
 *       INT// glType;
 * RETURNS:
 *   (texture &) self reference.
 */
mzgl::texture & mzgl::texture::AddFmt( std::string Name, INT W, INT H, INT glType )
{
  /* Setup OpenGL texture */
 // glGenTextures(1, &TexId);
 // glBindTexture(GL_TEXTURE_2D, TexId);

 // glTexStorage2D(GL_TEXTURE_2D, 1,// glType, W, H);

 // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_MIN_FILTER,// gl_NEAREST);
 // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_MAG_FILTER,// gl_NEAREST);


 // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_WRAP_S,// gl_REPEAT);
 // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_WRAP_T,// gl_REPEAT);

 // glBindTexture(GL_TEXTURE_2D, 0);

  this->W = W;
  this->H = H;
  this->IsCubeMap = FALSE;
  return *this;
} /* End of 'AddFmt' function */

/* Free texture function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::texture::Free( VOID )
{
} /* End of 'mzgl::texture::Free' function */

/* END OF 'texture.cpp' FILE */