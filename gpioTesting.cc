#include <iostream>
#include <pigpio.h>
#include <unistd.h>
#include <string>
#include "mp3Player.h"
using namespace std;

int main() {
	const int servoPin = 13;
	const int motorPin = 12;
	//gpioInitialise();
	cout<<"Using pigpio version" <<gpioVersion()<<endl;

	gpioInitialise();
	const char* device = "/dev/serial0";
	int serial = serOpen((char*)device,9600,0);
	mp3Player mp3;
	cout<<"here is a test cmd is 1 here it is " << (int)mp3.cmd <<endl;
	int trackToPlay = 3;
	mp3.playTrack(trackToPlay);
	cout<<"now it should be 3 here is is " <<(int)mp3.cmd <<endl;
	for(int i=0;i<10;i++){
		cout<<"Data: "<<(int)mp3.data[i]<<endl;
		}
	int dataLen = 10;
	//serWrite(serial,reinterpret_cast<char*>(mp3.data), dataLen);
	mp3.playTrack(4);
	serWrite(serial,reinterpret_cast<char*>(mp3.data), dataLen);

	serClose(serial);
	while(true){
	gpioHardwarePWM(servoPin, 50, 300000);
	}
	gpioTerminate();









}
