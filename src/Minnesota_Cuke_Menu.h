#pragma once


enum class MenuState {
	Main,
	Help,
	Settings,
	Parents,
	Quit,
	Remove,
	Gameover,
	WorldMap,
	StartGame,
	PlayGame,
};

void MC_Write(std::string str, int x, int y, Image& font, Video_Manager& vid);
void MC_PlayMovie(std::string movName, Engine_Instance* engine);
std::string to_string2(int _Val, int num);
void MC_ChangeMenuBack(void);
void MC_ChangeMenu(MenuState m);
void MC_lMenuRender(bool v);

//     Main Menu Callback

class menu_MainMenu {
private:
	Image MainMenu_Background;
	Image MainMenu_Stop_Hover;
	Image MainMenu_Stop_Click;
	Image MainMenu_Go_Active;
	Image MainMenu_Go_Hover;
	Image MainMenu_Go_Click;
	Image MainMenu_Settings_Hover;
	Image MainMenu_Settings_Click;
	Image MainMenu_Remove_Active;
	Image MainMenu_Remove_Hover;
	Image MainMenu_Remove_Click;
	Image MainMenu_Little_Hat;
	Image MainMenu_Little_Heart;

	Image mainFont;
	Image blueFont;
	Image smallFont;

	// Sound EFX
	NH_Sound cuke_Opening;
	NH_Sound cuke_Welcome;
	bool openP = false;
	bool WelcP = false;

	// Music
	NH_Music bgmusic;

	std::vector<PlayerData> Players;
	std::string NewPlayer;
	bool TypingName = false;
	int menu_PSelected = -1;

public:
	void MC_OnCall();
	void MC_Reset();
	void MC_Load(Video_Manager& vid);
	void MC_Unload();
	void MC_Render(Video_Manager& vid);
	void MC_Callback(Engine_Instance* engine);

};

//     Quit Menu Callback

class menu_QuitMenu {
private:
	Image Quit_Popup;
	Image Quit_Yes;
	Image Quit_No;

	// Sound EFX
	NH_Sound cuke_Yes;
	NH_Sound cuke_No;
	NH_Sound cuke_AreYouSure;
	NH_Sound cuke_Goodbye;

	int ButtonSelected = -1;

public:
	void MC_OnCall();
	void MC_Reset();
	void MC_Load(Video_Manager& vid);
	void MC_Unload();
	void MC_Callback(Engine_Instance* engine);
};


//     Remove player Menu Callback

class menu_RemoveMenu {
private:
	Image Remove_Popup;
	Image Remove_Yes;
	Image Remove_No;

	// Sound EFX
	NH_Sound cuke_Yes;
	NH_Sound cuke_No;
	NH_Sound cuke_AreYouSure;

	int ButtonSelected = -1;

public:
	void MC_OnCall();
	void MC_Reset();
	void MC_Load(Video_Manager& vid);
	void MC_Unload();
	void MC_Callback(Engine_Instance* engine);
};

// World map Menu Callback

class menu_WorldMap {
private:
	Image WorldMap;
	Image Sidebar;
	Image Buddy;
	Image Score_Pic;
	Image Lvl_Unlock;
	Image LevelPics[15];
	Image Larry;
	Image X_Pic;
	Image HelpButton;
	Image BackButton;
	Image BackButton_Hover;
	Image HelpButton_Hover;
	Image BackButton_Click;
	Image HelpButton_Click;

	Image sNumsFont; // Small numbers
	Image lNumsFont; // Large numbers

public:
	void MC_IntroAni(Engine_Instance* engine);
	void MC_OnCall(Engine_Instance* engine);
	void MC_Reset();
	void MC_Load(Video_Manager& vid);
	void MC_Unload();
	void MC_Render(Video_Manager& vid);
	void MC_Callback(Engine_Instance* engine);
};


class menu_HelpMenu {
private:
	Image Backpic;
	Image HelpPic;
	NH_Sound Larryspeak;
	bool PlayedSnd = false;
public:
	void MC_OnCall();
	void MC_Reset();
	void MC_Load(Video_Manager& vid);
	void MC_Unload();
	void MC_Callback(Engine_Instance* engine);
};


struct gsettings {
	bool EasyMode;
	int soundVol;
	int musicVol;

	int soundBx;
	int musicBx;
	std::string password = "t3st";
	int timelimit = 0;
};

void ResetSettings();

class menu_SettMenu {
private:
	Image Backpic;
	Image Back_Button_Hover;
	Image Back_Button_Click;
	Image Ctrl_Hover;
	Image Ctrl_Click;
	Image Credits_Hover;
	Image Credits_Click;
	Image EasyOn;
	Image Music_Slide;
	Image Music_Slide_Hover;
	Image Music_Slide_Drag;
	Image Voice_Slide;
	Image Voice_Slide_Hover;
	Image Voice_Slide_Drag;

	NH_Sound Larryspeak;
	NH_Sound VoiceSnd;
	NH_Music VolMusic;
	bool PlayedSnd = false;

	int sClickX = -1;
	int mClickX = -1;
public:
	void MC_OnCall();
	void MC_Reset();
	void MC_Load(Video_Manager& vid);
	void MC_Unload();
	void MC_Render(Video_Manager& vid);
	void MC_Callback(Engine_Instance* engine);
};

class menu_StartGame {
private:
	Image Popup;
	Image lButton_Hover;
	Image lButton_Click;
	Image rButton_Hover;
	Image rButton_Click;
	Image levelName;
	Image letCUKE[4];
	bool ranHelp = false;
	int levelOn = 0;
	bool LoadLvlName = false;
public:
	void MC_OnCall();
	void MC_Reset();
	void MC_Load(Video_Manager& vid);
	void MC_Unload();
	void MC_Callback(Engine_Instance* engine);
};