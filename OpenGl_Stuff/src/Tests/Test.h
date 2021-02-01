#pragma once
#include "ErrorHandler.h"
#include <string>
#include <vector>
#include <functional>

namespace test 
{

    class Test
    {
    public:
        Test(){}
        virtual ~Test(){}
        
        virtual void onUpdate(float deltatime) {}
        virtual void onRender() {}
        virtual void onImGuiRender() {}
    };

    class TestMenu : public Test
    {
    public:
        TestMenu(Test*& currentTest);

        void onImGuiRender() override ;

        template<typename T>
        void RegisterTest(const std::string& name) 
        {
            std::cout << "Registering test " << name << std::endl;
            mTests.push_back(std::make_pair(name, []() { return  new T(); }));
        }

    private:
        Test*& mCurrentTest;
        std::vector<std::pair<std::string, std::function<Test*()>>> mTests;
    };

}