#include "rockpaperscissors.h"
int main(int argc, char **argv) {
	pid_t child_id;
	//server socket id, client socket id, port number.
	//length of client address
	int socketserver, socketclient, portno;
	socklen_t clientaddress;  
	char child[30];
	struct sockaddr_in server_addr, client_addr; //server address, client address
	if(argc < 2) 
	{
		cout <<"error,didn't enter port" <<endl;
		exit(1);
	}
		//Creating a socket
		socketserver = socket(AF_INET, SOCK_STREAM, 0);
		if(socketserver<0)
		{
			cout <<"Error while opening socket" <<endl;
			exit(2);
		}
		
		//local address structure
		memset(&server_addr, 0, sizeof(server_addr));
		portno = atoi(argv[1]);
		server_addr.sin_family = AF_INET;//  Address Family 
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		server_addr.sin_port = htons(portno);//port number setting using htons function
		
		//binding the  socket created to the local address
		if(bind(socketserver, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		{	
			cout <<"Binding Error" <<endl;
			exit(3);
		}
		
		//listen for socket with 5 max connection requests
		if(listen(socketserver,5) < 0) 
		{
			cout <<"listen error" <<endl;
			exit(4);
		}
		
		
	while(1)
		{
			clientaddress = sizeof(client_addr);
			
			//accept the incoming client connection. 
			socketclient = accept(socketserver, (struct sockaddr *) &client_addr, &clientaddress);
			if(socketclient < 0) 
			{
				cout <<"Error accepting the connection";
				exit(4);
			}
		
			cout <<"New client connection  with client  port " <<inet_ntoa(client_addr.sin_addr) <<ntohs(client_addr.sin_port) <<endl;
			child_id = fork();//child creation
			if(child_id == -1){
				cout <<"parent: couldn't create child, errno = " <<errno <<endl;
				exit(5);	
			}
			else if(child_id == 0){
				sprintf(child, "%d", socketclient);
				child_id = execl("./serverG", "serverG", child,NULL);
				if ( child_id== -1 ) 
					{
					cout <<" parent:  execl failed, errno = " <<errno <<endl;
					exit (6);
					}
				
				close(socketclient);
				return 0;
				}
			else
				close(socketclient);
		}
		return 0;
}
	
