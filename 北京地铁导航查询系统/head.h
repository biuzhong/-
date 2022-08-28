#include<iostream>
#include<stdlib.h>
#include<string>
#include<fstream>
#include <sstream>    //ʹ��istringstream����Ҫ��ͷ�ļ� 
#include <cassert>
#include<queue>
#include<vector>
#include<time.h>
#include<graphics.h>
#include<conio.h>
#include<easyx.h>
#include<windows.h>
#include<mmsystem.h>
#include <unordered_map>
using	namespace std;
/*�����ڽӱ���Ϊ�洢�ṹ
	����վ��Station�͵�·Road���ֽṹ��*/
	//վ��ṹ������:
int	Stationnum = 356;
int insistnum = 352;
struct Stations
{
	string name;	//վ������
	string belongs[20];//������·������վ�Ļ����ڶ�����·��
	Stations* nextStaion;//ָ����һվ��ָ�루����վ�����ж����һվ��
}station[500];
Stations emptystation;

//�������ٻ�����ͼ
vector<vector<int>>Map(Stationnum, vector<int>(Stationnum));

//��·�ṹ������:
int	Roadnum = 800;
int staynum = 796;
struct Roads
{
	bool ifuse = true;
	string	from;	//��������
	string	to;		//������ȥ
	string  belong;	//������·
	double	distance;	//��·����
	double	equaltime;	//����ʱ��
}road[5000];

int	Sublinenum = 30;
//��¼������·�ٶ�
struct Sublines
{
	string	name;
	int		speed;
}subline[35];

//��¼����ʱ�ķ�ʽ
struct pos
{
	string	Loc;	//����λ��
	int	Distance;//�г̾���
	int	Changetime;//���˴���
	int	Costtime;//����ʱ��
	vector<string>Rember;//��¼;���ص�
};

//�洢����Ľṹ��
struct Outans
{
	vector<string>disans;	//���·�̽������
	vector<string>timans;	//���ʱ��������
	int	Odistance;			//���·�̾���
	int distime;			//���·��ʱ��
	double Otime;			//���ʱ��ʱ��
	int timdist;			//���ʱ�����
	int	Dcostmoney;			//���·�̻���
	int Tcostmoney;			//���ʱ�仨��
}outans, outans2;




//��ʼ���ڽӱ�͵�·
void	readfile1();
//��ʼ��������·���ٶȺ�ʱ��
void	readfile2();
//Ѱ�ҵ���վ�ı��
int findStation(string str);
//Ѱ�ҵ���·�ı��
int	findRoad(string start, string end);
//�����ڽӱ�������
void insertStation(int start, int end);
//��ӡ�ڽӱ�
void print1();
//��ӡ��·
void print2();
//���Ѹ����������
void bfs(string start, string end);
//���·������
void dijkstra(string start, string end);
//���ʱ������
void dijkstra2(string start, string end);
//���ٻ�������
void dijkstra3(string start, string end);
//���·����������������С�㺯��
int	Ddismin(vector<int>arr, vector<int>brr);
int	Ddismin2(vector<double>arr, vector<int>brr);
//������·��Ӧ���ٶ�
double	findspeed(string str);
//���ص�·��������·
string findbelong(string start, string end);
//���ٻ���·��
void dfs(string start, string end);
//easyx����
void button(int x, int y, int w, int h, TCHAR* text);
//չʾ����·��·��
void display();
//չʾ����ʱ��·��
void display2();
//չʾ���ٻ���·��
void display3();
//������̻��ѵ�Ǯ
int calculatemoney(double n);
//��������
bool showerror(string name);
//ͣ��վ��
void forbiddenstation(string name);
//ͣ����·
void forbiddenroad(string name);
//��ʼ��Map
void initMap();
//�����·
void insertroad(string start, string end, string length);
