#ifndef SJTU_LRU_HPP
#define SJTU_LRU_HPP

#include "utility.hpp"
#include "exceptions.hpp"
#include "class-integer.hpp"
#include "class-matrix.hpp"
#include <vector>
#include <iostream>
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
public:
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
	void initialize() {
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
		initialize();
	}
	double_list(const double_list<T> &other) {
		initialize();
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

    class const_iterator;
	class iterator{
	public:
    	Node<T>* node = nullptr;
        const double_list* dou_lis = nullptr;
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
            return it; 
		}
        /**
		 * ++iter
		 */
		iterator &operator++() {
            if(node == dou_lis->tail) {
                throw("segmentation fault");
            }
            node = node->behind;
            return *this; 
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
            return it; 
		}
        /**
		 * --iter
		 */
		iterator &operator--() {
            if(node == dou_lis->head->behind) {
                throw("segmentation fault");
            }
            node = node->front;
            return *this; 
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
            return (dou_lis!=rhs.dou_lis||node!=rhs.node);
		}
        bool operator==(const const_iterator &rhs) const {
            return (dou_lis==rhs.dou_lis&&node==rhs.node);
        }
		bool operator!=(const const_iterator &rhs) const {
            return (dou_lis!=rhs.dou_lis||node!=rhs.node);
        }
	};
    class const_iterator {
	public:
        Node<T>* node = nullptr;
        const double_list* dou_lis = nullptr;
    // --------------------------   
		const_iterator() {
		}
		const_iterator(const iterator &t) : node(t.node),dou_lis(t.dou_lis) {
		}
        ~const_iterator() {
            node = nullptr;
            dou_lis = nullptr;
        }
		/**
		 * iter++
		 */
		const_iterator operator++(int) {
            if(node == dou_lis->tail) {
                throw("segmentation fault");
            }
            const_iterator it = *this;
            node = node->behind;
            return it; 
        }
		/**
		 * ++iter
		 */
		const_iterator &operator++() {
            if(node == dou_lis->tail) {
                throw("segmentation fault");
            }
            node = node->behind;
            return *this; 
        }
		/**
		 * iter--
		 */
		const_iterator operator--(int) {
            if(node == dou_lis->head->behind) {
                throw("segmentation fault");
            }
            const_iterator it = *this;
            node = node->front;
            return it; 
        }
		/**
		 * --iter
		 */
		const_iterator &operator--() {
            if(node == dou_lis->head->behind) {
                throw("segmentation fault");
            }
            node = node->front;
            return *this; 
        }

		/**
		 * if the iter didn't point to a value
		 * throw 
		*/
		const T &operator*() const {
            if(node == nullptr||node == dou_lis->head||node == dou_lis->tail) {
                throw("segmentation fault");
            }
            return *(node->val);
		}
		const T *operator->() const noexcept {
            return node->val;
		}

		/**
		 * operator to check whether two iterators are same (pointing to the same memory).
		 */
		bool operator==(const iterator &rhs) const {
            return (dou_lis==rhs.dou_lis&&node==rhs.node);
        }
		bool operator!=(const iterator &rhs) const {
            return (dou_lis!=rhs.dou_lis||node!=rhs.node);
        }
		bool operator==(const const_iterator &rhs) const {
            return (dou_lis==rhs.dou_lis&&node==rhs.node);
        }
		bool operator!=(const const_iterator &rhs) const {
            return (dou_lis!=rhs.dou_lis||node!=rhs.node);
        }
	};
	/**
	 * return an iterator to the beginning
	 */
	iterator begin() const{
        iterator it;
        it.dou_lis = this;
        it.node = head->behind;
        return it;
	}
    const_iterator cbegin() const{
        const_iterator it;
		it.dou_lis = this;
		it.node = head->behind;
        return it;
	}
	/**
	 * return an iterator to the ending
	 * in fact, it returns the iterator point to nothing,
	 * just after the last element.
	 */
	iterator end() const{
        iterator it;
        it.dou_lis = this;
        it.node = tail;
        return it;
	}
    const_iterator cend() const{
        const_iterator it;
		it.dou_lis = this;
		it.node = tail;
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
        if(pos.dou_lis != this||pos.node == nullptr || pos.node == head || pos.node == tail) return end();
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
        ++count;
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
    double load_factor = 0.75;
    std::vector<double_list<value_type>> hash_map;
	// Hash function
    Hash hash_fn;
	Equal eq_fn;

// --------------------------

	/**
	 * the follows are constructors and destructors
	 * you can also add some if needed.
	*/
	hashmap() : hash_map(capacity) {
	}
	hashmap(const hashmap &other) : capacity(other.capacity),current_Size(other.current_Size),
							load_factor(other.load_factor),hash_map(other.hash_map),hash_fn(other.hash_fn),eq_fn(other.eq_fn) {
	}
    
	~hashmap() {}
	hashmap & operator=(const hashmap &other) {
        if(this != &other) {
            clear();
			capacity = other.capacity;
			current_Size = other.current_Size;
			load_factor = other.load_factor;
			hash_map = other.hash_map;
			hash_fn = other.hash_fn;
			eq_fn = other.eq_fn;
		}
		return *this;
	}

	class iterator{
	public:
        value_type* ptr = nullptr;
// --------------------------
        /**
         * the follows are constructors and destructors
         * you can also add some if needed.
        */
		iterator() {
		}
		iterator(const iterator &t) : ptr(t.ptr) {
		}
		~iterator() {
            ptr = nullptr;
        }

        /**
		 * if point to nothing
		 * throw 
		*/
		value_type &operator*() const {
            if(ptr == nullptr) throw("point to nothing");
            return *ptr;
		}

        /**
		 * other operation
		*/
		value_type *operator->() const noexcept {
            return ptr;
		}
		bool operator==(const iterator &rhs) const {
            return ptr == rhs.ptr;
    	}
		bool operator!=(const iterator &rhs) const {
            return ptr != rhs.ptr;
		}
	};

	void clear() {
        capacity = 16;
        current_Size = 0;
        for(int i=0;i<hash_map.size();++i) {
            hash_map[i].clear();
        }
        hash_map.resize(capacity);
	}
	/**
	 * you need to expand the hashmap dynamically
	*/
	void expand() {
        int new_capcity = capacity*2;
        std::vector<double_list<value_type>> new_hash_map(new_capcity);
        for(int i=0;i<capacity;++i) {
            for(auto it = hash_map[i].begin();it!=hash_map[i].end();++it) {
                size_t pos = hash_fn((*it).first) % new_capcity;
				new_hash_map[pos].insert_tail(*it);
            }
        }
		new_hash_map.swap(hash_map);
		capacity = new_capcity;
	}

    /**
     * the iterator point at nothing
    */
	iterator end() const {
        iterator it;
        return it;
	}
	/**
	 * find, return a pointer point to the value
	 * not find, return the end (point to nothing)
	*/
	iterator find(const Key &key)const {
        size_t pos = hash_fn(key)%capacity;
        for(auto it = hash_map[pos].begin();it!=hash_map[pos].end();++it) {
            if(eq_fn((*it).first,key)) {
                iterator it_;
                it_.ptr = &(*it);
                return it_;
            }
        }
        return end();
	}
	/**
	 * already have a value_pair with the same key
	 * -> just update the value, return false
	 * not find a value_pair with the same key
	 * -> insert the value_pair, return true
	*/
	sjtu::pair<iterator,bool> insert(const value_type &value_pair) {
        if(current_Size>=capacity*load_factor) {
            expand();
        }
        auto it = find(value_pair.first);
        if(it == end()) {
			size_t pos = hash_fn(value_pair.first)%capacity;
            hash_map[pos].insert_head(value_pair);
            it.ptr = (&(*(hash_map[pos].begin())));
            ++current_Size;
            return sjtu::pair<iterator,bool>{it,true};
        }
        (*it).second = value_pair.second;
        return sjtu::pair<iterator,bool>{it,false};
	}
	/**
	 * the value_pair exists, remove and return true
	 * otherwise, return false
	*/
	bool remove(const Key &key) {
        size_t pos = hash_fn(key)%capacity;
        for(auto it_ = hash_map[pos].begin();it_!=hash_map[pos].end();++it_) {
            if(eq_fn((*it_).first,key)) {
                hash_map[pos].erase(it_);
                --current_Size;
                return true;
            }
        }
        return false;
	}
};

template<
	class Key,
	class T,
	class Hash = std::hash<Key>, 
	class Equal = std::equal_to<Key>
> class linked_hashmap {
public:
    // 为什么我感觉这个继承没有什么用呢
	typedef pair<const Key, T> value_type;
    //using value_type = pair<const Key, T>;
	/*
	as contrary
	using is more morden
	and using can use for template
	The syntax structure of using can be simpler
	*/
    using iterator = typename double_list<value_type>::iterator;
    using const_iterator = typename double_list<value_type>::const_iterator;
    double_list<value_type> list;
    hashmap<Key,iterator,Hash,Equal> hash_map_iterator;

// --------------------------
	
 
	linked_hashmap() {
	}
	linked_hashmap(const linked_hashmap &other) : list(other.list),hash_map_iterator(other.hash_map_iterator) {
	}
	~linked_hashmap() {
	}
	linked_hashmap & operator=(const linked_hashmap &other) {
        if(this != &other) {
			list.clear();
			list = other.list;
			hash_map_iterator.operator=(other.hash_map_iterator);
		}
		return *this;
	}

 	/**
	 * return the value connected with the Key(O(1))
	 * if the key not found, throw 
	*/
	T & at(const Key &key) {
        auto it = hash_map_iterator.find(key);
        if(it == hash_map_iterator.end()) {
            throw("not found");
        }
        return  (it->second)->second;
	}
	const T & at(const Key &key) const {
        auto it = hash_map_iterator.find(key);
        if(it == hash_map_iterator.end()) {
            throw("not found");
        }
        return  (it->second)->second;
	}
	T & operator[](const Key &key) {
        auto it = hash_map_iterator.find(key);
        if(it == hash_map_iterator.end()) {
            throw("not found");
        }
        return  (it->second)->second;
	}
	const T & operator[](const Key &key) const {
        auto it = hash_map_iterator.find(key);
        if(it == hash_map_iterator.end()) {
            throw("not found");
        }
        return  (it->second)->second;
	}

	/**
	 * return an iterator point to the first 
	 * inserted and existed element
	 */
	iterator begin() const{
        return list.begin();
	}
	const_iterator cbegin() const {
        return list.cbegin();
	}
    /**
	 * return an iterator after the last inserted element
	 */
	iterator end() const{
        return list.end();
	}
	const_iterator cend() const {
        return list.cend();
	}
  	/**
	 * if didn't contain anything, return true, 
	 * otherwise false.
	 */
	bool empty() const {
        return hash_map_iterator.current_Size == 0;
	}

    void clear() {
        hash_map_iterator.clear();
        list.clear();
	}

	size_t size() const {
        return hash_map_iterator.current_Size;
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
        if(hash_map_iterator.current_Size>=hash_map_iterator.capacity*hash_map_iterator.load_factor) {
            hash_map_iterator.expand();
        }
        size_t pos = hash_map_iterator.hash_fn(value.first)%(hash_map_iterator.capacity);
        for(auto it = hash_map_iterator.hash_map[pos].begin();it!=hash_map_iterator.hash_map[pos].end();++it) {
            if(hash_map_iterator.eq_fn((*it).first,value.first)) {
                list.erase((*it).second);
                list.insert_tail(value);
				auto it_ = list.end();
				--it_;
                (*it).second = it_;
                return pair<iterator, bool>{(*it).second,false};
            }
        }
        list.insert_tail(value);
		auto it_ = list.end();
		--it_;
        hash_map_iterator.hash_map[pos].insert_head({value.first,it_});
		hash_map_iterator.current_Size++;
        return pair<iterator, bool>{it_,true};
	}
 	/**
	 * erase the value_pair pointed by the iterator
	 * if the iterator points to nothing
	 * throw 
	*/
	void remove(iterator pos) {
        value_type va_ty = *pos;
        list.erase(pos);
        hash_map_iterator.remove(va_ty.first);
	}
	/**
	 * return how many value_pairs consist of key
	 * this should only return 0 or 1
	*/
	size_t count(const Key &key) const {
        return (hash_map_iterator.find(key) == hash_map_iterator.end()?0:1);
	}
	/**
	 * find the iterator points at the value_pair
	 * which consist of key
	 * if not find, return the iterator 
	 * point at nothing
	*/
	iterator find(const Key &key) const {
        auto it = hash_map_iterator.find(key);
        if(it == hash_map_iterator.end()) {
            return end();
        }
        return (*it).second;
	}

};

class lru{
    using lmap = sjtu::linked_hashmap<Integer,Matrix<int>,Hash,Equal>;
    using value_type = sjtu::pair<const Integer, Matrix<int> >;
public:
    lmap* mem;
    size_t capacity = 0;
    lru(int size) : capacity(size){
        mem = new lmap();
    }
    ~lru() {
        delete mem;
        mem = nullptr;
    }
    /**
     * save the value_pair in the memory
     * delete something in the memory if necessary
    */
    void save(const value_type &v) const{
        if(mem->find(v.first)!=mem->end()) {
            mem->insert(v);
            return ;
        }
        if(mem->size() == capacity) {
            auto it = mem->begin();
            mem->remove(it);
            mem->insert(v);
            return ;
        }
        mem->insert(v);
    }
    /**
     * return a pointer contain the value
    */
    Matrix<int>* get(const Integer &v) /*const*/{
        typename sjtu::linked_hashmap<Integer,Matrix<int>,Hash,Equal>::iterator it = mem->find(v);
        if(it!=mem->end()) {
            Matrix<int> matrix = it.node->val->second;
            mem->remove(it);
            mem->insert(value_type(v,matrix));
            return &(mem->find(v).node->val->second);
        }
        return nullptr;
    }
    /**
     * just print everything in the memory
     * to debug or test.
     * this operation follows the order, but don't
     * change the order.
    */
    void print() {
        typename sjtu::linked_hashmap<Integer,Matrix<int>,Hash,Equal>::iterator it ;
        for (it=mem->begin();it!=mem->end();it++) {
            std::cout<<(*it).first.val<<" "<<(*it).second<<std::endl;
        }
    }
};
}

#endif
