#pragma once
#include<vector>
#if 0
namespace queue{

	template <class T,class Container = vector<T> >
	class priority_queue{
	    //实现大堆的向上、向下调整算法
		void ADjustUp(size_t Size)
		{
			int child = Size - 1;
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (_con[child] > _con[parent])
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}
				
			}
		}
		void  ADjustDown(size_t start)
		{
			size_t parent = start;
			size_t child = 2 * parent + 1;
			while (child < _con.size())
			{
				//选出最大的那个孩子
				if (child + 1 < _con.size() && _con[child + 1] > _con[child])
				{
					child = child + 1;
				}
				if (_con[child]>_con[parent])
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = 2 * parent + 1;
				}
				else
				{
					break;
				}
				
			}
		}
		//实现小堆的向上，向下算法

		void ADjustUp(size_t Size)
		{
			int child = Size - 1;
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				if (_con[child] < _con[parent])
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}

			}
		}
		void  ADjustDown(size_t start)
		{
			size_t parent = start;
			size_t child = 2 * parent + 1;
			while (child < _con.size())
			{
				//选出最大的那个孩子
				if (child + 1 < _con.size() && _con[child + 1] < _con[child])
				{
					child = child + 1;
				}
				if (_con[child]<_con[parent])
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = 2 * parent + 1;
				}
				else
				{
					break;
				}

			}
		}
	public:
		void push(const T& x)
		{
			_con.push_back(x);
			ADjustUp(_con.size());
		}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();

			ADjustDown(0);
		}
		bool empty() const
		{
			return _con.empty();
		}
		const T& top() const
		{
			return _con[0];
		}
		size_t size()  const
		{
			return _con.size();
		}



	private:
		Container _con;
	};
};
#endif

namespace queue{
	template <class T>
	struct less{
		bool operator()(const T& x1, const T& x2)
		{
			return  x1 < x2;
		}
	};
	template <class T>
	struct greater{
		bool operator()(const T& x1, const T& x2)
		{
			return  x1 > x2;
		}
		
	};
	template <class T, class Container = vector<T> ,class Compare=less<T>>
	class priority_queue{

		void ADjustUp(size_t Size)
		{
			Compare com;
			int child = Size - 1;
			int parent = (child - 1) / 2;
			while (child > 0)
			{
				//if (_con[child] > _con[parent])
				//if (_con[child] < _con[parent])
				if (com(_con[parent],_con[child]))
				{
					swap(_con[child], _con[parent]);
					child = parent;
					parent = (child - 1) / 2;
				}
				else
				{
					break;
				}

			}
		}
		void  ADjustDown(size_t start)
		{
			Compare com;
			size_t parent = start;
			size_t child = 2 * parent + 1;
			while (child < _con.size())
			{
				//选出最大的那个孩子
				//大堆if (child + 1 < _con.size() && _con[child + 1] > _con[child])
				//小堆  (child + 1 < _con.size() && _con[child + 1] < _con[child])
				if (child + 1 < _con.size() && com(_con[child] , _con[child+1]))
				{
					child = child + 1;
				}
				//大堆if (_con[child]>_con[parent])
				//小堆if (_con[child]<_con[parent])
				if (com(_con[parent],_con[child]))
				{
					swap(_con[parent], _con[child]);
					parent = child;
					child = 2 * parent + 1;
				}
				else
				{
					break;
				}

			}
		}
	public:
		void push(const T& x)
		{
			_con.push_back(x);
			ADjustUp(_con.size());
		}
		void pop()
		{
			swap(_con[0], _con[_con.size() - 1]);
			_con.pop_back();

			ADjustDown(0);
		}
		bool empty() const
		{
			return _con.empty();
		}
		const T& top() const
		{
			return _con[0];
		}
		size_t size()  const
		{
			return _con.size();
		}



	private:
		Container _con;
	};
};