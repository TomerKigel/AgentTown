#include "Physics.h"


Physics::Physics(double topspeed, double topacc, double startxspeed, double startyspeed, double startxacc, double startyacc)
{
	stats.topspeed = topspeed;
	stats.topacc = topacc;
	stats.xspeed = startxspeed;
	stats.yspeed = startyspeed;
	stats.accx = startxacc;
	stats.accy = startyacc;
	phyTimer.SetTimerMaxAsSeconds(1);
	unEffected = false;
}

void Physics::GravityOn()
{
	GForce = 0.4;
}
void Physics::GravityOff()
{
	GForce = 0;
}
void Physics::GravityUpward()
{
	GForce = -0.4;
}
void Physics::GravityFlip()
{
	GForce *= -1;
}

void Physics::UnEffectedByGravity()
{
	unEffected = true;
}

void Physics::EffectedByGravity()
{
	unEffected = false;
}

void Physics::AccelerateX(double i)
{
	if (i < 0) {
		stats.accx += i;
		if (-stats.topacc > stats.accx)
			stats.accx = -stats.topacc;

	}
	else
	{
		stats.accx += i;
		if (stats.topacc < stats.accx)
			stats.accx = stats.topacc;

	}
}
void Physics::AccelerateY(double i)
{
	if (i < 0) {
		stats.accy += i;
		if (-stats.topacc > stats.accy)
			stats.accy = -stats.topacc;

	}
	else
	{
		stats.accy += i;
		if (stats.topacc < stats.accy)
			stats.accy = stats.topacc;
	}
}
PhysicsStats  Physics::calcSpeed()
{
	if (stats.accx > 0 && stats.topspeed > stats.xspeed)
		stats.xspeed += stats.accx;
	else if (stats.accx < 0 && -stats.topspeed < stats.xspeed)
		stats.xspeed += stats.accx;

	if (stats.accy > 0 && stats.topspeed > stats.yspeed)
		stats.yspeed += stats.accy;
	else if (stats.accy < 0 && -stats.topspeed < stats.yspeed)
		stats.yspeed += stats.accy;

	if (stats.yspeed < E_TopSpeed && !unEffected)
		stats.yspeed += GForce;


	if (stats.yspeed  < GForce && stats.yspeed > -GForce)
		stats.yspeed = 0;
	if (stats.xspeed  < GForce && stats.xspeed > -GForce)
		stats.xspeed = 0;

	stats.accx = 0;
	stats.accy = 0;

	stats.xspeed *= 0.95;

	return stats;
}

void Physics::intersection(bool isx, bool isy, short dir)
{
	if (isx)
	{
		if (dir == left && stats.xspeed > 0)
			stats.xspeed = 0;
		else if (dir == right && stats.xspeed < 0)
			stats.xspeed = 0;
	}
	if (isy)
	{
		if (dir == top && stats.yspeed > 0)
			stats.yspeed = 0;
		if (dir == bottom && stats.yspeed < 0)
			stats.yspeed = 0;
	}
}

void Physics::setObjectsParameters(PhysicsStats sts)
{
	stats = sts;
}

void Physics::setTopSpeed(double topspeed)
{
	stats.topspeed = topspeed;
}

void Physics::setTopAcc(double topacc)
{
	stats.topacc = topacc;
}

Point Physics::reSpeed()
{
	return Point(stats.xspeed, stats.yspeed);
}
Point Physics::reAcc()
{
	return Point(stats.accx, stats.accy);
}