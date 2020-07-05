#pragma once
#include<vector>


namespace CloseHash{
	enum status{
		Empty,
		Delete,
		Exit,
	};

	template<class T>
	struct HashData{
		T _data;
		status _status;
		/*HashData(const T& data)
			:_data(data)
			, _status(Exit)
		{}*/
	};


	template <class K,class T,class KeyofValue>
	class Hashtable{
		typedef HashData<T>  Data;
	private:
		std::vector<Data> _table; //哈希表，用来存放数据
		size_t    _num=0 ;   //记录哈希表中有效数据的个数
	public:
		//插入的时候我们什么时候需要进行扩容呢？等到满的时候是不可能的？
		//我们需要一个空的位置，进行判断是否还要继续进行查找
		//因此我们需要一个负载因子，等负载因子到达一个值或高于这个值的时候，我们就进行扩容
		bool insert(const T& data)
		{
			KeyofValue kofv;
			if ( _table.size() == 0 ||  _num * 10 / _table.size() >= 7  )
			{
				std::vector<Data> newtable;
				size_t newsize = _table.size() == 0 ? 10 : _table.size() * 2;
				newtable.resize(newsize);
				for (size_t i = 0; i < _table.size(); ++i)
				{
					if (_table[i]._status == Exit)
					{
						size_t newIndex = kofv(_table[i]._data) % newsize;
						while (newtable[newIndex]._status == Exit)
						{
							++newIndex;
							if (newIndex == newtable.size())
							{
								newIndex = 0;
							}
						}
						newtable[newIndex] = _table[i];
					}
				}
				_table.swap(newtable);
			}
			//线性探测
			/*size_t index = kofv(data) % _table.size();

			while (_table[index]._status == Exit)
			{
				if (kofv(_table[index]._data) == kofv(data))
					return false;
				++index;
				if (index == _table.size())
					index = 0;
			}
			_table[index]._data = data;
			_table[index]._status = Exit;
			++_num;
			return true;*/
			//二次探测
			size_t index = kofv(data) % _table.size();
			int i = 1;
				while (_table[index]._status == Exit)
				{
					if (kofv(_table[index]._data) == kofv(data))
						return false;
					index = index + i ^ 2;
					i++;
					index %= _table.size();
				}
				_table[index]._data = data;
				_table[index]._status = Exit;
				++_num;
				return true;

		}

		T* find(const T& data)
		{
			KeyofValue kofv;
			size_t index = kofv(data) % _table.size();
			while (_table[index]._status != Empty)
			{
				if (_table[index]._status != Empty&&kofv(_table[index]._data) == kofv(data))
				{
					if (_table[index]._status == Exit)
						return &(_table[index]._data);
					else if (_table[index]._status == Delete)
						return nullptr;
				}
					
				else
				{
					++index;
					if (index == _table.size())
						index = 0;
				}

			}
			return nullptr;
		}

		bool erase(const T& data)
		{
			Data* ret = find(data);
			if (ret != nullptr)
			{
				ret->_staus = Delete;
				--_num;
				return true;
			}
			return false;

		}
	
	};
}