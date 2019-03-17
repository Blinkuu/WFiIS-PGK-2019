//
// Created by blinku on 15.03.19.
//

#pragma once

#include <memory>

class Window;

class Application {
public:
    Application();
    ~Application() = default;

    static Application* CreateApplication();
    static void CloseApplication();

    void Run();
private:
    static std::unique_ptr<Window> m_Window;
    static bool m_Running;
private:
    static Application* m_Instance;
};
