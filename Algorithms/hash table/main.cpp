#include <iostream>
#include <fstream>
#include "hash_table.h"

using namespace std;

int find_line_number(string search_word, string vocab_file); /// used to find the linenumber of a word from vocab.txt


int main(int argc, char* argv[]){
    string search_file_name;
    string vocab_file_name;
    if (argc != 3){ ///check if enough parameters have been passed
        cout << "Usage is <vocab file name> <search file name>"<<endl; // Inform the user of how to use the program
        //cin.get();
        exit(0);
    }
    else {
        vocab_file_name = argv[1];
        search_file_name = argv[2];
    }

    Hash_table linear1(17863);
    Hash_table linear2(21929);
    Hash_table double1(17863);
    Hash_table double2(21929);
    Hash_table universal1(17863);
    Hash_table universal2(21929);
    ifstream input_file(vocab_file_name);
    string word;
    int i=0; ///line counter
    while (input_file >> word){ ///read file
        if(word == ""){;} ///don't add empty lines
        else{
            linear1.linear_probe(i, word);
            linear2.linear_probe(i, word);
            double1.double_hash(i, word);
            double2.double_hash(i, word);
            universal1.universal_hash(i, word);
            universal2.universal_hash(i, word);
        }
        i++;
    }
    ifstream search_file(search_file_name);
    i=0; ///line counter
    int line_number;
    string search_word;
    while (search_file >> search_word){ ///read file
        line_number = find_line_number(search_word, vocab_file_name); ///find line number of the word we will search

        linear1.search_linear_probe(line_number, search_word);
        linear2.search_linear_probe(line_number, search_word);
        double1.search_double_hash(line_number, search_word);
        double2.search_double_hash(line_number, search_word);
        universal1.search_universal_hash(line_number, search_word);
        universal2.search_universal_hash(line_number, search_word);

        i++;
        break;
    }
    cout << "\tINSERTION COLLISIONS " << endl;
    cout << "linear probing" << endl;
    cout << "m = 17863:  " << linear1.get_collisions()<<endl;
    cout << "m = 21929:  " << linear2.get_collisions()<<endl;
    cout << "double hashing" << endl;
    cout << "m = 17863:  " << double1.get_collisions()<<endl;
    cout << "m = 21929:  " << double2.get_collisions()<<endl;
    cout << "universal hashing" << endl;
    cout << "m = 17863:  " << universal1.get_collisions()<<endl;
    cout << "m = 21929:  " << universal2.get_collisions()<<endl<<endl;

    cout << "\tSEARCH COLLISIONS " << endl;
    cout << "linear probing" << endl;
    cout << "m = 17863:  " << linear1.get_search_collisions()<<endl;
    cout << "m = 21929:  " << linear2.get_search_collisions()<<endl;
    cout << "double hashing" << endl;
    cout << "m = 17863:  " << double1.get_search_collisions()<<endl;
    cout << "m = 21929:  " << double2.get_search_collisions()<<endl;
    cout << "universal hashing" << endl;
    cout << "m = 17863:  " << universal1.get_search_collisions()<<endl;
    cout << "m = 21929:  " << universal2.get_search_collisions()<<endl;
    return 0;
}

int find_line_number(string search_word, string vocab_file){
    ifstream infile(vocab_file);
    string word;
    int i=0; ///line counter
    while (infile >> word){ ///read file
        if(word == search_word){
            return i;}
        i++;
    }
    cout << "word: " << search_word << " not found" << endl;
    return -1;
}
