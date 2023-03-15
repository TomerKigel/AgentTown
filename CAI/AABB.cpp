#include "AABB.h"
#include "Movable.h"

#define PI 3.14159265

AABB::AABB(double tlx, double tly, double brx, double bry)
{
	TL(tlx, tly);
	BR(brx, bry);
}


AABB::AABB(Point tl, Point br)
{
	TL = tl;
	BR = br;

}

std::shared_ptr<Point> AABB::getCenter()
{
	std::shared_ptr<Point> Center = std::make_shared<Point>();
	Center->SetX((TL.GetX() + BR.GetX()) / 2);
	Center->SetY((TL.GetY() + BR.GetY()) / 2);
	return Center;
}

int AABB::GetLen()
{
	return static_cast<int>(BR.GetX() - TL.GetX());
}


int AABB::GetWid()
{
	return static_cast<int>(BR.GetY() - TL.GetY());
}

Point AABB::GetTL()
{
	return TL;
}

Point AABB::GetBR()
{
	return BR;
}

bool AABB::operator==(const AABB& range)
{
	if (!(BR.GetX() < range.TL.GetX() - 1 || range.BR.GetX() + 1 < TL.GetX()) &&
		!(BR.GetY() < range.TL.GetY() - 1 || range.BR.GetY() + 1 < TL.GetY()))
	{
		return true;
	}
	return false;
}

bool AABB::operator<(AABB& range)
{
	return range.GetTL().GetX() > GetTL().GetX();
}

bool AABB::cmpPtN(AABB* range, AABB* secRange)
{
	return (range->GetTL().GetX() < secRange->GetTL().GetX());
}

int AABB::operator-=(AABB& range)
{
	if ((range.GetTL().GetX() - BR.GetX() == 1 || TL.GetX() - range.GetBR().GetX() == 1) && (TL.GetY() <= range.BR.GetY() && BR.GetY() >= range.TL.GetY()))
	{
		if ((range.GetTL().GetY() - BR.GetY() == 1 || TL.GetY() - range.GetBR().GetY() == 1) && (TL.GetX() <= range.BR.GetX() && BR.GetX() >= range.TL.GetX()))
			return 3;
		return 1;
	}
	if ((range.GetTL().GetY() - BR.GetY() == 1 || TL.GetY() - range.GetBR().GetY() == 1) && (TL.GetX() <= range.BR.GetX() && BR.GetX() >= range.TL.GetX()))
	{
		return 2;
	}
	if (*getAABB() == range)
	{
		return 4;
	}
	return false;
}

bool AABB::isContaining(Point pnt) const
{
	if ((pnt.GetX() >= TL.GetX() && pnt.GetX() <= BR.GetX()) &&
		(pnt.GetY() >= TL.GetY() && pnt.GetY() <= BR.GetY()))
	{
		return true;
	}
	return false;
}

void AABB::operator=(AABB& origin)
{
	TL = origin.TL;
	BR = origin.BR;
}

void AABB::operator()(double top_left_x, double top_left_y, double bottom_right_x, double bottom_right_y)
{
	TL(top_left_x, top_left_y);
	BR(bottom_right_x, bottom_right_y);
}

void AABB::operator()(Point top_left, Point bottom_right)
{
	TL(top_left.GetX(), top_left.GetY());
	BR(bottom_right.GetX(), bottom_right.GetY());
}

void AABB::operator*=(double f)
{
	Point ttl = TL;
	TL.SetX(TL.GetX() - ((BR.GetX() - TL.GetX()) / (f / 2)));
	TL.SetY(TL.GetY() - ((BR.GetY() - TL.GetY()) / (f / 2)));
	BR.SetX(BR.GetX() + ((BR.GetX() - ttl.GetX()) / (f / 2)));
	BR.SetY(BR.GetY() + ((BR.GetY() - ttl.GetY()) / (f / 2)));
}


void AABB::SetTL(double x, double y)
{
	TL.SetX(x);
	TL.SetY(y);
}
void AABB::SetBR(double x, double y)
{
	BR.SetX(x);
	BR.SetY(y);
}

AABB* AABB::getAABB()
{
	return this;
}
short AABB::WIRTTO(AABB other)
{
	int directions_count[4] = {0};
	auto last_x = this->getAABB()->getCenter()->GetX();
	auto last_y = this->getAABB()->getCenter()->GetY();

	auto other_right_x = other.GetBR().GetX();
	auto other_bottom_y = other.GetBR().GetY();
	auto other_left_x = other.GetTL().GetX();
	auto other_top_y = other.GetTL().GetY();

	auto x_relative_to_right = last_x - other_right_x;
	auto x_relative_to_left = last_x - other_left_x;
	auto y_relative_to_top = last_y - other_top_y;
	auto y_relative_to_bottom = last_y - other_bottom_y;

	if (x_relative_to_right > 0)
		directions_count[right-1] += 2;
	else
		directions_count[left - 1] += 2;
	if (x_relative_to_left > 0)
		directions_count[right - 1] += 2;
	else
		directions_count[left - 1] += 2;
	if(y_relative_to_top < 0)
		directions_count[top - 1] += 2;
	else
		directions_count[bottom - 1] += 2;
	if (y_relative_to_bottom < 0)
		directions_count[top - 1] += 2;
	else
		directions_count[bottom - 1] += 2;

	short selected_direction = top - 1;
	int max_count = 0;
	for (size_t i = 0; i < 4; i++)
	{
		if (directions_count[i] > max_count) {
			max_count = directions_count[i];
			selected_direction = i + 1;
		}
	}
	return selected_direction;
}


double AABB::Overlap(AABB t, short direction)
{
	double overlap = 0;
	switch (direction)
	{
	case top:
		overlap = BR.GetY() - t.TL.GetY();
		return overlap * (overlap > 0);
	case bottom:
		overlap = t.BR.GetY() - TL.GetY();
		return overlap * (overlap > 0);
	case left:
		overlap = BR.GetX() - t.TL.GetX();
		return overlap * (overlap > 0);
	case right:
		overlap = t.BR.GetX() - TL.GetX();
		return overlap * (overlap > 0);
	default:
		return 0;
	}
}

double AABB::GetLeft()
{
	return TL.GetX();
}

double AABB::GetRight()
{
	return BR.GetX();
}

double AABB::GetTop()
{
	return TL.GetY();
}

double AABB::GetBottom()
{
	return BR.GetY();
}