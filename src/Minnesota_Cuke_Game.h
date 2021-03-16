#pragma once

const int NumOfLevels = 5;

enum class Powerups {
	None,
	Bannanas,
	BubbleGum,
	Coconuts,
	Invince,
	Tuba,
};

struct Powerup {
	Powerups type;
	int amount;
};

struct Position{
	int x,y;
};

struct LevelData {
	bool CUKE[4] = { false };
	int coins = 0;
	NH_Clock t_played;
	NH_Clock t_best;
};

struct PlayerData {
	// In Game stuff
	Powerup tool = { Powerups::None,0 };
	int hearts = 6; // 6 = 3 whole hearts
	int coins = 0;
	Position checkpoint;
	Position curPos;
	Position lastPos;
	int flashtick = 0;
	bool CUKE[4] = {false};

	//////////////
	// Save stuff

	// Other stuff
	std::string name = "";
	int day = 0;
	int month = 0;
	int year = 0;
	int n;

	// In Game stuff
	int seconds = 0;
	long long score = 0;
	int lives = 3;
	LevelData leveldata[NumOfLevels*3];

	// World Map stuff
	int levelUnlocked = 0;
	int levelOn = 0;

	void reset() {
		levelOn = 0;
		levelUnlocked = 0;
		seconds = 0;
		score = 0;
		lives = 3;
		tool = { Powerups::None,0 };
		hearts = 6; // 6 = 3 whole hearts
		coins = 0;
		flashtick = 0;
		for(int i = 0; i < 4; i++)
			CUKE[i] = false;
		for (int i = 0; i < NumOfLevels * 3; i++) {
			leveldata[i].coins = 0;
			for (int e = 0; e < 4; e++)
				leveldata[i].CUKE[e] = false;
			leveldata[i].t_played.Clear();
			leveldata[i].t_best.Clear();
		}
		//////////////
	};
};

void MC_WriteNum(int v,int x,int y,Video_Manager& vid);
void MC_WriteNum2(int v, int x, int y, Video_Manager& vid);
void MC_WriteNum2c(int v, int x, int y, Video_Manager& vid);
void MC_GameSetup(Video_Manager& vid);
void MC_GameLoop(Engine_Instance* engine);
void MC_GameShutdown();
void MC_SetGamePlayer(PlayerData p);
void MC_LoadLevel(int levelId, Engine_Instance* engine);

