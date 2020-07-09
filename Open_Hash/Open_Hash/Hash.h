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
	//������
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
		//�����ж�һ��_node���ڵ�Ͱ���жϵ�ǰ���Ͱ�Ƿ������ϣ�������ϵĻ���ȥѰ����һ�������ݵ�Ͱ
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
				//û���ҵ��Ļ���˵���ñ�û���κ�������
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
						//����string���������ͣ��˴�û�а취ֱ��ȡģ����Ҫ�������⻯����
						size_t index = _hashfunc(koft(cur->_data)) % newtable.size();
						cur->_next = newtable[i];
						newtable[i] = cur;

						cur = next;
					}
					_table[i] = nullptr;
				}
				_table.swap(newtable);
			}
			//�����ڱ��е�λ��
			size_t index = _hashfunc(koft(data)) % _table.size();
			//�ж��Ƿ��ڱ�������ͬ������
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
			//���Ҹ�Ԫ�ص�λ��
			KeyofT koft;
			size_t index = _hashfunc(key)%_table.size();
			//�����������cur�ǵ�һ���ڵ㣬ɾ����ֻ��Ҫָ�����ĺ�һ���ڵ�
			//���ǵ�һ���ڵ�ǰһ���ڵ�ָ������һ���ڵ�
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