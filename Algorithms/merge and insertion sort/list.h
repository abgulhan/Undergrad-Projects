#include <vector>
#include "item.h"
using namespace std;
class List{
    string header;
    vector<Item> my_list;
    unsigned long int length = 0;
    string file_adr;
    void merge(vector<Item>&, vector<Item>&, vector<Item>&);
    void merge_sort(vector<Item>& );
    long double datetoint(string); /// convert timestamp to integer (in seconds) for comparison, example input 2017-06-20 07:35:05.285850
  public:
    List(string);
    void make(int, string);
    void merge_sort();
    void insertion_sort();
    void print();
    void write_to_file(string);
};
