// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

// Components list - must have at least one element
//
struct Transform;
struct Image;
struct Points;
struct ImageWithFrames;
struct Milagrosa;
struct Health;

#define _CMPS_LIST_ \
	Transform, \
	Image, \
	ImageWithFrames, \
	Milagrosa, \
	Points, \
	Health

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
class RenderSystem;
class PacManSystem;
class GameCtrlSystem;
class CollisionsSystem;
class FoodSystem;
class GhostSystem;
class ImmunitySystem;

#define _SYS_LIST_ \
	RenderSystem, \
	PacManSystem, \
	GameCtrlSystem, \
	CollisionsSystem, \
	FoodSystem, \
	GhostSystem, \
	ImmunitySystem

