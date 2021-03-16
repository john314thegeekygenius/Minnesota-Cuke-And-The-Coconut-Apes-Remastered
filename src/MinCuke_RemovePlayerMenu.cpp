
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
//     Remove Player Menu Callback
//

void menu_RemoveMenu::MC_OnCall() {
};

void menu_RemoveMenu::MC_Reset() {
	if (MenuDiff == true) {
		ButtonSelected = -1;
		MenuDiff = false;
	}
};

void menu_RemoveMenu::MC_Load(Video_Manager& vid) {
	vid.NH_SetImageClearColor(255, 0, 255);
	Remove_Popup.NH_LoadImage("graphics/menu/main/pop-remove.bmp", vid);
	Remove_Yes.NH_LoadImage("graphics/menu/main/remove-yes-click.bmp", vid);
	Remove_No.NH_LoadImage("graphics/menu/main/remove-no-click.bmp", vid);

	cuke_Yes.Load("sounds/menu/56_cuke_yes_removeplayer.wav", "56_cuke_yes_removeplayer");
	cuke_No.Load("sounds/menu/46_cuke_no_removeplayer.wav", "46_cuke_no_removeplayer");
	cuke_AreYouSure.Load("sounds/menu/49_cuke_sure_removeplayer.wav", "49_cuke_sure_removeplayer");

};

void menu_RemoveMenu::MC_Unload() {
	Remove_Popup.NH_FreeImage();
	Remove_Yes.NH_FreeImage();
	Remove_No.NH_FreeImage();

	cuke_Yes.Free();
	cuke_No.Free();
	cuke_AreYouSure.Free();
};

void menu_RemoveMenu::MC_Callback(Engine_Instance* engine) {
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

	engine->video_mngr.NH_DrawImageCenteredReal(Remove_Popup, 0.5, 0.5, 1.0, 1.0);

	if (ButtonSelected == -1) {
		engine->audio_mngr.Play(cuke_AreYouSure);
		ButtonSelected = 0;
	}

	if (MouseX >= 123 && MouseY >= 68 &&
		MouseX < 254 && MouseY < 162) {
		if (ButtonSelected != 1) {
			ButtonSelected = 1;
			// Play SFX
			engine->audio_mngr.Stop(cuke_No);
			engine->audio_mngr.Stop(cuke_AreYouSure);
			engine->audio_mngr.Play(cuke_Yes);
		}
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			// Press
			engine->video_mngr.NH_DrawImage(Remove_Yes, 123 + OffX, 68 + OffY, 1.0, 1.0);
		}
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			// Quit menu
			MC_ChangeMenuBack();
		}
	}
	if (MouseX >= 135 && MouseY >= 167 &&
		MouseX < 243 && MouseY < 243) {
		if (ButtonSelected != 2) {
			ButtonSelected = 2;
			// Play SFX
			engine->audio_mngr.Stop(cuke_Yes);
			engine->audio_mngr.Stop(cuke_AreYouSure);
			engine->audio_mngr.Play(cuke_No);
		}
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			// Press
			engine->video_mngr.NH_DrawImage(Remove_No, 135 + OffX, 167 + OffY, 1.0, 1.0);
		}
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			// Quit Menu
			MC_ChangeMenuBack();
			RemovePlayerb = -1;
		}
	}
	// Prevent
	if (engine->input_mngr.NH_GetMouseReleased() == 0) {}
	engine->video_mngr.NH_UpdateScreen();
};

