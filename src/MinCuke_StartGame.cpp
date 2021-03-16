
#include "Minnesota_Cuke_Heads.h"

extern MenuState CurrentMenu;
extern MenuState LastMenu;
extern bool RunOnRun;
extern bool MenuDiff;
extern bool NewPlayerActive;

extern bool RemoveM;
extern int RemovePlayerb;

extern Image mapFont;

//////////////////////////////////////////////////////////////////////////////////
//
//     Start Game Menu Callback
//

void menu_StartGame::MC_OnCall() {
	levelOn = 0;
	LoadLvlName = true;
};

void menu_StartGame::MC_Reset() {
};

void menu_StartGame::MC_Load(Video_Manager& vid) {
	Popup.NH_LoadImage("graphics/menu/map/level/pop-default.bmp", vid);
	lButton_Hover.NH_LoadImage("graphics/menu/map/level/leftb-over.bmp", vid);
	lButton_Click.NH_LoadImage("graphics/menu/map/level/leftb-down.bmp", vid);
	rButton_Hover.NH_LoadImage("graphics/menu/map/level/rightb-over.bmp", vid);
	rButton_Click.NH_LoadImage("graphics/menu/map/level/rightb-down.bmp", vid);
	letCUKE[0].NH_LoadImage("graphics/PowerUps/cuke-C.bmp", vid);
	letCUKE[1].NH_LoadImage("graphics/PowerUps/cuke-U.bmp", vid);
	letCUKE[2].NH_LoadImage("graphics/PowerUps/cuke-K.bmp", vid);
	letCUKE[3].NH_LoadImage("graphics/PowerUps/cuke-E.bmp", vid);
};

void menu_StartGame::MC_Unload() {
	Popup.NH_FreeImage();
	lButton_Hover.NH_FreeImage();
	lButton_Click.NH_FreeImage();
	rButton_Hover.NH_FreeImage();
	rButton_Click.NH_FreeImage();
	for (int i = 0; i < 4; i++)
		letCUKE[i].NH_FreeImage();
	levelName.NH_FreeImage();
};

void menu_StartGame::MC_Callback(Engine_Instance* engine) {
	int MouseX = engine->input_mngr.NH_GetMouseX();
	int MouseY = engine->input_mngr.NH_GetMouseY();

#define SCREEN_WIDTH engine->video_mngr.NH_Width
#define SCREEN_HEIGHT engine->video_mngr.NH_Height
	int OffX = (SCREEN_WIDTH - 800) / 2;
	int OffY = (SCREEN_HEIGHT - 600) / 2;
	// "Fix" the mouse coords
	MouseX -= OffX;
	MouseY -= OffY;

	extern PlayerData GamePlayer;
	extern const char* LvlNames[];

	int rlevel = GamePlayer.levelOn / 3;
	int unlocked = GamePlayer.levelUnlocked;

	if (LoadLvlName) {
		levelName.NH_LoadImage("graphics/Menu/map/stats/" + std::string(LvlNames[(rlevel*3) + levelOn]) + ".bmp", engine->video_mngr);
		LoadLvlName = false;
	}

	engine->video_mngr.NH_DrawImageCenteredReal(Popup, 0.5, 0.5, 1.0, 1.0);
	// Level Name
	engine->video_mngr.NH_DrawImage(levelName, OffX+ 330, OffY+ 187 + 8, 1, 1);

	// Times
	MC_Write(to_string2(GamePlayer.leveldata[(rlevel * 3) + levelOn].t_played.hour, 2),
		OffX + 356, OffY + 248, mapFont,engine->video_mngr);
	MC_Write(to_string2(GamePlayer.leveldata[(rlevel * 3) + levelOn].t_played.minute, 2),
		OffX + 388, OffY + 248, mapFont, engine->video_mngr);
	MC_Write(to_string2(GamePlayer.leveldata[(rlevel * 3) + levelOn].t_played.second, 2),
		OffX + 420, OffY + 248, mapFont, engine->video_mngr);
	// Best
	MC_Write(to_string2(GamePlayer.leveldata[(rlevel * 3) + levelOn].t_best.hour, 2),
		OffX + 356, OffY + 285, mapFont, engine->video_mngr);
	MC_Write(to_string2(GamePlayer.leveldata[(rlevel * 3) + levelOn].t_best.minute, 2),
		OffX + 388, OffY + 285, mapFont, engine->video_mngr);
	MC_Write(to_string2(GamePlayer.leveldata[(rlevel * 3) + levelOn].t_best.second, 2),
		OffX + 420, OffY + 285, mapFont, engine->video_mngr);
	// Coins
	MC_WriteNum(GamePlayer.leveldata[(rlevel * 3) + levelOn].coins, OffX+ 410,OffY+ 368, engine->video_mngr);
	// C U K E tiles
	for (int i = 0; i < 4; i++)
		if(GamePlayer.leveldata[(rlevel * 3) + levelOn].CUKE[i])
			engine->video_mngr.NH_DrawImage(letCUKE[i], OffX+336 + (i * 33),OffY+313, 1.0, 1.0);

	// Buttons
	int MButton = engine->input_mngr.NH_GetMouseReleased();
	if (MouseX >= 317 && MouseY >= 258 &&
		MouseX < 355 && MouseY < 298) {
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			engine->video_mngr.NH_DrawImage(lButton_Click, OffX + 317, OffY + 258, 1.0, 1.0);
		}
		else if (MButton == 0) {
			// Go back a level
			levelOn -= 1;
			if (levelOn < 0) {
				levelOn = 0;
			}
			else {
				LoadLvlName = true;
			}
		}
		else {
			engine->video_mngr.NH_DrawImage(lButton_Hover, OffX + 317, OffY + 258, 1.0, 1.0);
		}
	}
	if (MouseX >= 445 && MouseY >= 258 &&
		MouseX < 483 && MouseY < 298) {
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			engine->video_mngr.NH_DrawImage(rButton_Click, OffX + 445, OffY + 258, 1.0, 1.0);
		}
		else if (MButton == 0) {
			// Go up a level
			levelOn += 1;
			if ((rlevel * 3) + levelOn > unlocked){// || levelOn > 2) {
				levelOn -= 1;
			}
			else {
				LoadLvlName = true;
			}
		}
		else {
			engine->video_mngr.NH_DrawImage(rButton_Hover, OffX + 445, OffY + 258, 1.0, 1.0);
		}
	}
	engine->video_mngr.NH_UpdateScreen();

	if (!(MouseX >= 310 && MouseY >= 187 &&
		MouseX < 490 && MouseY < 413)) {
		if (MButton == 0) {
			MC_ChangeMenu(MenuState::WorldMap);
		}
	}


	if (engine->input_mngr.NH_GetKeyR(kb_Escape)) {
		MC_ChangeMenu(MenuState::WorldMap);
	}
	if (engine->input_mngr.NH_KeyReleased()) {
		MC_LoadLevel((rlevel * 3) + levelOn, engine);
		MC_ChangeMenu(MenuState::PlayGame);
	}
};

