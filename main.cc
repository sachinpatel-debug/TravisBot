#include <iostream>
#include <thread>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <pigpio.h>
using namespace std;
int fd = open("/dev/input/event2", O_RDONLY);
int main(){
	//cout<<"Hello from the pi. This is my first c++ program on the raspberry pi"<<endl;
	//cout<<"optimal number of threads is" <<thread::hardware_concurrency();
	const int servoPin = 13;
	const int motorPin = 12;
	int xValue = 0;
	int yValue = 0;
	int angle = 0;
	int radius = 0;
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
        			cout<<"this is 0, left JS x movement"<<endl;
			}
    			else if (ev.code == 1){
        			cout<<"This is 1, a left JS y movement"<<endl;
			}
			else if(ev.code == 2){
            			//setDirection(0)
            			//setSpeed(event.value)
			}
			else if (ev.code == 5){
            			cout<<"This is 5, a right trigger event"<<endl;
            			//setDirection(1)
            			//setSpeed(event.value)
				}

        		else if(ev.code == 3){
            			cout<<"This is 3, right JS x event"<<endl;
            			if(yValue<=0){
                			xValue = ev.value;
                			radius = (xValue*xValue + yValue*yValue); //fix this to square root it later
                			if(radius >= 5000){
                    				//angle = atan2(yValue, xValue); //compute angle later
                    				//angle = degrees(angle);
                    				//angle = angle * -1
                    				//onesPlace = angle % 10
                    				//angle = angle - onesPlace
                    				//print(f"Angle is {angle}")
                    				//if(30 <= angle <= 150){
                        			//	setAngle(angle)
		    				//	}
						}
					}	
				}
			else if(ev.code == 4){
				cout<<"This is 4, a right JS y event"<<endl;
				yValue = ev.value;
				}

	}

	}

	gpioTerminate();
}
