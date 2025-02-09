#pragma once

class Time {
public:
    static Time& get() {
        static Time instance;
        return instance;
    }

    double rate = 60; //
    double desiredFrameTime = 1. / rate;
    double eT = 0;
    double dT = 0;
    double fps = 0;
    double meanDelta = 0;
    double meanDeltaBf[30];
    double frameDelay = 0;
    double frameComputing = 0;
    double frameDur = 0;

    void setRate (const double& rate) {
        this->rate = rate;
        this->desiredFrameTime = 1. / rate;
    }

    unsigned int frame = 0;

    double startFrame ();
    double endFrame ();

    long long getSystemTime ();

    void updateMeanDelta (const double& dT);
    double beforeDelay ();
};
