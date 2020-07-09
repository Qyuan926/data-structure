#pragma once
#include<vector>
namespace Hash{
	
	template <class T>
	struct HashNode{
		T _data;
		HashNode<T>* _next;
		HashNode(const T& data)
			:_data(data)
			, _next(nullptr)
		{}
	};

	template<class K>
	struct _hash{
		const K& operator()(const K& key)
		{
			return key;
		}
	};
	template<>
	struct _hash<std::string>
	{
		size_t operator()(const std::string& str)
		{
			size_t i = 0;
			for (size_t j = 0; j < str.size(); ++j)
			{
				i *= 131;
				i += str[j];
			}
			return i;
		}
	};

	template <class K, class T, class KeyofT,class Ha>
	class hash;
	//迭代器
	template <class K,class T,class KeyofT,class Ha>
	struct hash_iterator{
		typedef hash<K, T, KeyofT,Ha> hashTable;
		typedef hash_iterator<K, T, KeyofT,Ha> Self;
		typedef HashNode<T> Node;
		
		Node* _node;
		hashTable* _hashtable;

		hash_iterator(Node* node,hashTable* table)
			:_node(node)
			, _hashtable(table)
		{}

		T& operator*()
		{
			return (_node->_data);
		}

		T* operator->()
		{
			return &(_node->_data);
		}
		//显现判断一下_node所在的桶，判断当前这个桶是否遍历完毕，遍历完毕的话，去寻找下一个有数据的桶
		Self operator++()
		{
			
			Node* cur = _node;
			if (cur != nullptr&&cur->_next != nullptr)
			{
				_node = cur->_next;
				return *this;
			}
			else
			{
				KeyofT koft;
				size_t index = _hashtable->_hashfunc(koft(_node->_data)) % _hashtable->_table.size();
				for (size_t i = index + 1; i < _hashtable->_table.size(); ++i)
				{
					cur = _hashtable->_table[i];
					if (cur != nullptr)
					{
						_node = cur;
						return (Self)(*this);
					}
				}
				//没有找到的话，说明该表没有任何数据了
				_node = nullptr;
			}
			return (Self)(*this);
		}
		bool operator!=(const Self& s)
		{
			return _node != s._node;
		}

	};



	template <class K,class T,class KeyofT,class Ha>
	class hash{
		typedef HashNode<T> Node;
		friend struct hash_iterator<K, T, KeyofT,Ha>   ;
		typedef hash_iterator<K, T, KeyofT,Ha> iterator;
		size_t _hashfunc(const K& key)
		{
			Ha _hash;
			return _hash(key);
		}
		void _Clear()
		{
			for (size_t i = 0; i < _table.size(); ++i)
			{
				Node* cur = _table[i];
				if (cur != nullptr)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_table[i] = nullptr;
			}
		}
	public:
		~hash()
		{
			_Clear();
		}
		iterator begin()
		{

			for (size_t i = 0; i < _table.size(); ++i)
			{
				Node* cur = _table[i];
				if (cur != nullptr)
					return iterator(_table[i],this);
			}
			return end();
		}
		iterator end()
		{
			return iterator(nullptr, this);
		}
		std::pair<iterator,bool> insert(const T& data)
		{
			KeyofT koft;
			if (_table.size() == 0 || (_num == _table.size()))
			{
				size_t newsize = _table.size() == 0 ? 10 : _table.size() * 2;
				std::vector<Node*> newtable;
				newtable.resize(newsize);
				for (size_t i = 0; i < _table.size(); ++i)
				{
					Node* cur = _table[i];
					while (cur != nullptr)
					{
						Node* next = cur->_next;
						//size_t index = koft(cur->_data) % newtable.size();
						//对于string等特殊类型，此处没有办法直接取模，需要进行特殊化处理
						size_t index = _hashfunc(koft(cur->_data)) % newtable.size();
						cur->_next = newtable[i];
						newtable[i] = cur;

						cur = next;
					}
					_table[i] = nullptr;
				}
				_table.swap(newtable);
			}
			//计算在表中的位置
			size_t index = _hashfunc(koft(data)) % _table.size();
			//判断是否在表中有相同的数据
			Node* cur = _table[index];
			while (cur != nullptr)
			{
				if (koft(cur->_data) == koft(data))
					return std::make_pair(iterator(cur,this),false);
				else
					cur = cur->_next;
			}
			Node* node = new Node(data);
			node->_next = _table[index];
			_table[index] = node;
			++_num;
			return std::make_pair(iterator(node,this),true);
		}

		iterator find(const K& key)
		{
			KeyofT koft;
			size_t index = _hashfunc(key) % _table.size();
			Node* cur = _table[index];
			while (cur != nullptr)
			{
				if (koft(cur->_data) ==key)
					return iterator(cur,this);
				else
					cur = cur->_next;
			}
			return iterator(nullptr, this);
		}

		bool erase(const K& key)
		{
			//先找该元素的位置
			KeyofT koft;
			size_t index = _hashfunc(key)%_table.size();
			//分两种情况，cur是第一个节点，删除是只需要指向它的后一个节点
			//不是第一个节点前一个节点指向它后一个节点
			Node* prev = nullptr;
			Node* cur = _table[index];
			while (cur != nullptr)
			{
				if (koft(cur->_data) == key)
				{
					if (prev == nullptr)
						_table[index] = cur->_next;
					else
						prev->_next = cur->_next;
					delete cur;
					cur = nullptr;
					return true;
				}
				else
				{
					prev = cur;
					cur = cur->_next;
				}


			}
			return false;
		}
		size_t size()
		{
			return _num;
		}
		bool empty()
		{
			bool ret = _num == 0 ? true : false;
			return ret;
		}

	private:
		std::vector<Node*> _table;
		size_t            _num=0;

	};


}