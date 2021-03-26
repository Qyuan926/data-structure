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
				printf("��ʼ���㲻����\n");
				return;
			}
			int desIndex = GetIndexofVertex(des);
			if (desIndex == -1)
			{
				printf("Ŀ�궥�㲻����\n");
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
				printf("��ѯ��Ŀ�겻����\n");
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
				printf("��ѯ��Ŀ�겻����\n");
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
		std::vector<V> _vertex;//��Ŷ���
		map<V, int>     _vertexIndex;//�����ھ����ж�Ӧ�±�
		std::vector<vector<W>> _matrix;//���󣺱�ʾ�����֮��Ĺ�ϵ
	};

	void TestGraph()
	{
		string strs[] = { "����", "ղķ˹", "Τ��", "������", "�Ʊ�", "����" };
		Graph<string, int> g(strs, sizeof(strs) / sizeof(string));

		g.ConnectVertex("����", "ղķ˹", 95);
		g.ConnectVertex("Τ��", "ղķ˹", 99);
		g.ConnectVertex("����", "ղķ˹", 80);
		g.ConnectVertex("����", "ղķ˹", 80);
		g.ConnectVertex("�Ʊ�", "ղķ˹", 85);
		g.ConnectVertex("�Ʊ�", "������", 80);
		g.ConnectVertex("�Ʊ�", "Τ��", 85);
		//g.DFS("ղķ˹");
		g.BFS("ղķ˹");
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
				printf("��ʼ���㲻����\n");
				return;
			}
			int desIndex = GetIndexofVertex(des);
			if (desIndex == -1)
			{
				printf("Ŀ�궥�㲻����\n");
				return;
			}

			//����һ���µĽڵ�
			ListNode<W>* node = new ListNode;
			node->_srcIndex = srcIndex;
			node->_desIndex=desIndex;
			node->_w = w;
			//����ͷ��
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
		vector<V> _vertex;            //���㼯��
		map<V, int> _vertexIndex;     //�����Ӧ�������±�
		vector<ListNode<W>*> _edge;   //�ڽӱ�
	};


}