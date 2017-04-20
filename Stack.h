#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include<cassert>

//------------使用类型萃取来拷贝栈内元素-------------
struct _TrueType
{
	bool Get()
	{
		return true;
	}
};

struct _FalseType
{
	bool Get()
	{
		return false;
	}
};

template<class _Tp>
struct TypeTraits
{
	typedef _FalseType _IsPODType;
};

template<>
struct TypeTraits<bool>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<int>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<unsigned int>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<char>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits< float >
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits< double >
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits<long>
{
	typedef _TrueType _IsPODType;
};

template<>
struct TypeTraits< unsigned long>
{
	typedef _TrueType _IsPODType;
};

template<class T>
void Copy(T* dst, T* src, size_t size)
{
	if (TypeTraits<T>::_IsPODType().Get())
	{
		memcpy(dst, src, size);
	}
	else
	{
		for (int i = 0; i < size; ++i)
		{
			dst[i] = src[i];
		}
	}
}

template<class T>
struct TypeTraits< T* >
{
	typedef _TrueType _IsPODype;
};

//-------------------------栈的基本操作----------------
template<class T>
class Stack
{
public:
	//构造函数
	Stack(int capacity = 10)
		:_pData(NULL)
		, _capacity(capacity)
		, _size(0)
	{
		_pData = new T[capacity];
	}

	//拷贝构造函数
	Stack(const Stack<T>& s)
		:_pData(new T[s._capacity])
		, _size(s._size)
		, _capacity(s._capacity)
	{
		for (int i = 0; i < _size; ++i)
		{
			_pData[i] = s._pData[i];
		}
	}

	//赋值运算符函数
	Stack& operator=(Stack<T> s)
	{
		std::swap(_pData, s._pData);
		_size = s._size;
		_capacity = s._capacity;
		return *this;
	}

	//入栈
	void Push(const T& data)
	{
		CheckCapacity();
		_pData[_size++] = data;
	}
	//出栈
	void Pop()
	{
		if (!Empty())
		{
			--_size;
		}
	}

	//获取栈顶元素
	T& Top()
	{
		if (!Empty())
		{
			return _pData[_size - 1];
		}
		else
		{
			cout << "栈为空\n" << endl;
		}
	}

	const T& Top()const
	{
		if (!Empty())
		{
			return _pData[_size - 1];
		}
	}

	size_t Size()const
	{
		return _size;
	}

	bool Empty()const
	{
		return 0 == _size;
	}

	//析构函数（释放资源）
	~Stack()
	{
		if (_pData)
		{
			delete[] _pData;
			_pData = NULL;
		}
	}

private:
	//增容
	void CheckCapacity()
	{
		if (_size >= _capacity)
		{
			_capacity = 2 * _capacity + 3;
			T* tmp = new T[_capacity];
			//拷贝原数据
			//释放旧空间
			//指向新空间
			//需要进行类型萃取
			Copy<T>(_pData, tmp, _size);
			delete[] _pData;
			_pData = tmp;
		}
	}

	T* _pData;
	int _capacity;
	int _size;
};
//----------------------------------------------------------
//需要用到的函数的声明
int GetPriority(char ch, int flag);//获取优先级
bool IsOperator(char ch);//判断是否为操作符
void prefixionToSuffix(char* dst, char* src);//中缀表达式转后缀表达式
int  SuffixToValue(char *suffix, char *prefixion);//后缀表达式求值
