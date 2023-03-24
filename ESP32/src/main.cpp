#define DEBUG_SERIAL 0
#define DEBUG_QUAT 0


#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>

#define NUM_SENSOR 4

#define SDA1_PIN 23 
#define SCL1_PIN 22
#define SDA2_PIN 4
#define SCL2_PIN 0
#define I2C_FREQ 400000U

#define INTPIN0 36
#define INTPIN1 35
#define INTPIN2 34
#define INTPIN3 39
#define UDP_PORT 6666

#include "IMU.hpp"
#include "secrets.h" //wifi SSID & PASSWORD

const char* ssid = SSID;
const char* password = PASSWORD;


WiFiUDP UDP;

IMU sensors[NUM_SENSOR] = {
    IMU(0x68, 0, &Wire),
    IMU(0x69, 1, &Wire),
    IMU(0x68, 2, &Wire1),
    IMU(0x69, 3, &Wire1),
};

#define MPU(index) sensors[index].MPU

// Interrupt Service Routine Functions
ISRF(sensors[0], 0)
ISRF(sensors[1], 1)
ISRF(sensors[2], 2)
ISRF(sensors[3], 3)

void sendPacket(struct PACKET packet);
void sendPacketAll(struct PACKET *packet);

void setup() {

    Wire.begin(SDA1_PIN, SCL1_PIN, I2C_FREQ);
    Wire1.begin(SDA2_PIN, SCL2_PIN, I2C_FREQ);
    WiFi.begin(ssid, password);

    #if DEBUG_SERIAL
    Serial.begin(115200);

    Serial.println(F("Testing device connections..."));
    Serial.println(MPU(0).testConnection() ? F("MPU6050_0 connection successful") : F("MPU6050_0 connection failed"));
    Serial.println(MPU(1).testConnection() ? F("MPU6050_1 connection successful") : F("MPU6050_1 connection failed"));
    Serial.println(MPU(2).testConnection() ? F("MPU6050_2 connection successful") : F("MPU6050_2 connection failed"));
    Serial.println(MPU(3).testConnection() ? F("MPU6050_3 connection successful") : F("MPU6050_3 connection failed"));

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    #endif

    UDP.begin(UDP_PORT);

    DMP_INIT(sensors[0], 0, INTPIN0)
    DMP_INIT(sensors[1], 1, INTPIN1)
    DMP_INIT(sensors[2], 2, INTPIN2)
    DMP_INIT(sensors[3], 3, INTPIN3)
}

char receive;
struct PACKET allPack[NUM_SENSOR];

void loop() {

    while(!UDP.parsePacket());
    UDP.read(&receive, 1024);

    switch (receive){
        case '0':
            sendPacket(sensors[0].readQuat());
            break;
        case '1':
            sendPacket(sensors[1].readQuat());
            break;
        case '2':
            sendPacket(sensors[2].readQuat());
            break;
        case '3':
            sendPacket(sensors[3].readQuat());
            break;
        case 'a': //all sensors
            
            for (short i = 0; i < NUM_SENSOR; i++)
                allPack[i] = sensors[i].readQuat();
            sendPacketAll(allPack);
                
            break;
        default:
            break;
    }
    
}

void sendPacketAll(struct PACKET *packet){
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.write((uint8_t*)packet, sizeof(struct PACKET) * NUM_SENSOR);
    UDP.endPacket();
}

void sendPacket(struct PACKET packet){
    UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
    UDP.write((uint8_t*)&packet, sizeof(struct PACKET));
    UDP.endPacket();
}

