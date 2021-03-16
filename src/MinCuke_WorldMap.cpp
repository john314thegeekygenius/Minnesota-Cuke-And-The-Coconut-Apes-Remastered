
#include "Minnesota_Cuke_Heads.h"

extern MenuState CurrentMenu;
extern MenuState LastMenu;
extern bool RunOnRun;
extern bool MenuDiff;
extern bool NewPlayerActive;

extern bool RemoveM;
extern int RemovePlayerb;

extern PlayerData GamePlayer;
extern Image mapFont;

//////////////////////////////////////////////////////////////////////////////////
//
//     World Map Menu Callback
//

void menu_WorldMap::MC_OnCall(Engine_Instance * engine) {
	engine->input_mngr.NH_ClearKeys();
};

void menu_WorldMap::MC_Reset() {
};

const char* LvlNames[] = {
	"map-lev-jungle1",
	"map-lev-jungle2",
	"map-lev-jungle3",
	"map-lev-pea1",
	"map-lev-pea2",
	"map-lev-pea3",
	"map-lev-river1",
	"map-lev-river2",
	"map-lev-river3",
	"map-lev-caves1",
	"map-lev-caves2",
	"map-lev-caves3",
	"map-lev-ruins1",
	"map-lev-ruins2",
	"map-lev-all",
};

void menu_WorldMap::MC_Load(Video_Manager& vid) {
	vid.NH_SetImageClearColor(255, 0, 255);
	WorldMap.NH_LoadImage("graphics/OverWorldMap.bmp", vid);
	Sidebar.NH_LoadImage("graphics/Menu/map/bar/map-bar-fm09.bmp", vid);
	Buddy.NH_LoadImage("graphics/Menu/map/stats/map-buddy-title.bmp", vid);
	Score_Pic.NH_LoadImage("graphics/Menu/map/stats/map-score.bmp", vid);
	Lvl_Unlock.NH_LoadImage("graphics/Menu/map/stats/map-lev-unlocked.bmp", vid);
	Larry.NH_LoadImage("graphics/Menu/map/stats/CukePicture.bmp", vid);
	X_Pic.NH_LoadImage("graphics/Menu/map/stats/counter-X.bmp", vid);
	BackButton.NH_LoadImage("graphics/Menu/map/go-back-default.bmp", vid);
	HelpButton.NH_LoadImage("graphics/Menu/map/help-btn-default.bmp", vid);
	BackButton_Hover.NH_LoadImage("graphics/Menu/map/go-back-click.bmp", vid);
	HelpButton_Hover.NH_LoadImage("graphics/Menu/map/help-btn-roll.bmp", vid);
	BackButton_Click.NH_LoadImage("graphics/Menu/map/go-back-roll.bmp", vid);
	HelpButton_Click.NH_LoadImage("graphics/Menu/map/help-btn-click.bmp", vid);
	for (int i = 0; i < 15; i++)
		LevelPics[i].NH_LoadImage("graphics/Menu/map/stats/" + std::string(LvlNames[i]) + ".bmp", vid);

};

void menu_WorldMap::MC_Unload() {
	WorldMap.NH_FreeImage();
	Sidebar.NH_FreeImage();
	Buddy.NH_FreeImage();
	Score_Pic.NH_FreeImage();
	Lvl_Unlock.NH_FreeImage();
	for (int i = 0; i < 15; i++)
		LevelPics[i].NH_FreeImage();
	Larry.NH_FreeImage();
	X_Pic.NH_FreeImage();
	HelpButton.NH_FreeImage();
	BackButton.NH_FreeImage();
};

void menu_WorldMap::MC_Callback(Engine_Instance* engine) {

	if (NewPlayerActive) {
		MC_IntroAni(engine);
		NewPlayerActive = false;
	}

	engine->audio_mngr.Stop();

	int MouseX = engine->input_mngr.NH_GetMouseX();
	int MouseY = engine->input_mngr.NH_GetMouseY();

#undef SCREEN_WIDTH 
#undef SCREEN_HEIGHT
#define SCREEN_WIDTH engine->video_mngr.NH_Width
#define SCREEN_HEIGHT engine->video_mngr.NH_Height
	int OffX = (SCREEN_WIDTH - 800) / 2;
	int OffY = (SCREEN_HEIGHT - 600) / 2;
	// "Fix" the mouse coords
	MouseX -= OffX;
	MouseY -= OffY;
	if (GamePlayer.levelUnlocked > 14)
		GamePlayer.levelUnlocked = 14;
	engine->video_mngr.NH_ClearScreen(0, 0, 0);
	engine->video_mngr.NH_DrawImageCenteredReal(WorldMap, 0.5, 0.5, 1.0, 1.0);
	engine->video_mngr.NH_DrawImage(Sidebar, OffX + 800 - 229, OffY, 1.0, 1.0);
	engine->video_mngr.NH_DrawImage(Buddy, OffX + 571, OffY + 50, 1.0, 1.0);
	engine->video_mngr.NH_DrawImage(Score_Pic, OffX + 636, OffY + 167, 1.0, 1.0);
	engine->video_mngr.NH_DrawImage(Lvl_Unlock, OffX + 595, OffY + 219, 1.0, 1.0);
	engine->video_mngr.NH_DrawImage(LevelPics[GamePlayer.levelUnlocked], OffX + 590, OffY + 240, 1.0, 1.0);
	engine->video_mngr.NH_DrawImage(Larry, OffX + 610, OffY + 284, 1.0, 1.0);
	engine->video_mngr.NH_DrawImage(X_Pic, OffX + 652, OffY + 316, 1.0, 1.0);

	MC_Write(GamePlayer.name, OffX+655-(((int)GamePlayer.name.length()*13)/2), OffY+138, mapFont, engine->video_mngr);
	MC_WriteNum(GamePlayer.lives+1,OffX + 680, OffY + 310, engine->video_mngr);
	MC_WriteNum2c(static_cast<int>(GamePlayer.score), OffX + 650, OffY + 185, engine->video_mngr);
	
	// Mouse stuff
	bool drawpic = true;
	if (MouseX >= 618 && MouseY >= 406 &&
		MouseX < 700 && MouseY < 452) {
		drawpic = false;
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			engine->video_mngr.NH_DrawImage(HelpButton_Hover, OffX + 618, OffY + 406, 1.0, 1.0);
		}
		else if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			// Run Help menu
			MC_ChangeMenu(MenuState::Help);
			return;
		}
		else {
			engine->video_mngr.NH_DrawImage(HelpButton_Click, OffX + 618, OffY + 406, 1.0, 1.0);
		}
	}
	if (drawpic) {
		engine->video_mngr.NH_DrawImage(HelpButton, OffX + 618, OffY + 406, 1.0, 1.0);
	}
	drawpic = true;
	if (MouseX >= 583 && MouseY >= 462 &&
		MouseX < 737 && MouseY < 545) {
		drawpic = false;
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			engine->video_mngr.NH_DrawImage(BackButton_Hover, OffX + 583, OffY + 462, 1.0, 1.0);
		}
		else if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			// Run Help menu
			MC_ChangeMenu(MenuState::Main);
			return;

		}
		else {
			engine->video_mngr.NH_DrawImage(BackButton_Click, OffX + 583, OffY + 462, 1.0, 1.0);
		}
	}
	if (drawpic) {
		engine->video_mngr.NH_DrawImage(BackButton, OffX + 583, OffY + 462, 1.0, 1.0);
	}
	if (engine->input_mngr.NH_GetMouseReleased()) {};
	
	// Input stuff
	
	if (engine->input_mngr.NH_GetKeyR(kb_Escape)) {
		MC_ChangeMenu(MenuState::Main);
		return;
	}
	
	if (engine->input_mngr.NH_KeyReleased()) {
		MC_ChangeMenu(MenuState::StartGame);
		MC_lMenuRender(true);
	}

	engine->video_mngr.NH_UpdateScreen();

};

void menu_WorldMap::MC_Render(Video_Manager& vid) {
#undef SCREEN_WIDTH 
#undef SCREEN_HEIGHT
#define SCREEN_WIDTH vid.NH_Width
#define SCREEN_HEIGHT vid.NH_Height
	int OffX = (SCREEN_WIDTH - 800) / 2;
	int OffY = (SCREEN_HEIGHT - 600) / 2;

	vid.NH_ClearScreen(0, 0, 0);
	vid.NH_DrawImageCenteredReal(WorldMap, 0.5, 0.5, 1.0, 1.0);
	vid.NH_DrawImage(Sidebar, OffX + 800 - 229, OffY, 1.0, 1.0);
	vid.NH_DrawImage(Buddy, OffX + 571, OffY + 50, 1.0, 1.0);
	vid.NH_DrawImage(Score_Pic, OffX + 636, OffY + 167, 1.0, 1.0);
	vid.NH_DrawImage(Lvl_Unlock, OffX + 595, OffY + 219, 1.0, 1.0);
	vid.NH_DrawImage(LevelPics[GamePlayer.levelUnlocked], OffX + 590, OffY + 240, 1.0, 1.0);
	vid.NH_DrawImage(Larry, OffX + 610, OffY + 284, 1.0, 1.0);
	vid.NH_DrawImage(X_Pic, OffX + 652, OffY + 316, 1.0, 1.0);

	MC_Write(GamePlayer.name, OffX + 660 - (((int)GamePlayer.name.length() * 13) / 2), OffY + 138, mapFont, vid);
	MC_WriteNum(GamePlayer.lives + 1, OffX + 680, OffY + 310, vid);
	MC_WriteNum2c(static_cast<int>(GamePlayer.score), OffX + 650, OffY + 185, vid);

	vid.NH_DrawImage(HelpButton, OffX + 618, OffY + 406, 1.0, 1.0);
	vid.NH_DrawImage(BackButton, OffX + 583, OffY + 462, 1.0, 1.0);
};

void menu_WorldMap::MC_IntroAni(Engine_Instance* engine) {
	Image pFrame;
	Image lFrame;
	std::string name;

	engine->audio_mngr.Stop();

	// Load Frame
	int P = 1;
	engine->video_mngr.NH_SetImageClearColor(255, 0, 255);
	for (int i = 1; i <= 120; i++) {
		int OffX = engine->video_mngr.NH_Width - 800;
		int OffY = engine->video_mngr.NH_Height - 600;
		OffX /= 2; OffY /= 2;
		name = "LarryParachute" + to_string2(i, 3);
		lFrame.NH_LoadImage("graphics/Menu/tga/" + name + ".bmp", engine->video_mngr);
		name = "PlaneSmoke2" + to_string2(P, 4);
		if (P <= 90) {
			P += 1;
			pFrame.NH_LoadImage("graphics/Menu/tga/" + name + ".bmp", engine->video_mngr);
		}
		engine->video_mngr.NH_ClearScreen(0, 0, 0);
		engine->video_mngr.NH_DrawImageCenteredReal(WorldMap, 0.5, 0.5, 1.0, 1.0);
		if (P <= 90) {
			engine->video_mngr.NH_DrawImage(pFrame, OffX + 34, OffY + 58, 1.0, 1.0);
		}
		engine->video_mngr.NH_DrawImage(lFrame, OffX + 6, OffY + 177, 1.0, 1.0);
		engine->video_mngr.NH_DrawBar(OffX, OffY, 800, 60, 0, 0, 0, 255);
		engine->video_mngr.NH_DrawBar(OffX, OffY + 600 - 60, 800, 60, 0, 0, 0, 255);
		engine->video_mngr.NH_DrawBar(OffX, OffY, 60, 600, 0, 0, 0, 255);
		engine->video_mngr.NH_DrawBar(OffX + 800 - 60, OffY, 60, 600, 0, 0, 0, 255);
		engine->video_mngr.NH_UpdateScreen();
		if (engine->input_mngr.NH_KeyReleased())
			goto end;
		if (!engine->MAIN_ThreadRunning)
			return;
	}
end:
	pFrame.NH_FreeImage();
	lFrame.NH_FreeImage();
	for (int i = 0; i <= 60; i++) {
		int OffX = engine->video_mngr.NH_Width - 800;
		int OffY = engine->video_mngr.NH_Height - 600;
		OffX /= 2;
		OffY /= 2;
		engine->video_mngr.NH_ClearScreen(0, 0, 0);
		engine->video_mngr.NH_DrawImageCenteredReal(WorldMap, 0.5, 0.5, 1.0, 1.0);
		engine->video_mngr.NH_DrawBar(OffX, OffY, 800, 60 - i, 0, 0, 0, 255);
		engine->video_mngr.NH_DrawBar(OffX, OffY + 600 - (60 - i), 800, 60 - i, 0, 0, 0, 255);
		engine->video_mngr.NH_DrawBar(OffX, OffY, 60 - i, 600, 0, 0, 0, 255);
		engine->video_mngr.NH_DrawBar(OffX + 800 - (60 - i), OffY, 60 - i, 600, 0, 0, 0, 255);
		engine->video_mngr.NH_UpdateScreen();
		if (!engine->MAIN_ThreadRunning)
			return;
	}

	// Side Menu Stuff

	for (int i = 1; i <= 9; i++) {
		lFrame.NH_LoadImage("graphics/Menu/map/bar/map-bar-fm" + to_string2(i, 2) + ".bmp", engine->video_mngr);

		int OffX = engine->video_mngr.NH_Width - 800;
		int OffY = engine->video_mngr.NH_Height - 600;
		OffX /= 2;
		OffY /= 2;
		engine->video_mngr.NH_ClearScreen(0, 0, 0);
		engine->video_mngr.NH_DrawImageCenteredReal(WorldMap, 0.5, 0.5, 1.0, 1.0);
		engine->video_mngr.NH_DrawImage(lFrame, OffX + 800 - 229, OffY, 1.0, 1.0);
		engine->video_mngr.NH_UpdateScreen();

		if (engine->input_mngr.NH_KeyReleased())
			goto end2;
		if (!engine->MAIN_ThreadRunning)
			return;
	}
	for (int i = 1; i <= 7; i++) {
		lFrame.NH_LoadImage("graphics/Menu/map/gobackfade/go-back-fm" + to_string2(i, 2) + ".bmp", engine->video_mngr);
		pFrame.NH_LoadImage("graphics/Menu/map/helpfade/help-btn-fm" + to_string2(i, 2) + ".bmp", engine->video_mngr);

		int OffX = engine->video_mngr.NH_Width - 800;
		int OffY = engine->video_mngr.NH_Height - 600;
		OffX /= 2;
		OffY /= 2;
		engine->video_mngr.NH_ClearScreen(0, 0, 0);
		engine->video_mngr.NH_DrawImageCenteredReal(WorldMap, 0.5, 0.5, 1.0, 1.0);
		engine->video_mngr.NH_DrawImage(Sidebar, OffX + 800 - 229, OffY, 1.0, 1.0);

		// Help Button
		engine->video_mngr.NH_DrawImage(pFrame, OffX + 618, OffY + 406, 1.0, 1.0);
		// Go back button
		engine->video_mngr.NH_DrawImage(lFrame, OffX + 583, OffY + 462, 1.0, 1.0);
		engine->video_mngr.NH_UpdateScreen();

		if (engine->input_mngr.NH_KeyReleased())
			goto end2;
		if (!engine->MAIN_ThreadRunning)
			return;
	}
end2:
	lFrame.NH_FreeImage();
	if (engine->input_mngr.NH_GetMouseReleased()) {}
};
