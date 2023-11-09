/* FILE NAME   : light.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               light module.
 */

#include "mzgl.h"

/* Light init function.
 * ARGUMENTS:
 *   - Name:
 *       std::string Name;
 * RETURNS:
 *   (light &) self reference.
 */
mzgl::light & mzgl::light::LightInit( std::string Name )
{
  LightDir = vec3(-5, 8, -5).Normalize();
  LightColor = vec3(1, 1, 1);

 // glGenFramebuffers(1, &ShadowFBO);
 // glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);

  //ShadowTex = Rnd->TxtLoadFmt(Name + "Shadow Map", SHADOW_MAP_SIZE, SHADOW_MAP_SIZE,// gl_DEPTH_COMPONENT24);
 // glFramebufferTexture2D(GL_FRAMEBUFFER,// gl_DEPTH_ATTACHMENT,// gl_TEXTURE_2D, ShadowTex->TexId, 0);

 // glBindFramebuffer(GL_FRAMEBUFFER, 0);
 // glActiveTexture(GL_TEXTURE0 + 8);
 // glBindTexture(GL_TEXTURE_2D, ShadowTex->TexId);

  return *this;
} /* End of 'LightInit' function */

/* Light shadow function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::light::LightShadow( VOID )
{
  FLT size = 100, far_dist = 300, clear_depth = 1;
  vec3 sclc = Rnd->Camera.Loc, scat = Rnd->Camera.At, scup = Rnd->Camera.Up;
  matr scp = Rnd->Camera.MatrProj;

  Rnd->Camera.MatrProj = matr().Ortho(-size, size, -size, size, -size * 8, far_dist);
  Rnd->Camera.CamSet(Rnd->Camera.At, Rnd->Camera.At - LightDir, vec3(0, 1, 0));
  ShadowMatr = Rnd->Camera.MatrVP;

 // glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);

 // glClearBufferfv(GL_DEPTH, 0, &clear_depth);
 // glViewport(0, 0, SHADOW_MAP_SIZE, SHADOW_MAP_SIZE);

 // glEnable(GL_POLYGON_OFFSET_FILL);
 // glPolygonOffset(4, 4);
 // glEnable(GL_CULL_FACE);
 // glCullFace(GL_FRONT);
  Rnd->IsShading = TRUE;

  for (INT i = 0; i < Rnd->PrimsToDraw.size(); i++)
    Rnd->Draw(Rnd->PrimsToDraw[i], Rnd->MatrsToDraw[i]);

  Rnd->IsShading = FALSE;
 // glDisable(GL_CULL_FACE);
 // glDisable(GL_POLYGON_OFFSET_FILL);
 // glFinish();

 // glBindFramebuffer(GL_FRAMEBUFFER, 0);

  Rnd->Camera.MatrProj = scp;
  Rnd->Camera.CamSet(sclc, scat, scup);
} /* End of 'LightShadow' function */

/* Free light function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::light::Free( VOID )
{
 // glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);
 // glFramebufferTexture2D(GL_FRAMEBUFFER,// gl_DEPTH_ATTACHMENT,// gl_TEXTURE_2D, 0, 0);
 // glBindFramebuffer(GL_FRAMEBUFFER, 0);
 // glDeleteFramebuffers(1, &ShadowFBO);
} /* End of 'mzgl::light::Free' function */

/* END OF 'light.cpp' FILE */