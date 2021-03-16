
#include "Minnesota_Cuke_Heads.h"

extern MenuState CurrentMenu;
extern MenuState LastMenu;
extern bool RunOnRun;
extern bool MenuDiff;
extern bool NewPlayerActive;

extern bool RemoveM;
extern int RemovePlayerb;

gsettings GameSettings;

void ResetSettings() {
	GameSettings.EasyMode = false;
	GameSettings.soundVol = 50;
	GameSettings.musicVol = 50;
	GameSettings.soundBx = 314;
	GameSettings.musicBx = 314;
};

//////////////////////////////////////////////////////////////////////////////////
//
//     Settings Menu Callback
//

void menu_SettMenu::MC_OnCall() {
	PlayedSnd = false;
	GameSettings.soundBx = static_cast<int>(((float)GameSettings.soundVol / 100.0f)* 135.0f) + 254;
	GameSettings.musicBx = static_cast<int>(((float)GameSettings.musicVol / 100.0f) * 135.0f) + 254;
};

void menu_SettMenu::MC_Reset() {
};

void menu_SettMenu::MC_Load(Video_Manager& vid) {
	vid.NH_SetImageClearColor(255, 0, 255);
	Backpic.NH_LoadImage("graphics/Menu/Settings/background.bmp", vid);
	Back_Button_Hover.NH_LoadImage("graphics/Menu/all/arrowmouseover.bmp", vid);
	Back_Button_Click.NH_LoadImage("graphics/Menu/all/arrowmouseup.bmp", vid);
	Ctrl_Hover.NH_LoadImage("graphics/Menu/Settings/controlsmouseover.bmp", vid);
	Ctrl_Click.NH_LoadImage("graphics/Menu/Settings/controlsclick.bmp", vid);
	Credits_Hover.NH_LoadImage("graphics/Menu/Settings/creditsmouseover.bmp", vid);
	Credits_Click.NH_LoadImage("graphics/Menu/Settings/creditsclick.bmp", vid);
	EasyOn.NH_LoadImage("graphics/Menu/Settings/easyon.bmp", vid);
	Music_Slide.NH_LoadImage("graphics/Menu/Settings/musicdefault.bmp", vid);
	Music_Slide_Hover.NH_LoadImage("graphics/Menu/Settings/musicmouseover.bmp", vid);
	Music_Slide_Drag.NH_LoadImage("graphics/Menu/Settings/musicdrag.bmp", vid);
	Voice_Slide.NH_LoadImage("graphics/Menu/Settings/voicesdefault.bmp", vid);
	Voice_Slide_Hover.NH_LoadImage("graphics/Menu/Settings/voicesmouseover.bmp", vid);
	Voice_Slide_Drag.NH_LoadImage("graphics/Menu/Settings/voicesdrag.bmp", vid);

	Larryspeak.Load("sounds/menu/51_cuke_change.wav", "LarryHelp");
	VoiceSnd.Load("sounds/menu/title.wav", "Voice");
	VolMusic.Load("sounds/Ambient.mp3", "Music");
};

void menu_SettMenu::MC_Unload() {
	Backpic.NH_FreeImage();
};

void menu_SettMenu::MC_Callback(Engine_Instance* engine) {

	if (!PlayedSnd) {
		engine->audio_mngr.Stop();
		engine->audio_mngr.Play(Larryspeak);
		PlayedSnd = true;
	}

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

	engine->video_mngr.NH_ClearScreen(0, 0, 0);
	engine->video_mngr.NH_DrawImageCenteredReal(Backpic, 0.5, 0.5, 1.0, 1.0);

	// Back button
	if (MouseX >= 0 && MouseY >= 0 &&
		MouseX < 78 && MouseY < 84) {
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			engine->video_mngr.NH_DrawImage(Back_Button_Click, OffX, OffY, 1.0, 1.0);
		}
		else if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			MC_ChangeMenu(MenuState::Main);
			engine->audio_mngr.Stop();
			return;
		}
		else {
			engine->video_mngr.NH_DrawImage(Back_Button_Hover, OffX, OffY, 1.0, 1.0);
		}
	}

	// Easy Mode
	if (MouseX >= 312 && MouseY >= 218 &&
		MouseX < 442 && MouseY < 284) {
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			GameSettings.EasyMode = !GameSettings.EasyMode;
		}
	}
	if (GameSettings.EasyMode)
		engine->video_mngr.NH_DrawImage(EasyOn, OffX+312, OffY+218, 1.0, 1.0);

	// Sound Volume
	if (MouseX >= GameSettings.soundBx && MouseY >= 430 &&
		MouseX < GameSettings.soundBx + 74 && MouseY < 452) {
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			if (sClickX==-1) {
				sClickX = (MouseX);
			}
			if (MouseX != sClickX) {
				GameSettings.soundBx += MouseX - sClickX;
				sClickX = (MouseX);
			}
			if (GameSettings.soundBx < 254)
				GameSettings.soundBx = 254;
			if (GameSettings.soundBx > 389)
				GameSettings.soundBx = 389;
			// Draw
			engine->video_mngr.NH_DrawImage(Voice_Slide_Drag, OffX+GameSettings.soundBx, OffY+430, 1.0, 1.0);
		}
		else {
			engine->video_mngr.NH_DrawImage(Voice_Slide_Hover, OffX+GameSettings.soundBx, OffY+ 430, 1.0, 1.0);
		}
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			sClickX = -1;
			if(!VoiceSnd.Playing())
				engine->audio_mngr.Play(VoiceSnd);
		}
		GameSettings.soundVol = static_cast<int>(((float)(GameSettings.soundBx-254) / 135.0f)*100.0f);
		engine->audio_mngr.SetSoundVolume(GameSettings.soundVol);
	}
	else {
		sClickX = -1;
		engine->video_mngr.NH_DrawImage(Voice_Slide, OffX+ GameSettings.soundBx, OffY+ 430, 1.0, 1.0);
	}

	// Music Volume
	if (MouseX >= GameSettings.musicBx && MouseY >= 485 &&
		MouseX < GameSettings.musicBx + 74 && MouseY < 507) {
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			if (mClickX == -1) {
				mClickX = (MouseX);
			}
			if (MouseX != mClickX ) {
				GameSettings.musicBx += MouseX - mClickX;
				mClickX = (MouseX);
			}
			if (GameSettings.musicBx < 254)
				GameSettings.musicBx = 254;
			if (GameSettings.musicBx > 389)
				GameSettings.musicBx = 389;
			// Draw
			engine->video_mngr.NH_DrawImage(Music_Slide_Drag, OffX + GameSettings.musicBx, OffY+485, 1.0, 1.0);
		}
		else {
			engine->video_mngr.NH_DrawImage(Music_Slide_Hover, OffX + GameSettings.musicBx, OffY+485, 1.0, 1.0);
		}
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			mClickX = -1;
			if (!VolMusic.Playing())
				engine->audio_mngr.Play(VolMusic,true);
		}

		GameSettings.musicVol = static_cast<int>(((float)(GameSettings.musicBx - 254) / 135.0f) * 100.0f);

		engine->audio_mngr.SetMusicVolume(GameSettings.musicVol);
	}
	else {
		mClickX = -1;
		engine->video_mngr.NH_DrawImage(Music_Slide, OffX+GameSettings.musicBx, OffY+ 485, 1.0, 1.0);
	}

	// Draw / Update stuff
	if (engine->input_mngr.NH_GetMouseReleased()==0) {
	}

	engine->video_mngr.NH_UpdateScreen();

	if (engine->input_mngr.NH_GetKeyR(kb_Escape)) {
		MC_ChangeMenu(MenuState::Main);
	}
};

void menu_SettMenu::MC_Render(Video_Manager& vid) {
#undef SCREEN_WIDTH 
#undef SCREEN_HEIGHT
#define SCREEN_WIDTH vid.NH_Width
#define SCREEN_HEIGHT vid.NH_Height
	int OffX = (SCREEN_WIDTH - 800) / 2;
	int OffY = (SCREEN_HEIGHT - 600) / 2;
	vid.NH_ClearScreen(0, 0, 0);
	vid.NH_DrawImageCenteredReal(Backpic, 0.5, 0.5, 1.0, 1.0);
};
