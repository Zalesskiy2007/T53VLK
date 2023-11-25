/* FILE NAME   : material.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Material module.
 */

#include "mzgl.h"

/* Material creation function.
 * ARGUMENTS:
 *   - material name:
 *       const std::string &MtlName;
 *   - ambient coefficient:
 *       vec3 Ka;
 *   - diffuse coefficient:
 *       vec3 Kd;
 *   - specular coefficient:
 *       vec3 Ks;
 *   - Phong coefficient - shiness:
 *       FLT Ph;
 *   - transparency factor:
 *       FLT Trans;
 *   - pointer to material pattern:
 *       material_pattern *NewNamePat;
 * RETURNS:
 *   (material &) self reference.
 */
mzgl::material & mzgl::material::Create( const std::string &MtlName, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, 
                                         FLT Ph, FLT Trans, material_pattern *NewMtlPat )
{
  MtlPat = NewMtlPat;
  MtlData.Ka4 = vec4(Ka);
  MtlData.KdTrans = vec4(Kd, Trans);
  MtlData.KsPh = vec4(Ks, Ph);
  for (INT i = 0; i < 8; i++)
    MtlData.Tex[i] = nullptr;

  MtlData.CntOfTex = 0;

  return *this;
} /* End of 'mzgl::material::Create' function */

/* Apply material function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (INT) new shader number.
 */
INT mzgl::material::Apply( VOID )
{
  INT prg = 0;//MtlPat->Shd->ProgId, loc;

 // glUseProgram(prg);
  if (prg == 0)
    return 0;
  
  //if ((loc = glGetUniformLocation(prg, "MtlKa4")) != -1)
   // glUniform4fv(loc, 1, &MtlData.Ka4[0]);
  //if ((loc = glGetUniformLocation(prg, "MtlKdTrans")) != -1)
   // glUniform4fv(loc, 1, &MtlData.KdTrans[0]);
  //if ((loc = glGetUniformLocation(prg, "MtlKsPh")) != -1)
   // glUniform4fv(loc, 1, &MtlData.KsPh[0]);

  if (MtlData.Tex[0] != nullptr && MtlData.Tex[0]->IsCubeMap)
  {
   // glActiveTexture(GL_TEXTURE0);
   // glBindTexture(GL_TEXTURE_CUBE_MAP, MtlData.Tex[0]->TexId);
  }
  else
    for (INT i = 0; i < 8; i++)
    {
      if (MtlData.Tex[i] != nullptr)
      {
       // glActiveTexture(GL_TEXTURE0 + i);
       // glBindTexture(GL_TEXTURE_2D, MtlData.Tex[i]->TexId);
        if (i < 4)
          MtlData.IsTexture0123[i] = 1;
        else
          MtlData.IsTexture4567[i - 4] = 1;
      }
      else
      {
        if (i < 4)
          MtlData.IsTexture0123[i] = 0;
        else
          MtlData.IsTexture4567[i - 4] = 0;
      }
    }

  //if ((loc = glGetUniformLocation(prg, "IsTexture0123")) != -1)
   // glUniform4fv(loc, 1, &MtlData.IsTexture0123[0]);
  //if ((loc = glGetUniformLocation(prg, "IsTexture4567")) != -1)
   // glUniform4fv(loc, 1, &MtlData.IsTexture4567[0]);

  return prg;
} /* End of 'mzgl::material::Apply' function */

/* Add texture function.
 * ARGUMENTS:
 *   - pointer to texture:
 *       texture *Txt;
 * RETURNS: None.
 */
VOID mzgl::material::AddTexture( mzgl::texture *Txt )
{
  if (MtlData.CntOfTex < 8)
  {
    MtlData.Tex[MtlData.CntOfTex] = Txt;
    MtlData.CntOfTex += 1;
  }
} /* End of 'AddTexture' function */

/* Free material function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::material::Free( VOID )
{
} /* End of 'mzgl::material::Free' function */

/* END OF 'material.cpp' FILE */