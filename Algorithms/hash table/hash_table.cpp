#include "hash_table.h"
#include <stdlib.h>
#include <time.h>

bool is_prime(int num){
  for (int i=2; i<=num/2 ; i++)
     if (num%i==0)
        return false;
  return true;
}

Hash_table::Hash_table(int size){
    srand (time(NULL));
    table = new string[size];
    array_size = size;
    for (int i=0;i<size;i++){
        table[i] = "";
    }

    int random_prime = rand() % size;
    while(!is_prime(random_prime)){
        random_prime = rand() % size;
    }
    p = random_prime;
    for(int i=0; i<=3; i++)
        a[i] = rand() % size;
}
Hash_table::~Hash_table(){
    delete [] table;
}

int Hash_table::get_array_size(){
    return array_size;
}
int Hash_table::get_hash_size(){
    return hash_size;
}
int Hash_table::get_collisions(){
    return collisions;
}
int Hash_table::get_search_collisions(){
    return search_collisions;
}
int Hash_table::get_p(){
    return p;
}
int Hash_table::get_a(int i){
    return a[i];
}
void Hash_table::linear_probe(int line_number, string word){
    if(hash_size == array_size){
        cout << "hash table full, cannot insert" << endl;
        return;
    }
    int i=0;
    int hashed_value;
    while (i <= array_size-1){
        hashed_value = (line_number + i)%array_size;
        if(table[hashed_value] == ""){
            table[hashed_value] = word;
            hash_size++;
            return;
        }
        else{
            i++;
            collisions++;
        }
    }
}

void Hash_table::double_hash(int line_number, string word){
    if(hash_size == array_size){
        cout << "hash table full, cannot insert" << endl;
        return;
    }
    int i=0;
    int hashed_value;

    while (i <= array_size-1){
        hashed_value = (line_number + i*(p - (line_number % p)))%array_size;
        if(table[hashed_value] == ""){ /// if no collision
            table[hashed_value] = word;
            hash_size++;
            return;
        }
        else{
            i++;
            collisions++;
        }
    }
    return;
}

void Hash_table::universal_hash(int line_number, string word){
    if(hash_size == array_size){
        cout << "hash table full, cannot insert" << endl;
        return;
    }
    int i=0;
    int hashed_value;
    int temp = line_number;
    int k[4]; ///decomposition of list_number:
    for(int i=3; i>=0; i--){
        k[i] = temp % 100; ///get first 2 digits
        temp -= k[i];
        temp = temp/100; /// remove last 2 digits
    }

    while (i <= array_size-1){
        ///using double hashing as our open addressing strategy, as it gives better results compared to linear probing
        hashed_value = (a[0]*k[0] + a[1]*k[1] + a[2]*k[2] + a[3]*k[3] + i*(p - (line_number % p)))%array_size ;
        if(table[hashed_value] == ""){ /// if no collision
            table[hashed_value] = word;
            hash_size++;
            return;
        }
        else{
            i++;
            collisions++;
        }
    }
    return;
}


void Hash_table::print(int print_size){
    if (print_size == -1)
        print_size = array_size;
    for(int i=0; i<print_size-1; i++){
        cout << i << ": " << table[i] << endl;
    }
    return;
}




int Hash_table::search_linear_probe(int line_number, string word){
    int i=0;
    int hashed_value;
    while (i <= array_size-1){
        hashed_value = (line_number + i)%array_size;
        if(table[hashed_value] == word){
            return hashed_value; ///word found
        }
        else{
            i++;
            search_collisions++;
        }
    }
    return -1; ///word not found in hash table
}

int Hash_table::search_double_hash(int line_number, string word){
    int i=0;
    int hashed_value;
    while (i <= array_size-1){
        hashed_value = (line_number + i*(p - (line_number % p)))%array_size;
        if(table[hashed_value] == word){
            return hashed_value; ///word found
        }
        else{
            i++;
            search_collisions++;
        }
    }
    return -1; ///word not found in hash table
}

int Hash_table::search_universal_hash(int line_number, string word){
    int i=0;
    int hashed_value;
    int temp = line_number;
    int k[4]; ///decomposition of list_number:
    for(int i=3; i>=0; i--){
        k[i] = temp % 100; ///get first 2 digits
        temp -= k[i];
        temp = temp/100; /// remove last 2 digits
    }

    while (i <= array_size-1){
        ///used double hashing as open adressing strategy
        hashed_value = (a[0]*k[0] + a[1]*k[1] + a[2]*k[2] + a[3]*k[3] + i*(p - (line_number % p)))%array_size ;
        if(table[hashed_value] == word){
            return hashed_value; ///word found
        }
        else{
            i++;
            search_collisions++;
        }
    }
    return -1; ///word not found in hash table
}
