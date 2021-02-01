#include "TestClearColor.h"

#include "ErrorHandler.h"

namespace test
{
    TestClearColor::TestClearColor()
        : mClearColor {0.2f, 0.3f, 0.8f, 1.0f}
    {

    }

    TestClearColor::~TestClearColor()
    {
    }

    void TestClearColor::onUpdate(float deltatime)
    {
    }
    void TestClearColor::onRender()
    {
        GLCall(glClearColor(mClearColor[0], mClearColor[1], mClearColor[2], mClearColor[3]));
        GLCall(glClear(GL_COLOR_BUFFER_BIT));
    }
    void TestClearColor::onImGuiRender()
    {
        ImGui::ColorEdit4("Clear Color ", mClearColor);
    }
}