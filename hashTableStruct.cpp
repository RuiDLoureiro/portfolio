#include <iostream>
#include <list>

using namespace std;

class HashTable {
private:
    int capacity;  
    list<int>* table;  
    int hashFunction(int key);  

public:
    HashTable(int capacity); 
    ~HashTable(); 
    void insert(int key); 
    void remove(int key); 
    bool search(int key);  
};

HashTable::HashTable(int capacity) {
    this->capacity = capacity;
    table = new list<int>[capacity];
}

HashTable::~HashTable() {
    delete[] table;
}

int HashTable::hashFunction(int key) {
    return key % capacity;
}

// Insert key into the table
void HashTable::insert(int key) {
    int index = hashFunction(key);
    table[index].push_back(key);
}

void HashTable::remove(int key) {
    int index = hashFunction(key);
    list<int>::iterator it;
    for (it = table[index].begin(); it != table[index].end(); it++) {
        if (*it == key) {
            table[index].erase(it);
            break;
        }
    }
}

bool HashTable::search(int key) {
    int index = hashFunction(key);
    list<int>::iterator it;
    for (it = table[index].begin(); it != table[index].end(); it++) {
        if (*it == key) {
            return true;
        }
    }
    return false;
}

// testing
int main() {
    HashTable hashtable(10);

    hashtable.insert(12);
    hashtable.insert(25);
    hashtable.insert(35);

    cout << "12 is in the table: " << hashtable.search(12) << endl;
    cout << "25 is in the table: " << hashtable.search(25) << endl;
    cout << "35 is in the table: " << hashtable.search(35) << endl;

    hashtable.remove(25);

    cout << "25 is in the table: " << hashtable.search(25) << endl;

    return 0;
}
