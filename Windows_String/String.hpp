#pragma once

#include <iostream>
#include <cassert>
#include <cstring>

namespace Lenyiin
{
	// ʵ��һ��֧����ɾ��ĵ� string
	class String
	{
	public:
		// ������
		typedef char* iterator;
		typedef const char* const_iterator;
		typedef char* riterator;
		typedef const char* const_riterator;

		iterator begin()	// �����׵�ַ
		{
			return _str;
		}

		iterator end()	// ����β��ַ
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
		//// Ĭ�Ϲ��캯��������һ�����ַ���
		//String()
		//	: _str(nullptr), _size(0), _capacity(0)
		//{
		//}

		//// �������Ĺ��캯������C����ַ�������String����
		//String(const char* str) {
		//	if (str) {
		//		_size = _capacity = strlen(str);
		//		_str = new char[_size + 1]; // �����ڴ棬+1��Ϊ�˴洢��ֹ��'\0'
		//		strcpy(_str, str);           // ���ַ������ݸ��Ƶ�dataָ����ڴ�
		//	}
		//	else {
		//		_str = nullptr;
		//		_size = _capacity = 0;
		//	}
		//}

		// ����д��
		// Ĭ�Ϲ��캯��
		String(const char* str = "")	// Ĭ�Ϲ��캯��
			: _str(new char[strlen(str) + 1]), _size(strlen(str)), _capacity(_size)
		{
			strcpy(_str, str);
		}

		// �������캯�������
		//String(const String& s) // �������캯��
		//	: _str(new char[s._capacity + 1]), _size(s._size), _capacity(s._capacity)
		//{
		//	strcpy(_str, s._str);
		//}

		// ����д��
		// ��������		����Ĭ�Ϲ���
		String(const String& s)
			: String(s._str)
		{}

		// ��ֵ����
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

		// ����д��
		// ��ֵ���������
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

		// �ƶ����캯��
		String(String&& s) noexcept
			: _str(s._str), _size(s._size), _capacity(s._capacity)
		{
			s._str = nullptr;
			s._size = s._capacity = 0;
		}

		// �ƶ���ֵ�����
		String& operator=(String&& s) noexcept
		{
			if (this != &s) {
				delete[] _str; // �ͷŵ�ǰ������ڴ�

				_str = s._str; // �ӹ���Դ
				_size = s._size;
				_capacity = s._capacity;

				s._str = nullptr; // ��other��������ΪĬ��״̬
				s._size = s._capacity = 0;
			}

			return *this;
		}

		// ���� [] �����
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

		// ��ȡ˽�г�Ա
		size_t size() const // ��ȡ��Ч�ַ�����
		{
			return _size;
		}

		size_t capacity() const // ��ȡ��Ч����
		{
			return _capacity;
		}

		const char* c_str() const	// �����ַ���
		{
			return _str;
		}

		// ��������
		~String()
		{
			delete[] _str;
			_str = nullptr;
			_size = _capacity = 0;
		}

		// ���ٿռ�
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

		// ����ָ����С, ����ʼ��
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

		// β��
		void push_back(char ch)	// β��һ���ַ�
		{
			if (_size == _capacity)
			{
				size_t newcapacity = _capacity == 0 ? 4 : _capacity * 2;
				reserve(newcapacity);
			}

			_str[_size++] = ch;
			_str[_size] = '\0';
		}

		// ׷��
		void append(const char ch)
		{
			push_back(ch);
		}

		void append(const char* str)	// ׷��һ���ַ���
		{
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}

			strcpy(_str + _size, str);
			_size += len;
		}

		void append(const String& s)	// ׷��һ������
		{
			append(s._str);
		}

		// ����� += ����
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

		// ����λ�ò����ַ�
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

		// ����λ�ò����ַ���
		String& insert(size_t pos, const char* str)
		{
			assert(pos <= _size);

			// 1. ����ռ䲻��������
			size_t len = strlen(str);
			if (_size + len > _capacity)
			{
				reserve(_size + len);
			}

			// 2. Ų������
			int end = _size;
			while (end >= (int)pos)
			{
				_str[end + len] = _str[end];
				--end;
			}

			// 3. ��������
			strncpy(_str + pos, str, len);
			_size += len;

			return *this;
		}

		// ����λ�ò���һ������
		String& insert(size_t pos, const String& s)
		{
			return insert(pos, s._str);
		}

		// ɾ��
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

		// βɾ
		void pop_back()
		{
			assert(_size > 0);

			--_size;
			_str[_size] = '\0';
		}

		// ����� < ����
		bool operator<(const String& s)
		{
			int ret = strcmp(_str, s._str);

			return ret < 0;
		}

		// ����� == ����
		bool operator==(const String& s)
		{
			int ret = strcmp(_str, s._str);

			return ret == 0;
		}

		// ����� <= ����
		bool operator<=(const String& s)
		{
			return *this < s || *this == s;
		}

		// ����� > ����
		bool operator>(const String& s)
		{
			int ret = strcmp(_str, s._str);

			return ret > 0;
		}

		// ����� >= ����
		bool operator>=(const String& s)
		{
			return !(*this < s);
		}

		// ����� != ����
		bool operator!=(const String& s)
		{
			return !(*this == s);
		}

		// �����ַ�
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

		// �����ַ���
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

		// ���Ҷ���
		size_t find(const String& s, size_t pos = 0) const
		{
			return find(s._str, pos);
		}

		// ��������ַ���
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

		// ��������ַ���
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

		// ���
		void clear()
		{
			_size = 0;
			_str[_size] = '\0';
		}

	private:
		char* _str;
		size_t _size;	// ��¼�Ѿ��洢�˶�����Ч�ַ�
		size_t _capacity;	// ��¼�ܴ洢������Ч�ַ�	'\0' ��β	������Ϊ��Ч�ַ�

	public:
		static size_t npos;	// size_t -> unsigned long long		-1 ��һ���������
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

			//if (ch == '\n')	// ͨ�����зָ�
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