/*

每个格子的生死遵循下面的原则：

1． 如果一个细胞周围有3个细胞为生（一个细胞周围共有8个细胞），
则该细胞为生（即该细胞若原先为死，则转为生，若原先为生，则保持不变） 。

2． 如果一个细胞周围有2个细胞为生，则该细胞的生死状态保持不变；

3． 在其它情况下，该细胞为死（即该细胞若原先为生，则转为死，
若原先为死，则保持不变）

*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <windows.h> 

#include <iostream>
using namespace std;

#define LENGTH 40
#define HEIGHT 40
#define SLEEP 100	//代际间延时，毫秒 
#define DELAY 100	//描点延时，毫秒  

bool matrix[HEIGHT][LENGTH]={0};
bool matrix_copy[HEIGHT][LENGTH]={0};

//display函数运行说明
//输入参数
//0 清空屏幕+延时
//1 不清空屏幕+延时
//2 清空屏幕+不延时
//3 不清空屏幕+不延时 
void display(int control)
{
	if(control==0||control==2)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});//system("cls");
	}
		
	for(int i=0;i<HEIGHT;i++)
	{
		for(int j=0;j<LENGTH;j++)
		{
			if(matrix[i][j])
			{
				printf("■");
			}
			else
			{
				printf("  ");
			}
		}
		printf("\n");
	}
	
	if(control==0||control==1)_sleep(SLEEP);
} 

int check(int y,int x)
{
	int sum=0;
	int a[8],b[8];//其余8个点坐标 
	
	a[0]=y-1;b[0]=x-1;//左上坐标
	a[1]=y-1;b[1]=x;//上坐标
	a[2]=y-1;b[2]=x+1;//右上坐标
	
	a[3]=y;b[3]=x-1;//左坐标
	a[4]=y;b[4]=x+1;//右坐标
	
	a[5]=y+1;b[5]=x-1;//左下坐标
	a[6]=y+1;b[6]=x;//下坐标
	a[7]=y+1;b[7]=x+1;//右下坐标
	
	if(a[0]==-1 && b[0]==-1){a[0]=HEIGHT-1;b[0]=LENGTH-1;}//左上角 
	if(a[5]==HEIGHT && b[5]==-1){a[0]=LENGTH-1;b[0]=0;} //左下角 
	if(a[2]==-1 && b[2]==LENGTH){a[0]=0;b[0]=HEIGHT-1;} //右上角 
	if(a[2]==HEIGHT && b[2]==LENGTH){a[0]=0;b[0]=0;} //右下角 
	
	//上边 
	if(a[0]==-1) a[0]=HEIGHT-1;
	if(a[1]==-1) a[1]=HEIGHT-1;
	if(a[2]==-1) a[2]=HEIGHT-1;
	//下边 
	if(a[5]==HEIGHT) a[5]=0;
	if(a[6]==HEIGHT) a[6]=0;
	if(a[7]==HEIGHT) a[7]=0;
	//左边 
	if(b[0]==-1) b[0]=LENGTH-1;
	if(b[3]==-1) b[3]=LENGTH-1;
	if(b[5]==-1) b[5]=LENGTH-1;
	//右边 
	if(b[2]==LENGTH) b[2]=0;
	if(b[4]==LENGTH) b[4]=0;
	if(b[7]==LENGTH) b[7]=0;
	
	for(int i=0;i<8;i++)
	{
		if(matrix[b[i]][a[i]])
		{
			sum++;
		}
	}
	
	return sum;
}

void copy(int way)
{
	if(way)//way==1 覆盖原内容 
	{
		for(int i=0;i<HEIGHT;i++)
		{
			for(int j=0;j<LENGTH;j++)
			{
				matrix[i][j]=matrix_copy[i][j];
			}
		}
	}
	else//way==0产生备份 
	{
		for(int i=0;i<HEIGHT;i++)
		{
			for(int j=0;j<LENGTH;j++)
			{
				matrix_copy[i][j]=matrix[i][j];
			}
		} 
	}
}

void init(int x,int y)//手动描点，显示 
{
	matrix[y][x]=1;
	display(2);
	cout<<">> 描点("<<y<<","<<x<<")成功"<<endl;
	_sleep(DELAY);
}

void include(int x,int y)//自动描点，不显示 
{
	matrix_copy[y][x]=1;
}

void seclude(int x,int y)//自动擦除，不显示 
{
	matrix_copy[y][x]=0;
}

void mode1(void)//回形 
{
	//数据区开始 
	init(8,8);
	init(8,9);
	init(8,10);
	init(7,8);
	init(7,10);
	init(6,8);
	init(6,9);
	init(6,10);
	//数据区结束 	
}

void mode2(void)//太空船 
{
	//数据区开始 
	init(14,4);
	init(14,5);
	init(14,6);
	init(15,6);
	init(16,6);
	init(17,6);
	init(15,3);
	init(18,3);
	init(18,5);
	//数据区结束 
}

void mode3(void)//T
{
	//数据区开始 
	init(4,4);
	init(5,4);
	init(6,4);
	init(5,5);
	init(5,6);
	//数据区结束 
}

void mode4(void)//蜂窝 
{
	//数据区开始 
	init(10,3);
	init(10,6);
	init(9,4);
	init(9,5);
	init(11,4);
	init(11,5);
	//数据区结束 
}

void mode5(void)//滑翔翼 
{
	//数据区开始 
	init(21,3);
	init(22,3);
	init(23,3);
	init(23,4);
	init(22,5);
	//数据区结束 
}

void mode6(void)//花 
{
	//数据区开始 
	init(15,20);
	init(15,21);
	init(15,22);
	init(15,23);
	
	init(16,16);
	init(16,17);
	init(16,19);
	init(16,24);
	
	init(17,15);
	init(17,19);
	init(17,24);
	
	init(18,15);
	init(18,20);
	init(18,21);
	
	init(19,15);
	init(19,18);
	init(19,23);
	init(19,24);
	
	init(20,15);
	init(20,18);
	init(20,22);
	init(20,25);
	
	init(21,16);
	init(21,17);
	init(21,22);
	init(21,25);
	
	init(22,19);
	init(22,20);
	init(22,25);
	
	init(23,16);
	init(23,21);
	init(23,25);
	
	init(24,16);
	init(24,21);
	init(24,23);
	init(24,24);
	
	init(25,17);
	init(25,18);
	init(25,19);
	init(25,20);
	//数据区结束 
}

void mode7(void)//花屏 
{
	//数据区开始 
	init(2,3);
	init(3,3);
	init(4,4);
	//数据区结束 
}

int main()
{
	int generation=1;
	display(0);
	
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),{0,0});//system("cls");
	
	mode6();//初始化实验模式 
	display(2);//绘图 
	cout<<">> Generation = "<<0;//第0代（父代） 
	_sleep(2*SLEEP);//等待 

	while(1)
	{
		copy(0);//产生备份
		
		for(int i=0;i<HEIGHT;i++)
		{
			for(int j=0;j<LENGTH;j++)
			{
				//如果一个细胞周围有2个细胞为生，则该细胞的生死状态保持不变；
				if(check(i,j)==2);
				//如果一个细胞周围有3个细胞为生（一个细胞周围共有8个细胞），
				//则该细胞为生（即该细胞若原先为死，则转为生，若原先为生，则保持不变） 。
				else if(check(i,j)==3)include(i,j);//描点
				// 在其它情况下，该细胞为死
				//（即该细胞若原先为生，则转为死，若原先为死，则保持不变）
				else seclude(i,j);//移除 
			}
		}
		
		copy(1);//覆盖原内容 
		
		display(2);
		cout<<">> Generation = "<<generation;
		generation++;
		_sleep(SLEEP);
	}
	
	system("PAUSE");
	return 0;
} 
