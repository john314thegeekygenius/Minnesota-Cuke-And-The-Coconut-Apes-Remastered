
#include "Minnesota_Cuke_Heads.h"


MenuState CurrentMenu = MenuState::Main;
MenuState LastMenu = CurrentMenu;
bool RunOnRun = false;
bool MenuDiff = false;
bool NewPlayerActive = false;

bool RemoveM = false;
int RemovePlayerb = -1;
bool RenderLastMenu = false;

void MC_ChangeMenu(MenuState m) {
	LastMenu = CurrentMenu;
	CurrentMenu = m;
	MenuDiff = true;
	RunOnRun = true;
	RenderLastMenu = false;
};

void MC_ChangeMenuBack(void) {
	MenuState tmp = LastMenu;
	LastMenu = CurrentMenu;
	CurrentMenu = tmp;
	MenuDiff = true;
	RunOnRun = true;
	RenderLastMenu = false;
};

void MC_lMenuRender(bool v) {
	RenderLastMenu = v;
};


std::string to_string2(int _Val, int num) { // convert double to string
	std::string a = "%0" + std::to_string(num) + "i";
	const auto _Len = static_cast<size_t>(_CSTD _scprintf(a.c_str(), _Val));
	std::string _Str(_Len, '\0');
	_CSTD sprintf_s(&_Str[0], _Len + 1, a.c_str(), _Val);
	return _Str;
}


void MC_PlayMovie(std::string movName, Engine_Instance* engine) {
	Image Frame1, Frame2;
	NH_Sound Speech1, Speech2;
	std::string name;
	std::ifstream f;
	f.open("Movies/" + movName + ".txt");
	if (!f.is_open()) {
		NH_ClearError();
		NH_AddError("Could not open Movies/" + movName + ".txt");
		NH_ErrorWarning();
		return;
	}

	engine->audio_mngr.Stop();

	while(!f.eof()){
		// Load Audio
		f >> name;
		if (name.compare("[END]") != 0) {
			Speech1.Free();
			Speech1.Load("sounds/CutScenes/" + movName + "/" + name + ".wav", "speak1");
			// Load Frame
			f >> name;
			Frame1.NH_FreeImage();
			Frame1.NH_LoadImage("Movies/" + name + ".bmp", engine->video_mngr);
		}
		while (Speech2.Playing()) {
			// Show Frame
			engine->video_mngr.NH_ClearScreen(0, 0, 0);
			engine->video_mngr.NH_DrawImageCenteredReal(Frame2, 0.5, 0.5, 1.0, 1.0);
			engine->video_mngr.NH_UpdateScreen();
			if (engine->input_mngr.NH_KeyReleased())
				goto end;
		};
		if (name.compare("[END]") == 0) {
			goto end;
		}

		// Play Audio
		engine->audio_mngr.Play(Speech1);
		// Show Frame
		engine->video_mngr.NH_ClearScreen(0, 0, 0);
		engine->video_mngr.NH_DrawImageCenteredReal(Frame1, 0.5, 0.5, 1.0, 1.0);
		engine->video_mngr.NH_UpdateScreen();

		// Load Audio
		f >> name;
		if (name.compare("[END]") != 0) {
			Speech2.Free();
			Speech2.Load("sounds/CutScenes/" + movName + "/" + name + ".wav", "speak2");
			// Load Frame
			f >> name;
			Frame2.NH_FreeImage();
			Frame2.NH_LoadImage("Movies/" + name + ".bmp", engine->video_mngr);
		}
		while (Speech1.Playing()) {
			// Show Frame
			engine->video_mngr.NH_ClearScreen(0, 0, 0);
			engine->video_mngr.NH_DrawImageCenteredReal(Frame1, 0.5, 0.5, 1.0, 1.0);
			engine->video_mngr.NH_UpdateScreen();
			if (engine->input_mngr.NH_KeyReleased())
				goto end;
		};
		if (name.compare("[END]") == 0) {
			goto end;
		}
		// Play Audio
		engine->audio_mngr.Play(Speech2);
		// Show Frame
		engine->video_mngr.NH_ClearScreen(0, 0, 0);
		engine->video_mngr.NH_DrawImageCenteredReal(Frame2, 0.5, 0.5, 1.0, 1.0);
		engine->video_mngr.NH_UpdateScreen();

	}
	end:
	Speech1.Free();
	Speech2.Free();
	Frame1.NH_FreeImage();
	Frame2.NH_FreeImage();

};

const std::string fontdecode = " !\" { }\'   +,-./0123456789      @ABCDEFGHIJKLMNOPQRSTUVWXYZ      abcdefghijklmnopqrstuvwxyz";

void MC_Write(std::string str, int x, int y, Image& font,Video_Manager &vid) {
	// decode str
	int w = font.width / 10;
	int h = font.height / 10;
	for (int i = 0; i < str.length(); i++) {
		for (int e = 0; e < fontdecode.length(); e++) {
			if (str[i] == fontdecode[e]) {
				// Draw that char
				int cy = e / 10;
				int cx = e - (cy * 10);
				vid.NH_DrawPartImage(font, x + (i * w), y, 1, 1, cx * w, cy * h, w, h);

			}
		}
	}
};

