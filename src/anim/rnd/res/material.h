/* FILE NAME   : material.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Material's and material's manager handle module.
 */

#ifndef __material_h_
#define __material_h_

#include "def.h"

#include "mtl_pattern.h"
#include "res_manager.h"
#include "stock/stock.h"
#include "texture.h"

#include "resource.h"
#include "../render.h"

#include <iostream>

/* Project namespace */
namespace mzgl
{
  /* Material data representation type */
  struct material_data
  {
    vec4 Ka4;           // Ambient
    vec4 KdTrans;       // Diffuse + transparency
    vec4 KsPh;          // Specular + phong coefficient
    texture* Tex[8];    // Textures
    INT CntOfTex;       // Count of Textures
    vec4 IsTexture0123; // Texture flag 
    vec4 IsTexture4567; // Texture flag
  }; /* End of 'material_data' struct */

  /* Material representation type */
  class material : public resource
  {
    friend class render;
  public:
    std::string Name;          // Material name
    material_pattern *MtlPat;  // pointer to material pattern
    material_data MtlData;

    /* Material default constructor */
    material( VOID )
    {
      Name = "";
    } /* End of 'material' function */

    /* Material default constructor */
    material( const std::string &N )
    {
      Name = N;
    } /* End of 'material' function */

    /* Material creation function.
     * ARGUMENTS:
     *   - material name:
     *       const std::string &MtlName;
     *   - ambient coefficient:
     *       vec3 Ka;
     *   - diffuse coefficient:
     *       vec3 Kd;
     *   - specular coefficient:
     *       vec3 Ks;
     *   - Phong coefficient - shiness:
     *       FLT Ph;
     *   - transparency factor:
     *       FLT Trans;
     *   - pointer to material pattern:
     *       material_pattern *NewMtlPat;
     * RETURNS:
     *   (material &) self reference.
     */
    material & Create( const std::string &MtlName, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, 
                       FLT Ph, FLT Trans, material_pattern *NewMtlPat );
    
    /* Apply material function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (INT) new shader stock number.
     */
    INT Apply( VOID );

    /* Add texture function.
     * ARGUMENTS:
     *   - pointer to texture:
     *       texture *Txt;
     * RETURNS: None.
     */
    VOID AddTexture( texture *Txt );
    
    /* Free material function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

  }; /* End of 'material' class */
  
  /* Material manager representation type */
  class material_manager : public resource_manager<material, std::string>
  {
  public:
    material_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'font_manager' function */
    /* Create material function.
     * ARGUMENTS:
     *   - name of matelial:
     *       const std::string &MtlName;
     *   - ambient coefficient:
     *       vec3 Ka;
     *   - diffuse coefficient:
     *       vec3 Kd;
     *   - specular coefficient:
     *       vec3 Ks;
     *   - Phong coefficient - shiness:
     *       FLT Ph;
     *   - transparency factor:
     *       FLT Trans;
     *       material_pattern *NewMtlPat;
     * RETURNS:
     *   (material *) created material interface.
     */
    material * MtlCreate( const std::string &MtlName, const vec3 &Ka, const vec3 &Kd, const vec3 &Ks, 
                          FLT Ph, FLT Trans, material_pattern *NewMtlPat )
    {
      material *m = resource_manager::Add(material(MtlName));

      return &m->Create(MtlName, Ka, Kd, Ks, Ph, Trans, NewMtlPat);
    } /* End of 'MtlCreate' function */

    /* Free material function.
     * ARGUMENTS:
     *   - material pointer:
     *       material *Mtl;
     * RETURNS: None.
     */
    VOID MtlFree( material *Mtl )
    {
      resource_manager::Delete(Mtl);
    } /* End of 'MtlFree' function */
  }; /* End of 'material_manager' class */

} /* end of 'mzgl' namespace */

#endif /* __material_h_ */

/* END OF 'material.h' FILE */