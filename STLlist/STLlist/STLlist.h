
namespace List{
	//定义链表节点
	template <class T>
	struct _list_node{
		T  _data;
		_list_node<T>* _prev;
		_list_node<T>* _next;

		_list_node(const T& data= T()) 
			:_data(data),
			_prev(nullptr),
			_next(nullptr)
		{}
	};
	//链表节点定义结束

	//用一个结构体封装迭代器
	template<class T,class Ref,class Ptr>
	struct  _list_iterator{
		typedef _list_iterator<T, Ref, Ptr> Self;
		typedef _list_node<T> node;

		node* _node;

		_list_iterator(node* node)
			:_node(node)
		{}

		//解引用，使用这个可以获得该节点的数值，即要返回一个变量（节点的数据）
		Ref operator*()
		{
			return _node->_data;
		}
		//  ->   返回一个指针
		Ptr operator->()
		{
			return  &(operator*() )
		}
		Self& operator++ ()
		{
			_node = _node->_next;
			return  *this;
		}
		Self& operator++ (int)
		{
			Self self = _node;
			++(*this);
			return self;
		}
		Self& operator-- ()
		{
			_node = _node->_prev;
			return *this;
		}
		Self& operator-- (int)
		{
			Self self = *this;
			--(*this);
			return self;
		}
		bool operator== (const Self& x)
		{
			return _node == x._node;
		}

		bool operator!= (const Self& x)
		{
			return _node != x._node;
		}

	};
	//链表迭代器封装完毕
	
	template  <class T>
	class list{
		typedef _list_node<T>  node;
	public:
		list()
		{
			_head = new node;
			_head->_next = _head;
			_head->_prev = _head;
		}
		list(const list<T>& lt)
		{
			_head = new node;
			_head->_prev = _head;
			_head->_next = _head;

			for (auto e : lt)
			{
				push_back(e);
			}
		}
		//拷贝构造
		//list<T>& operator=(const list<T>& lt)
		//{
		//	if (this != (&lt))
		//	{
		//		//将原有节点全部清除
		//		clear();
		//		//将lt的节点拷贝过来
		//		for (auto e : lt)
		//		{
		//			push_back(e);
		//		}

		//	}
		//	         
		//	return *this;
		//}
		list<T>& operator=(list<T>& lt)
		{
			swap(this->_head, lt._head);
			return *this;
		}
		~list()
		{
			clear();
			delete _head;
			_head = nullptr;
		}
	public:  
		typedef _list_iterator<T ,T& ,T*>   iterator;
		typedef _list_iterator< T,const T&,const T*>  const_iterator;
		//typedef _list_iterator<const T, const T&, const T*>  const_iterator;

		iterator begin()
		{
			return  (iterator)(_head->_next);
		}

		iterator end()
		{
			return (iterator)(_head);
		}

		const_iterator begin() const
		{
			return (const_iterator)(_head->_next);
		}

		const_iterator end() const
		{
			return (const_iterator)(_head);
		}

		size_t size()const
		{
			size_t ret = 0;
			iterator start = begin();
			while (start != end())
			{
				ret++;
				start++;
			}
			return ret;
		}

		bool empty()const
		{
			return _head->_next == _head;
		}


		T& front()
		{
			return *begin();
		}

		const T& front()const
		{
			return *begin();
		}

		T& back()
		{
			return *(--end());
		}

		const T& back()const
		{
			return *(--end());
		}


		void push_back(const T& val)
		{ 
			insert( end() , val);
		}

		void pop_back()
		{
			erase(--end());
		}

		void push_front(const T& val)
		{
			insert(begin(), val);
		}

		void pop_front()
		{
			erase(begin());
		}

		// 在pos位置前插入值为val的节点

		iterator insert(iterator pos, const T& val)
		{
			node* newnode=new node(val);
			node* cur = pos._node;
			node* cur_prev = cur->_prev;
			cur_prev->_next = newnode;
			newnode->_prev = cur_prev;
			newnode->_next = cur;
			cur->_prev = newnode;

			return (iterator)newnode;

		}

		// 删除pos位置的节点，返回该节点的下一个位置

		iterator erase(iterator pos)
		{
			node* cur = pos._node;
			node* pre = cur->_prev;
			node* next = cur->_next;

			pre->_next = next;
			next->_prev = pre;

			delete cur;
			cur = nullptr;
			return (iterator)next;
		}

		void clear()
		{
			iterator start = begin();
			while (start != end())
			{
				iterator it = ++start;
				erase(start);
				start = it;
			}

			_head->_prev = _head;
			_head->_next = _head;


		}

		void swap(list<T>& lt)
		{
			::swap(_head, lt._head);

		}



	private:
		node* _head;
	};
}