#ifndef IMU_H_
#define IMU_H_
#include "MPU6050_6Axis_MotionApps612.h"
#define CALIBRATE_QUALITY 1

uint8_t fifoBuffer[42];
Quaternion q;

struct PACKET
{
    int sensorIndex;
    float w;
    float x;
    float y;
    float z;
};



class IMU{
    uint8_t devStatus;
    public:
        bool dmpReady = false;
        uint16_t packetSize;
        volatile bool mpuInterrupt = false;
        uint8_t mpuIntStatus;
        MPU6050 MPU;
        int index;

        IMU(uint8_t addr, int index, void *wireObj){
            MPU = MPU6050(addr, wireObj);
            this->index = index;
        }
        uint8_t dmpInit(){
            devStatus = MPU.dmpInitialize();
            return devStatus;
        }
        struct PACKET readQuat(){
            struct PACKET packet;
            if(MPU.dmpGetCurrentFIFOPacket(fifoBuffer)) {
                MPU.dmpGetQuaternion(&q, fifoBuffer);
                packet.sensorIndex = index;
                packet.w = q.w;
                packet.x = q.x;
                packet.y = q.y;
                packet.z = q.z;

                #if DEBUG_QUAT
                Serial.print(index);
                Serial.print("\t");
                Serial.print(q.w);
                Serial.print("\t");
                Serial.print(q.x);
                Serial.print("\t");
                Serial.print(q.y);
                Serial.print("\t");
                Serial.println(q.z);
                Serial.println("-------------------------------------"); 
                #endif
            }
            else{
                packet.sensorIndex = -1;
            }
            return packet;
        }
};

#define ID(name, id) name##id

#define ISRF(IMU, index)\
    void ICACHE_RAM_ATTR ID(dmpDataReady, index)() {\
        IMU.mpuInterrupt = true;\
    }\
    
#define DMP_INIT(IMU, index, intpin)\
    if (IMU.dmpInit() == 0) {\
        IMU.MPU.CalibrateAccel(CALIBRATE_QUALITY);\
        IMU.MPU.CalibrateGyro(CALIBRATE_QUALITY);\
        IMU.MPU.setDMPEnabled(true);\
        pinMode(intpin, INPUT);\
        attachInterrupt(digitalPinToInterrupt(intpin), ID(dmpDataReady,index), RISING);\
        IMU.mpuIntStatus = IMU.MPU.getIntStatus();\
        IMU.dmpReady = true;\
        IMU.packetSize = IMU.MPU.dmpGetFIFOPacketSize();\
    }\

#endif