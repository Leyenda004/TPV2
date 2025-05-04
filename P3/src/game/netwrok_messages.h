// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL_stdinc.h>
#include "../sdlutils/SDLNetUtils.h"

enum MsgType : Uint8 {
	_NONE = 0, //
	_CONNECTION_REQUEST, //
	_CONNECTION_ACCEPTED, //
	_CONNECTION_REJECTED, //
	_DISCONNECTED,
	_NEW_CLIENT_CONNECTED, //
	_PLAYER_STATE, // sent frequently to boradcast the state
	_PLAYER_INFO, // sent only the first time the player connects
	_PLAYER_MOVED,
	_SHOOT, //
	_DEAD, //
	_RESTART
};

struct Msg {
	Uint8 _type;

	_IMPL_SERIALIAZION_(_type)
};

struct MsgWithId: Msg {
	Uint8 _client_id;

	_IMPL_SERIALIAZION_WITH_BASE_(Msg,_client_id)
};

struct MsgWithMasterId: MsgWithId {
	Uint8 _master_id;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId,_master_id)
};

struct PlayerStateMsg: MsgWithId {

	Uint8 _player_id;
	float x;
	float y;
	float rot;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, _player_id, x,y, rot)

};

struct PlayerInfoMsg: MsgWithId {

	float x;
	float y;
	float fvPAx;
	float fvPAy;
	float fvPBx;
	float fvPBy;
	float rot;
	Uint8 state;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, x,y, fvPAx, fvPAy, fvPBx, fvPBy,rot,state)

};

struct ShootMsg: MsgWithId {

	Uint8 _gunner_id;

	_IMPL_SERIALIAZION_WITH_BASE_(MsgWithId, _gunner_id)

};
