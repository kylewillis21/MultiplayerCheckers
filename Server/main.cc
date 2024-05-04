#include "../lib/include/asio.hpp"
#include <iostream>
#include "game.h"
#include "piece.h"

using asio::ip::tcp;

// Function prototypes
std::string getClientMessage(tcp::socket &socket);
void sendClientMessage(tcp::socket &socket, std::string message);

int main(int argc, char* argv[]) {
    try{
        asio::io_context io_context;

        // Need to create an acceptor to listen for incoming connections
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 12345));

        std::cout << "Server started. Listening for incoming connections..." << std::endl;

        tcp::socket socket(io_context);
        acceptor.accept(socket);
        ///////////////////////////////////////////////////////////////////////////
        piece red("red");
        piece black("black");
        piece blackKing("black");
        blackKing.makeKing();
        piece redKing("red");
        redKing.makeKing();

        game newGame(&red, &black, &blackKing, &redKing);
        std::string target = "";
        std::string destination = "";
        std::string boardString = "";

        while(!newGame.checkWin()){
            if(newGame.getTurnNum()%2==0){  // This decides whether it is the server or clients turn
                // Servers turn
                std::cout << newGame;
                std::cout << "It is " << newGame.getTurn() << " turn" << std::endl;
                do {
                    std::cout << "What piece would you like to move: ";
                    std::cin >> target;
                    std::cout << "Where would you like to move " << target << ": ";
                    std::cin >> destination;
                } while(!newGame.makeMove(target, destination));
                newGame.incrementTurnNum();
                sendClientMessage(socket, newGame.gameToString());
            }
            else{
                // Clients turn
                boardString = "";
                std::cout << newGame;
                std::cout << "It is " << newGame.getTurn() << " turn" << std::endl;
                std::cout << "Waiting on their move..." << std::endl;
                do{
                    boardString = getClientMessage(socket);
                } while(boardString == ""); // Keeps them waiting in the loop until they're sent the board string
                newGame.stringToGame(boardString);
                std::cout << newGame;
            } 
        }
        
        // Game done
        socket.close();
        std::cout << "Connection closed" << std::endl;
    } catch (std::exception &e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}

std::string getClientMessage(tcp::socket &socket){
    try {
        // Read message from client
        asio::streambuf receiveBuffer;
        asio::read_until(socket, receiveBuffer, '\n');
        std::string message(asio::buffer_cast<const char*>(receiveBuffer.data()), receiveBuffer.size());   
        return message;
    } catch(std::exception &e) {
        std::cerr << "Exception in getClientMessage: " << e.what() << std::endl;
        throw;
    }
    return "Error";
}

void sendClientMessage(tcp::socket &socket, std::string message){
    try {
        // Write message to client
        asio::write(socket, asio::buffer(message + "\n"));
    } catch(std::exception &e) {
        std::cerr << "Exception in sendClientMessage: " << e.what() << std::endl;
        throw;
    }
}