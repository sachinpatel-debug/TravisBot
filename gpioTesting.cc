#include <iostream>
#include <pigpio.h>
using namespace std;

int main() {
	const int servoPin = 13;
	const int motorPin = 12;
	//gpioInitialise();
	cout<<"Using pigpio version" <<gpioVersion()<<endl;
	gpioInitialise();
	const char* device = "/dev/serial0";
	int serial = serOpen((char*)device,9600,0);
	uint8_t version = 0xFF; //will always be this
	uint8_t length = 0x06; //will always be this
	uint8_t cmd = 0x03; //play track
	uint8_t feedback = 0x00; //0 means no feedback
	uint8_t highParameter = 0x00;  
	uint8_t lowParameter = 0x02;

	uint16_t checksum = 0xFFFF - (version + length + cmd + feedback + highParameter + lowParameter)+1; 
	uint8_t checksumHigh = (checksum >> 8) & 0xFF;
	uint8_t checksumLow = (checksum & 0xFF);
	uint8_t data[] = {0x7E, version, length, cmd, feedback, highParameter, lowParameter, checksumHigh, checksumLow, 0xEF };
	int dataLen = sizeof(data);
	serWrite(serial, (char*)data, dataLen);
	serClose(serial);
	while(true){
	gpioHardwarePWM(servoPin, 50, 300000);
	}
	gpioTerminate();









}
