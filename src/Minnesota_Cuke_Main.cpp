
#include "Minnesota_Cuke_Heads.h"

class Minnesota_Cuke_Instance : public GameInstance {
private:
	menu_MainMenu mMain;
	menu_QuitMenu mQuit;
	menu_RemoveMenu mRemove;
	menu_WorldMap mWorld;
	menu_HelpMenu mHelp;
	menu_SettMenu mSettings;
	menu_StartGame mStartG;
public:
	void onCreate(void) {
		// Run Into Movies
		MC_PlayAVI("Movies/antidote.avi");
		MC_PlayAVI("Movies/bigidea_intro.avi");
		ResetSettings();
		MC_GameSetup(engine->video_mngr);
		// Set to main menu
		MC_ChangeMenu(MenuState::Main);
		mMain.MC_Load(engine->video_mngr);
		mQuit.MC_Load(engine->video_mngr);
		mRemove.MC_Load(engine->video_mngr);
		mWorld.MC_Load(engine->video_mngr);
		mHelp.MC_Load(engine->video_mngr);
		mSettings.MC_Load(engine->video_mngr);
		mStartG.MC_Load(engine->video_mngr);
		MC_LoadGraphicsA(engine->video_mngr);
		extern gsettings GameSettings;
		engine->audio_mngr.SetSoundVolume(GameSettings.soundVol);
		engine->audio_mngr.SetMusicVolume(GameSettings.musicVol);
	};

	void onShutdown(void) {
		MC_UnloadGraphicsA();
		mMain.MC_Unload();
		mQuit.MC_Unload();
		mRemove.MC_Unload();
		mWorld.MC_Unload();
		mHelp.MC_Unload();
		mSettings.MC_Unload();
		mStartG.MC_Unload();
		MC_GameShutdown();
	};

	void Rlast() {
		extern bool RenderLastMenu;
		if (!RenderLastMenu)
			return;
		extern MenuState LastMenu;
		switch (LastMenu) {
		case MenuState::Main:
			mMain.MC_Render(engine->video_mngr);
			break;
		case MenuState::WorldMap:
			mMain.MC_Render(engine->video_mngr);
			break;
		case MenuState::Settings:
			mMain.MC_Render(engine->video_mngr);
			break;
		}
	}

	void onLoop(void) {
		extern MenuState CurrentMenu;
		extern bool RunOnRun;
		switch (CurrentMenu) {
			case MenuState::Main: 
				Rlast();
				if (RunOnRun) { mMain.MC_OnCall(); RunOnRun = false; }
				mMain.MC_Reset(); 
				mMain.MC_Callback(engine); 
				break;
			case MenuState::Quit: 
				if (RunOnRun) { mQuit.MC_OnCall(); RunOnRun = false; }
				mQuit.MC_Reset(); 
				mQuit.MC_Callback(engine); 
				break;
			case MenuState::Remove: 
				if (RunOnRun) { mRemove.MC_OnCall(); RunOnRun = false; }
				mRemove.MC_Reset(); 
				mRemove.MC_Callback(engine); 
				break;
			case MenuState::WorldMap: 
				if (RunOnRun) { mWorld.MC_OnCall(engine); RunOnRun = false; }
				mWorld.MC_Reset(); 
				mWorld.MC_Callback(engine);
				break;
			case MenuState::Help: 
				if (RunOnRun) { mHelp.MC_OnCall(); RunOnRun = false; }
				mHelp.MC_Reset(); 
				mHelp.MC_Callback(engine);
				break;
			case MenuState::Settings:
				if (RunOnRun) { mSettings.MC_OnCall(); RunOnRun = false; }
				mSettings.MC_Reset();
				mSettings.MC_Callback(engine);
				break;
			case MenuState::StartGame:
				if (RunOnRun) { mStartG.MC_OnCall(); RunOnRun = false; }
				mStartG.MC_Reset();
				mStartG.MC_Callback(engine);
				break;
			case MenuState::PlayGame:
				MC_GameLoop(engine);
				break;
		}
	};
};


int main(int argc, char* args[]) {
	NH_NoIntro();
	Engine_Instance engine("Minnesota Cuke and the Coconut Apes", 800, 600);
	Minnesota_Cuke_Instance game;
	engine.SetGameInstance(&game);
	engine.video_mngr.NH_ChageMinSize(800, 600);
	engine.run();
	return 0;
};