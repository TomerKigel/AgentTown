#include "agent.h"
#include "GameEngine.h"
#include "Framework.h"
//void send_messages(agent &me, agent &you)
//{
//	unsigned int i = 10000;
//	while (i < 10010) {
//		event_message* pmg = new event_message(i++, me.get_agent_id(), you.get_agent_id());
//		std::shared_ptr<event_message> msg = std::unique_ptr<event_message>(pmg);
//		you.push_message(&*msg);
//		std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100));
//	}
//}

int main()
{
	/*GameEngine game;
	game.GameLoop();*/
	#include <windows.h>
	ShowWindow(GetConsoleWindow(), SW_RESTORE); //SW_HIDE
	Framework fw;
	//while (true);
	//agent me;
	//agent you;
	//std::thread tr(&send_messages, std::ref(me), std::ref(you));
	//std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100));
	//unsigned int i = 0;
	//while (i < 10) {
	//	event_message *pmg = new event_message(i++, me.get_agent_id(), you.get_agent_id());
	//	std::shared_ptr<event_message> msg = std::unique_ptr<event_message>(pmg);
	//	you.push_message(&*msg);
	//	std::this_thread::sleep_for(std::chrono::duration<double, std::milli>(100));
	//}
	//tr.join();
	////MovingTask<double,int> new_task(3.0, 5);
	////int x = new_task.getArgumentAmount();
	////auto y = new_task.getArgument<double>(3);
}

