#include<bits/stdc++.h>

using namespace std;

class Data{
public:
	int count;
	char c;
};

class Compare{
public:
	bool operator() (Data const& a, Data const& b){
		return a.count < b.count;
	}
};

// hence the Data object with max. count value
// will be placed at the top of the heap

int main(){
	priority_queue<Data, vector<Data>, Compare> max_heap;
}

// priority queue by default is a max heap
/*
priority_queue::emplace() in C++ STL – This 
function is used to insert a new element into 
the priority queue container, the new element 
is added to the top of the priority queue.

priority_queue value_type in C++ STL– Represents 
the type of object stored as an element in a 
priority_queue. It acts as a synonym for 
the template parameter.*/