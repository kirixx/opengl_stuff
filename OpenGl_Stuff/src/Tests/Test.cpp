#include "Test.h"
namespace test
{
    TestMenu::TestMenu(Test*& currentTest)
        : mCurrentTest(currentTest)
    {

    }

    void TestMenu::onImGuiRender()
    {   
        for (auto& test : mTests)
        {
            if (ImGui::Button(test.first.c_str()))
                mCurrentTest = test.second();
        }
    }

}