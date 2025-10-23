#include "unitree/legControl/legControl.h"


int main() {

        // 初始化两个串口
        SerialPort serial1("/dev/ttyUSB0");
        SerialPort serial2("/dev/ttyUSB1");
        
        
        // 创建两个腿部控制器，分别连接到不同的串口和电机
        LegController RL_calf(serial1, MotorType::GO_M8010_6, 0);  // 右腿，串口1，电机ID 0
        LegController RR_calf(serial2, MotorType::GO_M8010_6, 1);  // 左腿，串口2，电机ID 1

        while(true) {
            // 控制右腿电机
            cout << "=== [RL_calf] ===" << endl;
            RL_calf.VelocityMode(3.14, 0.02);  // 可以设置不同的速度
            usleep(200);

            // 控制左腿电机
            cout << "=== [RR_calf] ===" << endl;
            RR_calf.VelocityMode(-3.14, 0.02);  // 可以设置不同的速度
            
            usleep(200);  // 200ms延时
        }

    return 0;
}