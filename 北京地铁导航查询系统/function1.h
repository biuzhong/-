#include"head.h"

void	readfile1()
{
	//1������ͷ�ļ�
	//2������������
	ifstream ifs;
	//3�����ļ������ж��Ƿ�򿪳ɹ�
	ifs.open("./resource/����2.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	//�洢�����õ����н�ֵ
	string	linename;//��·����
	int		cnt1 = 1;//��վ���
	int		cnt2 = 1;//��·���
	int		formStation;//ǰ��վ���
	int		lateStation;//�󳵱��
	//4��������
	string buf;
	while (getline(ifs, buf))	//��ÿһ�еĴ���
	{
		//cout << buf << endl;
		if (buf[0] == '#')	//����һ������·ʱ��ֻ�洢��·
		{
			linename = buf;
			continue;
		}
		istringstream is(buf);    //��is�󶨵�buf
		string s;
		int	tempcnt = 1;
		while (is >> s)
		{
			if (tempcnt == 1)	//��һ���ַ���
			{
				if (findStation(s) == -1)	//û�д洢���վ��
				{
					station[cnt1].name = s;
					int i = 0;
					while (station[cnt1].belongs[i] != "")
						i++;
					station[cnt1].belongs[i] = linename;
					formStation = cnt1;
					cnt1++;
				}
				else
				{
					int	j = findStation(s);
					int	i = 0;
					while (station[j].belongs[i] != "")
						i++;
					station[j].belongs[i] = linename;
					formStation = j;
				}
				tempcnt = 2;
			}
			else if (tempcnt == 2)
			{
				int j = cnt1;
				bool	ok = false;
				if (findStation(s) == -1)	//û�д洢���վ��
				{
					station[cnt1].name = s;
					ok = true;
				}
				else
				{
					j = findStation(s);
				}
				int i = 0;
				while (station[j].belongs[i] != "")
					i++;
				station[j].belongs[i] = linename;	//���������·
				insertStation(formStation, j);//����ǰһ�������ڽӱ�
				insertStation(j, formStation);
				lateStation = j;	//��¼�󳵱��
				if (ok)
					cnt1++;
				tempcnt = 3;
			}
			else if (tempcnt == 3)
			{
				if (findRoad(station[formStation].name, station[lateStation].name) == -1)
				{
					road[cnt2].from = station[formStation].name;
					road[cnt2].to = station[lateStation].name;
					road[cnt2].distance = atoi(s.c_str());
					//road[cnt2].equaltime = road[cnt2].distance / findspeed(findbelong(station[formStation].name, station[lateStation].name));
					cnt2++;
					road[cnt2].to = station[formStation].name;
					road[cnt2].from = station[lateStation].name;
					road[cnt2].distance = atoi(s.c_str());
					//road[cnt2].equaltime = road[cnt2].distance / findspeed(findbelong(station[formStation].name, station[lateStation].name));
					cnt2++;
				}
				tempcnt = 1;
			}
			//cout << s << endl;
		}

	}
	//5���ر��ļ�
	ifs.close();
}

void readfile2()

{
	//1������ͷ�ļ�
	//2������������
	ifstream ifs;
	//3�����ļ������ж��Ƿ�򿪳ɹ�
	ifs.open("./resource/����ƽ���ٶ�1.txt", ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ʧ��" << endl;
		return;
	}
	//ͳ�Ƶ������
	int	cnt = 1;
	//4��������
	string buf;
	while (getline(ifs, buf))	//��ÿһ�еĴ���
	{
		istringstream is(buf);    //��is�󶨵�buf
		string s;
		while (is >> s)
		{
			if (s[0] == '#')
				subline[cnt].name = s;
			else
			{
				subline[cnt].speed = atoi(s.c_str());
			}
		}
		cnt++;
	}
	//5���ر��ļ�
	ifs.close();
	for (int i = 1; i < Roadnum; i++)
	{
		road[i].equaltime = road[i].distance / findspeed(findbelong(road[i].from, road[i].to));
	}
}

int findStation(string str)
{
	for (int i = 1; i < Stationnum; i++)
	{
		if (station[i].name == str)
			return	i;
	}
	return	-1;	//�������ڴ�վ��ʱ
}

int	findRoad(string start, string end)
{
	for (int i = 1; i < Roadnum; i++)
	{
		if (road[i].from == start && road[i].to == end)
			return	i;
	}
	return	-1;	//�������������·ʱ
}

void insertStation(int start, int end)
{
	if (station[start].nextStaion == NULL)
	{
		Stations* newsta = new Stations;
		newsta->name = station[end].name;
		station[start].nextStaion = newsta;
		newsta->nextStaion = NULL;
	}
	else
	{
		Stations* newsta = new Stations;
		newsta->name = station[end].name;
		newsta->nextStaion = station[start].nextStaion;
		station[start].nextStaion = newsta;	//!!!
	}
}

void print1()
{
	for (int i = 1; i <= Stationnum; i++)
	{
		cout << station[i].name;
		Stations* sta = station[i].nextStaion;
		while (sta)
		{
			cout << "->" << sta->name;
			sta = sta->nextStaion;
		}
		cout << endl;
	}
}

void print2()
{
	for (int i = 1; i <= Roadnum; i++)
	{
		cout << road[i].from << "->" << road[i].to << " need " << road[i].distance << "and" << road[i].equaltime << endl;
	}
}

void bfs(string start, string end)
{
	vector<int>vis(300);
	queue<pos>que;
	pos	cur;
	pos ans[2000];
	pos res;
	int	cnt = 1;
	cur.Loc = start;
	cur.Distance = 0;
	cur.Rember.push_back(start);
	vis[findStation(start)] = 1;
	que.push(cur);
	while (!que.empty())
	{
		cur = que.front();
		que.pop();
		if (cur.Loc == end)	//�ҵ���Ŀ�ĵ�
		{
			ans[cnt] = cur;
			cnt++;
			break;
		}
		Stations* sta = station[findStation(cur.Loc)].nextStaion;
		while (sta)
		{
			pos nex;
			nex.Loc = sta->name;
			sta = sta->nextStaion;
			if (!vis[findStation(nex.Loc)])
			{
				nex.Distance = road[findRoad(cur.Loc, nex.Loc)].distance + cur.Distance;
				nex.Rember = cur.Rember;
				nex.Rember.push_back(nex.Loc);
				que.push(nex);
			}
		}
	}
	res.Distance = INT_MAX;
	for (int i = 1; i <= cnt - 1; i++)
	{
		if (ans[i].Distance < res.Distance)
			res = ans[i];
	}
	for (int i = 0; i < res.Rember.size(); i++)
		cout << res.Rember[i] << "->";
	cout << endl;
}

void	dijkstra(string start, string end)
{
	//���·���㷨��������
	vector<int>Dvis(Stationnum);//��Ƿ�������
	vector<int>Ddis(Stationnum);//�����ʼ�㵽ÿһ���˵����·������
	vector<double>Dtim(Stationnum);//��¼���ʱ��
	vector<int>Dlin(Stationnum);//��¼��ǰ�����һ�������ʲô
	vector<string>Dans;//���·�߽��
	for (int i = 1; i < Stationnum; i++)	//��������г�ʼ��
	{
		Ddis[i] = INT_MAX;
	}
	Ddis[findStation(start)] = 0;	//��ʼ���������
	Dtim[findStation(start)] = 0;
	while (Dvis[findStation(end)] != 1)	//���յ�û�б����ʱ������ѭ��
	{
		int	cur = Ddismin(Ddis, Dvis);	//�ҵ���ǰ�������̵�·��
		Stations* sta = station[cur].nextStaion;
		while (sta)	//���¸ý�㵽�������ľ���
		{
			int nex = findStation(sta->name);
			if (Ddis[nex] > Ddis[cur] + road[findRoad(station[cur].name, station[nex].name)].distance)
			{
				Ddis[nex] = Ddis[cur] + road[findRoad(station[cur].name, station[nex].name)].distance;
				Dtim[nex] = Dtim[cur] + road[findRoad(station[cur].name, station[nex].name)].equaltime;
				Dlin[nex] = cur;
			}
			sta = sta->nextStaion;
		}
		Dvis[cur] = 1;
	}
	int	temp = findStation(end);
	while (temp != findStation(start))
	{
		Dans.push_back(station[temp].name);
		temp = Dlin[temp];
	}
	//Dans.insert(Dans.begin(), start);
	Dans.push_back(start);
	string	linenote = station[findStation(Dans[0])].belongs[0];
	outans.disans = Dans;
	outans.Odistance = Ddis[findStation(end)];
	outans.distime = Dtim[findStation(end)];
	double tempdis = (double)outans.Odistance / 1000;
	outans.Dcostmoney = calculatemoney(tempdis);
	for (int i = 0; i < Dans.size(); i++)
	{

		cout << Dans[Dans.size() - i - 1] << "->";
	}
	cout << endl;
	cout << "�������ȣ�" << endl;
	cout << "��̾���Ϊ��" << Ddis[findStation(end)] << endl;
	cout << "����ʱ��Ϊ:" << Dtim[findStation(end)] << endl;
	cout << "���軨��Ϊ��" << outans.Dcostmoney << endl;
}

void dijkstra2(string start, string end)
{

	//���·���㷨��������
	vector<int>Dvis(Stationnum);//��Ƿ�������
	vector<double>Ddis(Stationnum);//�����ʼ�㵽ÿһ���˵����·������
	vector<int>Dtim(Stationnum);
	vector<int>Dlin(Stationnum);//��¼��ǰ�����һ�������ʲô
	vector<string>Dans;//���·�߽��
	for (int i = 1; i < Stationnum; i++)	//��������г�ʼ��
	{
		Ddis[i] = INT_MAX;
	}
	Ddis[findStation(start)] = 0;	//��ʼ���������
	Dtim[findStation(start)] = 0;
	while (Dvis[findStation(end)] != 1)	//���յ�û�б����ʱ������ѭ��
	{
		int	cur = Ddismin2(Ddis, Dvis);	//�ҵ���ǰ�������̵�·��
		Stations* sta = station[cur].nextStaion;
		while (sta)	//���¸ý�㵽�������ľ���
		{
			int nex = findStation(sta->name);
			if (Ddis[nex] > Ddis[cur] + road[findRoad(station[cur].name, station[nex].name)].equaltime)
			{
				Ddis[nex] = Ddis[cur] + road[findRoad(station[cur].name, station[nex].name)].equaltime;
				Dtim[nex] = Dtim[cur] + road[findRoad(station[cur].name, station[nex].name)].distance;
				Dlin[nex] = cur;
			}
			sta = sta->nextStaion;
		}
		Dvis[cur] = 1;
	}
	int	temp = findStation(end);
	while (temp != findStation(start))
	{
		Dans.push_back(station[temp].name);
		temp = Dlin[temp];
	}
	//Dans.insert(Dans.begin(), start);
	Dans.push_back(start);
	string	linenote = station[findStation(Dans[0])].belongs[0];
	outans.timans = Dans;
	outans.Otime = Ddis[findStation(end)];
	outans.timdist = Dtim[findStation(end)];
	outans.Tcostmoney = calculatemoney(double(outans.timdist) / 1000);
	for (int i = 0; i < Dans.size(); i++)
	{

		cout << Dans[Dans.size() - i - 1] << "->";
	}
	cout << endl;
	cout << "ʱ�����ȣ�" << endl;
	cout << "���þ���Ϊ��" << Dtim[findStation(end)] << endl;
	cout << "���ʱ��Ϊ��" << Ddis[findStation(end)] << endl;
	cout << "���軨��Ϊ��" << outans.Tcostmoney << endl;
}

void dijkstra3(string start, string end)
{
	vector<int>vis(Stationnum);
	vector<int>dis(Stationnum);
	vector<int>lin(Stationnum);
	vector<string>ans;
	for (int i = 1; i < Stationnum; i++)
	{
		dis[i] = INT_MAX;
	}
	dis[findStation(start)] = 0;
	while (vis[findStation(end)] != 1)
	{
		int cur = Ddismin(dis, vis);
		for (int i = 1; i < Stationnum; i++)
		{
			int nex = i;
			if (dis[nex] > dis[cur] + Map[cur][nex])
			{
				dis[nex] = dis[cur] + Map[cur][nex];
				lin[nex] = cur;
			}
			vis[cur] = 1;
		}
	}
	int	temp = findStation(end);
	while (temp != findStation(start))
	{
		ans.push_back(station[temp].name);
		temp = lin[temp];
	}
	ans.push_back(start);
	outans2.timans = ans;




	for (int i = 0; i < ans.size(); i++)
	{
		cout << ans[ans.size() - i - 1] << "->";
	}
}


int	Ddismin(vector<int>arr, vector<int>brr)
{
	int	temp = INT_MAX;
	int	ans = 0;
	for (int i = 1; i < arr.size(); i++)
	{
		if (arr[i] < temp && brr[i] != 1)
		{
			temp = arr[i];
			ans = i;
		}
	}
	return	ans;
}
int	Ddismin2(vector<double>arr, vector<int>brr)
{
	int	temp = INT_MAX;
	int	ans = 0;
	for (int i = 1; i < arr.size(); i++)
	{
		if (arr[i] < temp && brr[i] != 1)
		{
			temp = arr[i];
			ans = i;
		}
	}
	return	ans;
}

double	findspeed(string str)
{
	for (int i = 1; i < Sublinenum; i++)
	{
		if (subline[i].name == str)
			return	subline[i].speed;
	}
	return	-1;
}

string findbelong(string start, string end)
{
	unordered_map<string, int>hash;
	int	cur = findStation(start);
	int	nex = findStation(end);
	for (int i = 0; i < 10; i++)
	{
		hash[station[cur].belongs[i]]++;
	}
	for (int i = 0; i < 10; i++)
	{
		if (hash[station[nex].belongs[i]] > 0)
		{
			return	station[nex].belongs[i];
		}
	}
	return "";
}

//void dfs()
//{
//
//}
int calculatemoney(double n)
{
	if (n <= 6)
		return	3;
	else if (n > 6 && n <= 12)
		return	4;
	else if (n > 12 && n <= 22)
		return	5;
	else if (n > 22 && n <= 32)
		return	6;
	else
	{
		return	(n - 32) / 20 + 1 + 6;
	}

}

void initMap()
{
	for (int i = 1; i < Stationnum; i++)
	{
		for (int j = 1; j < Stationnum; j++)
		{
			if (findbelong(station[i].name, station[j].name) != "")
			{
				Map[i][j] = 1;
			}
			else
			{
				Map[i][j] = 9999;
			}
		}
	}
	/*for (int i = 1; i < Stationnum; i++)
	{
		for (int j = 2; j < Stationnum; j++)
		{
			cout << Map[i][j] << " ";
		}
		cout << endl;
	}*/
}

void insertroad(string start, string end, string length)
{
	if (findStation(end) == -1)	//û�д洢���վ��
	{
		station[insistnum].name = end;
		insistnum++;
	}
	int s = findStation(start);
	int e = findStation(end);
	insertStation(s, e);//����ǰһ�������ڽӱ�
	insertStation(e, s);

	road[staynum].from = start;
	road[staynum].to = end;
	road[staynum].distance = atoi(length.c_str());
	//road[cnt2].equaltime = road[cnt2].distance / findspeed(findbelong(station[formStation].name, station[lateStation].name));
	staynum++;
	road[staynum].to = start;
	road[staynum].from = end;
	road[staynum].distance = atoi(length.c_str());
	//road[cnt2].equaltime = road[cnt2].distance / findspeed(findbelong(station[formStation].name, station[lateStation].name));
	staynum++;


}

void button(int x, int y, int w, int h, TCHAR* text)
{
	setbkmode(TRANSPARENT);
	setfillcolor(LIGHTGREEN);
	fillroundrect(x, y, x + w, y + h, 10, 10);
	// ����ַ�����MBCS �ַ�����
	TCHAR s1[] = "����";
	settextstyle(30, 0, s1);
	TCHAR s[50] = "hello";

	int tx = x + (w - textwidth(text)) / 2;
	int ty = y + (h - textheight(text)) / 2;

	outtextxy(tx, ty, text);

}

void display()
{
	int	lengthcnt = 2;//��������
	int lengthlim = 35;//����λ
	//int	widthcnt = 0;//��������
	int	widthlim = 6;//����λ
	int width = 0;
	bool stopsignal = false;//ֹͣ��ӡ���··����־
	while (!stopsignal)
	{
		string templine = "";
		for (int i = outans.disans.size() - 1; i >= 0; i--)
		{
			if (width > 900)
			{
				lengthcnt++;
				width = 0;
			}
			if (i == outans.disans.size() - 1)
			{
				templine = findbelong(outans.disans[i], outans.disans[i - 1]);
				lengthcnt++;
				setbkmode(TRANSPARENT);
				setfillcolor(LIGHTRED);
				int	strlength = templine.size();
				fillroundrect(20, lengthlim * lengthcnt, 20 + strlength * 15, lengthlim * lengthcnt + 25, 10, 10);
				settextstyle(25, 0, "����");
				setbkmode(TRANSPARENT);
				settextcolor(WHITE);
				outtextxy(20, lengthlim * lengthcnt, templine.c_str());
				lengthcnt++;
				//widthcnt = 0;
			}	//�����ӡ������


			setbkmode(TRANSPARENT);
			setfillcolor(LIGHTBLUE);
			int	strlength = outans.disans[i].size();
			fillroundrect(width, lengthlim * lengthcnt, width + 13 * strlength, lengthlim * lengthcnt + 25, 10, 10);
			settextstyle(25, 0, "����");
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(width, lengthlim * lengthcnt, outans.disans[i].c_str());
			width += 13 * strlength + widthlim;
			//widthcnt++;

			if (i > 0 && findbelong(outans.disans[i], outans.disans[i - 1]) != templine)
			{
				templine = findbelong(outans.disans[i], outans.disans[i - 1]);
				lengthcnt++;
				setbkmode(TRANSPARENT);
				setfillcolor(LIGHTRED);
				int	strlength1 = templine.size();
				fillroundrect(20, lengthlim * lengthcnt, 20 + strlength1 * 15, lengthlim * lengthcnt + 25, 10, 10);
				settextstyle(25, 0, "����");
				setbkmode(TRANSPARENT);
				settextcolor(WHITE);
				outtextxy(20, lengthlim * lengthcnt, templine.c_str());
				lengthcnt++;
				//widthcnt = 0;
				width = 0;


				setbkmode(TRANSPARENT);
				setfillcolor(LIGHTBLUE);
				int	strlength = outans.disans[i].size();
				fillroundrect(width + 0, lengthlim * lengthcnt, width + 0 + 13 * strlength, lengthlim * lengthcnt + 25, 10, 10);
				settextstyle(25, 0, "����");
				setbkmode(TRANSPARENT);
				settextcolor(YELLOW);
				outtextxy(width + 0, lengthlim * lengthcnt, outans.disans[i].c_str());
				//widthcnt++;
				width += strlength * 13 + widthlim;
			}	//�����ӡ������

		}
		stopsignal = true;
	}
	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(700, 10, 700 + 300, 10 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 10, "�ܾ��룺");
	char grade[100] = "";
	sprintf(grade, "%d", outans.Odistance);
	outtextxy(800, 10, grade);

	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(700, 40, 700 + 300, 40 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 40, "Ԥ��ʱ�䣺");
	char grade1[100] = "";
	sprintf(grade1, "%d", outans.distime);
	outtextxy(825, 40, grade1);

	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(700, 70, 700 + 300, 70 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 70, "Ԥ�ƻ��ѣ�");
	char grade2[100] = "";
	sprintf(grade2, "%d", outans.Dcostmoney);
	outtextxy(825, 70, grade2);

	setbkmode(TRANSPARENT);
	setfillcolor(YELLOW);
	fillroundrect(200, 50, 200 + 210, 50 + 35, 10, 10);
	settextstyle(35, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(CYAN);
	outtextxy(200, 50, "��̾������");


	/*setbkmode(TRANSPARENT);
	setfillcolor(LIGHTBLUE);
	fillroundrect(10, 100, 10 + 75, 100 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	outtextxy(10, 100, "��ֱ��");*/
}


void display2()

{
	int	lengthcnt = 2;//��������
	int lengthlim = 35;//����λ
	//int	widthcnt = 0;//��������
	int	widthlim = 6;//����λ
	int width = 0;
	bool stopsignal = false;//ֹͣ��ӡ���··����־
	while (!stopsignal)
	{
		string templine = "";
		for (int i = outans.timans.size() - 1; i >= 0; i--)
		{
			if (width > 900)
			{
				lengthcnt++;
				width = 0;
			}
			if (i == outans.timans.size() - 1)
			{
				templine = findbelong(outans.timans[i], outans.timans[i - 1]);
				lengthcnt++;
				setbkmode(TRANSPARENT);
				setfillcolor(LIGHTRED);
				int	strlength = templine.size();
				fillroundrect(20, lengthlim * lengthcnt, 20 + strlength * 15, lengthlim * lengthcnt + 25, 10, 10);
				settextstyle(25, 0, "����");
				setbkmode(TRANSPARENT);
				settextcolor(WHITE);
				outtextxy(20, lengthlim * lengthcnt, templine.c_str());
				lengthcnt++;
				//widthcnt = 0;
			}	//�����ӡ������


			setbkmode(TRANSPARENT);
			setfillcolor(LIGHTBLUE);
			int	strlength = outans.timans[i].size();
			fillroundrect(width, lengthlim * lengthcnt, width + 13 * strlength, lengthlim * lengthcnt + 25, 10, 10);
			settextstyle(25, 0, "����");
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(width, lengthlim * lengthcnt, outans.timans[i].c_str());
			width += 13 * strlength + widthlim;
			//widthcnt++;

			if (i > 0 && findbelong(outans.timans[i], outans.timans[i - 1]) != templine)
			{
				templine = findbelong(outans.timans[i], outans.timans[i - 1]);
				lengthcnt++;
				setbkmode(TRANSPARENT);
				setfillcolor(LIGHTRED);
				int	strlength1 = templine.size();
				fillroundrect(20, lengthlim * lengthcnt, 20 + strlength1 * 15, lengthlim * lengthcnt + 25, 10, 10);
				settextstyle(25, 0, "����");
				setbkmode(TRANSPARENT);
				settextcolor(WHITE);
				outtextxy(20, lengthlim * lengthcnt, templine.c_str());
				lengthcnt++;
				//widthcnt = 0;
				width = 0;


				setbkmode(TRANSPARENT);
				setfillcolor(LIGHTBLUE);
				int	strlength = outans.timans[i].size();
				fillroundrect(width + 0, lengthlim * lengthcnt, width + 0 + 13 * strlength, lengthlim * lengthcnt + 25, 10, 10);
				settextstyle(25, 0, "����");
				setbkmode(TRANSPARENT);
				settextcolor(YELLOW);
				outtextxy(width + 0, lengthlim * lengthcnt, outans.timans[i].c_str());
				//widthcnt++;
				width += strlength * 13 + widthlim;
			}	//�����ӡ������

		}
		stopsignal = true;
	}
	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(700, 10, 700 + 300, 10 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 10, "�ܾ��룺");
	char grade[100] = "";
	sprintf(grade, "%d", outans.timdist);
	outtextxy(800, 10, grade);

	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(700, 40, 700 + 300, 40 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 40, "Ԥ��ʱ�䣺");
	char grade1[100] = "";
	sprintf(grade1, "%d", (int)outans.Otime);
	outtextxy(825, 40, grade1);

	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(700, 70, 700 + 300, 70 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 70, "Ԥ�ƻ��ѣ�");
	char grade2[100] = "";
	sprintf(grade2, "%d", outans.Tcostmoney);
	outtextxy(825, 70, grade2);

	setbkmode(TRANSPARENT);
	setfillcolor(MAGENTA);
	fillroundrect(200, 50, 200 + 210, 50 + 35, 10, 10);
	settextstyle(35, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTCYAN);
	outtextxy(200, 50, "���ʱ�����");


	/*setbkmode(TRANSPARENT);
	setfillcolor(LIGHTBLUE);
	fillroundrect(10, 100, 10 + 75, 100 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	outtextxy(10, 100, "��ֱ��");*/
}

void display3()
{
	int	lengthcnt = 2;//��������
	int lengthlim = 35;//����λ
	//int	widthcnt = 0;//��������
	int	widthlim = 6;//����λ
	int width = 0;
	bool stopsignal = false;//ֹͣ��ӡ���··����־
	while (!stopsignal)
	{
		string templine = "";
		for (int i = outans2.timans.size() - 1; i >= 0; i--)
		{
			if (width > 900)
			{
				lengthcnt++;
				width = 0;
			}
			if (i == outans2.timans.size() - 1)
			{
				templine = findbelong(outans2.timans[i], outans2.timans[i - 1]);
				lengthcnt++;
				setbkmode(TRANSPARENT);
				setfillcolor(LIGHTRED);
				int	strlength = templine.size();
				fillroundrect(20, lengthlim * lengthcnt, 20 + strlength * 15, lengthlim * lengthcnt + 25, 10, 10);
				settextstyle(25, 0, "����");
				setbkmode(TRANSPARENT);
				settextcolor(WHITE);
				outtextxy(20, lengthlim * lengthcnt, templine.c_str());
				lengthcnt++;
				//widthcnt = 0;
			}	//�����ӡ������


			setbkmode(TRANSPARENT);
			setfillcolor(LIGHTBLUE);
			int	strlength = outans2.timans[i].size();
			fillroundrect(width, lengthlim * lengthcnt, width + 13 * strlength, lengthlim * lengthcnt + 25, 10, 10);
			settextstyle(25, 0, "����");
			setbkmode(TRANSPARENT);
			settextcolor(YELLOW);
			outtextxy(width, lengthlim * lengthcnt, outans2.timans[i].c_str());
			width += 13 * strlength + widthlim;
			//widthcnt++;

			if (i > 0 && findbelong(outans2.timans[i], outans2.timans[i - 1]) != templine)
			{
				templine = findbelong(outans2.timans[i], outans2.timans[i - 1]);
				lengthcnt++;
				setbkmode(TRANSPARENT);
				setfillcolor(LIGHTRED);
				int	strlength1 = templine.size();
				fillroundrect(20, lengthlim * lengthcnt, 20 + strlength1 * 15, lengthlim * lengthcnt + 25, 10, 10);
				settextstyle(25, 0, "����");
				setbkmode(TRANSPARENT);
				settextcolor(WHITE);
				outtextxy(20, lengthlim * lengthcnt, templine.c_str());
				lengthcnt++;
				//widthcnt = 0;
				width = 0;


				setbkmode(TRANSPARENT);
				setfillcolor(LIGHTBLUE);
				int	strlength = outans2.timans[i].size();
				fillroundrect(width + 0, lengthlim * lengthcnt, width + 0 + 13 * strlength, lengthlim * lengthcnt + 25, 10, 10);
				settextstyle(25, 0, "����");
				setbkmode(TRANSPARENT);
				settextcolor(YELLOW);
				outtextxy(width + 0, lengthlim * lengthcnt, outans2.timans[i].c_str());
				//widthcnt++;
				width += strlength * 13 + widthlim;
			}	//�����ӡ������

		}
		stopsignal = true;
	}
	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(700, 10, 700 + 300, 10 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 10, "�ܾ��룺");
	/*char grade[100] = "";
	sprintf(grade, "%d", outans.timdist);
	outtextxy(800, 10, grade);*/

	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(700, 40, 700 + 300, 40 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 40, "Ԥ��ʱ�䣺");
	/*char grade1[100] = "";
	sprintf(grade1, "%d", (int)outans.Otime);
	outtextxy(825, 40, grade1);*/

	setbkmode(TRANSPARENT);
	setfillcolor(WHITE);
	fillroundrect(700, 70, 700 + 300, 70 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
	outtextxy(700, 70, "Ԥ�ƻ��ѣ�");
	/*char grade2[100] = "";
	sprintf(grade2, "%d", outans.Tcostmoney);
	outtextxy(825, 70, grade2);*/

	setbkmode(TRANSPARENT);
	setfillcolor(LIGHTGRAY);
	fillroundrect(200, 50, 200 + 210, 50 + 35, 10, 10);
	settextstyle(35, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(LIGHTCYAN);
	outtextxy(200, 50, "���ٻ��˲���");


	/*setbkmode(TRANSPARENT);
	setfillcolor(LIGHTBLUE);
	fillroundrect(10, 100, 10 + 75, 100 + 25, 10, 10);
	settextstyle(25, 0, "����");
	setbkmode(TRANSPARENT);
	settextcolor(YELLOW);
	outtextxy(10, 100, "��ֱ��");*/
}

bool showerror(string name)
{
	if (findStation(name) == -1)
	{
		HWND abc = GetHWnd();   //��ȡ���ھ��
		SetWindowText(abc, "Caicai:���ִ���");   //�޸Ĵ��ڱ��� 
		MessageBox(abc, "����������Ʋ����ڻ�ͣ��", "PiedpiperG", MB_OKCANCEL);  //���öԻ���
		return	true;
	}
	return	false;
}

void forbiddenstation(string name)
{
	int cur = findStation(name);
	Stations* sta = station[cur].nextStaion;
	while (sta)
	{
		int nex = findRoad(station[cur].name, sta->name);
		road[nex].ifuse = false;
		sta = sta->nextStaion;
	}
	station[0].nextStaion = emptystation.nextStaion;
	station[cur].nextStaion = station[0].nextStaion;

}

void forbiddenroad(string name)
{
	for (int i = 1; i < Stationnum; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			if (station[i].belongs[j] == name)
			{
				forbiddenstation(station[i].name);
				break;
			}
		}
	}
}