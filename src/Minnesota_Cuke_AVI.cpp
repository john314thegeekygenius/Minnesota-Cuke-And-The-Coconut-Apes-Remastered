
#include "Minnesota_Cuke_Heads.h"

struct color {
	int r, g, b;
};

std::vector<color> frame;

void MC_PlayAVI(std::string name) {
	std::ifstream avifile;
	avifile.open(name);
	if (avifile.is_open()) {
		// Get Audio data
		// Get Image 
		avifile.close();
	}

};