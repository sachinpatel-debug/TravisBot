#include <iostream>
#include "mp3Player.h"
using namespace std;

int main(){

	cout<<"Whats Up"<<endl;
	mp3Player mp3;
	cout<<"Printing data here" <<mp3.data[1]<<endl;
	for(int i = 0; i<10;i++){
		cout<< i << "  :  "<<mp3.data[i]<<endl;
		}
	
}
