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


class xitong              //xitong������
{
public:
	virtual void setname(string n) = 0;
	virtual void setid(string i) = 0;
	virtual string getname() = 0;
	virtual string getid() = 0;
	virtual void print() = 0;
	virtual ~xitong() {};
};

class xinxi              //xinxi��
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

class stu :public xinxi            //stu��
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
void stu::setgrade(double *g)                    //ת�����㺯��
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
int stu::getrank()                              //��������
{
	int r = 1;
	for (int i = 0; i < xsshu; i++)
		if (st[i].getgpa() > this->getgpa()) r++;
	return r;
}


class course               //course��
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
double course::getmax()                 //�����߷ֺ���
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
double course::getmin()                 //�����ͷֺ���
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
double course::getave()                 //���ƽ���ֺ���
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
double course::getrate()                //��ü����ʺ���
{
	double m=0.0;
	for (int i = 0; i < xsshu; i++)
		if (st[i].getgrade(num))
			m=m+1;
	return m / xsshu;
}
course cou[5];
double stu::getgpa()               //getgpa����������ѧ������
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


void caidan1();    //��������
void caidan2();
void luru();
void luru1();
void xiugai();
void chaxun();
void tongji1();
void tongji2();
void shanchu();
void shuchu();

void caidan()                       //�˵�
{
	cout << "*   *  * ***��ӭ����ѧ���ɼ�����ϵͳ��*** *  *   *" << endl;
	cout << "  �밴���ּ�ѡ����ڣ�(�״ν����밴3���ļ���������)" << endl;
	cout << "  1.����ѧ��" << endl; cout << "  2.���ǽ�ʦ" << endl;
	cout << "  3.���ļ�¼������" << endl; cout << "  4.�뿪ϵͳ" << endl;
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
void caidan1()                               //ѧ���˵�
{
	system("cls");
	string a, b; int flag = 0; stu st1;
	cout << "����������:";
	cin >> a;
	for (int i = 0; i < xsshu; i++)
		if (st[i].getname() == a) flag = 1;
	if (flag)
	{
		int k = 0;
		while (!k)
		{
			cout << endl << "������ѧ�ţ�";
			cin >> b;
			for (int i = 0; i < xsshu; i++)
				if (st[i].getid() == b) { k = 1; st1 = st[i]; }
			if (k) {
				for (int i = 0; i < kcshu; i++)
					cout << setw(12) << cou[i].getcla();
				cout << "    GPA    "<<" ����" << endl;
				for (int i = 0; i < kcshu; i++)
					cout << setw(12) << st1.getgrade(i);
				cout <<"    "<< st1.getgpa() << "  " << st1.getrank() << "/" << xsshu << endl;
			}
			else cout << "ѧ�Ŵ���"<<endl ;
		}
	}
	else cout << "���޴��ˣ�"<<endl; 
	cout << "��������뿪ϵͳ" << endl; system("pause");
}

void caidan2()                        //��ʦ�˵�
{
	system("cls");
	cout << "    �밴�����ּ��������²�����" << endl;
	cout << "1.  ¼��ѧ���ɼ�" << endl;
	cout << "2.  �޸�ѧ���ɼ�" << endl;
	cout << "3.  ��ѯѧ���ɼ�" << endl;
	cout << "4.  ͳ��ĳ�γ̳ɼ����" << endl;
	cout << "5.  ͳ������ѧ���������" << endl;
	cout << "6.  ɾ��ѧ���ɼ�" << endl;
	cout << "7.  �뿪ϵͳ(��Ҫ����������Ӵ˴��˳�)" << endl;
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

void luru1()                         //���ļ�¼�뺯��
{
	string str; char a; double g[5];
	ifstream is("��������.txt", ios_base::in);
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
		cout << "�Ѵ��ļ�¼�����ݣ�" << endl;
	}
	else {
		cout << "�������"; system("pause");
	}
	is.close();
}

void luru()                           //�ֶ�¼�뺯��
{
	system("cls");
	string a, b; double g[5], x; int flag = 0;
	cout << "������ ���� ѧ�ţ�"<<endl;
	cin >> a >> b;
	if (xxshu)
	{
		for (int i = 0; i < xxshu; i++)
			if (xx[i].getid() == b)
				flag = 1;
	}
	if (flag)
	{
		cout << "��ѧ���ɼ���Ϣ�Ѵ��ڣ���Ҫ����¼����ѡ���޸�" << endl; system("pause");
	}
	else 
	{
		xx[xxshu].setname(a); xx[xxshu].setid(b);
		st[xsshu].setname(a); st[xsshu].setid(b);
		for (int i = 0; i < kcshu; i++)
		{
			cout << cou[i].getcla() << " �ɼ����ٷ��ƣ���";
			cin >> x; while (x < 0 || x>100) { cout << "�ɼ���������������" << endl; cin >> x; }
			g[i] = x;
		}
		xx[xxshu].setsco(g); st[xsshu].num=xx[xxshu].num = xxshu; st[xsshu].setgrade(g);
		xxshu++; xsshu++;
		cout << "¼��ɹ����Ƿ����¼�룿��y/n��";
		if (_getch() == 'y') luru();
	}
}

void xiugai()                    //�޸ĺ���
{
	system("cls"); string a,b; int i,flag,j;
	cout << "����Ҫ�޸ĵ�ѧ��������";
	cin >> a;
	int k = 0;
	for ( i = 0; i < xxshu; i++)
		if (xx[i].getname() == a)
		{
			k++; break;
		}
	if (!k)
	{
		cout << "û�������Ϣѽ���Ƿ�������ּ�����ѯ��(y/n)" << endl;
		if (_getch() == 'y')
			xiugai();
	}
	else {
		cout << "��� ����   ѧ����    ";
		for (j = 0; j < kcshu; j++)
			cout << setw(8) << cou[j].getcla();
		cout << endl;
		xx[i].print();
		cout << "�밴���ּ�ѡ��Ҫ�޸ĵ��1.���� 2.ѧ�� 3.�ɼ�" << endl;
		flag = 0;
		switch (_getch())
		{
		case'1':
			do {
				cout << "�������޸ĺ��������"; cin >> b;
				st[i].setname(b); xx[i].setname(b);
				for (int j = 0; j < xxshu; j++)
					if (xx[j] == xx[i]&&j!=i) {
						cout << "��Ϣ�Ѵ��ڣ�����������" << endl; flag = 1;
					}
			} while (flag == 1);
			cout << "�Ƿ�����޸ģ���y/n��";
			if (_getch() == 'y') xiugai(); break;
		case'2':
			cout << "�������޸ĺ��ѧ�ţ�"; cin >> b;
			for (i = 0; i < xsshu; i++)
				if (st[i].getid() == b) flag = 1;
			if (flag) { cout << "��ѧ���Ѵ��ڣ�"; system("pause"); break; }
			else st[i].setid(b); xx[i].setid(b);
			cout << "�Ƿ�����޸ģ���y/n��";
			if (_getch() == 'y') xiugai(); break;
		case'3':
			cout << "��ѡ��Ҫ�޸ĵĿγ̣�1.΢���� 2.����� 3.��ѧ���� 4.Ӣ�� 5.����" << endl;
			cin >> i;
			cout << "�������޸ĺ�ĳɼ����ٷ��ƣ���"; double x;
			cin >> x; while (x < 0 || x>100) { cout << "�ɼ���������������" << endl; cin >> x; }
			st[i].setgrade(x, i - 1); xx[i].setsco(x, i - 1);
			cout << "�Ƿ�����޸ģ���y/n��";
			if (_getch() == 'y') xiugai(); break;
		}
	}
}

void chaxun()                     //��ѯ����
{
	system("cls");
	string a; int i,flag = 0;
	cout << "������Ҫ��ѯ��ѧ��������";
	cin >> a;
	for ( i = 0; i < xsshu; i++)
		if (st[i].getname() == a) {	flag = 1; break;}
	if(flag)
	{
		cout << "��� ����   ѧ����    ";
		for (int j = 0; j < kcshu; j++)
			cout << setw(9) << cou[j].getcla();
		cout << "  GPA  " << "����"<<endl;
		st[i].print();
		cout << "�Ƿ������ѯ��y/n��";
		if (_getch() == 'y') chaxun();
	}
	else {
		cout << "δ�ҵ���ѧ����Ϣ��"; system("pause");
	}
}
	
void tongji1()             //ͳ�ƿγ��������
{
	system("cls");
	string a; int i,flag=0;
	cout << "������γ�����";
	cin >> a;
	for (i = 0; i < 5; i++)
		if (a == cou[i].getcla())
		{
			flag = 1; break;
		}
	if (flag) {
		cout << "�γ̺ţ�" << cou[i].num << endl;
		cout << "ѧ�֣�" << cou[i].getpoint() << endl;
		cout << "��߷֣�" << cou[i].getmax() << endl;
		cout << "��ͷ֣�" << cou[i].getmin() << endl;
		cout << "ƽ���֣�" << cou[i].getave() << endl;
		cout << "�����ʣ�" << cou[i].getrate() << endl;
		cout << "�Ƿ����ͳ�ƣ�(y/n)";
		if (_getch() == 'y') tongji1();
	}
	else { cout << "�޴˿γ̣�"; system("pause"); }
}

void tongji2()                 //ͳ��ѧ�����㺯��
{
	system("cls");
	int b = 0, k = xsshu, m = k - 1; stu d;
	cout << "����  ����       ѧ����      GPA  "<<endl;
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
	cout << "��������������˵�"; system("pause");
}

void shanchu()                //ɾ������
{
	system("cls");
	string b; int flag = 0, i;
	cout << "��� ����   ѧ����    ";
	for (i = 0; i < kcshu; i++)
		cout << setw(8) << cou[i].getcla();
	cout << endl;
	for (i = 0; i < xxshu; i++)
		xx[i].print();
	cout << "������Ҫɾ������Ϣ���:";
	int a; cin >> a;
	while (a<0 || a>xxshu - 1) { cout << "���������룺"; cin >> a; }
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
	cout << "�Ƿ����ɾ����(y/n)";
	if (_getch() == 'y') shanchu();

}

void shuchu()                        //����������ļ�����
{
	ofstream tfile("��������.txt");
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
	cou[0].setcla("΢����"); cou[0].setpoint(5); cou[0].num = 0;           //�������ſγ�
	cou[1].setcla("�����"); cou[1].setpoint(4); cou[1].num = 1;
	cou[2].setcla("��ѧ����"); cou[2].setpoint(3); cou[2].num = 2;
	cou[3].setcla("Ӣ��"); cou[3].setpoint(2); cou[3].num = 3;
	cou[4].setcla("����"); cou[4].setpoint(1); cou[4].num = 4;
	caidan();
}
