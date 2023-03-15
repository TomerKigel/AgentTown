#include "Yeti.h"
#include "Factory.h"

Yeti::Yeti(double tspd, AABB range, double hp, double ad, double spd, std::shared_ptr<sf::RenderWindow> window, std::shared_ptr<sf::Texture> txt) : Monster(range, hp, ad, spd, window, txt)
{
	attTimer.SetTimerMaxAsSeconds(1.5);
	ph.setTopSpeed(tspd);
}

void Yeti::Controls()
{
	if (cd.IsTimeUp()) {
		int g = 0;
		if (focus == nullptr) {
			if (disfedge.GetX() > 120 && disfedge.GetY() > 120) {
				g = rand() % 19;
				if (g > 11 && jcd.IsTimeUp())
				{
					jcd.resetTimer();
					Accelerate(0, -10);
				}
				if (g > 5 && g < 12) {
					if (mnstrstate.looking_state == lookingright) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingleft;
					}
					Accelerate(-3, 0);
				}
				if (g < 6) {
					if (mnstrstate.looking_state == lookingleft) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingright;
					}
					Accelerate(3, 0);
				}
			}
			else if (disfedge.GetX() < 120)
			{
				g = rand() % 12;
				if (g % 2 == 0 && g < 6)
					Accelerate(3, 0);
			}
			else
			{
				g = rand() % 12;
				if (g % 2 != 0 && g < 6)
					Accelerate(-3, 0);
			}
		}
		else
		{
			g = rand() % 19;
			if (focus->getCenter()->GetX() < space.getCenter()->GetX())
			{
				if (g < 17) {
					if (mnstrstate.looking_state == lookingright) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingleft;
					}
					Accelerate(-3, 0);
				}
				if (g > 16) {
					if (mnstrstate.looking_state == lookingleft) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingright;
					}
					Accelerate(3, 0);
				}
			}
			else
			{
				if (g < 17) {
					if (mnstrstate.looking_state == lookingleft) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingright;
					}
					Accelerate(3, 0);
				}
				if (g > 16) {
					if (mnstrstate.looking_state == lookingright) {
						mdisp->FlipHorizontali();
						mnstrstate.looking_state = lookingleft;
					}
					Accelerate(-3, 0);
				}
			}
			if (focus->getCenter()->GetY() < space.getCenter()->GetY() && jcd.IsTimeUp())
			{
				jcd.resetTimer();
				Accelerate(0, -10);
			}
			if (focus->getCenter()->GetX() - space.getCenter()->GetX() < 30 && focus->getCenter()->GetX() - space.getCenter()->GetX() > -30)
			{
				Attack();
			}
		}
		cd.resetTimer();
	}
}

void Yeti::intersection(Object* obj)
{
	switch (obj->reType())
	{
	case skill:
	{
		Skill* p = dynamic_cast<Skill*>(obj);
		if (p->returnowner()->reType() == ply && invulnerable.IsTimeUp())
		{
			std::shared_ptr<Player> tpl = std::dynamic_pointer_cast<Player>(p->returnowner());
			PushBack(tpl->reState().looking_state);
			tpl->IncStamina(20);
			setFocus(tpl->getAABB());
			DecHealth(30);
			mdisp->changeColor(true);
			invulnerable.resetTimer();
			if (!isLiving()) {
				destroy();
				//short g = rand() % 6;
				if (tpl->ps.moving_state == dashing_left || tpl->ps.moving_state == dashing_right) {
					AABB s(space.GetBR().GetX() - 50, space.GetBR().GetY() - 50, space.GetBR().GetX(), space.GetBR().GetY());
					const char* name = "HealthPotion.png";
					Factory::SetUpItm::SetUpItem(s, mdisp->rewin(), name);
					Factory::CreateItem();
				}
			}
		}
		break;
	}
	case ply:
		//setFocus(dynamic_cast<Player*>(obj)->getAABB());
		//MakeAggresive();
		break;
	case sttc:
		StaticObject* sptr = dynamic_cast<StaticObject*>(obj);
		auto direction = Lastspace.WIRTTO(*sptr->getAABB());
		double overlap = getAABB()->Overlap(*sptr->getAABB(), direction);
		PhysicsIntersection(overlap, direction);
		calcDisFromEdge(sptr);
		break;
	}
}

short Yeti::reMType()
{
	return yeti;
}

void Yeti::Attack()
{
	if (attTimer.IsTimeUp()) {
		Point p = *space.getCenter().get();
		Factory::SetUpsk::SetUpSkill(p, mdisp->rewin(), "swash.png", shared_from_this(), mnstrstate.looking_state);
		Factory::CreateSkill();
		attTimer.resetTimer();
	}
}
