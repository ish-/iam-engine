#pragma once

class Time {
public:
    static Time& get() {
        static Time instance;
        instance.update();
        return instance;
    }

    double rate = 60; // fps
    double eT = 0; // elapsed time
    double dT = 0; // delta time
    double frameDelay = 0; // delta time
    double abs = 0; // delta time

    double update ();

    double endFrame ();
};
