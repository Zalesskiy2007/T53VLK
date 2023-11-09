/* FILE NAME   : model.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               model unit.
 */

#include "mzgl.h"

/* model_unit unit representation type */
class model_unit : public mzgl::unit
{
public:
  mzgl::model *mod;

  BOOL NeedToDraw;

  mzgl::prim *Node;

  FLT Size;

  /* model_unit constructor */
  model_unit(mzgl::anim *MyAnim)
  {
    mzgl::material_pattern *MtlP = MyAnim->MtlPatCreate("abc", 16, "dae");
    mzgl::material *Mtl = MyAnim->MtlCreate("abc2", mzgl::vec3(0.3, 0, 0), 
                                            mzgl::vec3(0.1, 0.1, 0.1), mzgl::vec3(1, 1, 1),
                                            32, 1, MtlP);


    /* WORKING IF MESH IS <TRIANGLES> TAG, NOT WORKING IF <POLYLIST> TAG */
    mod = MyAnim->ModelCreate("bin/models/ZebraLOD1.dae", "Test_Name", Mtl);
    mod->SetDAE(MyAnim);

    Size = 0.05;



    mzgl::material_pattern *MtlP2 = MyAnim->MtlPatCreate("abcNode", 16, "default");
    mzgl::material *Mtl2 = MyAnim->MtlCreate("abc2Node", mzgl::vec3(0.3, 0, 0), 
                                            mzgl::vec3(0.1, 0.1, 0.1), mzgl::vec3(1, 1, 1),
                                            32, 1, MtlP2);
    mzgl::topology::base<mzgl::vertex::std> topo;
    topo.Type = mzgl::prim_type::TRIMESH;
    mzgl::vertex::std P[8];

    FLT scale = 2;

    P[0].P = mzgl::vec3(-1, 1, -1) * scale;
    P[0].C = mzgl::vec4(1, 1, 1, 1);
    P[0].N = mzgl::vec3(0, 1, 0);
    P[0].T = mzgl::vec2(0, 0);
    topo.V.push_back(P[0]);
    P[1].P = mzgl::vec3(1, 1, -1) * scale;
    P[1].C = mzgl::vec4(1, 1, 0, 1);
    P[1].N = mzgl::vec3(0, 1, 0);
    P[1].T = mzgl::vec2(0, 1);
    topo.V.push_back(P[1]);
    P[2].P = mzgl::vec3(1, -1, -1) * scale;
    P[2].C = mzgl::vec4(1, 0, 1, 1);
    P[2].N = mzgl::vec3(0, 1, 0);
    P[2].T = mzgl::vec2(1, 0);
    topo.V.push_back(P[2]);
    P[3].P = mzgl::vec3(-1, -1, -1) * scale;
    P[3].C = mzgl::vec4(1, 0, 0, 1);
    P[3].N = mzgl::vec3(0, 1, 0);
    P[3].T = mzgl::vec2(1, 1);
    topo.V.push_back(P[3]);
    P[4].P = mzgl::vec3(-1, 1, 1) * scale;
    P[4].C = mzgl::vec4(0, 1, 1, 1);
    P[4].N = mzgl::vec3(0, 1, 0);
    topo.V.push_back(P[4]);
    P[5].P = mzgl::vec3(1, 1, 1) * scale;
    P[5].C = mzgl::vec4(0, 1, 0, 1);
    P[5].N = mzgl::vec3(0, 1, 0);
    topo.V.push_back(P[5]);
    P[6].P = mzgl::vec3(1, -1, 1) * scale;
    P[6].C = mzgl::vec4(0, 0, 1, 1);
    P[6].N = mzgl::vec3(0, 1, 0);
    topo.V.push_back(P[6]);
    P[7].P = mzgl::vec3(-1, -1, 1) * scale;
    P[7].C = mzgl::vec4(0, 0, 0, 1);
    P[7].N = mzgl::vec3(0, 1, 0);
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
    Node = MyAnim->PrimCreate<mzgl::vertex::std>(Mtl2, topo);
    NeedToDraw = TRUE;
  } /* End of 'model_unit' constructor */

  /* Virtual render function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Render(mzgl::anim* Ani) override
  {
    if (NeedToDraw)
      mod->DrawDAE(Ani, Size);
    else
      mod->DrawJoints(Node, Ani, mzgl::matr().Scale(mzgl::vec3(Size)));

  } /* End of 'Render' function */

  /* Virtual response function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Response(mzgl::anim* Ani) override
  {
    mod->ResponseTime(Ani->Time);

    if (Ani->KeysClick['Q'] || Ani->KeysClick['q'])
      NeedToDraw = !NeedToDraw;
  } /* End of 'Response' function */

  VOID ToDraw( mzgl::anim *Ani ) override
  {
    mod->ToDrawDAE(Ani, Size);
  }

}; /* End of 'model_unit' class */

static mzgl::anim::unit_register<model_unit> _("Model unit");

/* END OF 'model.cpp' FILE */