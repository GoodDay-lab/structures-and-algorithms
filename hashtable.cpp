#include <iostream>

template <class TYPE>
struct HashtableNode {
    int is_empty;
    TYPE data;
};

template <class TYPE>
class Hashtable {
private:
    HashtableNode<TYPE> *buffer;
    unsigned int size;

    unsigned int hash1(const char *key) {
        unsigned int retval;
        const char *cur_i;
        for (cur_i = key; *cur_i != 0; cur_i++) {
            retval += *cur_i + (*cur_i % 7);
        }
        return retval % this->size;
    };
    unsigned int hash2(const char *key) {
        unsigned int retval;
        const char *cur_i;
        for (cur_i = key; *cur_i != 0; cur_i++) {
            retval += *cur_i + (*cur_i % 7);
        }
        return retval % (this->size / 3);
    };
public:
    Hashtable(unsigned int size);
    ~Hashtable();

    void addItem(const char *key, TYPE item);
    void getItem(const char *key, TYPE *item);
};

template <class TYPE>
Hashtable<TYPE>::Hashtable(unsigned int size) {
    this->buffer = new HashtableNode<TYPE>[size];
    this->size = size;
    
    unsigned int i;
    for (i = 0; i < this->size; i++) {
        this->buffer[i].is_empty = 1;
    }
}

template <class TYPE>
Hashtable<TYPE>::~Hashtable() {
    delete [] this->buffer;
}

template <class TYPE>
void Hashtable<TYPE>::addItem(const char *key, TYPE item) {
    if (!key) return;
    unsigned int base_I = this->hash1(key);
    unsigned int step_I = this->hash2(key);
    unsigned int count = 5;

    std::cout << "adding (key: \"" << key << "\") to index: " << base_I << std::endl;
    this->buffer[base_I].data = item;
    this->buffer[base_I].is_empty = 0;
}

template <class TYPE>
void Hashtable<TYPE>::getItem(const char *key, TYPE *item) {
    if (!key) return;
    unsigned int base_I = this->hash1(key);
    unsigned int step_I = this->hash2(key);
    unsigned int count = 5;

    std::cout << "getting (key: \"" << key << "\") to index: " << base_I << std::endl;
    *item = this->buffer[base_I].data;
    this->buffer[base_I].is_empty = 1;
}


int main() {
    int var;

    Hashtable<int> hshtb { 128 };
    hshtb.addItem("123", 14);
    hshtb.addItem("124", 15);
    hshtb.addItem("512", 16);
    hshtb.addItem("215", 18);

    hshtb.getItem("512", &var);
    std::cout << var << std::endl;
}
