#include "rockpaperscissors.h"
int moveIsValid(int);
using namespace std;
int main (int argc, char *argv[]){
	int orig_sock;// original socket in client
	int	 portno,soc;
	struct sockaddr_in serv_adr; // server address
	struct hostent *host;
	string PlayerName;
	int c_won=0,u_won=0,tie=0;
	int p1,p2,rounds;
	int bytes_recvd, bytes_sent;
	char  comp_choice[2];
	char noofrounds[10],msg[40];
	
	if (argc != 3){
		cout<<"usage:"<<argv[0]<<"server"<<endl;
		return 1;
	}
	host = gethostbyname(argv[1]);// obtaining host server info
	if (host ==(struct hostent*) NULL) {
		perror("gethostbyname");
		return 2;
	}
	
	// Creating a  stream socket using TCP
	 soc=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(soc == -1)
	{	
		perror("socket could not be created!");
		return 3;
	}
	
	memset(&serv_adr, 0, sizeof( serv_adr));
	serv_adr.sin_family = AF_INET;// IPv4 address family
	memcpy(&serv_adr.sin_addr, host->h_addr, host->h_length);
	portno = atoi(argv[2]);
	serv_adr.sin_port = htons(portno);
	
	// creation of socket
	if ((orig_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		perror("creation error");
		return 4;
	}
	
	// connecting to server
	if (connect( orig_sock,(struct sockaddr *)&serv_adr,sizeof(serv_adr)) < 0) { 
		perror("connection error");
		return 5;
	}
	cout << "Enter Your Name:"<<endl;
	cin >> PlayerName;
	cout<<"enter number of rounds u want to play"<<endl;
	cin>>rounds;
	sprintf(noofrounds, "%d", rounds);
	bytes_sent = send(orig_sock, &noofrounds, sizeof(noofrounds)+1, 0);
    for(int i=1;i<=rounds;i++)
	 {
		cout <<"----- "<<PlayerName << "'s turn-----" << endl;
		cout << "Enter your choice-- 0 for rock--1 for paper--2 for scissors" << endl;
		cin >> p1;
		int flag=moveIsValid(p1);
		   while(flag != 1){
			 cout <<"invalid input,enter again"<< endl;
			 cin >> p1;
			 flag=moveIsValid(p1);
		    }
	    bytes_sent = send(orig_sock, "go", sizeof("go")+1, 0);
	        if(bytes_sent == -1)
			{
				perror("message failed to send");
				return 6;
			}
	
	    bytes_recvd = recv(orig_sock, &comp_choice, sizeof(comp_choice), 0);
		    if(bytes_recvd == -1)
			{
				perror("computer data received error");
				return 6;
			}
		int p2=atoi(comp_choice);
			if(p1 == 0){      /*the following is for determining the winner*/
	           cout<<"YOUR CHOICE: Rock"<<endl;
			   }
            else if(p1 == 1){
	            cout<<"YOUR CHOICE: Paper"<<endl;
			} 
			else{
			    cout<<"YOUR CHOICE: Scissors"<<endl;
			}
            if(p2 == 0){
	            cout<<"COMPUTER CHOICE: Rock"<<endl;
	        }
            else if(p2 == 1){
	            cout<<"COMPUTER CHOICE: Paper"<<endl;
	         }
            else{
	            cout<<"COMPUTER CHOICE: Scissors"<<endl;
		     }
            if (p1 == p2){
		         tie++;
	             cout<<"Round "<< i<< " is a tie\n"<<endl;;
	        }
            else if(p1 == 0 && p2 == 2){
			   u_won++;
	           cout<<"Round"<< i<<"--- Rock beats Scissors: YOU WON!!!\n"<<endl;
	        }
            else if(p1 == 0 && p2 == 1){
			   c_won++;
	           cout<<"Round"<< i <<"---Paper beats Rock: COMPUTER WON!!!\n"<<endl;
	        }
            else if(p1 == 1 && p2 == 0){
			  u_won++;
	          cout<<"Round "<< i <<"---Paper beats Rock: YOU WON!\n"<<endl;
	        }
            else if(p1 == 1 && p2 == 2){
			 c_won++;
	         cout<<"Round"<< i<<"---Scissors beats Paper: COMPUTER WON!\n"<<endl;
	        }
            else if(p1 == 2 && p2 == 1){
			u_won++;
	        cout<<"Round "<< i<<"---Scissors beats Paper: YOU WON!\n"<<endl;
	        }
            else if(p1 == 2 && p2 == 0){
		    c_won++;
	        cout<<"Round"<< i<<"---Rock beats Scissors: COMPUTER WON!\n"<<endl;
	        }
		     signal(SIGPIPE, SIG_IGN);
 	
	 }
			  
			 if(c_won>u_won){
				 cout<<"Computer won = "<<c_won<<"\nyou won = "<<u_won<<"\nTies = "<<tie<<"\nFINAL RESULT----COMPUTER WON"<<endl;
			 }
			 else if(u_won>c_won){
				   cout<<"Computer won = "<<c_won<<"\nyou won = "<<u_won<<"\nTies = "<<tie<<"\nFINAL RESULT----YOU WON"<<endl;
			 }
			 else if(u_won==c_won){
				   cout<<"Computer won = "<<c_won<<"\nyou won = "<<u_won<<"\nTies = "<<tie<<"\nFINAL RESULT----TIE"<<endl;
			 }
			 
	return 0;
	}
int moveIsValid (int a )
{
  if(a>=0 && a<3){
	  return true;
  }
  else{
	  return false;
  }
}








