#include <iostream>
#include "src/application.hpp"

int main()
{
   Application* application = Application::CreateApplication();
   application->Run();
   delete application;
}