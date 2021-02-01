#pragma once
#include "ErrorHandler.h"
#include "Test.h"
#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"
#include <memory>

namespace test
{
	class TestTexture2D : public Test
	{
    public:
        TestTexture2D();
        ~TestTexture2D();

        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;
    
    private:        
        glm::vec3 mTranslationA;
        glm::vec3 mTranslationB;
        glm::mat4 mProjection;
        glm::mat4 mView;
        std::unique_ptr<VertexArray> mVAO;
        std::unique_ptr<IndexBuffer> mIndexBuffer;
        std::unique_ptr<VertexBuffer> mVertexBuffer;
        std::unique_ptr<Shader> mShader;
        std::unique_ptr<Texture> mTexture;
    };
}