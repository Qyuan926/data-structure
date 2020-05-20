#pragma once
#include<deque>

namespace stack{
	template <class T, class Sequence = deque<T>>
	class stack{
	public:
		bool empty() const
		{
			return c.empty();
		}
		size_t size()  const
		{
			return c.size();
		}
		T& top()
		{
			return c.back();
		}
		const T& top()   const
		{
			return c.back();
		}
		void push(const T& x)
		{
			c.push_back(x);
		}
		void pop()
		{
			c.pop_back();
		}
	private:
		Sequence c;
	};

}

namespace queue{
	template <class T,class Sequence =deque<T>>
	class queue{
	public:
		bool empty() const
		{
			return c.empty();
		}
		size_t size() const
		{
			return c.size();
		}
		T& front()
		{
			return c.front();
		}
		T& back()
		{
			return c.back();
		}
		void push(const T& x)
		{
			c.push_back(x);
		}
		void pop()
		{
			c.pop_front();
		}
	private:
		Sequence c;
	};	
}