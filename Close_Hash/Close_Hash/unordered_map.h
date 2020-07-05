#pragma once
#include"Close_Hash.h"


namespace MAP{

	
	

	template <class K, class V>
	class unordered_map{
		template <class K, class V>
		struct MapKeyofValue{
			const K& operator() (const std::pair<K, V>& key)
			{
				return key.first;
			}
		};
		public:
		bool insert(const std::pair<K,V>& kv)
		{
			return _hash.insert(kv);
		}
		bool erase(const std::pair<K, V>& kv)
		{
			return _hash.erase(kv);
		}
		 std::pair<K, V>* find(const std::pair<K, V>& kv)
		{
			return  _hash.find(kv);

		}
	private:
		CloseHash::Hashtable<K, std::pair<K,V> , MapKeyofValue<K,V>>  _hash;
	};

	void test_maphash()
	{
		MAP::unordered_map<int, int> hashmap;
		hashmap.insert(std::make_pair(1, 1));
		hashmap.insert(std::make_pair(11, 11));
		hashmap.insert(std::make_pair(111, 111));
		hashmap.insert(std::make_pair(2, 2));
		hashmap.insert(std::make_pair(3, 3));
		hashmap.insert(std::make_pair(4, 4));

		hashmap.find(std::make_pair(2, 3));
	}



}