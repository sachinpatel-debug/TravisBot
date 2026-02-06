#include <iostream>
#include <thread>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <pigpio.h>
#include <math.h>
#include <iomanip>
using namespace std;
int fd = open("/dev/input/event2", O_RDONLY);
const int directionPin1= 27;
const int directionPin2 = 22;
void setDirection(int direction){
	if(direction==1){
		gpioWrite(directionPin1, 0);
		gpioWrite(directionPin2, 1);		
		}
	else if(direction==0){
		gpioWrite(directionPin1, 1);
		gpioWrite(directionPin2, 0);
		}
}
int main(){
	//cout<<"Hello from the pi. This is my first c++ program on the raspberry pi"<<endl;
	//cout<<"optimal number of threads is" <<thread::hardware_concurrency();
	const int servoPin = 13;
	const int motorPin = 12;
	    gpioSetMode(directionPin1, PI_OUTPUT);
	    gpioSetMode(directionPin2, PI_OUTPUT);
	int xValue = 0;
	int yValue = 0;
	double angle = 0;
	double radius = 0;
	//cout<<"Using pigpio version" <<gpioVersion()<<endl;
	gpioInitialise();
	//gpioHardwarePWM(servoPin, 50, 300000);
	

	if (fd<0){
		perror("open");
		return 1;	
	}
	//if(gpioInitialise() < 0){
		//cerr << "pigpio did not initialize correctly"<<endl;
		//return 1;
		//}
	
	input_event ev;
	while (1){
		ssize_t n = read(fd, &ev, sizeof(ev));
		if (n != sizeof(ev))
			continue;
		if(ev.type == EV_KEY){
			cout<<" key code is " << ev.code << " value is " << ev.value<<endl;
		}
		else if(ev.type == EV_ABS){
        //Handle absolute axis events (e.g., joystick or touchscreen)
        //print(f"Absolute event: code={event.code}, value={event.value}")
    			if (ev.code== 0){
        			//cout<<"this is 0, left JS x movement"<<endl;
			}
    			else if (ev.code == 1){
        			//cout<<"This is 1, a left JS y movement"<<endl;
			}
			else if(ev.code == 2){
            			setDirection(0);
            			gpioHardwarePWM(motorPin, 800, ev.value*1000000/1024);
			}
			else if (ev.code == 5){
            			cout<<"This is 5, a right trigger event"<<endl;
            			setDirection(1);
				gpioHardwarePWM(motorPin, 800, ev.value*1000000/1024);
				}

        		else if(ev.code == 3){
            			//cout<<"This is 3, right JS x event"<<endl;
            			if(yValue<=0){
                			xValue = ev.value;
                			radius = sqrt(xValue*xValue + yValue*yValue); //fix this to square root it later
                			//cout<<fixed << setprecision(5) << "radius is" << radius<<endl;
					if(radius >= 5000){
                    				angle = atan2(yValue, xValue); //compute angle later
                    				angle = angle*180/3.14159;
                    				angle = angle * -1;
                    				//onesPlace = angle % 10
                    				//angle = angle - onesPlace
                    				cout<<"Angle is " << angle<<endl;
                    				if(30 <= angle <= 150){
                        				double duty = (angle/18) + 2;
							duty = duty*10000;
							gpioHardwarePWM(servoPin, 50, duty); //duty cycle is out of a million, servo duty cycles should be 5-10% this equates to 0-2 ms out of a 20 ms period (@50 Hz)
		    					}
						}
					}	
				}
			else if(ev.code == 4){
				//cout<<"This is 4, a right JS y event"<<endl;
				yValue = ev.value;
				}

	}

	}

	gpioTerminate();
}
