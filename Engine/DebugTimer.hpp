#pragma once
#include <iostream>
#include <chrono>
#include <string>

class DebugTimer {
public:
    DebugTimer(const std::string& name, bool autoStop = true)
        : m_Name(name), m_AutoStop(autoStop), m_Stopped(false) {
        m_StartTimepoint = std::chrono::high_resolution_clock::now();
    }

    ~DebugTimer() {
        if (m_AutoStop && !m_Stopped)
            stop();
    }

    void stop() {
        auto endTimepoint = std::chrono::high_resolution_clock::now();
        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

        float duration = (end - start) * 0.001f; // convert microseconds to milliseconds
        std::cout << "[" << m_Name << "] Duration: " << duration << " ms\n";

        m_Stopped = true;
    }

private:
    std::string m_Name;
    bool m_AutoStop;
    bool m_Stopped;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
};
