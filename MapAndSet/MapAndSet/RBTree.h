#pragma once
#include<iostream>
#include<assert.h>
#include<algorithm>
#include<string>
using namespace std;

enum Color{
	Red,
	Black,
};


template<class T>
struct TreeNode
{
	TreeNode<T>* _left;
	TreeNode<T>* _right;
	TreeNode<T>* _parent;

	T _data;

	Color _color;

	TreeNode(const T& data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _color(Red)
	{}
};

template<class T,class Ref,class Ptr>
struct __TreeIterator{
	typedef TreeNode<T> Node;
	typedef __TreeIterator<T,Ref,Ptr> Self;
	Node* _node;

	__TreeIterator(Node* node)
		:_node(node)
	{}
  Ref  operator*()
	{
		return _node->_data;
	}
  Ptr  operator->()
  {
	  return &(_node->_data);
  }
  Self& operator++()
  {
	  if (_node->_right != nullptr)
	  {
		  //找最左节点
		  Node* nodeR = _node->_right;
		  while (nodeR->_left != nullptr)
		  {
			  nodeR = nodeR->_left;
		  }
		  _node = nodeR;
	  }
	  else
	  {
		  Node* cur = _node;
		  Node* parent = cur->_parent;
		  while (parent != nullptr&&cur == parent->_right)
		  {
			  cur = cur->_parent;
			  parent = parent->_parent;
		  }
		  _node = parent;
	  }
	  return *this;
  }
  Self& operator--()
  {
	  if (_node->_left != nullptr)
	  {
		  Node* nodeL = _node->_left;
		  while (nodeL != nullptr&&nodeL->_right != nullptr)
		  {
			  nodeL = nodeL->_right;
		  }
		  _node = nodeL;
	  }
	  else
	  {
		  Node* cur = _node;
		  Node* parent = cur->_parent;
		  while (parent != nullptr&&parent->_left == cur)
		  {
			  cur = parent;
			  parent = cur->_parent;
		  }

		  _node = parent;
	  }
	  return *this;
  }
  bool operator==(const Self&  self)
  {
	  return _node == self._node;
  }
  bool operator!=(const Self& self)
  {
	  return _node != self._node;
  }


};



template <class K,class T,class KofValue>
class RBTree{
	typedef TreeNode<T>  Node;
public:
	typedef __TreeIterator<T,T&,T*> iterator;
	typedef __TreeIterator< T,const T&,const T*> const_iterator;
	iterator begin()
	{
		Node* cur = _root;
		while (cur != nullptr&&cur->_left != nullptr)
		{
			cur = cur->_left;
		}
		return (iterator)cur;
	}
	iterator end()
	{
		return (iterator)nullptr;
	}
	pair<iterator,bool> insert(const T& data)
	{
		
		if (_root == nullptr)
		{
			_root = new Node(data);
			_root->_color = Black;
			return make_pair((iterator)(_root) ,true);
		}
		else
		{
			KofValue KofV;
			Node* parent = nullptr;
			Node* cur = _root;
			while (cur != nullptr)
			{
				if (   KofV(cur->_data) < KofV(data)  )
				{
					parent = cur;
					cur = cur->_right;
				}
				else if (KofV(cur->_data) >KofV(data))
				{
					parent = cur;
					cur = cur->_left;
				}
				else
				{
					return make_pair((iterator)cur, false );
				}
			}
			//插入新节点，将新节点默认给成红色
			
			cur = new Node(data);
			if (KofV(parent->_data) <KofV(data))
			{
				parent->_right = cur;
			}
			else if (KofV(parent->_data) >KofV(data))
			{
				parent->_left = cur;
			}
			cur->_color = Red;
			cur->_parent = parent;

			Node*  newnode = cur;


			//判断当前树是否符合红黑树性质，不符合则进行调整
			while (parent != nullptr&&parent->_color == Red)
			{
				Node* grandfather = parent->_parent;
				if (parent == grandfather->_left)
				{
					Node* uncle = grandfather->_right;
					if (uncle != nullptr&&uncle->_color == Red)
					{
						parent->_color = uncle->_color = Black;
						grandfather->_color = Red;
						cur = grandfather;
						parent = cur->_parent;
					}
					else
					{				
							if (cur == parent->_right)
							{
								RotateL(parent);
								swap(parent, cur);
							}							
								RotateR(grandfather);
								parent->_color = Black;
								grandfather->_color = Red;
								break;
					}
				}

				else   
				{
					Node* uncle = grandfather->_left;
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
							if (cur == parent->_left)
							{
								RotateR(parent);
								swap(cur, parent);

							}
							RotateL(grandfather);
							parent->_color = Black;
							grandfather->_color = Red;
							break;				
					}
				}

			}
			_root->_color = Black;
			return make_pair((iterator)(newnode),true);
		
		}

		
	}
	iterator find(const T&  key)
	{
		KofValue KofV;
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (KofV(cur->_data) <KofV(data))
			{
				cur = cur->_right;
			}
			else if (KofV(cur->_data) >KofV(data))
			{
				cur = cur->_left;
			}
			else
			{
				return (iterator)cur;
			}
		}
		return (iterator)nullptr;
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


private:
	Node* _root = nullptr;

};