
#include "Minnesota_Cuke_Heads.h"

// Actual gameplay stuff
MapData CurrentLevel;
Position Camera;
extern PlayerData GamePlayer;
MCE_Animation Animations[72];
MCE_Animation ItemAnimations[16];
MCE_Animation EnemyAnimations[16];

// Images
Image PlantsImages[72];

// Some tools for loading maps
void readline(std::string& ld, std::ifstream& f) {
	ld.clear();
	while (1) {
		int ch = f.get();
		if (f.eof()) return;
		if (ch == 13 || ch == 10) return;
		ld.push_back(ch);
	}
};

int to_int(std::string& s) {
	int v = 0;
	bool neg = false;
	for (int i = 0; i < s.length(); i++) {
		if (s[0] == '-' && i == 0) {
			neg = true;
			continue;
		}
		v *= 10;
		v += s[i] - '0';
	}
	return (neg) ? (-1 * v) : v;
};

void AddAnimation(MCE_Animation& ani,std::string dir,std::string name,Video_Manager &vid) {
	std::ifstream file;
	file.open(dir + name);
	if (file.is_open()) {
		while (!file.eof()) {
			std::string tag;
			readline(tag, file);
			if (tag.compare("[BMP]") == 0) {
				std::string data;
				readline(data, file);
				ani.img.NH_LoadImage(dir + data, vid);
				continue;
			}
			if (tag.compare("[NUM_FRAMES]") == 0) {
				std::string data;
				readline(data, file);
				ani.numFrames = to_int(data);
				continue;
			}
			if (tag.compare("[NUM_COL]") == 0) {
				std::string data;
				readline(data, file);
				ani.cols = to_int(data);
				continue;
			}
			if (tag.compare("[NUM_ROWS]") == 0) {
				std::string data;
				readline(data, file);
				ani.rows = to_int(data);
				continue;
			}
			if (tag.compare("[SIZE]") == 0) {
				std::string data;
				readline(data, file);
				int w = to_int(data);
				readline(data, file);
				int h = to_int(data);
				//Animations[i].width = w / Animations[i].cols;
				//Animations[i].height = h / Animations[i].rows;
				continue;
			}
			if (tag.compare("[SPRITE_SIZE]") == 0) {
				std::string data;
				readline(data, file);
				ani.width = to_int(data);
				readline(data, file);
				ani.height = to_int(data);
				continue;
			}
			if (tag.compare("[FRAMETIME]") == 0) {
				std::string data;
				ani.frameTicks.resize(ani.numFrames);
				for (int m = 0; m < ani.frameTicks.size(); m++) {
					readline(data, file);
					ani.frameTicks[m] = to_int(data);
				}
				continue;
			}
			if (tag.compare("[KEYFRAME]") == 0) {
				std::string data;
				ani.keyFrames.resize(ani.numFrames);
				for (int m = 0; m < ani.keyFrames.size(); m++) {
					readline(data, file);
					ani.keyFrames[m] = data;
				}
				continue;
			}
			if (tag.compare("[XOFFSET]") == 0) {
				std::string data;
				ani.offset.resize(ani.numFrames);
				for (int m = 0; m < ani.offset.size(); m++) {
					readline(data, file);
					ani.offset[m].x = to_int(data);
				}
				continue;
			}
			if (tag.compare("[YOFFSET]") == 0) {
				std::string data;
				ani.offset.resize(ani.numFrames);
				for (int m = 0; m < ani.offset.size(); m++) {
					readline(data, file);
					ani.offset[m].y = to_int(data);
				}
				continue;
			}
			if (tag.compare("[COLLRECT]") == 0) {
				std::string data;
				readline(data, file);
				ani.collbox.resize(ani.numFrames);
				for (int m = 0; m < ani.offset.size(); m++) {
					readline(data, file);
					ani.collbox[m].x = to_int(data);
					readline(data, file);
					ani.collbox[m].y = to_int(data);
					readline(data, file);
					ani.collbox[m].w = to_int(data);
					readline(data, file);
					ani.collbox[m].h = to_int(data);
				}
				continue;
			}

		}
		file.close();
	}
};

void MC_LoadGraphicsA(Video_Manager &vid) {
	int v = 0;
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "Banana.txt",vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "heart.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "coin.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "Pot.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "Invince.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "Gum.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "tuba.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "1up.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "Banana_1.txt", vid);
//	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "Cocanut.txt",vid);
	v++; v++; v++;
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "cuke-C.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "cuke-U.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "cuke-K.txt", vid);
	AddAnimation(ItemAnimations[v++], "graphics/PowerUps/", "cuke-E.txt", vid);
	/*
	v = 0;
	std::ifstream file;
	file.open("graphics/Enemys/EnemyList.txt");
	if (!file.is_open()) {
		NH_ClearError();
		NH_AddError("Could not open ");
		NH_AddError("graphics/Enemys/EnemyList.txt\n");
		NH_RunError();
	}
	else {
		while (!file.eof()) {
			std::string data;
			std::string dir;
			std::string fname;
			readline(data, file);
			for (int i = 1; i < data.length()-1; i++) {
				dir.push_back(data[i]);
			}
			AddAnimation(EnemyAnimations[v++], "graphics/Enemys/", dir + fname, vid);
		}
		file.close();
	}*/
};

void MC_UnloadGraphicsA() {
	for (int i = 0; i < 16; i++) {
		ItemAnimations[i].img.NH_FreeImage();
	}
};

void MC_LoadMap(int levelId,Video_Manager &vid) {
	// Unload the old map
	MC_UnloadMap();
	// Position Cuke
	GamePlayer.curPos.x = 50;
	GamePlayer.curPos.y = 50;
	Camera.x = 0;
	Camera.y = 0;// (CurrentLevel.MapHeight * Tile_Height) - 100;
	// Actual loading code
	std::string TilesetName;
	std::string mapname;
	std::ifstream file;
	extern gsettings GameSettings;
	// Make sure to add 'easy' to the path if it's on easy mode
	int levelv = (levelId / 3)+1;
	int a = levelId % 3;
	mapname = std::string("maps/") + (GameSettings.EasyMode?"easy/":"") +"level"+ std::to_string(levelv) + (char)('a'+a);
	// Open
	file.open(mapname + ".txt", std::ios::binary);
	if (file.is_open() == false) {
		std::cout << "Could not open map " << mapname + ".txt" << std::endl;
		return;
	}
	else {
		std::cout << "Opened map " << mapname << std::endl;
		while (!file.eof()) {
			std::string tag;
			readline(tag, file);
			if (tag.compare("[TILESET]") == 0) {
				std::string data;
				readline(data, file);
				// Load tileset image
				TilesetName = data;
				CurrentLevel.tileSet.NH_LoadImage(std::string("graphics/") + TilesetName, vid);
				// Precalculate tile size
				CurrentLevel.Tile_Width = CurrentLevel.tileSet.width / 8;
				CurrentLevel.Tile_Height = CurrentLevel.tileSet.height / 10;

			}
			else if (tag.compare("[TILESET_SIZE]") == 0) {
				std::string data;
				readline(data, file);
				//Tileset_Width = to_int(data);
				readline(data, file);
				//Tileset_Height = to_int(data);
			}
			else if (tag.compare("[COLUMNS]") == 0) {
				std::string data;
				readline(data, file);
				CurrentLevel.MapWidth = to_int(data);
			}
			else if (tag.compare("[ROWS]") == 0) {
				std::string data;
				readline(data, file);
				CurrentLevel.MapHeight = to_int(data);
			}
			else if (tag.compare("[TILES]") == 0) {
				CurrentLevel.MapData.resize(CurrentLevel.MapHeight * CurrentLevel.MapWidth, 0);
				for (int e = 0; e < CurrentLevel.MapHeight; e++) {
					for (int i = 0; i < CurrentLevel.MapWidth; i++) {
						std::string sV;
						readline(sV, file);
						int V = to_int(sV);
						CurrentLevel.MapData[e * CurrentLevel.MapWidth + i] = V;
					}
				}
			}
		}
		file.close();
	}

	file.open(mapname + "coll.txt", std::ios::binary);
	if (file.is_open() == false) {
		std::cout << "Could not open rects " << mapname + "coll.txt" << std::endl;
		return;
	}
	std::cout << "Opened rects" << std::endl;
	while (!file.eof()) {
		std::string tag;
		readline(tag, file);
		if (tag.compare("[RECTS]") == 0) {
			std::string data;
			readline(data, file);
			CurrentLevel.RectData.resize(to_int(data));
		}
		if (tag.compare("[RECTINFO]") == 0) {
			std::string data;
			for (int i = 0; i < CurrentLevel.RectData.size(); i++) {
				readline(data, file);
				CurrentLevel.RectData[i].x = to_int(data);
				readline(data, file);
				CurrentLevel.RectData[i].y = to_int(data);
				readline(data, file);
				CurrentLevel.RectData[i].w = to_int(data);
				readline(data, file);
				CurrentLevel.RectData[i].h = to_int(data);
				readline(data, file);
				CurrentLevel.RectData[i].type = to_int(data);
			}
		}
	}
	file.close();

	file.open(mapname + "AI.txt", std::ios::binary);
	if (file.is_open() == false) {
		std::cout << "Could not open AI " << mapname + "AI.txt" << std::endl;
		return;
	}
	std::cout << "Opened AI" << std::endl;
	while (!file.eof()) {
		std::string tag;
		readline(tag, file);

		Enemy_Type et = Enemy_Type::MONKEY;
		if (tag.compare("[MONKEY]") == 0) {
			et = Enemy_Type::MONKEY;
		}
		else if (tag.compare("[PEA_NATIVE]") == 0) {
			et = Enemy_Type::PEA;
		}
		else if (tag.compare("[LIZARD]") == 0) {
			et = Enemy_Type::FLIES;
		}
		else if (tag.compare("[PEA_CHIEF]") == 0) {
			et = Enemy_Type::DOUBLE_PEAS;
		}
		else if (tag.compare("[COCONUT_APE]") == 0) {
			et = Enemy_Type::APE;
		}
		else if (tag.compare("[COCONUT_TOSSING_MONKEY]") == 0) {
			et = Enemy_Type::COCO_MONKEY;
		}
		else if (tag.compare("[SWOOPING_BAT]") == 0) {
			et = Enemy_Type::BAT;
		}
		else if (tag.compare("[BOOMERANG_TOSSING_APE]") == 0) {
			et = Enemy_Type::THROW_APE;
		}
		else if (tag.compare("[JUMPING_FISH]") == 0) {
			et = Enemy_Type::FISH;
		}
		else if (tag.compare("[THICK_SCALED_JUMPING_FISH]") == 0) {
			et = Enemy_Type::FISH;
		}
		else if (tag.compare("[COCONUT_DROPPING_MONKEY]") == 0) {
			et = Enemy_Type::MONKEY;
		}
		else if (tag.compare("[DIVE_BOMBING_COCONUT_APES]") == 0) {
			et = Enemy_Type::APE;
		}
		else if (tag.compare("[PEA_GUARD]") == 0) {
			et = Enemy_Type::PEA;
		}
		else if (tag.compare("[SWINGING_MONKEY]") == 0) {
			et = Enemy_Type::MONKEY;
		}
		else if (tag.compare("[SKIING_APE]") == 0) {
			et = Enemy_Type::APE;
		}
		else if (tag.compare("[WINDOWSILL_CREATURE]") == 0) {
			et = Enemy_Type::SMASHER;
		}
		std::string data;
		readline(data, file);
		int num = to_int(data);
		for (int i = 0; i < num; i++) {
			readline(data, file);
			int x1 = to_int(data);
			readline(data, file);
			int y1 = to_int(data);
			readline(data, file);
			int x2 = to_int(data);
			readline(data, file);
			int y2 = to_int(data);
			readline(data, file);
			int x3 = to_int(data);
			readline(data, file);
			int y3 = to_int(data);
			MCE_Enemy e;
			e.Pos.x = x1;
			e.Pos.y = y1;
			e.PathMin.x = x2;
			e.PathMin.y = y2;
			e.PathMax.x = x3;
			e.PathMax.y = y3;
			e.aniOn = 0;
			e.aniTick = 0;
			if(x1 < x2)
				e.dir = Direction::dirRight;
			else
				e.dir = Direction::dirLeft;
			CurrentLevel.Enemys[static_cast<int>(et)].e.push_back(e);
		}
	}
	file.close();

	file.open(mapname + "triggers.txt", std::ios::binary);
	if (file.is_open() == false) {
		std::cout << "Could not open triggers " << mapname + "triggers.txt" << std::endl;
		return;
	}
	std::cout << "Opened triggers" << std::endl;
	while (!file.eof()) {
		std::string tag;
		readline(tag, file);
		int Ttype = -1;
		if (tag.compare("[LEVEL]") == 0) {
			Ttype = 0;
		}
		else if (tag.compare("[SOUND]") == 0) {
			Ttype = 1;
		}
		else if (tag.compare("[START]") == 0) {
			Ttype = 2;
		}
		else if (tag.compare("[SAVE]") == 0) {
			Ttype = 3;
		}
		else if (tag.compare("[TELEPORT]") == 0) {
			Ttype = 4;
		}

		if (Ttype != -1) {
			std::string data;
			readline(data, file);
			int num = to_int(data);
			for (int i = 0; i < num; i++) {
				MCE_Trigger trig;
				readline(data, file);
				trig.x = to_int(data);
				readline(data, file);
				trig.y = to_int(data);
				readline(data, file);
				trig.value = (data);
				CurrentLevel.Triggers[Ttype].t.push_back(trig);
			}
		}
	}
	file.close();

	file.open(mapname + "item.txt", std::ios::binary);
	if (file.is_open() == false) {
		std::cout << "Could not open items " << mapname + "item.txt" << std::endl;
		return;
	}
	std::cout << "Opened items" << std::endl;
	while (!file.eof()) {
		std::string tag;
		readline(tag, file);
		int Ttype = -1;
		if (tag.compare("[BANANA]") == 0) {
			Ttype = 0;
		}
		else if (tag.compare("[HEARTS]") == 0) {
			Ttype = 1;
		}
		else if (tag.compare("[COINS]") == 0) {
			Ttype = 2;
		}
		else if (tag.compare("[CLAYPOT]") == 0) {
			Ttype = 3;
		}
		else if (tag.compare("[INVINCIBLE]") == 0) {
			Ttype = 4;
		}
		else if (tag.compare("[BUBBLE_GUM]") == 0) {
			Ttype = 5;
		}
		else if (tag.compare("[TUBA]") == 0) {
			Ttype = 6;
		}
		else if (tag.compare("[1-UP]") == 0) {
			Ttype = 7;
		}
		else if (tag.compare("[A-BANANA]") == 0) {
			Ttype = 8;
		}
		else if (tag.compare("[BLANK]") == 0) {
			Ttype = 9;
		}
		else if (tag.compare("[BLANK]") == 0) {
			Ttype = 10;
		}
		else if (tag.compare("[BLANK]") == 0) {
			Ttype = 11;
		}
		else if (tag.compare("[C]") == 0) {
			Ttype = 12;
		}
		else if (tag.compare("[U]") == 0) {
			Ttype = 13;
		}
		else if (tag.compare("[K]") == 0) {
			Ttype = 14;
		}
		else if (tag.compare("[E]") == 0) {
			Ttype = 15;
		}

		if (Ttype != -1) {
			std::string data;
			readline(data, file);
			int num = to_int(data);
			for (int i = 0; i < num; i++) {
				MCE_Powerup itm;
				readline(data, file);
				itm.Pos.x = to_int(data);
				readline(data, file);
				itm.Pos.y = to_int(data);
				readline(data, file);
				readline(data, file);
				readline(data, file);
				readline(data, file);
				itm.Collected = false;
				itm.aniOn = 0;
				itm.frameOn = 0;
//				itm.AnimationID = Ttype;
				CurrentLevel.Items[Ttype].i.push_back(itm);
			}
		}
	}
	file.close();

	file.open(mapname + "BG1.txt", std::ios::binary);
	if (file.is_open() == false) {
		std::cout << "Could not open BG1 " << mapname + "BG1.txt" << std::endl;
		return;
	}
	std::cout << "Opened BG1" << std::endl;
	std::string data;

	int Ttype = 0;
	readline(data, file);
	int numAnis = to_int(data);
	int numLoad = 0;
	while (!file.eof()) {
		std::string tag;
		readline(tag, file); // name
		readline(tag, file); // bmp
		readline(tag, file); // width
		readline(tag, file); // height
		readline(tag, file);
		int numa = to_int(tag);

		for (int i = 0; i < numa; i++) {
			std::string data;
			MCE_Object obj;
			readline(data, file);
			obj.x = to_int(data);
			readline(data, file);
			obj.y = to_int(data);
			CurrentLevel.BG_Objects[Ttype].o.push_back(obj);
		}
		if(numa)
			PlantsImages[Ttype].NH_LoadImage("graphics/plants/plant" + std::to_string(Ttype + 1) + ".bmp", vid);
		numLoad += numa;
		if (numLoad >= numAnis) {
			goto endBG1;
		}

		Ttype += 1;
	}
	endBG1:
	file.close();

	file.open(mapname + "FG1.txt", std::ios::binary);
	if (file.is_open() == false) {
		std::cout << "Could not open FG1 " << mapname + "FG1.txt" << std::endl;
		return;
	}
	std::cout << "Opened FG1" << std::endl;

	Ttype = 0;
	readline(data, file);
	numAnis = to_int(data);
	numLoad = 0;
	while (!file.eof()) {
		std::string tag;
		readline(tag, file); // name
		readline(tag, file); // bmp
		readline(tag, file); // width
		readline(tag, file); // height
		readline(tag, file);
		int numa = to_int(tag);

		for (int i = 0; i < numa; i++) {
			std::string data;
			MCE_Object obj;
			readline(data, file);
			obj.x = to_int(data);
			readline(data, file);
			obj.y = to_int(data);
			CurrentLevel.FG_Objects[Ttype].o.push_back(obj);
		}
		if(numa)
			PlantsImages[Ttype].NH_LoadImage("graphics/plants/plant" + std::to_string(Ttype + 1) + ".bmp", vid);
		numLoad += numa;
		if (numLoad >= numAnis) {
			goto endFG1;
		}

		Ttype += 1;
	}
	endFG1:
	file.close();

	file.open(mapname + "Anim.txt", std::ios::binary);
	if (file.is_open() == false) {
		std::cout << "Could not open Anim " << mapname + "Anim.txt" << std::endl;
		return;
	}
	std::cout << "Opened Anim" << std::endl;

	Ttype = 0;
	readline(data, file);
	numAnis = to_int(data);
	numLoad = 0;
	while (!file.eof()) {
		std::string tag;
		// Skip this stuff because we don't need it
		readline(tag, file); // name
		readline(tag, file); // bmp
		readline(tag, file); // width
		readline(tag, file); // height
		readline(tag, file);
		int numa = to_int(tag);
		for (int i = 0; i < numa; i++) {
			std::string data;
			MCE_Object obj;
			readline(data, file);
			obj.x = to_int(data);
			readline(data, file);
			obj.y = to_int(data);
			obj.curframe = 0;
			CurrentLevel.Anim_Objects[Ttype].o.push_back(obj);
		}
//		if(numa)
//			AniImages[Ttype].NH_LoadImage("graphics/animations/anim" + std::to_string(Ttype + 1) + ".bmp", vid);
		numLoad += numa;
		if (numLoad >= numAnis) {
			goto endAniLoad;
		}
		Ttype += 1;
	}
	endAniLoad:
	file.close();

	// Load Animation data
	for (int i = 0; i < 72; i++) {
		AddAnimation(Animations[i], "graphics/animations/", "anim" + std::to_string(i + 1) + ".txt", vid);
	}
	CurrentLevel.backdrop.NH_LoadImage("graphics/background/level" + std::to_string(levelv) + (char)('a' + a) + ".bmp", vid);
	std::cout << "Done loading..." << std::endl;

};

void MC_UnloadMap() {
	// Unload all of the old stuff
	CurrentLevel.MapWidth = 1;
	CurrentLevel.MapHeight = 1;
	CurrentLevel.Tile_Width = 1;
	CurrentLevel.Tile_Height = 1;
	CurrentLevel.backdrop.NH_FreeImage();
	CurrentLevel.tileSet.NH_FreeImage();

	#define fi(n) for (int i = 0; i < n; i++)

	fi(16)
		CurrentLevel.Items[i].i.clear();
	fi(5) 
		CurrentLevel.Triggers[i].t.clear();
	fi(72) {
		CurrentLevel.BG_Objects[i].o.clear();
		CurrentLevel.FG_Objects[i].o.clear();
		CurrentLevel.Anim_Objects[i].o.clear();
	}
	CurrentLevel.MapData.clear();
	CurrentLevel.RectData.clear();
	CurrentLevel.Fastcoll.clear(); 

	fi(72) {
		PlantsImages[i].NH_FreeImage();
		Animations[i].img.NH_FreeImage();
	}
};

void MC_DrawBackground(Video_Manager& vid) {
#define SCREEN_WIDTH vid.NH_Width
#define SCREEN_HEIGHT vid.NH_Height
	int OffX = (SCREEN_WIDTH - 800) / 2;
	int OffY = (SCREEN_HEIGHT - 600) / 2;

	// Main back bmp
	vid.NH_ClearScreen(0, 0, 0); // Black bars

	int bx = -Camera.x / (CurrentLevel.backdrop.width / 200);
	int by = -Camera.y / (CurrentLevel.backdrop.height / 200);
	if (by < 0)
		by = 0;
	if (bx >= CurrentLevel.backdrop.width) {
		bx -= CurrentLevel.backdrop.width;
	}
	if (bx < 0)
		bx += CurrentLevel.backdrop.width;
	vid.NH_DrawImage(CurrentLevel.backdrop, bx - CurrentLevel.backdrop.width, SCREEN_HEIGHT - CurrentLevel.backdrop.height + by, 1, 1);
	vid.NH_DrawImage(CurrentLevel.backdrop, bx, SCREEN_HEIGHT - CurrentLevel.backdrop.height + by, 1, 1);
	vid.NH_DrawImage(CurrentLevel.backdrop, bx + CurrentLevel.backdrop.width, SCREEN_HEIGHT - CurrentLevel.backdrop.height + by, 1, 1);

	// Background elements
	for (int e = 0; e < 72; e++) {
		for (int i = 0; i < CurrentLevel.BG_Objects[e].o.size(); i++) {
			int x = CurrentLevel.BG_Objects[e].o[i].x;
			int y = CurrentLevel.BG_Objects[e].o[i].y;
			int t = e;
			y += SCREEN_HEIGHT;
			y -= CurrentLevel.Tile_Height * CurrentLevel.MapHeight;
			x -= Camera.x;
			y -= Camera.y;
			vid.NH_DrawImage(PlantsImages[t], x, y, 1, 1);
		}
	}
};

void MC_DrawMap(Video_Manager &vid) {
	// Draw the map tiles
	for (int e = 0; e < CurrentLevel.MapHeight; e++) {
		for (int i = 0; i < CurrentLevel.MapWidth; i++) {
			int v = CurrentLevel.MapData[e * CurrentLevel.MapWidth + i];
			int x = i * CurrentLevel.Tile_Width;
			int y = e * CurrentLevel.Tile_Height;
			y += SCREEN_HEIGHT;
			y -= CurrentLevel.Tile_Height * CurrentLevel.MapHeight;
			x -= Camera.x;
			y -= Camera.y;
			if (v > 0) {
				v -= 1;
				int dy = v / 8;
				int dx = v - (dy * 8);
				vid.NH_DrawPartImage(CurrentLevel.tileSet, x, y, 1, 1, 
					dx* CurrentLevel.Tile_Width, dy* CurrentLevel.Tile_Height, 
					CurrentLevel.Tile_Width, CurrentLevel.Tile_Height);
			}
		}
	}
	// Draw the enemys
	
	for (int i = 0; i < 16; i++) {
		for (int e = 0; e < CurrentLevel.Enemys[i].e.size(); e++) {
			MCE_Enemy& enemy = CurrentLevel.Enemys[i].e[e];
			int x = enemy.Pos.x;
			int y = enemy.Pos.y;
			y += SCREEN_HEIGHT;
			y -= CurrentLevel.Tile_Height * CurrentLevel.MapHeight;
			x -= Camera.x;
			y -= Camera.y;

			//int cols = EnemyAnimations[t].cols;
			//int ay = CurrentLevel.Items[t].i[i].aniOn / cols;
			//int ax = CurrentLevel.Items[t].i[i].aniOn % cols;
			//int aw = ItemAnimations[t].width;
			//int ah = ItemAnimations[t].height;
			//vid.NH_DrawPartImage(ItemAnimations[t].img, x, y, 1, 1, ax * aw, ay * ah, aw, ah);
			vid.NH_DrawBar(x, y, 50, 50, 255, 0, 0, 255);
		}
	}
};

void MC_DrawForeground(Video_Manager& vid) {
	// Draw Collectables
	for (int t = 0; t < 16; t++) {
		for (int i = 0; i < CurrentLevel.Items[t].i.size(); i++) {
			if (ItemAnimations[t].numFrames == 0)
				continue;
			int x = CurrentLevel.Items[t].i[i].Pos.x;
			int y = CurrentLevel.Items[t].i[i].Pos.y;
			y += SCREEN_HEIGHT;
			y -= CurrentLevel.Tile_Height * CurrentLevel.MapHeight;
			x -= Camera.x;
			y -= Camera.y;
			int cols = ItemAnimations[t].cols;
			int ay = CurrentLevel.Items[t].i[i].aniOn / cols;
			int ax = CurrentLevel.Items[t].i[i].aniOn % cols;
			int aw = ItemAnimations[t].width;
			int ah = ItemAnimations[t].height;
			vid.NH_DrawPartImage(ItemAnimations[t].img, x, y, 1, 1, ax * aw, ay * ah, aw, ah);
		}
	}

	// Draw foreground elements
	for (int e = 0; e < 72; e++) {
		for (int i = 0; i < CurrentLevel.Anim_Objects[e].o.size(); i++) {
			int x = CurrentLevel.Anim_Objects[e].o[i].x;
			int y = CurrentLevel.Anim_Objects[e].o[i].y;
			int t = e;
			y += SCREEN_HEIGHT;
			y -= CurrentLevel.Tile_Height * CurrentLevel.MapHeight;
			x -= Camera.x;
			y -= Camera.y;
			int dw = Animations[t].width;
			int dh = Animations[t].height;
			int f = CurrentLevel.Anim_Objects[e].o[i].curframe;
			int dy = f / Animations[t].cols;
			int dx = (f % Animations[t].cols);
			vid.NH_DrawPartImage(Animations[t].img, x, y, 1, 1,dx*dw,dy*dh,dw,dh);
		}
		for (int i = 0; i < CurrentLevel.FG_Objects[e].o.size(); i++) {
			int x = CurrentLevel.FG_Objects[e].o[i].x;
			int y = CurrentLevel.FG_Objects[e].o[i].y;
			int t = e;
			y += SCREEN_HEIGHT;
			y -= CurrentLevel.Tile_Height * CurrentLevel.MapHeight;
			x -= Camera.x;
			y -= Camera.y;
			vid.NH_DrawImage(PlantsImages[t], x, y, 1, 1);
		}
	}

};

void MC_UpdateAnimations() {
	for (int e = 0; e < 72; e++) {
		for (int i = 0; i < CurrentLevel.Anim_Objects[e].o.size(); i++) {
			MCE_Object& obj = CurrentLevel.Anim_Objects[e].o[i];
			int f = obj.curframe;
			if (++obj.anitime > Animations[e].frameTicks[f]) {
				obj.anitime -= Animations[e].frameTicks[f];
				obj.curframe += 1;
				if (obj.curframe >= Animations[e].numFrames) {
					obj.curframe = 0;
				}
			}
		}
	}
	// Update Collectables
	for (int t = 0; t < 16; t++) {
		if (ItemAnimations[t].numFrames == 0)
			continue;
		for (int i = 0; i < CurrentLevel.Items[t].i.size(); i++) {
			MCE_Powerup& p = CurrentLevel.Items[t].i[i];
			int f = p.aniOn;
			p.frameOn += 1;
			if (p.frameOn > ItemAnimations[t].frameTicks[f]){
				p.frameOn -= ItemAnimations[t].frameTicks[f];
				p.aniOn += 1;
				if (p.aniOn >= ItemAnimations[t].numFrames) {
					p.aniOn = 0;
				}
			}
		}
	}

	// Update Enemys
	for (int i = 0; i < 16; i++) {
		for (int e = 0; e < CurrentLevel.Enemys[i].e.size(); e++) {
			MCE_Enemy& enemy = CurrentLevel.Enemys[i].e[e];
			if (enemy.Pos.x < enemy.PathMin.x) {
				enemy.dir = Direction::dirRight;
			}
			if (enemy.Pos.x > enemy.PathMax.x) {
				enemy.dir = Direction::dirLeft;
			}
			if (enemy.dir == Direction::dirLeft) {
				enemy.Pos.x -= 1;
			}
			if (enemy.dir == Direction::dirRight) {
				enemy.Pos.x += 1;
			}

			enemy.Pos.y += 1;
			// Collide with the collision boxes
			int ew = 50;
			int eh = 50;
			for (int b = 0; b < CurrentLevel.RectData.size(); b++) {
				MC_Rect r = CurrentLevel.RectData[b];
				r.w -= r.x;
				r.h -= r.y;
				if (r.w <= 1 || r.h <= 1 || r.type == 0)
					continue;
				if (enemy.Pos.x + ew >= r.x && enemy.Pos.x <= r.x + r.w &&
					enemy.Pos.y + eh >= r.y && enemy.Pos.y <= r.y + r.h) {
					if (r.type == 1 || r.type == 130) {
						if (enemy.Pos.y + eh > r.y) {
							enemy.Pos.y = r.y - eh;
						}
					}
					if (r.type == 9) {
						// Get slope
						if ((enemy.Pos.x + ew) - r.x < r.w && enemy.Pos.x + ew >= r.x) {
							float slope = static_cast<float>(r.h) / static_cast<float>(r.w);
							int my = r.y + r.h - static_cast<int>(((enemy.Pos.x + ew) - r.x) * slope);
							if (enemy.Pos.y + eh > my) {
								enemy.Pos.y = my - eh;
							}
						}
					}
					if (r.type == 17) {
						// Get slope
						if ((enemy.Pos.x ) - r.x < r.w && enemy.Pos.x >= r.x) {
							float slope = static_cast<float>(r.h) / static_cast<float>(r.w);
							int my = r.y + static_cast<int>((enemy.Pos.x - r.x) * slope);
							if (enemy.Pos.y + eh > my) {
								enemy.Pos.y = my - eh;
							}
						}
					}
				}
			}
		}
	}
}
