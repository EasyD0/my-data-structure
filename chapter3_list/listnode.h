template<typename T>
struct ListNode{
	T data;
	ListNode<T> *pred = nullptr;
	ListNode<T> *succ = nullptr;


	//构造函数
	ListNode() = default;
	ListNode(const T &e, ListNode<T> *p = nullptr, ListNode<T> *s = nullptr)  //转换构造
	:data(e), pred(p), succ(s) {};

	//操作接口
	ListNode<T>* insertAsPred(const T &e);
	ListNode<T>* insertAsSucc(const T &e);
};
template<typename T>
ListNode<T>* ListNode<T>::insertAsPred(const T &e){
	auto the_insert=new ListNode(e, pred, this);
	auto oldpred = pred;
	
	pred = the_insert;
	oldpred->succ = the_insert;

	return the_insert;
}

template<typename T>
ListNode<T>* ListNode<T>::insertAsSucc(const T &e){
	auto the_insert = new ListNode<T>(e,this, succ);
	auto old_succ = succ;

	succ = the_insert;
	old_succ->pred = the_insert;
	
	return the_insert;
}

