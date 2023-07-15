#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CAIUnitTest
{
	TEST_CLASS(classtest)
	{
	public:

		TEST_METHOD(Message__Creation)
		{
			message::Message msg;
			Assert::AreEqual(true, msg.direction == msg.In);
			Assert::AreEqual(true, msg.body.size() == 0);
			Assert::AreEqual(true, msg.header.body_size == 0);
			Assert::AreEqual(true, msg.header.connection_id == 0);
			Assert::AreEqual(true, msg.header.type.size() == 0);
		}

		TEST_METHOD(Message__to_string)
		{
			message::Message msg;
			/*message::Message msg;
			Message_Generator message_generator;
			message::Parsed_Message pmsg;
			Queue_Manager<message::Message> queue_manager;*/
			//Assert::AreEqual(x, 2);
		}

		TEST_METHOD(x)
		{
			/*message::Message msg;
			Message_Generator message_generator;
			message::Parsed_Message pmsg;
			Queue_Manager<message::Message> queue_manager;*/
			//Assert::AreEqual(x, 2);
		}

		TEST_METHOD(y)
		{
			/*message::Message msg;
			Message_Generator message_generator;
			message::Parsed_Message pmsg;
			Queue_Manager<message::Message> queue_manager;*/
			//Assert::AreEqual(x, 2);
		}
	};
}
