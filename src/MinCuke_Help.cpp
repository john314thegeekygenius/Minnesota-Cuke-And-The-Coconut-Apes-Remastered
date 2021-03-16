
#include "Minnesota_Cuke_Heads.h"

extern MenuState CurrentMenu;
extern MenuState LastMenu;
extern bool RunOnRun;
extern bool MenuDiff;
extern bool NewPlayerActive;

extern bool RemoveM;
extern int RemovePlayerb;


//////////////////////////////////////////////////////////////////////////////////
//
//     Help Menu Callback
//

void menu_HelpMenu::MC_OnCall() {
	PlayedSnd = false;
};

void menu_HelpMenu::MC_Reset() {
};

void menu_HelpMenu::MC_Load(Video_Manager& vid) {
	vid.NH_SetImageClearColor(255, 0, 255);
	Backpic.NH_LoadImage("graphics/Menu/map/instructions-back.bmp", vid);
	HelpPic.NH_LoadImage("graphics/Menu/map/instructions-screen.bmp", vid);
	Larryspeak.Load("sounds/menu/instructions.wav", "LarryHelp");
};

void menu_HelpMenu::MC_Unload() {
	Backpic.NH_FreeImage();
	HelpPic.NH_FreeImage();
	Larryspeak.Free();
};

void menu_HelpMenu::MC_Callback(Engine_Instance* engine) {

	if (!PlayedSnd) {
		engine->audio_mngr.Play(Larryspeak);
		PlayedSnd = true;
	}

	#define SCREEN_WIDTH engine->video_mngr.NH_Width
	#define SCREEN_HEIGHT engine->video_mngr.NH_Height
	int OffX = (SCREEN_WIDTH - 800) / 2;
	int OffY = (SCREEN_HEIGHT - 600);// / 2;

	// Render background img
	engine->video_mngr.NH_ClearScreen(0, 0, 0); // Black bars
	engine->video_mngr.NH_DrawImage(Backpic, OffX - 396, (SCREEN_HEIGHT - Backpic.height) + 29, 1.0, 1.0);
	engine->video_mngr.NH_DrawImage(HelpPic, OffX, SCREEN_HEIGHT - HelpPic.height, 1.0, 1.0);
	engine->video_mngr.NH_UpdateScreen();

	if (engine->input_mngr.NH_GetMouseReleased() == 0) {
		// Should check for game play...
		MC_ChangeMenuBack();
	}

	if (engine->input_mngr.NH_KeyReleased()) {
		// Should check for game play...
		MC_ChangeMenuBack();
	}
	
};


