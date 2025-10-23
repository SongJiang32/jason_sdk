#pragma once
#include "unitree/legControl/legControl.h"

class QuadrupedLeg {
public:
    LegController hip;
    LegController thigh;
    LegController calf;

    QuadrupedLeg(SerialPort& ser, MotorType hipType, int hipId,
                 MotorType thighType, int thighId,
                 MotorType calfType, int calfId);

    void setAllVelocity(double hipVel, double thighVel, double calfVel);
    void setAllPosition(double hipPos, double thighPos, double calfPos);
    void setAllTorque(double hipTorque, double thighTorque, double calfTorque);
    void setAllDamping(double hipKd, double thighKd, double calfKd);
    void printAllMotorData();
    void lockAll();
};
