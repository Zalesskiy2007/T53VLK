/* FILE NAME   : font.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               font module.
 */

#include "mzgl.h"
#include <cstdio>

/* Font load function.
 * ARGUMENTS:
 *   - File name:
 *       const CHAR *FileName;
 *   - Name:
 *       std::string Name;
 * RETURNS:
 *   (font &) self reference.
 */
mzgl::font & mzgl::font::FntLoad( const CHAR *FileName, std::string Name )
{
  FILE *F;
  INT i;
  DWORD Sign, W, H, *tex;
  struct tmpChars
  {
    vec3 P;
    vec2 T;
    vec3 N;
    vec4 C;
  } Chars[256][4];
  material *mtl;

  if ((F = fopen(FileName, "rb")) == NULL)
    return *this;

  fread(&Sign, 4, 1, F);
  if (Sign != *(DWORD *)"G3DF")
  {
    fclose(F);
    return *this;
  }

  fread(&inf, sizeof(font_info), 1, F);
  fread(Chars, sizeof(Chars), 1, F);
  fread(&W, 4, 1, F);
  fread(&H, 4, 1, F);
  if ((tex = (DWORD *)malloc(W * H * 4)) == NULL)
  {
    fclose(F);
    return *this;
  }
  fread(tex, 4, W * H, F);
  fclose(F);
  material_pattern *MtlP = Rnd->MtlPatCreate(Name, 16, "font");
  mtl = Rnd->MtlCreate(Name, vec3(0.3, 0, 0), 
                                               vec3(1, 0, 0), vec3(1, 1, 1),
                                               32, 1, MtlP);
  texture *t = nullptr;//Rnd->TxtLoadImg(Name, W, H, 4, tex);
  mtl->AddTexture(t);
  free(tex);
  this->Mtl = mtl;
  for (i = 0; i < 256; i++)
  {
    INT k;
    vertex::std v[4];

    topology::base<vertex::std> topo;
    topo.Type = prim_type::STRIP;

    for (k = 0; k < 4; k++)
    {
      v[k].P = Chars[i][k].P, v[k].T = Chars[i][k].T,
      v[k].N = vec3(0, 0, 1), v[k].C = vec4(1);

      topo.V.push_back(v[k]);
    }

    FntChars[i] = Rnd->PrimCreate<vertex::std>(this->Mtl, topo);
  }

  return *this;
} /* End of 'FntLoad' function */

/* Font draw function.
 * ARGUMENTS:
 *   - String to draw:
 *       CHAR *Str;
 * RETURNS: None.
 */
VOID mzgl::font::FntDraw( CHAR *Str )
{
  vec3 Pos = vec3(0);

  while (*Str != 0)
  {
    if (*Str == '\n')
      Pos[0] = 0, Pos[1] -= 1;
    else
      if (inf.AdvanceX[(UCHAR)*Str] != 0)
      {
        Rnd->Draw(FntChars[(UCHAR)*Str], matr().Translate(Pos));
        Pos[0] += inf.AdvanceX[(UCHAR)*Str];
      }

    Str++;
  }
} /* End of 'FntDraw' function */

/* Free font function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::font::Free( VOID )
{
  for (INT i = 0; i < 256; i++)
    FntChars[i]->Free();

  memset(FntChars, 0, sizeof(FntChars));
} /* End of 'mzgl::font::Free' function */

/* END OF 'font.cpp' FILE */