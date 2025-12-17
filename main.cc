#include <iostream>
#include <thread>
#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;
int main(){
	//cout<<"Hello from the pi. This is my first c++ program on the raspberry pi"<<endl;
	//cout<<"optimal number of threads is" <<thread::hardware_concurrency();
	int fd = open("/dev/input/event2", O_RDONLY);
	if (fd<0){
		perror("open");
		return 1;	
	}
	input_event ev;
	while (1){
		ssize_t n = read(fd, &ev, sizeof(ev));
		if (n != sizeof(ev))
			continue;
		if(ev.type == EV_KEY){
			cout<<" key code is " << ev.code << " value is " << ev.value<<endl;
		}
	}
}
