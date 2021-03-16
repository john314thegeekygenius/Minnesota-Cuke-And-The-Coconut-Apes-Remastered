
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
//     Main Menu Callback
//

void menu_MainMenu::MC_OnCall() {
//	WelcP = false;
};

void menu_MainMenu::MC_Reset() {
	if (MenuDiff == true) {
		MenuDiff = false;
	}
};

void menu_MainMenu::MC_Load(Video_Manager& vid) {
	vid.NH_SetImageClearColor(255, 0, 255);
	mainFont.NH_LoadImage("graphics/menu/font/white.bmp", vid);
	blueFont.NH_LoadImage("graphics/menu/font/blue.bmp", vid);
	smallFont.NH_LoadImage("graphics/menu/main/smalltext.bmp", vid);

	MainMenu_Background.NH_LoadImage("graphics/menu/main/main.bmp", vid);
	MainMenu_Stop_Hover.NH_LoadImage("graphics/menu/main/quit-mouseover.bmp", vid);
	MainMenu_Stop_Click.NH_LoadImage("graphics/menu/main/quit-mousedown.bmp", vid);
	MainMenu_Go_Active.NH_LoadImage("graphics/menu/main/go-active.bmp", vid);
	MainMenu_Go_Hover.NH_LoadImage("graphics/menu/main/go-mouseover.bmp", vid);
	MainMenu_Go_Click.NH_LoadImage("graphics/menu/main/go-mousedown.bmp", vid);
	MainMenu_Settings_Hover.NH_LoadImage("graphics/menu/main/settings-mouseover.bmp", vid);
	MainMenu_Settings_Click.NH_LoadImage("graphics/menu/main/settings-mousedown.bmp", vid);
	MainMenu_Remove_Active.NH_LoadImage("graphics/menu/main/remove-active.bmp", vid);
	MainMenu_Remove_Hover.NH_LoadImage("graphics/menu/main/remove-mouseover.bmp", vid);
	MainMenu_Remove_Click.NH_LoadImage("graphics/menu/main/remove-mousedown.bmp", vid);
	MainMenu_Little_Hat.NH_LoadImage("graphics/menu/main/littlehat.bmp", vid);
	MainMenu_Little_Heart.NH_LoadImage("graphics/menu/main/littleheart.bmp", vid);

	// Load sounds and music
	bgmusic.Load("sounds/Theme.mp3", "Theme");
	cuke_Opening.Load("sounds/menu/54_cuke_welcome.wav", "title");
	cuke_Welcome.Load("sounds/menu/sign-in.wav", "sign-in");

	// Load Player Data
	std::ifstream f;
	std::string name;
	f.open("playerlist.txt", std::ios::binary);
	if (!f.is_open()) {
		// That's fine, just make a new one later.
	}
	else {
		int num = 0;
		f >> num;
		for (int i = 0; i < num; i++) {
			f >> name;
			std::ifstream f2;
			f2.open(name + ".txt", std::ios::binary);
			if (f.is_open()) {
				PlayerData p;
				int n = 0;
				p.reset();
				f2 >> p.name;
				f2 >> p.seconds;
				f2 >> p.n;
				f2 >> p.levelUnlocked; if (p.levelUnlocked > 14) p.levelUnlocked = 14;
				f2 >> p.lives;
				f2 >> p.n;
				f2 >> p.score;
				if (p.score > 9999999999) p.score = 9999999999;
				f2 >> p.levelOn;
				f2 >> p.day;
				f2 >> p.month;
				f2 >> p.year;
				for(int m = 0; m < NumOfLevels*3; m++){
					int cuke = 0;
					f2 >> cuke;
					p.leveldata[m].CUKE[0] = cuke & 1;
					p.leveldata[m].CUKE[1] = cuke & 2;
					p.leveldata[m].CUKE[2] = cuke & 4;
					p.leveldata[m].CUKE[3] = cuke & 8;
				}
				for(int m = 0; m < NumOfLevels*3; m++){
					f2 >> p.leveldata[m].coins; // Coins
					f2 >> p.leveldata[m].t_played.hour;
					f2 >> p.leveldata[m].t_played.minute;
					f2 >> p.leveldata[m].t_played.second;
					f2 >> p.leveldata[m].t_best.hour;
					f2 >> p.leveldata[m].t_best.minute;
					f2 >> p.leveldata[m].t_best.second;
				}
				Players.push_back(p);
				f2.close();
			}
			else {
				// Ooops!
			}
		}
		f.close();
	}
	// Save Parental Settings
	f.open("parents.txt", std::ios::binary);
	if (!f.is_open()) {
		// That's fine, just don't save anyone
	}
	else {
		extern gsettings GameSettings;
		std::string str;
		f >> str;
		f >> GameSettings.password;
		f >> GameSettings.soundVol;
		f >> GameSettings.musicVol;
		f >> GameSettings.timelimit;
		f.close();
	}

};

void menu_MainMenu::MC_Unload() {
	mainFont.NH_FreeImage();
	blueFont.NH_FreeImage();
	smallFont.NH_FreeImage();
	MainMenu_Background.NH_FreeImage();
	MainMenu_Stop_Hover.NH_FreeImage();
	MainMenu_Stop_Click.NH_FreeImage();
	MainMenu_Go_Active.NH_FreeImage();
	MainMenu_Go_Hover.NH_FreeImage();
	MainMenu_Go_Click.NH_FreeImage();
	MainMenu_Settings_Hover.NH_FreeImage();
	MainMenu_Settings_Click.NH_FreeImage();
	MainMenu_Remove_Active.NH_FreeImage();
	MainMenu_Remove_Hover.NH_FreeImage();
	MainMenu_Remove_Click.NH_FreeImage();
	MainMenu_Little_Hat.NH_FreeImage();
	MainMenu_Little_Heart.NH_FreeImage();

	bgmusic.Free();
	cuke_Opening.Free();
	cuke_Welcome.Free();

	// Save Player Data
	std::ofstream f;
	std::string name;
	f.open("playerlist.txt", std::ios::binary);
	if (!f.is_open()) {
		// That's fine, just don't save anyone
	}
	else {
		int num = static_cast<int>(Players.size());
		f << num << "\n";
		for (int i = 0; i < num; i++) {
			name = Players[i].name;
			f << name << "\n";
			std::ofstream f2;
			f2.open(name + ".txt", std::ios::binary);
			if (f.is_open()) {
				PlayerData& p = Players[i];
				p.n = 0;
				f2 << p.name << "\n";
				f2 << p.seconds << "\n";
				f2 << p.n << "\n";
				f2 << p.levelUnlocked << "\n";
				f2 << p.lives << "\n";
				f2 << p.n << "\n";
				f2 << p.score << "\n";
				f2 << p.levelOn << "\n";
				f2 << p.day << "\n";
				f2 << p.month << "\n";
				f2 << p.year << "\n";
				for (int m = 0; m < NumOfLevels * 3; m++) {
					int cuke = p.leveldata[i].CUKE[0];
					cuke += (p.leveldata[i].CUKE[1] * 2);
					cuke += (p.leveldata[i].CUKE[2] * 4);
					cuke += (p.leveldata[i].CUKE[3] * 8);
					f2 << cuke << "\n";
				}
				for (int m = 0; m < NumOfLevels * 3; m++) {
					f2 << p.leveldata[m].coins << "\n";
					f2 << p.leveldata[m].t_played.hour << " ";
					f2 << p.leveldata[m].t_played.minute << " ";
					f2 << p.leveldata[m].t_played.second << "\n";
					f2 << p.leveldata[m].t_best.hour << " ";
					f2 << p.leveldata[m].t_best.minute << " ";
					f2 << p.leveldata[m].t_best.second << "\n";
				}
				f2.close();
			}
			else {
				// Ooops!
			}
		}
		f.close();
	}

	// Save Parental Settings
	f.open("parents.txt", std::ios::binary);
	if (!f.is_open()) {
		// That's fine, just don't save anything
	}
	else {
		extern gsettings GameSettings;
		f << "[PASSWORD]\n";
		f << GameSettings.password << "\n";
		f << GameSettings.soundVol << "\n";
		f << GameSettings.musicVol << "\n";
		f << GameSettings.timelimit << "\n";
		f.close();
	}
};

void menu_MainMenu::MC_Callback(Engine_Instance* engine) {
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

	if (!bgmusic.Playing()) {
		engine->audio_mngr.Stop();
		engine->audio_mngr.Play(bgmusic, true);
	}

	// Play sounds
	if (openP == false) {
		openP = true;
		engine->audio_mngr.Play(cuke_Opening);
	}
	if (WelcP == false) {
		if (!cuke_Opening.Playing()) {
			WelcP = true;
			engine->audio_mngr.Play(cuke_Welcome);
		}
	}

	// Render background img
	engine->video_mngr.NH_ClearScreen(0, 0, 0); // Black bars
	engine->video_mngr.NH_DrawImageCenteredReal(MainMenu_Background, 0.5, 0.5, 1.0, 1.0);

	// Draw player names
	for (int i = 0; i < Players.size() && i < 6; i++) {
		MC_Write(Players[i].name, OffX+512, OffY+223 + (i * 30), mainFont, engine->video_mngr);
	}
	if (menu_PSelected != -1) {
		// Draw buddy hat
		engine->video_mngr.NH_DrawImage(MainMenu_Little_Hat, OffX+487, OffY+229 + (menu_PSelected * 30), 1, 1);
		// Fill in information at top
		MC_Write(Players[menu_PSelected].name, OffX+487, OffY+93, blueFont, engine->video_mngr);
		// Score
		std::string tmpstr = std::to_string(Players[menu_PSelected].score);
		std::string tmp, tmp2;
		int c = 0;

		for (int i = static_cast<int>(tmpstr.length()) - 1; i >= 0; i--) {
			// Add commas
			tmp2.push_back(tmpstr[i]);
			if (++c >= 3) {
				c = 0;
				tmp2.push_back(',');
			}
		}
		for (int i = static_cast<int>(tmp2.length()) - 1; i >= 0; i--) {
			tmp.push_back(tmp2[i]);
		}
		tmpstr = tmp;
		for (int i = 0; i < tmpstr.length(); i++) {
			int dx = tmpstr[i] - '0';
			if (tmpstr[i] == 'h') dx = 10;
			if (tmpstr[i] == '-') dx = 11;
			if (tmpstr[i] == ',') dx = 12;
			if (tmpstr[i] == 'm') dx = 13;
			engine->video_mngr.NH_DrawPartImage(smallFont, OffX+555 + (i * 7), OffY+142, 1, 1, dx * 7, 0, 7, 9);
		}
		long long hors = Players[menu_PSelected].seconds / 3600;
		long long mins = ((long long)Players[menu_PSelected].seconds - (hors * 3600)) / 60;
		if (hors > 999999999999) hors = 999999999999;
		tmpstr = std::to_string(hors) + "h " + std::to_string(mins / 10) + std::to_string(mins % 10) + "m";
		for (int i = 0; i < tmpstr.length(); i++) {
			int dx = tmpstr[i] - '0';
			if (tmpstr[i] == 'h') dx = 10;
			if (tmpstr[i] == '-') dx = 11;
			if (tmpstr[i] == ',') dx = 12;
			if (tmpstr[i] == 'm') dx = 13;
			if (tmpstr[i] == ' ')
				continue;
			engine->video_mngr.NH_DrawPartImage(smallFont, OffX+600 + (i * 7), OffY+161, 1, 1, dx * 7, 0, 7, 9);
		}
		{
			int dx = (Players[menu_PSelected].levelOn / 3)+1;
			engine->video_mngr.NH_DrawPartImage(smallFont, OffX+710, OffY + 142, 1, 1, dx * 7, 0, 7, 9);
			dx = (Players[menu_PSelected].levelOn % 3)+1;
			engine->video_mngr.NH_DrawPartImage(smallFont, OffX + 710 + 9, OffY + 142, 1, 1, 77, 0, 7, 9);
			engine->video_mngr.NH_DrawPartImage(smallFont, OffX + 710 + 9 + 9, OffY + 142, 1, 1, dx * 7, 0, 7, 9);
		}
	}

	// Stop sign

	if (MouseX >= 11 && MouseY >= 492 &&
		MouseX < 89 && MouseY < 570) {
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			// Press
			engine->video_mngr.NH_DrawImage(MainMenu_Stop_Click, 11 + OffX, 492 + OffY, 1.0, 1.0);
		}
		else {
			// Hover
			engine->video_mngr.NH_DrawImage(MainMenu_Stop_Hover, 11 + OffX, 492 + OffY, 1.0, 1.0);
		}
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			// Quit Menu
			MC_ChangeMenu(MenuState::Quit);
			MC_lMenuRender(true);
			return;
		}
	}

	// Note book stuff

	bool drwgopic = true;

	// Type Name
	if (MouseX >= 486 && MouseY >= 92 &&
		MouseX < 744 && MouseY < 128) {
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			TypingName = true;
		}
	}
	if (TypingName) {
		int k = engine->input_mngr.NH_KeyReleased();
		if (k) {
			if (menu_PSelected != -1) {
				menu_PSelected = -1;
				NewPlayer.clear();
			}

			if ((k >= 'a' && k <= 'z') ||
				(k >= 'A' && k <= 'Z') ||
				(k >= '0' && k <= '9') ||
				(k == '!' || k == '@' || k == '\'' || k == '+' || k == '-' ||
					k == '.' || k == ',' || k == '\"' || k == '/')) {
				if (NewPlayer.size() < 13) {
					if (engine->input_mngr.NH_GetKey(kb_RShift) || engine->input_mngr.NH_GetKey(kb_LShift))
						k = toupper(k);
					NewPlayer.push_back(k);
				}
			}
			if (k == kb_Return) {
				// Start the game??
				goto StartNewGame;
			}
			if (k == kb_backspace) {
				if (NewPlayer.size())
					NewPlayer.pop_back();
			}
		}
		// Render NewPlayer name not Player[v].name
		MC_Write(NewPlayer, OffX+487, OffY + 93, blueFont, engine->video_mngr);
	}

	// Player selection
	if (MouseX >= 492 && MouseY >= 223 &&
		MouseX < 738 && MouseY < 400) {
		if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			TypingName = false;
			NewPlayer.clear();
			menu_PSelected = (MouseY - 223) / 30;
			if (menu_PSelected >= Players.size()) menu_PSelected = -1;
		}
	}

	// Remove player
	if (RemoveM) {
		RemoveM = false;
		if (RemovePlayerb != -1) {

			int p = RemovePlayerb;
			std::vector<PlayerData> newlist;
			for (int i = 0; i < Players.size(); i++) {
				if (i != p)
					newlist.push_back(Players[i]);
			}
			Players.clear();
			for (PlayerData p : newlist) {
				Players.push_back(p);
			}
			menu_PSelected = -1;
		}
	}

	// Start Game
	if (NewPlayer.length() || menu_PSelected != -1) {

		if (MouseX >= 636 && MouseY >= 453 &&
			MouseX < 750 && MouseY < 538) {
			if (engine->input_mngr.NH_GetMousePressed() == 0) {
				engine->video_mngr.NH_DrawImage(MainMenu_Go_Click, 636 + OffX, 453 + OffY, 1.0, 1.0);
			}
			else
				if (engine->input_mngr.NH_GetMouseReleased() == 0) {
					if (NewPlayer.length()) {
					StartNewGame:
						PlayerData p;
						p.name = NewPlayer;
						p.reset();
						Players.push_back(p);
						TypingName = false;
						NewPlayer.clear();
						menu_PSelected = static_cast<int>(Players.size() - 1);
						NewPlayerActive = true;
						MC_SetGamePlayer(Players.back());
						MC_PlayMovie("intro", engine);
						MC_ChangeMenu(MenuState::WorldMap);
						return;
					}
					else {
						NewPlayerActive = false;
						MC_SetGamePlayer(Players[menu_PSelected]);
						MC_ChangeMenu(MenuState::WorldMap);
						return;
					}
				}
				else {
					drwgopic = false;
					engine->video_mngr.NH_DrawImage(MainMenu_Go_Hover, 636 + OffX, 453 + OffY, 1.0, 1.0);
				}
		}
		if (drwgopic) {
			engine->video_mngr.NH_DrawImage(MainMenu_Go_Active, 636 + OffX, 453 + OffY, 1.0, 1.0);
		}
	}

	// Settings
	if (MouseX >= 481 && MouseY >= 481 &&
		MouseX < 605 && MouseY < 530) {
		if (engine->input_mngr.NH_GetMousePressed() == 0) {
			engine->video_mngr.NH_DrawImage(MainMenu_Settings_Click, 481 + OffX, 481 + OffY, 1.0, 1.0);
		}
		else if (engine->input_mngr.NH_GetMouseReleased() == 0) {
			MC_ChangeMenu(MenuState::Settings);
			return;
		}
		else {
			engine->video_mngr.NH_DrawImage(MainMenu_Settings_Hover, 481 + OffX, 481 + OffY, 1.0, 1.0);
		}
	}

	// Remove Player
	if (menu_PSelected != -1) {
		// Draw active pic
		bool drwpic = true;
		if (MouseX >= 481 && MouseY >= 422 &&
			MouseX < 605 && MouseY < 475) {
			drwpic = false;
			if (engine->input_mngr.NH_GetMousePressed() == 0) {
				engine->video_mngr.NH_DrawImage(MainMenu_Remove_Click, 481 + OffX, 422 + OffY, 1.0, 1.0);
			}
			else if (engine->input_mngr.NH_GetMouseReleased() == 0) {
				RemoveM = true;
				RemovePlayerb = menu_PSelected;

				MC_ChangeMenu(MenuState::Remove);
				MC_lMenuRender(true);
				return;
			}
			else {
				engine->video_mngr.NH_DrawImage(MainMenu_Remove_Hover, 481 + OffX, 422 + OffY, 1.0, 1.0);
			}

		}
		if (drwpic) {
			engine->video_mngr.NH_DrawImage(MainMenu_Remove_Active, 481 + OffX, 422 + OffY, 1.0, 1.0);
		}
	}
	// Prevent
	if (engine->input_mngr.NH_GetMouseReleased() == 0) {
	}

	engine->video_mngr.NH_UpdateScreen();

	if (engine->input_mngr.NH_GetKeyR(kb_Escape)) {
		MC_ChangeMenu(MenuState::Quit);
	}

};

void menu_MainMenu::MC_Render(Video_Manager& vid) {
#undef SCREEN_WIDTH 
#undef SCREEN_HEIGHT
#define SCREEN_WIDTH vid.NH_Width
#define SCREEN_HEIGHT vid.NH_Height
	int OffX = (SCREEN_WIDTH - 800) / 2;
	int OffY = (SCREEN_HEIGHT - 600) / 2;

	// Render background img
	vid.NH_ClearScreen(0, 0, 0); // Black bars
	vid.NH_DrawImageCenteredReal(MainMenu_Background, 0.5, 0.5, 1.0, 1.0);

	// Draw player names
	for (int i = 0; i < Players.size() && i < 6; i++) {
		MC_Write(Players[i].name, OffX + 512, OffY + 223 + (i * 30), mainFont, vid);
	}
	if (menu_PSelected != -1) {
		// Draw buddy hat
		vid.NH_DrawImage(MainMenu_Little_Hat, OffX + 487, OffY + 229 + (menu_PSelected * 30), 1, 1);
		// Fill in information at top
		MC_Write(Players[menu_PSelected].name, OffX + 487, OffY + 93, blueFont, vid);
		// Score
		std::string tmpstr = std::to_string(Players[menu_PSelected].score);
		std::string tmp, tmp2;
		int c = 0;

		for (int i = static_cast<int>(tmpstr.length()) - 1; i >= 0; i--) {
			// Add commas
			tmp2.push_back(tmpstr[i]);
			if (++c >= 3) {
				c = 0;
				tmp2.push_back(',');
			}
		}
		for (int i = static_cast<int>(tmp2.length()) - 1; i >= 0; i--) {
			tmp.push_back(tmp2[i]);
		}
		tmpstr = tmp;
		for (int i = 0; i < tmpstr.length(); i++) {
			int dx = tmpstr[i] - '0';
			if (tmpstr[i] == 'h') dx = 10;
			if (tmpstr[i] == '-') dx = 11;
			if (tmpstr[i] == ',') dx = 12;
			if (tmpstr[i] == 'm') dx = 13;
			vid.NH_DrawPartImage(smallFont, OffX + 555 + (i * 7), OffY + 142, 1, 1, dx * 7, 0, 7, 9);
		}
		tmpstr = std::to_string(Players[menu_PSelected].seconds / 3600) + "h" + std::to_string(int(Players[menu_PSelected].seconds / 600)) + std::to_string(int(Players[menu_PSelected].seconds / 60) % 10) + "s";
		for (int i = 0; i < tmpstr.length(); i++) {
			int dx = tmpstr[i] - '0';
			if (tmpstr[i] == 'h') dx = 10;
			if (tmpstr[i] == '-') dx = 11;
			if (tmpstr[i] == ',') dx = 12;
			if (tmpstr[i] == 'm') dx = 13;
			vid.NH_DrawPartImage(smallFont, OffX + 600 + (i * 7), OffY + 161, 1, 1, dx * 7, 0, 7, 9);
		}
		{
			int dx = Players[menu_PSelected].levelOn / 3;
			vid.NH_DrawPartImage(smallFont, OffX + 710, OffY + 142, 1, 1, dx * 7, 0, 7, 9);
			dx = Players[menu_PSelected].levelOn % 3;
			vid.NH_DrawPartImage(smallFont, OffX + 710 + 9, OffY + 142, 1, 1, 77, 0, 7, 9);
			vid.NH_DrawPartImage(smallFont, OffX + 710 + 9 + 7, OffY + 142, 1, 1, dx * 7, 0, 7, 9);
		}
	}

	// Note book stuff
	if (TypingName) {
		// Render NewPlayer name not Player[v].name
		MC_Write(NewPlayer, OffX + 487, OffY + 93, blueFont, vid);
	}
	// Start Game
	if (NewPlayer.length() || menu_PSelected != -1) {
		vid.NH_DrawImage(MainMenu_Go_Active, 636 + OffX, 453 + OffY, 1.0, 1.0);
	}

	// Remove Player
	if (menu_PSelected != -1) {
		// Draw active pic
		vid.NH_DrawImage(MainMenu_Remove_Active, 481 + OffX, 422 + OffY, 1.0, 1.0);
	}
};
