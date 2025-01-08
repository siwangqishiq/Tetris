#include "render/cmd/cmd_round_rect.h"

namespace purple{
    void RoundRectRenderCommand::putParams(
                Rect &rect, 
                glm::mat4 &matrix ,Paint &paint){
        
        rect_ = rect;
        paint_ = paint;
        modelMat_ = matrix;

        vertexCount_ = 4; //4个顶点
        attrCount_ = 3 + 4;//每个顶点3个属性长度 + 4全局的矩形信息

        float depth = engine_->getAndChangeDepthValue();
        
        int requestSize = vertexCount_ * attrCount_ * sizeof(float);
        int allocateSize = 0;
        allocatorVRam(requestSize , allocateSize);
        std::vector<float> buf(vertexCount_ * attrCount_);

        const int attrC = attrCount_;

        //v1
        buf[0 * attrC + 0] = rect.left;
        buf[0 * attrC + 1] = rect.top - rect.height;
        buf[0 * attrC + 2] = depth;

        buf[0 * attrC + 3] = rect.left;
        buf[0 * attrC + 4] = rect.top;
        buf[0 * attrC + 5] = rect.width;
        buf[0 * attrC + 6] = rect.height;

        //v2
        buf[1 * attrC + 0] = rect.left + rect.width;
        buf[1 * attrC + 1] = rect.top - rect.height;
        buf[1 * attrC + 2] = depth;

        buf[1 * attrC + 3] = rect.left;
        buf[1 * attrC + 4] = rect.top;
        buf[1 * attrC + 5] = rect.width;
        buf[1 * attrC + 6] = rect.height;

        //v3
        buf[2 * attrC + 0] = rect.left + rect.width;
        buf[2 * attrC + 1] = rect.top;
        buf[2 * attrC + 2] = depth;

        buf[2 * attrC + 3] = rect.left;
        buf[2 * attrC + 4] = rect.top;
        buf[2 * attrC + 5] = rect.width;
        buf[2 * attrC + 6] = rect.height;

        //v4
        buf[3 * attrC + 0] = rect.left;
        buf[3 * attrC + 1] = rect.top;
        buf[3 * attrC + 2] = depth;

        buf[3 * attrC + 3] = rect.left;
        buf[3 * attrC + 4] = rect.top;
        buf[3 * attrC + 5] = rect.width;
        buf[3 * attrC + 6] = rect.height;

        buildGlCommands(buf);
    }

    void RoundRectRenderCommand::runCommands(){
        if(shader_.programId <= 0){
            return;
        }
        
        shader_.useShader();
        shader_.setUniformMat4("modelMat" , modelMat_);
        shader_.setUniformMat3("transMat" , engine_->normalMatrix_);
        shader_.setUniformVec4("uColor" , paint_.color);
        
        glBindVertexArray(vao_);
        glBindBuffer(GL_ARRAY_BUFFER , vbo_);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0 , 3 , GL_FLOAT , GL_FALSE , 
            attrCount_ * sizeof(float) , 
            reinterpret_cast<void *>(vboOffset_));

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1 , 4 , GL_FLOAT , GL_FALSE , 
            attrCount_ * sizeof(float) , 
            reinterpret_cast<void *>(vboOffset_ + 3 * sizeof(float)));
        
        glDrawArrays(GL_TRIANGLE_FAN , 0 , vertexCount_);
        glBindBuffer(GL_ARRAY_BUFFER , 0);
        glBindVertexArray(0);
        // std::cout << "gl error:" << glGetError() << std::endl;
    }
    
}