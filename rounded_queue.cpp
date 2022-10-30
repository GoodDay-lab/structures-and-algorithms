/*
 *   Rounded queue is non-blocking structure, so it safer to use 
 * in different async apps. For example, web-servers.
 */


template <class TYPE>
class RoundedQueue {
private:
    TYPE *buffer;
    unsigned int w_head;
    unsigned int r_head;
    unsigned int size;
public:
    RoundedQueue(unsigned int size);
    ~RoundedQueue();
    void addItem(TYPE item);
    TYPE getItem();
};

template <class TYPE>
RoundedQueue<TYPE>::RoundedQueue(unsigned int size) {
    this->buffer = new TYPE[size];
    this->w_head = this->r_head = 0;
    this->size = size;
}

template <class TYPE>
RoundedQueue<TYPE>::~RoundedQueue() {
    delete [] this->buffer;
}

template <class TYPE>
void RoundedQueue<TYPE>::addItem(TYPE item) {
    unsigned int next_Index = (this->w_head + 1) % this->size;
    if (next_Index == this->r_head) 
        return;
    this->buffer[this->w_head] = item;
    this->w_head = next_Index;
}

template <class TYPE>
TYPE RoundedQueue<TYPE>::getItem() {
    unsigned int next_Index = (r_head + 1) % this->size;
    TYPE ret;
    if (this->w_head == this->r_head)
        return 0;
    ret = this->buffer[this->r_head];
    this->r_head = next_Index;
    return ret;
}

#include <iostream>

int main() {
    RoundedQueue<int> rqi(10); 
    rqi.addItem(6);
    rqi.addItem(10);
    int ans;
    std::cout << rqi.getItem() << std::endl;
    std::cout << rqi.getItem() << std::endl;
    std::cout << rqi.getItem() << std::endl;
}
