
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
//     Quit Menu Callback
//

void menu_QuitMenu::MC_OnCall() {
};

void menu_QuitMenu::MC_Reset() {
	if (MenuDiff == true) {
		ButtonSelected = -1;
		MenuDiff = false;
	}
};

void menu_QuitMenu::MC_Load(Video_Manager& vid) {
	vid.NH_SetImageClearColor(255, 0, 255);
	Quit_Popup.NH_LoadImage("graphics/menu/main/pop-stop.bmp", vid);
	Quit_Yes.NH_LoadImage("graphics/menu/main/stop-yes-click.bmp", vid);
	Quit_No.NH_LoadImage("graphics/menu/main/stop-no-click.bmp", vid);

	cuke_Yes.Load("sounds/menu/57_cuke_yes_stopgame.wav", "57_cuke_yes_stopgame");
	cuke_No.Load("sounds/menu/45_cuke_nokeep.wav", "45_cuke_nokeep");
	cuke_AreYouSure.Load("sounds/menu/42_cuke_areyousure.wav", "42_cuke_areyousure");
	cuke_Goodbye.Load("sounds/menu/58_cuke_goodbye.wav", "58_cuke_goodbye");

};

void menu_QuitMenu::MC_Unload() {
	Quit_Popup.NH_FreeImage();
	Quit_Yes.NH_FreeImage();
	Quit_No.NH_FreeImage();

	cuke_Yes.Free();
	cuke_No.Free();
	cuke_AreYouSure.Free();
	cuke_Goodbye.Free();
};

void menu_QuitMenu::MC_Callback(Engine_Instance* engine) {
	int MouseX = engine->input_mngr.NH_GetMouseX();
	int MouseY = engine->input_mngr.NH_GetMouseY();

#define SCREEN_WIDTH engine->video_mngr.NH_Width
#define SCREEN_HEIGHT engine->video_mngr.NH_Height
	int OffX = (SCREEN_WIDTH - 800) / 2;
	int OffY = (SCREEN_HEIGHT - 600) / 2;
	OffX += 266;
	OffY += 173;
	// "Fix" the mouse coords
	MouseX -= OffX;
	MouseY -= OffY;

	engine->video_mngr.NH_DrawImageCenteredReal(Quit_Popup, 0.5, 0.5, 1.0, 1.0);

	if (ButtonSelected == -1) {
		engine->audio_mngr.Play(cuke_AreYouSure);
		ButtonSelected = 0;
	}

	if (MouseX >= 13 && MouseY >= 68 &&
		MouseX < 145 && MouseY < 162) {
		if (ButtonSelected != 1) {
			ButtonSelected = 1;
			// Play SFX
			engine->audio_mngr.Stop(cuke_No);
			engine->audio_mngr.Stop(cuke_AreYouSure);
			engine->audio_mngr.Play(cuke_Yes);
		}
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			// Press
			engine->video_mngr.NH_DrawImage(Quit_Yes, 13 + OffX, 68 + OffY, 1.0, 1.0);
		}
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			// Quit Game
			engine->audio_mngr.Play(cuke_Goodbye);
			while (cuke_Goodbye.Playing()) {};
			engine->MAIN_ThreadRunning = false;
		}
	}
	if (MouseX >= 25 && MouseY >= 167 &&
		MouseX < 132 && MouseY < 243) {
		if (ButtonSelected != 2) {
			ButtonSelected = 2;
			// Play SFX
			engine->audio_mngr.Stop(cuke_Yes);
			engine->audio_mngr.Stop(cuke_AreYouSure);
			engine->audio_mngr.Play(cuke_No);
		}
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			// Press
			engine->video_mngr.NH_DrawImage(Quit_No, 25 + OffX, 167 + OffY, 1.0, 1.0);
		}
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			// Quit Menu
			MC_ChangeMenuBack();
		}
	}
	// Prevent
	if (engine->input_mngr.NH_GetMouseReleased() == 0) {}
	engine->video_mngr.NH_UpdateScreen();
};

