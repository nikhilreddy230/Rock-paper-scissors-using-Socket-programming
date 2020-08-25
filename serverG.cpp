#include "rockpaperscissors.h"
int main(int argc, char **argv){
 	int socket_game;
    char msg[5],comp_choice[5], noofrounds[5];
    int bytes_recvd, bytes_sent;
    if(argc > 1)
    {    
		socket_game = atoi(argv[1]);
	    bytes_recvd =  recv(socket_game, &noofrounds, sizeof(noofrounds), 0);
       int rounds=atoi(noofrounds);
		for(int i=0;i<=rounds;i++){
			bytes_recvd =  recv(socket_game, &msg, sizeof(msg), 0);
				if(bytes_recvd == -1)
					{
						perror("user data received error");
						exit(1);
					}
					
        srand(time(NULL));
	    int server_move = rand() % 3;
		sprintf(comp_choice, "%d", server_move);
		bytes_sent = send(socket_game, &comp_choice, sizeof(comp_choice), 0);
            if(bytes_sent==-1){
				 perror("failed to send message");
				 exit(2);
			}
			 
         signal(SIGPIPE, SIG_IGN);
		}
		
	  close(socket_game);
    return 0;
}
}





