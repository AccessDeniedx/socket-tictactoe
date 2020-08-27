#include"gamefunc.h"

void checkwin(char board[3][3])
{
	if(iswin(board)==1)
		printf("游戏结束，恭喜，你赢啦！\n");
	else if(iswin(board)==2)
		printf("游戏结束，很遗憾，你输了！\n");
	else if(iswin(board)==3)
		printf("没有可以落子的地方啦！游戏结束!\n");
}

int main(int argc,char *argv[])
{
	if(argc!=3){
		printf("Usage:%s [ip][port]\n",argv[0]);
		return 1;
	}
	
	int sock;
	struct sockaddr_in serv_addr;
	socklen_t serv_addr_len = sizeof(serv_addr);
	
	sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock ==-1){
		printf("sock() error!");
		return 2;
	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	location loc;
	
	//init(board);
	while(1)
	{
		printmenu();
		char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
		int choice;
		scanf("%d",&choice);
		
		if(choice == 1)
		{
			if(connect(sock,(struct sockaddr*)&serv_addr,serv_addr_len)==-1)
			{	printf("connect() error!\n");	return 3;	}
			printf("游戏开始！你先走！\n说明：你是X，对方是O。\n");
			print(board);
			while(1)
			{
				location loc;
				
				clientmove(board,&loc);
				write(sock,&loc,sizeof(loc));
				print(board);
				
				if(iswin(board))//!=0
				{
					checkwin(board);
					break;
				}
				//sleep(1);
				printf("等待对方落子...\n");
				
				location locp;
				read(sock,&locp,sizeof(locp));
				board[locp.x-1][locp.y-1] = 'O';
				print(board);
				if(iswin(board))//!=0
				{
					checkwin(board);
					break;
				}
				
				
			}
		}
		else if(choice == 2)
		{
			printf("您已退出游戏！\n");
			break;
		}
		else
		{
			printf("输入有误！\n");
			continue;
		}		
	}
	close(sock);
	return 0;
}












