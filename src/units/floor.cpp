/* FILE NAME   : floor.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Floor unit.
 */

#include "mzgl.h"

/* floor_unit unit representation type */
class floor_unit : public mzgl::unit
{
public:
  mzgl::prim *pr;
  /* floor_unit constructor */
  floor_unit(mzgl::anim *MyAnim)
  {
    mzgl::material_pattern *MtlP = MyAnim->MtlPatCreate("MtlP", 16, "materials");
    mzgl::material *Mtl = MyAnim->MtlCreate("Mtl", mzgl::vec3(0.3, 0, 0), 
                                                                    mzgl::vec3(0.2, 0.2, 0.2), mzgl::vec3(1, 1, 1),
                                                                    1164, 1, MtlP);
    mzgl::texture *Txt = nullptr;//= MyAnim->TxtLoad("bin/textures/map.g24", "TestTxt", FALSE);
    Mtl->AddTexture(Txt);
    mzgl::topology::base<mzgl::vertex::std> topo;
    topo.Type = mzgl::prim_type::TRIMESH;

    mzgl::vertex::std P[4];

    P[0].P = mzgl::vec3(-15, -0.2, -15);
    P[0].C = mzgl::vec4(1, 1, 1, 1);
    P[0].N = mzgl::vec3(0, 1, 0);
    P[0].T = mzgl::vec2(0, 0);
    topo.V.push_back(P[0]);

    P[1].P = mzgl::vec3(15, -0.2, -15);
    P[1].C = mzgl::vec4(1, 1, 0, 1);
    P[1].N = mzgl::vec3(0, 1, 0);
    P[1].T = mzgl::vec2(1, 0);
    topo.V.push_back(P[1]);

    P[2].P = mzgl::vec3(-15, -0.2, 15);
    P[2].C = mzgl::vec4(1, 0, 1, 1);
    P[2].N = mzgl::vec3(0, 1, 0);
    P[2].T = mzgl::vec2(0, 1);
    topo.V.push_back(P[2]);

    P[3].P = mzgl::vec3(15, -0.2, 15);
    P[3].C = mzgl::vec4(1, 0, 0, 1);
    P[3].N = mzgl::vec3(0, 1, 0);
    P[3].T = mzgl::vec2(1, 1);
    topo.V.push_back(P[3]);

    topo.I = {0, 1, 2, 1, 2, 3};

    pr = MyAnim->PrimCreate<mzgl::vertex::std>(Mtl, topo);
  } /* End of 'floor_unit' constructor */

  /* Virtual render function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Render(mzgl::anim* Ani) override
  {
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
}; /* End of 'floor_unit' class */

static mzgl::anim::unit_register<floor_unit> _("Floor unit");

/* END OF 'floor.cpp' FILE */