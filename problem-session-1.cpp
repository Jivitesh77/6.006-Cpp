#include <bits/stdc++.h>
using namespace std;
int main() {
//1-1. sterling approximation {\displaystyle n!\sim {\sqrt {2\pi n}}\left({\frac {n}{e}}\right)^{n}.}
// \(n!\approx \left(\frac{n}{e}\right)^{n}\)
// 1-2
}
class DS{
    private:
    deque<int> d;
    public:
    void insert_first(int x){
        d.push_front(x);
    }
    int delete_first(){
        if(d.empty()){
            throw out_of_range("Deque is empty");
        }
        int x = d.front();
        d.pop_front();
        return x;
    }
    int delete_last(){
        if(d.empty()){
            throw out_of_range("Deque is empty");
            
        }
        int x = d.back();
            d.pop_back();
            return x;

    }
    void insert_last(int x){
        d.push_back(x);
    }
    int size(){
        return d.size();
    }
};
    void swap_ends(DS& D){
        if(D.size() < 2){
            return;
        }
        int first_item = D.delete_first();
        int last_item = D.delete_last();
        D.insert_first(last_item);
        D.insert_last(first_item);
    }
    void shift_left(DS& D, int k){
        for(int i =0; i< k; i++){
            int item = D.delete_first();
            D.insert_last(item);
        }
    }
    void shift_right(DS& D, int k){
        for(int i=0; i<k; i++){
            int item = D.delete_last();

        }
    }
    // 1-3
    class DynamicCircularArray {
private:
    vector<int>A; // Memory allocation is handled automatically
    int head;
    int size;

    // Resizes and realigns the array to start at physical index 0
    void resize(int new_capacity) {
        if (new_capacity < 1) new_capacity = 1;
        
        // Let std::vector allocate the new memory block
        vector<int> new_A(new_capacity);
        
        for (int i = 0; i < size; ++i) {
            new_A[i] = A[(head + i) % A.size()];
        }
        
        // Move assignment safely swaps the underlying memory and cleans up the old array
        A = std::move(new_A); 
        head = 0;
    }

public:
    DynamicCircularArray() {
        A.resize(4); // Initial capacity
        head = 0;
        size = 0;
    }

    // O(1) Worst-case Index Lookup
    int get(int i) const {
        if (i < 0 || i >= size) throw std::out_of_range("Index out of bounds");
        return A[(head + i) % A.size()];
    }

    // O(1) Worst-case Index Update
    void set(int i, int val) {
        if (i < 0 || i >= size) throw std::out_of_range("Index out of bounds");
        A[(head + i) % A.size()] = val;
    }

    // Amortized O(1) Insert at Front
    void insert_first(int x) {
        if (size == A.size()) {
            resize(2 * A.size());
        }
        head = (head - 1 + A.size()) % A.size();
        A[head] = x;
        size++;
    }

    // Amortized O(1) Insert at Back
    void insert_last(int x) {
        if (size == A.size()) {
            resize(2 * A.size());
        }
        int tail = (head + size) % A.size();
        A[tail] = x;
        size++;
    }

    // Amortized O(1) Delete from Front
    int delete_first() {
        if (size == 0) throw std::out_of_range("Sequence is empty");
        
        int val = A[head];
        head = (head + 1) % A.size();
        size--;

        if (size > 0 && size <= A.size() / 4) {
            resize(A.size() / 2);
        }
        return val;
    }

    // Amortized O(1) Delete from Back
    int delete_last() {
        if (size == 0) throw std::out_of_range("Sequence is empty");
        
        int tail = (head + size - 1) % A.size();
        int val = A[tail];
        size--;

        if (size > 0 && size <= A.size() / 4) {
            resize(A.size() / 2);
        }
        return val;
    }

    int get_size() const {
        return size;
    }
    
    int get_capacity() const {
        return A.size();
    }
};

int main() {
    DynamicCircularArray seq;

    seq.insert_last(10);  // [10]
    seq.insert_last(20);  // [10, 20]
    seq.insert_first(5);  // [5, 10, 20]
    seq.insert_first(2);  // [2, 5, 10, 20]

    std::cout << "Sequence after insertions: ";
    for (int i = 0; i < seq.get_size(); ++i) {
        std::cout << seq.get(i) << " ";
    }
    std::cout << "\n";

}
//1-4
/*
 * ALGORITHM DESCRIPTION (Part A):
 * 
 * 1. Find the Midpoint: Initialize two pointers, `slow` and `fast`, pointing to 
 *    the head. Move `slow` one step and `fast` two steps at a time. Because 
 *    the list has exactly 2n nodes, when `fast` reaches the end, `slow` will 
 *    land on the (n+1)st node (the start of the second half). Keep track of 
 *    the nth node using a `prev_to_slow` pointer.
 * 
 * 2. Sever the List: Break the linked list into two independent halves by 
 *    setting the nth node's `next` pointer to `nullptr`.
 * 
 * 3. Reverse the Second Half: Iterate through the second half (starting at 
 *    `slow`). Use three temporary pointers (`prev`, `curr`, `next_temp`) to 
 *    flip the direction of the `next` links in place. This operates in O(n) 
 *    time and uses O(1) space, satisfying the no-new-nodes constraint.
 * 
 * 4. Reconnect: Set the nth node's `next` pointer to point to `prev` (which 
 *    is now the head of the reversed second half), stitching the list back 
 *    together.
 */
struct Node {
    std::string name;
    Node* next;
};

void reorder_students(Node* head) {
    if (!head || !head->next) return;
    
    // 1. Find the midpoint using fast and slow pointers
    Node* slow = head;
    Node* fast = head;
    Node* prev_to_slow = nullptr;
    
    while (fast && fast->next) {
        fast = fast->next->next;
        prev_to_slow = slow;
        slow = slow->next;
    }
    
    // 2. Sever the list into two halves
    prev_to_slow->next = nullptr;
    
    // 3. Reverse the second half in-place (O(1) space)
    Node* prev = nullptr;
    Node* curr = slow;
    while (curr) {
        Node* next_temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_temp;
    }
    
    // 4. Reconnect the end of the first half to the head of the reversed second half
    prev_to_slow->next = prev;
}
//(b)
struct Node {
    std::string name;
    Node* next;
    
    Node(std::string n) : name(n), next(nullptr) {}
};

void reorder_students(Node* head) {
    // Check if the list is empty or has only 1 node (though problem states 2n kids)
    if (!head || !head->next) {
        return;
    }
    
    Node* slow = head;
    Node* fast = head;
    Node* prev_to_slow = nullptr;
    
    // 1. Find the (n+1)st node using slow/fast pointers
    while (fast && fast->next) {
        fast = fast->next->next;
        prev_to_slow = slow;
        slow = slow->next;
    }
    
    // 2. Sever the connection between the first half and second half
    if (prev_to_slow) {
        prev_to_slow->next = nullptr;
    }
    
    // 3. Reverse the second half of the list in place
    Node* prev = nullptr;
    Node* curr = slow;
    while (curr) {
        Node* next_temp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next_temp;
    }
    
    // 4. Reconnect the end of the first half to the new start of the second half
    if (prev_to_slow) {
        prev_to_slow->next = prev;
    }
}

// Helper function to print the list
void print_list(Node* head) {
    while (head) {
        std::cout << head->name;
        if (head->next) std::cout << " -> ";
        head = head->next;
    }
    std::cout << "\n";
}

int main() {
    // Setup a 2n list (n=3, 2n=6 kids)
    Node* head = new Node("Kid1");
    head->next = new Node("Kid2");
    head->next->next = new Node("Kid3"); // End of first half (Jen's line)
    head->next->next->next = new Node("Kid4"); // Start of second half
    head->next->next->next->next = new Node("Kid5");
    head->next->next->next->next->next = new Node("Kid6");

    std::cout << "Original Line: ";
    print_list(head);

    reorder_students(head);

    std::cout << "Reordered Line: ";
    print_list(head);

    // Memory cleanup omitted for brevity
}
