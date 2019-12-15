#include<iostream>
using namespace std;

template<class T>
struct BSTNode
{
	//二叉搜索树节点的创建
	BSTNode(const T& data = T())//T() :若为内置类型则表示0，若为自定义类型则必须显式给出构造
		:_pLeft(nullptr)
		,_pRight(nullptr)
		,_data(data)

	BSTNode<T>* _pLeft;
	BSTNode<T>* _Right;
	T _data;
};

template<class T>
class BSTree
{
public:
     //构造
	BSTree()
	{}

	//插入


	//查找


	//删除


	//最左叶子节点


	//最右叶子节点


	//中序遍历

	void Inorder()
	{
		return Inorder(_pRoot);
	}
private:



private:
	BSTNode<T>* _pRoot;
};
