#pragma once

#include<assert.h>
#include<stdlib.h>

namespace MyVector{
	template<class T>
	class vector{
		public:
		typedef   T*  iterator;
		typedef const T*  const_iterator;

		iterator begin()
		{
			return _start;
		}

		iterator end()
		{
			return _finish;
		}

		const_iterator cbegin() const
		{
			return _start;
		}

		const_iterator cend() const
		{
			return _finish;
		}



			// construct and destroy

		vector()
			:_start(0), _finnish(0), _end(0)
		{ }
		//v(v1)
		vector(int n, const T& value = T())
		{
			_start = new T[n];
			for (int i = 0; i < n; ++i)
			{
				_start[i] = value;
			}
			_finish = _start + n;
			_end = _finish;

		}

			template<class InputIterator>

			vector(InputIterator first, InputIterator last)
				:_start(0), _finish(0), _end(0)
			{
				for (; first != last; ++first)
					push_back(*frist);
			}
			vector(const vector<T>& v)
			{
				_start = new T[v.size()];
				_finish = _start + v.size();
				_end = _finish;
				memcpy(_start, v._start, sizeof(T)*v.size());
			}

			vector<T>& operator= (vector<T> v)
			{
				this->swap(v);
				return *this;
			}

				~vector()
			{
					delete[] _start;
					_start = nullptr;
					_finish = nullptr;
					_end = nullptr;
			}

			// capacity

				size_t size() const
				{
					return _finish - _start;
				}

				size_t capacity() const
				{
					return _end - _start;
				}

				void reserve(size_t n)
				{
					if (n > capacity())
					{
						size_t sz = size();
						T* tmp = new T[n];
						memcpy(tmp, _start, sizeof(T)*sz);
						delete[] _start;
						_start = tmp;
						_finish = _start + sz;
						_end = _start + n;
					}
				}

				void resize(size_t n, const T& value = T())
				{
					if (n > size())
					{

						sz = size();
						if (n>capacity())
						 reserve(n);
						memset(_start + sz, value, sizeof(T)*(n - sz));
					}
						else
						{

							_finish = _start + n;
						}
					
				}



			///////////////access///////////////////////////////

				T& operator[](size_t pos)
				{
					assert(pos < size());
					return _start[pos];
				}

				const T& operator[](size_t pos)const
				{
					assert(pos < size());
					return _start[pos];

				}



			///////////////modify/////////////////////////////

			void push_back(const T& x)
			{   //空间满了，需要扩展空间
				/*if (_finish == _end)
				{
					size_t cap = capacity() == 0 ? 2 : capacity() * 2;
					reserve(cap);
				}
				_start[size()] = x;
				++_finish;*/
				insert(end(), x);
			}

			void pop_back()
			{
				/*assert(size() > 0);
				--_finish;*/
				erase(end()-1);
			}

			void swap(vector<T>& v)
			{
				::swap(_start, v._start);
				::swap(_finish, v._finnish);
				::swap(_end, v._end);
			}

			iterator insert(iterator pos, const T& x)
			{
				assert(pos <= _finish);
				if (_finish == _end)
				{
					int len = pos - _start;
					size_t cap = capacity() == 0 ? 2 : capacity() * 2;
					reserve(cap);
					pos = _start + len;
				}
				size_t sz = size() + 1;
				while (_finish != pos)
				{
					*(_finish + 1) = *_finish;
					--_finish;
				}
				*pos = x;
				_finish = _start + sz;
				return pos;
			}

			iterator erase(iterator pos)
			{
				assert(pos<_finish&&pos>=_start);
				iterator it = pos + 1;
				while (it != _finish)
				{
					*(it-1)= *it;
					++it;
				}
				--_finish;
				return pos;
			}
	private:
		iterator  _start;
		iterator  _finish;
		iterator  _end;
	};


};