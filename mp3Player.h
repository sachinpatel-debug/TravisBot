#include <cstdint>
#ifndef MP3PLAYER_H
#define MP3PLAYER_H
class mp3Player {

	public:
		void playTrack(int trackNumber);
		void raiseVolume(); //I think the brackets define funcs when they should be defined in .cc, so remove
		void lowerVolume(){}
		void playNext(){}
		void playPrevious(){}
		void pause(){}
		uint8_t data[10] = {start, version, length, cmd, feedback, highParameter, lowParameter, checksumHigh, checksumLow, end};


	private: 
		const uint8_t start = 0x7E;	
		const uint8_t version = 0xFF; //will always be this
		const uint8_t length = 0x06; //will always be this
		uint8_t cmd = 0x03; //play track
		uint8_t feedback = 0x00; //0 means no feedback
		uint8_t highParameter = 0x00;  //high parameter on left low on right, so 1 would be high=00, low=01
		uint8_t lowParameter = 0x02;
		uint16_t checksum = 0xFFFF - (version + length + cmd + feedback + highParameter + lowParameter)+1; 
		uint8_t checksumHigh = (checksum >> 8) & 0xFF;
		uint8_t checksumLow = (checksum & 0xFF);
		const uint8_t end = 0xEF;
		int arraySize = 10;

};

#endif
