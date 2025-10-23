#include "unitree/legControl/legControl.h"

using namespace std;

double clamp(double value, double min, double max) {
    return std::max(min, std::min(value, max));
}

LegController::LegController(SerialPort& ser, MotorType type, int id)
    : serial(ser), motorType(type), motorId(id) {
    gearRatio = queryGearRatio(motorType);
}

void LegController::printMotorData(const MotorData& data) {
    cout << endl;
    cout << "motor.q: " << data.q << endl;
    cout << "motor.temp: " << data.temp << endl;
    cout << "motor.W: " << data.dq << endl;
    cout << "motor.merror: " << data.merror << endl;
    cout << endl;
}

void LegController::PositionMode(double targetPos, double kp) {
    MotorCmd cmd;
    MotorData data;
    // 可根据实际需求限制位置范围，这里暂不限制
    cmd.motorType = motorType;
    data.motorType = motorType;
    cmd.mode = queryMotorMode(motorType, MotorMode::FOC);
    cmd.id = motorId;
    cmd.kp = kp;
    cmd.kd = 0.0;
    cmd.q = targetPos * gearRatio;
    cmd.dq = 0.0;
    cmd.tau = 0.0;
    serial.sendRecv(&cmd, &data);
    printMotorData(data);
}

void LegController::VelocityMode(double targetVel, double kd) {
    MotorCmd cmd;
    MotorData data;
    double limitedVel = clamp(targetVel, -LegController::MAX_VELOCITY, LegController::MAX_VELOCITY);
    cmd.motorType = motorType;
    data.motorType = motorType;
    cmd.mode = queryMotorMode(motorType, MotorMode::FOC);
    cmd.id = motorId;
    cmd.kp = 0.0;
    cmd.kd = kd;
    cmd.q = 0.0;
    cmd.dq = limitedVel * gearRatio;
    cmd.tau = 0.0;
    serial.sendRecv(&cmd, &data);
    printMotorData(data);
}

void LegController::DampingMode(double kd) {
    MotorCmd cmd;
    MotorData data;
    cmd.motorType = motorType;
    data.motorType = motorType;
    cmd.mode = queryMotorMode(motorType, MotorMode::FOC);
    cmd.id = motorId;
    cmd.kp = 0.0;
    cmd.kd = kd;
    cmd.q = 0.0;
    cmd.dq = 0.0;
    cmd.tau = 0.0;
    serial.sendRecv(&cmd, &data);
    printMotorData(data);
}

void LegController::TorqueMode(double targetTorque) {
    MotorCmd cmd;
    MotorData data;
    double limitedTorque = clamp(targetTorque, -LegController::MAX_TORQUE, LegController::MAX_TORQUE);  // 符号为方向
    cmd.motorType = motorType;
    data.motorType = motorType;
    cmd.mode = queryMotorMode(motorType, MotorMode::FOC);
    cmd.id = motorId;
    cmd.kp = 0.0;
    cmd.kd = 0.0;
    cmd.q = 0.0;
    cmd.dq = 0.0;
    cmd.tau = limitedTorque;
    serial.sendRecv(&cmd, &data);
    printMotorData(data);
}

void LegController::setZeroTorqueMode() {
    TorqueMode(0.0);
}

void LegController::HybridMode(double targetTorque, double targetPos, double targetVel, double kp, double kd) {
    MotorCmd cmd;
    MotorData data;
    double limitedVel = clamp(targetVel, -LegController::MAX_VELOCITY, LegController::MAX_VELOCITY);
    double limitedTorque = clamp(targetTorque, -LegController::MAX_TORQUE, LegController::MAX_TORQUE);
    // 可根据实际需求限制位置范围，这里暂不限制
    cmd.motorType = motorType;
    data.motorType = motorType;
    cmd.mode = queryMotorMode(motorType, MotorMode::FOC);
    cmd.id = motorId;
    cmd.kp = kp;
    cmd.kd = kd;
    cmd.q = targetPos * gearRatio;
    cmd.dq = limitedVel * gearRatio;
    cmd.tau = limitedTorque;
    serial.sendRecv(&cmd, &data);
    printMotorData(data);
}

void LegController::LockMode() {
    MotorCmd cmd;
    MotorData data;
    cmd.motorType = motorType;
    data.motorType = motorType;
    cmd.mode = queryMotorMode(motorType, MotorMode::BRAKE);
    cmd.id = motorId;
    serial.sendRecv(&cmd, &data);
    printMotorData(data);
}