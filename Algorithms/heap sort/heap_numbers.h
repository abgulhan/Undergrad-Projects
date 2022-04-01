
using namespace std;
class Heap_numbers{ ///always max heap
public:
    int *heap;
    int heap_size = 0;
    int array_size = 0;
    int max_array_size;
  public:
    Heap_numbers(int);//
    ~Heap_numbers();//
    int get_array_size();
    int get_heap_size();
    void max_heapify( int);
    void build_max_heap();
    void heapsort( int);
    void insert(int);//
    void extract_max();//
    void reset_heap(); ///adds removed items back to heap (maked heap_size = array_size)
    int get_number(int);
    void write_to_file();

};

