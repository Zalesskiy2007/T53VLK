/* FILE NAME   : target.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               target module.
 */

#include "mzgl.h"
#include <cstdio>
#include <string>

/* Target create function.
 * ARGUMENTS:
 *   - Width:
 *       INT W;
 *   - Height:
 *       INT H;
 * RETURNS:
 *   (target &) self reference.
 */
mzgl::target & mzgl::target::TargetCreate( INT W, INT H )
{
  INT i, status = 0;
  UINT DrawBuffer[RND_TARGETS];

  /* Create FBO */
 // glGenFramebuffers(1, &TargetId);
 // glBindFramebuffer(GL_FRAMEBUFFER, TargetId);

  /* Attach textures */
  //for (i = 0; i < RND_TARGETS; i++)
  //{
   // glDeleteTextures(1, &TargetScreen->Mtl->MtlData.Tex[i]->TexId);
   // glGenTextures(1, &TargetScreen->Mtl->MtlData.Tex[i]->TexId);
   // glBindTexture(GL_TEXTURE_2D, TargetScreen->Mtl->MtlData.Tex[i]->TexId);
   // glTexStorage2D(GL_TEXTURE_2D, 1,// gl_RGBA32F, W, H);
   // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_MIN_FILTER,// gl_NEAREST);
   // glTexParameteri(GL_TEXTURE_2D,// gl_TEXTURE_MAG_FILTER,// gl_NEAREST);
   // glBindTexture(GL_TEXTURE_2D, 0);

   // glFramebufferTexture2D(GL_FRAMEBUFFER,// gl_COLOR_ATTACHMENT0 + i,// gl_TEXTURE_2D, TargetScreen->Mtl->MtlData.Tex[i]->TexId, 0);
    //DrawBuffer[i] =// gl_COLOR_ATTACHMENT0 + i;
  //}
 // glDrawBuffers(RND_TARGETS, DrawBuffer);

  /* Attach render buffer (depth) */
 // glGenRenderbuffers(1, &RndBufId);
 // glBindRenderbuffer(GL_RENDERBUFFER, RndBufId);
 // glRenderbufferStorage(GL_RENDERBUFFER,// gl_DEPTH_COMPONENT, W, H);
 // glBindRenderbuffer(GL_RENDERBUFFER, 0);
 // glFramebufferRenderbuffer(GL_FRAMEBUFFER,// gl_DEPTH_ATTACHMENT,// gl_RENDERBUFFER, RndBufId);

  //status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  //if (status !=// gl_FRAMEBUFFER_COMPLETE)
  //{
    //OutputDebugString("\nError create frame buffer\n");
  //}
 // glBindFramebuffer(GL_FRAMEBUFFER, 0);

  return *this;
} /* End of 'TargetCreate' function */

/* Target init function.
 * ARGUMENTS:
 *   - Name:
 *       std::string Name;
 * RETURNS:
 *   (target &) self reference.
 */
mzgl::target & mzgl::target::TargetInit( std::string Name )
{
  material_pattern *MtlP = Rnd->MtlPatCreate(Name + " TrgMtlP", 16, "lights/ambient");
  material *mtl = Rnd->MtlCreate(Name + " Target material", mzgl::vec3(0.3, 0, 0), 
                                               mzgl::vec3(1, 0, 0), mzgl::vec3(1, 1, 1),
                                               32, 1, MtlP);
  INT i;

  for (i = 0; i < RND_TARGETS; i++)
  {
    //mtl->MtlData.Tex[i] = Rnd->TxtLoadFmt(Name + " Target" + std::to_string(i), Rnd->Camera.FrameW, Rnd->Camera.FrameH, gl_RGBA32F);
  }
  mzgl::topology::base<mzgl::vertex::std> topo;
  topo.Type = mzgl::prim_type::TRIMESH;
  mzgl::vertex::std P[4];

  P[0].P = mzgl::vec3(-1, 1, 0);
  P[0].C = mzgl::vec4(1, 1, 1, 1);
  P[0].N = (P[0].P - mzgl::vec3(0)).Normalizing();
  P[0].T = mzgl::vec2(0, 0);
  topo.V.push_back(P[0]);

  P[1].P = mzgl::vec3(1, 1, 0);
  P[1].C = mzgl::vec4(1, 1, 0, 1);
  P[1].N = (P[1].P - mzgl::vec3(0)).Normalizing();
  P[1].T = mzgl::vec2(1, 0);
  topo.V.push_back(P[1]);

  P[2].P = mzgl::vec3(-1, -1, 0);
  P[2].C = mzgl::vec4(1, 0, 1, 1);
  P[2].N = (P[2].P - mzgl::vec3(0)).Normalizing();
  P[2].T = mzgl::vec2(0, 1);
  topo.V.push_back(P[2]);

  P[3].P = mzgl::vec3(1, -1, 0);
  P[3].C = mzgl::vec4(1, 0, 0, 1);
  P[3].N = (P[3].P - mzgl::vec3(0)).Normalizing();
  P[3].T = mzgl::vec2(1, 1);
  topo.V.push_back(P[3]);

  topo.I = {0, 1, 2, 1, 2, 3};

  TargetScreen = Rnd->PrimCreate<mzgl::vertex::std>(mtl, topo);
  
  TargetCreate(Rnd->Camera.FrameW, Rnd->Camera.FrameH);

  return *this;
} /* End of 'TargetInit' function */

/* Target resize function.
 * ARGUMENTS:
 *   - Width:
 *       INT W;
 *   - Height:
 *       INT H;
 * RETURNS: None.
 */
VOID mzgl::target::TargetResize( INT W, INT H )
{
  Free();
  TargetCreate(W, H);
 // glViewport(0, 0, W, H);
} /* End of 'TargetResize' function */

/* Target start function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::target::TargetStart( VOID )
{
  INT i;
  FLT dv = 1;
  vec4 Col0 = {0.30, 0.47, 0.8, 1};

 // glBindFramebuffer(GL_FRAMEBUFFER, TargetId);
  //for (i = 0; i < RND_TARGETS; i++)
   // glClearBufferfv(GL_COLOR, i, &Col0[0]);
 // glClearBufferfv(GL_DEPTH, 0, &dv);
 // glViewport(0, 0, Rnd->Camera.FrameW, Rnd->Camera.FrameH);
} /* End of 'TargetStart' function */

/* Target end function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::target::TargetEnd( VOID )
{
  vec3 Col = {0, 0, 0};
  
  Rnd->Lgh->LightShadow();
 // glFinish();

 // glBindFramebuffer(GL_FRAMEBUFFER, 0);
 // glViewport(0, 0, Rnd->Camera.FrameW, Rnd->Camera.FrameH);

 // glClearBufferfv(GL_COLOR, 0, &Col[0]);
 // glDisable(GL_DEPTH_TEST);
  
 // glActiveTexture(GL_TEXTURE0 + 8);
 // glBindTexture(GL_TEXTURE_2D, Rnd->Lgh->ShadowTex->TexId);

 // glBlendFunc(GL_ONE,// gl_ONE);
  Rnd->Draw(TargetScreen);
 // glBlendFunc(GL_ONE,// gl_ZERO);

 // glEnable(GL_DEPTH_TEST);
 // glFinish();
} /* End of 'TargetEnd' function */

/* Free target function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::target::Free( VOID )
{
 // glBindFramebuffer(GL_FRAMEBUFFER, TargetId);
  /* Detach textures */
  //for (INT i = 0; i < RND_TARGETS; i++)
   // glFramebufferTexture2D(GL_FRAMEBUFFER,// gl_COLOR_ATTACHMENT0 + i,// gl_TEXTURE_2D, 0, 0);
  /* Detach render buffer (depth) */
 // glFramebufferRenderbuffer(GL_FRAMEBUFFER,// gl_DEPTH_ATTACHMENT,// gl_RENDERBUFFER, 0);
 // glDeleteRenderbuffers(1, &RndBufId);
 // glBindFramebuffer(GL_FRAMEBUFFER, 0);
 // glDeleteFramebuffers(1, &TargetId);
  TargetId = 0;
  RndBufId = 0;
} /* End of 'mzgl::target::Free' function */

/* END OF 'target.cpp' FILE */