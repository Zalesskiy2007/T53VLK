#include "mzgl.h"

mzgl::pipeline & mzgl::pipeline::Create( mzgl::prim_type TypeDraw )
{
  std::vector<VkDynamicState> dynamicStates = 
  {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR
  };
  
  VkPipelineDynamicStateCreateInfo dynamicState{};

  dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
  dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
  dynamicState.pDynamicStates = dynamicStates.data();

  VkPipelineVertexInputStateCreateInfo vertexInputInfo{};

  auto bindingDescription =    mzgl::vertex::std::getBindingDescription();
  auto attributeDescriptions = mzgl::vertex::std::getAttributeDescriptions();

  vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
  vertexInputInfo.vertexBindingDescriptionCount = 1; // 1 -> 0 if not work
  vertexInputInfo.pVertexBindingDescriptions = &bindingDescription; // Optional
  vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(attributeDescriptions.size()); // -> 0 if not work
  vertexInputInfo.pVertexAttributeDescriptions = attributeDescriptions.data(); // Optional

  VkPipelineInputAssemblyStateCreateInfo inputAssembly{};

  inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
  inputAssembly.topology = TypeDraw == mzgl::prim_type::TRIMESH ? VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST : 
                           TypeDraw == mzgl::prim_type::POINTS ? VK_PRIMITIVE_TOPOLOGY_POINT_LIST : 
                           VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
  inputAssembly.primitiveRestartEnable = VK_FALSE;

  VkViewport viewport{};
  viewport.x = 0.0f;
  viewport.y = 0.0f;
  viewport.width = (float) Rnd->SwapChainExtent.width;
  viewport.height = (float) Rnd->SwapChainExtent.height;
  viewport.minDepth = 0.0f;
  viewport.maxDepth = 1.0f;

  VkRect2D scissor{};
  scissor.offset = {0, 0};
  scissor.extent = Rnd->SwapChainExtent;

  VkPipelineViewportStateCreateInfo viewportState{};

  viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
  viewportState.viewportCount = 1;
  viewportState.pViewports = &viewport;
  viewportState.scissorCount = 1;
  viewportState.pScissors = &scissor;

  VkPipelineRasterizationStateCreateInfo rasterizer{};
  rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
  rasterizer.depthClampEnable = VK_FALSE;

  rasterizer.rasterizerDiscardEnable = VK_FALSE;

  rasterizer.polygonMode = VK_POLYGON_MODE_FILL;

  rasterizer.lineWidth = 1.0f;

  rasterizer.cullMode = VK_CULL_MODE_NONE;
  rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;

  rasterizer.depthBiasEnable = VK_FALSE;
  rasterizer.depthBiasConstantFactor = 0.0f; // Optional
  rasterizer.depthBiasClamp = 0.0f; // Optional
  rasterizer.depthBiasSlopeFactor = 0.0f; // Optional

  VkPipelineMultisampleStateCreateInfo multisampling{};

  multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  multisampling.sampleShadingEnable = VK_FALSE;
  multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;
  multisampling.minSampleShading = 1.0f; // Optional
  multisampling.pSampleMask = nullptr; // Optional
  multisampling.alphaToCoverageEnable = VK_FALSE; // Optional
  multisampling.alphaToOneEnable = VK_FALSE; // Optional

  VkPipelineColorBlendAttachmentState colorBlendAttachment{};
  colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
  colorBlendAttachment.blendEnable = VK_FALSE;
  colorBlendAttachment.srcColorBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstColorBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.colorBlendOp = VK_BLEND_OP_ADD; // Optional
  colorBlendAttachment.srcAlphaBlendFactor = VK_BLEND_FACTOR_ONE; // Optional
  colorBlendAttachment.dstAlphaBlendFactor = VK_BLEND_FACTOR_ZERO; // Optional
  colorBlendAttachment.alphaBlendOp = VK_BLEND_OP_ADD; // Optional

  VkPipelineColorBlendStateCreateInfo colorBlending{};
  colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
  colorBlending.logicOpEnable = VK_FALSE;
  colorBlending.logicOp = VK_LOGIC_OP_COPY; // Optional
  colorBlending.attachmentCount = 1;
  colorBlending.pAttachments = &colorBlendAttachment;
  colorBlending.blendConstants[0] = 0.0f; // Optional
  colorBlending.blendConstants[1] = 0.0f; // Optional
  colorBlending.blendConstants[2] = 0.0f; // Optional
  colorBlending.blendConstants[3] = 0.0f; // Optional

    // В данном случае указаны параметры для отключения сглаживания.
  VkPipelineMultisampleStateCreateInfo MSCreateInfo {};
  MSCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
  MSCreateInfo.sampleShadingEnable = VK_FALSE;                                  // При данном значении цвет пикселя
                                                                    // определяется только сэмплом в его центре,
                                                                    // при VK_TRUE - интерполяцией сэмплов
                                                                    // вокруг данного пикселя.
  
  MSCreateInfo.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;                    // При данном значении мультисэмплинг выключен,
                                                                      // при увеличении значения качество изображения
                                                                      // повышается, но увеличивается количество
                                                                      // ресурсов, затрачиваемых на отрисовку.

  VkDescriptorSetLayoutBinding uboLayoutBinding{};
  uboLayoutBinding.binding = 0;
  uboLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  uboLayoutBinding.descriptorCount = 1;
  uboLayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
  uboLayoutBinding.pImmutableSamplers = nullptr; // Optional

  VkDescriptorSetLayoutBinding samplerLayoutBinding{};
  samplerLayoutBinding.binding = 1;
  samplerLayoutBinding.descriptorCount = 1;
  samplerLayoutBinding.descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  samplerLayoutBinding.pImmutableSamplers = nullptr;
  samplerLayoutBinding.stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT;


  std::array<VkDescriptorSetLayoutBinding, 2> bindings = {uboLayoutBinding, samplerLayoutBinding};
  VkDescriptorSetLayoutCreateInfo layoutInfo{};
  layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.bindingCount = static_cast<uint32_t>(bindings.size());
  layoutInfo.pBindings = bindings.data();

  if (vkCreateDescriptorSetLayout(Rnd->LogicalDevice, &layoutInfo, nullptr, &descriptorSetLayout) != VK_SUCCESS)
  {
    throw std::runtime_error("failed to create descriptor set layout!");
  }

  VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
  pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  pipelineLayoutInfo.setLayoutCount = 1; // Optional
  pipelineLayoutInfo.pSetLayouts = &descriptorSetLayout; // Optional
  pipelineLayoutInfo.pushConstantRangeCount = 0; // Optional
  pipelineLayoutInfo.pPushConstantRanges = nullptr; // Optional

  if (vkCreatePipelineLayout(Rnd->LogicalDevice, &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS)
  {
    throw std::runtime_error("failed to create pipeline layout!");
  }

  std::array<VkDescriptorPoolSize, 2> poolSizes{};
  poolSizes[0].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
  poolSizes[0].descriptorCount = static_cast<uint32_t>(Rnd->MAX_FRAMES_IN_FLIGHT);
  poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  poolSizes[1].descriptorCount = static_cast<uint32_t>(Rnd->MAX_FRAMES_IN_FLIGHT);

  VkDescriptorPoolCreateInfo poolInfo{};
  poolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  poolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
  poolInfo.pPoolSizes = poolSizes.data();
  poolInfo.maxSets = static_cast<uint32_t>(Rnd->MAX_FRAMES_IN_FLIGHT);

  if (vkCreateDescriptorPool(Rnd->LogicalDevice, &poolInfo, nullptr, &descriptorPool) != VK_SUCCESS)
  {
    throw std::runtime_error("failed to create descriptor pool!");
  }


  std::vector<VkDescriptorSetLayout> layouts(Rnd->MAX_FRAMES_IN_FLIGHT, descriptorSetLayout);
  VkDescriptorSetAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.descriptorPool = descriptorPool;
  allocInfo.descriptorSetCount = static_cast<uint32_t>(Rnd->MAX_FRAMES_IN_FLIGHT);
  allocInfo.pSetLayouts = layouts.data();

  descriptorSets.resize(Rnd->MAX_FRAMES_IN_FLIGHT);
  if (vkAllocateDescriptorSets(Rnd->LogicalDevice, &allocInfo, descriptorSets.data()) != VK_SUCCESS)
  {
    throw std::runtime_error("failed to allocate descriptor sets!");
  }

  Buf = Rnd->BufferCreate(Name, sizeof(prim_data));
  Img = Rnd->TxtLoad("/bin/textures/" + Name);

  for (size_t i = 0; i < Rnd->MAX_FRAMES_IN_FLIGHT; i++)
  {

    //todo check buffer existing
    VkDescriptorBufferInfo bufferInfo{};
    bufferInfo.buffer = Buf->uniformBuffers[i];
    bufferInfo.offset = 0;
    bufferInfo.range = Buf->Size;

    //todo check image existing
    VkDescriptorImageInfo imageInfo{};
    imageInfo.imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    imageInfo.imageView = Img->textureImageView;
    imageInfo.sampler = Img->textureSampler;

    std::array<VkWriteDescriptorSet, 2> descriptorWrites{};

    descriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites[0].dstSet = descriptorSets[i];
    descriptorWrites[0].dstBinding = 0;
    descriptorWrites[0].dstArrayElement = 0;
    descriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
    descriptorWrites[0].descriptorCount = 1;
    descriptorWrites[0].pBufferInfo = &bufferInfo;

    descriptorWrites[1].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    descriptorWrites[1].dstSet = descriptorSets[i];
    descriptorWrites[1].dstBinding = 1;
    descriptorWrites[1].dstArrayElement = 0;
    descriptorWrites[1].descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
    descriptorWrites[1].descriptorCount = 1;
    descriptorWrites[1].pImageInfo = &imageInfo;

    vkUpdateDescriptorSets(Rnd->LogicalDevice, static_cast<uint32_t>(descriptorWrites.size()), descriptorWrites.data(), 0, nullptr);
  }

  s = Rnd->ShaderCreate(Name);

  VkGraphicsPipelineCreateInfo PipelineCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
    .stageCount = 2,
    .pStages = s->shaderStages,
    .pVertexInputState = &vertexInputInfo,
   //...                                                   // Указатели на остальные ранее созданные структуры.
    .pColorBlendState = &colorBlending,
    .renderPass = Rnd->RenderPass,
    .basePipelineHandle = VK_NULL_HANDLE,                  // Данные поля позволяют создать pipeline на базе другого.
    .basePipelineIndex = -1,
  };
  PipelineCreateInfo.layout = pipelineLayout;
  PipelineCreateInfo.layout = pipelineLayout;
  PipelineCreateInfo.pRasterizationState = &rasterizer;
  PipelineCreateInfo.subpass = 0;
  PipelineCreateInfo.pDynamicState = &dynamicState;  
  PipelineCreateInfo.pViewportState = &viewportState;
  PipelineCreateInfo.pInputAssemblyState = &inputAssembly;
  PipelineCreateInfo.pDepthStencilState = nullptr;
  PipelineCreateInfo.pMultisampleState = &MSCreateInfo;

  if (vkCreateGraphicsPipelines(Rnd->LogicalDevice, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &Pipeline) != VK_SUCCESS)
  {
    throw;
  }

  return *this;
}

/* Free pipeline function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::pipeline::Free( VOID )
{
  Rnd->ShaderFree(s);

  vkDestroyDescriptorPool(Rnd->LogicalDevice, descriptorPool, nullptr);

  vkDestroyDescriptorSetLayout(Rnd->LogicalDevice, descriptorSetLayout, nullptr);

  vkDestroyDescriptorSetLayout(Rnd->LogicalDevice, descriptorSetLayout, nullptr);

  vkDestroyPipelineLayout(Rnd->LogicalDevice, pipelineLayout, nullptr);

  vkDestroyDescriptorSetLayout(Rnd->LogicalDevice, descriptorSetLayout, nullptr);

  vkDestroyPipeline(Rnd->LogicalDevice, Pipeline, nullptr);
} /* End of 'mzgl::pipeline::Free' function */