/* FILE NAME   : render.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Render system module.
 *               Render (*.cpp) file module.
 */

#include "mzgl.h"
#include <cstdio>
#include <filesystem>
#include <sstream>

/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *      UINT Source;
 *   - error type:
 *      UINT Type;
 *   - error message id:
 *      UINT Id,
 *   - message severity:
 *      UINT severity,
 *   - message text length:
 *      INT Length,
 *   - message text:
 *      CHAR *Message,
 *   - user addon parameters pointer:
 *      VOID *UserParam;
 * RETURNS: None.
 */
/* VOID APIENTRY// glDebugOutput(UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message, const VOID *UserParam )
{
  std::string Buf;

  if (Id == 131169 || Id == 131185 || Id == 131218 || Id == 131204)
    return;
  Buf = "Debug message " + std::string(Message) + "\n";

  switch (Source)
  {
  case// gl_DEBUG_SOURCE_API:
    Buf += "Source: API\n";
    break;
  case// gl_DEBUG_SOURCE_WINDOW_SYSTEM:
    Buf += "Source: Window System\n";
    break;
  case// gl_DEBUG_SOURCE_SHADER_COMPILER:
    Buf += "Source: Shader Compiler\n";
    break;
  case// gl_DEBUG_SOURCE_THIRD_PARTY:
    Buf += "Source: Third Party\n";
    break;
  case// gl_DEBUG_SOURCE_APPLICATION:
    Buf += "Source: Application";
    break;
  case// gl_DEBUG_SOURCE_OTHER:
    Buf += "Source: Other";
    break;
  }
  Buf += "\n";

  switch (Type)
  {
  case// gl_DEBUG_TYPE_ERROR:
    Buf += "Type: Error";
    break;
  case// gl_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
    Buf += "Type: Deprecated Behaviour";
    break;
  case// gl_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
    Buf += "Type: Undefined Behaviour";
    break; 
  case// gl_DEBUG_TYPE_PORTABILITY:
    Buf += "Type: Portability";
    break;
  case// gl_DEBUG_TYPE_PERFORMANCE:
    Buf += "Type: Performance";
    break;
  case// gl_DEBUG_TYPE_MARKER:
    Buf += "Type: Marker";
    break;
  case// gl_DEBUG_TYPE_PUSH_GROUP:
    Buf += "Type: Push Group";
    break;
  case// gl_DEBUG_TYPE_POP_GROUP:
    Buf += "Type: Pop Group";
    break;
  case// gl_DEBUG_TYPE_OTHER:
    Buf += "Type: Other";
    break;
  }
  Buf += "\n";

  switch (Severity)
  {
  case// gl_DEBUG_SEVERITY_HIGH:
    Buf += "Severity: high";
    break;
  case// gl_DEBUG_SEVERITY_MEDIUM:
    Buf += "Severity: medium";
    break;
  case// gl_DEBUG_SEVERITY_LOW:
    Buf += "Severity: low";
    break;
  case// gl_DEBUG_SEVERITY_NOTIFICATION:
    Buf += "Severity: notification";
    break;
  }
  Buf += "\n\n";

  OutputDebugString(Buf.c_str());
} */

 /* Render system initialization function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID mzgl::render::Init(VOID)
{
  INT i;
  //PIXELFORMATDESCRIPTOR pfd = { 0 };
  UINT nums;
  //HGLRC hRC;
  //INT PixelAttribs[] =
  //{
  //  WGL_DRAW_TO_WINDOW_ARB, TRUE,
  //  WGL_SUPPORT_OPENGL_ARB, TRUE,
  //  WGL_DOUBLE_BUFFER_ARB, TRUE,
  //  WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
  //  WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
  //  WGL_COLOR_BITS_ARB, 32,
  //  WGL_DEPTH_BITS_ARB, 32,
  //  0
  //};
  //INT ContextAttribs[] =
  //{
  //  WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
  //  WGL_CONTEXT_MINOR_VERSION_ARB, 6,
  //  WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_COMPATIBILITY_PROFILE_BIT_ARB,
  //  /* WGL_CONTEXT_CORE_PROFILE_BIT_ARB, */
  //  0
  //};

  /* Prepare frame compatible device context */
  hDC = GetDC(hWnd);

  /* OpenGL init: pixel format setup */
  //pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  //pfd.nVersion = 1;
  //pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  //pfd.cColorBits = 32;
  //pfd.cDepthBits = 32;
  //i = ChoosePixelFormat(hDC, &pfd);
  //DescribePixelFormat(hDC, i, sizeof(pfd), &pfd);
  //SetPixelFormat(hDC, i, &pfd);
  //
  ///* OpenGL init: rendering context setup */
  //hGLRC = wglCreateContext(hDC);
  //wglMakeCurrent(hDC, hGLRC);
  //
  ///*// glEW initialization */
  //if (glewInit() !=// glEW_OK)
  //{
  //  IsInit = FALSE;
  //  exit(0);
  //}
  ///* Enable a new OpenGL profile support */
  //wglChoosePixelFormatARB(hDC, PixelAttribs, nullptr, 1, &i, &nums);
  //hRC = wglCreateContextAttribsARB(hDC, nullptr, ContextAttribs);
  //
  //wglMakeCurrent(nullptr, nullptr);
  //wglDeleteContext(hGLRC);
  //
  //hGLRC = hRC;
  //wglMakeCurrent(hDC, hGLRC);
  //
  //#ifndef NDEBUG
  //  OutputDebugString(reinterpret_cast<LPCSTR>(glGetString(GL_VERSION)));
  //  OutputDebugString("\n");
  //  OutputDebugString(reinterpret_cast<LPCSTR>(glGetString(GL_VENDOR)));
  //  OutputDebugString("\n");
  //  OutputDebugString(reinterpret_cast<LPCSTR>(glGetString(GL_RENDERER)));
  //  OutputDebugString("\n");
  //
  // // glEnable(GL_DEBUG_OUTPUT);
  // // glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  // // glDebugMessageCallback(glDebugOutput, NULL);
  // // glDebugMessageControl(GL_DONT_CARE,// gl_DONT_CARE,// gl_DONT_CARE,
  //    0, nullptr,// gl_TRUE);
  //#endif /* NDEBUG */
  //
  ///* Render parameters setup */
  //glClearColor(0.30, 0.47, 0.8, 1);
  //glEnable(GL_DEPTH_TEST);
  //
  //glEnable(GL_PRIMITIVE_RESTART);
  //glPrimitiveRestartIndex(-1);
  //
  //glEnable(GL_BLEND);
  //glBlendFunc(GL_SRC_ALPHA,// gl_ONE_MINUS_SRC_ALPHA);

  /* Set camera */
  Camera.ProjSize = 0.1;
  Camera.ProjDist = Camera.ProjSize;
  Camera.ProjFarClip = 3000;
  Camera.FrameW = 300;
  Camera.FrameH = 300;

  Camera.CamSet(vec3(0, 10, 20), vec3(0), vec3(0, 1, 0));
  CHAR Buf[_MAX_PATH];
  GetCurrentDirectory(sizeof(Buf), Buf);
  Path = Buf;

  Trg = TrgCreate("FBO");
  Lgh = LghCreate("Shadows");

  IsInit = TRUE;
} /* End of 'mzgl::render::Init' function */

/* Render system close (deinitialization) function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::render::Close(VOID)
{
  //wglMakeCurrent(nullptr, nullptr);
  //wglDeleteContext(hGLRC);
  ReleaseDC(hWnd, hDC);
} /* End of 'mzgl::render::Close' function */

/* Render system resize function.
 * ARGUMENTS:
 *   - window new size:
 *       INT NewW, INT NewH;
 * RETURNS: None.
 */
VOID mzgl::render::Resize(INT NewW, INT NewH)
{
  //glViewport(0, 0, NewW, NewH);

  /* Save size */
  Camera.FrameH = NewH;
  Camera.FrameW = NewW;

  Trg->TargetResize(NewW, NewH);
  /* Reset projection */
  Camera.ProjSet();
} /* End of 'mzgl::render::Resize' function */

/* Start render frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::render::FrameStart(VOID)
{
  //glClear(GL_COLOR_BUFFER_BIT |// gl_DEPTH_BUFFER_BIT);
  PrimsToDraw.clear();
  MatrsToDraw.clear();

  Trg->TargetStart();
} /* End of 'mzgl::render::FrameStart' function */

/* Finish render frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::render::FrameEnd(VOID)
{
  Trg->TargetEnd();
  SwapBuffers(hDC);
} /* End of 'mzgl::render::FrameEnd' function */

/* Primitive load function.
* ARGUMENTS:
*   - Filename:
*       const CHAR *Fn;
*   - Material:
*       material *Mat;
* RETURNS:
*   (prim *) created primitive;
*/
mzgl::topology::base<mzgl::vertex::std> mzgl::render::LoadModel( const CHAR *Fn )
{
  static CHAR Buf[10000];
  INT nv, nf, size, i;
  std::vector<vertex::std> V;
  std::vector<INT> Ind;
  FILE *F;

  if ((F = fopen(Fn, "r")) == NULL)
    return topology::base<mzgl::vertex::std>();

  nv = nf = 0;
  while (fgets(Buf, sizeof(Buf) - 1, F) != NULL)
  {
    if (Buf[0] == 'v' && Buf[1] == ' ')
    {
      DBL x, y, z;

      sscanf(Buf + 2, "%lf%lf%lf", &x, &y, &z);

      vertex::std p;
      p.C = vec4(rand() / (FLT)RAND_MAX, rand() / (FLT)RAND_MAX, rand() / (FLT)RAND_MAX, 1);
      p.P = vec3(x, y, z);
      V.push_back(p);
      nv++;
    }
    else if (Buf[0] == 'f' && Buf[1] == ' ')
    {
      INT c1 = 0, c0 = 0, c, n = 0;
      CHAR *ptr = Buf + 2, old = ' ';

      while (*ptr != 0)
      {
        if (*ptr != ' ' && old == ' ')
        {
          sscanf(ptr, "%d", &c);
          if (c < 0)
            c = nv + c;
          else
            c--;
          if (n == 0)
            c0 = c;
          else if (n == 1)
            c1 = c;
          else
          {
            Ind.push_back(c0);
            nf++;
            Ind.push_back(c1);
            nf++;
            Ind.push_back(c);
            nf++;
            c1 = c;
          }
          n++;
        }
        old = *ptr++;
      }
    }
  }


  for (i = 0; i < nf; i += 3)
    {
      vec3
        p0 = V[Ind[i]].P,
        p1 = V[Ind[i + 1]].P,
        p2 = V[Ind[i + 2]].P,
        N = ((p1 - p0) % (p2 - p0)).Normalize();

      V[Ind[i]].N = (V[Ind[i]].N + N);
      V[Ind[i + 1]].N = (V[Ind[i + 1]].N + N);
      V[Ind[i + 2]].N = (V[Ind[i + 2]].N + N);
    }

  for (i = 0; i < nv; i++)
      V[i].N = (V[i].N).Normalize();

  fclose(F);
  topology::base<mzgl::vertex::std> topo;
  topo.Type = mzgl::prim_type::TRIMESH;
  topo.V = V;
  topo.I = Ind;

  return topo;
} /* End of 'LoadModel' function */

/* Primitive draw function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       prim *Pr;
 *   - transformation matrix:
 *       const matr &World;
 * RETURNS: None.
 */
VOID mzgl::render::Draw(const prim* Pr, const matr& World)
{
  Pr->Mtl->MtlPat->Shd->Update();
  matr
    w = Pr->Transform * World,
    winw = w.Inverse().Transpose(),
    wp = Camera.MatrProj,
    wv = Camera.MatrView,
    wvp = w * Camera.MatrVP;

  //INT
  //  RndProgId, loc,
  // // gl_prim_type = Pr->Type == prim_type::LINES ?// gl_LINES :
  //  Pr->Type == prim_type::TRIMESH ?// gl_TRIANGLES :
  //  Pr->Type == prim_type::STRIP ?// gl_TRIANGLE_STRIP :
  // // gl_POINTS;
  //Prim_data.MatrWVP = wvp;
  //Prim_data.MatrW = w;
  //Prim_data.MatrWInvTrans = winw;
  //
  //RndProgId = Pr->Mtl->Apply();
  //if ((loc =// glGetUniformLocation(RndProgId, "MatrWvp")) != -1)
  // // glUniformMatrix4fv(loc, 1,// gl_FALSE, wvp.A[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "MatrWorld")) != -1)
  // // glUniformMatrix4fv(loc, 1,// gl_FALSE, w.A[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "MatrTrans")) != -1)
  // // glUniformMatrix4fv(loc, 1,// gl_FALSE, Pr->Transform.A[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "MatrShadow")) != -1)
  // // glUniformMatrix4fv(loc, 1,// gl_FALSE, Lgh->ShadowMatr.A[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "CamLoc")) != -1)
  // // glUniform3fv(loc, 1, &Camera.Loc[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "CamDir")) != -1)
  // // glUniform3fv(loc, 1, &Camera.Dir[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "CamUp")) != -1)
  // // glUniform3fv(loc, 1, &Camera.Up[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "CamRight")) != -1)
  // // glUniform3fv(loc, 1, &Camera.Right[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "LightDir")) != -1)
  // // glUniform3fv(loc, 1, &Lgh->LightDir[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "LightColor")) != -1)
  // // glUniform3fv(loc, 1, &Lgh->LightColor[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "FrameW")) != -1)
  // // glUniform1f(loc, Camera.FrameW);
  //if ((loc =// glGetUniformLocation(RndProgId, "FrameH")) != -1)
  // // glUniform1f(loc, Camera.FrameH);
  //if ((loc =// glGetUniformLocation(RndProgId, "ProjDist")) != -1)
  // // glUniform1f(loc, Camera.ProjDist);
  //if ((loc =// glGetUniformLocation(RndProgId, "ProjSize")) != -1)
  // // glUniform1f(loc, Camera.ProjSize);
  //if ((loc =// glGetUniformLocation(RndProgId, "Time")) != -1)
  // // glUniform1f(loc, Time);
  //
  //glBindVertexArray(Pr->VA);
  //if (Pr->IBuf != 0)
  //{
  // // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
  // // glDrawElements(gl_prim_type, Pr->NumOfElements,// gl_UNSIGNED_INT, nullptr);
  // // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  //}
  //else
  // // glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
  //glBindVertexArray(0);
  //glUseProgram(0);
} /* End of 'mzgl::render::Draw' function */

/* END OF 'render.cpp' FILE */