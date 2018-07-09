#include<graphics.h>
#include<conio.h>
#include<math.h>
#include<time.h>
#include<iostream>
using namespace std;
const int WINDOW_HEIGHT = 600;  //���崰�ڵĸ�
const int WINDOW_WIDE = 400;    //���崰�ڵĿ�
//const int TIME = 3;//С������ʱ��

class Ball
{
private:
    int speed = 2;    //������ķ����ٶ�
public:
	double addx, addy;
	const int r = 8;        //������İ뾶
	double ballx = WINDOW_WIDE / 2, bally = WINDOW_HEIGHT - r - 1;       //�����������
																	  //������������־��
	//bool go;            //С���Ƿ���
	bool iscatch;       //С���Ƿ񵽴�ײ�
						//int getr(){return r;}//�ṩС��İ뾶
						//���캯��  ʹС���ʼ��ʱλ��ľ��������
	Ball()
	{
		//��ʼʱС�������Ϸ���
        //go = 0;         //��ʼ��״̬ С��δ�����ȥ
		iscatch = 1;    //��ʼ��״̬ ��ľ���ס
	};
	void setaddx(double addx0) { addx = addx0; }
	void setaddy(double addy0) { addy = addy0; }//��ʾ��ķ��з���

													 //С���ƶ�����
	void Move()
	{
		BeginBatchDraw();       //����������ͼģʽ
        setfillcolor(BLACK);    //����С��ǰλ��
		solidcircle(ballx, bally, r);
		ballx += addx * speed;    //С���˶�λ��
		bally += addy * speed;
		setfillcolor(RED);      //����λ�û�С��
		solidcircle(ballx, bally, r);
								//����߽磺���ң��ϱ߽�Ҫ����
		if (ballx >= WINDOW_WIDE - r || ballx <= r) { addx *= -1; }
		if (bally <= r) { addy *= -1; }
		//��С�򴥼��±߽� ˵��һ�غϽ���
		if (bally >= WINDOW_HEIGHT - r) {
			iscatch = 0; return; }
		FlushBatchDraw();       //��֮ǰ���еĻ�ͼ������ʾ����
		Sleep(3);               //���ߣ�������ͣ,ʹС���������˶�
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
			case WM_LBUTTONDOWN://������������
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
			//������С�����ȥ�Ķ���
			if (ball.ballx >= WINDOW_WIDE / 2) { ball.setaddx(-1); }
			else { ball.setaddx(1); }

			while (1)
			{
				BeginBatchDraw();
				setfillcolor(BLACK);
				solidcircle(ball.ballx, 591, ball.r);
				ball.ballx += ball.addx * 2;    //С���˶�λ��
				ball.bally =591;
				setfillcolor(RED);      //����λ�û�С��
				solidcircle(ball.ballx,591, ball.r);
				if (ball.addx>0&&ball.ballx>=200||ball.addx<0&&ball.ballx<=200 ) { 
					break; }
				FlushBatchDraw();    
				Sleep(3);//��֮ǰ���еĻ�ͼ������ʾ����
				
			}
			return MessageBox(NULL, L"You Lose!", L"��ש��", MB_RETRYCANCEL);
		}
		ball.Move();
		
	}
}
int main()
{
	initgraph(WINDOW_WIDE, WINDOW_HEIGHT);  //��ʼ������
	
	while (1)
	{
		if (Gaming() == IDCANCEL)           //��� ȡ��
			return 0;
	}
}