#include "unitree/legControl/quadruped_leg.h"

QuadrupedLeg::QuadrupedLeg(SerialPort& ser, MotorType hipType, int hipId,
                           MotorType thighType, int thighId,
                           MotorType calfType, int calfId)
    : hip(ser, hipType, hipId),
      thigh(ser, thighType, thighId),
      calf(ser, calfType, calfId) {
      }

void QuadrupedLeg::setAllVelocity(double hipVel, double thighVel, double calfVel) {
    hip.VelocityMode(hipVel);
    thigh.VelocityMode(thighVel);
    calf.VelocityMode(calfVel);
}

void QuadrupedLeg::setAllPosition(double hipPos, double thighPos, double calfPos) {
  hip.PositionMode(hipPos);
  thigh.PositionMode(thighPos);
  calf.PositionMode(calfPos);
}

void QuadrupedLeg::setAllTorque(double hipTorque, double thighTorque, double calfTorque) {
  hip.TorqueMode(hipTorque);
  thigh.TorqueMode(thighTorque);
  calf.TorqueMode(calfTorque);
}

void QuadrupedLeg::setAllDamping(double hipKd, double thighKd, double calfKd) {
  hip.DampingMode(hipKd);
  thigh.DampingMode(thighKd);
  calf.DampingMode(calfKd);
}

void QuadrupedLeg::printAllMotorData() {
  // 可根据 LegController::printMotorData 实现
  // 这里只是示例，实际可传入最新的 MotorData
  // hip.printMotorData(...);
  // thigh.printMotorData(...);
  // calf.printMotorData(...);
}

void QuadrupedLeg::lockAll() {
  hip.LockMode();
  thigh.LockMode();
  calf.LockMode();
}
