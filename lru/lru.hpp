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
template<class T> class double_list{
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
	double_list(){
	}
	double_list(const double_list<T> &other){
	}
	~double_list(){
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
		iterator(){}
		iterator(const iterator &t){
		}
		~iterator(){}
        /**
		 * iter++
		 */
		iterator operator++(int) {
		}
        /**
		 * ++iter
		 */
		iterator &operator++() {
		}
        /**
		 * iter--
		 */
		iterator operator--(int) {
		}
        /**
		 * --iter
		 */
		iterator &operator--() {
		}
		/**
		 * if the iter didn't point to a value
		 * throw " invalid"
		*/
		T &operator*() const {
		}
        /**
         * other operation
        */
		T *operator->() const noexcept {
		}
		bool operator==(const iterator &rhs) const {
    	}
		bool operator!=(const iterator &rhs) const {
		}
	};
	/**
	 * return an iterator to the beginning
	 */
	iterator begin(){
	}
	/**
	 * return an iterator to the ending
	 * in fact, it returns the iterator point to nothing,
	 * just after the last element.
	 */
	iterator end(){
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
	iterator erase(iterator pos){
	}

	/**
	 * the following are operations of double list
	*/
	void insert_head(const T &val){
	}
	void insert_tail(const T &val){
	}
	void delete_head(){
	}
	void delete_tail(){
	}
	/**
	 * if didn't contain anything, return true, 
	 * otherwise false.
	 */
	bool empty(){
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
	/**
	 * elements
	 * add whatever you want
	*/

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