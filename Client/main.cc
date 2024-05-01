#include <iostream>
#include "../lib/include/asio.hpp"

using asio::ip::tcp;

// Function prototypes
std::string getServerMessage(tcp::socket &socket);
void sendServerMessage(tcp::socket &socket, std::string message);

int main() {
    try {
        asio::io_context io_context;
        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);

        asio::connect(socket, resolver.resolve("localhost", "12345"));

        std::string message;
        std::cout << "Write your message: ";
        std::getline(std::cin, message);
        sendServerMessage(socket, message);

        std::cout << "Awaiting message from server..." << std::endl;

        std::cout << getServerMessage(socket) << std::endl;
        
        // Game done
        socket.close();
        std::cout << "Connection closed." << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
}

std::string getServerMessage(tcp::socket &socket){
    try {
        // Read the message from the server
        asio::streambuf receiveBuffer;
        asio::read_until(socket, receiveBuffer, '\n');
        std::string message(asio::buffer_cast<const char*>(receiveBuffer.data()), receiveBuffer.size());
        
        return message;
    } catch(std::exception &e){
        std::cerr << "Exception in getServerMessage: " << e.what() << std::endl;
    }
    return "Error";
}

void sendServerMessage(tcp::socket &socket, std::string message){
    try{
        asio::write(socket, asio::buffer(message + "\n"));
    } catch(std::exception &e){
        std::cerr << "Exception in sendServerMessage: " << e.what() << std::endl;
    }
}
