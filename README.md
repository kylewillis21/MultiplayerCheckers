# MultiplayerCheckers
This program is designed to allow two different players play a game of Checkers through an established TCP connection. The bulk of the program is ran through the server side allowing for the client side to do very little to make the program work.

The goal of this project was to be able to learn about TCP/IP protocols and finding a way to implement them in a project.

- Author: Kyle Willis
- LinkedIn: [Kyle Willis](https://www.linkedin.com/in/kyle-willis21/)
- Twitter: [@KyleWillis21](https://twitter.com/KyleWillis21)

## How to Run
Attached in the Server folder and the Client folder there are two different programs. They will compile seperately using the Makefile provided in each of the folders. The following commands will need to be used in a Linux terminal.

1. Clone the GitHub repository.
   ```bash
   git clone https://github.com/kylewillis21/MultiplayerCheckers.git
   ```
2. Navigate into the server folder
3. Run the Makefile
   ```bash
   make
   ```
4. Repeat step 3 inside of the client folder
5. Inside each of the folders there will be a program named main. Run them using
   ```bash
   ./main
   ```

## Helpful Resources
