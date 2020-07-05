#pragma once
#include"Close_Hash.h"



namespace SET{

	template <class K>
	struct KeyofValue{
		const K& operator() (const K& key)
		{
			return key;
		}
	};

	template <class K>
	class unordered_set{
	public:
		bool insert(const K& key)
		{
			return _hash.insert(key);
		}
		bool erase(const K& key)
		{
			return _hash.erase(key);
		}
		K* find(const K& key)
		{
			 return  _hash.find(key);

		}
	private:
		CloseHash::Hashtable<K, K, KeyofValue<K>>  _hash;
	};
	void test_set()
	{
		unordered_set<int>  us;
		us.insert(1);
		us.insert(11);
		us.insert(111);
		us.insert(11111);
		us.insert(4);
		us.insert(2);

	}



}