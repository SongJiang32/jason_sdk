#pragma once
#include "unitree/serialPort/SerialPort.h"
#include "unitree/unitreeMotor/unitreeMotor.h"
#include <iostream>
#include <unistd.h>

using namespace std;

class LegController {
private:
    SerialPort& serial;
    MotorType motorType;
    int motorId;
    double gearRatio;
    
public:
    LegController(SerialPort& ser, MotorType type, int id);
    static constexpr double MAX_VELOCITY = 30.0;   // rad/s
    static constexpr double MAX_TORQUE = 23.7;     // Nm
    void printMotorData(const MotorData& data);
    void PositionMode(double targetPos, double kp);	    // default value of kp is 0.02
    void VelocityMode(double targetVel, double kd);	    // Default value of kd is 0.02
    void DampingMode(double kd);				        // Default value of kd is 0.02
    void TorqueMode(double targetTorque);
    void setZeroTorqueMode();
    void HybridMode(double targetTorque, double targetPos, double targetVel, double kp, double kd);
    void LockMode();
};
