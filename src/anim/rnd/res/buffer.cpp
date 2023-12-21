#include "mzgl.h"

mzgl::buffer & mzgl::buffer::Create( uint32_t bufferSize )
{
  Size = bufferSize;
  uniformBuffers.resize(Rnd->MAX_FRAMES_IN_FLIGHT);
  uniformBuffersMemory.resize(Rnd->MAX_FRAMES_IN_FLIGHT);
  uniformBuffersMapped.resize(Rnd->MAX_FRAMES_IN_FLIGHT);

  for (size_t i = 0; i < Rnd->MAX_FRAMES_IN_FLIGHT; i++)
  {
    Rnd->CreateBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

    vkMapMemory(Rnd->LogicalDevice, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
  }

  return *this;
}

VOID mzgl::buffer::Free( VOID )
{
  for (size_t i = 0; i < Rnd->MAX_FRAMES_IN_FLIGHT; i++)
  {
    vkDestroyBuffer(Rnd->LogicalDevice, uniformBuffers[i], nullptr);
    vkFreeMemory(Rnd->LogicalDevice, uniformBuffersMemory[i], nullptr);
  }
}