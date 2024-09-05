#pragma once

#include <iostream>
#include <cassert>
#include <cstring>

namespace Lenyiin
{
	// 实现一个支持增删查改的 string
	class String
	{
	public:
		// 迭代器
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef char* riterator;
		typedef const char* const_riterator;

		iterator begin()	// 返回首地址
		{
			return _str;
		}

		iterator end()	// 返回尾地址
		{
			return _str + _size;
		}

		const_iterator begin() const
		{
			return _str;
		}

		const_iterator end() const
		{
			return _str + _size;
		}

		riterator rbegin()
		{
			return _str + _size - 1;
		}

		riterator rend()
		{
			return _str - 1;
		}

		const_riterator rbegin() const
		{
			return _str + _size - 1;
		}

		const_riterator rend() const
		{
			return _str - 1;
		}

	public:
		//// 默认构造函数：创建一个空字符串
		//String()
		//	: _str(nullptr), _size(0), _capacity(0)
		//{
		//}

		//// 带参数的构造函数：从C风格字符串创建String对象
		//String(const char* str) {
		//	if (str) {
		//		_size = _capacity = strlen(str);
		//		_str = new char[_size + 1]; // 分配内存，+1是为了存储终止符'\0'
		//		strcpy(_str, str);           // 将字符串内容复制到data指向的内存
		//	}
		//	else {
		//		_str = nullptr;
		//		_size = _capacity = 0;
		//	}
		//}

		// 进阶写法
		// 默认构造函数
		String(const char* str = "")	// 默认构造函数
			: _str(new char[strlen(str) + 1]), _size(strlen(str)), _capacity(_size)
		{
			strcpy(_str, str);
		}

		// 拷贝构造函数：深拷贝
		//String(const String& s) // 拷贝构造函数
		//	: _str(new char[s._capacity + 1]), _size(s._size), _capacity(s._capacity)
		//{
		//	strcpy(_str, s._str);
		//}

		// 进阶写法
		// 拷贝构造		复用默认构造
		String(const String& s)
			: String(s._str)
		{}

		// 赋值运算
		 //String &operator=(const String &s)
		 //{
		 //    if (this != &s)
		 //    {
		 //        char *tmp = new char[s._capacity + 1];
		 //        strcpy(tmp, s._str);
		 //        delete[] _str;
		 //        _str = tmp;
		 //        _size = s._size;
		 //        _capacity = s._capacity;
		 //    }

		 //    return *this;
		 //}

		// 进阶写法
		// 赋值运算符重载
		void Swap(String& s)
		{
			std::swap(_str, s._str);
			std::swap(_size, s._size);
			std::swap(_capacity, s._capacity);
		}

		String& operator=(String s)
		{
			this->Swap(s);

			return *this;
		}

		String& operator=(const char* str)
		{
			String s(str);
			this->Swap(s);

			return *this;
		}

		// 移动构造函数
		String(String&& s) noexcept
			: _str(s._str), _size(s._size), _capacity(s._capacity)
		{
			s._str = nullptr;
			s._size = s._capacity = 0;
		}

		// 移动赋值运算符
		String& operator=(String&& s) noexcept
		{
			if (this != &s) {
				delete[] _str; // 释放当前对象的内存

				_str = s._str; // 接管资源
				_size = s._size;
				_capacity = s._capacity;

				s._str = nullptr; // 将other对象重置为默认状态
				s._size = s._capacity = 0;
			}

			return *this;
		}

		// 重载 [] 运算符
		char& operator[](size_t pos)
		{
			assert(pos < _size);

			return _str[pos];
		}

		const char& operator[](size_t pos) const
		{
			assert(pos < _size);

			return _str[pos];
		}

		// 获取私有成员
		size_t size() const // 获取有效字符个数
		{
			return _size;
		}

		size_t capacity() const // 获取有效容量
		{
			return _capacity;
		}

		const char* c_str() const	// 返回字符串
		{
			return _str;
		}

		// 析构函数
		~String()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		// 开辟空间
		void reserve(size_t newcapacity)
		{
			if (newcapacity > _capacity)
			{
				char* newstr = new char[newcapacity + 1];
				strcpy(newstr, _str);
				delete[] _str;
				_str = newstr;
				_capacity = newcapacity;
			}
		}

		// 设置指定大小, 并初始化
		void resize(size_t newsize, char ch = '\0')
		{
			if (newsize < _size)
			{
				_size = newsize;
				_str[_size] = '\0';
			}
			else
			{
				if (newsize > _capacity)
				{
					reserve(newsize);
				}
				for (size_t i = _size; i < newsize; i++)
				{
					_str[i] = ch;
				}
				_size = newsize;
				_str[_size] = '\0';
			}
		}

		// 尾插
		void push_back(char ch)	// 尾插一个字符
		{
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}

			_str[_size++] = ch;
			_str[_size] = '\0';
		}

		// 追加
		void append(const char ch)
		{
			push_back(ch);
		}

		void append(const char* str)	// 追加一个字符串
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}

			strcpy(_str + _size, str);
			_size += len;
		}

		void append(const String& s)	// 追加一个对象
		{
			append(s._str);
		}

		// 运算符 += 重载
		String& operator+=(const char ch)
		{
			this->push_back(ch);

			return *this;
		}

		String& operator+=(const char* str)
		{
			this->append(str);

			return *this;
		}

		String& operator+=(const String& s)
		{
			append(s);

			return *this;
		}

		// 任意位置插入字符
		String& insert(size_t pos, char ch)
		{
			assert(pos <= _size);

			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}

			int end = _size;
			while (end >= (int)pos)
			{
				_str[end + 1] = _str[end];
				--end;
			}
			_str[pos] = ch;
			++_size;

			return *this;
		}

		// 任意位置插入字符串
		String& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);

			// 1. 如果空间不够就扩容
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}

			// 2. 挪动数据
			int end = _size;
			while (end >= (int)pos)
			{
				_str[end + len] = _str[end];
				--end;
			}

			// 3. 插入数据
			strncpy(_str + pos, str, len);
			_size += len;

			return *this;
		}

		// 任意位置插入一个对象
		String& insert(size_t pos, const String& s)
		{
			return insert(pos, s._str);
		}

		// 删除
		String& erase(size_t pos = 0, size_t len = npos)
		{
			assert(pos < _size);

			if (len >= _size - pos)
			{
				_str[pos] = '\0';
				_size = pos;
			}
			else
			{
				while (pos <= _size - len)
				{
					_str[pos] = _str[pos + len];
					++pos;
				}
				_size -= len;
			}

			return *this;
		}

		// 尾删
		void pop_back()
		{
			assert(_size > 0);

			--_size;
			_str[_size] = '\0';
		}

		// 运算符 < 重载
		bool operator<(const String& s)
		{
			int ret = strcmp(_str, s._str);

			return ret < 0;
		}

		// 运算符 == 重载
		bool operator==(const String& s)
		{
			int ret = strcmp(_str, s._str);

			return ret == 0;
		}

		// 运算符 <= 重载
		bool operator<=(const String& s)
		{
			return *this < s || *this == s;
		}

		// 运算符 > 重载
		bool operator>(const String& s)
		{
			int ret = strcmp(_str, s._str);

			return ret > 0;
		}

		// 运算符 >= 重载
		bool operator>=(const String& s)
		{
			return !(*this < s);
		}

		// 运算符 != 重载
		bool operator!=(const String& s)
		{
			return !(*this == s);
		}

		// 查找字符
		size_t find(char ch, size_t pos = 0) const
		{
			for (size_t i = pos; i < _size; i++)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}

			return npos;
		}

		// 查找字符串
		size_t find(const char* str, size_t pos = 0) const
		{
			char* p = strstr(_str, str);

			if (p == nullptr)
			{
				return npos;
			}
			else
			{
				return p - _str;
			}
		}

		// 查找对象
		size_t find(const String& s, size_t pos = 0) const
		{
			return find(s._str, pos);
		}

		// 反向查找字符串
		size_t rfind(char ch, size_t pos = npos) const
		{
			if (pos == npos)
			{
				pos = _size - 1;
			}

			for (int i = pos; i >= 0; i--)
			{
				if (_str[i] == ch)
				{
					return i;
				}
			}

			return npos;
		}

		// 反向查找字符串
		size_t rfind(const char* str, size_t pos = npos)
		{
			size_t len = strlen(str);
			if (len > _size)
			{
				return npos;
			}

			if (pos >= _size)
			{
				pos = _size - 1;
			}

			for (size_t i = pos; i != npos; i--)
			{
				if (strncmp(_str + i, str, len) == 0)
				{
					return i;
				}
			}

			return npos;
		}

		String substr(size_t pos = 0, size_t len = npos) const
		{
			assert(pos < _size);

			if (len == npos || len + pos > _size)
			{
				len = _size - pos;
			}

			char* buffer = new char[len + 1];
			strncpy(buffer, _str + pos, len);
			buffer[len] = '\0';

			return String(buffer);

		}

		// 清空
		void clear()
		{
			_size = 0;
			_str[_size] = '\0';
		}

	private:
		char* _str;
		size_t _size;	// 记录已经存储了多少有效字符
		size_t _capacity;	// 记录能存储多少有效字符	'\0' 结尾	但不作为有效字符

	public:
		static size_t npos;	// size_t -> unsigned long long		-1 是一个极大的数
	};

	size_t String::npos = -1;

	std::ostream& operator<<(std::ostream& _cout, const String& s)
	{
		for (size_t i = 0; i < s.size(); i++)
		{
			_cout << s[i];
		}
		return _cout;
	}

	std::istream& operator>>(std::istream& _cin, String& s)
	{
		while (true)
		{
			char ch;
			//_cin >> ch;
			ch = _cin.get();

			//if (ch == '\n')	// 通过换行分割
			if (ch == ' ' || ch == '\n')
			{
				break;
			}
			else
			{
				s += ch;
			}
		}

		return _cin;
	}
}