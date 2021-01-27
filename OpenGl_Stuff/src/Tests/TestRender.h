#pragma once

#include "Test.h"
#include "Renderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include "Texture.h"
namespace test
{
	class TestRender : public Test
	{
    public:
        TestRender();
        ~TestRender();

        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;
    
    private:
        float mPositions[4*4];
        uint32_t mIndices[2*3];
        VertexArray mVA;
        IndexBuffer mIB;
        VertexBuffer mVB;
        VertexBufferLayout mLayout;
        glm::vec3 mTranslationA;
        glm::vec3 mTranslationB;
        glm::mat4 mProjection;
        glm::mat4 mView;
        Renderer mRenderer;
        Shader mShader;
        Texture mTexture;
    };
}