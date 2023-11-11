#include <iostream>
#include <string>

// Класс узла списка
class Node {
public:
    char value;    // Значение узла
    Node* next;    // Указатель на следующий узел
    Node* prev;    // Указатель на предыдущий узел

    // Конструктор узла
    Node(char val) : value(val), next(nullptr), prev(nullptr) {}
};

// Класс двунаправленного кольцевого символьного списка
class CircularDoublyLinkedList {
private:
    Node* head;  // Указатель на начало списка
    Node* tail;  // Указатель на конец списка

public:
    CircularDoublyLinkedList() : head(nullptr), tail(nullptr) {}

    // Проверка, пуст ли список
    bool isEmpty() {
        return head == nullptr;
    }

    // Добавление элемента в конец списка
    void append(char value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            head = newNode;
            tail = newNode;
            head->next = tail;
            head->prev = tail;
        } else {
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            tail = newNode;
        }
    }

    // Добавление элемента в начало списка
    void insertAtBeginning(char value) {
        Node* newNode = new Node(value);
        if (isEmpty()) {
            append(value);
        } else {
            newNode->next = head;
            newNode->prev = tail;
            tail->next = newNode;
            head->prev = newNode;
            head = newNode;
        }
    }

    // Вставка элемента на заданную позицию
    void insertAtPosition(char value, int position) {
        if (position < 0) {
            std::cout << "Невозможная позиция" << std::endl;
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
                std::cout << "Вы вышли за список" << std::endl;
                return;
            }
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }

    // Удаление элемента с начала списка
    void removeAtBeginning() {
        if (isEmpty()) {
            std::cout << "Список пуст" << std::endl;
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

    // Вывод списка на экран
    void printList() {
        if (isEmpty()) {
            std::cout << "Список пуст." << std::endl;
            return;
        }
        Node* current = head;
        int index = 0;
        do {
            std::cout << "Значение в индексе " << index << ": " << current->value << std::endl;
            current = current->next;
            index++;
        } while (current != head);
    }

    // Деструктор для освобождения памяти
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
