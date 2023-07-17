#include "Message_Dependencies.h"
#include "CppUnitTest.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace CAIUnitTest
{
	TEST_CLASS(message_test)
	{
	public:

		TEST_METHOD(Message__Creation)
		{
			message::Message msg;
			Assert::AreEqual(true, msg.direction == message::Message::message_direction::In);
			Assert::AreEqual(true, msg.body.size() == 0);
			Assert::AreEqual(true, msg.header.body_size == 0);
			Assert::AreEqual(true, msg.header.connection_id == 0);
			Assert::AreEqual(true, msg.header.type.size() == 0);
		}

		TEST_METHOD(Message__operator_rol)
		{
			message::Message msg;
			std::string data = "hello";
			msg << data;
			Assert::AreEqual(true, msg.header.body_size == 5);
		}

		TEST_METHOD(Message__operator_ror)
		{
			message::Message msg;
			std::string g_data = "lets try \n more text";
			msg << g_data;
			std::string msg_data;
			msg >> msg_data;
			Assert::AreEqual(true, msg_data.compare("lets try \n more text") == 0);
		}

		TEST_METHOD(Message__to_string)
		{
			message::Message msg;
			std::string data = "hello";
			msg << data;
			msg.header.type = "new agent";
			msg.header.connection_id = 1;
			Assert::AreEqual(true, to_string(msg) == "[new agent]{hello}");
		}

		TEST_METHOD(Message__get_part_of_message)
		{
			message::Message msg;
			std::string data = "hello";
			msg << data;
			Assert::AreEqual(true, get_part_of_message(msg, "h", "o") == "ell");


			std::string new_data = "\nwelcome";
			msg << data;
			Assert::AreEqual(true, get_part_of_message(msg, "h", "e") == "");


			message::Message n_msg;
			std::string g_data = "lets try \n more text";
			n_msg << g_data;
			Assert::AreEqual(true, get_part_of_message(n_msg, "r", "r") == "y \n mo");

			message::Message u_msg;
			std::string u_data = "from: x to \n";
			u_msg << u_data;
			Assert::AreEqual(true, get_part_of_message(u_msg, "from:", "\n") == " x to ");

			message::Message header_msg;
			header_msg.header.type = "move";
			Assert::AreEqual(true, get_part_of_message(header_msg, "m", "e") == std::nullopt);
		}

		TEST_METHOD(Message__reset)
		{
			message::Message msg;
			std::string g_data = "lets try \n more text";
			msg << g_data;
			msg.header.type = "hello";
			msg.header.connection_id = 12;
			msg.direction == message::Message::message_direction::Out;
			reset(msg);

			Assert::AreEqual(true, msg.direction == message::Message::message_direction::In);
			Assert::AreEqual(true, msg.body.size() == 0);
			Assert::AreEqual(true, msg.header.body_size == 0);
			Assert::AreEqual(true, msg.header.connection_id == 0);
			Assert::AreEqual(true, msg.header.type.size() == 0);
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
