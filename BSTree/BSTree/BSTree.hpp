#include<iostream>
using namespace std;

template<class T>
struct BSTNode
{
	//�����������ڵ�Ĵ���
	BSTNode(const T& data = T())//T() :��Ϊ�����������ʾ0����Ϊ�Զ��������������ʽ��������
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
     //����
	BSTree()
	{}

	//����


	//����


	//ɾ��


	//����Ҷ�ӽڵ�


	//����Ҷ�ӽڵ�


	//�������

	void Inorder()
	{
		return Inorder(_pRoot);
	}
private:



private:
	BSTNode<T>* _pRoot;
};
