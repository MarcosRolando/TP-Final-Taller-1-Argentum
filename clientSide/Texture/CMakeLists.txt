cmake_minimum_required(VERSION 3.10.2)

add_library(texture NPCTexture.cpp PlayerTexture.cpp Texture.cpp EntityTexture.h
        EntityTexture.cpp TextureRepository.cpp TextureRepository.h PlayerEquipment.h TextureID.h)
