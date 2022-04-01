#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "list.h"
using namespace std;

List::List(string adress){
    file_adr = adress;
}

void List::make(int len, string criterion){///size defines how many lines to read
    ifstream data(file_adr);
    string line;
    unsigned int value = 0; /// contains column to sort value

    getline(data, line); /// get the headers
    header = line;
    char * ch = const_cast<char*> (line.c_str()); /// turning string into char* to be used with strtok
    ch = strtok(ch,",");

    while (ch != NULL){ ///determine which column to sort with
        //printf ("%s\n",ch);
        if (strcmp(ch,criterion.c_str()) != 0){
            value++;
            //cout << ch << endl;
        }
        else{
            break;
        }
        ch = strtok (NULL, ",");
    }

    unsigned int i = 0;
    string my_row;
    string my_item;
    while (getline(data, my_row) && (length < len)){
        //cout << my_row << endl;
        my_list.push_back(Item());
        my_list[length].data = my_row;

        istringstream iss(my_row);///iterate over current line
        while(getline(iss, my_item,',')){///get the label for each row
            if(i == value){
                i = 0;
                if(value == 0){ /// if comparing time stamps change it into seconds
                    my_list[length].label = datetoint(my_item);
                }
                else{
                    my_list[length].label = stof(my_item); /// assign label
                }
                break;
            }
            else{
                i++;
            }

        }
        length++;
    }
    data.close();
}

void List::print(){
    ///cout << header << endl;
    for(unsigned int i=0; i<length; i++){
        cout << my_list[i].label << endl;
        //cout << "____________________" << endl;
    }
}


void List::merge_sort(vector<Item> & part){
    if (part.size() <= 1){///ending condition
        return;
    }

        auto half = part.size() / 2; /// split vector in middle
        //cout << "half: "<<half << endl;
        vector<Item> left(part.begin(), part.begin() + half);
        vector<Item> right(part.begin() + half, part.end());

        merge_sort(left);
        merge_sort(right);
        merge(left, right, part); ///sort and merge the sublists
}

void List::merge(vector<Item>& left, vector<Item>& right, vector<Item>& part)
{
    int size_L = left.size();
    int size_R = right.size();
    int part_count = 0;
    int left_count = 0;
    int right_count = 0;

    while (left_count < size_L && right_count < size_R){
        if (left[left_count].label < right[right_count].label) {
            part[part_count] = left[left_count];
            left_count++;
        }
        else {
            part[part_count] = right[right_count];
            right_count++;
        }
        part_count++;
    }
    ///when one side finishes before the other
    while (left_count < size_L) {
        part[part_count] = left[left_count];
        left_count++;
        part_count++;
    }
    while (right_count < size_R) {
        part[part_count] = right[right_count];
        right_count++;
        part_count++;
    }
}

void List::merge_sort(){
    merge_sort(my_list);
}

void List::insertion_sort(){
   unsigned int i; ///outer loop counter
   int j; ///inner loop counter
   Item key;
   //int key_count;
   for (i = 1; i < length; i++) {
       key = my_list[i];
       //key_count = i;
       j = i-1;

       while (j >= 0 && my_list[j].label > key.label) {
            my_list[j+1] = my_list[j];
            j = j-1;
       }
       my_list[j+1] = key;
   }
}

void List::write_to_file(string filename){
    ofstream outfile(filename);

    outfile << header << "\n";
    for(unsigned int i = 0; i < length; i++){
        outfile << my_list[i].data << "\n";
    }
    outfile.close();
}

long double List::datetoint(string timestamp){ ///date to seconds, example input 2017-06-20 07:35:05.285850
    double data[6];
    long double total = 0;
    char * ch = const_cast<char*> (timestamp.c_str()); /// turning string into char* to be used with strtok
    ch = strtok(ch," -:");
    int i = 0;
    while (ch != NULL || i < 6){ ///determine which column to sort with
        //cout << ch << endl;
        data[i] = atoi(ch);
        ch = strtok (NULL, " -:");
        i++;
    }
    ///convert timestamp into seconds
    total = data[0]*31557600 + data[1]*2592000 + data[2]*86400 + data[3]*3600 + data[4]*60 + data[5];
    return total;
}
