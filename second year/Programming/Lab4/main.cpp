#include <iostream>
#include <string>

using namespace std;

class Node
{
    char value;
    Node* next;
    Node* prev;

    Node(char val) : value(val), next(nullptr), prev(nullptr) {}
};

class CircularDoublyLinkedList
{
    Node* head;
    Node* tail;

    CircularDoublyLinkedList() : head(nullptr), tail(nullptr) {}

    bool isEmpty() {
        return head == nullptr;
    }

    void append(char value)
    {
        Node* newNode = new Node(value);
        if (isEmpty())
        {
            head = newNode;
            tail = newNode;
            head->next = tail;
            head->prev = tail;
        } else
        {
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
        }
    }

    void insertAtBeginning(char value) {
        Node* newNode = new Node(value);
        if (isEmpty())
        {
            append(value);
        } else
        {
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insertAtPosition(char value, int position) {
        if (position < 0) {
            cout << "Invalid position" << endl;
            return;
        }
        if (position == 0) {
            insertAtBeginning(value);
        } else {
            Node* newNode = new Node(value);
            Node* current = head;
            int count = 0;
            while (current && count < position) {
                current = current->next;
                count++;
            }
            if (count < position) {
                cout << "Position out of range" << endl;
                return;
            }
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }

    void removeAtBeginning() {
        if (isEmpty()) {
            cout << "List is empty, cannot remove." << endl;
            return;
        }
        if (head == tail) {
            delete head;
            head = nullptr;
            tail = nullptr;
        } else {
            Node* newHead = head->next;
            newHead->prev = tail;
            tail->next = newHead;
            delete head;
            head = newHead;
        }
    }

    void printList() {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }
        Node* current = head;
        int index = 0;
        do {
            cout << "Element at index " << index << ": " << current->value << endl;
            current = current->next;
            index++;
        } while (current != head);
    }

    ~CircularDoublyLinkedList() {
        while (!isEmpty()) {
            removeAtBeginning();
        }
    }
};

int main() {
    CircularDoublyLinkedList myList;
    myList.append('A');
    myList.append('B');
    myList.append('C');
    myList.insertAtBeginning('Z');
    myList.insertAtPosition('X', 2);
    myList.printList();
    myList.removeAtBeginning();
    myList.printList();
    return 0;
}
