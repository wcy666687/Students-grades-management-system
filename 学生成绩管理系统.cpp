#include<iostream>
#include<cstring>
#include<iomanip>
#include<string>
#include<cstdlib>
#include<fstream>
#include<conio.h>
using namespace std;

static int xsshu = 0, kcshu = 5, xxshu = 0;
static int r = 0;


class xitong              //xitong抽象类
{
public:
	virtual void setname(string n) = 0;
	virtual void setid(string i) = 0;
	virtual string getname() = 0;
	virtual string getid() = 0;
	virtual void print() = 0;
	virtual ~xitong() {};
};

class xinxi              //xinxi类
{
public:
	xinxi(){ score = new double[kcshu]; }
	void setname(string n) { name = n; }
	void setid(string i) { id = i; }
	void setsco(double *g) {  for (int i = 0; i < kcshu; i++) score[i] = g[i]; }
	void setsco(double g, int i) { score[i] = g; }
	string getname() { return name; }
	string getid() { return id; }
	double *getsco() { return score; }
	double getsco(int i) { return score[i]; }
	friend bool operator ==(xinxi &xx1, xinxi &xx2);
	int num;
	void print()
	{
		cout <<num<<". "<<name <<" "<< id <<" ";
		for (int i = 0; i < kcshu; i++)
			cout <<"    "<< score[i];
		cout << endl;
	}
private:
	string name, id,cla;
	double *score;
};
xinxi xx[200];
bool operator ==(xinxi &xx1, xinxi &xx2)
{
	if (xx1.getname() == xx2.getname() && xx1.getid() == xx2.getid() && xx1.getsco() == xx2.getsco())
		return 1;
	else return 0;
}

class course;

class stu :public xinxi            //stu类
{
public:
	stu() { grade = new double[kcshu]; }
	~stu() {  }
	void setname(string n) {name = n; }
	void setid(string i) { id = i; }
	void setgrade(double *g);
	void setgrade(double g, int i);
	string getname() { return name; }
	string getid() { return id; }
	double getgrade(int i) { return grade[i]; }
	double getgpa();
	int getrank();
	void print()
	{
		cout <<num<<". "<< name <<" "<< id << "  ";
		for (int i = 0; i < kcshu; i++)
			cout << "    " << getgrade(i); 
		cout << setw(10) << getgpa() << setw(4) << getrank() << "/" << xsshu;
		cout << endl;
	}
	int num;
private:
	string name, id;
	double gpa;
	double *grade;
	int rank;
};
stu st[100];
void stu::setgrade(double *g)                    //转换绩点函数
{
	for (int i = 0; i < kcshu; i++)
	{
		if (g[i] >= 95) grade[i] = 4.0;
		else if (g[i] >= 90) grade[i] = 3.7;
		else if (g[i] >= 85) grade[i] = 3.3;
		else if (g[i] >= 80) grade[i] = 3.0;
		else if (g[i] >= 77) grade[i] = 2.7;
		else if (g[i] >= 73) grade[i] = 2.3;
		else if (g[i] >= 70) grade[i] = 2.0;
		else if (g[i] >= 67) grade[i] = 1.7;
		else if (g[i] >= 63) grade[i] = 1.3;
		else if (g[i] >= 60) grade[i] = 1.0;
		else grade[i] = 0.0;
	}
}
void stu::setgrade(double g, int i)
{
	if (g >= 95) grade[i] = 4.0;
	else if (g >= 90) grade[i] = 3.7;
	else if (g >= 85) grade[i] = 3.3;
	else if (g >= 80) grade[i] = 3.0;
	else if (g >= 77) grade[i] = 2.7;
	else if (g >= 73) grade[i] = 2.3;
	else if (g >= 70) grade[i] = 2.0;
	else if (g >= 67) grade[i] = 1.7;
	else if (g >= 63) grade[i] = 1.3;
	else if (g >= 60) grade[i] = 1.0;
	else grade[i] = 0;
}
int stu::getrank()                              //排名函数
{
	int r = 1;
	for (int i = 0; i < xsshu; i++)
		if (st[i].getgpa() > this->getgpa()) r++;
	return r;
}


class course               //course类
{
public:
	course() {};
	~course() {};
	void setcla(string c) { cla = c; }
	void setpoint(int p) { point = p; }
	string getcla() { return cla; }
	int getpoint() { return point; }
	double getmax();
	double getmin();
	double getave();
	double getrate();
	int num;
private:
	string cla;
	double max, min, ave,rate;
	int point;
};
double course::getmax()                 //获得最高分函数
{
	double m = 0;
	if (xxshu)
	{
		for (int i = 0; i < xxshu; i++)
			if (xx[i].getsco(num) > m)
				m = xx[i].getsco(num);
		return m;
	}
	else return 0;
}
double course::getmin()                 //获得最低分函数
{
	double m = 100;
	if (xxshu)
	{
		for (int i = 0; i < xxshu; i++)
			if (xx[i].getsco(num) < m)
				m = xx[i].getsco(num);
		return m;
	}
	else return 0;
}
double course::getave()                 //获得平均分函数
{
	double s = 0;
	if (xxshu)
	{
		for (int i = 0; i < xsshu; i++)
			s += xx[i].getsco(num);
		return s / xxshu;
	}
	else return 0;
}
double course::getrate()                //获得及格率函数
{
	double m=0.0;
	for (int i = 0; i < xsshu; i++)
		if (st[i].getgrade(num))
			m=m+1;
	return m / xsshu;
}
course cou[5];
double stu::getgpa()               //getgpa函数，计算学生绩点
{
	double s = 0.0, t = 0.0;
	for (int i = 0; i < kcshu; i++)
	{
		s += getgrade(i) * cou[i].getpoint(); t += cou[i].getpoint();
	}
	if (t)
		return s / t;
	else return 0.0;
}


void caidan1();    //函数声明
void caidan2();
void luru();
void luru1();
void xiugai();
void chaxun();
void tongji1();
void tongji2();
void shanchu();
void shuchu();

void caidan()                       //菜单
{
	cout << "*   *  * ***欢迎进入学生成绩管理系统！*** *  *   *" << endl;
	cout << "  请按数字键选择入口：(首次进入请按3从文件读入数据)" << endl;
	cout << "  1.我是学生" << endl; cout << "  2.我是教师" << endl;
	cout << "  3.从文件录入数据" << endl; cout << "  4.离开系统" << endl;
	if (r)
		switch (_getch())
		{
		case '1':caidan1(); break;
		case '2':caidan2(); break;
		case '3':luru1(); caidan(); break;
		case '4':exit(1);
		default:system("cls"); caidan();
		}
	else if (_getch() == '3') { luru1(); r++; caidan(); }
	else { system("cls"); caidan(); }
}
void caidan1()                               //学生菜单
{
	system("cls");
	string a, b; int flag = 0; stu st1;
	cout << "请输入姓名:";
	cin >> a;
	for (int i = 0; i < xsshu; i++)
		if (st[i].getname() == a) flag = 1;
	if (flag)
	{
		int k = 0;
		while (!k)
		{
			cout << endl << "请输入学号：";
			cin >> b;
			for (int i = 0; i < xsshu; i++)
				if (st[i].getid() == b) { k = 1; st1 = st[i]; }
			if (k) {
				for (int i = 0; i < kcshu; i++)
					cout << setw(12) << cou[i].getcla();
				cout << "    GPA    "<<" 排名" << endl;
				for (int i = 0; i < kcshu; i++)
					cout << setw(12) << st1.getgrade(i);
				cout <<"    "<< st1.getgpa() << "  " << st1.getrank() << "/" << xsshu << endl;
			}
			else cout << "学号错误！"<<endl ;
		}
	}
	else cout << "查无此人！"<<endl; 
	cout << "按任意键离开系统" << endl; system("pause");
}

void caidan2()                        //教师菜单
{
	system("cls");
	cout << "    请按下数字键进行如下操作：" << endl;
	cout << "1.  录入学生成绩" << endl;
	cout << "2.  修改学生成绩" << endl;
	cout << "3.  查询学生成绩" << endl;
	cout << "4.  统计某课程成绩情况" << endl;
	cout << "5.  统计所有学生绩点情况" << endl;
	cout << "6.  删除学生成绩" << endl;
	cout << "7.  离开系统(若要保存数据请从此处退出)" << endl;
	switch (_getch())
	{
	case '1':luru(); caidan2(); break;
	case '2':xiugai(); caidan2(); break;
	case '3':chaxun(); caidan2(); break;
	case '4':tongji1(); caidan2(); break;
	case '5':tongji2(); caidan2(); break;
	case '6': shanchu(); caidan2(); break;
	case '7': shuchu(); exit(1); break;
	default:system("cls"); caidan2();
	}
}

void luru1()                         //从文件录入函数
{
	string str; char a; double g[5];
	ifstream is("测试数据.txt", ios_base::in);
	if (is.good())
	{
		is >> xxshu;  xsshu = xxshu;
		for (int i = 0; i < xxshu; i++)
		{
			is >> str; xx[i].setname(str); st[i].setname(str);
			is >> str; xx[i].setid(str); st[i].setid(str);
			for (int j = 0; j < kcshu; j++)
				is >> g[j];
			xx[i].setsco(g); st[i].setgrade(g);
			xx[i].num=st[i].num=i;
		}
		cout << "已从文件录入数据！" << endl;
	}
	else {
		cout << "读入错误！"; system("pause");
	}
	is.close();
}

void luru()                           //手动录入函数
{
	system("cls");
	string a, b; double g[5], x; int flag = 0;
	cout << "请输入 姓名 学号："<<endl;
	cin >> a >> b;
	if (xxshu)
	{
		for (int i = 0; i < xxshu; i++)
			if (xx[i].getid() == b)
				flag = 1;
	}
	if (flag)
	{
		cout << "该学生成绩信息已存在！若要重新录入请选择修改" << endl; system("pause");
	}
	else 
	{
		xx[xxshu].setname(a); xx[xxshu].setid(b);
		st[xsshu].setname(a); st[xsshu].setid(b);
		for (int i = 0; i < kcshu; i++)
		{
			cout << cou[i].getcla() << " 成绩（百分制）：";
			cin >> x; while (x < 0 || x>100) { cout << "成绩有误！请重新输入" << endl; cin >> x; }
			g[i] = x;
		}
		xx[xxshu].setsco(g); st[xsshu].num=xx[xxshu].num = xxshu; st[xsshu].setgrade(g);
		xxshu++; xsshu++;
		cout << "录入成功！是否继续录入？（y/n）";
		if (_getch() == 'y') luru();
	}
}

void xiugai()                    //修改函数
{
	system("cls"); string a,b; int i,flag,j;
	cout << "输入要修改的学生姓名：";
	cin >> a;
	int k = 0;
	for ( i = 0; i < xxshu; i++)
		if (xx[i].getname() == a)
		{
			k++; break;
		}
	if (!k)
	{
		cout << "没有相关信息呀，是否更改名字继续查询？(y/n)" << endl;
		if (_getch() == 'y')
			xiugai();
	}
	else {
		cout << "序号 姓名   学生号    ";
		for (j = 0; j < kcshu; j++)
			cout << setw(8) << cou[j].getcla();
		cout << endl;
		xx[i].print();
		cout << "请按数字键选择要修改的项：1.姓名 2.学号 3.成绩" << endl;
		flag = 0;
		switch (_getch())
		{
		case'1':
			do {
				cout << "请输入修改后的姓名："; cin >> b;
				st[i].setname(b); xx[i].setname(b);
				for (int j = 0; j < xxshu; j++)
					if (xx[j] == xx[i]&&j!=i) {
						cout << "信息已存在！请重新输入" << endl; flag = 1;
					}
			} while (flag == 1);
			cout << "是否继续修改？（y/n）";
			if (_getch() == 'y') xiugai(); break;
		case'2':
			cout << "请输入修改后的学号："; cin >> b;
			for (i = 0; i < xsshu; i++)
				if (st[i].getid() == b) flag = 1;
			if (flag) { cout << "该学号已存在！"; system("pause"); break; }
			else st[i].setid(b); xx[i].setid(b);
			cout << "是否继续修改？（y/n）";
			if (_getch() == 'y') xiugai(); break;
		case'3':
			cout << "请选择要修改的课程：1.微积分 2.计算机 3.大学物理 4.英语 5.体育" << endl;
			cin >> i;
			cout << "请输入修改后的成绩（百分制）："; double x;
			cin >> x; while (x < 0 || x>100) { cout << "成绩有误！请重新输入" << endl; cin >> x; }
			st[i].setgrade(x, i - 1); xx[i].setsco(x, i - 1);
			cout << "是否继续修改？（y/n）";
			if (_getch() == 'y') xiugai(); break;
		}
	}
}

void chaxun()                     //查询函数
{
	system("cls");
	string a; int i,flag = 0;
	cout << "请输入要查询的学生姓名：";
	cin >> a;
	for ( i = 0; i < xsshu; i++)
		if (st[i].getname() == a) {	flag = 1; break;}
	if(flag)
	{
		cout << "序号 姓名   学生号    ";
		for (int j = 0; j < kcshu; j++)
			cout << setw(9) << cou[j].getcla();
		cout << "  GPA  " << "排名"<<endl;
		st[i].print();
		cout << "是否继续查询（y/n）";
		if (_getch() == 'y') chaxun();
	}
	else {
		cout << "未找到该学生信息！"; system("pause");
	}
}
	
void tongji1()             //统计课程情况函数
{
	system("cls");
	string a; int i,flag=0;
	cout << "请输入课程名：";
	cin >> a;
	for (i = 0; i < 5; i++)
		if (a == cou[i].getcla())
		{
			flag = 1; break;
		}
	if (flag) {
		cout << "课程号：" << cou[i].num << endl;
		cout << "学分：" << cou[i].getpoint() << endl;
		cout << "最高分：" << cou[i].getmax() << endl;
		cout << "最低分：" << cou[i].getmin() << endl;
		cout << "平均分：" << cou[i].getave() << endl;
		cout << "及格率：" << cou[i].getrate() << endl;
		cout << "是否继续统计？(y/n)";
		if (_getch() == 'y') tongji1();
	}
	else { cout << "无此课程！"; system("pause"); }
}

void tongji2()                 //统计学生绩点函数
{
	system("cls");
	int b = 0, k = xsshu, m = k - 1; stu d;
	cout << "名次  姓名       学生号      GPA  "<<endl;
	while (b < m)
	{
		int j = m - 1; m = 0;
		for (int i = b; i <= j; i++)
			if ((st[i].getrank()>st[i + 1].getrank())
				|| (st[i].getrank() == st[i + 1].getrank()&& st[i].getid()> st[i + 1].getid()))
			{
				d = st[i]; st[i] = st[i + 1]; st[i + 1] = d; m = i;
			}
		j = b + 1; b = 0;
		for (int i = m; i >= j; i--)
			if ((st[i - 1].getrank()>st[i].getrank())
				|| (st[i - 1].getrank() == st[i].getrank() && st[i - 1].getid()> st[i].getid()))
			{
				d = st[i]; st[i] = st[i - 1]; st[i - 1] = d; b = i;
			}
	}
	for (int i = 0; i < xsshu; i++)
		cout << st[i].getrank()<<"."<<std::left<<st[i].getname() <<std::right<<setw(14)<< st[i].getid() << "    " << st[i].getgpa()  << endl;
	cout << "按任意键返回主菜单"; system("pause");
}

void shanchu()                //删除函数
{
	system("cls");
	string b; int flag = 0, i;
	cout << "序号 姓名   学生号    ";
	for (i = 0; i < kcshu; i++)
		cout << setw(8) << cou[i].getcla();
	cout << endl;
	for (i = 0; i < xxshu; i++)
		xx[i].print();
	cout << "请输入要删除的信息序号:";
	int a; cin >> a;
	while (a<0 || a>xxshu - 1) { cout << "请重新输入："; cin >> a; }
	for (int i = 0; i < xxshu; i++)
		if (a ==xx[i].num)
		{
			if (a < xxshu - 1)
			{
				for (int j = a; j < xxshu - 1; j++)
				{
					xx[j] = xx[j + 1]; xx[j].num--;
				}
				xxshu--;
			}
			else xxshu--;
		}
	for (int i = 0; i < xsshu; i++)
		if (a == st[i].num)
		{
			if (a < xsshu - 1)
			{
				for (int j = a; j < xsshu - 1; j++)
				{
					st[j] = st[j + 1]; st[j].num--;
				}
				xsshu--;
			}
			else xsshu--;
		}
	cout << "是否继续删除？(y/n)";
	if (_getch() == 'y') shanchu();

}

void shuchu()                        //数据输出到文件函数
{
	ofstream tfile("测试数据.txt");
	tfile << xxshu << endl;
	for (int i = 0; i < xxshu; i++)
	{
		tfile << xx[i].getname() << " " << xx[i].getid();
		for (int j = 0; j < kcshu; j++)
			tfile << " "<<xx[i].getsco(j);
		tfile << endl;
	}
	tfile.close();
}

void main()                 
{
	system("color 70");
	cou[0].setcla("微积分"); cou[0].setpoint(5); cou[0].num = 0;           //设置五门课程
	cou[1].setcla("计算机"); cou[1].setpoint(4); cou[1].num = 1;
	cou[2].setcla("大学物理"); cou[2].setpoint(3); cou[2].num = 2;
	cou[3].setcla("英语"); cou[3].setpoint(2); cou[3].num = 3;
	cou[4].setcla("体育"); cou[4].setpoint(1); cou[4].num = 4;
	caidan();
}
