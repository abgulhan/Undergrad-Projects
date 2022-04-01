#include <string>
using namespace std;
class Item{ ///Each line of csv will be stored in this class
  public:
    string data;  /// each csv line is stored here
    long double label;  /// sorting by labels
};
