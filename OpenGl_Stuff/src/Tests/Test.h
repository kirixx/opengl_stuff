#pragma once


namespace test 
{

    class Test
    {
    public:
        Test() : mTests{"ClearColor", "RenderTest"}{}
        virtual ~Test(){}
        
        virtual void onUpdate(float deltatime) {}
        virtual void onRender() { }
        virtual void onImGuiRender() {}

        const char* mTests[2];
    };

}