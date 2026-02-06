#include <iostream>
#include <pigpio.h>
using namespace std;

int main() {
	const int servoPin = 13;
	const int motorPin = 12;
	//gpioInitialise();
	cout<<"Using pigpio version" <<gpioVersion()<<endl;
	gpioInitialise();
	while(true){
	gpioHardwarePWM(servoPin, 50, 300000);
	}
	gpioTerminate();









}
