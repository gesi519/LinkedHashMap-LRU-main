#include "src.hpp"
#if defined (_UNORDERED_MAP_)  || (defined (_LIST_)) || (defined (_MAP_)) || (defined (_SET_)) || (defined (_UNORDERED_SET_))||(defined (_GLIBCXX_MAP)) || (defined (_GLIBCXX_UNORDERED_MAP))
BOOM :)
#endif
#include <iostream>
#include <cassert>
#include <string>
#include <unordered_map>
#include <list>

// if this is 1, output yes or no
//otherwise, output the exact num
#define STATUS 0

std::string c[]={
    "   pass!",
    "   error.",
    "test1: constructor",
    "test2: insert & expand",
    "test3: remove",
    "test4: find & correctness of insert and remove",
    "test5: clear",
    "Congratulations. Your submission has passed all correctness tests. Good job! :)",
    "test6: constructor(), =",
    "test const iterator",
};

bool exists(sjtu::hashmap<int,int> map,sjtu::hashmap<int,int>::iterator i){
    return i!=map.end();
}

bool equal(Integer a,Integer b){
    return a.val == b.val;
}

void Integer_linked_hashmap_tester(){
    using value_type = sjtu::pair<Integer,Integer>;
    using mp = sjtu::linked_hashmap<Integer,Integer,Hash,Equal>;
    using test_type = std::unordered_map<Integer,Integer,Hash, Equal >;
    const int n = 4000;
    // test: constructor
    if(STATUS)std::cout<<c[2];
    mp map;
    test_type ref;
    std::list<Integer> order;
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: insert,remove and expand
    if(STATUS)std::cout<<c[3];
    for(int i=0;i<n;i++){
        map.insert(value_type(Integer(i),Integer(i)));
        ref.insert(std::pair<Integer,Integer>(Integer(i),Integer(i)));
        order.push_back(Integer(i));
    }

    if(STATUS)std::cout<<std::endl<<c[4];//test remove
    for(mp::iterator it = map.begin();it!=map.end();it++){
        order.remove((*it).first);
        ref.erase((*it).first);
	    mp::iterator tmpit = it;
        it++;
        map.remove(tmpit);
        if(it == map.end()){
            break;
        }
        it++;
        if(it == map.end()){
            break;
        }
    }
    if(STATUS)std::cout<<c[0]<<std::endl;
    for(int i=0;i<n;i+=4){
        map.insert(value_type(Integer(i),Integer(4 * i)));
        ref.insert(std::pair<Integer,Integer>(Integer(i),Integer(4*i)));
        order.remove(Integer(i));
        order.push_back(Integer(i));
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: counter

    int ct = 0;
    for(int i=0;i<n;i++){
        ct += map.count(Integer(i));
    }
    std::cout<<ct<<std::endl;

    //test: iterator
    mp::iterator it = map.begin();
    std::list<Integer>::iterator lit = order.begin();
    while(it != map.end()){
        std::cout<<(*it).first.val<<" "<<(*it).second.val<<" "<<(*lit).val<<" "<<(*(ref.find(*lit))).second.val <<std::endl;
        it++;
        lit++;
    }

    //test: const iterator

    if(STATUS)std::cout<<c[9];
    mp::iterator iter;
    iter = map.begin();
    iter = map.end();
    mp::const_iterator const_iter;
    const_iter = map.cend();
    const_iter = map.cbegin();
    if(STATUS)std::cout<<c[0]<<std::endl;
    //test: find
    if(STATUS)std::cout<<c[5];
    for(int i=0;i<n;i++){
        mp::iterator it = map.find(Integer(i));
        if(STATUS == 0){
            if(it != map.end())
            std::cout<<(*it).second.val<<std::endl;
        }
        if(i%3==0 && i%4 != 0){
            if(it != map.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!equal(Integer(4 * i),(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!equal(Integer(i),(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: constructor(), =
    if(STATUS)std::cout<<c[8];
    mp map2(map);
    map2.clear();
    map2 = map;
    for(int i=0;i<n;i++){
        mp::iterator it = map2.find(Integer(i));
        if(i%3==0 && i%4 != 0){
            if(it != map2.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!equal(Integer(4 * i),(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!equal(Integer(i),(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: clear
    if(STATUS)std::cout<<c[6];
    map.clear();
    map.clear();
    if(STATUS)std::cout<<c[0]<<std::endl;
}

void Matrix_linked_hashmap_tester(){
    using mType = Matrix<int>;
    using value_type = sjtu::pair<Integer,mType >;
    using mp = sjtu::linked_hashmap<Integer,mType, Hash, Equal>;
    const int n = 100;
    // test: constructor
    if(STATUS)std::cout<<c[2];
    mp map;
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: insert,remove and expand
    if(STATUS)std::cout<<c[3];
    for(int i=0;i<n;i++){
        map.insert(value_type(Integer(i),mType(2,2,i)));
    }
    if(STATUS)std::cout<<std::endl<<c[4];//test remove

    for(mp::iterator it = map.begin();it!=map.end();it++){
	    mp::iterator tmpit = it;
        it++;
        map.remove(tmpit);
        if(it == map.end()){
            break;
        }
        it++;
        if(it == map.end()){
            break;
        }
    }

    for(int i=0;i<n;i+=4){
        map.insert(value_type(Integer(i),mType(2,2,4 * i)));
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: counter

    int ct = 0;
    for(int i=0;i<n;i++){
        ct += map.count(Integer(i));
    }
    std::cout<<ct<<std::endl;

    //test: iterator
    mp::iterator it = map.begin();
    while(it != map.end()){
        std::cout<<(*it).first.val<<" "<<(*it).second<<std::endl;
        it++;
    }

    //test: const iterator

    if(STATUS)std::cout<<c[9];
    mp::iterator iter;
    iter = map.begin();
    iter = map.end();
    mp::const_iterator const_iter;
    const_iter = map.cend();
    const_iter = map.cbegin();
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: find
    if(STATUS)std::cout<<c[5];
    for(int i=0;i<n;i++){
        mp::iterator it = map.find(Integer(i));
        if(STATUS == 0){
            if(it != map.end())
            std::cout<<(*it).second<<std::endl;
        }
        if(i%3==0 && i%4 != 0){
            if(it != map.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!(mType(2,2,4 * i)==(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!(mType(2,2,i)==(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: constructor(), =
    if(STATUS)std::cout<<c[8];
    mp map2(map);
    map2.clear();
    map2 = map;
    for(int i=0;i<n;i++){
        mp::iterator it = map2.find(Integer(i));
        if(i%3==0 && i%4 != 0){
            if(it != map2.end()){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else if (i % 4 == 0){
            if(!(mType(2,2,4 * i)==(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
        else{
            if(!(mType(2,2,i)==(*it).second)){
                std::cout<<c[1]<<std::endl;
                exit(0);
            }
        }
    }
    if(STATUS)std::cout<<c[0]<<std::endl;

    //test: clear
    if(STATUS)std::cout<<c[6];
    map.clear();
    map.clear();
    if(STATUS)std::cout<<c[0]<<std::endl;
}

int main(){
#ifdef _OUTPUT_
    freopen("5.out","w",stdout);
#endif
    Integer_linked_hashmap_tester();
   // Matrix_linked_hashmap_tester();
    std::cout << c[7] << std::endl;
}
