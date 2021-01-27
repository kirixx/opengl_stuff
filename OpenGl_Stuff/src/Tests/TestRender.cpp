#include "TestRender.h"


namespace test
{
    TestRender::TestRender():
        mPositions
        {
            -50.0f, -50.0f, 0.0f, 0.0f,//0 
             50.0f, -50.0f, 1.0f, 0.0f,//1
             50.0f,  50.0f, 1.0f, 1.0f,//2
            -50.0f,  50.0f, 0.0f, 1.0f//3
        }
        ,mIndices
        {
             0, 1, 2,
             2, 3, 0
        }
        ,mVA()
        ,mIB(mIndices, 2 * 3)
        ,mVB(mPositions, 4 * 4 * sizeof(float))
        ,mLayout()
        ,mTranslationA(200, 200, 0)
        ,mTranslationB(400, 200, 0)
        ,mProjection()
        ,mView()
        ,mRenderer()
        ,mShader("res/Shaders/Basic.shader")
        ,mTexture("res/textures/Bats.png")
    {

        mLayout.Push<float>(2);
        mLayout.Push<float>(2);
        mVA.AddBuffer(mVB, mLayout);

        mProjection = glm::ortho(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1.0f); //4:3
        mView = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));

        mShader.Bind();
        mShader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

        mTexture.Bind();
        mShader.SetUniform1i("u_Texture", 0);

        mVA.Unbind();
        mVB.Unbind();
        mIB.Unbind();
        mShader.Unbind();

    }

    TestRender::~TestRender()
    {
    }

    void TestRender::onUpdate(float deltatime)
    {
    }
    void TestRender::onRender()
    {
        mRenderer.Clear();
        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), mTranslationA);
            glm::mat4 mvp = mProjection * mView * model;
            mShader.Bind();
            mShader.SetUniformMatrix4f("u_MVP", mvp);

            mRenderer.Draw(mVA, mIB, mShader);
        }

        {
            glm::mat4 model = glm::translate(glm::mat4(1.0f), mTranslationB);
            glm::mat4 mvp = mProjection * mView * model;
            mShader.Bind();
            mShader.SetUniformMatrix4f("u_MVP", mvp);

            mRenderer.Draw(mVA, mIB, mShader);
        }
    }
    void TestRender::onImGuiRender()
    {
        ImGui::SliderFloat3("Translation A", &mTranslationA.x, 0.0f, 960.0f);
        ImGui::SliderFloat3("Translation B", &mTranslationB.x, 0.0f, 960.0f);
    }
}