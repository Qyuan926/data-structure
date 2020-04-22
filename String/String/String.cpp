#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
#include<assert.h>
#include<string.h>
using namespace std;
#include<string>
#include<algorithm>
namespace MyString
{
	class String{
	public:
		//浅拷贝
        //拷贝构造，缺省值为"" ；不能给nullptr指针
		String(const char* str="")
			:_size (strlen(str))
		{
			_str = new char[_size + 1];
			strcpy(_str, str);
			_capacity = _size;
		}

		//深拷贝
		String(const String& s)
		{
			_size = s._size;
			_str = new char[_size+1];
			strcpy(_str, s._str);
			_capacity = _size;
		}

		~String()
		{
			delete[]_str;
			_str = nullptr;
			_capacity = _size = 0;
		}

		String& operator =(const String& s)
		{
			if (_str != s._str)
			{
				delete[] _str;
				_str = new char[(s._size) + 1];
				strcpy(_str, s._str);
				_size = s._size;
				_capacity = _size;
			}
			return  *this;
		}
		// 字符串的迭代器底层相当于一个char* 指针
		typedef char* iterator;
		//begin获取第一个有效字符
		iterator begin()
		{
			return _str;
		}
		//end获取最后一个有效字符的下一个字符
		iterator end()
		{
			return _str+_size ;
		}

			// modify

			void  PushBack(char c)
			{
				if (_size == _capacity)
				{
					if (_capacity == 0)
					{
						reserve(2);
					}
					else
					reserve(_capacity * 2);
				}
				_str[_size] = c;
				_size++;
				_str[_size] = '\0';
			}

			String& operator+=(char c)
			{
				this->PushBack(c);
				return (*this) ;
			}

			String& operator+=(const char* str)
			{
				int Size = strlen(str);
				if (_capacity < Size + _size)
				{
					reserve(Size + _size);
				}
				strcpy(_str + _size, str);
				_size += Size;
				return (*this);
			}

			void append(const char* str)
			{
				(*this) += (*str);
			}
			//
			void clear()
			{
				_size = 0;

			}
			//
			void swap(String& s)
			{
				if (_str != s._str)
				{
					char* tmp1 = new char[s._size + 1];
					char* tmp2 = new char[_size + 1];
					strcpy(tmp1, s._str);
					strcpy(tmp2, _str);
					delete[] _str;
					delete[] s._str;
					_str = tmp1;
					s._str = tmp2;
				}
			}

			const char* c_str()const
			{
				return _str;
			}
			

			size_t size()const
			{
				return _size;
			}

			size_t capacity()const
			{
				return _capacity;
			}

			bool empty()const
			{
				if (_size == 0)
					return true;
				else
					return false;
			}

			void resize(size_t newSize, char c = '\0')
			{
				if (newSize < _size)
				{
					_size = newSize;
					_str[_size] = '\0';
				}
				else
				{
					if (newSize>_capacity)
					{
						this->reserve(newSize);
					}
					for (size_t i = _size; i < newSize; ++i)
					{
						_str[i] = c;
					}
					_size = newSize;
					_str[_size] = '\0';					
				}
			}

			void reserve(size_t newCapacity)
			{
				if (newCapacity > _capacity)
				{
					char* tmp = new char[newCapacity + 1];
					strcpy(tmp, _str);
					delete[] _str;
					_str = tmp;
					_capacity = newCapacity;
				}
				
			}
			

			char& operator[](size_t index)
			{
				assert(index < _size);
				return  _str[index];
			}

			const char& operator[](size_t index)const
			{
				assert(index < _size);
				return  _str[index];
			}
	

			bool operator<(const String& s)
			{
				return strcmp(_str,s._str)<0;
#if 0
				int strIndex = 0;
				int sIndex = 0;
				//while (strIndex<_size&&sIndex<s.size())
				while (_str[strIndex] != '\0'&&s[sIndex] != '\0')
				{
					if (_str[strIndex] < s[sIndex])
						return true;
					else if (_str[strIndex>s[sIndex]])
						return false;
					else
					{
						strIndex++;
						sIndex++;
					}
				}
				if (s[sIndex] != '\0')
				{
					return true;
				}
				return false;
#endif
			}

			bool operator==(const String& s)
			{
				return strcmp(_str,s._str)==0;
#if 0
				int strIndex = 0;
				int sIndex = 0;
				while (*(_str + strIndex) != '\0'&&*(s._str + sIndex) != '\0')
				{
					if (*(_str + strIndex) == *(s._str + sIndex))
					{
						strIndex++;
						sIndex++;
					}
					else
					{
						return false;
					}
				}
				if (*(s._str+sIndex) == '\0'&&*(_str+strIndex)=='\0')
				{
					return true;
				}
				return false;
#endif
			}

			bool operator<=(const String& s)
			{
				return (*this<s) || (*this == s);
			}

			bool operator>(const String& s)
			{
				return !((*this) <= s);
			}

			bool operator>=(const String& s)
			{
				return (*this > s) || (*this == s);
			}

			bool operator!=(const String& s)
			{
				return !(*this == s);
			}
			// 返回c在string中pos位置后第一次出现的位置

			size_t find(char c, size_t pos = 0) const
			{
				for (size_t i = pos; i < _size; ++i)
				{
					if (_str[i] == c)
					{
						return i;
					}
				}
				return npos;
			}

			// 返回子串s在string中第一次出现的位置

			size_t find(const char* s, size_t pos = 0) const
			{
				for (size_t i = pos; i < _size; ++i)
				{
					int j = i;
					int k = 0;
					while (_str[j] == s[k]&&_str[j]!='\0'&&s[k]!='\0')
					{
						j++;
						++k;
					}
	
						if (s[k] == '\0')
							return i;
				}

				return npos;
			}

			// 在pos位置上插入字符c/字符串str
			String& insert(size_t pos, char c)
			{
				assert(pos <= _size);
				if (_size + 1 > _capacity)
				{
					reserve(_capacity + 1);
				}
				for (size_t i = _size+1; i > pos; --i)
				{
					_str[i] = _str[i-1];
				}
				_str[pos] = c;
				_size = _size + 1;
				return *this;
			}

			String& insert(size_t pos, const char* str)
			{
				assert(pos <=_size);

				size_t len = strlen(str);
				if (_size + len>_capacity)
				{
					reserve(_size + len);	
				}
				for (size_t i = _size; i >= pos; --i)
				{
					_str[i + len] = _str[i];
				}
				strncpy(_str + pos, str, len);
				_size +=  len;
				return   *this;
			}



			// 删除pos起len个字符

			String& erase(size_t pos = 0, size_t len = npos)
			{
				     assert(pos <= _size);
					if (pos + len >= _size)
					{
						_str[pos] = '\0';
						_size = pos;
					}
					else
					{
						//size_t j = pos ;
						/*for (size_t i = pos  + len; i <= _size; ++i)
						{
							_str[j++] = _str[i];
						}*/
						strcpy(_str + pos, _str + pos + len);
						//_str[j] = '\0';
						_size -= len;
					}
					return (*this);
			}
			friend ostream& operator<<(ostream& _cout, const MyString::String& s);
			

			friend istream& operator>>(istream& _cin, MyString::String& s);

	private:
		char* _str;
		size_t _size;
		size_t _capacity;
		static size_t npos;

	};
	 ostream& operator<<(ostream& _cout, const MyString::String& s)
	{
		 for (size_t i = 1; i <= s.size(); ++i)
		 {
			 _cout << s[i];
		 }
		 return _cout;
	}


	 istream& operator>>(istream& _cin, MyString::String& s)
	 {
		 while (1)
		 {
			 char c = _cin.get();
			 if (c == ' ' || c == '\n')
			 {
				 break;
			 }
			 else
				 s += c;
		 }
		 return _cin;
	 }
	 size_t MyString::String::npos = -1;
};


using namespace std;
void  InsertTest()
{
	MyString::String  s1("MyString");
	s1 += ' ';
	cout << s1 << endl;
	s1 += "can";
	cout << s1 << endl;
	s1.insert(s1.size(), '!');
	cout << s1 << endl;
	s1.erase(s1.size(),1);
	cout << s1 << endl;
	s1.erase(s1.size()-1, 1);
	s1 += ' ';
	cout << s1 << endl;
	s1.insert(s1.size(), "run right");
	cout << s1 << endl;

}
void FindTest()
{
	MyString::String  s1("abbacccdcc");
	string s2("abbacccdcc");
	cout << s1.find('b') << endl;
	cout << s2.find('b') << endl;
	cout << s1.find("ac") << endl;
	cout << s2.find("ac") << endl;

}
void  CmpTest()
{
	MyString::String  s1("abbacccdcc");
	MyString::String  s2("abbacccdcc");
	MyString::String  s3("abbaccdcc");
	MyString::String  s4("abxacccdcc");
	cout << (s1 < s2) << endl;
	cout << (s1 == s2) << endl;
	cout << (s1 < s3) << endl;
	cout << (s1 > s3) << endl;
	cout << (s1 < s4) << endl;


}
namespace MyStringNew{
	class String{
	public:
		String(char* str="")
			:_str(new char[strlen(str)+1])
		{
			strcpy(_str, str);
		}
		~String()
		{
			delete _str;
			_str = nullptr;
		}
		 String(String& s)
			 :_str(nullptr)
		{
			 String tmp(s._str);
			 swap(_str, tmp._str);
		}
	String& 	operator=(String& s)
		{
		   swap(_str, s._str);
		   return *this;

		}

	private: 
		char* _str;
	};
}

int main()
{
	//InsertTest();
	//FindTest();
	//CmpTest();
	MyStringNew::String  s1("abbacccdcc");

	MyStringNew::String  s2(s1);
	MyStringNew::String s3("ss");
	s3 = s1;
	
	return 0;
}