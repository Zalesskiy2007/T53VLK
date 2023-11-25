/* FILE NAME   : render.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Render system module.
 *               Render (*.cpp) file module.
 */

#include "mzgl.h"
#include <cstdio>
#include <filesystem>
#include <sstream>

#pragma comment(lib, "vulkan-1.lib")

VOID mzgl::render::InstanceInit( VOID )
{
  // Informatin structure of application.
  VkApplicationInfo AppInfo 
  {
    .sType = VK_STRUCTURE_TYPE_APPLICATION_INFO,
    .pApplicationName = "MZ2 Vulkan Project",
    .applicationVersion = 1,
    .apiVersion = VK_MAKE_VERSION(1, 0, 0),   // version of VulkanAPI.
  };
  
  // Information structie for instance creating.
  VkInstanceCreateInfo InstanceCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO,
    .pApplicationInfo = &AppInfo,
  };

  // extensions for instance.
  std::vector<const CHAR *> InstanceExtensionNames 
  {
    VK_KHR_WIN32_SURFACE_EXTENSION_NAME,
    VK_KHR_SURFACE_EXTENSION_NAME,
    VK_EXT_DEBUG_REPORT_EXTENSION_NAME,
    VK_EXT_DEBUG_UTILS_EXTENSION_NAME,
  };
  InstanceCreateInfo.enabledExtensionCount = (UINT32)InstanceExtensionNames.size();
  InstanceCreateInfo.ppEnabledExtensionNames = InstanceExtensionNames.data();

  // NOT WORKING
  // layers of instance. 
  std::vector<const CHAR *> EnabledLayersNames
  {
    "VK_LAYER_KHRONOS_validation"   // Validation layer.
  };
  
  
  InstanceCreateInfo.enabledLayerCount = (UINT32)EnabledLayersNames.size();
  InstanceCreateInfo.ppEnabledLayerNames = EnabledLayersNames.data();
 
  // ������� ������������ ���������.
  // ��� ������������ �������� ������������ (��� ������ 1.3: ����� 4.2, ��������� VkValidationFeaturesEXT).
  VkValidationFeaturesEXT ValidationFeatures 
  {
    .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
  };
  std::vector<VkValidationFeatureEnableEXT> ValidationFeaturesEnable
  {
    VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,    // ������������ ��� ��������� ��������.
    VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT   // ������������ �������������� ����� warning'��.
  };
  ValidationFeatures.enabledValidationFeatureCount = (UINT32)ValidationFeaturesEnable.size();
  ValidationFeatures.pEnabledValidationFeatures = ValidationFeaturesEnable.data();
 
  InstanceCreateInfo.pNext = &ValidationFeatures;
 
  // �������� ���������� ��������.
  VkDebugReportCallbackCreateInfoEXT DebugReportCallbackInfo {};
  DebugReportCallbackInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
 
  DebugReportCallbackInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
  DebugReportCallbackInfo.pNext = nullptr;
  DebugReportCallbackInfo.flags =
    VK_DEBUG_REPORT_INFORMATION_BIT_EXT |
    VK_DEBUG_REPORT_WARNING_BIT_EXT |
    VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT |
    VK_DEBUG_REPORT_ERROR_BIT_EXT |
    VK_DEBUG_REPORT_DEBUG_BIT_EXT;
  DebugReportCallbackInfo.pfnCallback = [](
    VkDebugReportFlagsEXT Flags,
    VkDebugReportObjectTypeEXT ObjectType,
    UINT64 Object,
    SIZE_T Location,
    INT32 MessageCode,
    const CHAR *LayerPrefix,
    const CHAR *Message,
    VOID *UserData) -> VkBool32
  {
    if ((Flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT) != 0)
      return VK_FALSE;
    std::string Res = "DEBUG REPORT: (";
 
    if ((Flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT) != 0)
      Res += "INFO";
    if ((Flags & VK_DEBUG_REPORT_WARNING_BIT_EXT) != 0)
      Res += "WARNING";
    if ((Flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT) != 0)
      Res += "PERFORMANCE";
    if ((Flags & VK_DEBUG_REPORT_ERROR_BIT_EXT) != 0)
      Res += "ERROR";
    Res += ")";
    Res += std::string("{") + LayerPrefix + "} " + Message + "\n";
    OutputDebugString(Res.c_str());
    return VK_FALSE;
  };
  DebugReportCallbackInfo.pUserData = nullptr;
 
  ValidationFeatures.pNext = &DebugReportCallbackInfo;
 
  if (vkCreateInstance(&InstanceCreateInfo, nullptr, &Instance) != VK_SUCCESS)
  {
    throw;
  }
}

VOID mzgl::render::PhysicalDeviceInit( VOID )
{
  std::vector<VkPhysicalDevice> PhysDevices;
  UINT32 PhysicalDeviceCount = 0;

  VkResult a = vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, nullptr);
  if (a != VK_SUCCESS)
  {
    throw;
  }
 
  // ��������� ���������� ��������� �������.
  PhysDevices.resize(PhysicalDeviceCount);
  if (vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysDevices.data()) != VK_SUCCESS)
  {
    throw;
  }
 
  // ����� ����������� ���������� �� �����������.
  VkPhysicalDevice PhysDevice = VK_NULL_HANDLE;
  for (VkPhysicalDevice &Device : PhysDevices)
  {
    std::vector<VkQueueFamilyProperties> QueueFamilies;
    // ���������� ���������� ����� ��������� ������ �� ���:
    VkPhysicalDeviceProperties DeviceProperties;                                   // �������� ����������
    vkGetPhysicalDeviceProperties(Device, &DeviceProperties);                      // (��������, ���� ����������,
                                                                                   // �������� ������������ ����������),
 
    VkPhysicalDeviceFeatures DeviceF;                                              // �������������� ������������ 
    vkGetPhysicalDeviceFeatures(Device, &DeviceF);                                 // (��������, ��������� �������������� �
                                                                                   // ������������� ��������),
 
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);  // �������������� ����� ���������
                                                                                   // �������� (��������, ���������
                                                                                   //  �� ��� ������������� ���
                                                                                   // ��������� �������������� ������).
    QueueFamilies.resize(QueueFamilyCount);        
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, QueueFamilies.data());
 
    PhysicalDevice = Device;
    DeviceFeatures = DeviceF;
  }
 
  if (PhysicalDevice == VK_NULL_HANDLE)
  {
    throw;
  }
}

VOID mzgl::render::LogicalDeviceInit( VOID )
{
  std::vector<FLT> QueuePriorities; 
  
  for (size_t i = 0; i < QueueFamilyCount; i++)
    QueuePriorities.push_back(1);

  VkDeviceQueueCreateInfo QueueInfo
  {
    .sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .queueFamilyIndex = 0,
    .queueCount = QueueFamilyCount,
    .pQueuePriorities = QueuePriorities.data(),
  };        
 
  // ������� ���������� ����������� ����������.
  std::vector<const CHAR *> ExtensionNames
  {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME,
  };
 
  VkDeviceCreateInfo DeviceInfo
  {
    .sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .queueCreateInfoCount = 1,
    .pQueueCreateInfos = &QueueInfo,
    .enabledLayerCount = 0,
    .ppEnabledLayerNames = nullptr,
    .enabledExtensionCount = (UINT32)ExtensionNames.size(),
    .ppEnabledExtensionNames = ExtensionNames.data(),
    .pEnabledFeatures = &DeviceFeatures
  };
 
  vkCreateDevice(
    PhysicalDevice,                                     // ���������� ����������.
    &DeviceInfo,                                        // ���������� ��������.
    nullptr,                                            // ��������� ������ (������������).
    &LogicalDevice                                      // ��������� �� ���������� ������ ����������
                                                        // ����������� ���������� (VkLogicalDevice).
  );
}

VOID mzgl::render::SurfaceInit( VOID )
{
  VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
    .flags = 0,
    .hinstance = GetModuleHandle(nullptr),                      // ���������� ���������� ����������.
    .hwnd = hWnd,                                               // ���������� ����, � �������� ����� ��������� Vulkan.
  };
  
  if (vkCreateWin32SurfaceKHR(Instance, &SurfaceCreateInfo, nullptr, &Surface) != VK_SUCCESS)
    throw;
}

VkSwapchainKHR mzgl::render::SwapchainInit( VOID )
{
  VkSwapchainCreateInfoKHR SwapchainCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
    .flags = 0,
    .surface = Surface,
    .minImageCount = 2,                                  // ����������� ���������� �����������, ��������� �� swapchain.

    // � ��������� ������� ��������� ��������� ��������, �������������� �� 
    // ������ ��������� ���������� ����������� ��� ������� surface.
    // ��� �������� ���������� ��������������� 
    // vkGetPhysicalDeviceSurfaceFormatsKHR(...).
    .imageFormat = VK_FORMAT_B8G8R8A8_SRGB,                      // ��������� �������� ��������� � �����.
    .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,        // ������������ �������� ������������, 
                                                                 // � ������� �������� �����.
    
    //.imageExtent.width = Camera.FrameW,                         // � ��������� ������� ���� ����� ��������
                                                         // �������� ��������, ������ �� 
   // .imageExtent.height = Camera.FrameH,                        // SurfaceCapabilities.minImageExtent.width,
                                                         // SurfaceCapabilities.maxImageExtent.width.
                                                         // ��� ��������� SurfaceCapabilities ������������
                                                         // vkGetPhysicalDeviceSurfaceCapabilitiesKHR(...).

    .imageArrayLayers = 1,                               // ���������� ����� ��� ���������.
    
    .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,   // ��� ����������� ������������ ����������� swapchain.
                                                         // � ������ ������ - � �������� �������� ������� �� �����
                                                         // ����������. ������ ����� ������������� - � ��������
                                                         // ������� ������� ��� stencil.
    
    .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,       // ������ �������� ����� ���� ������, ��� �����������
                                                         // swapchain ����� �������������� ������ ����� ����������
                                                         // ��������. ���� ���� ������������� � �������������
                                                         // ����������� ����������� ��������, ������ ���� ������
                                                         // ��������� VK_SHARING_MODE_CONCURRENT, � � ��������� �����
                                                         // ������ ����������� ���������� �� ���� ���������� ��������.
    .queueFamilyIndexCount = 0,
    .pQueueFamilyIndices = nullptr,
    
    .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,  // ��������������, ������� ���������� ��������� �
                                                            // ������������ (��������, ��������� �� �����������).

    .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,    // ������ �����-����� ��� ��������� � ������� ������.
                                                            // ��� ������������� �����-������ ������������ ��������
                                                            // VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR.

    // � ��������� ������� ��������� ��������� ��������, �������������� �� 
    // ������ ��������� ���������� ����������� ��� ������� surface.
    // ��� �������� ���������� ��������������� 
    // vkGetPhysicalDeviceSurfacePresentModesKHR(...).
    .presentMode = VK_PRESENT_MODE_FIFO_KHR,             // ������ �������������� � �������� �����������
                                                         // (� ������ ������ - "First In, First Out").

    .clipped = VK_TRUE,                                     // �������� VK_TRUE � ������ ���� ��������, ��� �����
                                                            // ���������� �������� (��������, ������ �����)
                                                            // ������������.

    .oldSwapchain = Swapchain,                         // ������� swapchain. ������ ���� ��������� ���
                                                            // ������������ swapchain. (��������, ��� ���������
                                                            // �������� ����).
  };

  SwapchainCreateInfo.imageExtent.width = Camera.FrameW;
  SwapchainCreateInfo.imageExtent.height = Camera.FrameH;

  SwapChainExtent = SwapchainCreateInfo.imageExtent;
  
  if (vkCreateSwapchainKHR(LogicalDevice, &SwapchainCreateInfo, nullptr, &Swapchain) != VK_SUCCESS)
    throw;

  std::vector<VkImage> SwapchainImages;
  if (vkGetSwapchainImagesKHR(LogicalDevice, Swapchain, &SwapchainImagesCount, nullptr) != VK_SUCCESS)
    throw;
  
  SwapchainImages.resize(SwapchainImagesCount);
  SwapchainImageViews.resize(SwapchainImagesCount);
  if (vkGetSwapchainImagesKHR(LogicalDevice, Swapchain, &SwapchainImagesCount, &SwapchainImages[0]) != VK_SUCCESS)
    throw;

  for (INT i = 0; i < SwapchainImages.size(); i++) 
  {
    // ��������� � ���������� �������� image view �������� � ������� 6.5.
    VkImageViewCreateInfo ImageViewCreateInfo 
    {
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .image = SwapchainImages[i],
      
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = VK_FORMAT_B8G8R8A8_SRGB,
      .components =
      {
        .r = VK_COMPONENT_SWIZZLE_IDENTITY,
        .g = VK_COMPONENT_SWIZZLE_IDENTITY,
        .b = VK_COMPONENT_SWIZZLE_IDENTITY,
        .a = VK_COMPONENT_SWIZZLE_IDENTITY,
      },
  
      // �������� ����, ��� ����������� ������������ ����������� � ����� ����� ����������� ����� ��������������.
      .subresourceRange =
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .baseMipLevel = 0,
        .levelCount = 1,
        .baseArrayLayer = 0,
        .layerCount = 1,
      },
    };
  
    if (vkCreateImageView(LogicalDevice, &ImageViewCreateInfo, nullptr, &SwapchainImageViews[i]) != VK_SUCCESS)
      throw;
  }

  return SwapchainCreateInfo.oldSwapchain;
}

VOID mzgl::render::RenderPassInit( VOID )
{
   /* ���������, ����������� G-Buffer. */
  VkAttachmentDescription AttachmentDescription
  {
    .flags = 0,                                         // �����.
    .format = VK_FORMAT_B8G8R8A8_SRGB,                     // ������ ����������� attachment'�.
    .samples = VK_SAMPLE_COUNT_1_BIT,                   // Multisampling.
    .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,              // ��, ��� ���������� � ������� ��� ������ subpass'�.
    .storeOp = VK_ATTACHMENT_STORE_OP_STORE,            // ��� ���������� ��� ������� ���-���� ��������.
    .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,   // ��-��, �� ��� Stencil Buffer'�.
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, // 
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,         // ����� layout ������ ���� � ����������� � ������ ����������.
    .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,     // ����� layout ����� � ����������� � �����.
  };
  
  /* ���������, ����������� �� ����������� G-Buffer � ������������ ��� ��������� �� ����� subpass'� */
  VkAttachmentReference ColorAttachmentReference
  {
    .attachment = 0,                                    // ������ attachment'� � ����� ������.
    .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // Layout ����������� attachment'� �� ����� ����������.
  };
  
  /* ���������, ����������� ���� ��������� */
  VkSubpassDescription SubpassDescription
  {
    .flags = 0,                                           // �����.
    .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS, // ����� ��� pipeline ���������� ������ subpass.
    .inputAttachmentCount = 0,                            // ���������� ������� attachment'��.
    .pInputAttachments = nullptr,                         // �� VkAttachmentReference[].
    .colorAttachmentCount = 1,                            // ���������� �������� attachment'��.
    .pColorAttachments = &ColorAttachmentReference,   // �� VkAttachmentReference[].
    .pResolveAttachments = nullptr,                       // Attachment'� ��� multisampling'�.
    .pDepthStencilAttachment = nullptr,                   // Reference Depthbuffer'�, ������������ � ����������.

    .preserveAttachmentCount = 0,                         // Attachment'�, ������� � ������ ����������
                                                          // �� ��������� ��������, �� ������ ������� ������
                                                          // ����������� ��� ������������� � ���������� �����������.
    .pPreserveAttachments = nullptr,
  };
  

  /* ���������, ����������� ������� ����� subpass'��� */
  VkSubpassDependency SubpassDependency
  {
    .srcSubpass = VK_SUBPASS_EXTERNAL,                             // ������ ����������, �� �������� �� ���������.
                                                                   // VK_SUBPASS_EXTERNAL ��������, ��� srcSubpass,
                                                                   // ���, �.�. �� ������ �������� ��� ������.
    .dstSubpass = 0,                                               // ������ ����������, � ������� �� ���������.
    .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, // ��������� ���� Pipeline � srcSubpass'�, �
                                                                   // ������� ����� ���������� ������� � dstSubpass.
    .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, // ���������, � �������� ����� �������� �����������
                                                                   // ������� �� dstAccessMask.
    .srcAccessMask = 0,                                            // ������ � G-Buffer'� � srcSubpass.
    .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,         // ������ � G-Buffer'� � dstSubpass.
    .dependencyFlags = 0,                                          // �����
  };

  /* ���������, ���������� ��� ���������� ��� �������� renderpass'� */
  VkRenderPassCreateInfo CreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO, // ��� ���������.
    .pNext = nullptr,                                   // ��������� �� ���������-����������, ���� ��� ����.
    .flags = 0,                                         // �����.
    .attachmentCount = 1,                               // ���������� color attachment'�� �� ��� renderpass'�.
    .pAttachments = &AttachmentDescription,         // �� ��������.
    .subpassCount = 1,                                  // ���������� ����������� ����������.
    .pSubpasses = &SubpassDescription,              // �������� �����������.
    .dependencyCount = 1,                               // ���������� ��������� ����� subpass'���.
    .pDependencies = &SubpassDependency,            // �� ��������.
  };
  
  //VkRenderPass RenderPass = VK_NULL_HANDLE;

  if (vkCreateRenderPass(LogicalDevice, &CreateInfo, nullptr, &RenderPass) != VK_SUCCESS)
    throw;
}
VOID mzgl::render::FrameBuffersInit( VOID )
{
  FrameBuffers.resize(SwapchainImageViews.size());
  for (INT i = 0; i < SwapchainImageViews.size(); i++)
  {
    std::vector<VkImageView> Attachments = 
    {
      SwapchainImageViews[i],
      //DepthImageView
    };
  
    VkFramebufferCreateInfo FrameBufferCreateInfo
    {
      .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
      .renderPass = RenderPass,
      .attachmentCount = (uint32_t)(Attachments.size()),
      .pAttachments = Attachments.data(),
      .width = SwapChainExtent.width,
      .height = SwapChainExtent.height,
      .layers = 1,                                                   // ���������� ����� ��������� ������.
    };
  
    if (vkCreateFramebuffer(LogicalDevice, &FrameBufferCreateInfo, nullptr, &FrameBuffers[i]) != VK_SUCCESS)
      throw;
  }
}

VOID mzgl::render::QueueInit( VOID )
{
  // ��������� ������������ ��� ������� ��������� ��������.
  vkGetDeviceQueue(
    LogicalDevice, // ���������� ����������.
    0,      // ������ ��������� ��������.
    0,      // ������ �������.
    &Queue  // ��������� �� ���������� VkQueue.
  );
}

VOID mzgl::render::CommandPoolInit( VOID )
{
  queue_family_indices Indices = GetQueueFamilyIndices();
  VkCommandPoolCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,      // ��� ���������.
    .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, // ����� ���� ������.
    .queueFamilyIndex = Indices.GraphicsFamily.value(),
  };

  vkCreateCommandPool(
    LogicalDevice,               // ���������� ����������.
    &Info,                // ���������� ��������.
    nullptr,              // ��������� ������ (������������).
    &CommandPool          // ��������� �� ���������� VkCommandPool.
  );
}

VOID mzgl::render::CommandBufferInit( VOID )
{
  VkCommandBufferAllocateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, // ��� ���������.
    .commandPool = CommandPool,                              // ������������ ��� ������.
    .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,                // ��� ���������� ������.
    .commandBufferCount = 1                                  // ���������� ���������� �������.
  };
  
  vkAllocateCommandBuffers(
    LogicalDevice,               // ���������� ����������.
    &Info,                // ���������� ��������.
    &CommandBuffer        // ��������� �� ������ ���������� VkCommandBuffer.
  );
}

VOID mzgl::render::FenceInit( VOID )
{
  VkFenceCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, // ��� ���������.
    .flags = VK_FENCE_CREATE_SIGNALED_BIT   // ������� ���������.
  };

  vkCreateFence(
    LogicalDevice,  // ���������� ����������.
    &Info,   // ���������� ��������.
    nullptr, // ��������� ������ (������������).
    &Fence   // ��������� �� ���������� VkFence.
  );
}

VOID mzgl::render::InstanceClose( VOID )
{
  vkDestroyInstance(Instance, nullptr); 
}

VOID mzgl::render::PhysicalDeviceClose( VOID )
{
  // Empty
}

VOID mzgl::render::LogicalDeviceClose( VOID )
{
  vkDestroyDevice(LogicalDevice, nullptr);
}

VOID mzgl::render::SurfaceClose( VOID )
{
  vkDestroySurfaceKHR(Instance, Surface, nullptr);
}

VOID mzgl::render::SwapchainClose( VOID )
{
  for (INT i = 0; i < SwapchainImageViews.size(); i++)
    vkDestroyImageView(LogicalDevice, SwapchainImageViews[i], nullptr);
  vkDestroySwapchainKHR(LogicalDevice, Swapchain, nullptr);
}

VOID mzgl::render::RenderPassClose( VOID )
{
  /* �������� RenderPass */
  vkDestroyRenderPass(LogicalDevice, RenderPass, nullptr);
}

VOID mzgl::render::FrameBuffersClose( VOID )
{
  for (VkFramebuffer FrameBuffer : FrameBuffers)
    vkDestroyFramebuffer(LogicalDevice, FrameBuffer, nullptr);
}

VOID mzgl::render::QueueClose( VOID )
{
  // Empty
}

VOID mzgl::render::CommandPoolClose( VOID )
{
  vkDestroyCommandPool(
    LogicalDevice,      // ���������� ����������.
    CommandPool, // ��������� ������.
    nullptr      // ��������� ������ (������ ��������� � �������������� � ��������).
  );
}

VOID mzgl::render::CommandBufferClose( VOID )
{
  // Empty
}

VOID mzgl::render::FenceClose( VOID )
{   
  VkResult Result = vkWaitForFences(
    LogicalDevice,      // ���������� ����������.
    1, // ���������� �������� ��� ��������.
    &Fence,      // ������ �������� ��� ��������.
    TRUE, // �������� ����, ���� ������� ���������������.
    UINT64_MAX      // ����� ������� �������� (��������: UINT64_MAX).
  );
  vkResetFences(
    LogicalDevice,      // ���������� ����������.
    1, // ���������� �������� ��� ������.
    &Fence      // ������ �������� ��� ������.
  );

  vkDestroyFence(
    LogicalDevice,  // ���������� ������.
    Fence,    // ��������� ������.
    nullptr // ��������� ������ (������ ��������� � �������������� � ��������).
  );
}

 /* Render system initialization function.
  * ARGUMENTS: None.
  * RETURNS: None.
  */
VOID mzgl::render::Init(VOID)
{
  /* Prepare frame compatible device context */
  hDC = GetDC(hWnd);

  /* Set camera */
  Camera.ProjSize = 0.1;
  Camera.ProjDist = Camera.ProjSize;
  Camera.ProjFarClip = 3000;
  Camera.FrameW = 1424;
  Camera.FrameH = 720;

  Camera.CamSet(vec3(0, 10, 20), vec3(0), vec3(0, 1, 0));
  CHAR Buf[_MAX_PATH];
  GetCurrentDirectory(sizeof(Buf), Buf);
  Path = Buf;

  InstanceInit();
  PhysicalDeviceInit();
  LogicalDeviceInit();
  SurfaceInit();
  SwapchainInit();
  RenderPassInit();

  Pipeline = PipelineCreate("triangle");

  FrameBuffersInit();
  QueueInit();
  CommandPoolInit();
  CommandBufferInit();
  FenceInit();

  //Trg = TrgCreate("FBO");
  //Lgh = LghCreate("Shadows");

  IsInit = TRUE;
} /* End of 'mzgl::render::Init' function */

/* Render system close (deinitialization) function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::render::Close(VOID)
{
  FenceClose();
  CommandBufferClose();
  CommandPoolClose();
  QueueClose();
  FrameBuffersClose();

  PipelineFree(Pipeline);

  RenderPassClose();
  SwapchainClose();
  SurfaceClose();
  LogicalDeviceClose();
  PhysicalDeviceClose();
  InstanceClose();

  ReleaseDC(hWnd, hDC);
} /* End of 'mzgl::render::Close' function */

/* Render system resize function.
 * ARGUMENTS:
 *   - window new size:
 *       INT NewW, INT NewH;
 * RETURNS: None.
 */
VOID mzgl::render::Resize(INT NewW, INT NewH)
{
  //glViewport(0, 0, NewW, NewH);
  vkDeviceWaitIdle(LogicalDevice);

  /* Save size */
  Camera.FrameH = NewH;
  Camera.FrameW = NewW;

  //Trg->TargetResize(NewW, NewH);
  /* Reset projection */
  Camera.ProjSet();

  for (INT i = 0; i < FrameBuffers.size(); i++)
    vkDestroyFramebuffer(LogicalDevice, FrameBuffers[i], nullptr);          // � Frame buffers � ������� 2.5.
  
  for (INT i = 0; i < SwapchainImageViews.size(); i++)
    vkDestroyImageView(LogicalDevice, SwapchainImageViews[i], nullptr);

  VkSwapchainKHR old = SwapchainInit();

  vkDestroySwapchainKHR(LogicalDevice, old, nullptr);

  FrameBuffersInit();


} /* End of 'mzgl::render::Resize' function */

VOID mzgl::render::CommandBufferStart( VOID )
{
  VkResult Result = vkWaitForFences(
    LogicalDevice,      // ���������� ����������.
    1, // ���������� �������� ��� ��������.
    &Fence,      // ������ �������� ��� ��������.
    TRUE, // �������� ����, ���� ������� ���������������.
    UINT64_MAX      // ����� ������� �������� (��������: UINT64_MAX).
  );
  // ��������� ���������� (��� ����� ����� ������).
  switch (Result)
  {
  case VK_SUCCESS:
    break;
  case VK_TIMEOUT:
    return;
  }

  vkResetFences(
    LogicalDevice,      // ���������� ����������.
    1, // ���������� �������� ��� ������.
    &Fence      // ������ �������� ��� ������.
  );

  vkAcquireNextImageKHR(LogicalDevice, Swapchain, UINT64_MAX, VK_NULL_HANDLE, Fence, &ImageIndex);

  vkResetCommandBuffer(
    CommandBuffer, // ��������� �����.
    0              // ����� ������.
  );

  VkCommandBufferBeginInfo BeginInfo
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, // ��� ���������.
    .flags = 0,                                           // ����� ������������� ������.
    .pInheritanceInfo = nullptr,                          // ������������� ������. ���������� ��� ���������.
  };
  vkBeginCommandBuffer(CommandBuffer, &BeginInfo);

  //std::array<VkClearValue, 1> ClearValues = {{0.1f, 0.9f, 0.3f}}; // ��������� � ������ 8.1
  std::vector<VkClearValue> ClearValues {{0.3f, 0.5f, 0.1f}}; // ��������� � ������ 8.1

  VkRenderPassBeginInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO, // ��� ���������.
    .renderPass = RenderPass,                          // ������������ ������ �������.
    .framebuffer = FrameBuffers[ImageIndex],                        // ������������ ����� �����.
    .renderArea =
    {
      .offset = // �������� ������� ������ �����, ��������� ��� ���������.
      {
        .x = 0,
        .y = 0
      },
      .extent = // ������ ������� ������ �����, ��������� ��� ���������.
      {
        .width = SwapChainExtent.width,
        .height = SwapChainExtent.height
      }
    },
    .clearValueCount = static_cast<UINT32>(ClearValues.size()), // ���������� �������� ������� ������ �����.
    .pClearValues = ClearValues.data()                          // �������� ������� ������ �����.
  };  

  vkCmdBeginRenderPass(
    CommandBuffer,             // ��������� �����.
    &Info,                     // ���������� ������.
    VK_SUBPASS_CONTENTS_INLINE // ��� �������� ����������
  );

  vkCmdBindPipeline(CommandBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, Pipeline->Pipeline);

  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = static_cast<float>(SwapChainExtent.width);
  viewport.height = static_cast<float>(SwapChainExtent.height);
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;
  vkCmdSetViewport(CommandBuffer, 0, 1, &viewport);
  
  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = SwapChainExtent;
  vkCmdSetScissor(CommandBuffer, 0, 1, &scissor);
  
  /* NEED TO REPLACE IN DRAW FUNCTION */
  vkCmdDraw(CommandBuffer, 3, 1, 0, 0);
  /* NEED TO REPLACE IN DRAW FUNCTION */
}

VOID mzgl::render::CommandBufferEnd( VOID )
{
  vkCmdEndRenderPass(CommandBuffer);
  vkEndCommandBuffer(CommandBuffer);

  VkSubmitInfo submitInfo{};
  submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;

  VkPipelineStageFlags waitStages[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  submitInfo.waitSemaphoreCount = 0;
  submitInfo.pWaitDstStageMask = waitStages;

  submitInfo.commandBufferCount = 1;
  submitInfo.pCommandBuffers = &CommandBuffer;

  VkResult Result = vkWaitForFences(
    LogicalDevice,      // ���������� ����������.
    1, // ���������� �������� ��� ��������.
    &Fence,      // ������ �������� ��� ��������.
    TRUE, // �������� ����, ���� ������� ���������������.
    UINT64_MAX      // ����� ������� �������� (��������: UINT64_MAX).
  );
  vkResetFences(
    LogicalDevice,      // ���������� ����������.
    1, // ���������� �������� ��� ������.
    &Fence      // ������ �������� ��� ������.
  );

  if (vkQueueSubmit(Queue, 1, &submitInfo, Fence) != VK_SUCCESS) {
    throw std::runtime_error("failed to submit draw command buffer!");
  }

  VkPresentInfoKHR presentInfo{};
  presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  UINT32 Img = 0;

  presentInfo.waitSemaphoreCount = 0;
  VkSwapchainKHR swapChains[] = {Swapchain};
  presentInfo.swapchainCount = 1;
  presentInfo.pSwapchains = swapChains;
  presentInfo.pImageIndices = &ImageIndex;
  presentInfo.pResults = nullptr; // Optional

  vkQueuePresentKHR(Queue, &presentInfo);
}

/* Start render frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::render::FrameStart(VOID)
{
  //glClear(GL_COLOR_BUFFER_BIT |// gl_DEPTH_BUFFER_BIT);
  CommandBufferStart();
  PrimsToDraw.clear();
  MatrsToDraw.clear();

 // Trg->TargetStart();
} /* End of 'mzgl::render::FrameStart' function */

/* Finish render frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::render::FrameEnd(VOID)
{
 // Trg->TargetEnd();
  CommandBufferEnd();
  SwapBuffers(hDC);
} /* End of 'mzgl::render::FrameEnd' function */

/* Primitive draw function.
 * ARGUMENTS:
 *   - primitive pointer:
 *       prim *Pr;
 *   - transformation matrix:
 *       const matr &World;
 * RETURNS: None.
 */
VOID mzgl::render::Draw(const prim* Pr, const matr& World)
{
  Pr->Mtl->MtlPat->Shd->Update();
  matr
    w = Pr->Transform * World,
    winw = w.Inverse().Transpose(),
    wp = Camera.MatrProj,
    wv = Camera.MatrView,
    wvp = w * Camera.MatrVP;

  //INT
  //  RndProgId, loc,
  // // gl_prim_type = Pr->Type == prim_type::LINES ?// gl_LINES :
  //  Pr->Type == prim_type::TRIMESH ?// gl_TRIANGLES :
  //  Pr->Type == prim_type::STRIP ?// gl_TRIANGLE_STRIP :
  // // gl_POINTS;
  //Prim_data.MatrWVP = wvp;
  //Prim_data.MatrW = w;
  //Prim_data.MatrWInvTrans = winw;
  //
  //RndProgId = Pr->Mtl->Apply();
  //if ((loc =// glGetUniformLocation(RndProgId, "MatrWvp")) != -1)
  // // glUniformMatrix4fv(loc, 1,// gl_FALSE, wvp.A[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "MatrWorld")) != -1)
  // // glUniformMatrix4fv(loc, 1,// gl_FALSE, w.A[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "MatrTrans")) != -1)
  // // glUniformMatrix4fv(loc, 1,// gl_FALSE, Pr->Transform.A[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "MatrShadow")) != -1)
  // // glUniformMatrix4fv(loc, 1,// gl_FALSE, Lgh->ShadowMatr.A[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "CamLoc")) != -1)
  // // glUniform3fv(loc, 1, &Camera.Loc[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "CamDir")) != -1)
  // // glUniform3fv(loc, 1, &Camera.Dir[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "CamUp")) != -1)
  // // glUniform3fv(loc, 1, &Camera.Up[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "CamRight")) != -1)
  // // glUniform3fv(loc, 1, &Camera.Right[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "LightDir")) != -1)
  // // glUniform3fv(loc, 1, &Lgh->LightDir[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "LightColor")) != -1)
  // // glUniform3fv(loc, 1, &Lgh->LightColor[0]);
  //if ((loc =// glGetUniformLocation(RndProgId, "FrameW")) != -1)
  // // glUniform1f(loc, Camera.FrameW);
  //if ((loc =// glGetUniformLocation(RndProgId, "FrameH")) != -1)
  // // glUniform1f(loc, Camera.FrameH);
  //if ((loc =// glGetUniformLocation(RndProgId, "ProjDist")) != -1)
  // // glUniform1f(loc, Camera.ProjDist);
  //if ((loc =// glGetUniformLocation(RndProgId, "ProjSize")) != -1)
  // // glUniform1f(loc, Camera.ProjSize);
  //if ((loc =// glGetUniformLocation(RndProgId, "Time")) != -1)
  // // glUniform1f(loc, Time);
  //
  //glBindVertexArray(Pr->VA);
  //if (Pr->IBuf != 0)
  //{
  // // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, Pr->IBuf);
  // // glDrawElements(gl_prim_type, Pr->NumOfElements,// gl_UNSIGNED_INT, nullptr);
  // // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  //}
  //else
  // // glDrawArrays(gl_prim_type, 0, Pr->NumOfElements);
  //glBindVertexArray(0);
  //glUseProgram(0);
} /* End of 'mzgl::render::Draw' function */

/* END OF 'render.cpp' FILE */