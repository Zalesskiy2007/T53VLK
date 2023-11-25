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
 
  // Задание возможностей валидации.
  // Для подробностей смотреть спецификацию (Для версии 1.3: пункт 4.2, структура VkValidationFeaturesEXT).
  VkValidationFeaturesEXT ValidationFeatures 
  {
    .sType = VK_STRUCTURE_TYPE_VALIDATION_FEATURES_EXT,
  };
  std::vector<VkValidationFeatureEnableEXT> ValidationFeaturesEnable
  {
    VK_VALIDATION_FEATURE_ENABLE_GPU_ASSISTED_EXT,    // Используется для валидации шейдеров.
    VK_VALIDATION_FEATURE_ENABLE_BEST_PRACTICES_EXT   // Обеспечивает дополнительный вывод warning'ов.
  };
  ValidationFeatures.enabledValidationFeatureCount = (UINT32)ValidationFeaturesEnable.size();
  ValidationFeatures.pEnabledValidationFeatures = ValidationFeaturesEnable.data();
 
  InstanceCreateInfo.pNext = &ValidationFeatures;
 
  // Создание отладочных колбеков.
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
 
  // Получение физических устройств системы.
  PhysDevices.resize(PhysicalDeviceCount);
  if (vkEnumeratePhysicalDevices(Instance, &PhysicalDeviceCount, PhysDevices.data()) != VK_SUCCESS)
  {
    throw;
  }
 
  // Выбор физического устройства по требованиям.
  VkPhysicalDevice PhysDevice = VK_NULL_HANDLE;
  for (VkPhysicalDevice &Device : PhysDevices)
  {
    std::vector<VkQueueFamilyProperties> QueueFamilies;
    // Физическое устройство стоит подбирать исходя из его:
    VkPhysicalDeviceProperties DeviceProperties;                                   // основных параметров
    vkGetPhysicalDeviceProperties(Device, &DeviceProperties);                      // (например, типа устройства,
                                                                                   // пределов возможностей устройства),
 
    VkPhysicalDeviceFeatures DeviceF;                                              // дополнительных возможностей 
    vkGetPhysicalDeviceFeatures(Device, &DeviceF);                                 // (например, поддержки геометрических и
                                                                                   // теселяционных шейдеров),
 
    vkGetPhysicalDeviceQueueFamilyProperties(Device, &QueueFamilyCount, nullptr);  // поддерживаемых типов командных
                                                                                   // очередей (например, некоторые
                                                                                   //  из них преднозначены для
                                                                                   // обработки вычислительных команд).
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
 
  // Задание расширений логического устройства.
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
    PhysicalDevice,                                     // Физическое устройство.
    &DeviceInfo,                                        // Информация создания.
    nullptr,                                            // Аллокатор памяти (опциональный).
    &LogicalDevice                                      // Указатель на переменную записи созданного
                                                        // логического устройства (VkLogicalDevice).
  );
}

VOID mzgl::render::SurfaceInit( VOID )
{
  VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
    .flags = 0,
    .hinstance = GetModuleHandle(nullptr),                      // Дескриптор экземпляра приложения.
    .hwnd = hWnd,                                               // Дескриптор окна, к которому нужно привязать Vulkan.
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
    .minImageCount = 2,                                  // Минимальное количество изображений, требуемое от swapchain.

    // В некоторых случаях требуется совершать проверку, поддерживаются ли 
    // данные параметры физическим устройством для данного surface.
    // Для проверки необходимо воспользоваться 
    // vkGetPhysicalDeviceSurfaceFormatsKHR(...).
    .imageFormat = VK_FORMAT_B8G8R8A8_SRGB,                      // Параметры цветовых компонент и типов.
    .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,        // Используемое цветовое пространство, 
                                                                 // в котором задаются цвета.
    
    //.imageExtent.width = Camera.FrameW,                         // В некоторых случаях есть смысл провести
                                                         // клампинг размеров, исходя из 
   // .imageExtent.height = Camera.FrameH,                        // SurfaceCapabilities.minImageExtent.width,
                                                         // SurfaceCapabilities.maxImageExtent.width.
                                                         // Для получения SurfaceCapabilities использовать
                                                         // vkGetPhysicalDeviceSurfaceCapabilitiesKHR(...).

    .imageArrayLayers = 1,                               // Количество слоев при отрисовке.
    
    .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,   // Как планируется использовать изображения swapchain.
                                                         // В данном случае - в качестве цветовых буферов во время
                                                         // рендеринга. Пример иного использования - в качестве
                                                         // буферов глубины или stencil.
    
    .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,       // Данное значение этого поля значит, что изображения
                                                         // swapchain могут использоваться только одним семейством
                                                         // очередей. Если есть необходимость в использовании
                                                         // несколькими семействами очередей, данное поле должно
                                                         // равняться VK_SHARING_MODE_CONCURRENT, а в следующих полях
                                                         // должна содержаться информация об этих семействах очередей.
    .queueFamilyIndexCount = 0,
    .pQueueFamilyIndices = nullptr,
    
    .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,  // Преобразование, которое необходимо применить к
                                                            // изображениям (например, отражение по горизонтали).

    .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,    // Задает альфа-канал при блендинге с другими окнами.
                                                            // Для игнорирования альфа-канала используется значение
                                                            // VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR.

    // В некоторых случаях требуется совершать проверку, поддерживаются ли 
    // данные параметры физическим устройством для данного surface.
    // Для проверки необходимо воспользоваться 
    // vkGetPhysicalDeviceSurfacePresentModesKHR(...).
    .presentMode = VK_PRESENT_MODE_FIFO_KHR,             // Формат взаимодействия с очередью изображений
                                                         // (в данном случае - "First In, First Out").

    .clipped = VK_TRUE,                                     // Значение VK_TRUE в данном поле означает, что цвета
                                                            // перекрытых пикселей (например, другим окном)
                                                            // игнорируются.

    .oldSwapchain = Swapchain,                         // Прошлый swapchain. Данное поле актуально при
                                                            // пересоздании swapchain. (например, при изменении
                                                            // размеров окна).
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
    // Подробнее о параметрах создания image view объектов в разделе 6.5.
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
  
      // Описание того, как планируется использовать изображение и какая часть изображения будет использоваться.
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
   /* Структура, описывающая G-Buffer. */
  VkAttachmentDescription AttachmentDescription
  {
    .flags = 0,                                         // Флаги.
    .format = VK_FORMAT_B8G8R8A8_SRGB,                     // Формат изображения attachment'а.
    .samples = VK_SAMPLE_COUNT_1_BIT,                   // Multisampling.
    .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,              // То, что происходит с данными при начале subpass'а.
    .storeOp = VK_ATTACHMENT_STORE_OP_STORE,            // Что происходит при попытке что-либо записать.
    .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,   // То-же, но для Stencil Buffer'а.
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE, // 
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,         // Какой layout должен быть у изображения в начале рендеринга.
    .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,     // Какой layout будет у изображения в конце.
  };
  
  /* Структура, ссылающаяся на определённый G-Buffer и показывающая его состояние во время subpass'а */
  VkAttachmentReference ColorAttachmentReference
  {
    .attachment = 0,                                    // Индекс attachment'а в общем списке.
    .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // Layout изображения attachment'а во время рендеринга.
  };
  
  /* Структура, описывающая один подпроход */
  VkSubpassDescription SubpassDescription
  {
    .flags = 0,                                           // Флаги.
    .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS, // Какой тип pipeline использует данный subpass.
    .inputAttachmentCount = 0,                            // Количество входных attachment'ов.
    .pInputAttachments = nullptr,                         // Их VkAttachmentReference[].
    .colorAttachmentCount = 1,                            // Количество выходных attachment'ов.
    .pColorAttachments = &ColorAttachmentReference,   // Их VkAttachmentReference[].
    .pResolveAttachments = nullptr,                       // Attachment'ы для multisampling'а.
    .pDepthStencilAttachment = nullptr,                   // Reference Depthbuffer'а, участвующего в подпроходе.

    .preserveAttachmentCount = 0,                         // Attachment'ы, которые в данном подпроходе
                                                          // не участвуют напрямую, но данные которых должны
                                                          // сохраниться для использования в дальнейших подпроходах.
    .pPreserveAttachments = nullptr,
  };
  

  /* Структура, описывающая переход между subpass'ами */
  VkSubpassDependency SubpassDependency
  {
    .srcSubpass = VK_SUBPASS_EXTERNAL,                             // Индекс подпрохода, из которого мы переходим.
                                                                   // VK_SUBPASS_EXTERNAL означает, что srcSubpass,
                                                                   // нет, т.е. мы только начинаем сам проход.
    .dstSubpass = 0,                                               // Индекс подпрохода, в который мы переходим.
    .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, // Состояние всех Pipeline в srcSubpass'е, в
                                                                   // котором будет произведен переход в dstSubpass.
    .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, // Состояние, с которого будут получены возможности
                                                                   // доступа из dstAccessMask.
    .srcAccessMask = 0,                                            // Доступ в G-Buffer'а в srcSubpass.
    .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,         // Доступ в G-Buffer'а в dstSubpass.
    .dependencyFlags = 0,                                          // флаги
  };

  /* Структура, содержащая всю информацию для создания renderpass'а */
  VkRenderPassCreateInfo CreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO, // Тип структуры.
    .pNext = nullptr,                                   // Указатель на структуру-расширение, если она есть.
    .flags = 0,                                         // Флаги.
    .attachmentCount = 1,                               // Количество color attachment'ов во всём renderpass'е.
    .pAttachments = &AttachmentDescription,         // Их описания.
    .subpassCount = 1,                                  // Количество подпроходов рендеринга.
    .pSubpasses = &SubpassDescription,              // Описания подпроходов.
    .dependencyCount = 1,                               // Количество переходов между subpass'ами.
    .pDependencies = &SubpassDependency,            // Их описания.
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
      .layers = 1,                                                   // Количество слоев отрисовки буфера.
    };
  
    if (vkCreateFramebuffer(LogicalDevice, &FrameBufferCreateInfo, nullptr, &FrameBuffers[i]) != VK_SUCCESS)
      throw;
  }
}

VOID mzgl::render::QueueInit( VOID )
{
  // Получение дескрипторов для каждого семейства очередей.
  vkGetDeviceQueue(
    LogicalDevice, // Логическое устройство.
    0,      // Индекс семейства очередей.
    0,      // Индекс очереди.
    &Queue  // Указатель на переменную VkQueue.
  );
}

VOID mzgl::render::CommandPoolInit( VOID )
{
  queue_family_indices Indices = GetQueueFamilyIndices();
  VkCommandPoolCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,      // Тип структуры.
    .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, // Флаги пула команд.
    .queueFamilyIndex = Indices.GraphicsFamily.value(),
  };

  vkCreateCommandPool(
    LogicalDevice,               // Логическое устройство.
    &Info,                // Информация создания.
    nullptr,              // Аллокатор памяти (опциональный).
    &CommandPool          // Указатель на переменную VkCommandPool.
  );
}

VOID mzgl::render::CommandBufferInit( VOID )
{
  VkCommandBufferAllocateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, // Тип структуры.
    .commandPool = CommandPool,                              // Используемый пул команд.
    .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,                // Тип командного буфера.
    .commandBufferCount = 1                                  // Количество выделяемых буферов.
  };
  
  vkAllocateCommandBuffers(
    LogicalDevice,               // Логическое устройство.
    &Info,                // Информация создания.
    &CommandBuffer        // Указатель на массив переменных VkCommandBuffer.
  );
}

VOID mzgl::render::FenceInit( VOID )
{
  VkFenceCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, // Тип струкутры.
    .flags = VK_FENCE_CREATE_SIGNALED_BIT   // Базовое состояние.
  };

  vkCreateFence(
    LogicalDevice,  // Логическое устройство.
    &Info,   // Информация создания.
    nullptr, // Аллокатор памяти (опциональный).
    &Fence   // Указатель на переменную VkFence.
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
  /* Удаление RenderPass */
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
    LogicalDevice,      // Логическое устройство.
    CommandPool, // Удаляемый объект.
    nullptr      // Аллокатор памяти (должен совпадать с использованным в создании).
  );
}

VOID mzgl::render::CommandBufferClose( VOID )
{
  // Empty
}

VOID mzgl::render::FenceClose( VOID )
{   
  VkResult Result = vkWaitForFences(
    LogicalDevice,      // Логическое устройство.
    1, // Количество объектов для ожидания.
    &Fence,      // Массив объектов для ожидания.
    TRUE, // Ожидание всех, либо первого активированного.
    UINT64_MAX      // Лимит времени ожидания (максимум: UINT64_MAX).
  );
  vkResetFences(
    LogicalDevice,      // Логическое устройство.
    1, // Количество объектов для сброса.
    &Fence      // Массив объектов для сброса.
  );

  vkDestroyFence(
    LogicalDevice,  // Логический девайс.
    Fence,    // Удаляемый объект.
    nullptr // Аллокатор памяти (должен совпадать с использованным в создании).
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
    vkDestroyFramebuffer(LogicalDevice, FrameBuffers[i], nullptr);          // О Frame buffers в разделе 2.5.
  
  for (INT i = 0; i < SwapchainImageViews.size(); i++)
    vkDestroyImageView(LogicalDevice, SwapchainImageViews[i], nullptr);

  VkSwapchainKHR old = SwapchainInit();

  vkDestroySwapchainKHR(LogicalDevice, old, nullptr);

  FrameBuffersInit();


} /* End of 'mzgl::render::Resize' function */

VOID mzgl::render::CommandBufferStart( VOID )
{
  VkResult Result = vkWaitForFences(
    LogicalDevice,      // Логическое устройство.
    1, // Количество объектов для ожидания.
    &Fence,      // Массив объектов для ожидания.
    TRUE, // Ожидание всех, либо первого активированного.
    UINT64_MAX      // Лимит времени ожидания (максимум: UINT64_MAX).
  );
  // Возможные результаты (без учёта кодов ошибок).
  switch (Result)
  {
  case VK_SUCCESS:
    break;
  case VK_TIMEOUT:
    return;
  }

  vkResetFences(
    LogicalDevice,      // Логическое устройство.
    1, // Количество объектов для сброса.
    &Fence      // Массив объектов для сброса.
  );

  vkAcquireNextImageKHR(LogicalDevice, Swapchain, UINT64_MAX, VK_NULL_HANDLE, Fence, &ImageIndex);

  vkResetCommandBuffer(
    CommandBuffer, // Командный буфер.
    0              // Флаги сброса.
  );

  VkCommandBufferBeginInfo BeginInfo
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, // Тип струкутры.
    .flags = 0,                                           // Флаги использования буфера.
    .pInheritanceInfo = nullptr,                          // Специализация буфера. Необходимо для вторичных.
  };
  vkBeginCommandBuffer(CommandBuffer, &BeginInfo);

  //std::array<VkClearValue, 1> ClearValues = {{0.1f, 0.9f, 0.3f}}; // Подробнее в пункте 8.1
  std::vector<VkClearValue> ClearValues {{0.3f, 0.5f, 0.1f}}; // Подробнее в пункте 8.1

  VkRenderPassBeginInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO, // Тип струкутры.
    .renderPass = RenderPass,                          // Используемый проход рендера.
    .framebuffer = FrameBuffers[ImageIndex],                        // Используемый буфер кадра.
    .renderArea =
    {
      .offset = // Смещение области буфера кадра, доступной для отрисовки.
      {
        .x = 0,
        .y = 0
      },
      .extent = // Размер области буфера кадра, доступной для отрисовки.
      {
        .width = SwapChainExtent.width,
        .height = SwapChainExtent.height
      }
    },
    .clearValueCount = static_cast<UINT32>(ClearValues.size()), // Количество значений очистки буфера кадра.
    .pClearValues = ClearValues.data()                          // Значения очистки буфера кадра.
  };  

  vkCmdBeginRenderPass(
    CommandBuffer,             // Командный буфер.
    &Info,                     // Информация начала.
    VK_SUBPASS_CONTENTS_INLINE // Тип контента подпрохода
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
    LogicalDevice,      // Логическое устройство.
    1, // Количество объектов для ожидания.
    &Fence,      // Массив объектов для ожидания.
    TRUE, // Ожидание всех, либо первого активированного.
    UINT64_MAX      // Лимит времени ожидания (максимум: UINT64_MAX).
  );
  vkResetFences(
    LogicalDevice,      // Логическое устройство.
    1, // Количество объектов для сброса.
    &Fence      // Массив объектов для сброса.
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