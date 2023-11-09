/* FILE NAME   : mtl_pattern.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Material pattern module.
 */

#include "mzgl.h"

/* Material pattern creation function.
 * ARGUMENTS:
 *   - material pattern name:
 *       const std::string &MtlPatName;
 *   - attribution size:
 *       INT Attrib;
 *   - shader name:
 *       const std::string &NewShdName
 * RETURNS:
 *   (material_pattern &) self reference.
 */
mzgl::material_pattern & mzgl::material_pattern::Create( const std::string &MtlPatName, 
                                                         INT Attrib, 
                                                         const std::string &NewShdName )
{
  AttribSize = Attrib;
  Shd = Rnd->ShaderCreate(NewShdName);

  return *this;
} /* End of 'mzgl::material_pattern::Create' function */

/* Free material pattern function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::material_pattern::Free( VOID )
{
  Rnd->ShaderFree(Shd);
} /* End of 'mzgl::material_pattern::Free' function */

/* END OF 'mtl_pattern.cpp' FILE */
