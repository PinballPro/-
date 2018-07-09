#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<iostream>
using namespace std;
const int WINDOW_HEIGHT = 600;  //定义窗口的高
const int WINDOW_WIDE = 400;    //定义窗口的宽
//const int TIME = 3;//小球发射间隔时间

class Ball
{
private:
    int speed = 2;    //定义球的飞行速度
public:
	double addx, addy;
	const int r = 8;        //定义球的半径
	double ballx = WINDOW_WIDE / 2, bally = WINDOW_HEIGHT - r - 1;       //定义球的坐标
																	  //设置两个个标志量
	//bool go;            //小球是否发射
	bool iscatch;       //小球是否到达底部
						//int getr(){return r;}//提供小球的半径
						//构造函数  使小球初始化时位于木板中心上
	Ball()
	{
		//初始时小球向右上发射
        //go = 0;         //初始化状态 小球未发射出去
		iscatch = 1;    //初始化状态 球被木板接住
	};
	void setaddx(double addx0) { addx = addx0; }
	void setaddy(double addy0) { addy = addy0; }//表示球的飞行方向

													 //小球移动函数
	void Move()
	{
		BeginBatchDraw();       //开启批量画图模式
        setfillcolor(BLACK);    //擦除小球当前位置
		solidcircle(ballx, bally, r);
		ballx += addx * speed;    //小球运动位置
		bally += addy * speed;
		setfillcolor(RED);      //在新位置画小球
		solidcircle(ballx, bally, r);
								//处理边界：左，右，上边界要反弹
		if (ballx >= WINDOW_WIDE - r || ballx <= r) { addx *= -1; }
		if (bally <= r) { addy *= -1; }
		//若小球触及下边界 说明一回合结束
		if (bally >= WINDOW_HEIGHT - r) {
			iscatch = 0; return; }
		FlushBatchDraw();       //把之前所有的绘图内容显示出来
		Sleep(3);               //休眠，就是暂停,使小球慢慢地运动
	}
};
int Gaming()
{
	//clock_t now = clock();
	Ball ball;
	setfillcolor(RED);
	solidcircle(ball.ballx, ball.bally, ball.r);
	double Xmouse = 0, Ymouse = 0, z;
	MOUSEMSG m;
	if (Xmouse == 0 && Ymouse == 0)
	{
		while (1)
		{
			m = GetMouseMsg();
			switch (m.uMsg)
			{
			case WM_LBUTTONDOWN://点鼠标左键发射
				Xmouse = m.x - WINDOW_WIDE / 2;
				Ymouse = WINDOW_HEIGHT - m.y;
				z = sqrt(Xmouse*Xmouse + Ymouse * Ymouse);
				Xmouse = Xmouse / z;
				Ymouse = -1 * Ymouse / z;
				break;
				//default: break;
			}
			if (Xmouse != 0 && Ymouse != 0)break;
		}
	}
	ball.setaddx(Xmouse); ball.setaddy(Ymouse);
	while (1)
	{
		if (ball.iscatch == 0)
		{
			//绘制让小球滚回去的动画
			if (ball.ballx >= WINDOW_WIDE / 2) { ball.setaddx(-1); }
			else { ball.setaddx(1); }

			while (1)
			{
				BeginBatchDraw();
				setfillcolor(BLACK);
				solidcircle(ball.ballx, 591, ball.r);
				ball.ballx += ball.addx * 2;    //小球运动位置
				ball.bally =591;
				setfillcolor(RED);      //在新位置画小球
				solidcircle(ball.ballx,591, ball.r);
				if (ball.addx>0&&ball.ballx>=200||ball.addx<0&&ball.ballx<=200 ) { 
					break; }
				FlushBatchDraw();    
				Sleep(3);//把之前所有的绘图内容显示出来
				
			}
			return MessageBox(NULL, L"You Lose!", L"打砖块", MB_RETRYCANCEL);
		}
		ball.Move();
		
	}
}
int main()
{
	initgraph(WINDOW_WIDE, WINDOW_HEIGHT);  //初始化窗口
	
	while (1)
	{
		if (Gaming() == IDCANCEL)           //点击 取消
			return 0;
	}
}