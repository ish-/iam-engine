#pragma once
#include <SDL3/SDL_timer.h>

class Time {
public:
    static Time& get() {
        static Time instance;
        return instance;
    }

    double rate = 60; // fps
    double eT = 0; // elapsed time
    double dT = 0; // delta time

    double update () {
        double now = SDL_GetTicks() / 1000.;
        dT = now - eT;
        eT = now;
        return dT;
    }

    double frameEnd () {
        double now = SDL_GetTicks() / 1000.;
        return 1. / rate - (now - eT);
    }
};
