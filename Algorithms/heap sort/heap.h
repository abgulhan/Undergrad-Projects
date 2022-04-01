#include "node.h"
using namespace std;
class Heap{
//public:
    node *heap;
    int heap_size = 0;
    int array_size = 0;
    int max_array_size;
    int heap_type = 1;  ///0 min heap, 1 max heap
    int max_id = 0;
  public:
    Heap(int,int);//
    ~Heap();//
    int get_array_size();
    int get_id(int);
    int get_max_id();
    void max_heapify( int);/// according to performance
    void min_heapify( int);/// according to performance
    void build_max_heap();/// build heap according to performance
    void build_min_heap();//
    void heapsort( int, int);/// sorts according to performance
    void insert(node);//
    void extract_max();//
    void extract_min();//
    void increase_key(int, node);
    int find_node(int);
    void reset_heap(); ///adds removed items back to heap (maked heap_size = array_size)

    void heapsort_calls( int, int);/// sorts according to number of calls
    void build_max_heap_calls();/// build heap according to number of calls
    void build_min_heap_calls();/// build heap according to number of calls
    void max_heapify_calls( int);/// according to number of calls
    void min_heapify_calls( int);/// according to number of calls
    void increase_key_calls(int, node);
};

