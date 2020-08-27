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
	//这里加下棋的算法函数调用
	int net[3][3];//0 means null;1 means X;2 means O;
	int i,j;
	for(i=0;i<3;i++)
	{
		for(j=0;j<3;j++)
		{
			if(board[i][j]==' ')
				net[i][j] = 0;
			else if(board[i][j]=='X')
				net[i][j] = 1;
			else
				net[i][j] = 2;
		}
	}
	
       int level[3][3]={{0,0,0},{0,0,0},{0,0,0}};//越大优先级越高 
       int o2=10000;//一个己方活二权值
       int x2=1000;//一个对方活二权值
       int x=10;//一个对方活一权值
       int o=6;//一个己方活一权值
       int nothing=1;//一个空行权值

	
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(net[i][j]!=0)
				level[i][j]=0;

			else{
			        //自己活二,,220
				if(((net[0][j]+net[1][j]+net[2][j])==4)&&(net[0][j]*net[1][j]*net[2][j])==0
						&&((net[0][j]-1)*(net[1][j]-1)*(net[2][j]-1))==-1)
					level[i][j]+=o2;
				if(((net[i][0]+net[i][1]+net[i][2])==4)&&(net[i][0]*net[i][1]*net[i][2])==0
						&&((net[i][0]-1)*(net[i][1]-1)*(net[i][2]-1))==-1)
					level[i][j]+=o2;
				//对方活二，110
				if(((net[0][j]+net[1][j]+net[2][j])==2)&&(net[0][j]*net[1][j]*net[2][j])==0
						&&((net[0][j]-1)*(net[1][j]-1)*(net[2][j]-1))==0)
					level[i][j]+=x2;
				if(((net[i][0]+net[i][1]+net[i][2])==2)&&(net[i][0]*net[i][1]*net[i][2])==0
						&&((net[i][0]-1)*(net[i][1]-1)*(net[i][2]-1))==0)
					level[i][j]+=x2;
				//单个X，100
				if(((net[0][j]+net[1][j]+net[2][j])==1)&&(net[0][j]*net[1][j]*net[2][j])==0
						&&((net[0][j]-1)*(net[1][j]-1)*(net[2][j]-1))==0)
					level[i][j]+=x;
				if(((net[i][0]+net[i][1]+net[i][2])==1)&&(net[i][0]*net[i][1]*net[i][2])==0
						&&((net[i][0]-1)*(net[i][1]-1)*(net[i][2]-1))==0)
					level[i][j]+=x;
				//单个O，200
				if(((net[0][j]+net[1][j]+net[2][j])==2)&&(net[0][j]*net[1][j]*net[2][j])==0
						&&((net[0][j]-1)*(net[1][j]-1)*(net[2][j]-1))==1)
					level[i][j]+=o;
				if(((net[i][0]+net[i][1]+net[i][2])==2)&&(net[i][0]*net[i][1]*net[i][2])==0
						&&((net[i][0]-1)*(net[i][1]-1)*(net[i][2]-1))==1)
					level[i][j]+=o;
				//空行，000
				if(((net[0][j]+net[1][j]+net[2][j])==0)&&(net[0][j]*net[1][j]*net[2][j])==0
						&&((net[0][j]-1)*(net[1][j]-1)*(net[2][j]-1))==-1)
					level[i][j]+=nothing;
				if(((net[i][0]+net[i][1]+net[i][2])==0)&&(net[i][0]*net[i][1]*net[i][2])==0
						&&((net[i][0]-1)*(net[i][1]-1)*(net[i][2]-1))==-1)
					level[i][j]+=nothing;

				//分情况
				//主对角线
				if((i==0&&j==0)||(i==2&&j==2)||(i==1&&j==1)){
				//己方活二
				if(((net[0][0]+net[1][1]+net[2][2])==4)&&(net[0][0]*net[1][1]*net[2][2])==0&&
				((net[0][0]-1)*(net[1][1]-1)*(net[2][2]-1))==-1)
					level[i][j]+=o2;
				//对方活二
				if(((net[0][0]+net[1][1]+net[2][2])==2)&&(net[0][0]*net[1][1]*net[2][2])==0&&
				((net[0][0]-1)*(net[1][1]-1)*(net[2][2]-1))==0)
					level[i][j]+=x2;
				//单个X
				if(((net[0][0]+net[1][1]+net[2][2])==1)&&(net[0][0]*net[1][1]*net[2][2])==0&&
				((net[0][0]-1)*(net[1][1]-1)*(net[2][2]-1))==0)
					level[i][j]+=x;
				//单个O
				if(((net[0][0]+net[1][1]+net[2][2])==2)&&(net[0][0]*net[1][1]*net[2][2])==0&&
				((net[0][0]-1)*(net[1][1]-1)*(net[2][2]-1))==1)
					level[i][j]+=o;
				//空行，000
				if(((net[0][0]+net[1][1]+net[2][2])==0)&&(net[0][0]*net[1][1]*net[2][2])==0&&
				((net[0][0]-1)*(net[1][1]-1)*(net[2][2]-1))==-1)
					level[i][j]+=nothing;
				}

       

				//副对角线
				if((i==0&&j==2)||(i==2&&j==0)||(i==1&&j==1)){
				//己方活二
				if(((net[0][2]+net[1][1]+net[2][0])==4)&&(net[0][2]*net[1][1]*net[2][0])==0&&
				((net[0][2]-1)*(net[1][1]-1)*(net[2][0]-1))==-1)
				level[i][j]+=o2;

				//对方活二
				if(((net[0][2]+net[1][1]+net[2][0])==2)&&(net[0][2]*net[1][1]*net[2][0])==0&&
				((net[0][2]-1)*(net[1][1]-1)*(net[2][0]-1))==0)
				level[i][j]+=x2;

				//单个X
				if(((net[0][2]+net[1][1]+net[2][0])==1)&&(net[0][2]*net[1][1]*net[2][0])==0&&
				((net[0][2]-1)*(net[1][1]-1)*(net[2][0]-1))==0)
				level[i][j]+=x;

				//单个O
				if(((net[0][2]+net[1][1]+net[2][0])==2)&&(net[0][2]*net[1][1]*net[2][0])==0&&
				((net[0][2]-1)*(net[1][1]-1)*(net[2][0]-1))==1)
				level[i][j]+=o;
					  
				//空行，000
				if(((net[0][2]+net[1][1]+net[2][0])==0)&&(net[0][2]*net[1][1]*net[2][0])==0&&
				((net[0][2]-1)*(net[1][1]-1)*(net[2][0]-1))==-1)
				level[i][j]+=nothing;
				}//the end of for if
			}//the end of if
		}//the end of for j
	}//the end of for i
	
	//寻找最大权值的位置
	int maxi = 0,maxj = 0,temp = 0;
	for(i=0;i<3;i++)
		for(j=0;j<3;j++)
			if(level[i][j]>temp){
				temp=level[i][j];
				maxi=i;
				maxj=j;
			}
	loc->x = maxi;
	loc->y = maxj;
	printf("计算所得落子点：%d  %d\n",maxi+1,maxj+1);
	
	board[loc->x][loc->y] = 'O';
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

















