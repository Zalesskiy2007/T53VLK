/* FILE NAME   : test_unit.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Test unit.
 */

#include "mzgl.h"

/* Test unit representation type */
class test_unit : public mzgl::unit
{
public:
  mzgl::prim *pr;

  /* Test unit constructor */
  test_unit(mzgl::anim *MyAnim)
  {
    //mzgl::material_pattern *MtlP = MyAnim->MtlPatCreate("TestMtlP", 16, "default");
    //mzgl::material *Mtl = MyAnim->MtlCreate("TestMtl", mzgl::vec3(0.3, 0, 0), 
                            //                                        mzgl::vec3(1, 0, 0), mzgl::vec3(1, 1, 1),
                             //                                       32, 1, MtlP);
    mzgl::topology::base<mzgl::vertex::std> topo;
    topo.Type = mzgl::prim_type::TRIMESH; // WORKS!!!
    mzgl::vertex::std P[8];

    P[0].P = mzgl::vec3(10, 0, 10);
    P[0].C = mzgl::vec4(1, 1, 1, 1);
    P[0].N = mzgl::vec3(0, 1, 0);
    P[0].T = mzgl::vec2(0, 0);
    topo.V.push_back(P[0]);

    P[1].P = mzgl::vec3(10, 0, -10);
    P[1].C = mzgl::vec4(1, 1, 0, 1);
    P[1].N = mzgl::vec3(0, 1, 0);
    P[1].T = mzgl::vec2(1, 0);
    topo.V.push_back(P[1]);

    P[2].P = mzgl::vec3(-10, 0, -10);
    P[2].C = mzgl::vec4(1, 0, 1, 1);
    P[2].N = mzgl::vec3(0, 1, 0);
    P[2].T = mzgl::vec2(1, 1);
    topo.V.push_back(P[2]);

    P[3].P = mzgl::vec3(-10, 0, 10);
    P[3].C = mzgl::vec4(1, 0, 0, 1);
    P[3].N = mzgl::vec3(0, 1, 0);
    P[3].T = mzgl::vec2(0, 1);
    topo.V.push_back(P[3]);

    topo.I = {0, 1, 2, 2, 3, 0};

    pr = MyAnim->PrimCreate<mzgl::vertex::std>(nullptr, topo);
    pr->VBuf = MyAnim->VertexBufferCreate("TEST_UNIT_VB", topo.V, topo.I);  // NEED TO REPLACE IN PRIMCREATE
    pr->PL = MyAnim->PipelineCreate("vulkan_triangle.jpg", topo.Type);          // NEED TO REPLACE IN PRIMCREATE
    // AND ALSO DELETE PIPELINE WITH VERTEX BUFFER

  } /* End of 'test_unit' constructor */

  /* Virtual render function.
   * ARGUMENTS:
   *   - animation context:
   *       anim *Ani;
   * RETURNS: None.
   */
  VOID Render(mzgl::anim* Ani) override
  {
    Ani->Draw(pr, mzgl::matr().RotateY(sin(Ani->Time) * 0));
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

  VOID ToDraw( mzgl::anim *Ani ) override
  {
    Ani->PrimsToDraw.push_back(pr);
    Ani->MatrsToDraw.push_back(mzgl::matr().RotateY(sin(Ani->Time * 2) * 300));
  }
}; /* End of 'test_unit' class */

static mzgl::anim::unit_register<test_unit> _("Test unit");

/* END OF 'test_unit.cpp' FILE */