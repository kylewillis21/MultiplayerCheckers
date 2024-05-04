#include <iostream>
#include "game.h"
#include "piece.h"

#include "../lib/include/asio.hpp"

using asio::ip::tcp;

// Function prototypes
std::string getServerMessage(tcp::socket &socket);
void sendServerMessage(tcp::socket &socket, std::string message);

int main() {
    try {
        // Connecting to server
        asio::io_context io_context;
        tcp::socket socket(io_context);
        tcp::resolver resolver(io_context);

        asio::connect(socket, resolver.resolve("localhost", "12345"));
        //////////////////////////////////////////////////////////////
        piece red("red");
        piece redKing("red");
        redKing.makeKing();
        piece black("black");
        piece blackKing("black");
        blackKing.makeKing();

        std::string boardString;
        game newGame(&red,&black,&blackKing,&redKing);
        std::string target = "";
        std::string destination = "";

        while(!newGame.checkWin()){
            if(newGame.getTurnNum()%2==1){  // This decides whether it is the server or clients turn
                // Clients turn
                std::cout << "It is " << newGame.getTurn() << " turn\n";
                do {
                    std::cout << "What piece would you like to move: ";
                    std::cin >> target;
                    std::cout << "Where would you like to move " << target << ": ";
                    std::cin >> destination;
                } while(!newGame.makeMove(target, destination));
                newGame.incrementTurnNum();
                sendServerMessage(socket, newGame.gameToString());
            }
            else{
                // Servers turn
                boardString = "";
                std::cout << newGame;
                std::cout << "It is " << newGame.getTurn() << " turn" << std::endl;
                std::cout << "Waiting on their move..." << std::endl;
                do{
                    boardString = getServerMessage(socket);
                } while(boardString == ""); // This will keep them in this loop until the board is sent over
                newGame.stringToGame(boardString);
                std::cout << newGame;
            } 
        }

        ///////////////////////////////////////////////////////////////
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
        throw;
    }
    return "Error";
}

void sendServerMessage(tcp::socket &socket, std::string message){
    try{
        // Write message to server
        asio::write(socket, asio::buffer(message + "\n"));
    } catch(std::exception &e){
        std::cerr << "Exception in sendServerMessage: " << e.what() << std::endl;
        throw;
    }
}
