#include "mp3Player.h"
#include <iostream>

void mp3Player::playTrack(int trackNumber){
	std::cout<<"Function play track called " <<std::endl;
	this->cmd = 0x03;
	uint16_t parameters = (uint16_t)trackNumber;
	lowParameter = (parameters & 0xFF);
	highParameter = (parameters>>8) & 0xFF;	
	highParameter = 0x00;
	calculateChecksum();
	refreshData();
	}
void mp3Player::calculateChecksum(){
	checksum = 0xFFFF - (version + length + cmd + feedback + highParameter + lowParameter)+1; 
	checksumHigh = (checksum >> 8) & 0xFF;
	checksumLow = (checksum & 0xFF);
	}
void mp3Player::refreshData(){
	data[3] = cmd;
	data[5] = highParameter;
	data[6] = lowParameter;
	data[7] = checksumHigh;
	data[8] = checksumLow;

	}
