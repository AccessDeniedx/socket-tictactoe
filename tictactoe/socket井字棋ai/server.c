#include"gamefunc.h"

void checkwin(char board[3][3])
{
	if(iswin(board)==1)
		printf("游戏结束，人类赢！\n");
	else if(iswin(board)==2)
		printf("游戏结束，算法赢！\n");
	else if(iswin(board)==3)
		printf("没有可以落子的地方啦！游戏结束！\n");

}

int main(int argc ,char* argv[])
{
	int serv_sock;
	int clnt_sock;
	struct sockaddr_in serv_addr;
	struct sockaddr_in clnt_addr;
	socklen_t clnt_addr_size = sizeof(clnt_addr);
	
	//init(board);
	
	if(argc != 3)
	{	printf("Usage:%s [ip][port]\n",argv[0]);	exit(1);	}
	
	serv_sock = socket(AF_INET,SOCK_STREAM,0);
	if(serv_sock == -1)
	{	printf("socket() error!\n");	exit(2);	}
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));
	
	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) == -1 )
	{	printf("bind() error!\n");	exit(3);	}
	
	if(listen(serv_sock,5) == -1)
	{	printf("listen() error!\n");	exit(4);	}
	

	while(1)
	{
		printf("是否进行游戏匹配？（1是/2否）\n");
		int choice=-1;
		scanf("%d",&choice);
		//printf("your choice is:%d<<<",choice);
		if(choice == 1)
		{
			char board[3][3]={{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
			location loc;
			printf("等待用户连接...\n");
			clnt_sock = accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
			if(clnt_sock ==-1)
			{	printf("accept() error!\n");	continue;	}
			else
				printf("对手已就位，游戏开始！\n");
			//print(board);
			while(1)
			{
				location locp;
				read(clnt_sock,&locp,sizeof(locp));
				board[locp.x-1][locp.y-1] = 'X';
				//print(board);
				if(iswin(board))//!=0
				{
					checkwin(board);
					break;
				}
				
				location loc;
				servmove(board,&loc);
				//print(board);
				write(clnt_sock,&loc,sizeof(loc));
				if(iswin(board))//!=0
				{
					checkwin(board);
					break;
				}
			}		
		}	
		else if(choice==2)
		{printf("已成功关闭服务器！\n");break;}
		else
		{	printf("输入有误！\n");	continue;}
			
			
	}
	close(serv_sock);
	close(clnt_sock);
	return 0;
}

