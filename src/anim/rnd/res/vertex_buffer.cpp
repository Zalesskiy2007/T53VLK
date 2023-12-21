#include "mzgl.h"

VOID mzgl::vertex_buffer::CreateVertexBuffer( std::vector<mzgl::vertex::std> &V )
{
  VkDeviceSize bufferSize = sizeof(V[0]) * V.size();
  SizeV = V.size();
  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  Rnd->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  VOID *data;
  vkMapMemory(Rnd->LogicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
      memcpy(data, V.data(), (size_t)bufferSize);
  vkUnmapMemory(Rnd->LogicalDevice, stagingBufferMemory);

  Rnd->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);
  Rnd->CopyBuffer(stagingBuffer, vertexBuffer, bufferSize);

  vkDestroyBuffer(Rnd->LogicalDevice, stagingBuffer, nullptr);
  vkFreeMemory(Rnd->LogicalDevice, stagingBufferMemory, nullptr);
}

VOID mzgl::vertex_buffer::CreateIndexBuffer( std::vector<uint32_t> &I )
{
  SizeI = I.size();
  if (SizeI <= 0)
    return;

  VkDeviceSize bufferSize = sizeof(I[0]) * I.size();

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  Rnd->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  VOID *data;
  vkMapMemory(Rnd->LogicalDevice, stagingBufferMemory, 0, bufferSize, 0, &data);
  memcpy(data, I.data(), (size_t) bufferSize);
  vkUnmapMemory(Rnd->LogicalDevice, stagingBufferMemory);

  Rnd->CreateBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, indexBuffer, indexBufferMemory);

  Rnd->CopyBuffer(stagingBuffer, indexBuffer, bufferSize);

  vkDestroyBuffer(Rnd->LogicalDevice, stagingBuffer, nullptr);
  vkFreeMemory(Rnd->LogicalDevice, stagingBufferMemory, nullptr);
}

mzgl::vertex_buffer & mzgl::vertex_buffer::Create( std::vector<mzgl::vertex::std> &V, std::vector<uint32_t> &I )
{
  CreateVertexBuffer(V);
  CreateIndexBuffer(I);

  return *this;
}

VOID mzgl::vertex_buffer::Free( VOID )
{
  // Clean-Up swapchain...

  vkDestroyBuffer(Rnd->LogicalDevice, indexBuffer, nullptr);
  vkFreeMemory(Rnd->LogicalDevice, indexBufferMemory, nullptr);

  vkDestroyBuffer(Rnd->LogicalDevice, vertexBuffer, nullptr);
  vkFreeMemory(Rnd->LogicalDevice, vertexBufferMemory, nullptr);
}