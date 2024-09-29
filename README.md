# 告别平庸！实现一个比标准库更强的 C++ String 类

<p align="right">--- All rights by auther Lenyiin</p>



本项目，我们将详细讲解如何从头实现一个功能齐全且强大的 `C++ String` 类，并深入到各个细节。下面将包括每一步的代码实现、解释以及扩展功能的探讨，目标是让初学者也能轻松理解。

# 一、简介

## 1.1、背景介绍

在 `C++` 编程中，`std::string` 类是最常用的字符串处理工具，它提供了丰富的功能。然而，初学者经常使用它而不太理解其背后的实现原理。在深入学习 `C++` 的过程中，了解如何手动实现一个类似于 `std::string` 的字符串类，不仅有助于加深对 `C++` 内存管理的理解，还能更好地掌握 `C++` 的面向对象编程、动态内存分配、迭代器设计、运算符重载以及异常处理等核心概念。



## 1.2、学习目标

通过阅读本文，您将掌握以下技能：

- 如何从零开始实现一个功能齐全的 `C++ String` 类。
- 理解 `C++` 中动态内存分配的机制，并学习如何防止内存泄漏。
- 学会运算符重载的正确使用方式。
- 实现 `C++` 类的拷贝构造函数、赋值运算符、移动构造函数和移动赋值运算符。
- 实现迭代器功能
- 学习如何处理异常情况，并编写健壮的代码。





# 二、设计目标

## 2.1、String 类的基本功能

我们将逐步实现以下功能：

1. **字符串存储**：`String` 类应该能够存储和管理字符串数据，确保能够正确地处理空字符串、较长的字符串等情况。
2. **动态内存管理**：`String` 类应该能够自动管理内存的分配和释放，避免内存泄漏和无效的内存访问。
3. **基本字符串操作**：包括字符串的拼接、比较、查找、截取子串等常见操作。
4. **迭代器**：实现正向迭代器，反向迭代器，const 迭代器。
5. **运算符重载**：实现对 `+`、`==`、`!=`、`<`、`>` 等运算符的重载，使 `String` 类可以像标准库的 `std::string` 一样使用。
6. **与 C 风格字符串的兼容性**：`String` 类应该能够方便地与 `C` 风格字符串（即 `char*`）进行互操作，支持从 `char*` 构造 `String` 对象，或将 `String` 对象转换为 `char*`。
7. **错误处理**：合理处理异常和错误情况。



## 2.2、高级功能与扩展

在基本功能之外，我们还将探讨一些高级功能的实现，例如：

- **引用计数与内存优化**：通过引用计数机制优化内存管理，避免频繁的内存分配和拷贝操作。
- **多线程安全**：确保 `String` 类在多线程环境下的安全性和稳定性。
- **与标准库的性能对比**：对比自定义 `String` 类与 `std::string` 在不同场景下的性能表现，分析优缺点。



# 三、基础实现

## 3.1、数据成员的设计与初始化

在实现 `String` 类的过程中，首先需要设计类的数据成员，用于存储字符串数据和管理字符串长度。

### 3.1.1、数据成员定义

```
class String {
private:
    char* _str;
	size_t _size;	// 记录已经存储了多少有效字符
	size_t _capacity;	// 记录能存储多少有效字符	'\0' 结尾	但不作为有效字符

	static size_t npos;	// size_t -> unsigned long long		-1 是一个极大的数
};

size_t String::npos = -1;
```

**详细解释：**

- **`char* _str`**： `_str` 是一个指向 `char` 类型的指针，代表一个字符数组（即字符串）。在 C++ 中，字符串通常用以空字符 `'\0'` 结尾的字符数组表示。因此，我们需要确保 `_str` 指向的内存足够存储整个字符串，包括末尾的 `'\0'`。
- **`_size`**： `_size` 变量用于存储字符串的长度，但不包括末尾的 `'\0'`。
- **`_capacity`**： `_capacity` 用于记录 `string` 容器的容量。
- **`npos`**： `npos` 是 `size_t` 类型，是一种无符号整型类型，`unsigned long long`， 常用于表示大小和长度。



### 3.1.2、构造函数与初始化

为了正确地初始化 `String` 对象，我们需要提供多个构造函数：

1. **默认构造函数**：用于初始化一个空字符串。
2. **带参数的构造函数**：从 C 风格字符串（`char*`）创建 `String` 对象。

```
class String {
public:
    // 默认构造函数：创建一个空字符串
    String() : _str(nullptr), _size(0), _capacity(0) {}

    // 带参数的构造函数：从C风格字符串创建String对象
    String(const char* str) {
        if (str) {
            _size = _capacity = strlen(str);
            _str = new char[_size + 1]; // 分配内存，+1是为了存储终止符'\0'
            strcpy(_str, str);           // 将字符串内容复制到data指向的内存
        } else {
            _str = nullptr;
            _size = _capacity = 0;
        }
    }

    // 析构函数：释放动态分配的内存
    ~String() {
        delete[] _str; // 释放内存，防止内存泄漏
        _str = nullptr;
        _size = _capacity = 0;
    }
};
```

**详细解释：**

- **默认构造函数**：初始化一个空字符串，`_str` 指针设为 `nullptr`，表示当前对象未分配任何内存，`_size, _capacity` 为 `0`。
- **带参数的构造函数**：该构造函数接受一个 `C` 风格字符串 `str` 作为参数。如果传入的 `str` 不是 `nullptr`，则计算其长度，分配相应大小的内存，并将 `str` 的内容复制到 `_str` 指向的内存中。注意，分配的内存大小为 `_size + 1`，其中额外的一个字节用于存储字符串的终止符 `'\0'`。
- **析构函数**：在对象生命周期结束时，析构函数自动调用，用于释放动态分配的内存，避免内存泄漏。

**进阶：**

- 也可以将默认构造函数和带参数默认构造函数合并为一个构造函数：

```
// 默认构造函数
String(const char* str = "")	// 默认构造函数
	: _str(new char[strlen(str) + 1]), _size(strlen(str)), _capacity(_size)
{
	strcpy(_str, str);
}
```



## 3.2、深拷贝与浅拷贝

在 `C++` 中，拷贝一个对象时，默认的拷贝行为是浅拷贝，即仅复制对象的指针或引用。这对管理动态内存的类而言，可能会导致问题，例如多个对象指向同一块内存，导致重复释放或修改冲突。为避免这些问题，我们需要实现深拷贝。

### 3.2.1、拷贝构造函数

拷贝构造函数用于创建一个新对象，该对象是通过复制另一个现有对象生成的。对于 `String` 类，我们需要确保在拷贝时，新对象有自己独立的内存副本。

```
// 拷贝构造函数：深拷贝
String(const String &s) // 拷贝构造函数
	: _str(new char[s._capacity + 1]), _size(s._size), _capacity(s._capacity)
{
	strcpy(_str, s._str);
}
```

**详细解释：**

- **深拷贝**：通过分配新内存来创建新对象的独立副本，而不是简单地复制指针。这样，两个 `String` 对象可以独立管理各自的内存，避免潜在的内存管理冲突。

**进阶：**

- 也可以复用默认构造函数

```
// 拷贝构造		复用默认构造
String(const String &s)
	: String(s._str)
{}
```



### 3.2.2、赋值运算符

赋值运算符用于将一个对象的内容复制到另一个已经存在的对象中。为了避免自赋值和内存泄漏，我们需要在实现赋值运算符时特别小心。

```
// 赋值运算
String &operator=(const String &s)
{
    if (this != &s)	// 检查自赋值
    {
        char *tmp = new char[s._capacity + 1];
        strcpy(tmp, s._str);
        delete[] _str;	// 释放当前对象的内存
        _str = tmp;
        _size = s._size;
        _capacity = s._capacity;
    }

    return *this;
}
```

**详细解释：**

- **自赋值检查**：在赋值运算符实现中，首先检查是否为自赋值，即 `this` 指针是否与 `s` 相同。如果是自赋值，则无需进行任何操作，直接返回当前对象。
- **内存管理**：在分配新内存之前，记得释放当前对象所持有的旧内存，防止内存泄漏。
- **深拷贝**：与拷贝构造函数类似，通过分配新内存来存储字符串的副本，确保两个对象独立管理各自的内存。

**进阶：**

- 也可以复用拷贝构造函数

```
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
```



## 3.3、移动语义

`C++11` 引入了移动语义，允许在一定条件下避免不必要的深拷贝，从而提高程序性能。移动构造函数和移动赋值运算符是移动语义的核心。

### 3.3.1 移动构造函数

移动构造函数用于将资源从一个对象 “搬迁” 到另一个对象，而不是复制。这在避免不必要的内存分配和拷贝时非常有用。

```
// 移动构造函数
String(String&& s) noexcept
	: _str(s._str), _size(s._size), _capacity(s._capacity)
{
    s._str = nullptr;
    s._size = s._capacity = 0;
}
```

**详细解释：**

- **移动构造**：将 `s` 对象的资源直接转移到当前对象（通过简单地复制指针），然后将 `s` 的指针、长度和容量重置为默认状态。这样可以避免不必要的内存分配和数据复制。

- **`noexcept`**：标记为 `noexcept` 的函数表示在其内部不会抛出异常。这对移动构造函数尤其重要，因为这确保了在某些情况下（如在标准容器中使用）不会因为抛出异常而触发回滚操作。

      

### 3.3.2 移动赋值运算符

移动赋值运算符用于将资源从一个对象 “搬迁” 到另一个已存在的对象中。

```
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
```

**详细解释：**

- **资源搬迁**：通过简单地复制指针，将 `s` 对象的资源转移到当前对象中，并释放当前对象的旧资源。然后，将 `s` 对象重置为默认状态，避免两个对象共享同一块内存。
- **自赋值检查**：和赋值运算符一样，首先检查是否为自赋值。



## 3.4、下标运算符 [] 重载

为了使 `String` 类在操作上尽可能接近标准库中的 `std::string`，实现随机访问，我们需要重载下标运算符。

```
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
```



## 3.5、获取私有成员

为了使 `String` 类在操作上尽可能接近标准库中的 `std::string`，为了更方便使用，我们需要增加私有成员获取接口。

```
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
```



# 四、进阶功能

## 4.1、迭代器实现

为了支持在 `String` 对象上进行迭代，我们需要实现迭代器类。迭代器使得我们能够像标准库容器一样访问 `String` 的每个字符。

### 4.1.1、正向迭代器 

```
// 正向迭代器
typedef char* iterator;
typedef const char* const_iterator;

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
```

**详细解释：**

- **迭代器**：`iterator` 通过指针实现，用于遍历 `String` 中的字符。使其能够像标准库迭代器一样工作。

- **`begin` 和 `end` 函数**：`begin` 返回指向字符串开头的迭代器，`end` 返回指向字符串结尾的迭代器，这使得可以使用基于范围的 for 循环。

      

### 4.1.2、反向迭代器

```
// 反向迭代器
typedef char* riterator;
typedef const char* const_riterator;

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
```

**详细解释：**

- **反向迭代器类**：允许从字符串末尾向前遍历。
- **`rbegin` 和 `rend` 函数**：`rbegin` 返回指向字符串最后一个字符的迭代器，`rend` 返回指向字符串之前的迭代器。



## 4.2、容器容量设置

### 4.2.1、reserve 函数

为了使 `String` 类在操作上尽可能接近标准库中的 `std::string`，设计了 reserve 函数。

```
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
```



### 4.2.2、resize 函数

```
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
```



## 4.3、插入

### 4.3.1、push_back

```
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
```



### 4.3.2、append

```
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
```



### 4.3.3、运算符 += 重载

```
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
```



### 4.3.4、insert

```
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
```



## 4.4、删除

### 4.4.1、pop_back

```
// 尾删
void pop_back()
{
	assert(_size > 0);

	--_size;
	_str[_size] = '\0';
}
```



### 4.4.2、erase

```
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
```



## 4.5、字符串比较

实现字符串的比较功能，以便能够使用 `==`、`!=`、`<`、`>` 等运算符来比较两个 `String` 对象。

```
// 运算符 < 重载
bool operator<(const String& s)
{
	return strcmp(_str, s._str) < 0;
}

// 运算符 == 重载
bool operator==(const String& s)
{
	return strcmp(_str, s._str) == 0;
}

// 运算符 <= 重载
bool operator<=(const String& s)
{
	return *this < s || *this == s;
}

// 运算符 > 重载
bool operator>(const String& s)
{
	return strcmp(_str, s._str) > 0;
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
```

**解释：**

- **字符串比较**：使用标准库中的 `strcmp` 函数比较两个字符串，并根据结果返回相应的布尔值。



## 4.6、字符串查找

为了增加查找和反向查找功能，我们实现了相应的查找函数。这些函数将返回第一次或最后一次出现某个字符的位置。

### 4.6.1、正向查找

```
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
```



### 4.6.2、反向查找

```
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
```

**解释：**

- **字符串查找**：使用 `strstr` 函数查找子串在当前字符串中的位置。如果找到，返回位置索引，否则返回 `std::string::npos` 表示未找到。
- **`find` 函数**：从字符串开头开始查找指定字符，返回其第一次出现的位置。
- **`rfind` 函数**：从字符串末尾开始查找指定字符，返回其最后一次出现的位置。



## 4.7、子串操作 substr

实现获取子串的功能，可以从一个字符串中提取子串。

```
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
```

**解释：**

- **子串操作**：从原字符串中提取指定位置和长度的子串。首先检查起始位置是否超出字符串长度，然后复制相应的字符。



## 4.8、清空操作 clear

```
// 清空
void clear()
{
	delete[] _str;
	_str = new char[1];
	_str[0] = '\0';
	_size = _capacity = 0;
}
```

**详细解释：**

- **`clear` 函数**：释放原有内存，将字符串重置为空。



## 4.9、重载 >> << 运算符

```
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
```



# 五、拓展

## 5.1、内存管理优化

为了进一步优化，我们可以在 `String` 类中实现对内存的缓存和管理策略，避免频繁的内存分配和释放。可以通过引用计数或其他内存管理技术优化 `String` 类的性能。

### 5.1.1、引用计数

引用计数是一种内存管理技术，通过跟踪一个资源（如字符串）被多少个对象共享，从而决定何时释放该资源。

```
class String {
private:
    char* _str;
    size_t _size;
    size_t _capacity;
    int* _ref_count; // 引用计数

public:
    // 构造函数
    String(const char* str = "") {
        _size = _capacity = strlen(str);
        _str = new char[length + 1];
        strcpy(_str, str);

        _ref_count = new int(1); // 初始化引用计数为1
    }

    // 拷贝构造函数
    String(const String& s) {
        _str = s._str;
        _size = s._size;
        _capacity = s._capacity;
        _ref_count = s._ref_count;
        ++(*_ref_count); // 增加引用计数
    }

    // 析构函数
    ~String() {
        if (--(*_ref_count) == 0) { // 如果没有其他对象引用这块内存
            delete[] _str; // 释放内存
            delete _ref_count; // 释放引用计数
        }
    }

    // 赋值运算符
    String& operator=(const String& s) {
        if (this != &s) {
            if (--(*_ref_count) == 0) { // 释放当前对象的内存
                delete[] _str;
                delete _ref_count;
            }

            _str = s._str;
            _size = s._size;
            _capacity = s._capacity;
            _ref_count = s._ref_count;
            ++(*_ref_count); // 增加引用计数
        }
        return *this;
    }
};

```

**详细解释：**

- **引用计数管理**：通过 `_ref_count` 变量管理字符串资源的引用计数。每次拷贝构造或赋值时，增加引用计数。每次析构时，减少引用计数。如果引用计数变为 `0`，说明没有其他对象引用这块内存，此时释放资源。



### 5.1.2、性能测试

可以编写一些测试代码，比较使用引用计数优化的 `String` 类与未优化的 `String` 类、标准库 `std::string` 的性能差异。

```
void testStringPerformance() {
    String s1("Hello");
    String s2 = s1; // 引用计数增加
    String s3;
    s3 = s2; // 引用计数增加

    // ... 进行大量字符串操作
}

void testStdStringPerformance() {
    std::string s1("Hello");
    std::string s2 = s1;
    std::string s3;
    s3 = s2;

    // ... 进行大量字符串操作
}
```



## 5.2、异常处理

在实现 `String` 类的过程中，可能会遇到内存分配失败等异常情况。通过使用 C++ 异常处理机制，可以在这些情况下保证程序的健壮性。确保在异常情况下（如内存分配失败）能够安全退出，避免程序崩溃

```
class String {
public:
    String(const char* str) {
        try {
            _size = _capacity = strlen(str);
            _str = new char[_size + 1];
            strcpy(_str, str);
        } catch (std::bad_alloc& e) {
            std::cerr << "Memory allocation failed: " << e.what() << std::endl;
            _str = nullptr;
            _size = _capacity = 0;
        }
    }
};
```

**详细解释：**

- **异常处理**：使用 `try-catch` 块捕获 `new` 操作符可能抛出的 `std::bad_alloc` 异常。当内存分配失败时，可以通过异常机制捕获并处理，而不是导致程序崩溃。



## 5.3、其他拓展

- **模板化的字符串类**：进一步研究如何将 `String` 类模板化，使其支持宽字符（`wchar_t`）和其他字符类型。
- **多线程安全**：探讨如何将 `String` 类改进为多线程安全的版本，可能需要使用 `std::mutex` 或 `std::shared_mutex`。
- **与 STL 容器的集成**：研究如何将自定义 `String` 类与 C++ 标准模板库（STL）容器如 `std::vector`、`std::map` 结合使用。

通过这些扩展内容，您将能够进一步提升 C++ 编程技能，为未来的开发工作打下坚实的基础。



# 六、完整实现代码和测试

## 6.1、String.hpp

> 新建头文件 `String.hpp`

```
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
		String(const String &s)
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
```



## 6.2、String.cpp

> 新建源文件 `String.cc`

```
#define _CRT_SECURE_NO_WARNINGS
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
	for (const auto& ch : s)
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
	//test1();
	//test2();
	//test3();
	//test4();
	test5();

	return 0;
}
```



# 七、总结与扩展

通过本项目的学习，我们深入探讨了如何从零开始实现一个功能完备的 C++ `String` 类，涵盖了从动态内存管理到高级特性如引用计数和移动语义的各个方面。

这个版本的 `String` 类已经相当完善，支持动态扩容、迭代器、反向迭代器、查找与反向查找等功能。通过这些实现，`String` 类几乎可以媲美标准库的 `std::string`。

实现一个 `String` 类虽然是一个相对基础的任务，但它涉及到了 C++ 编程中的众多核心概念。通过这些内容，不仅可以更好地理解 `std::string` 的内部实现，还能提高对 C++ 面向对象编程、内存管理、类的设计与实现、运算符重载、异常处理等方面有更深刻的理解。



希望这个项目对您有所帮助，也欢迎您在此基础上进行更多的探索和改进。如果您有任何问题或建议，欢迎在评论区留言，我们可以共同探讨和学习。更多知识分享可以访问我的个人博客网站 ： https://blog.lenyiin.com/ 。