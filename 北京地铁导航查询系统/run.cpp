#undef UNICODE
#undef _UNICODE
#include"function1.h"

int	main()
{
	readfile1();
	readfile2();
	initMap();
	//cout << findbelong("ɳ��", "��ƽ");
	//string start;
	//string end;
	/*print1();
	print2();*/
	HWND hwnd;
	hwnd = initgraph(1000, 750, SHOWCONSOLE);//����һ������
	IMAGE background;//����һ��ͼƬ��.
	loadimage(&background, "./images/Bsubway.png", 1000, 750, 1);//��ͼƬ�ļ���ȡͼ��
	SetWindowText(hwnd, "PiedpiperG and Cai");
	int	Mode = 0;	//�жϴ���ʲôģʽ��Ĭ��ֵ0Ϊ�˵�ģʽ
	char start[10] = {};
	char end[10] = {};
	char insertstart[10] = {};
	char insertend[10] = {};
	char insertlength[10] = {};
	char stopusesta[10] = {};
	char stopuselin[10] = {};
	while (1)
	{
		BeginBatchDraw(); //��������ӡ����ֹ����
		cleardevice();//ˢ��
		putimage(0, 0, &background);//����ͼ����Ļ��ͼƬ���Ͻ�����Ϊ(0,0)

		while (_kbhit())//����а�������룬���򲻽���ѭ��
		{
			char userkey = 0;
			userkey = _getch();
			if (userkey == VK_ESCAPE)
			{
				Mode = 0;
			}
		}

		if (Mode == 0)
		{
			TCHAR s[50] = "1.������·";
			TCHAR s1[50] = "2.��ͣվ��";
			TCHAR s2[50] = "3.��ͣ��·";
			TCHAR s3[50] = "4.����·��";
			button(391, 200, 170, 50, s);
			button(391, 300, 170, 50, s1);
			button(391, 400, 170, 50, s2);
			button(391, 500, 170, 50, s3);
			ExMessage msg;
			if (peekmessage(&msg, EM_MOUSE))
			{
				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					if (msg.x >= 391 && msg.x <= 391 + 170 && msg.y >= 200 && msg.y <= 200 + 50)
					{
						cout << "!" << endl;
						Mode = 1;
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					if (msg.x >= 391 && msg.x <= 391 + 170 && msg.y >= 300 && msg.y <= 300 + 50)
					{
						cout << "?" << endl;
						Mode = 2;
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  
					}
					if (msg.x >= 391 && msg.x <= 391 + 170 && msg.y >= 400 && msg.y <= 400 + 50)
					{
						cout << "@" << endl;
						Mode = 3;
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					if (msg.x >= 391 && msg.x <= 391 + 170 && msg.y >= 500 && msg.y <= 500 + 50)
					{
						cout << "&" << endl;
						Mode = 4;
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					break;
				default:
					break;
				}
			}

		}
		else if (Mode == 1)
		{


			TCHAR s[50] = "���������";
			TCHAR s1[50] = "�������յ�";
			TCHAR s2[50] = "ȷ��";
			button(391, 200, 250, 50, s);
			button(391, 300, 250, 50, s1);
			button(391, 400, 250, 50, s2);
			ExMessage msg;
			if (peekmessage(&msg, EM_MOUSE))
			{

				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					//cout << "!!!!!!!" << endl;
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 200 && msg.y <= 200 + 50)
					{
						cout << "�������" << endl;
						InputBox(start, 100, "���������");
						if (showerror(start))
						{
							start[0] = '\0';
						}
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 300 && msg.y <= 300 + 50)
					{
						cout << "�����յ�" << endl;
						InputBox(end, 100, "�������յ�");
						if (showerror(end))
						{
							end[0] = '\0';
						}
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  
					}
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 400 && msg.y <= 400 + 50)
					{
						cout << "ȷ��" << endl;
						string s = start;
						string e = end;
						dijkstra(s, e);
						dijkstra2(s, e);
						dijkstra3(s, e);
						Mode = 9;
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  

					}
					break;
				default:
					break;
				}
			}
			setbkmode(TRANSPARENT);
			settextcolor(LIGHTBLUE);
			outtextxy(751, 200, start);
			outtextxy(751, 300, end);
		}
		else if (Mode == 9)
		{
			//cout << "9" << endl;
			display();
			TCHAR s[50] = "��һҳ";
			button(700, 700, 100, 25, s);
			ExMessage msg;
			if (peekmessage(&msg, EM_MOUSE))
			{

				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					//cout << "!!!!!!!" << endl;
					if (msg.x >= 700 && msg.x <= 700 + 75 && msg.y >= 700 && msg.y <= 700 + 25)
					{
						cout << "��һҳ" << endl;
						Mode = 10;
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					break;
				default:
					break;
				}
			}
		}
		else if (Mode == 10)
		{
			display2();
			TCHAR s[50] = "��һҳ";
			button(600, 700, 100, 25, s);
			TCHAR s1[50] = "��һҳ";
			button(700, 700, 100, 25, s1);
			ExMessage msg;
			if (peekmessage(&msg, EM_MOUSE))
			{

				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					//cout << "!!!!!!!" << endl;
					if (msg.x >= 600 && msg.x <= 600 + 75 && msg.y >= 700 && msg.y <= 700 + 25)
					{
						cout << "��һҳ" << endl;
						Mode = 9;
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					if (msg.x >= 700 && msg.x <= 700 + 75 && msg.y >= 700 && msg.y <= 700 + 25)
					{
						cout << "��һҳ" << endl;
						Mode = 11;
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					break;
				default:
					break;
				}
			}
		}
		else if (Mode == 11)
		{
			display3();
			TCHAR s[50] = "��һҳ";
			button(600, 700, 100, 25, s);
			ExMessage msg;
			if (peekmessage(&msg, EM_MOUSE))
			{

				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					//cout << "!!!!!!!" << endl;
					if (msg.x >= 600 && msg.x <= 600 + 75 && msg.y >= 700 && msg.y <= 700 + 25)
					{
						cout << "��һҳ" << endl;
						Mode = 10;
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					break;
				default:
					break;
				}
			}
		}
		else if (Mode == 2)
		{
			TCHAR s[50] = "������Ҫͣ�õ�վ��";
			TCHAR s2[50] = "ȷ��";
			button(391, 200, 280, 50, s);
			button(391, 400, 280, 50, s2);
			ExMessage msg;
			if (peekmessage(&msg, EM_MOUSE))
			{

				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					//cout << "!!!!!!!" << endl;
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 200 && msg.y <= 200 + 50)
					{

						cout << "������Ҫͣ�õ�վ��" << endl;
						InputBox(stopusesta, 100, "������Ҫͣ�õ�վ��");
						if (showerror(stopusesta))
							stopusesta[0] = '\0';
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 400 && msg.y <= 400 + 50)
					{
						cout << "ȷ��2" << endl;
						string s = stopusesta;
						forbiddenstation(s);
						HWND abc = GetHWnd();   //��ȡ���ھ��
						SetWindowText(abc, "Caicai:�����ɹ�");   //�޸Ĵ��ڱ��� 
						MessageBox(abc, "վ���ѱ��ر�", "PiedpiperG", MB_OKCANCEL);  //���öԻ���
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  
					}
					break;
				default:
					break;
				}
			}
			setbkmode(TRANSPARENT);
			settextcolor(LIGHTBLUE);
			outtextxy(751, 200, stopusesta);
		}
		else if (Mode == 3)
		{
			TCHAR s[50] = "������Ҫͣ�õ���·";
			TCHAR s2[50] = "ȷ��";
			button(391, 200, 280, 50, s);
			button(391, 400, 280, 50, s2);
			ExMessage msg;
			if (peekmessage(&msg, EM_MOUSE))
			{
				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					//cout << "!!!!!!!" << endl;
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 200 && msg.y <= 200 + 50)
					{

						cout << "������Ҫͣ�õ���·" << endl;
						InputBox(stopuselin, 100, "��·ǰ+#��#1����");

						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 400 && msg.y <= 400 + 50)
					{
						cout << "ȷ��2" << endl;
						string s = stopuselin;
						forbiddenroad(s);
						HWND abc = GetHWnd();   //��ȡ���ھ��
						SetWindowText(abc, "Caicai:�����ɹ�");   //�޸Ĵ��ڱ��� 
						MessageBox(abc, "��·�ѱ��ر�", "PiedpiperG", MB_OKCANCEL);  //���öԻ���
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  
					}
					break;
				default:
					break;
				}
			}
			setbkmode(TRANSPARENT);
			settextcolor(LIGHTBLUE);
			outtextxy(751, 200, stopuselin);
		}
		else if (Mode == 4)
		{
			TCHAR s[50] = "���������";
			TCHAR s1[50] = "�������յ�";
			TCHAR s2[50] = "ȷ��";
			TCHAR s3[50] = "���������";
			button(391, 200, 250, 50, s);
			button(391, 300, 250, 50, s1);
			button(391, 500, 250, 50, s2);
			button(391, 400, 250, 50, s3);
			ExMessage msg;

			if (peekmessage(&msg, EM_MOUSE))
			{

				switch (msg.message)
				{
				case WM_LBUTTONDOWN:
					//cout << "!!!!!!!" << endl;
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 200 && msg.y <= 200 + 50)
					{
						cout << "�������" << endl;
						InputBox(insertstart, 100, "���������");
						cout << insertstart << endl;
						if (showerror(insertstart))
						{
							start[0] = '\0';
						}
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���
					}
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 300 && msg.y <= 300 + 50)
					{
						cout << "�����յ�" << endl;
						InputBox(insertend, 100, "�������յ�");
						cout << insertend << endl;

						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  
					}
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 500 && msg.y <= 500 + 50)
					{
						cout << "ȷ��" << endl;
						string s = insertstart;
						string e = insertend;
						insertroad(insertstart, insertend, insertlength);
						HWND abc = GetHWnd();   //��ȡ���ھ��
						SetWindowText(abc, "Caicai:�����ɹ�");   //�޸Ĵ��ڱ��� 
						MessageBox(abc, "�ɹ�������·", "PiedpiperG", MB_OKCANCEL);  //���öԻ���
						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  

					}
					if (msg.x >= 391 && msg.x <= 391 + 250 && msg.y >= 400 && msg.y <= 400 + 50)
					{
						cout << "�������" << endl;
						InputBox(insertlength, 100, "���������");

						//�ڴ˴�д�°�ť���ʱҪִ�еĺ�����ʵ����Ӧ�Ĺ���  
					}
					break;
				default:
					break;
				}
			}
			setbkmode(TRANSPARENT);
			settextcolor(LIGHTBLUE);
			outtextxy(751, 200, insertstart);
			outtextxy(751, 300, insertend);
			outtextxy(751, 400, insertlength);
		}


		EndBatchDraw();//��������ӡ
	}
	closegraph();//�رմ���





}
