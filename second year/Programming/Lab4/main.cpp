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
    void clear() 
    {
    while (!isEmpty()) 
    {
        removeAtBeginning();
    }
    }
};

/**
 * @brief Функция для взаимодействия с пользователем через меню.
 * @param myList Ссылка на объект CircularDoublyLinkedList для выполнения операций.
 */
void menu(CircularDoublyLinkedList& myList) {
    int choice;
    do {
        // Вывод меню
        std::cout << "\nВыберите операцию:" << std::endl;
        std::cout << "1. Добавить элемент в конец списка" << std::endl;
        std::cout << "2. Добавить элемент в начало списка" << std::endl;
        std::cout << "3. Вставить элемент на заданную позицию" << std::endl;
        std::cout << "4. Удалить элемент с начала списка" << std::endl;
        std::cout << "5. Удалить элемент по заданной позиции" << std::endl;
        std::cout << "6. Найти элемент в списке" << std::endl;
        std::cout << "7. Вывести список" << std::endl;
        std::cout << "8. Очистить список" << std::endl;
        std::cout << "0. Выйти из программы" << std::endl;
        std::cout << "Введите номер операции: ";
        
        // Ввод выбора пользователя
        std::cin >> choice;

        switch (choice) {
            case 1: {
                char value;
                std::cout << "Введите значение для добавления в конец списка: ";
                std::cin >> value;
                myList.append(value);
                break;
            }
            case 2: {
                char value;
                std::cout << "Введите значение для добавления в начало списка: ";
                std::cin >> value;
                myList.insertAtBeginning(value);
                break;
            }
            case 3: {
                char value;
                int position;
                std::cout << "Введите значение для вставки: ";
                std::cin >> value;
                std::cout << "Введите позицию для вставки: ";
                std::cin >> position;
                myList.insertAtPosition(value, position);
                break;
            }
            case 4:
                myList.removeAtBeginning();
                break;
            case 5: {
                int position;
                std::cout << "Введите позицию для удаления: ";
                std::cin >> position;
                myList.removeAtPosition(position);
                break;
            }
            case 6: {
                char searchValue;
                std::cout << "Введите значение для поиска: ";
                std::cin >> searchValue;
                int foundIndex = myList.findElement(searchValue);
                if (foundIndex != -1) {
                    std::cout << "Элемент '" << searchValue << "' найден в индексе: " << foundIndex << std::endl;
                } else {
                    std::cout << "Элемент: " << searchValue << " не найден" << std::endl;
                }
                break;
            }
            case 7:
                std::cout << "Список:" << std::endl;
                myList.printList();
                break;
            case 8:
                myList.clear();
                std::cout << "Список очищен." << std::endl;
                break;
            case 0:
                std::cout << "Выход из программы." << std::endl;
                break;
            default:
                std::cout << "Неверный выбор. Попробуйте еще раз." << std::endl;
        }
    } while (choice != 0);
}

int main() {
    setlocale(LC_ALL, "");
    CircularDoublyLinkedList myList;
    for (char ch = 'A'; ch <= 'T'; ++ch) {
        myList.append(ch);
    }
    // Вызов функции меню для взаимодействия с пользователем
    menu(myList);

    return 0;
}

