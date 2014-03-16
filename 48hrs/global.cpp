#include <iostream>
#include <vector>

#include "hge.h"
#include "hgefont.h"
#include "hgeresource.h"

// Pointer to the HGE interface.
HGE *hge=0;

hgeFont * fnt;
hgeResourceManager resource;

HTEXTURE bar;

HEFFECT punch;
HEFFECT shoot;

HSTREAM music;

hgeSprite * particles;

short NUMBER_PLAYERS = 2;
short PLUGGED_IN = 0;

short RED_FADE_ALPHA = 0;

bool DEBUG = false;

float GENERIC_COUNTDOWN = 0;