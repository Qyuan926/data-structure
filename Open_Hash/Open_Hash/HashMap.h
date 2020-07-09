#pragma once
#include"Hash.h"

namespace HashMap{
	template <class K, class V>
	struct MapKeyofT{
		K operator()(const std::pair<K, V>& data)
		{
			return data.first;
		}
	};

	template <class K, class V,class Ha=Hash::_hash<K>>
	class unordered_map{
		
	public:
		typedef typename Hash::hash_iterator<K, std::pair<K, V>, MapKeyofT<K, V>,Ha>  iterator;
		iterator begin()
		{
			return _table.begin();
		}
		iterator end()
		{
			return _table.end();
		}
		std::pair<iterator, bool> insert(std::pair<K, V> data)
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

		V& operator[](const K& key)
		{
			return _table.insert(std::make_pair(key, V())).first->second;
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
		Hash::hash<K, std::pair<K, V>, MapKeyofT<K,V>,Ha>  _table;
	};

}
