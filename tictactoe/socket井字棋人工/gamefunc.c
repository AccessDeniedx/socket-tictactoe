#include"gamefunc.h"

void printmenu()
{
	printf("\n---------------------------------------\n");
	printf("|                游戏菜单              |\n");
	printf("|                                      |\n");
	printf("|          1:开始匹配 2: 退出游戏      |\n");
	printf("|                                      |\n");
	printf("---------------------------------------\n");
	printf("请选择：");
}

void print(char board[3][3])
{
	int i;
	for(i=0;i<3;i++)
	{
		printf(" %c | %c | %c \n",board[i][0],board[i][1],board[i][2]);
		if(i==1 ||i==0)
			printf("---|---|---\n");
	}
}


void servmove(char board[3][3],location *loc)
{
	while(1){
		printf("请输入您的坐标，横坐标(1-3) 纵坐标(1-3)：");
		scanf("%d%d",&loc->x,&loc->y);
		if( loc->x>=1 && loc->x<=3   &&   loc->x>=1 && loc->y <=3){
			if(board[loc->x - 1][loc->y - 1]==' ')
			{
				board[loc->x - 1][loc->y - 1] = 'O';
				break;
			}else
				printf("该位置已有棋子！\n");				
		}
		else{printf("输入坐标范围错误，请重新输入！\n");}
	}
}

void clientmove(char board[3][3],location *loc)
{
	//int flag = 0;
	while(1){
		printf("请输入您的坐标，横坐标(1-3) 纵坐标(1-3)：");
		scanf("%d%d",&loc->x,&loc->y);
		if( loc->x>=1 && loc->x<=3   &&   loc->x>=1 && loc->y <=3){
			if(board[loc->x - 1][loc->y - 1]==' ')
			{
				board[loc->x - 1][loc->y - 1] = 'X';
				break;
			}else
				printf("该位置已有棋子！\n");				
		}
		else{printf("输入坐标范围错误，请重新输入！\n");}
	}
}

int iswin(char board[3][3])
{
	int flag = 0;
	int i,j;
	int count=0;
	if((board[0][0]==board[1][1])&&(board[1][1]==board[2][2])&&(board[0][0]=='X'||board[0][0]=='O'))
		flag = board[0][0];
	if((board[0][2]==board[1][1])&&(board[1][1]==board[2][0])&&(board[0][2]=='X'||board[0][2]=='O'))
		flag = board[1][1];
	for(i=0;i<3;i++)
		if((board[i][0]==board[i][1])&&(board[i][1]==board[i][2])&&(board[i][0]=='X'||board[i][0]=='O'))
			flag = board[i][1];
	for(j=0;j<3;j++)
		if((board[0][j]==board[1][j])&&(board[1][j]==board[2][j])&&(board[0][j]=='X'||board[0][j]=='O'))
			flag = board[1][j];
			
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(board[i][j]==' ')
				count++;
	//printf("this is iswin(),now count=%d\n",count);
	if(count==0){
		return 3;
	}	
	
	if(flag==0)
		return 0;
	else
	{
		if(flag=='X')
			return 1;
		else if(flag=='O')
			return 2;
	}
}

















