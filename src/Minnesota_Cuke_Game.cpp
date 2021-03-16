
#include "Minnesota_Cuke_Heads.h"

PlayerData GamePlayer;

Image Loading_Back;
Image Loading_Pic;
Image lNumsFont;
Image sNumsFont;
Image mapFont;
Image LevelNamePic;
Image GetReadyImg;
Image PauseImg;

NH_Music LevelMusic;
NH_Sound GetReadySnd;


void MC_WriteNum(int v,int x,int y,Video_Manager& vid){
	std::string str = std::to_string(v);
	for(int i = 0; i < str.length(); i ++){
		int dx = str[i] - '0';
		if(dx>=0||dx<=9)
			vid.NH_DrawPartImage(lNumsFont,x+(i*16),y,1,1,dx*16,0,16,30);
	}
};

void MC_WriteNum2(int v,int x,int y,Video_Manager &vid){
	std::string str = std::to_string(v);
	std::string str2;
	str2.clear();
	int ncount = 0;
	for (int i = 0; i < str.length(); i++) {
		str2 += (str[str.length() - (1 + i)]);
		if (++ncount >= 3) {
			str2 += (',');
		}
	}
	str.clear();
	str = "";
	for (int i = 0; i < str2.length(); i++) {
		str += (str2[str2.length() - (1 + i)]);
	}
	for(int i = 0; i < str.length(); i ++){
		int dx = str[i] - '0';
		if(str[i]==',') dx = 10;
		if(dx>=0||dx<=10)
			vid.NH_DrawPartImage(sNumsFont,x+(i*13),y,1,1,dx*13,0,13,24);
	}
};

void MC_WriteNum2c(int v,int x,int y,Video_Manager&vid){
	std::string str = std::to_string(v);
	std::string str2;
	str2.clear();
	int ncount = 0;
	for(int i = (int)str.length()-1; i >=0; i --){
		str2 += str[i];
		if(++ncount>=3 && i != 0){
			str2 += (',');
			ncount = 0;
		}
	}
	str.clear();
	str = "";
	for(int i = (int)str2.length(); i >= 0; i --){
		str += str2[i];
	}
	x -= ((int)str.length() * 13) / 2;
	for(int i = 0; i < str.length(); i ++){
		int dx = str[i] - '0';
		if(str[i]==',') dx = 10;
		if(dx>=0||dx<=10)
			vid.NH_DrawPartImage(sNumsFont,x+(i*13),y,1,1,dx*13,0,13,24);
	}
};


void MC_GameSetup(Video_Manager& vid) {
	lNumsFont.NH_LoadImage("graphics/menu/map/whitenum.bmp", vid);
	sNumsFont.NH_LoadImage("graphics/menu/map/whitenumsmall.bmp", vid);
	mapFont.NH_LoadImage("graphics/Menu/font/map.bmp", vid);
	GetReadyImg.NH_LoadImage("graphics/Menu/levelcomplete/get-ready.bmp", vid);
	PauseImg.NH_LoadImage("graphics/Menu/pause.bmp", vid);
	GetReadySnd.Load("sounds/menu/43_cuke_getready.wav","GetReady");
};

void MC_GameShutdown(){
	lNumsFont.NH_FreeImage();
	sNumsFont.NH_FreeImage();
	mapFont.NH_FreeImage();
	GetReadyImg.NH_FreeImage();
	PauseImg.NH_FreeImage();
	GetReadySnd.Free();
};

void MC_SetGamePlayer(PlayerData p) {
	GamePlayer = p;
};

void MC_DrawLoad(Engine_Instance* engine){
	
	#define SCREEN_WIDTH engine->video_mngr.NH_Width
	#define SCREEN_HEIGHT engine->video_mngr.NH_Height
	int OffX = (SCREEN_WIDTH - 800) / 2;
	int OffY = (SCREEN_HEIGHT - 600);// / 2;

	// Render background img
	engine->video_mngr.NH_ClearScreen(0, 0, 0); // Black bars
	// Extended background
	engine->video_mngr.NH_DrawImage(Loading_Back, (OffX - 270)- Loading_Back.width, SCREEN_HEIGHT - Loading_Back.height, 1.0, 1.0);
	engine->video_mngr.NH_DrawImage(Loading_Back, OffX - 270, SCREEN_HEIGHT - Loading_Back.height, 1.0, 1.0);
	// Loading pic
	engine->video_mngr.NH_DrawImage(Loading_Pic, OffX, SCREEN_HEIGHT - Loading_Pic.height, 1.0, 1.0);	
	engine->video_mngr.NH_DrawImage(LevelNamePic, OffX + 252, OffY + 200, 1.0, 1.0);
	MC_WriteNum(GamePlayer.lives+1,OffX+420,OffY+315,engine->video_mngr);
	engine->video_mngr.NH_UpdateScreen();
};

const char* musicnames[5] = {
	"Jungle",
	"Village",
	"River",
	"Cave",
	"Ruins",
};

bool Getreadyplay = false;

void MC_LoadLevel(int levelId,Engine_Instance* engine){
	char lvlChar = 'a' + levelId%3;
	int lvlNum = (levelId / 3) + 1;
	// Load level specifitc stuff
	LevelNamePic.NH_LoadImage("graphics/level"+std::to_string(lvlNum) + lvlChar + std::string("load.bmp"),engine->video_mngr);
	Loading_Back.NH_LoadImage("graphics/background/levelstart.bmp", engine->video_mngr);
	Loading_Pic.NH_LoadImage("graphics/loading.bmp", engine->video_mngr);

	// Reset the player stuff
	
	GamePlayer.tool = { Powerups::None,0 };
	GamePlayer.hearts = 6; // 6 = 3 whole hearts
	GamePlayer.coins = 0;
	GamePlayer.flashtick = 0;
	for(int i = 0; i < 4; i++)
		GamePlayer.CUKE[i] = false;

	MC_DrawLoad(engine);

	// Actual loading stuff
	MC_LoadMap(levelId,engine->video_mngr);
	LevelMusic.Load(std::string("sounds/") + musicnames[(levelId/3)] + std::string(".mp3"), "Background-Music");

	Getreadyplay = true;

	// Load the level
	int coutdown = 0x80;
	while(coutdown--){
		MC_DrawLoad(engine);
		if (!engine->MAIN_ThreadRunning)
			break;
	}

	// Position stuff
	GamePlayer.checkpoint = GamePlayer.curPos;
	GamePlayer.lastPos = GamePlayer.curPos;
	
	LevelNamePic.NH_FreeImage();
	Loading_Back.NH_FreeImage();
	Loading_Pic.NH_FreeImage();

};

bool inGameLoop = false;
extern Position Camera;

void MC_GameLoop(Engine_Instance* engine) {
	bool canMove = true;
	if (Getreadyplay) {
		engine->audio_mngr.Play(GetReadySnd);
		Getreadyplay = false;
	}
	if (GetReadySnd.Playing()) {
		canMove = false;
	}
	if(canMove){
		if(!LevelMusic.Playing())
			engine->audio_mngr.Play(LevelMusic, true);
		if (engine->input_mngr.NH_GetKeyR(kb_Escape)) {
			MC_ChangeMenu(MenuState::WorldMap);
		}
		// Update objects
		if (engine->input_mngr.NH_GetKey(kb_RightKey)) {
			Camera.x += 4;
		}
		if (engine->input_mngr.NH_GetKey(kb_LeftKey)) {
			Camera.x -= 4;
		}
		if (engine->input_mngr.NH_GetKey(kb_UpKey)) {
			Camera.y -= 4;
		}
		if (engine->input_mngr.NH_GetKey(kb_DownKey)) {
			Camera.y += 4;
		}
		if (Camera.x < 0)
			Camera.x = 0;
		if (Camera.y > 0)
			Camera.y = 0;

		// Update map?
		MC_UpdateAnimations();
	}

	MC_DrawBackground(engine->video_mngr);
	MC_DrawMap(engine->video_mngr);
	MC_DrawForeground(engine->video_mngr);
	
	if (!canMove) {
		engine->video_mngr.NH_DrawImageCenteredReal(GetReadyImg, 0.5f, 0.4f, 1, 1);
	}

	engine->video_mngr.NH_UpdateScreen();

};

