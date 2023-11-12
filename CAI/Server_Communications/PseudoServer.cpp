//#include "PseudoServer.h"
//
//
//using boost::asio::ip::tcp;
//
//using std::cin;
//using std::cout;
//using std::cerr;
//using std::endl;
//using std::string;
//
//
//
//PseudoServer::PseudoServer(string host_, short port_) : host_(host_), port_(port_), io_service_(),
//socket_(io_service_) {
//}
//
//PseudoServer::~PseudoServer() {
//	close();
//}
//
//bool PseudoServer::connect() {
//	std::cout << "Starting connect to "
//		<< host_ << ":" << port_ << std::endl;
//	try {
//		tcp::endpoint endpoint(boost::asio::ip::address::from_string(host_), port_); // the server endpoint
//		boost::system::error_code error;
//		socket_.connect(endpoint, error);
//		if (error)
//			throw boost::system::system_error(error);
//	}
//	catch (std::exception& e) {
//		std::cerr << "Could not connect to server" << std::endl;
//		return false;
//	}
//	return true;
//}
//
//bool PseudoServer::getBytes(char bytes[], unsigned int bytesToRead) {
//	size_t tmp = 0;
//	boost::system::error_code error;
//	try {
//		while (!error && bytesToRead > tmp) {
//			tmp += socket_.read_some(boost::asio::buffer(bytes + tmp, bytesToRead - tmp), error);
//		}
//		if (error)
//			throw boost::system::system_error(error);
//	}
//	catch (std::exception& e) {
//		std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
//		return false;
//	}
//	return true;
//}
//
//bool PseudoServer::sendBytes(const char bytes[], int bytesToWrite) {
//	int tmp = 0;
//	boost::system::error_code error;
//	try {
//		while (!error && bytesToWrite > tmp) {
//			tmp += socket_.write_some(boost::asio::buffer(bytes + tmp, bytesToWrite - tmp), error);
//		}
//		if (error)
//			throw boost::system::system_error(error);
//	}
//	catch (std::exception& e) {
//		std::cerr << "recv failed (Error: " << e.what() << ')' << std::endl;
//		return false;
//	}
//	return true;
//}
//
//bool PseudoServer::getLine(std::string& line) {
//	return getFrameAscii(line, '\n');
//}
//
//bool PseudoServer::sendLine(std::string& line) {
//	return sendFrameAscii(line, '\n');
//}
//
//
//bool PseudoServer::getFrameAscii(std::string& frame, char delimiter) {
//	char ch;
//	// Stop when we encounter the null character.
//	// Notice that the null character is not appended to the frame string.
//	try {
//		do {
//			if (!getBytes(&ch, 1)) {
//				return false;
//			}
//			if (ch != '\0')
//				frame.append(1, ch);
//		} while (delimiter != ch);
//	}
//	catch (std::exception& e) {
//		std::cerr << "recv failed2 (Error: " << e.what() << ')' << std::endl;
//		return false;
//	}
//	return true;
//}
//
//bool PseudoServer::sendFrameAscii(const std::string& frame, char delimiter) {
//	bool result = sendBytes(frame.c_str(), frame.length());
//	if (!result) return false;
//	return sendBytes(&delimiter, 1);
//}
//
//void PseudoServer::close() {
//	try {
//		socket_.close();
//	}
//	catch (...) {
//		std::cout << "closing failed: connection already closed" << std::endl;
//	}
//}
