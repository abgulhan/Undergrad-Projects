#include <iostream>
#include "string.h"
#include "heap.h"
#include "heap_numbers.h"
#include <chrono>
#include <fstream>
#include <sstream>

using namespace std;

int main(){
    string file_name = "./day";
    Heap max_heap(1000,1);///stores according to score
    Heap min_heap(1000,0);
    Heap max_heap_calls(1000,1);///stores according to call number
    Heap min_heap_calls(1000,0);
    int key_location; /// used for checking if id already exists
    //bool is_heap;
    string id;
    string calls;
    string pos;
    string neg;

    for(int i=1; i<=10; i++){
        max_heap.reset_heap();///since we sorted the heaps, heap size was decreased, reset heap size.
        min_heap.reset_heap();
        max_heap_calls.reset_heap();
        min_heap_calls.reset_heap();
        ifstream file(file_name + to_string(i) + ".csv");
        //cout << file_name + to_string(i) << endl;
        while (getline(file, id, ',')) { ///read each line

            //cout << "ID: " << id << " ";

            getline(file, calls, ',');
            //cout << "Calls: " << calls << " ";

            getline(file, pos, ',');
            //cout << "Pos feedback: " << pos << " ";
            getline(file, neg);
            //cout << "Neg feedback: " <<  neg<< endl ;
            node new_node(stoi(id),stoi(calls),stoi(pos),stoi(neg)); ///contruct new node to be added


            if( new_node.get_id() > max_heap.get_max_id()){ ///since max and min heap contain same items only need to search one heap
                //cout << "insert "<<new_node.id << endl;
                max_heap.insert(new_node); ///add node
                min_heap.insert(new_node);
                max_heap_calls.insert(new_node);
                min_heap_calls.insert(new_node);
            }
            else{///id already in heap
                //key_location = -1;
                key_location = max_heap.find_node(stoi(id));
                //cout << new_node.id << "->"<< max_heap.get_id(key_location)<<endl;
                max_heap.increase_key(key_location, new_node);///updating existing node keeps heap property

                key_location = min_heap.find_node(stoi(id));
                min_heap.increase_key(key_location, new_node);

                key_location = max_heap_calls.find_node(stoi(id));
                //cout << new_node.id << "->"<< max_heap.get_id(key_location)<<endl;
                max_heap_calls.increase_key_calls(key_location, new_node);

                key_location = min_heap_calls.find_node(stoi(id));
                min_heap_calls.increase_key_calls(key_location, new_node);
            }
        }///end of while


        ///sort heap for 3 items
        max_heap.heapsort(3,1);
        min_heap.heapsort(3,0);
        max_heap_calls.heapsort_calls(3,1);
        min_heap_calls.heapsort_calls(3,0);


        cout << "AFTER DAY-" << i << endl;
        cout << "BEST PERFORMANCE :" << max_heap.get_id(max_heap.get_array_size()-1)<< ", "
            << max_heap.get_id(max_heap.get_array_size()-2) << ", "
            << max_heap.get_id(max_heap.get_array_size()-3) << endl;
        //for(int i=0; i<max_heap.get_array_size(); i++){
            //cout << max_heap.heap[i].id << ": " << max_heap.heap[i].score << endl;
        //}
        cout << "WORST PERFORMANCE:" << min_heap.get_id(max_heap.get_array_size()-1) << ", "
            << min_heap.get_id(max_heap.get_array_size()-2) << ", "
            << min_heap.get_id(max_heap.get_array_size()-3) << endl;



        cout << "MAXIMUM CALLS    :" << max_heap_calls.get_id(max_heap.get_array_size()-1)<< ", "
            << max_heap_calls.get_id(max_heap.get_array_size()-2) << ", "
            << max_heap_calls.get_id(max_heap.get_array_size()-3) << endl;
     //   for(int i=0; i<max_heap.array_size; i++){
            //cout << max_heap_calls.heap[i].id << ": " << max_heap_calls.heap[i].calls << endl;
       // }
        cout << "MINIMUM CALLS    :" << min_heap_calls.get_id(max_heap.get_array_size()-1) << ", "
            << min_heap_calls.get_id(max_heap.get_array_size()-2) << ", "
            << min_heap_calls.get_id(max_heap.get_array_size()-3) << endl;
        //for(int i=0; i<min_heap.array_size; i++){
            //cout << min_heap_calls.heap[i].id << ": " << min_heap_calls.heap[i].calls << endl;
        //}
        cout << endl;
    }///end of for

    ///sorting numbers.csv
    int new_num;
    int temp_size;
    Heap_numbers num_heap(2500000);

    ifstream file("numbers.csv");
    while(file >> new_num){/// read file
        num_heap.insert(new_num);
    }
    int counter = 0;
    while(num_heap.get_heap_size()>0){
        counter++;
        temp_size = num_heap.get_heap_size();
        auto start = chrono::steady_clock::now(); ///start time before sort
        num_heap.heapsort(200000);
        auto end = chrono::steady_clock::now(); /// end time after sort
        /*for(int i=num_heap.get_heap_size()-1; i<temp_size; i++){
            cout << num_heap.get_number(i) << endl;
        }*/
        chrono::duration<double> diff = end-start;///total time taken to sort
        cout << "Heap size: " << temp_size << endl;
        cout << "Time taken to sort block " << counter<< " of 200k: " <<diff.count() << "s" << endl;
    }

    file.close();
    num_heap.write_to_file();///write to numbers_sorted.csv
    return 0;
}
