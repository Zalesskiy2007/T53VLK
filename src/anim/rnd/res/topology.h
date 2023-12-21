/* FILE NAME   : topology.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               Topology handle module.
 */

#ifndef __topology_h_
#define __topology_h_

#include "def.h"

#include <vector>
#include <array>

namespace mzgl
{
  /* Primitive shape representation type */
  enum struct prim_type
  {
    TRIMESH, /* Triangle mesh */
    POINTS,  /* Points collection */
    STRIP,   /* Strip of triangles */
    LINES    /* Line segments (by 2 points) */
  }; /* End of 'prim_type' enum */
 
  /* Vertex collection namespace */
  namespace vertex
  {
    /* Standard vertex representation type */
    struct std
    {
      vec3 P;  /* Vertex position */
      vec2 T;  /* Vertex texture coordinates */
      vec3 N;  /* Normal at vertex */
      vec4 C;  /* Vertex color */
      vec4 GM; /* Vertex Indices */
      vec4 GW; /* Vertex weights */

      static VkVertexInputBindingDescription getBindingDescription() 
      {
        VkVertexInputBindingDescription bindingDescription{};

        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(std);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
      }

      static ::std::array<VkVertexInputAttributeDescription, 6> getAttributeDescriptions()
      {
        ::std::array<VkVertexInputAttributeDescription, 6> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(std, P);

        attributeDescriptions[1].binding = 0;
        attributeDescriptions[1].location = 1;
        attributeDescriptions[1].format = VK_FORMAT_R32G32_SFLOAT;
        attributeDescriptions[1].offset = offsetof(std, T);

        attributeDescriptions[2].binding = 0;
        attributeDescriptions[2].location = 2;
        attributeDescriptions[2].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[2].offset = offsetof(std, N);

        attributeDescriptions[3].binding = 0;
        attributeDescriptions[3].location = 3;
        attributeDescriptions[3].format = VK_FORMAT_R32G32B32A32_SFLOAT;
        attributeDescriptions[3].offset = offsetof(std, C);

        attributeDescriptions[4].binding = 0;
        attributeDescriptions[4].location = 4;
        attributeDescriptions[4].format = VK_FORMAT_R32G32B32A32_SFLOAT;
        attributeDescriptions[4].offset = offsetof(std, GM);

        attributeDescriptions[5].binding = 0;
        attributeDescriptions[5].location = 5;
        attributeDescriptions[5].format = VK_FORMAT_R32G32B32A32_SFLOAT;
        attributeDescriptions[5].offset = offsetof(std, GW);

        return attributeDescriptions;
      }

    }; /* End of 'std' structure */
 
    /* The only point vertex representation type */
    struct point
    {
      vec3 P;  /* Vertex position */

      static VkVertexInputBindingDescription getBindingDescription() 
      {
        VkVertexInputBindingDescription bindingDescription{};

        bindingDescription.binding = 0;
        bindingDescription.stride = sizeof(std);
        bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

        return bindingDescription;
      }

      static ::std::array<VkVertexInputAttributeDescription, 1> getAttributeDescriptions()
      {
        ::std::array<VkVertexInputAttributeDescription, 1> attributeDescriptions{};

        attributeDescriptions[0].binding = 0;
        attributeDescriptions[0].location = 0;
        attributeDescriptions[0].format = VK_FORMAT_R32G32B32_SFLOAT;
        attributeDescriptions[0].offset = offsetof(std, P);

        return attributeDescriptions;
      }
    }; /* End of 'point' structure */
  } /* end of 'vertex' namespace */
 
  /* Topology structures namespase */
  namespace topology
  {
    /* Base topology class */
    template<class vertex_type>
      class base
      {
        friend class prim;
      public:
        prim_type Type = prim_type::TRIMESH;
 
        /* Vertex array */
        std::vector<vertex_type> V;
        /* Index array */
        std::vector<uint32_t> I;
      public:
        /* Class default constructor */
        base( VOID )
        {
        } /* End of 'base' function */
 
        /* Class constructor.
         * ARGUMENTS:
         *   - primitive type:
         *       prim_type NewType;
         *   - vertex array:
         *       const std::vector<vertex_type> &NewV;
         *   - index array:
         *       const std::vector<INT> &NewI;
         */
        base( prim_type NewType,
              const std::vector<vertex_type> &NewV = {},
              const std::vector<uint32_t> &NewI = {} ) :
          Type(NewType), V(NewV), I(NewI)
        {
        } /* End of 'base' function */
      }; /* End of 'base' class */
  } /* end of 'topology' namespace */
} /* end of 'mzgl' namespace */

#endif /* __topology_h_ */

/* END OF 'topology.h' FILE */