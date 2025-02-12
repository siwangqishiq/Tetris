#pragma once

#include <memory>
#include <string>
#include <vector>
#include "render/common.h"

namespace purple{
    struct TextureInfo;
    class TextureImageRegion;

    class TextureImage{
    public:
        TextureImage(std::shared_ptr<TextureInfo> textureInfo);

        Rect getRect();

        virtual int getWidth();
        virtual int getHeight();
        virtual int getPixFormat();
        virtual unsigned int getTextureId();

        virtual void dispose();

        //纹理所占显存大小
        long textireSize();

        std::shared_ptr<TextureImageRegion> createImageRegion(float offsetX , float offsetY,
            float regionWidth , float regionHeight);

        //更新纹理数据
        virtual void updateTextureData(uint8_t *pData);

        std::shared_ptr<TextureInfo> getTextureInfo(){
            return textureInfo_;
        }

        
    private:
        std::shared_ptr<TextureInfo> textureInfo_;
    };

    struct Point;

    class TextureImageRegion{
    public:
        Point getOffset();
        float getWidth();
        float getHeight();
        float getTexWidth();
        float getTexHeight();
        unsigned int getTextureId();

        TextureImageRegion(unsigned int textureId,
            float offsetX , float offsetY , 
            float width , float height,
            float texWidth , float texHeight){
            textureId_ = textureId;
            offsetX_ = offsetX;
            offsetY_ = offsetY;
            width_ = width;
            height_ = height;
            texWidth_ = texWidth;
            texHeight_ = texHeight; 
        } 
    private:
        unsigned int textureId_;
        float offsetX_;
        float offsetY_;
        float width_;
        float height_;
        float texWidth_;
        float texHeight_;
    };

    //动画
    class TextureImageAnimation{
    private:
        std::vector<std::shared_ptr<TextureImageRegion>> imageRegionList_;
        // int currentFrame_ = 0;
        // long duration_ = 200;
    public:
        TextureImageAnimation(){};

        ~TextureImageAnimation(){};
    };

    //从asset目录中加载纹理图片资源
    std::shared_ptr<TextureImage> BuildImageByAsset(std::string path);

    //加载一张空的纹理 纹理内容
    std::shared_ptr<TextureImage> BuildEmptyImage(int width , int height , int format);

    //从像素数据中加载纹理
    std::shared_ptr<TextureImage> BuildImageByPixlData(uint8_t *pixelData , int width , int height, int format);
}
