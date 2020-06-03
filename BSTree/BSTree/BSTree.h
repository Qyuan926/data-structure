#pragma once
#include<iostream>
using namespace  std;

template <class T>
struct BSTreeNode{
	struct BSTreeNode<T>* _left;
	struct BSTreeNode<T>*  _right;
	T _val;
	BSTreeNode(const T& val )
		:_left(nullptr)
		, _right(nullptr)
		, _val(val)
	{}
};

template <class T>
class BSTree{
	typedef struct BSTreeNode<T> Node;
public:	
	bool insert( const T& val)
	{
		//如果根为空的话，直接构建根
		if (_root == nullptr)
		{
			_root = new Node(val);
			return true;
		}
		//不为空找到应该插入的位置，你申请的只是一个节点，没有与树相连接
		//所以你必须找到父节点，经过判断在进行连接，称为树节点
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur!=nullptr)
		{
			parent = cur;
			if (cur->_val < val)
				cur = cur->_right;
			else if (cur->_val>val)
				cur = cur->_left;
			else
				return false;
		}
		cur = new Node(val);
		if (parent->_val > val)
			parent->_left = cur;
		else
			parent->_right = cur;
		return true;
		
	}
	bool _insertRecursive(Node*& node, const T& val)
	{
		if (node == nullptr)
		{
			node = new Node(val);
			return true;
		}
		if (node->_val > val)
		{
			_insertRecursive(node->_left,val);
		}
		else if (node->_val < val)
		{
			_insertRecursive(node->_right,val);
		}
		else
		{
			return false;
		}
	}

	bool insertRecursive(const T& val)
	{
		return _insertRecursive(_root,val);
	}

	Node* find(const T& val)
	{
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_val > val)
			{
				cur = cur->_left;
			}
			else if (cur->_val < val)
			{
				cur = cur->_right;
			}
			else
			{
				return cur;
			}
		}
		return nullptr;
	}
	Node* _findRecursive(Node* node, const T& val)
	{
		if (node == nullptr)
			return nullptr;
		if (node->_val > val)
		{
			_findRecursive(node->_left, val);

		}
		else if (node->_val < val)
		{
			_findRecursive(node->_right, val);
		}
		else
		{
			return node;
		}
	}
	Node* findRecursive(const T& val)
	{
		return _findRecursive(_root, val);
	}
	bool erase(const T& val)
	{
		Node* parent = nullptr;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_val > val)
			{
				parent = cur;
				cur = cur->_left;
			}
			else if (cur->_val < val)
			{
				parent = cur;
				cur = cur->_right;
			}
			else
			{
				if (cur->_left == nullptr)
				{
					if (parent == nullptr) //删除左子树为空的根节点
					{
						_root = cur->_right;
					}
					else
					{
						if (cur == parent->_left)
							parent->_left = cur->_right;
						else
							parent->_right = cur->_right;
						delete cur;
					}
				}
				else if (cur->_right == nullptr)//右子树为空
				{
					if (parent == nullptr)
					{//删除右子树为空的根节点{
						_root = cur->_left;
					}
					else
					{
						if (cur == parent->_left)
							parent->_left = cur->_left;
						else
							parent->_right = cur->_left;
						delete cur;
					}

				}
				else
				{//左、右子树都不为空
					Node* minNodeparent = cur;
					Node* minNode = cur->_right;
					while (minNode->_left != nullptr)
					{
						minNodeparent = minNode;
						minNode = minNode->_left;
					}
					swap(cur->_val, minNode->_val);
					if (minNodeparent->_left == minNode)
						minNodeparent->_left = minNode->_right;
					else
						minNodeparent->_right = minNode->_right;
					delete minNode;
				}	
				return true;
			}
		}
		return false;
	}
	bool _eraseRecursive(Node*& node, const T& val)
	{
		if (node == nullptr)
			return false;
		if (node->_val > val)
		{
			return _eraseRecursive(node->_left, val);
		}
		else if (node->_val < val)
		{
			return _eraseRecursive(node->_right, val);
		}
		else
		{
			Node* del = node;
			if (node->_left == nullptr)
			{
				node = node->_right;
				delete del;
				return true;
			}
			else if (node->_right == nullptr)
			{
				node = node->_left;
				delete del;
				return true;
			}
			else
			{//找右子树的最小值
				Node* minNode = node->_right;
				while (minNode->_left!=nullptr)
				{
					minNode = minNode->_left;
				}
				node->_val = minNode->_val;
				return _eraseRecursive(node->_right, minNode->_val);

			}
		}


	}
	
	bool eraseRecursive(const T& val)
	{
		return _eraseRecursive(_root, val);
		
	}


	void _Inorder(Node* Node)
	{
		if (Node == nullptr)
			return;
		_Inorder( Node->_left);
		cout << Node->_val << " ";
		_Inorder(Node->_right);
	}
	void Inorder()
	{
		_Inorder(_root);
		cout << endl;
	}

private:
	Node* _root = nullptr;
};



