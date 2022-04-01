#include <iostream>
#include <string>
using namespace std;
class Hash_table{
    string *table;
    int hash_size = 0;
    int array_size = 0;
    int collisions = 0; ///total collisions when inserting
    int search_collisions = 0; /// total collsions when searching
    int p; ///random prime
    int a[4]; ///used for universal hashing
  public:
    Hash_table(int size); ///read from file and initialize hash table
    ~Hash_table();
    //int get_array_size();
    int get_array_size();
    int get_hash_size();
    int get_collisions();
    int get_p();
    int get_a(int);
    int get_search_collisions();
    void linear_probe(int line_number, string word);
    void double_hash(int line_number, string word);
    void universal_hash(int line_number, string word);
    void print(int = -1);
    int search_linear_probe(int line_number, string word);
    int search_double_hash(int line_number, string word);
    int search_universal_hash(int line_number, string word);

};



