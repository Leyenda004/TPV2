// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
struct Transform;
struct Image;
struct StarMotion;
struct Points;
struct ImageWithFrames;
struct Milagrosa;

#define _CMPS_LIST_ \
	Transform, \
	Image, \
	ImageWithFrames, \
	Milagrosa, \
	StarMotion, \
	Points

// Groups list - must have at least one element
//
#define _GRPS_LIST_ \
	STARS, \
	FOOD, \
	GHOSTS

// Handlers list - must have at least one element
//
#define _HDLRS_LIST_ \
    PACMAN

// Systems list - must have at least one element
//
class StarsSystem;
class RenderSystem;
class PacManSystem;
class GameCtrlSystem;
class CollisionsSystem;
class FoodSystem;
class GhostSystem;
class ImmunitySystem;

#define _SYS_LIST_ \
    StarsSystem, \
	RenderSystem, \
	PacManSystem, \
	GameCtrlSystem, \
	CollisionsSystem, \
	FoodSystem, \
	GhostSystem, \
	ImmunitySystem

