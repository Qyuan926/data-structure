#pragma once
#include"Hash.h"

namespace HashSet{
	template <class K>
	struct SetKeyofT
	{
		K operator()(const K& key)
		{
			return key;
		}
	};

	template <class K, class Ha = Hash::_hash<K>>
	class unordered_set{
	public:
		typedef typename Hash::hash_iterator<K, K, SetKeyofT<K>, Ha>  iterator;
		iterator begin()
		{
			return _table.begin();
		}
		iterator end()
		{
			return _table.end();
		}
		std::pair<iterator, bool> insert(K data)
		{
			return _table.insert(data);
		}

		iterator find(const K& key)
		{
			return _table.find(key);
		}

		bool erase(const K& key)
		{
			return _table.erase(key);
		}

		bool empty()
		{
			return _table.empty();
		}
		size_t size()
		{
			return _table.size();
		}



	private:
		Hash::hash<K, K, SetKeyofT<K>, Ha> _table;
	};

}