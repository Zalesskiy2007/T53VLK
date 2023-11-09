/* FILE NAME   : mth_camera.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Math module.
 *               3D math camera implementation module.
 */

#ifndef __mth_camera_h_
#define __mth_camera_h_

#include "mth_def.h"

 /* Math namespace */
namespace mth
{
  /* Camera representation type */
  template<typename Type>
  class camera
  {
  public:
    vec3<Type>
      Loc,               // Camera location
      Dir,               // Camera forward direction
      Up,                // Camera up direction
      Right,             // Camera right direction
      At;                // Camera look at direction

    Type
      ProjSize,          // Projection plane fit square
      ProjDist,          // Distance to projection plane from viewer (near)
      ProjFarClip,       // Distance to projection far clip plane (far) 
      Wp, Hp;            // Projection plane size

    INT FrameW, FrameH;  // Camera frame size

    matr<Type>
      MatrView,          // View coordinate system matrix
      MatrProj,          // Projection coordinate system matrix
      MatrVP;            // Stored (View * Proj) matrix

    /* Class constructor.
     * Set camera parameters function.
     * ARGUMENTS:
     *   - parameters to look:
     *       vec3<Type> loc, At, Up;
     */
    camera(VOID) :
      Loc(0, 1.3, 4), At(0, 0, 0), FrameW(700), FrameH(700),
      ProjDist(0.1), ProjSize(0.1), ProjFarClip(3000),
      Up(0, 1, 0), Hp(0.1), Wp(0.1)
    {
      CamSet(Loc, At, Up);
      ProjSet();
    } /* End of 'camera' constructor */

    /* Render set camera function.
     * ARGUMENTS:
     *   - camera parametrs to look:
     *       const vec3<Type> loc, At, Up;
     * RETURNS: None.
     */
    VOID CamSet(const vec3<Type>& CamLoc, const vec3<Type>& CamAt, const vec3<Type>& CamUp)
    {
      MatrView = matr<Type>::View(CamLoc, CamAt, CamUp);
      MatrVP = MatrView * MatrProj;

      Loc = CamLoc;
      Dir = vec3<Type>(-MatrView.A[0][2],
        -MatrView.A[1][2],
        -MatrView.A[2][2]);
      Up = vec3<Type>(MatrView.A[0][1],
        MatrView.A[1][1],
        MatrView.A[2][1]);
      Right = vec3<Type>(MatrView.A[0][0],
        MatrView.A[1][0],
        MatrView.A[2][0]);
    } /* End of 'CamSet' function */

    /* Reset projection function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID ProjSet(VOID)
    {
      DBL rx, ry;

      rx = ry = ProjSize;

      if (FrameW > FrameH)
        rx *= (DBL)FrameW / FrameH;
      else
        ry *= (DBL)FrameH / FrameW;

      MatrProj =
        matr<Type>::Frustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
          ProjDist, ProjFarClip);
      MatrVP = MatrView * MatrProj;
    } /* End of 'ProjSet' function */
  }; /* End of 'camera' class */
} /* end of 'mth' namespace */

#endif /* __mth_camera_h_ */

/* END OF 'mth_camera.h' FILE */