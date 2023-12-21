/* FILE NAME   : control.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Control unit.
 */

#include "mzgl.h"

/* Control unit representation type */
class control : public mzgl::unit
{
  mzgl::font *fnt;
  BOOL DrawMode;
public:
  /* Control constructor */
  control(mzgl::anim *MyAnim)
  {
  //  fnt = MyAnim->FntCreate("bin/fonts/Book.g3df", "TestFnt");
    DrawMode = TRUE;
  } /* End of 'control' constructor */

  /* Virtual render function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Render(mzgl::anim* Ani) override
  {
    //if (!Ani->IsShading)
    //{
      //CHAR Dest[400] = "";
      //sprintf(Dest, "MZ2 FPS: %f\nQ - %s mode", Ani->FPS, DrawMode ? "bones" : "mesh");
      //fnt->FntDraw(Dest);
   // }
  } /* End of 'Render' function */

  /* Virtual response function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Response(mzgl::anim* Ani) override
  {
    Ani->KeyboardResponse();
    Ani->MouseResponse();
    if (Ani->KeysClick['Q'] || Ani->KeysClick['q'])
      DrawMode = !DrawMode;

    if (Ani->Keys[VK_CONTROL] && Ani->Keys['F'])
    {
      Ani->Camera.CamSet(mzgl::vec3(8, 8, 8), mzgl::vec3(0), mzgl::vec3(0, 1, 0));
    }
    if (Ani->Keys[VK_CONTROL])
    {
      FLT
        Dist = !(Ani->Camera.At - Ani->Camera.Loc),
        cosT = (Ani->Camera.Loc[1] - Ani->Camera.At[1]) / Dist,
        sinT = sqrt(1 - cosT * cosT),
        plen = Dist * sinT,
        cosP = (Ani->Camera.Loc[2] - Ani->Camera.At[2]) / plen,
        sinP = (Ani->Camera.Loc[0] - Ani->Camera.At[0]) / plen,
        Azimuth = R2D(atan2(sinP, cosP)),
        Elevator = R2D(atan2(sinT, cosT));

      Azimuth += Ani->GlobalDeltaTime * 1 *
      (-300 * Ani->Keys[VK_LBUTTON] * Ani->Mdx +
       -102 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]));

      Elevator += Ani->GlobalDeltaTime * 1 *
        (-300 * Ani->Keys[VK_LBUTTON] * Ani->Mdy +
         -102 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));

      if (Elevator < 0.08)
        Elevator = 0.08;
      else if (Elevator > 178.90)
        Elevator = 178.90;

      Dist += Ani->GlobalDeltaTime * (1 + Ani->Keys[VK_SHIFT] * 28) *
        (-47 * Ani->Mdz +
          53 * (Ani->Keys['s'] - Ani->Keys['w']) +
          53 * (Ani->Keys['S'] - Ani->Keys['W']) +
          53 * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));
      if (Dist < 0.1)
        Dist = 0.1;

      mzgl::vec3 newAt = Ani->Camera.At +
          Ani->Camera.Right * (0.102 * (Ani->Keys['d'] - Ani->Keys['a']) +
          0.102 * (Ani->Keys['D'] - Ani->Keys['A'])) + 
          Ani->Camera.Up * 0.08 * (Ani->Keys[VK_HOME] - Ani->Keys[VK_END]);

      mzgl::vec3 newLoc = Ani->Camera.Loc +
                        Ani->Camera.Right * (0.102 * (Ani->Keys['d'] - Ani->Keys['a']) +
                        0.102 * (Ani->Keys['D'] - Ani->Keys['A'])) +
                        Ani->Camera.Up * 0.08 * (Ani->Keys[VK_HOME] - Ani->Keys[VK_END]);       

    Ani->Camera.CamSet((mzgl::matr().RotateX(Elevator) *
                  mzgl::matr().RotateY(Azimuth) *
                  mzgl::matr().Translate(newAt)).TransformPoint(mzgl::vec3(0, Dist, 0)),
                  newAt,
                  mzgl::vec3(0, 1, 0));
    }
  } /* End of 'Response' function */
}; /* End of 'control' class */

static mzgl::anim::unit_register<control> _("Control unit");

/* END OF 'control.cpp' FILE */