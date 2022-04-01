
#include "heap_numbers.h"
#include <iostream>
#include <fstream>
using namespace std;

Heap_numbers::Heap_numbers(int size){
    heap = new int[size];
    max_array_size = size;
}
Heap_numbers::~Heap_numbers(){
    delete [] heap;
}

int Heap_numbers::get_array_size(){
    return array_size;
}

int Heap_numbers::get_heap_size(){
    return heap_size;
}

void Heap_numbers::extract_max(){
    heap_size--;
    int temp = heap[0];
    heap[0] = heap[heap_size];
    heap[heap_size] = temp;
}


void Heap_numbers::max_heapify( int item){
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
        int temp;
        temp = heap[item];
        heap[item] = heap[largest];
        heap[largest] = temp;
        max_heapify(largest);
    }
}


void Heap_numbers::build_max_heap(){
    for(int i = ((heap_size-1)/2); i>=0; i--){
        max_heapify(i);
    }
}

void Heap_numbers::heapsort( int amount_to_sort){
    int end_key = 1;
    if (amount_to_sort <= array_size){
        end_key = heap_size - amount_to_sort;
    }

    build_max_heap();
    for(int i = heap_size-1; i>=end_key; i--){
        extract_max();
        max_heapify(0);
    }
}

void Heap_numbers::insert(int item){
    if(array_size == max_array_size){
        cout << "array is full" << endl;
    }
    else{
        heap[array_size] = item;
        array_size++;
        heap_size = array_size; ///list loses heap property
    }
}

void Heap_numbers::reset_heap(){
    heap_size = array_size;
}

int Heap_numbers::get_number(int key){
    return heap[key];
}

void Heap_numbers::write_to_file(){
      ofstream myfile;
      myfile.open ("numbers_sorted.csv");
      for(int i=0; i<array_size ; i++){
        myfile << heap[i] <<"\n";
      }
      myfile.close();
}

