// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <SDL_net.h>
#include <SDL_stdinc.h>

#include "netwrok_messages.h"
class Vector2D;

class Networking {
public:
	Networking();
	virtual ~Networking();

	bool init(char *host, Uint16 port);
	bool disconnect();
	void update();

	Uint8 client_id() {
		return _clientId;
	}

	bool is_master() {
		return _clientId == _masterId;
	}

	void send_state(Uint8 id, const Vector2D& pos, const Vector2D& fovPointA, const Vector2D& fovPointB, float rot);
	void send_my_info(const Vector2D& pos, const Vector2D& fovPointA, const Vector2D& fovPointB, float rot,
			Uint8 state);
	
	void send_shoot();
	void send_dead(Uint8 id);
	void send_restart();
	void send_countdown_info(bool active, int count_val);
	void send_health_update(Uint8 id, float health);

private:

	void handle_new_client(Uint8 id);
	void handle_disconnet(Uint8 id);
	void handle_player_state(const PlayerStateMsg &m);
	void handle_player_info(const PlayerInfoMsg &m);
	void handle_shoot(const ShootMsg &m);
	void handle_dead(const DeathMsg &m);
	void handle_restart();
	void handle_countdown(const CountdownMsg& m);
	void handle_health_update(const HealthUpdateMsg& m);

	UDPsocket _sock;
	SDLNet_SocketSet _socketSet;
	UDPpacket *_p;
	IPaddress _srvadd;
	Uint8 _clientId;
	Uint8 _masterId;
};

