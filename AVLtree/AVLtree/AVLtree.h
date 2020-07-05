#pragma once
#include<iostream>
#include<assert.h>
#include<algorithm>
using namespace std;

template <class K,class V>
struct AVLtreeNode{



	AVLtreeNode<K,V>*  _left;
	AVLtreeNode<K,V>*  _right;
	AVLtreeNode<K,V>* _parent;
	pair<K,V>  _data;
	int _bf;

	AVLtreeNode(const pair<K, V>& data)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _data(data)
		, _bf(0)
	{}
};

template <class K,class V>
class AVLtree{
	typedef AVLtreeNode<const K,V> Node;
public:
	AVLtree() = default;
	
	~AVLtree()
	{
		_Destory(_root);
		_root = nullptr;
	}
	bool insert(const pair< K, V>& data)
	{
		//����Ҫ�����λ��
		   //���ǿ���
		if (_root == nullptr)
		{
			_root = new Node(data);
			return true;
		}
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
				//�ҵ���Ҫ����Ľڵ���ͬ�Ľڵ�
				return false;
			}
		}
		//�ҵ���Ҫ�����λ��cur
		cur = new Node(data);
		if (parent->_data.first<data.first)
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}
		
		//��������ڵ�����ȵ�ƽ�����ӣ�������Ҫ���ʱ��Ҫ������ת���ﵽҪ��
		while (parent != nullptr)
		{
			if (cur == parent->_right)
			{
				parent->_bf++;
			}
			else if (cur == parent->_left)
			{
				parent->_bf--;
			}

			if (parent->_bf == 0)
			{//�ø��ڵ��ƽ������Ϊ0��ʱ�򣬸��ڵ����ڵ������߶���û����֮ǰ�ĸ߶���ͬ��������Ľṹû���κ�Ӱ�죬����Ҫ�����ڵ���
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1)
			{
				//���ϵ���
				cur = parent;
				parent = cur->_parent;
			}
			else if (parent->_bf == 2 || parent->_bf == -2)
			{
				//������ƽ���������������������Ҫ��ת����������
				if (parent->_bf == 2 && cur->_bf == 1)
					RotateL(parent);
				if (parent->_bf == -2 && cur->_bf == -1)
					RotateR(parent);
				if (parent->_bf == 2 && cur->_bf == -1)
					RotateRL(parent);
				if (parent->_bf == -2 && cur->_bf == 1)
					RotateLR(parent);

				break;
			}
			else
			{//ƽ������������������������ĳ��λ�ó���ֱ�ӱ���
				assert(false);
			}
		}
		return true;
	}
	Node* find(const K&  key)
	{
		Node* cur = _root;
		while (cur != nullptr)
		{
			if (cur->_data.first < key)
				cur = cur->_right;
			else if (cur->_data.first>key)
				cur = cur->_left;
			else
				return cur;

		}
		return nullptr;
		
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

		//����ƽ������
		parent->_bf = parentL->_bf = 0;

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

		parent->_bf = parentR->_bf = 0;
	}
	void RotateRL(Node* parent)
	{
		Node* parentR = parent->_right;
		Node* parentRL = parentR->_left;
		int bf = parentRL->_bf;

		RotateR(parent->_right);
		RotateL(parent);
		if (bf == -1)
		{
			parent->_bf = parentRL->_bf = 0;
			parentR->_bf = 1;
		}
		else if (bf == 1)
		{
			parentR->_bf = parentRL->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == 0)
		{
			parent->_bf = parentR->_bf = parentRL->_bf = 0;
		}

	}
	void RotateLR(Node* parent)
	{
		Node* parentL = parent->_left;
		Node* parentLR = parentL->_right;
		int bf = parentLR->_bf;

		RotateL(parent->_left);
		RotateR(parent);

		if (bf == -1)
		{
			parentL->_bf = parentLR->_bf = 0;
			parent->_bf = 1;
		}
		else if (bf == 1)
		{
			parentL->_bf = -1;
			parent->_bf = parentLR->_bf = 0;
		}
		else if (bf == 0)
		{
			parent->_bf = parentL->_bf = parentLR->_bf = 0;
		}
	}
	public:
		void IsBanlance()
		{
			if (_IsBanlance(_root))
			{
				cout << "is banlance" << endl;
				_Inorder(_root);
				cout << endl;
			}
			else
			{
				cout << "not banlance" << endl;
			}
		}
	private:
		void _Inorder(Node* root)
		{
			if (root == nullptr)
				return;
			_Inorder(root->_left);
			cout << root->_data.first << " ";
			_Inorder(root->_right);
		}
		bool _IsBanlance(Node* root)
		{
			if (root == nullptr)
				return true;
			int lefthigh = _Depth(root->_left);
			int righthigh = _Depth(root->_right);
			if (righthigh - lefthigh != root->_bf)
			{
				cout << root->_data.first<<" :bf�쳣" << endl;
			}
			return abs(lefthigh - righthigh) < 2 && _IsBanlance(root->_left) && _IsBanlance(root->_right);
		}
		int _Depth(Node* root)
		{
			if (root == nullptr)
				return 0;
			return max(_Depth(root->_left), _Depth(root->_right)) + 1;
		}
		void _Destory(Node* root)
		{
			if (root == nullptr)
				return;
			_Destory(root->_left);
			_Destory(root->_right);
			delete root;
		}


private:
	Node* _root = nullptr;

};






