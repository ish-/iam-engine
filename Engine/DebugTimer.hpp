#pragma once
#include <iostream>
#include <chrono>
#include <string>
#include "imgui.h"
#include "GUI.hpp"

static uint T_IMGUI = 1 << 1;
static uint T_AUTOSTOP = 1 << 2;

class DebugTimer {
public:
    DebugTimer(const std::string& name, uint params = 0)
        : m_Name(name), params(params), m_Stopped(false) {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~DebugTimer() {
        if (params & T_AUTOSTOP && !m_Stopped)
            stop();
    }

    void stop() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        float duration = (end - start) * 0.001f; // convert microseconds to milliseconds
        if (params & T_IMGUI) {
            if (GUI::get().conf.showDebug) {
                ImGui::Begin("iam-engine");
                    ImGui::Text("%s: %.2f ms", m_Name.c_str(), duration);
                ImGui::End();
            }
        }
        else {
            std::cout << "DebugTimer [" << m_Name << "]: " << duration << " ms\n";
        }

        m_Stopped = true;
    }

private:
    std::string m_Name;
    uint params = 0;
    bool m_AutoStop = true;
    bool m_Stopped = false;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};
