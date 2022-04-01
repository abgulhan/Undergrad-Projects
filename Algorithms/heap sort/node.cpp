#include "node.h"
using namespace std;

node::node(int new_id, int new_calls, int new_pos, int new_neg){
    id = new_id;
    calls = new_calls;
    positive_feedback = new_pos;
    negative_feedback = new_neg;
    score = 2*new_calls + new_pos - new_neg;
}
node::node(){
    id = 0;
    calls = 0;
    positive_feedback = 0;
    negative_feedback = 0;
    score = 0;
}

void node::add_calls(int new_id, int new_calls, int new_pos, int new_neg){
    id += new_id;
    calls += new_calls;
    positive_feedback += new_pos;
    negative_feedback += new_neg;
    score = 2*calls + positive_feedback - negative_feedback;
}

int node::get_id(){
    return id;
}

int node::get_calls(){
    return calls;
}


