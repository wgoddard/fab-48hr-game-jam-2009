#ifndef _GLOBAL_H
#define _GLOBAL_H

#include <iostream>
#include <vector>
#include <string>

#include "hge.h"
#include "hgefont.h"
#include "hgeresource.h"
#include "hgesprite.h"

extern HGE *hge;

extern hgeFont * fnt;
extern hgeSprite * particles;
extern hgeResourceManager resource;

extern HTEXTURE bar;

extern HEFFECT punch;
extern HEFFECT shoot;
extern HSTREAM music;

bool lastFrame();
bool loseRender();
bool winRender();
bool obscenityFrame();
bool obscenityRender();
bool riotFrame();
bool riotRender();

extern float GENERIC_COUNTDOWN;


extern bool DEBUG;

enum screen {S_WIDTH = 1280, S_HEIGHT = 720, S_BPP = 32, S_WINDOWED = true};

const std::string NAME = "Heart Quaker";
const std::string LOGFILE = "hq.log";
const char TITLE_GRAPHIC[] = "Title.png";

const DWORD COLOR = 0xFFFF0000;

extern short RED_FADE_ALPHA;

const int MAX_CONTROLLERS = 2;
extern short NUMBER_PLAYERS;
extern short PLUGGED_IN;

const int PHYS_ITER = 10;

#endif