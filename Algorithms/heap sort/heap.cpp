#include "heap.h"
#include <iostream>
using namespace std;

Heap::Heap(int size, int type){
    heap = new node[size];
    int heap_type = type;
    max_array_size = size;
    //for (int i=0;i<size;i++){
    //    heap[i] = node();
    //}
}
Heap::~Heap(){///minmap chunk error when deleting?
    //delete [] heap;
}

int Heap::get_array_size(){
    return array_size;
}

int Heap::get_id(int key){
    return heap[key].get_id();
}

int Heap::get_max_id(){
    return max_id;
}

void Heap::extract_max(){
    heap_size--;
    node temp = heap[0];
    heap[0] = heap[heap_size];
    heap[heap_size] = temp;
}

void Heap::extract_min(){
    heap_size--;
    node temp = heap[0];
    heap[0] = heap[heap_size];
    heap[heap_size] = temp;
}

void Heap::max_heapify( int item){
    int l = (2*item)+1;
    int r = (2*item)+2;
    int largest = item;
    if (l < heap_size && heap[l] > heap[item]){
        largest = l;
    }
    else {
        largest = item;
    }

    if(r < heap_size && heap[r] > heap[largest]){
        largest = r;
    }

    if(largest != item){
        node temp(0,0,0,0);
        temp = heap[item];
        heap[item] = heap[largest];
        heap[largest] = temp;
        max_heapify(largest);
    }
}

void Heap::min_heapify( int item){
    int l = (2*item)+1;
    int r = (2*item)+2;
    int small = item;
    if (l < heap_size && heap[l] < heap[item]){
        small = l;
    }
    else {
        small = item;
    }

    if(r < heap_size && heap[r] < heap[small]){
        small = r;
    }

    if(small != item){
        node temp(0,0,0,0);
        temp = heap[item];
        heap[item] = heap[small];
        heap[small] = temp;
        min_heapify(small);
    }
}

void Heap::build_max_heap(){
    for(int i = ((heap_size-1)/2); i>=0; i--){
        max_heapify(i);
    }
    heap_type = 1;
}

void Heap::build_min_heap(){
    for(int i = ((heap_size-1)/2); i>=0; i--){
        min_heapify(i);
    }
    heap_type = 0;
}

void Heap::heapsort( int amount_to_sort, int type){
    int end_key = 1;
    if (amount_to_sort <= array_size){
        end_key = heap_size-1 - amount_to_sort;
    }
    if (type == 0){
            build_min_heap();
        for(int i = heap_size-1; i>=end_key; i--){
            extract_min();
            min_heapify(0);
        }
    }
    else{
            build_max_heap();
        for(int i = heap_size-1; i>=end_key; i--){
            extract_max();
            max_heapify(0);
        }
    }
}

void Heap::insert(node item){

    //node new_node(item.get_id(), item.calls, item.positive_feedback, item.negative_feedback);
    if(array_size == max_array_size){
        cout << "array is full" << endl;
        //cout << "full " << item.get_id() << endl;
    }
    else{
        heap[array_size] = item;
        array_size++;
        heap_size = array_size; ///list loses heap property
        if (item.get_id() > max_id){
            max_id = item.get_id();
        }
    }
}

void Heap::increase_key(int key, node increase){
    node new_node = heap[key];
    new_node += increase;
    if(heap_type == 1){/// if max heap
        if(new_node < heap[key]){
            heap[key] += increase;
            max_heapify(key);
        }
        else{
            heap[key] += increase;
            node temp;
            while (false && key > 0 && (heap[(key-1)/2] < heap[key]) ){ /// (key-1)/2 is parent node
                heap[(key-1)/2] = temp;
                heap[(key-1)/2] = heap[key];
                heap[key] = temp;
                key = (key-1)/2;
            }
        }
    }

    else{/// if min heap
        if(new_node > heap[key]){
            heap[key] += increase;
            min_heapify(key);
        }
        else{
            heap[key] += increase;
            node temp;
            while (false && key > 0 && (heap[(key-1)/2] > heap[key]) ){ /// (key-1)/2 is parent node
                heap[(key-1)/2] = temp;
                heap[(key-1)/2] = heap[key];
                heap[key] = temp;
                key = (key-1)/2;
            }
        }
    }
}

int Heap::find_node(int node_id){ ///search for node id, return key of node if found, else reutrn -1
    for(int i=0; i<array_size; i++){
        if(heap[i].get_id() == node_id){
            return i;
        }
    }
    return -1;
}

void Heap::reset_heap(){
    heap_size = array_size;
}

void Heap::heapsort_calls( int amount_to_sort, int type){
    int end_key = 1;
    if (amount_to_sort <= array_size){
        end_key = heap_size-1 - amount_to_sort;
    }
    if (type == 0){
            build_min_heap_calls();
        for(int i = heap_size-1; i>=end_key; i--){
            extract_min();

            min_heapify_calls(0);
        }
    }
    else{
            build_max_heap_calls();
        for(int i = heap_size-1; i>=end_key; i--){
            extract_max();

            max_heapify_calls(0);
        }
    }
}

void Heap::build_max_heap_calls(){
    for(int i = ((heap_size-1)/2); i>=0; i--){
        max_heapify_calls(i);
    }
    heap_type = 1;
}

void Heap::build_min_heap_calls(){
    for(int i = ((heap_size-1)/2); i>=0; i--){
        min_heapify_calls(i);
    }
    heap_type = 0;
}

void Heap::max_heapify_calls( int item){
    int l = (2*item)+1;
    int r = (2*item)+2;
    int largest = item;
    if (l < heap_size && (heap[l].get_calls() > heap[item].get_calls()) ){
        largest = l;
    }
    else {
        largest = item;
    }

    if(r < heap_size && (heap[r].get_calls() > heap[largest].get_calls()) ){
        largest = r;
    }

    if(largest != item){
        node temp(0,0,0,0);
        temp = heap[item];
        heap[item] = heap[largest];
        heap[largest] = temp;
        max_heapify_calls(largest);
    }
}

void Heap::min_heapify_calls( int item){
    int l = (2*item)+1;
    int r = (2*item)+2;
    int small = item;
    if (l < heap_size && (heap[l].get_calls() < heap[item].get_calls()) ){
        small = l;
    }
    else {
        small = item;
    }

    if(r < heap_size && (heap[r].get_calls() < heap[small].get_calls()) ){
        small = r;
    }

    if(small != item){
        node temp(0,0,0,0);
        temp = heap[item];
        heap[item] = heap[small];
        heap[small] = temp;
        min_heapify_calls(small);
    }
}
void Heap::increase_key_calls(int key, node increase){
    node new_node = heap[key];
    new_node += increase;
    if(heap_type == 1){/// if max heap
        if(new_node < heap[key]){
            //cout <<  heap[key].get_id() << ": "<< heap[key].calls << " + "<< increase.calls << "-->";
            heap[key] += increase;
            //cout << heap[key].calls << endl;
            max_heapify(key);
        }
        else{
            //cout <<  heap[key].get_id() << ": "<< heap[key].calls << " + "<< increase.calls << "-->";
            heap[key] += increase;
            //cout << heap[key].calls << endl;
            node temp;
            while (false && key > 0 && (heap[(key-1)/2] < heap[key]) ){ /// (key-1)/2 is parent node
                heap[(key-1)/2] = temp;
                heap[(key-1)/2] = heap[key];
                heap[key] = temp;
                key = (key-1)/2;
            }
        }
    }

    else{/// if min heap
        if(new_node.get_calls() > heap[key].get_calls()){
            heap[key] += increase;
           // min_heapify(key);
        }
        else{
            heap[key] += increase;
            node temp;
            while (false && key > 0 && (heap[(key-1)/2].get_calls() > heap[key].get_calls()) ){ /// (key-1)/2 is parent node
                heap[(key-1)/2] = temp;
                heap[(key-1)/2] = heap[key];
                heap[key] = temp;
                key = (key-1)/2;
            }
        }
    }
}
