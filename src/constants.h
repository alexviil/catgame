#pragma once
#ifndef CATGAME_CONSTANTS_H
#define CATGAME_CONSTANTS_H

using namespace std;

const string ROOT = "../src/resources/";

const string FONT_DEFAULT = ROOT + "fonts/PIXEARG_.TTF";

// Player
const string SPRITE_PLAYER_DEFAULT = ROOT + "sprites/player_default.png";
const string SPRITE_PLAYER_DEFAULT_IDLE = ROOT + "sprites/player_defafult_idle.png";
const string SPRITE_PLAYER_DEFAULT_MOVE = ROOT + "sprites/player_default_move.png";

// World
const int TILE_WIDTH = 48;
const int TILE_HEIGHT = 48;
const string SPRITE_TILE_DEFAULT = ROOT + "sprites/tile_grass1.png";

#endif //CATGAME_CONSTANTS_H
