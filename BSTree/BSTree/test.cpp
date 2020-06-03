#define _CRT_SECURE_NO_WARNINGS 1
#include"BSTree.h"

void Test()
{
	int a[] = { 5, 3, 4, 1, 7, 8, 2, 6, 0, 9 };
	BSTree<int> bst;
	for (auto e : a)
	{
		bst.insert(e);
		
	}
	bst.Inorder();
	for (auto e : a)
	{
		//bst.erase(e);
		bst.eraseRecursive(e);
		bst.Inorder();
	}

	bst.Inorder();

}





int main()
{
	Test();
	return 0;
}