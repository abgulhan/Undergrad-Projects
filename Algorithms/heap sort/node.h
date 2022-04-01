using namespace std;

class node{
//public:
    int id;
    int calls;
    int positive_feedback;
    int negative_feedback;
    int score;
  public:
    node(int, int, int, int);
    node();
    void add_calls(int, int, int, int);
    int get_id();
    int get_calls();
    friend bool operator> (const node &n1, const node &n2){
        return n1.score > n2.score;
    }
    friend bool operator< (const node &n1, const node &n2){
        return n1.score < n2.score;
    }
    node& operator+=(const node& rhs){
        this->calls += rhs.calls;
        this->positive_feedback += rhs.positive_feedback;
        this->negative_feedback += rhs.negative_feedback;
        score = 2*calls + positive_feedback - negative_feedback;
        return *this;
    }
};
