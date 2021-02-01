#include "TestTexture2D.h"


namespace test
{
    TestTexture2D::TestTexture2D():
         mTranslationA(200, 200, 0)
        ,mTranslationB(400, 200, 0)
        ,mProjection(glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f)) //4:3)
        ,mView(glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0)))
    {
        float mPositions[4 * 4] = 
        {
            -50.0f, -50.0f, 0.0f, 0.0f,//0 
             50.0f, -50.0f, 1.0f, 0.0f,//1
             50.0f,  50.0f, 1.0f, 1.0f,//2
            -50.0f,  50.0f, 0.0f, 1.0f//3
        };

        uint32_t indices[2 * 3] =
        {
             0, 1, 2,
             2, 3, 0
        };

        mVAO = std::make_unique<VertexArray>();
        
        mShader = std::make_unique<Shader>("res/Shaders/Basic.shader");
        mVertexBuffer = std::make_unique <VertexBuffer> (mPositions, 4 * 4 * sizeof(float));
        VertexBufferLayout layout;
        layout.Push<float>(2);
        layout.Push<float>(2);
        mVAO->AddBuffer(*mVertexBuffer, layout);

        mIndexBuffer = std::make_unique<IndexBuffer>(indices, 6);

        mShader->Bind();
        mShader->SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        mTexture = std::make_unique<Texture>("res/textures/Bats.png");
        mShader->SetUniform1i("u_Texture", 0);
    }

    TestTexture2D::~TestTexture2D()
    {
    }
    void TestTexture2D::onUpdate(float deltatime)
    {
    }

    void TestTexture2D::onRender()
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 1.0f));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
        Renderer mRenderer;
        mTexture->Bind();
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), mTranslationA);
            glm::mat4 mvp = mProjection * mView * model;
            mShader->Bind();
            mShader->SetUniformMatrix4f("u_MVP", mvp);

            mRenderer.Draw(*mVAO, *mIndexBuffer, *mShader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), mTranslationB);
            glm::mat4 mvp = mProjection * mView * model;
            mShader->Bind();
            mShader->SetUniformMatrix4f("u_MVP", mvp);

            mRenderer.Draw(*mVAO, *mIndexBuffer, *mShader);
        }
    }
    void TestTexture2D::onImGuiRender()
    {
        ImGui::SliderFloat3("Translation A", &mTranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation B", &mTranslationB.x, 0.0f, 960.0f);
        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    }
}