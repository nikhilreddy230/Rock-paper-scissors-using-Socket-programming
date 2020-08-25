# Rock-paper-scissors-using-Socket-programming
In this project, we implemented a socket rock paper scissors game.The game is played between the player and a server.After serverC executes fork system call the child process will execute another program called serverG.The game starts with player selecting his choice and later server selecting its choice  and also server can handle multiple clients simultaneously.
serverC:- server first create the socket and bind the socket to local address and listen to the socket.Then it will accept the connection from the client and fork a child process to handle the game.
serverG:- This is the server which handles the actual gameplay.It receives the client message and after that it generates random choice and sends it back to the server.
Client:- Client has to choose its choice and after the client receives the choice from the server the winner is decided and displayed.
To compile:
g++ serverC.cpp -o serverC
g++ serverG.cpp -o serverG
g++ client.cpp -o client
To run:open terminal
./serverC 12000
Open another terminal
./client 127.0.0.1 12000
