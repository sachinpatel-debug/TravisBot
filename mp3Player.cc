#include "mp3Player.h"

void mp3Player::playTrack(int trackNumber){
	
	cmd = 0x03;
	//uint16_t parameters = (uint16_t)trackNumber;
	lowParameter = 0x01;
	//highParameter = (parameters>>8) & 0xFF;	
	highParameter = 0x00;
	}
