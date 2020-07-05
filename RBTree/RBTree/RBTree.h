#pragma once
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;

enum Color{
	Red,
	Black,
};

template <class K,class V>
struct TreeNode{
	TreeNode(const pair<K,V> data)   
	:_left(nullptr),
	_right(nullptr),
	_parent(nullptr),
	_data(data)
	{
		_color = Red;
	}

	TreeNode<K, V>* _left;
	TreeNode<K, V>* _right;
	TreeNode<K, V>* _parent;

	pair<K, V>  _data;
	Color   _color;
};


template <class K,class V>
class RBTree{
	typedef TreeNode<K,V>  Node;
public:
	bool insert(const pair<K, V>& data)
	{

		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_color = Black;
			return true;
		}
		else
		{
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur != nullptr)
			{
				if (cur->_data.first < data.first)
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (cur->_data.first>data.first)
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return false;
				}
			}
			//插入新节点，将新节点默认给成红色
			cur = new Node(data);
			if (parent->_data.first< data.first)
			{
				parent->_right = cur;
			}
			else if (parent->_data.first>data.first)
			{
				parent->_left = cur;
			}
			cur->_color = Red;
			cur->_parent = parent;


			//判断当前树是否符合红黑树性质，不符合则进行调整
			while (parent != nullptr&&parent->_color == Red)
			{
				Node* grandfather = parent->_parent;
				if (parent == grandfather->_left)
				{
					Node* uncle = grandfather->_right;
					//叔叔存在且为红色，那么我们只需要变色
					//父节点和叔叔节点变为黑色
					//祖父节点变为红色
					if (uncle != nullptr&&uncle->_color == Red)
					{
						parent->_color = uncle->_color = Black;
						grandfather->_color = Red;
						//向上更新
						cur = grandfather;
						parent = cur->_parent;
					}
					else
					{
						//叔叔不存在或者为黑色

						//如果叔叔不存在，cur一定是新插入的节点    父节点右旋加祖父变红  父节点变黑
						/*if (uncle == nullptr)
						{
							RotateR(parent);
							parent->_color = Black;
							grandfather->_color = Red;
							break;
						}*/
						//else if (uncle->_color == Black)
						
							//如果cur是父节点的左节点，右单旋+父节点变黑、祖父节点变红
							//如果cur是父节点的右节点，需要进行双旋操作


							//如果cur是父节点的右节点，需要进行双旋操作
							if (cur == parent->_right)
							{
								RotateL(parent);
								swap(parent, cur);
							}

							//如果cur是父节点的左节点，右单旋+父节点变黑、祖父节点变红
							//if (cur == parent->_left)
							
								RotateR(grandfather);
								parent->_color = Black;
								grandfather->_color = Red;
								break;
					}
				}

				else   //if (parent == grandfather->_right)
				{
					Node* uncle = grandfather->_left;
					//叔叔存在且为红色，那么我们只需要变色
					//父节点和叔叔节点变为黑色
					//祖父节点变为红色
					if (uncle != nullptr&&uncle->_color == Red)
					{
						parent->_color = uncle->_color = Black;
						grandfather->_color = Red;
						//向上更新
						cur = grandfather;
						parent = cur->_parent;
					}
					else
					{
						//叔叔不存在或者为黑色

						//如果叔叔不存在，cur一定是新插入的节点    父节点左旋加祖父变红  父节点变黑
						//if (uncle == nullptr)
						//{
						//	RotateL(parent);
						//	grandfather->_color = Red;
						//	parent->_color = Black;
						//	break;
						//}
						//叔叔节点存在且为黑色
						//else if (uncle->_color == Black)
						
							if (cur == parent->_left)
							{
								RotateR(parent);
								swap(cur, parent);

							}
							//如果cur为父节点的右节点，左单旋+父节点变红、祖父节点变黑
							//if(cur==parent->_right)
							RotateL(grandfather);
							parent->_color = Black;
							grandfather->_color = Red;
							break;

						
					}
				}

			}
			_root->_color = Black;
			return true;
		
		}

		
	}
private:
	void RotateR(Node* parent)
	{
		Node* parentL = parent->_left;
		Node* parentLR = parentL->_right;

		parent->_left = parentLR;
		if (parentLR != nullptr)
			parentLR->_parent = parent;
		parentL->_right = parent;


		if (parent->_parent == nullptr)
		{
			_root = parentL;
			parentL->_parent = nullptr;
		}
		else
		{
			Node* pparent = parent->_parent;
			if (pparent->_left == parent)
				pparent->_left = parentL;
			else
				pparent->_right = parentL;

			parentL->_parent = pparent;
		}

		parent->_parent = parentL;


	}
	void RotateL(Node* parent)
	{
		Node* parentR = parent->_right;
		Node* parentRL = parentR->_left;

		parent->_right = parentRL;
		if (parentRL != nullptr)
			parentRL->_parent = parent;

		parentR->_left = parent;

		if (parent == _root)
		{
			_root = parentR;
			parentR->_parent = nullptr;
		}
		else
		{
			Node* pparent = parent->_parent;
			if (pparent->_left == parent)
				pparent->_left = parentR;
			else
				pparent->_right = parentR;

			parentR->_parent = pparent;
		}
		parent->_parent = parentR;

		
	}

public:
	

	void InOrder()
	{
		_InOrder(_root);
	}

	bool IsValidRBTree()
	{
		Node* pRoot = _root;
		// 空树也是红黑树
		if (nullptr == pRoot)
			return true;

		// 检测根节点是否满足情况
		if (Black != pRoot->_color)
		{
			cout << "违反红黑树性质二：根节点必须为黑色" << endl;
			return false;
		}

		// 获取任意一条路径中黑色节点的个数
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (Black == pCur->_color)
				blackCount++;

			pCur = pCur->_left;
		}

		// 检测是否满足红黑树的性质，k用来记录路径中黑色节点的个数
		size_t k = 0;
		return _IsValidRBTree(pRoot, k, blackCount);
	}

	private:
	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;

		_InOrder(root->_left);
		cout << root->_data.first << ":" << root->_data.second << endl;
		_InOrder(root->_right);
	}

	bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		//走到null之后，判断k和black是否相等
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;
		}

		// 统计黑色节点的个数
		if (Black == pRoot->_color)
			k++;

		// 检测当前节点与其双亲是否都为红色
		Node* pParent = pRoot->_parent;
		if (pParent && Red == pParent->_color && Red == pRoot->_color)
		{
			cout << pParent->_data.first << endl;
			cout << "违反性质三：没有连在一起的红色节点" << endl;
			return false;
		}

		return _IsValidRBTree(pRoot->_left, k, blackCount) &&
			_IsValidRBTree(pRoot->_right, k, blackCount);
	}
public:
	Node* find(const K&  key)
	{
		
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_data.first < key)
			{
				cur=cur->_right;
			}
			else if (cur->_data.first>key)
			{
				cur = cur->_left;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}



private:
	Node* _root = nullptr;

};