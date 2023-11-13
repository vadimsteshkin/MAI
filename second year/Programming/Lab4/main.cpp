#include <iostream>
#include <string>

/**
 * @brief Класс Node представляет узел в двунаправленном кольцевом списке.
 */
class Node {
public:
    char value;    /**< Значение, хранящееся в узле. */
    Node* next;    /**< Указатель на следующий узел в списке. */
    Node* prev;    /**< Указатель на предыдущий узел в списке. */

    /**
     * @brief Конструктор класса Node.
     * @param val Значение, которое будет храниться в узле.
     * @details Создает новый узел с указанным значением, инициализирует указатели на следующий и предыдущий узлы как nullptr.
     */
    Node(char val) : value(val), next(nullptr), prev(nullptr) {}
};

/**
 * @brief Класс CircularDoublyLinkedList представляет двунаправленный кольцевой список символов.
 */
class CircularDoublyLinkedList {
private:
    Node* head;  /**< Указатель на начало списка. */
    Node* tail;  /**< Указатель на конец списка. */

public:
    /**
     * @brief Конструктор класса CircularDoublyLinkedList.
     * @details Инициализирует указатели на начало и конец списка как nullptr.
     */
    CircularDoublyLinkedList() : head(nullptr), tail(nullptr) {}

    /**
     * @brief Деструктор класса CircularDoublyLinkedList.
     * @details Освобождает память, выделенную для узлов списка,
     * вызывая метод removeAtBeginning() до тех пор, пока список не станет пустым.
     */
    ~CircularDoublyLinkedList() {
        while (!isEmpty()) {
            removeAtBeginning();
        }
    }

    /**
     * @brief Проверяет, пуст ли список.
     * @return Возвращает true, если список пуст, иначе false.
     */
    bool isEmpty() {
        return head == nullptr;
    }

    /**
     * @brief Добавляет элемент в конец списка.
     * @param value Значение, которое нужно добавить в список.
     * @details Если список пуст, создается новый узел и он становится началом и концом списка. Иначе создается новый узел,
     *          устанавливаются связи между узлами, и новый узел становится концом списка.
     */
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

    /**
     * @brief Добавляет элемент в начало списка.
     * @param value Значение, которое нужно добавить в список.
     * @details Если список пуст, создается новый узел и он становится началом и концом списка. Иначе создается новый узел,
     *          устанавливаются связи между узлами, и новый узел становится началом списка.
     */
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

    /**
     * @brief Вставляет элемент на заданную позицию в списке.
     * @param value Значение, которое нужно вставить в список.
     * @param position Позиция, на которую нужно вставить элемент.
     * @details Если позиция меньше 0, выводится сообщение об ошибке. Если позиция равна 0, вызывается метод insertAtBeginning().
     *          В противном случае создается новый узел, устанавливаются связи между узлами, и новый узел вставляется на указанную позицию.
     */
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

    /**
     * @brief Удаляет элемент с начала списка.
     * @details Если список пуст, выводится сообщение об ошибке. Если в списке есть только один элемент, он удаляется, и указатели
     *          на начало и конец списка становятся nullptr. В противном случае, устанавливаются новые связи между узлами,
     *          и первый узел удаляется.
     */
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

    /**
     * @brief Удаляет элемент из позиции списка с заданным номером.
     * @param position Позиция элемента, который нужно удалить.
     * @details Если позиция меньше 0 или больше размера списка, выводится сообщение об ошибке. Если позиция равна 0,
     *          вызывается метод removeAtBeginning(). В противном случае, устанавливаются связи между соседними узлами,
     *          и удаляемый узел освобождается.
     */
    void removeAtPosition(int position) {
        if (position < 0 || isEmpty()) {
            std::cout << "Невозможная позиция или список пуст" << std::endl;
            return;
        }
        if (position == 0) {
            removeAtBeginning();
        } else {
            Node* current = head;
            int count = 0;
            while (current && count < position) {
                current = current->next;
                count++;
            }
            if (count < position || !current) {
                std::cout << "Вы вышли за список" << std::endl;
                return;
            }
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
        }
    }

    /**
     * @brief Поиск элемента в списке с заданным значением и получение его номера.
     * @param value Значение, которое нужно найти в списке.
     * @return Номер (индекс) найденного элемента. Если элемент не найден, возвращает -1.
     */
    int findElement(char value) {
        if (isEmpty()) {
            std::cout << "Список пуст" << std::endl;
            return -1;
        }

        Node* current = head;
        int index = 0;
        do {
            if (current->value == value) {
                return index;
            }
            current = current->next;
            index++;
        } while (current != head);

        std::cout << "Элемент не найден" << std::endl;
        return -1;
    }

    /**
     * @brief Выводит список на экран.
     * @details Если список пуст, выводится сообщение о пустом списке. Иначе происходит циклический вывод значений узлов списка.
     */
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
};

int main() {
    CircularDoublyLinkedList myList;
    std::cout << "Список: ";
    myList.printList();
    myList.append('A');
    myList.append('B');
    myList.append('C');
    std::cout << "Список после добавления элементов: \n";
    myList.printList();
    std::cout<<"Введите значение для добавление в начало списка \n";
    char startValue;
    std::cin>>startValue;
    myList.insertAtBeginning(startValue);
    //myList.insertAtPosition('X', 2);
    // Вывод списка
    std::cout << "Список после вставок:" << std::endl;
    myList.printList();

    // Поиск элемента
    char searchValue;
    std::cout<<"Введите ключ для поиска \n";
    std::cin>>searchValue;
    std::cout<<"Поиск элемента : "<<searchValue<<'\n';
    int foundIndex = myList.findElement(searchValue);
    if (foundIndex != -1) {
        std::cout << "Элемент '" << searchValue << "' найден в индексе: " << foundIndex << std::endl;
    }
    else{
        std::cout<<"Элемент: "<<searchValue<<" не найден"<<'\n';
    }

    // Удаление элемента по позиции
    int removePosition;
    std::cout<<"Введите индекс для удаления \n";
    std::cin >> removePosition;
    myList.removeAtPosition(removePosition);

    // Вывод списка после удаления
    std::cout << "Список после удаления с позиции "<<removePosition<<": " << std::endl;
    myList.printList();

    return 0;
}
