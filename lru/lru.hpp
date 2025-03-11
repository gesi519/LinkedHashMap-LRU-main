#ifndef SJTU_LRU_HPP
#define SJTU_LRU_HPP

#include "utility.hpp"
#include "exceptions.hpp"
#include "class-integer.hpp"
#include "class-matrix.hpp"
class Hash {
public:
	unsigned int operator () (Integer lhs) const {
		int val = lhs.val;
		return std::hash<int>()(val);
	}
};
class Equal {
public:
	bool operator () (const Integer &lhs, const Integer &rhs) const {
		return lhs.val == rhs.val;
	}
};

namespace sjtu {

/*
这是double_list中每一个节点的定义，包括需要的构造函数
*/
template<class T> class Node {
	T* val = nullptr;/* 无法确定T类型是否有默认构造函数 */
	Node* front = nullptr;
	Node* behind = nullptr;
	Node() {}
	Node(Node* _front,Node* _behind) : front(_front),behind(_behind) {}
	Node(T* _val,Node* _front,Node* _behind) : val(_val),front(_front),behind(_behind) {}
};

template<class T> class double_list{
public:
	class iterator;

	Node<T>* head;
	Node<T>* tail;
	size_t count = 0;

// --------------------------
	//初始化的默认构造
	void Default_Construction() {
		head = new Node<T>();
		tail = new Node<T>();
		head->behind = tail;
		tail->front = head; 
	}
	//析构的基本步骤和=重载的基本前提清理
	void clear() {
		while(!empty()) {
			delete_head();
		}
	}

	double_list() {
		Default_Construction();
	}
	double_list(const double_list<T> &other) {
		Default_Construction()
		for(auto it = other.begin();it != other.end();++it) {
            insert_tail(*it);
        }
	}
    // = 重载 为了之后linked_hashmap的=重载和拷贝构造
    double_list& operator=(const double_list<T> &other) {
		if(this != &other) {
			clear();
			for(auto it = other.begin();it != other.end();++it) {
                insert_tail(*it);
            }
		}
		return *this;
	}
	~double_list() {
		clear();
		tail->front = nullptr;
		head->behind = nullptr;
		delete head;
		delete tail;
	}

	class iterator{
	public:
    	Node<T>* node = nullptr;
        double_list* dou_lis = nullptr;
	    // --------------------------
        /**
		 * the follows are constructors and destructors
		 * you can also add some if needed.
		*/
		iterator(){}
		iterator(const iterator &t) : node(t.node),dou_lis(t.dou_lis){
		}
        iterator(Node<T>* t,double_list* d) : node(t),dou_lis(d) {
        }
		~iterator() {
            node = nullptr;
            dou_lis = nullptr;
        }
        /**
		 * iter++
		 */
		iterator operator++(int) {
            if(node == dou_lis->tail) {
                throw("segmentation fault");
            }
            iterator it = *this;
            node = node->behind;
            retrun it; 
		}
        /**
		 * ++iter
		 */
		iterator &operator++() {
            if(node == dou_lis->tail) {
                throw("segmentation fault");
            }
            node = node->behind;
            retrun *this; 
		}
        /**
		 * iter--
		 */
		iterator operator--(int) {
            if(node == dou_lis->head->behind) {
                throw("segmentation fault");
            }
            iterator it = *this;
            node = node->front;
            retrun it; 
		}
        /**
		 * --iter
		 */
		iterator &operator--() {
            if(node == dou_lis->head->behind) {
                throw("segmentation fault");
            }
            node = node->front;
            retrun *this; 
		}
		/**
		 * if the iter didn't point to a value
		 * throw " invalid"
		*/
		T &operator*() const {
            if(node == nullptr||node == dou_lis->head||node == dou_lis->tail) {
                throw("segmentation fault");
            }
            return *(node->val);
		}
        /**
         * other operation
        */
		T *operator->() const noexcept {
            return node->val;
		}
		bool operator==(const iterator &rhs) const {
            return (dou_lis==rhs.dou_lis&&node==rhs.node);
    	}
		bool operator!=(const iterator &rhs) const {
            return (dou_lis!=rhs.dou_lis&&node!=rhs.node);
		}
	};
	/**
	 * return an iterator to the beginning
	 */
	iterator begin() const{
        iterator it(head,this);
        ++it;
        return it;
	}
	/**
	 * return an iterator to the ending
	 * in fact, it returns the iterator point to nothing,
	 * just after the last element.
	 */
	iterator end() const{
        iterator it(tail,this);
        return it;
	}
	/**
	 * if the iter didn't point to anything, do nothing,
	 * otherwise, delete the element pointed by the iter
	 * and return the iterator point at the same "index"
	 * e.g.
	 * 	if the origin iterator point at the 2nd element
	 * 	the returned iterator also point at the
	 *  2nd element of the list after the operation
	 *  or nothing if the list after the operation
	 *  don't contain 2nd elememt.
	*/
	iterator erase(iterator pos) {
        if(pos.dou_lis != this||pos.node == nullptr || pos.node == head || pos.node == tail) return pos;
        Node<T>* now = pos.node;
        Node<T>* now_front = now->front;
        Node<T>* now_behind = now->behind;
        now_front->behind = now_behind;
        now_behind->front = now_front;
        delete now->val;
        delete now;
        --count;
        pos.node = now_behind;
        return pos;
	}

	/**
	 * the following are operations of double list
	*/
	void insert_head(const T &val) {
        Node<T>* tmp_node = new Node<T>(new T(val),head,head->behind);
        head->behind = tmp_node;
        tmp_node->behind->front = tmp_node;
        ++count;
	}
	void insert_tail(const T &val) {
        Node<T>* tmp_node = new Node<T>(new T(val),tail->front,tail);
        tail->front = tmp_node;
        tmp_node->front->behind = tmp_node;
        ++count
	}
	void delete_head() {
        erase(begin());
	}
	void delete_tail() {
        iterator it = end();
        --it;
        erase(it);
	}
	/**
	 * if didn't contain anything, return true, 
	 * otherwise false.
	 */
	bool empty() {
        return count == 0;
	}
};

template<
	class Key,
	class T,
	class Hash = std::hash<Key>, 
	class Equal = std::equal_to<Key>
> class hashmap{
public:
	using value_type = pair<const Key, T>;
	
    size_t capacity = 16;
	size_t current_Size = 0; 
    double load_factor = 1.1;
	// Hash function
    Hash hash_fn;
	Equal eq_fn;

// --------------------------

	/**
	 * the follows are constructors and destructors
	 * you can also add some if needed.
	*/
	hashmap() {
	}
	hashmap(const hashmap &other){
	}
	~hashmap(){
	}
	hashmap & operator=(const hashmap &other){
	}

	class iterator{
	public:
    	/**
         * elements
         * add whatever you want
        */
// --------------------------
        /**
         * the follows are constructors and destructors
         * you can also add some if needed.
        */
		iterator(){
		}
		iterator(const iterator &t){
		}
		~iterator(){}

        /**
		 * if point to nothing
		 * throw 
		*/
		value_type &operator*() const {
		}

        /**
		 * other operation
		*/
		value_type *operator->() const noexcept {
		}
		bool operator==(const iterator &rhs) const {
    	}
		bool operator!=(const iterator &rhs) const {
		}
	};

	void clear(){
	}
	/**
	 * you need to expand the hashmap dynamically
	*/
	void expand(){
	}

    /**
     * the iterator point at nothing
    */
	iterator end() const{
	}
	/**
	 * find, return a pointer point to the value
	 * not find, return the end (point to nothing)
	*/
	iterator find(const Key &key)const{
	}
	/**
	 * already have a value_pair with the same key
	 * -> just update the value, return false
	 * not find a value_pair with the same key
	 * -> insert the value_pair, return true
	*/
	sjtu::pair<iterator,bool> insert(const value_type &value_pair){
	}
	/**
	 * the value_pair exists, remove and return true
	 * otherwise, return false
	*/
	bool remove(const Key &key){
	}
};

template<
	class Key,
	class T,
	class Hash = std::hash<Key>, 
	class Equal = std::equal_to<Key>
> class linked_hashmap :public hashmap<Key,T,Hash,Equal>{
public:
	typedef pair<const Key, T> value_type;
	/**
	 * elements
	 * add whatever you want
	*/
// --------------------------
	class const_iterator;
	class iterator{
	public:
    	/**
         * elements
         * add whatever you want
        */
    // --------------------------
		iterator(){
		}
		iterator(const iterator &other){
		}
		~iterator(){
		}

		/**
		 * iter++
		 */
		iterator operator++(int) {}
		/**
		 * ++iter
		 */
		iterator &operator++() {}
		/**
		 * iter--
		 */
		iterator operator--(int) {}
		/**
		 * --iter
		 */
		iterator &operator--() {}

		/**
		 * if the iter didn't point to a value
		 * throw "star invalid"
		*/
		value_type &operator*() const {
		}
		value_type *operator->() const noexcept {
		}

		/**
		 * operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const {}
		bool operator!=(const iterator &rhs) const {}
		bool operator==(const const_iterator &rhs) const {}
		bool operator!=(const const_iterator &rhs) const {}
	};
 
	class const_iterator {
		public:
        	/**
             * elements
             * add whatever you want
            */
    // --------------------------   
		const_iterator() {
		}
		const_iterator(const iterator &other) {
		}

		/**
		 * iter++
		 */
		const_iterator operator++(int) {}
		/**
		 * ++iter
		 */
		const_iterator &operator++() {}
		/**
		 * iter--
		 */
		const_iterator operator--(int) {}
		/**
		 * --iter
		 */
		const_iterator &operator--() {}

		/**
		 * if the iter didn't point to a value
		 * throw 
		*/
		const value_type &operator*() const {
		}
		const value_type *operator->() const noexcept {
		}

		/**
		 * operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const {}
		bool operator!=(const iterator &rhs) const {}
		bool operator==(const const_iterator &rhs) const {}
		bool operator!=(const const_iterator &rhs) const {}
	};
 
	linked_hashmap() {
	}
	linked_hashmap(const linked_hashmap &other){
	}
	~linked_hashmap() {
	}
	linked_hashmap & operator=(const linked_hashmap &other) {
	}

 	/**
	 * return the value connected with the Key(O(1))
	 * if the key not found, throw 
	*/
	T & at(const Key &key) {
	}
	const T & at(const Key &key) const {
	}
	T & operator[](const Key &key) {
	}
	const T & operator[](const Key &key) const {
	}

	/**
	 * return an iterator point to the first 
	 * inserted and existed element
	 */
	iterator begin() {
	}
	const_iterator cbegin() const {
	}
    /**
	 * return an iterator after the last inserted element
	 */
	iterator end() {
	}
	const_iterator cend() const {
	}
  	/**
	 * if didn't contain anything, return true, 
	 * otherwise false.
	 */
	bool empty() const {
	}

    void clear(){
	}

	size_t size() const {
	}
 	/**
	 * insert the value_piar
	 * if the key of the value_pair exists in the map
	 * update the value instead of adding a new element，
     * then the order of the element moved from inner of the 
     * list to the head of the list
	 * and return false
	 * if the key of the value_pair doesn't exist in the map
	 * add a new element and return true
	*/
	pair<iterator, bool> insert(const value_type &value) {
	}
 	/**
	 * erase the value_pair pointed by the iterator
	 * if the iterator points to nothing
	 * throw 
	*/
	void remove(iterator pos) {
	}
	/**
	 * return how many value_pairs consist of key
	 * this should only return 0 or 1
	*/
	size_t count(const Key &key) const {
	}
	/**
	 * find the iterator points at the value_pair
	 * which consist of key
	 * if not find, return the iterator 
	 * point at nothing
	*/
	iterator find(const Key &key) {
	}

};

class lru{
    using lmap = sjtu::linked_hashmap<Integer,Matrix<int>,Hash,Equal>;
    using value_type = sjtu::pair<const Integer, Matrix<int> >;
public:
    lru(int size){
    }
    ~lru(){
    }
    /**
     * save the value_pair in the memory
     * delete something in the memory if necessary
    */
    void save(const value_type &v) const{
    }
    /**
     * return a pointer contain the value
    */
    Matrix<int>* get(const Integer &v) const{
    }
    /**
     * just print everything in the memory
     * to debug or test.
     * this operation follows the order, but don't
     * change the order.
    */
    void print(){
    }
};
}

#endif