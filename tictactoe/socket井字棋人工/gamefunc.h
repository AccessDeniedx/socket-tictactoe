#pragma once
#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>

typedef struct{
	int x;
	int y;
}location;


void printmenu();

void print(char board[3][3]);

void servmove(char board[3][3],location *loc);

void clientmove(char board[3][3],location *loc);

int iswin(char board[3][3]);

