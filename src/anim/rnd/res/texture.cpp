/* FILE NAME   : texture.cpp
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 02.08.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Resorces system module.
 *               texture module.
 */

#include "mzgl.h"
#include <cstdio>

IWICImagingFactory2 *mzgl::texture::WicFactory = nullptr;

std::vector<DWORD> mzgl::texture::LoadAll( std::string Name, INT *tW, INT *tH)
{
  std::vector<DWORD> Res;

  *tW = 0;
  *tH = 0;

  if (WicFactory == nullptr)
  {
    CoInitialize(nullptr);
    CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_ALL, IID_PPV_ARGS(&WicFactory));
  }
  // Load through Window Image Component
  if (WicFactory != nullptr)
  {
    IWICBitmapDecoder *Decoder {};
    std::wstring FileNameW {Name.begin(), Name.end()};

    // Create decoder (loader)
    WicFactory->CreateDecoderFromFilename(FileNameW.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &Decoder);
    if (Decoder != nullptr)
    {
      IWICBitmapFrameDecode *Frame {};
      Decoder->GetFrame(0, &Frame);
      UINT fw = 0, fh = 0;

      if (Frame != nullptr)
      {
        Frame->GetSize(&fw, &fh);
        if (fw != 0 && fh != 0)
        {           
          // Converting image format to standard - RGBA with 8-bits per pixel
          IWICFormatConverter *Convert {};
          WicFactory->CreateFormatConverter(&Convert);
          if (Convert != nullptr)
          {
            // Converter initialization
            Convert->Initialize(Frame, GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);

            // Size checking
            Convert->GetSize(&fw, &fh);
            if (fw != 0 && fh != 0)
            {
              this->W = fw;
              this->H = fh;
              Res.resize((size_t)fw * fh);

              // Copying image pixels to container pixel array
              WICRect Rect {0, 0, static_cast<INT>(fw), static_cast<INT>(fh)};
              Convert->CopyPixels(&Rect, fw * 4, fw * fh * 4, (BYTE *)Res.data());
            }
            Convert->Release();
          }
        }
        Frame->Release();
      }
      Decoder->Release();

      *tW = fw;
      *tH = fh;
    }
  }

  return Res;
}

VOID mzgl::texture::CreateImage( uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory )
{
  VkImageCreateInfo imageInfo{};
  imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  imageInfo.imageType = VK_IMAGE_TYPE_2D;
  imageInfo.extent.width = width;
  imageInfo.extent.height = height;
  imageInfo.extent.depth = 1;
  imageInfo.mipLevels = 1;
  imageInfo.arrayLayers = 1;
  imageInfo.format = format;
  imageInfo.tiling = tiling;
  imageInfo.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
  imageInfo.usage = usage;
  imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
  imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

  if (vkCreateImage(Rnd->LogicalDevice, &imageInfo, nullptr, &image) != VK_SUCCESS)
  {
    throw std::runtime_error("failed to create image!");
  }

  VkMemoryRequirements memRequirements;
  vkGetImageMemoryRequirements(Rnd->LogicalDevice, image, &memRequirements);

  VkMemoryAllocateInfo allocInfo{};
  allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.allocationSize = memRequirements.size;
  allocInfo.memoryTypeIndex = Rnd->findMemoryType(memRequirements.memoryTypeBits, properties);

  if (vkAllocateMemory(Rnd->LogicalDevice, &allocInfo, nullptr, &imageMemory) != VK_SUCCESS)
  {
    throw std::runtime_error("failed to allocate image memory!");
  }

  vkBindImageMemory(Rnd->LogicalDevice, image, imageMemory, 0);
}

mzgl::texture & mzgl::texture::Create( VOID )
{
  CreateTextureImage();
  CreateTextureImageView();
  CreateTextureSampler();

  return *this;
}

VOID mzgl::texture::CreateTextureImage( VOID )
{
  INT texWidth, texHeight, texChannels = 4;
  std::vector<DWORD> pixels = LoadAll(Rnd->Path + Name, &texWidth, &texHeight);
  VkDeviceSize imageSize = texWidth * texHeight * 4;

  VkBuffer stagingBuffer;
  VkDeviceMemory stagingBufferMemory;
  Rnd->CreateBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

  VOID *data;
  vkMapMemory(Rnd->LogicalDevice, stagingBufferMemory, 0, imageSize, 0, &data);
      memcpy(data, pixels.data(), static_cast<size_t>(imageSize));
  vkUnmapMemory(Rnd->LogicalDevice, stagingBufferMemory);

  CreateImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);

  Rnd->TransitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
  Rnd->CopyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
  Rnd->TransitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_SRGB, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

  vkDestroyBuffer(Rnd->LogicalDevice, stagingBuffer, nullptr);
  vkFreeMemory(Rnd->LogicalDevice, stagingBufferMemory, nullptr);
}

VOID mzgl::texture::CreateTextureImageView( VOID )
{
  textureImageView = Rnd->CreateImageView(textureImage, VK_FORMAT_R8G8B8A8_SRGB);
}

VOID mzgl::texture::CreateTextureSampler( VOID )
{
  VkSamplerCreateInfo samplerInfo{};
  samplerInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  samplerInfo.magFilter = VK_FILTER_LINEAR;
  samplerInfo.minFilter = VK_FILTER_LINEAR;

  samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
  samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

  /* TODO
  samplerInfo.anisotropyEnable = VK_TRUE;
  VkPhysicalDeviceProperties properties{};
  vkGetPhysicalDeviceProperties(Rnd->PhysicalDevice, &properties);
  samplerInfo.maxAnisotropy = properties.limits.maxSamplerAnisotropy;
  */

  samplerInfo.anisotropyEnable = VK_FALSE;
  samplerInfo.maxAnisotropy = 1.0f;


  samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
  samplerInfo.unnormalizedCoordinates = VK_FALSE;
  samplerInfo.compareEnable = VK_FALSE;
  samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

  samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
  samplerInfo.mipLodBias = 0.0f;
  samplerInfo.minLod = 0.0f;
  samplerInfo.maxLod = 0.0f;

   if (vkCreateSampler(Rnd->LogicalDevice, &samplerInfo, nullptr, &textureSampler) != VK_SUCCESS)
   {
     throw std::runtime_error("failed to create texture sampler!");
   }
}

/* Free texture function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID mzgl::texture::Free( VOID )
{
  vkDestroySampler(Rnd->LogicalDevice, textureSampler, nullptr);
  vkDestroyImageView(Rnd->LogicalDevice, textureImageView, nullptr);

  vkDestroyImage(Rnd->LogicalDevice, textureImage, nullptr);
  vkFreeMemory(Rnd->LogicalDevice, textureImageMemory, nullptr);
} /* End of 'mzgl::texture::Free' function */

/* END OF 'texture.cpp' FILE */