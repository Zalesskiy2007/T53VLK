/* FILE NAME   : render.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 31.07.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Render system module.
 *               Render handle module.
 */

#ifndef __render_h_
#define __render_h_

#include "def.h"

#include "anim/rnd/res/shader.h"
#include "anim/rnd/res/mtl_pattern.h"
#include "anim/rnd/res/material.h"
#include "anim/rnd/res/primitives.h"
#include "anim/rnd/res/font.h"
#include "anim/rnd/res/target.h"
#include "anim/rnd/res/light.h"
#include "anim/rnd/res/model.h"
#include "anim/rnd/res/buffer.h"
#include "anim/rnd/res/pipeline.h"
#include "anim/rnd/res/vertex_buffer.h"

#include "anim/input/timer.h"
#include <string>

#include "anim/anim.h"

#include <optional>

 /* Project namespace */
namespace mzgl
{
   /* Primitive data representation type */
  struct prim_data
  {
    matr MatrWVP;
  }; /* End of 'prim_data' class */

  /* Render representation type */
  class render : public timer, 
    public shader_manager, public material_pattern_manager,
    public material_manager, public primitive_manager, public texture_manager, public font_manager,
    public target_manager, public light_manager, public model_manager, public buffer_manager, public pipeline_manager, public vertex_buffer_manager
  {
  public:
    HWND& hWnd;     // Render reference to window handle
    HDC hDC;        // Render window device context

    VkInstance Instance;                     
    VkDevice LogicalDevice;                      
    VkPhysicalDevice PhysicalDevice;         
    VkPhysicalDeviceFeatures DeviceFeatures;
    UINT32 QueueFamilyCount;
    VkSurfaceKHR Surface;
    std::vector<VkImageView> SwapchainImageViews;
    VkSwapchainKHR Swapchain;
    UINT32 SwapchainImagesCount;
    VkExtent2D SwapChainExtent;
    VkRenderPass RenderPass;
    std::vector<VkFramebuffer> FrameBuffers;
    VkQueue Queue;
    VkCommandPool CommandPool;
    VkCommandBuffer CommandBuffer;
    VkFence Fence;
    UINT32 ImageIndex;

    static const INT MAX_FRAMES_IN_FLIGHT = 2;

  public:
    camera Camera;   // Camera type
    prim_data Prim_data;  // Primitive data 
    target *Trg;
    light *Lgh;

    //pipeline *Pipeline;

    std::vector<prim *> PrimsToDraw;
    std::vector<matr> MatrsToDraw;
    BOOL IsShading = FALSE;

    /* Path to shader directory */
    std::string Path;

    /* Render default constructor */
    render(HWND& hNewWnd) : hWnd(hNewWnd), timer(),
      shader_manager(*this), material_pattern_manager(*this),
      material_manager(*this), primitive_manager(*this), texture_manager(*this), font_manager(*this),
      target_manager(*this), light_manager(*this), model_manager(*this), buffer_manager(*this), pipeline_manager(*this), vertex_buffer_manager(*this)
    {      
    }
    /* Render default destructor */
    ~render(VOID)
    {
    }

    BOOL IsInit;  // Flag for initialization render

    /* Render system initialization function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init(VOID);

    uint32_t findMemoryType( uint32_t typeFilter, VkMemoryPropertyFlags properties );
    VOID CreateBuffer( VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory );
    VOID CopyBuffer( VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size );

    VkCommandBuffer BeginSingleTimeCommands( VOID );
    VOID EndSingleTimeCommands( VkCommandBuffer commandBuffer );
    VOID TransitionImageLayout( VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout );
    VOID CopyBufferToImage( VkBuffer buffer, VkImage image, uint32_t width, uint32_t height );


    VkImageView CreateImageView( VkImage image, VkFormat format );

    /* Render system close (deinitialization) function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close(VOID);

    /* Render system resize function.
     * ARGUMENTS:
     *   - window new size:
     *       INT W, INT H;
     * RETURNS: None.
     */
    VOID Resize(INT NewW, INT NewH);

    /* Start render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameStart(VOID);

    /* Finish render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameEnd(VOID);

    /* Primitive draw function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     *   - transformation matrix:
     *       const matr &World;
     * RETURNS: None.
     */
    VOID Draw( const prim* Pr, const matr& World = matr().Identity());

    VOID InstanceInit( VOID );
    VOID InstanceClose( VOID );

    VOID PhysicalDeviceInit( VOID );
    VOID PhysicalDeviceClose( VOID );

    VOID LogicalDeviceInit( VOID );
    VOID LogicalDeviceClose( VOID );

    VOID SurfaceInit( VOID );
    VOID SurfaceClose( VOID );

    VkSwapchainKHR SwapchainInit( VOID );
    VOID SwapchainClose( VOID );

    VOID RenderPassInit( VOID );
    VOID RenderPassClose( VOID );

    VOID FrameBuffersInit( VOID );
    VOID FrameBuffersClose( VOID );

    VOID QueueInit( VOID );
    VOID QueueClose( VOID );

    VOID CommandPoolInit( VOID );
    VOID CommandPoolClose( VOID );

    VOID CommandBufferInit( VOID );
    VOID CommandBufferClose( VOID );

    VOID CommandBufferStart( VOID );
    VOID CommandBufferEnd( VOID );

    VOID FenceInit( VOID );
    VOID FenceClose( VOID );

    struct queue_family_indices
    {
      std::optional<UINT32> GraphicsFamily;      // Индекс семейства очередей рендеринга
      std::optional<UINT32> PresentFamily;       // Индекс семейства очередей экранного вывода
    };

    queue_family_indices GetQueueFamilyIndices( VOID )
    {
      UINT32 QueueFamilyCount = 0;

      vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, nullptr);
      std::vector<VkQueueFamilyProperties> QueueFamilyProperties {QueueFamilyCount};
      vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, QueueFamilyProperties.data());

      queue_family_indices Indices;
      for (UINT32 i = 0; i < QueueFamilyCount; i++)
      {
        // Проверка поддержки рендеринга семейством очередей
        if ((QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
          Indices.GraphicsFamily = i;
      
        // Проверка поддержки экранного вывода семейством очередей
        VkBool32 PresentSupport = VK_FALSE;
        vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &PresentSupport);
        if (PresentSupport == VK_TRUE)
          Indices.PresentFamily = i;
      }

      return Indices;
    }


  }; /* End of 'render' class */

} /* end of 'mzgl' namespace */

#endif /* __render_h_ */

/* END OF 'render.h' FILE */