# 智能蛇实验报告
## 实验目的
1.了解 算法 与 “智能” 的关系

2.通过算法赋予蛇智能

3.了解 Linux IO 设计的控制

## 实验环境

这里我采取Unbutu Linus虚拟机

## 控制输入/输出设备

## 编写智能算法
由于有贪吃蛇的基础，一些简单的东西我们便不加解释了，直接上代码
~~~
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SNAKE_MAX_LENGTH 20    
#define SNAKE_HEAD 'H' 
#define SNAKE_BODY 'X'
#define	BLANK_CELL ' '
#define SNAKE_FOOD '$'
#define WALL_CELL '*'


void snakeMove(int ,int );
void putMoney(void);
void output();
void gameover(int ,int );
void getMoney(int ,int );
void sleep(clock_t wait);
char whereGoNext(const int ,const int ,const int ,const int ); 
int getAbsolute(const int ,const int );

char map[12][12]=
	{"************",
	 "*XXXXH     *",
	 "*          *",                  
	 "*          *",                   
	 "*          *",
	 "*          *",
	 "*  *****   *",
	 "*          *",
	 "*          *",
	 "*          *",
	 "*          *",
	 "************"};

//define vars for snake, notice name of vars in C	 
int snakeX[SNAKE_MAX_LENGTH]={1,2,3,4,5};
int snakeY[SNAKE_MAX_LENGTH]={1,1,1,1,1};               
int snakeLength = 5;                                    

int isAlive = 1;                                        //等于 1 时表示蛇还存活，等于 0 时表示蛇已死亡 
int flag=0;                                             //等于 1 时表示吃到了 $ ,等于 0 时表示没吃到 $ 
int Hx=5,Hy=1;                                          //蛇头的坐标
int Fx,Fy;                                              //食物的坐标 

int main(){
	char ch;
	int i,j;
	
	putMoney();                                      //
	
	for(i=0;i<12;i++){
		for(j=0;j<12;j++){
			if(j<11)
				printf("%c",map[i][j]);
			else if(j==11)
				printf("%c\n",map[i][j]);
		}
	}                                                //
	
	while(isAlive!=0){
		
		sleep(1000);
		ch=whereGoNext(Hx,Hy,Fx,Fy);
		switch(ch){
			case 'A': gameover(-1,0);                //先判断是否触发gameover的条件 
					  snakeMove(-1,0);               //往左移动一格 
					  output();break;                //打印新的表格 
			case 'D': gameover(1,0);
					  snakeMove(1,0);                //往右移动一格 
					  output();break;              
			case 'W': gameover(0,-1);
					  snakeMove(0,-1);               //往上移动一格 
					  output();break;
			case 'S': gameover(0,1);
					  snakeMove(0,1);                //往下移动一格 
					  output();break;
		}
		Hx=snakeX[snakeLength-1];
		Hy=snakeY[snakeLength-1]; 
		
	}
	
	printf("Game Over!!!\n");
	
	return 0;
} 

void snakeMove(int dx,int dy){
	int tmpX1=0,tmpY1=0,tmpX2=0,tmpY2=0,i,j;
	tmpX1=snakeX[snakeLength-1];
	tmpY1=snakeY[snakeLength-1];
	
	getMoney(dx,dy);
	if(flag==1){							  //当吃到了食物时 
		snakeLength++;
		snakeX[snakeLength-1]=snakeX[snakeLength-2]+dx;
		snakeY[snakeLength-1]=snakeY[snakeLength-2]+dy;
		map[snakeY[snakeLength-1]][snakeX[snakeLength-1]]='H';
		map[snakeY[snakeLength-2]][snakeX[snakeLength-2]]='X';
		flag=0;
	} 										  
	else if(flag==0){                         //当没吃到食物 时 
		for(i=snakeLength-2;i>=0;i--){
			tmpX2=snakeX[i];
			tmpY2=snakeY[i];                  //tmpX2、tmpY2用于记录蛇当前部分的坐标 
			snakeX[i]=tmpX1;
			snakeY[i]=tmpY1;                  //tmpX1、tmpY1用于记录蛇上一部分的坐标 
			tmpX1=tmpX2;
			tmpY1=tmpY2;
		}                                     //将后面的蛇身往前挪一位 
	
		map[tmpY1][tmpX1]=' ';                //将末尾改为空格 
	
		if(dx==-1&&dy==0)
			snakeX[snakeLength-1]-=1;
		else if(dx==1&&dy==0)
			snakeX[snakeLength-1]+=1;
		else if(dx==0&&dy==-1)
			snakeY[snakeLength-1]-=1;
		else if(dx==0&&dy==1)
			snakeY[snakeLength-1]+=1;		  //将蛇头按方向行进一位
			                                   
		for(i=0;i<snakeLength;i++){
			if(i<snakeLength-1)
				map[snakeY[i]][snakeX[i]]='X';
			else if(i==snakeLength-1)
				map[snakeY[i]][snakeX[i]]='H';
		}									  //将蛇头和蛇身赋值相应字符
	}
}

void gameover(int dx,int dy){
	if(map[snakeY[snakeLength-1]+dy][snakeX[snakeLength-1]+dx]=='X'||map[snakeY[snakeLength-1]+dy][snakeX[snakeLength-1]+dx]=='*')
		isAlive=0;
}                                             //判断游戏是否结束

void putMoney(){
	int x,y;
	
	srand(time(NULL));
	x=1+(rand()%10);
	y=1+(rand()%10);
	while(map[x][y]!=' '){
		x=1+(rand()%10);
		y=1+(rand()%10);
	}
	Fx=y;
	Fy=x;
	map[x][y]='$';
}                                          //随机位置产生一个食物

void getMoney(int dx,int dy){	
	if(map[snakeY[snakeLength-1]+dy][snakeX[snakeLength-1]+dx]=='$'){
		if(snakeLength<SNAKE_MAX_LENGTH){
			flag=1;
			putMoney();
		}
		else
			putMoney(); 
	}
}                                          //判断是否吃到食物
void output(){
	int i=0,j=0;
	for(i=0;i<12;i++){
		for(j=0;j<12;j++){
			if(j<11)
				printf("%c",map[i][j]);
			else if(j==11)
				printf("%c\n",map[i][j]);
		}
	}
}	                                    	  //打印 

void sleep(clock_t wait)
{
clock_t goal;
goal = wait + clock();
while(goal > clock());
}

int getAbsolute(const int x,const int y){
	if(x-y<0)
		return y-x;
	else
		return x-y;
}

char whereGoNext(const int Hx,const int Hy,const int Fx,const int Fy){
	char movable[4]={'A','D','W','S'};                       
	int distance[4]={0,0,0,0};     //各个方向与最终目标的距离
	if(map[Hy][Hx-1]==' '||map[Hy][Hx-1]=='$')
		distance[0]= getAbsolute(Fx,Hx-1) + getAbsolute(Fy,Hy);
	else
		distance[0]=9999;
	if(map[Hy][Hx+1]==' '||map[Hy][Hx+1]=='$')
		distance[1]= getAbsolute(Fx,Hx+1) + getAbsolute(Fy,Hy);
	else
		distance[1]=9999;
	if(map[Hy-1][Hx]==' '||map[Hy-1][Hx]=='$')
		distance[2]= getAbsolute(Fx,Hx) + getAbsolute(Fy,Hy-1);
	else
		distance[2]=9999;
	if(map[Hy+1][Hx]==' '||map[Hy+1][Hx]=='$')
		distance[3]= getAbsolute(Fx,Hx) + getAbsolute(Fy,Hy+1);
	else
		distance[3]=9999;    //计算走四个方向后与食物的距离                                
	
	if(distance[0]==9999&&distance[1]==9999&&distance[2]==9999&&distance[3]==9999){
		isAlive=0;
		return movable[0];
	}                  //如果四个方向都是死路 则生命值变为 0 
	else{
		int min=9999,flag=0,i=0;
		for(i=0;i<4;i++){
			if(min>distance[i]){
				flag=i;
				min=distance[i];
			}
		}
		return movable[flag];
	}                 //返回最近的走法                                           
}

~~~

## 实验总结

这个简单的字符游戏让我感受到了自顶向下，逐步求精的妙用,刚刚看到这个题的时候头都大了，但是后来通过弄成几个函数之后就把复杂的问题简单化了，很棒的一次实验体验！