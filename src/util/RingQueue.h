
#include <queue>

using namespace std;

template <typename T>
class RingQueue : public deque<T> {
  const int length;

 public:
  RingQueue(int l) : length(l) {}

  void push(const T& value) {
    if (this->size() == length) this->pop_front();
    deque<T>::push_back(value);
  }
};