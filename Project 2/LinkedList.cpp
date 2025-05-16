#include "include/LinkedList.hpp"

void insert(int x, int priority) {
    Node* t = new Node;
    t->data = x;
    t->priority = priority;
    t->next = nullptr;

    if (first == nullptr || priority > first->priority) {
        t->next = first;
        first = t;
    } else {
        Node* p = first;
        while (p->next != nullptr && p->next->priority >= priority) {
            p = p->next;
        }
        t->next = p->next;
        p->next = t;
    }
}

// void delete_p(int priority) {
//     if (first == nullptr) return;

//     Node* p = first;
//     Node* q = nullptr;

//     // Jeśli pierwszy element ma podany priorytet
//     if (first->priority == priority) {
//         q = first;
//         first = first->next;
//         delete q;
//         return;
//     }

//     // Szukamy dalej w kolejce
//     while (p->next != nullptr && p->next->priority != priority) {
//         p = p->next;
//     }

//     // Jeśli znaleziono
//     if (p->next != nullptr) {
//         q = p->next;
//         p->next = q->next;
//         delete q;
//     }
//     // Jeśli nie znaleziono — nic nie robimy
// }

void delete_p() {
    if (first == nullptr) return;

    Node* temp = first;
    first = first->next;
    delete temp;
}


void create(int data[], int priorytety[], int n) {
    for (int i = 0; i < n; ++i) {
        insert(data[i], priorytety[i]);
    }
}

int queue_size() {
    int count = 0;
    Node* p = first;
    while (p != nullptr) {
        count++;
        p = p->next;
    }
    return count;
}


void display(){
    Node* p = first;
    while (p != nullptr ) {
        std::cout << "<" << p->data << ","<< p->priority << ">  ";
        p = p->next;
    }
    
}

int peek() {
    // if(first == nullptr) {
    //     std::cout << "Queue is empty.\n";
    //     return -1;
    // }
    return first->data;
}


void modify_priority(int data, int old_p, int new_p) {
    if (first == nullptr) return;

    Node* p = first;
    Node* q = nullptr;

    
    if (first->priority == old_p && first->data == data) {
        Node* temp = first;
        first = first->next;
        delete temp;
        insert(data, new_p);
        return;
    }

    // Szukamy dalej
    while (p->next != nullptr) {
        if (p->next->priority == old_p && p->next->data == data) {
            q = p->next;
            p->next = q->next;
            delete q;
            insert(data, new_p);
            return;
        }
        p = p->next;
    }

    // std::cout << "Nie znaleziono  <" << data << ", " << old_p << ">\n";
}

void random_array(int* tab, int size, int down, int up) {
    for (int i = 0; i < size; i++) {
        tab[i] = rand() % (up - down + 1) + down;
    }
}

void create_optimized(int data[], int priorities[], int n) {
    std::vector<std::pair<int, int>> pairs(n);
    for (int i = 0; i < n; ++i) {
        pairs[i] = { priorities[i], data[i] };
    }

    // Sort by priority descending
    std::sort(pairs.begin(), pairs.end(), std::greater<>());

    for (int i = 0; i < n; ++i) {
        Node* t = new Node;
        t->data = pairs[i].second;
        t->priority = pairs[i].first;
        t->next = first;
        first = t;
    }
}

void clear_queue() {
    Node* p = first;
    while (p != nullptr) {
        Node* temp = p;
        p = p->next;
        delete temp;
    }
    first = nullptr;
}
