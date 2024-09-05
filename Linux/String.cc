#include "String.hpp"
using namespace std;
using namespace Lenyiin;

// 测试遍历
void test1()
{
    String s("abcdefghijklmn");

    // 1. [] 下标运算符访问
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

    // 4. 范围 for
    for (const auto &ch : s)
    {
        cout << ch << " ";
    }
    cout << endl;

    // 5. 反向迭代器 riterator
    String::riterator rit = s.rbegin();
    while (rit != s.rend())
    {
        cout << *rit << " ";
        --rit;
    }
    cout << endl;

    // 6. 反向迭代器 const_riterator
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
    // 默认构造函数
    String s1;
    // 默认有参构造函数
    String s2("Hello Lenyiin");
    // 拷贝构造函数
    String s3(s2);

    // 输出 << 重载
    cout << "s1: " << s1 << endl;
    cout << "s2: " << s2 << endl;
    cout << "s3: " << s3 << endl;

    // 赋值 = 运算符重载
    s1 = s2;
    cout << "s1: " << s1 << endl;
}

void test3()
{
    String s1;

    // 尾插
    s1.push_back('H');
    s1.push_back('e');
    s1.push_back('l');
    s1.push_back('l');
    s1.push_back('o');
    cout << "s1: " << s1 << endl;

    // 测试 size()	capacity()
    cout << s1.size() << " " << s1.capacity() << endl;

    // 追加一个字符
    s1.append(' ');
    // 追加一个字符串
    s1.append("Lenyiin");
    cout << "s1: " << s1 << endl;
    cout << s1.size() << " " << s1.capacity() << endl;

    // +=
    s1 += " abc";
    cout << "s1: " << s1 << endl;
    cout << s1.size() << " " << s1.capacity() << endl;

    // 测试 resize
    s1.resize(7);
    cout << "s1: " << s1 << endl;
    cout << s1.size() << " " << s1.capacity() << endl;

    // 测试 reserve
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

    // 测试尾删
    s1.pop_back();
    cout << "s: " << s1 << endl;
    cout << s1.size() << " " << s1.capacity() << endl;

    // 测试 erase
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

    // 查找字符
    size_t pos = s.find('b');
    if (pos != String::npos)
    {
        cout << "找到啦！下标是: " << pos << endl;
    }
    else
    {
        cout << "没找到！" << endl;
    }

    // 查找字符串
    pos = s.find("Lenyiin");
    if (pos != String::npos)
    {
        cout << "找到啦！下标是: " << pos << endl;
    }
    else
    {
        cout << "没找到！" << endl;
    }

    // 反向查找字符
    pos = s.rfind('x');
    if (pos != String::npos)
    {
        cout << "找到啦！下标是: " << pos << endl;
    }
    else
    {
        cout << "没找到 x !" << endl;
    }

    // 反向查找字符串
    pos = s.rfind("Lenyiin");
    if (pos != String::npos)
    {
        cout << "找到啦！下标是: " << pos << endl;
    }
    else
    {
        cout << "没找到！" << endl;
    }

    // 截取字符串
    String s2 = s.substr(5, 7);
    cout << "截取到的字符串是: " << s2 << endl;

    // 测试 >> 运算符
    cout << "请输入字符: ";
    String s3;
    cin >> s3;
    cout << "你输入的是: " << s3 << endl;
}

int main()
{
    // test1();
    // test2();
    // test3();
    // test4();
    test5();

    return 0;
}