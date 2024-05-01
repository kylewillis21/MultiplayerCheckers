#include "lib/include/asio.hpp"
#include "lib/include/asio/ts/buffer.hpp"
#include "lib/include/asio/ts/internet.hpp"
#include <iostream>
#include "game.h"
#include "piece.h"

using asio::ip::tcp;

void waitForClient(asio::io_context &io_context, tcp::acceptor &accpetor);

int main(int argc, char* argv[]) {
    try{
        asio::io_context io_context;

        // Need to create an acceptor to listen for incoming connections
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

        std::cout << "Server started. Listening for incoming connections..." << std::endl;

        tcp::socket socket(io_context);
        acceptor.accept(socket);
        
        // Game done
        socket.close();
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}

std::string getClientMessage(tcp::socket &socket){
    try {
        while(true) {
            // Read message from client
            asio::streambuf receiveBuffer;
            asio::read_until(socket, receiveBuffer, '\n');
            std::string message(asio::buffer_cast<const char*>(receiveBuffer.data()), receiveBuffer.size());
            
            // Send acknowledgment back to client
            asio::write(socket, asio::buffer("ACK\n"));
            return message;
        }
    } catch(std::exception &e) {
        std::cerr << "Exception in getClientMessage: " << e.what() << std::endl;
    }


    
}