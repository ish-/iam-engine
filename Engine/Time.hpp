#pragma once

class Time {
public:
    static Time& get() {
        static Time instance;
        instance.update();
        return instance;
    }

    double rate = 60; //
    double eT = 0;
    double dT = 0;
    double frameDelay = 0;

    unsigned int frame = 0;

    double update ();

    double endFrame ();

    long long getSystemTime () {
        auto chronoNow = std::chrono::system_clock::now();
        return static_cast<long long>(std::chrono::system_clock::to_time_t(chronoNow));
    }
};
