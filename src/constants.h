#pragma once
#ifndef CATGAME_CONSTANTS_H
#define CATGAME_CONSTANTS_H

using namespace std;

const string ROOT = "../src/resources/";

const string FONT_DEFAULT = ROOT + "fonts/PIXEARG_.TTF";

// Player
const string SPRITE_PLAYER_DEFAULT = ROOT + "sprites/player_default.png";

// World
const int TILE_WIDTH = 48;
const int TILE_HEIGHT = 48;
const string SPRITE_TILE_DEFAULT = ROOT + "sprites/tile_grass.png";
const string SPRITE_TILE_BOUNCY = ROOT + "sprites/tile_bounce.png";

#endif //CATGAME_CONSTANTS_H
