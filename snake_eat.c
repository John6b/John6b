#include<stdio.h>
#include<stdlib.h>
#include<time.h>


#define SNAKE_MAX_LENGTH 20
#define SNAKE_HEAD 'H'
#define SNAKE_BODY 'X'
#define BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'//定义蛇的最大长度，头部与身体字符及墙壁为游戏开始准备条件 


//snake stepping: dy=-1(up),1(down);dx=-1(left),1(right);0(no mopve);
void snakeMove(int dy,int dx);
//put a food randomized on a blank cell;
void put_food(void);
// out cells of the grid;
void output(void);
//outs when gameover;
void gameover(void);


char map[12][23]= 
	{"**********************",               //直接打出初始状态的表格 
	 "*XXXXH               *",
	 "*                    *",
	 "*                    *",
	 "*                    *",
	 "*                    *",
	 "*                    *",
	 "*                    *",
	 "*                    *",
	 "*                    *",
	 "*                    *",
	 "**********************"};

int flag=1,flag2=1;        //flag1为游戏是否结束的标准，flag2为是否生成食物的标准 
// define vars for snake,notice name of vars in C
int snakeX[SNAKE_MAX_LENGTH]={1,2,3,4,5};       //蛇身和蛇头坐标 
int snakeY[SNAKE_MAX_LENGTH]={1,1,1,1,1};       // X为横，Y为纵 
int snakeLength = 5;


int main(){          //自顶向下，逐步求精
	char ch;
	int dy,dx;
	put_food();      //生成食物 
	output();        //生成初始图 
	
	while(1){
		dy=0;
		dx=0;
		scanf("%c",&ch);
		if(ch=='a'||ch=='s'||ch=='d'||ch=='w'){
			switch(ch){                           //输入进去的字符转变为相应的横纵坐标变化 
				case 'w':dy=-1;break; 
				case 's':dy=1;break;
				case 'a':dx=-1;break;
				case 'd':dx=1;break;	
			}
			snakeMove(dy,dx);                     //对蛇的位置做出处理 
			put_food();                           //生成食物 
			output();                             //输出当前的图表 
			gameover();                           //判断是否游戏结束 
			if(flag==0){                          //flag是否为0为游戏是否进行的标准，若为零则表示已经Game Over 
				return 0;
			}
			if(snakeLength==SNAKE_MAX_LENGTH){
				printf("You Win!!\n");            //如果蛇身长度达到所设置的最长长度,则玩家取得胜利 
				return 0;
			}
		} 
	}
	return 0;
}

void snakeMove(int dy,int dx){
	int i,j;
	if(map[snakeY[snakeLength-1]+dy][snakeX[snakeLength-1]+dx]==SNAKE_FOOD){ 
		snakeLength++;                                                           //如果蛇头碰到食物,则长度+1 
		flag2=1;                                                                 //flag2为是否生成食物的标准 
		snakeX[snakeLength-1]=snakeX[snakeLength-2]+dx;                          //长度加长之后，只需要改变蛇头位置即可 
		snakeY[snakeLength-1]=snakeY[snakeLength-2]+dy;
		map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]=SNAKE_BODY;
		map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]=SNAKE_HEAD;
	}
	else{
		map[snakeY[0]][snakeX[0]]=BLANK_CELL;                                   //把蛇尾位置换为空格 
		for(i=0;i<snakeLength-1;i++){
			snakeX[i]=snakeX[i+1];                                              //把整条蛇的坐标往后推一位 
			snakeY[i]=snakeY[i+1];
			map[snakeY[i]][snakeX[i]]=SNAKE_BODY;
		}
		snakeX[snakeLength-1]=snakeX[snakeLength-2]+dx;                         //蛇头位置做出相应变化 
		snakeY[snakeLength-1]=snakeY[snakeLength-2]+dy;
		map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]=SNAKE_HEAD;
	}
}

void output(void){//把表打印出来
	int i;
	for(i=0;i<12;i++){
		printf("%s\n",map[i]);                       
	}
}

void gameover(void){
	
	int i;
	for(i=0;i<snakeLength-1;i++){
		if((snakeX[i]==snakeX[snakeLength-1]&&snakeY[i]==snakeY[snakeLength-1])||snakeX[snakeLength-1]==0||snakeX[snakeLength-1]==21||snakeY[snakeLength-1]==0||snakeY[snakeLength-1]==11){
			printf("Game Over!!\n");                      //判断蛇头是否碰撞到自身或者墙壁，是就打印Game Over
			flag=0;                                       //flag1为0表示game over，可以跳出循环了 
			break;
		}
	}
	
}
void put_food(void){
	
	int y,x;
	if(flag2==1){                                          //如果flag2为1，需要生成一个食物 
		y=rand()%10+1;
		x=rand()%19+1;                                    //保证食物的坐标处在方框内 
		while(map[y][x]!=BLANK_CELL){                     //如果当前位置不为空，则需要重新生成随机数直至位置为空 
			y=rand()%10+1;
			x=rand()%19+1;
		}
		map[y][x]=SNAKE_FOOD;                             //在当前位置放食物$ 
		flag2=0;                                          //flag2为0,此时不用放食物了 
	}
	
}
