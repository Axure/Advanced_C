#include <iostream>
#include <cstdlib>
#include <cstring>

// I wanna utilize std::pair...
// But where?
// Maybe somewhere else...
// You should write your code first, and you need to. Write what you can with the highest speed.



template<class T>
class Node
{
private:
	T mElement;
	Node<T> *mPrev, *mNext;

public:
	
	Node();
	Node(T element);
	~Node();
	void setToPrev(Node prevNode);
	void setToNext(Node nextNode);
	void print();

};

template<class T>
Node<T>::Node()
{

}

template<class T>
Node<T>::Node(T element)
{
	this->mElement = element;
}

template<class T>
class List
{
private:

public:
	List();
	~List();
	void addHead(T element);
	void addTail(T element);

};

template<class T>
class TreeNode
{
private:
	T mElement;
	TreeNode mParent, mLeft, mRight;

public:
	TreeNode();
	~TreeNode();
	void addToLeft(TreeNode leftTreeNode);
	void addToRight(TreeNode rightTreeNode);
};

class Token
{
private:
	int type;
	union {
		int number;
		char unaryOperator;
		char binaryOperator;
	} content;

public:

	Token();
	~Token();
	int getType();

};





// Please do not use STL!
template<class T>
class TokenToNode : Token
{
private:
	Node<T> _node;

};

template<class T>
class TokenToTreeNode : Token
{
private:
	TreeNode<T> _treeNode;

};



Token::Token()
{

}

Token::~Token()
{

}

int Token::getType()
{

}

// Token::getContent()
// {

// }

template<class T>
List<T>::List()
{

}

template<class T>
List<T>::~List()
{

}









int main(int argc, char const *argv[])
{
	List<int>();
	Node<int> myIntNode = new Node<int>(3);


	return 0;
}






