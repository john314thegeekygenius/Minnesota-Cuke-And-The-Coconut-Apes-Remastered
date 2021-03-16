#pragma once
typedef struct MC_Rect {
	int x;
	int y;
	int w;
	int h;
	int type;
}MC_Rect;

typedef struct MC_Collide {
	std::vector <int> data;
}MC_Collide;

struct MCE_Trigger {
	int x;
	int y;
	std::string value;
};

struct MCE_Object {
	int x = 0;
	int y = 0;
	int curframe = 0;
	int anitime = 0;
};

struct MCE_Animation {
	int width;
	int height;
	int cols; // width
	int rows; // height
	int numFrames;
	Image img;
	std::vector<int> frameTicks;
	std::vector<Position> offset;
	std::vector<std::string> keyFrames;
	std::vector<MC_Rect> collbox;
	// Callback things?
};

struct MCE_Powerup {
	Position Pos;
	bool Collected;
	int aniOn;
	int frameOn;
	//int AnimationID;
};

enum class Enemy_Type {
	MONKEY,
	PEA,
	FLIES,
	DOUBLE_PEAS,
	APE,
	COCO_MONKEY,
	BOWLING_APE,
	THROW_APE,
	SMASHER,
	BAT,
	FISH,
	CROCK_APE,
	JIMMY,
};

enum class Direction {
	dirLeft,
	dirRight,
	dirUp,
	dirDown
};

struct MCE_Enemy {
	Position Pos;
	Position PathMin;
	Position PathMax;
	Direction dir;
	int aniOn;
	int aniTick;
	// TODO:
	// Add more here
};


struct MCE_O {
	std::vector <MCE_Object> o;
};

struct MCE_T {
	std::vector<MCE_Trigger> t;
};

struct MCE_I {
	std::vector<MCE_Powerup> i;
};

struct MCE_E {
	std::vector<MCE_Enemy> e;
};

struct MapData {
	int MapWidth;
	int MapHeight;

	int Tile_Width;
	int Tile_Height;

	Image backdrop;
	Image tileSet;
	// vectors of things
	MCE_I Items[16];
	MCE_T Triggers[5];
	MCE_O BG_Objects[72];
	MCE_O FG_Objects[72];
	MCE_O Anim_Objects[72];
	MCE_E Enemys[16];

	std::vector<int> MapData;
	std::vector<MC_Rect> RectData;
	std::vector<MC_Collide> Fastcoll; // I have no idea what this is for
};

void MC_LoadGraphicsA(Video_Manager& vid);
void MC_UnloadGraphicsA();
void MC_LoadMap(int levelId, Video_Manager& vid);
void MC_UnloadMap();
void MC_DrawBackground(Video_Manager& vid);
void MC_DrawMap(Video_Manager& vid);
void MC_DrawForeground(Video_Manager& vid);
void MC_UpdateAnimations();

