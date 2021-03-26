#include<iostream>
#include<vector>
#include<map>
#include<string>
#include<queue>
using namespace std;




namespace matrix{
	template<class V,class W,bool Direction=false>
	class Graph{
	public:
		Graph(V* vertex,size_t size)
		{
			
			for (size_t i = 0; i < size; ++i)
			{
				_vertex.push_back(vertex[i]);
				_vertexIndex[vertex[i]] = i;
			}
			_matrix.resize(size);
			
			for (size_t  i = 0; i < size; ++i)
			{
				_matrix[i].resize(size, W());
			}
		}
		int GetIndexofVertex(const V& v)
		{
			map<V, int>::iterator Index = _vertexIndex.find(v);
			if (Index != _vertexIndex.end())
			{
				return Index->second;
			}
			return -1;
		}
		void  ConnectVertex(const V& src, const V& des, const W& w)
		{
			int srcIndex=GetIndexofVertex(src);
			if (srcIndex == -1)
			{
				printf("起始顶点不存在\n");
				return;
			}
			int desIndex = GetIndexofVertex(des);
			if (desIndex == -1)
			{
				printf("目标顶点不存在\n");
				return;
			}
			_matrix[srcIndex][desIndex] = w;
			if (Direction == false)
			{
				_matrix[desIndex][srcIndex] = w;
			}

		}
		 void _DFS(int index, vector<bool>& visited)
		{
			cout << _vertex[index] << endl;
			visited[index] = true;
			for (size_t i = 0; i < _vertex.size(); ++i)
			{
				if (_matrix[index][i] !=W() && visited[i] == false)
				{
					_DFS(i, visited);
				}
			}

		}
		void DFS(const V& v)
		{
			int index = GetIndexofVertex(v);
			if (index == -1)
			{
				printf("查询的目标不存在\n");
				return;
			}
			vector<bool> visited(_vertex.size(), false);
			_DFS(index, visited);
			return;
		}

		void BFS(const V& v)
		{
			int index = GetIndexofVertex(v);
			if (index == -1)
			{
				printf("查询的目标不存在\n");
				return;
			}
			vector<bool> visited(_vertex.size(), false);
			queue<int> q;
			q.push(index);
			while (!q.empty())
			{
				int front = q.front();
				q.pop();
				visited[front] = true;
				cout << _vertex[front] << endl;
				
				for (int i = 0; i < _matrix.size(); ++i)
				{
					if (_matrix[front][i] != W() && visited[i] == false)
					{
						q.push(i);
						visited[i] = true;
					}
				}
			}
			cout << endl;
		}

	private:
		std::vector<V> _vertex;//存放顶点
		map<V, int>     _vertexIndex;//顶点在矩阵中对应下标
		std::vector<vector<W>> _matrix;//矩阵：表示边与边之间的关系
	};

	void TestGraph()
	{
		string strs[] = { "保罗", "詹姆斯", "韦德", "加内特", "科比", "库里" };
		Graph<string, int> g(strs, sizeof(strs) / sizeof(string));

		g.ConnectVertex("保罗", "詹姆斯", 95);
		g.ConnectVertex("韦德", "詹姆斯", 99);
		g.ConnectVertex("库里", "詹姆斯", 80);
		g.ConnectVertex("库里", "詹姆斯", 80);
		g.ConnectVertex("科比", "詹姆斯", 85);
		g.ConnectVertex("科比", "加内特", 80);
		g.ConnectVertex("科比", "韦德", 85);
		//g.DFS("詹姆斯");
		g.BFS("詹姆斯");
	}
}


namespace list{
	template<class W>
	struct ListNode{
		size_t _srcIndex;
		size_t _desIndex;
		W  _w;
		ListNode<W>* _next;
	};
	template<class V,class W,bool Direction=flase>
	class Graph{
		Graph(const V* vertex,size_t size)
		{
			_vertexIndex.reserve(size);
			for (int i = 0; i < vertex.size(); ++i)
			{
				_vertex.push_back(vertex[i]);
				_vertexIndex[vertex[i]] = i;
			}
			_edge.reserve(n, nullptr);
			
		}
		int GetIndexofVertex(const V& v)
		{
			iterator Index = _vertexIndex.find(v);
			if (Index != _vertexIndex.end())
			{
				return Index->second;
			}
			return -1;
		}

		void  ConnectVertex(const V& src, const V& des, const W& w)
		{
			int srcIndex = GetIndexofVertex(src);
			if (srcIndex == -1)
			{
				printf("起始顶点不存在\n");
				return;
			}
			int desIndex = GetIndexofVertex(des);
			if (desIndex == -1)
			{
				printf("目标顶点不存在\n");
				return;
			}

			//申请一个新的节点
			ListNode<W>* node = new ListNode;
			node->_srcIndex = srcIndex;
			node->_desIndex=desIndex;
			node->_w = w;
			//进行头插
			node->_next = _vertexIndex[srcIndex];
			_vertexIndex[srcIndex] = node;

			if (Direction == false)
			{
				ListNode<W>* node = new ListNode;
				node->_srcIndex = desIndex;
				node->_desIndex = srcIndex;
				node->_w = w;

				node->_next = _vertexIndex[desIndex];
				_vertexIndex[desIndex] = node;
			}
		}


	private:
		vector<V> _vertex;            //顶点集合
		map<V, int> _vertexIndex;     //顶点对应的链表下标
		vector<ListNode<W>*> _edge;   //邻接表
	};


}