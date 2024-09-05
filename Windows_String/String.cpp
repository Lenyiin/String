#define _CRT_SECURE_NO_WARNINGS
#include "String.hpp"
using namespace std;
using namespace Lenyiin;


// ���Ա���
void test1()
{
	String s("abcdefghijklmn");

	// 1. [] �±����������
	for (size_t i = 0; i < s.size(); i++)
	{
		cout << s[i] << " ";
	}
	cout << endl;

	// 2. iterator
	String::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	// 3. const_iterator
	String::const_iterator cit = s.begin();
	while (cit != s.end())
	{
		cout << *cit << " ";
		++cit;
	}
	cout << endl;

	// 4. ��Χ for
	for (const auto& ch : s)
	{
		cout << ch << " ";
	}
	cout << endl;

	// 5. ��������� riterator
	String::riterator rit = s.rbegin();
	while (rit != s.rend())
	{
		cout << *rit << " ";
		--rit;
	}
	cout << endl;

	// 6. ��������� const_riterator
	String::const_riterator crit = s.rbegin();
	while (crit != s.rend())
	{
		cout << *crit << " ";
		--crit;
	}
	cout << endl;
}

void test2()
{
	// Ĭ�Ϲ��캯��
	String s1;
	// Ĭ���вι��캯��
	String s2("Hello Lenyiin");
	// �������캯��
	String s3(s2);

	// ��� << ����
	cout << "s1: " << s1 << endl;
	cout << "s2: " << s2 << endl;
	cout << "s3: " << s3 << endl;

	// ��ֵ = ���������
	s1 = s2;
	cout << "s1: " << s1 << endl;
}

void test3()
{
	String s1;

	// β��
	s1.push_back('H');
	s1.push_back('e');
	s1.push_back('l');
	s1.push_back('l');
	s1.push_back('o');
	cout << "s1: " << s1 << endl;

	// ���� size()	capacity()
	cout << s1.size() << " " << s1.capacity() << endl;

	// ׷��һ���ַ�
	s1.append(' ');
	// ׷��һ���ַ���
	s1.append("Lenyiin");
	cout << "s1: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;

	// +=
	s1 += " abc";
	cout << "s1: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;

	// ���� resize
	s1.resize(7);
	cout << "s1: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;

	// ���� reserve
	s1.reserve(20);
	cout << "s1: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;

	// += s
	String s2("aaa");
	s1 += s2;
	s1.append(s2);
	cout << "s: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;

	// insert
	s1.insert(1, "abc");
	cout << "s: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;
	s1.insert(6, s2);
	cout << "s: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;

	// ����βɾ
	s1.pop_back();
	cout << "s: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;

	// ���� erase
	s1.erase(10, 5);
	cout << "s: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;
	s1.erase(3);
	cout << "s: " << s1 << endl;
	cout << s1.size() << " " << s1.capacity() << endl;
}

void test4()
{
	String s1("aaaa");
	String s2("aabb");
	String s3("aaaa");
	String s4("abaa");
	String s5("abcd");

	if (s1 < s2)
	{
		cout << s1 << " < " << s2 << endl;
	}
	else
	{
		cout << s1 << " >= " << s2 << endl;
	}

	if (s4 > s2)
	{
		cout << s4 << " > " << s2 << endl;
	}
	else
	{
		cout << s4 << " <= " << s2 << endl;
	}

	if (s1 == s3)
	{
		cout << s1 << " == " << s2 << endl;
	}

	if (s1 != s2)
	{
		cout << s1 << " != " << s2 << endl;
	}
}

void test5()
{
	String s("abcd Lenyiin efghi Lenyiin jklmn");

	// �����ַ�
	size_t pos = s.find('b');
	if (pos != String::npos)
	{
		cout << "�ҵ������±���: " << pos << endl;
	}
	else
	{
		cout << "û�ҵ���" << endl;
	}

	// �����ַ���
	pos = s.find("Lenyiin");
	if (pos != String::npos)
	{
		cout << "�ҵ������±���: " << pos << endl;
	}
	else
	{
		cout << "û�ҵ���" << endl;
	}

	// ��������ַ�
	pos = s.rfind('x');
	if (pos != String::npos)
	{
		cout << "�ҵ������±���: " << pos << endl;
	}
	else
	{
		cout << "û�ҵ� x !" << endl;
	}

	// ��������ַ���
	pos = s.rfind("Lenyiin");
	if (pos != String::npos)
	{
		cout << "�ҵ������±���: " << pos << endl;
	}
	else
	{
		cout << "û�ҵ���" << endl;
	}

	// ��ȡ�ַ���
	String s2 = s.substr(5, 7);
	cout << "��ȡ�����ַ�����: " << s2 << endl;

	// ���� >> �����
	cout << "�������ַ�: ";
	String s3;
	cin >> s3;
	cout << "���������: " << s3 << endl;
}

int main()
{
	//test1();
	//test2();
	//test3();
	//test4();
	test5();

	return 0;
}