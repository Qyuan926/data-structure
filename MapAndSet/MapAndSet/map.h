#pragma once
#include"RBTree.h"


namespace Map{

	template<class K, class V>
	
	class map{
		struct MapKofValue{
	    const K&	operator()(const pair<K, V>& data)
			{
				return data.first;
			}

		};
	public:
		typedef typename RBTree<K, pair<K, V>, MapKofValue>::iterator  iterator;
		iterator begin()
		{
			return _tree.begin();
		}
		iterator end()
		{
			return _tree.end();
		}
		pair<iterator,bool> insert(const pair<K, V>& data)
		{
			return _tree.insert(data);
		}
		iterator find(const pair<K, V>& data)
		{
			return _tree.find(data);
		}
		//   (*((ret).first)).second   (*(it)).second        (*( it).second
		V& operator[](const K& key)
		{
			/*pair<iterator, bool> ret = this->insert(make_pair(key, V()));
			iterator it = ret.first;
			return (*it).second;*/

			pair<iterator, bool> ret = _tree.insert(make_pair(key, V()));
			return ret.first->second;
		}

	private:
		RBTree<K, pair<K, V>, MapKofValue> _tree;
	};






}