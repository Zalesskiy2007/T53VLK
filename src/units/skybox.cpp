/* FILE NAME   : skybox.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Skybox unit.
 */

#include "mzgl.h"

/* Skybox unit representation type */
class skybox : public mzgl::unit
{
public:
  mzgl::prim *pr;

  /* Skybox constructor */
  skybox(mzgl::anim *MyAnim)
  {
    mzgl::material_pattern *MtlP = MyAnim->MtlPatCreate("SkyP", 16, "skybox");
    mzgl::material *Mtl = MyAnim->MtlCreate("SkyMtl", mzgl::vec3(0.3, 0, 0), 
                                                                    mzgl::vec3(1, 0, 0), mzgl::vec3(1, 1, 1),
                                                                    32, 1, MtlP);
    mzgl::texture *Txt = MyAnim->TxtLoad("bin/textures/sky2", "SkyTxt", TRUE);
    Mtl->AddTexture(Txt);
    mzgl::topology::base<mzgl::vertex::std> topo;
    topo.Type = mzgl::prim_type::TRIMESH;

    mzgl::vertex::std P[8];

    P[0].P = mzgl::vec3(-1, 1, -1);
    P[0].C = mzgl::vec4(1, 1, 1, 1);
    topo.V.push_back(P[0]);

    P[1].P = mzgl::vec3(1, 1, -1);
    P[1].C = mzgl::vec4(1, 1, 0, 1);
    topo.V.push_back(P[1]);

    P[2].P = mzgl::vec3(1, -1, -1);
    P[2].C = mzgl::vec4(1, 0, 1, 1);
    topo.V.push_back(P[2]);

    P[3].P = mzgl::vec3(-1, -1, -1);
    P[3].C = mzgl::vec4(1, 0, 0, 1);
    topo.V.push_back(P[3]);

    P[4].P = mzgl::vec3(-1, 1, 1);
    P[4].C = mzgl::vec4(0, 1, 1, 1);
    topo.V.push_back(P[4]);

    P[5].P = mzgl::vec3(1, 1, 1);
    P[5].C = mzgl::vec4(0, 1, 0, 1);
    topo.V.push_back(P[5]);

    P[6].P = mzgl::vec3(1, -1, 1);
    P[6].C = mzgl::vec4(0, 0, 1, 1);
    topo.V.push_back(P[6]);

    P[7].P = mzgl::vec3(-1, -1, 1);
    P[7].C = mzgl::vec4(0, 0, 0, 1);
    topo.V.push_back(P[7]);

    topo.I = {
         0, 1, 2,
         0, 2, 3,
         2, 1, 5,
         2, 5, 6,
         3, 2, 6,
         3, 6, 7,
         0, 3, 7,
         0, 7, 4,
         1, 0, 4,
         1, 4, 5,
         6, 5, 4,
         6, 4, 7};

    pr = MyAnim->PrimCreate<mzgl::vertex::std>(Mtl, topo);
  } /* End of 'skybox' constructor */

  /* Virtual render function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Render(mzgl::anim* Ani) override
  {
    if (!Ani->IsShading)
      Ani->Draw(pr);
  } /* End of 'Render' function */

  /* Virtual response function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Response(mzgl::anim* Ani) override
  {
  } /* End of 'Response' function */
}; /* End of skybox class */

static mzgl::anim::unit_register<skybox> _("Skybox unit");

/* END OF 'skybox.cpp' FILE */