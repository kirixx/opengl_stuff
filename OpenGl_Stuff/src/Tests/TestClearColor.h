#pragma once

#include "Test.h"

namespace test
{
    class TestClearColor : public Test
    {
    public:
        TestClearColor();
        ~TestClearColor();

        void onUpdate(float deltatime) override;
        void onRender() override;
        void onImGuiRender() override;

    protected:
        float mClearColor[4];
    };
}
