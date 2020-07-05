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
			//�����½ڵ㣬���½ڵ�Ĭ�ϸ��ɺ�ɫ
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


			//�жϵ�ǰ���Ƿ���Ϻ�������ʣ�����������е���
			while (parent != nullptr&&parent->_color == Red)
			{
				Node* grandfather = parent->_parent;
				if (parent == grandfather->_left)
				{
					Node* uncle = grandfather->_right;
					//���������Ϊ��ɫ����ô����ֻ��Ҫ��ɫ
					//���ڵ������ڵ��Ϊ��ɫ
					//�游�ڵ��Ϊ��ɫ
					if (uncle != nullptr&&uncle->_color == Red)
					{
						parent->_color = uncle->_color = Black;
						grandfather->_color = Red;
						//���ϸ���
						cur = grandfather;
						parent = cur->_parent;
					}
					else
					{
						//���岻���ڻ���Ϊ��ɫ

						//������岻���ڣ�curһ�����²���Ľڵ�    ���ڵ��������游���  ���ڵ���
						/*if (uncle == nullptr)
						{
							RotateR(parent);
							parent->_color = Black;
							grandfather->_color = Red;
							break;
						}*/
						//else if (uncle->_color == Black)
						
							//���cur�Ǹ��ڵ����ڵ㣬�ҵ���+���ڵ��ڡ��游�ڵ���
							//���cur�Ǹ��ڵ���ҽڵ㣬��Ҫ����˫������


							//���cur�Ǹ��ڵ���ҽڵ㣬��Ҫ����˫������
							if (cur == parent->_right)
							{
								RotateL(parent);
								swap(parent, cur);
							}

							//���cur�Ǹ��ڵ����ڵ㣬�ҵ���+���ڵ��ڡ��游�ڵ���
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
					//���������Ϊ��ɫ����ô����ֻ��Ҫ��ɫ
					//���ڵ������ڵ��Ϊ��ɫ
					//�游�ڵ��Ϊ��ɫ
					if (uncle != nullptr&&uncle->_color == Red)
					{
						parent->_color = uncle->_color = Black;
						grandfather->_color = Red;
						//���ϸ���
						cur = grandfather;
						parent = cur->_parent;
					}
					else
					{
						//���岻���ڻ���Ϊ��ɫ

						//������岻���ڣ�curһ�����²���Ľڵ�    ���ڵ��������游���  ���ڵ���
						//if (uncle == nullptr)
						//{
						//	RotateL(parent);
						//	grandfather->_color = Red;
						//	parent->_color = Black;
						//	break;
						//}
						//����ڵ������Ϊ��ɫ
						//else if (uncle->_color == Black)
						
							if (cur == parent->_left)
							{
								RotateR(parent);
								swap(cur, parent);

							}
							//���curΪ���ڵ���ҽڵ㣬����+���ڵ��졢�游�ڵ���
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
		// ����Ҳ�Ǻ����
		if (nullptr == pRoot)
			return true;

		// �����ڵ��Ƿ��������
		if (Black != pRoot->_color)
		{
			cout << "Υ����������ʶ������ڵ����Ϊ��ɫ" << endl;
			return false;
		}

		// ��ȡ����һ��·���к�ɫ�ڵ�ĸ���
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (Black == pCur->_color)
				blackCount++;

			pCur = pCur->_left;
		}

		// ����Ƿ��������������ʣ�k������¼·���к�ɫ�ڵ�ĸ���
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
		//�ߵ�null֮���ж�k��black�Ƿ����
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "Υ�������ģ�ÿ��·���к�ɫ�ڵ�ĸ���������ͬ" << endl;
				return false;
			}
			return true;
		}

		// ͳ�ƺ�ɫ�ڵ�ĸ���
		if (Black == pRoot->_color)
			k++;

		// ��⵱ǰ�ڵ�����˫���Ƿ�Ϊ��ɫ
		Node* pParent = pRoot->_parent;
		if (pParent && Red == pParent->_color && Red == pRoot->_color)
		{
			cout << pParent->_data.first << endl;
			cout << "Υ����������û������һ��ĺ�ɫ�ڵ�" << endl;
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