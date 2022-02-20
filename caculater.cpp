#include <string>
#include <vector>
#include <stack>
#include <iostream>
using namespace std;
//#define TEST_FOR_NUM
#define TEST_FOR_CACULATER
int num_after(string x, bool first=0,int start=0);//first��һ�������������һ��
int ston(string x)//
{
	return 1;
}

string ntos(double x)//
{
	return "1";
}

int oper(char x)
{
	if (x == '-' || x == '+')
		return 1;
	else if (x == '*' || x == '/')
		return 2;
	return 0;
}

bool num_char(char x)
{
	if (x < '0' || x>'9')
		return false;
	return true;
}

bool num(string x)//Ϊ�ղ�����
{
	if (x.empty())//corner case
		return false;
	int dot = x.find('.');
	if (dot > x.length())//int
	{
		for (int i = 0; i < x.length(); i++)
			if (!num_char(x[i]))
				return false;
		return true;
	}
	else//double(һλС��)
	{
		if (dot == x.length() - 2 && num_char(x[dot + 1]))
		{
			for (int i = 0; i < dot; i++)
				if (!num_char(x[i]))
					return false;
			return true;
		}
		return false;
	}
}

int after_num(string x,bool first,int start)
//�����string��ͷ�Ƿ���һ�����ֲ����ظ����ֺ��������
//first=1��ʾ�����и��ţ�
//�����ǺϷ������֣�����-1
{
	int i = start;
	if (x[i] == '-')
	{
		if (!first)
			return -1;
		i += 1;
		while (i < x.length() && (num_char(x[i]) || x[i] == '.')) i++;
		if (!num(x.substr(start+1,i-1-start)))
			return -1;
		return i;
	}
	else
	{
		
		while (i < x.length() && (num_char(x[i]) || x[i] == '.')) i++;
		if (!num(x.substr(start, i-start)))
			return -1;
		return i;
	}	
}

int after_brac(string x,int start)//���ţ�������after_num����,����ֵ�Ǻ����ŵ�����
{
	int count = 1;
	for (int i = start + 1; i < x.length(); i++)
	{
		if (x[i] == '(')
			count++;
		else if (x[i] == ')')
		{
			count--;
			if (count == 0)
				return i;
		}
	}
	return -1;
}



string caculater(string x)
{
	bool nu = true;
	bool fi = true;
	vector<string> unit;
	stack<char> st;
	for (int i = 0; i < x.length();)
	{
		if (nu)//���Ƿ�����
		{
			if (x[i] == '-' && x[i+1]=='(')//����
			{
				if (fi)//�����ţ�ִ�в���
				{
					nu = false;
					fi = false;
					int start = i + 1;//ƥ�����ŵ���ʼ
					int last = after_brac(x, start);
					if (last == -1)
						return "Bracket mismatch!";
					i = last + 1;//ָ����һ��!
					string res = caculater(x.substr(start + 1, last - start - 1));
					res = "-" + res;
					unit.push_back(res);
					continue;
				}
				else//��������
				{
					return "Minus misuse!";
				}
			}
			else if (x[i]=='(')//�޸���
			{
				fi = false;//֮����������
				nu = false;
				int start = i ;//ƥ�����ŵ���ʼ
				int last = after_brac(x, start);
				if (last == -1)
					return "Bracket mismatch!";
				i = last + 1;//ָ����һ��!
				string res = caculater(x.substr(start + 1, last - start - 1));
				unit.push_back(res);
				continue;
			}
		}

		if (nu && fi)//����ֱ�Ӵ�����,�ų����������
		{
			int pos = i;
			i = after_num(x, 1, i);
			if (i ==-1)
				return "Operator misuse";
			unit.push_back(x.substr(pos,i-pos));
			nu = false;
			fi = false;
			continue;
		}
		else if (nu && !fi)
		{
			int pos = i;
			i = after_num(x, 0, i);
			if (i ==-1)
				return "Operator misuse";
			unit.push_back(x.substr(pos,i-pos));
			nu = false;
			continue;
		}
		//��������
		if (!nu)
		{
			nu = true;
			if (!oper(x[i]))
				return "Operator misuse";
			if (st.empty()||oper(x[i])>= oper(st.top()))
			{
				st.push(x[i]);
				i += 1;
				continue;
			}
			else
			{
				while (!st.empty())
				{
					unit.push_back(string(1, st.top()));
					st.pop();
				}
				st.push(x[i]);
				i += 1;
				continue;
			}
		}
	}

	while (!st.empty())
	{
		unit.push_back(string(1, st.top()));
		st.pop();
	}

	string res;
	for (int j = 0; j < unit.size(); j++)
	{
		res += unit[j];
		res += " ";
	}
	return res;
}



int main()
{
#ifdef TEST_FOR_NUM
	cout << num("") << endl;//0
	cout << num("123") << endl;
	cout << num("123.4") << endl;
	cout << num("123.45") << endl;//0
	cout << num("0.0") << endl;
	cout << num("0.0.") << endl;//0
	cout << num("0") << endl;
	cout << num("22.2.2") << endl;//0
#endif

#ifdef TEST_FOR_CACULATER
	cout << "1 " << caculater("1") << endl;
	cout << "1 " << caculater("1+1") << endl;
	cout << "0 " << caculater("!") << endl;
	cout << "1 " << caculater("-1") << endl;
	cout << "1 " << caculater("1+(1+1)") << endl;
	cout << "0 " << caculater("1+)1") << endl;
	cout << "0 " << caculater("1++1") << endl;
	cout << "1 " << caculater("1*2+3/4") << endl;
	cout << "0 " << caculater("1++") << endl;
#endif
}