// This file is part of the course TPV2@UCM - Samir Genaim

/*
 * The content of this class is based on https://glouw.com/2018/03/11/littlewolf.html
 */

#pragma once

#include <SDL.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <string>
#include <fstream>

#include "../sdlutils/InputHandler.h"

class LittleWolf {
public:

	// a point in a 2D-plane
	struct Point {
		float x;
		float y;
	};


	// Used to represent a position where a ray hits, and which tile
	struct Hit {
		int tile;
		Point where;
	};

	// a line between two points
	struct Line {
		Point a;
		Point b;
	};

	// The information on the window/renderer, the size of the window, and a texture
	// that we use to draw the walls, etc.
	struct Gpu {
		SDL_Window *window;
		SDL_Renderer *renderer;
		SDL_Texture *texture;
		int xres;
		int yres;
	};

	// when we lock a texture, we get an array of pixels where we can draw
	struct Display {
		uint32_t *pixels;
		int width;
	};

	// representing a (project) wall
	struct Wall {
		int top;
		int bot;
		float size;
	};

	// the status of a player
	enum PlayerState : uint8_t {
		NOT_USED, ALIVE, DEAD
	};

	// player information
	struct Player {
		uint8_t id;          // the id
		Line fov;            // focal view
		Point where;         // current position (wrt. to the grid)
		Point velocity;      // current velocity
		float speed;         // maximum speed
		float acceleration;  // acceleration
		float theta;         // rotation (in rad)
		PlayerState state;   // the state
float health;        // health of the player
	};

	// Representing a map, the user_walling is the walling provided by the user, and
	// walling is a scaled up version. Here is a brief explanation of what method load
	// does.
	//
	// 1. The input JSON file is read into the user_walling field. The fields user_walling_width
	//    and user_walling_height indicates the size of the matrix.
	//
	// 2. The size of the window will be like the size of the walling multiplied by the scaling
	//    factor that is provide in the JSON file. This means that every cell of user_walling is
	//    drawn as square of size scaling_factor x scaling_factor.
	//
	// 3. The user_walling is to small for navigation, you can see for example the the corridors have
	//    width of two cells. We can use a scaled version for navigation, which is stored in walling.
	//    The size of walling can be like the size of the window, or less for efficiency reasons. It is
	//    determined by the value of the field _walling_size_factor as follows: if the window's resolution
	//    is (_xres x _yres) then the size of walling is (_xres/_walling_size_factor x _yres/_walling_size_factor).
	//    Fields walling_width and walling_height include the dimension of walling.
	//
	struct Map {
		uint8_t **user_walling;
		uint8_t **walling;

		uint16_t user_walling_width;
		uint16_t user_walling_height;
		uint16_t walling_width;
		uint16_t walling_height;

		Map() {
			user_walling = walling = nullptr;
			user_walling_width = user_walling_height = walling_width =
					walling_height = 0u;
		}

		~Map() {
			if (user_walling != nullptr) {
				for (auto i = 0u; i < user_walling_height; i++) {
					delete[] user_walling[i];
				}
				delete[] user_walling;
			}
			if (walling != nullptr) {
				for (auto i = 0u; i < walling_height; i++) {
					delete[] walling[i];
				}
				delete[] walling;
			}
		}
	};

	LittleWolf();
	virtual ~LittleWolf();

	// load a map from a file
	void load(std::string filename);

	// add a new player with identifier <id>, returns false if the id is already occupied
	bool addPlayer(std::uint8_t id);

	// removes a new player with identifier <id>
	bool removePlayer(std::uint8_t id);

	// as master handles whether another player has been shoot or not
	void handle_shoot(std::uint8_t id);

	void killPlayer(std::uint8_t id);

	// initialize the SDL window information
	void init(SDL_Window *window, SDL_Renderer *render);

	// render the walls, etc
	void render();

	// update the world, etc
	void update();

	void send_my_info();

	void update_player_info(Uint8 id, float posX, float posY, float fovPointAX, float fovPointAY,
		float fovPointBX, float fovPointBY, float rot, Uint8 state);

	void update_player_state(Uint8 id, float posX, float posY, float fovPointAX, float fovPointAY,
		float fovPointBX, float fovPointBY, float rot);

	void update_player_health(Uint8 id, float health);

	int get_xres() {
		return _xres;
	}

	int get_yres() {
		return _yres;
	}

	// mark all (used) player alive
	void bringAllToLife();

	void randomizePlayerPositions();
	void randomizePlayerPosition(std::uint8_t id);

	inline int getPlayersAlive() {
		int count = 0;
		for (int i = 0; i < _max_player; i++) if (_players[i].state == ALIVE) count++;
		return count;
	}

	void checkRestart();

	void set_countdown_params(bool active, int count_val);

private:

	// Checks if the game is restarting, for the render
	bool restarting = false;
	int start_time;

	int countdown_val;

	float _max_health = 100.0f;

	// Calculates wall size using the <corrected> ray to the wall.
	Wall project(const int xres, const int yres, const float focal,
			const Point corrected);

	// Casts a ray from <where> in unit <direction> until a <walling> tile is hit.
	Hit cast(const Point where, Point direction, uint8_t **walling,
			bool ignore_players, bool ignore_deads);

	// Moves the player when w,a,s,d are held down. Handles collision detection for the walls.
	bool shoot(Player &p);

	// Spins the player when keys grid_h,l are held down. When left-shit is held down the move is slower
	inline void spin(Player &p);

	// Moves the player when w,a,s,d are held down. Handles collision detection for the walls.
	void move(Player &p);

	// Renders the entire scene from the <current player> perspective given a <map> and a software <gpu>.
	void render_map(Player &p);

	// Renders the entire scene from the <current player> perspective given a <map> and a software <gpu>.
	void render_upper_view();

	// Render a list of current player
	void render_players_info();

	// These are auxiliary function for vectors, colors, etc. All are from original littlewolf.

	// Changes the field of view. A focal value of 1.0 is 90 degrees.
	inline Line viewport(float focal) {
		Line fov = { { focal, -1.0f }, { focal, +1.0f }, };
		return fov;
	}

	// Rotates the player by some radian value.
	inline Point turn(const Point a, const float t) {
		const Point b = { a.x * cosf(t) - a.y * sinf(t), a.x * sinf(t)
				+ a.y * cosf(t) };
		return b;
	}

	// Rotates a point 90 degrees.
	inline Point rag(const Point a) {
		const Point b = { -a.y, a.x };
		return b;
	}

	// Subtracts two points.
	inline Point sub(const Point a, const Point b) {
		const Point c = { a.x - b.x, a.y - b.y };
		return c;
	}

	// Adds two points.
	inline Point add(const Point a, const Point b) {
		const Point c = { a.x + b.x, a.y + b.y };
		return c;
	}

	// Multiplies a point by a scalar value.
	inline Point mul(const Point a, const float n) {
		const Point b = { a.x * n, a.y * n };
		return b;
	}

	// Returns the magnitude of a point.
	inline float mag(const Point a) {
		return sqrtf(a.x * a.x + a.y * a.y);
	}

	// Returns the unit vector of a point.
	inline Point unit(const Point a) {
		return mul(a, 1.0f / mag(a));
	}

	// Returns the slope of a point.
	inline float slope(const Point a) {
		return a.y / a.x;
	}

	// Rotates a line by some radian amount.
	inline Line rotate(const Line l, const float t) {
		const Line line = { turn(l.a, t), turn(l.b, t) };
		return line;
	}

	// Linear interpolation.
	inline Point lerp(const Line l, const float n) {
		return add(l.a, mul(sub(l.b, l.a), n));
	}

	// Fast floor (math.grid_h is too slow).
	inline int fl(const float x) {
		return (int) x - (x < (int) x);
	}

	// Fast ceil (math.grid_h is too slow).
	inline int cl(const float x) {
		return (int) x + (x > (int) x);
	}

	// Returns a decimal value of the ascii tile value on the map.
	inline uint8_t tile(const Point a, uint8_t **tiles) {
		const int x = a.x;
		const int y = a.y;
		return tiles[y][x];
	}

	inline Display lock(const Gpu gpu) {
		void *screen;
		int pitch;
		SDL_LockTexture(gpu.texture, NULL, &screen, &pitch);
		const Display display = { (uint32_t*) screen, pitch
				/ (int) sizeof(uint32_t) };
		return display;
	}

	// Places a pixels in gpu video memory.
	inline void put(const Display display, const int x, const int y,
			const uint32_t pixel) {
		display.pixels[y + x * display.width] = pixel;
	}

	// Unlocks the gpu, making the pointer to video memory ready for presentation
	inline void unlock(const Gpu gpu) {
		SDL_UnlockTexture(gpu.texture);
	}

	// Steps horizontally along a square grid.
	inline Point sh(const Point a, const Point b) {
		const float x = b.x > 0.0f ? fl(a.x + 1.0f) : cl(a.x - 1.0f);
		const float y = slope(b) * (x - a.x) + a.y;
		const Point c = { x, y };
		return c;
	}

	// Steps vertically along a square grid.
	inline Point sv(const Point a, const Point b) {
		const float y = b.y > 0.0f ? fl(a.y + 1.0f) : cl(a.y - 1.0f);
		const float x = (y - a.y) / slope(b) + a.x;
		const Point c = { x, y };
		return c;
	}

	// Floating point decimal.
	inline float dec(const float x) {
		return x - (int) x;
	}

	// Returns a color value (RGBA) from a decimal tile value.
	// Why we need it? For some reason, the texture used in the original wolf
	// uses ARGB, and for Textures in SDLUtils we use RGBA. I tried to change the
	// one of littlewolf to use RGBA with no success ...
	inline uint32_t color_rgba(const uint8_t tile) {
		uint32_t c = color(tile);
		return (c << 8) | (c >> 24 & 0xff);
	}

	// Returns a color value (ARGB) from a decimal tile value.
	// Tile 1-9 represent walls, 10- are for players, 0 is not handled
	// because it is an empty cell
	inline uint32_t color(const uint8_t tile) {
		switch (tile) {
		case 1:
			return 0x00AA0000; // Red.
		case 2:
			return 0x0000AA00; // Green.
		case 3:
			return 0x000000AA; // Blue.
		case 4:
			return 0x00FFFF00; // Yellow
		case 5:
			return 0x0000FFFF; //Cyan/Aqua
		case 6:
			return 0x00FF00FF; // Magenta/Fuchsia
		case 7:
			return 0x00C0C0C0; // Silver
		case 8:
			return 0x00808080; // Gray
		case 9:
			return 0x00800000; // Maroon

			// from 10 on are colors of fighters
		case 10:
			return 0x00808000; // Olive
		case 11:
			return 0x00008000; // Green
		case 12:
			return 0x00800080; // Purple
		case 13:
			return 0x00008080; // Teal
		case 14:
			return 0x00000080; // Navy
		default:
			return 0x00f260b0; // Kind of dark green
		}
	}

	inline uint8_t player_to_tile(uint8_t id) {
		return id + 10;
	}

	inline uint8_t tile_to_player(uint8_t tile) {
		assert(tile >= 10);
		return tile - 10;
	}

	// Some fields defining all elements of the world, etc

	bool _show_help;

	// maximum number of player
	static constexpr uint8_t _max_player = 10;

	// resolution
	int _xres;
	int _yres;

	// Relation between window size and walling size
	static constexpr uint8_t _walling_size_factor = 2;

	// width/height of the walling
	uint16_t _walling_width;
	uint16_t _walling_height;

	// a distance after which shoot has no effect
	float _shoot_distace;

	// the map that includes the walling, etc
	Map _map;

	// array of players
	Player _players[_max_player];

	// id of the current player, used since we allows switching between players
	uint8_t _curr_player_id;

	// the GPU structure with all the needed elements to draw the world
	Gpu _gpu;

	// constant to convert from radians to degrees
	static constexpr float _rd = 180 / 3.14159265358979323846264338327950288f;
};

