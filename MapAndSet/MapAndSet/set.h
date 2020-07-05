#pragma once
#include"RBTree.h"

namespace Set{

	template<class K>
	class set{
		struct SetKofValue{
			const K& operator()(const K& data)
			{
				return data;
			}

		};
	public:
		typedef typename RBTree<K, K, SetKofValue>::iterator iterator;
		iterator begin()
		{
			return _tree.begin();
		}
		iterator end()
		{
			return _tree.end();
		}
		pair<iterator,bool> insert(const K& data)
		{
			return _tree.insert(data);
		}
		bool find(const K& data)
		{
			return _tree.find(data);
		}





	private:
		RBTree<K, K, SetKofValue> _tree;
	};






}