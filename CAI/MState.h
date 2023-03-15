#pragma once
#include "Mat.h"

struct mstates
{
	short collision_state = In_air;
	short looking_state = lookingright;
	short attack = non_attack;
	short jump = non_jump;
	short moving_state = non_moving;
	short mood = neutral;
};

