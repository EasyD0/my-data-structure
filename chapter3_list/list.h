#include "listnode.h"
#include <cstddef>
#include <functional>
#include <vector>

template <typename T>
class List{

private:
	size_t _size = 0;
	ListNode<T> *header;
	ListNode<T> *trailer;
	~List(); //TODO:析构函数

public:
	List(){init();};
	List(const std::vector<T> &v); //转换构造函数

	size_t size() const { return _size; }
	bool empty() const { return _size <= 0; }

	void init();

	ListNode<T>* first() const { return header->succ; }
	ListNode<T>* last() const { return trailer->pred; }
	
	//插入
	ListNode<T>* insertAsFirst(const T &e);
	ListNode<T>* insertAsLast(const T &e);
	ListNode<T>* insertBefore(ListNode<T> *p, const T &e);
	ListNode<T>* insertAfter(ListNode<T> *p, const T &e);

	//删除
	T remove(ListNode<T> *p);
	T reomve(const size_t &r);

	//查找相关
	ListNode<T>& operator[](const size_t &r); //重载下标运算符

	ListNode<T>* begin()const {return _size>0? header->succ:nullptr;}
	ListNode<T>* end()const {return _size>0? trailer->pred:nullptr;}
	ListNode<T>* find(const T &e) const;
	ListNode<T>* find(const T &e, ListNode<T>* bg, ListNode<T>* ed) const;

	//去重
	size_t deduplicate(); //无序列表去重
	size_t uniquify(); //有序列表去重
	//遍历处理
	void traverses(std::function<void(T&)> func);

};

template<typename T>
void List<T>::init(){ //初始化列表
	header = new ListNode<T>(T{}, nullptr, nullptr);
	trailer = new ListNode<T>(T{}, header, nullptr);
	header->succ = trailer;
	_size = 0;
}

template<typename T>
List<T>::List(const std::vector<T> &v){	//转换构造函数
	init();
	
	if (v.empty()) return;
	
	for(auto &e:v)
		insertAsLast(e);
}

//插入节点
template<typename T>
ListNode<T>* List<T>::insertAsFirst(const T &e) //在首节点之后插入
{ header->insertAsSucc(e);_size++;}

template<typename T>
ListNode<T>* List<T>::insertAsLast(const T &e) //在末节点之前插入
{ trailer->insertAsPred(e);_size++; }

template<typename T>
ListNode<T>* List<T>::insertBefore(ListNode<T> *p, const T &e) //在p之前插入
{ p->insertAsPred(e);_size++; }

template<typename T>
ListNode<T>* List<T>::insertAfter(ListNode<T> *p, const T &e) //在p之后插入
{ p->insertAsSucc(e);_size++; }

//删除节点
template<typename T>
T List<T>::remove(ListNode<T> *p){ //删除节点p
	if (p==header || p==trailer){
		return T{}; //值初始化
	}

	T e = p->data;

	auto the_pred=p->pred;
	auto the_succ=p->succ;

	the_pred->succ = the_succ;
	the_succ->pred = the_pred;
	
	_size--;
	return e;
}

template<typename T>
T List<T>::reomve(const size_t &r){ //删除第r个节点
	if (r>=_size) return T{};
	auto p = &(*this)[r];
	return remove(p);
}

//查找相关
template<typename T>
ListNode<T>& List<T>::operator[](const size_t &r){ //这个函数复杂度高，不建议使用
	auto p = begin();
	long int index = 0;
	while(index++<r){
		p = p->succ;
	}
	return *p;
}

template<typename T>
ListNode<T>* List<T>::find(const T &e) const{ //无序列表暴力查找
	long int tempsize = _size;
	auto p = begin();
	while(tempsize--){
		if (p->data == e) return p;
		p = p->succ;
	}	
}

template<typename T>
ListNode<T>* List<T>::find(const T &e, ListNode<T>* bg, ListNode<T>* ed) const
{
	auto p = bg;
	while(p!=ed && p->data!=e)
		p = p->succ;

	return p==ed? nullptr:p;
}

//去重
template<typename T>
size_t List<T>::deduplicate() //无序列表去重
{
	if (_size<2) return 0;
	auto oldsize = _size;
	auto p = begin();

	while(p!=trailer){
		auto q = find(p->data,header,p);
		if (q)
			remove(q);
		p = p->succ;
	}
	return oldsize - _size;
}

//遍历
template<typename T>
void List<T>::traverses(std::function<void(T&)> func)
{
	auto p = begin();
	while(p!=trailer){
		func(p->data);
		p = p->succ;
	}
}


