#include <iostream>
#include <queue>
#include <cstdlib>
#include <algorithm> // Добавлен заголовок для std::max

using namespace std;


template <typename T>
struct TreeNode {
    T key;             // Ключ узла
    TreeNode* left;    // Левое поддерево
    TreeNode* right;   // Правое поддерево
    int height;        // Высота узла
    int balance;       // Баланс узла

    TreeNode(T value) : key(value), left(nullptr), right(nullptr), height(1), balance(0) {}
};

// Класс бинарного дерева поиска
template <typename T>
class BinarySearchTree 
{
private:
    TreeNode<T>* root;

    // Рекурсивная вставка
    void insertRecursive(TreeNode<T>*& node, T value);
    // Рекурсивный поиск
    TreeNode<T>* findRecursive(TreeNode<T>* node, T value);
    // Рекурсивное удаление
    TreeNode<T>* deleteRecursive(TreeNode<T>*& node, T value);
    // Рекурсивный вывод в порядке возрастания
    void inorderTraversalRecursive(TreeNode<T>* node);
    // Рекурсивный вывод структуры дерева
    void printTreeRecursive(TreeNode<T>* node, int depth);
    // Рекурсивное получение высоты
    int getHeightRecursive(TreeNode<T>* node);
    // Рекурсивное подсчет количества узлов
    int countNodesRecursive(TreeNode<T>* node);
    // Рекурсивное подсчет количества узлов на каждом уровне
    void countNodesPerLevel(TreeNode<T>* node, vector<int>& levelCount, int level);

    // Функции для балансировки дерева
    int balanceFactor(TreeNode<T>* node);
    void fixHeight(TreeNode<T>* node);
    TreeNode<T>* rotateRight(TreeNode<T>* p);
    TreeNode<T>* rotateLeft(TreeNode<T>* q);
    TreeNode<T>* balance(TreeNode<T>* p);

public:
    BinarySearchTree() : root(nullptr) {}

    // Вставка элемента в дерево
    void insert(T value);
    // Поиск элемента в дереве
    TreeNode<T>* find(T value);
    // Удаление элемента из дерева
    void remove(T value);
    // Вывод в порядке возрастания
    void inorderTraversal();
    // Вывод структуры дерева
    void printTree();
    // Получение высоты дерева
    int getHeight();
    // Подсчет количества узлов в дереве
    int countNodes();
    // Подсчет количества узлов на каждом уровне
    void countNodesPerLevel(vector<int>& levelCount);
};

template <typename T>
void BinarySearchTree<T>::insertRecursive(TreeNode<T>*& node, T value) 
{
    if (node == nullptr) 
    {
        node = new TreeNode<T>(value);
    }
    else 
    {
        if (value < node->key) 
        {
            insertRecursive(node->left, value);
        }
        else if (value > node->key)
        {
            insertRecursive(node->right, value);
        }
    }
    node = balance(node);
}

template <typename T>
void BinarySearchTree<T>::insert(T value) 
{
    insertRecursive(root, value);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::findRecursive(TreeNode<T>* node, T value) 
{
    if (node == nullptr || node->key == value) 
    {
        return node;
    }

    if (value < node->key) 
    {
        return findRecursive(node->left, value);
    }
    else 
    {
        return findRecursive(node->right, value);
    }
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::find(T value) 
{
    return findRecursive(root, value);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::deleteRecursive(TreeNode<T>*& node, T value) 
{
    if (node == nullptr) 
    {
        return node;
    }

    if (value < node->key) 
    {
        node->left = deleteRecursive(node->left, value);
    }
    else if (value > node->key) 
    {
        node->right = deleteRecursive(node->right, value);
    }
    else 
    {
        if (node->left == nullptr) 
        {
            TreeNode<T>* temp = node->right;
            delete node;
            return temp;
        }
        else if (node->right == nullptr) 
        {
            TreeNode<T>* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode<T>* temp = node->right;
        while (temp->left != nullptr) 
        {
            temp = temp->left;
        }

        node->key = temp->key;
        node->right = deleteRecursive(node->right, temp->key);
    }

    return balance(node);
}

template <typename T>
void BinarySearchTree<T>::remove(T value) 
{
    root = deleteRecursive(root, value);
}

template <typename T>
void BinarySearchTree<T>::inorderTraversalRecursive(TreeNode<T>* node) 
{
    if (node != nullptr) 
    {
        inorderTraversalRecursive(node->left);
        cout << node->key << " ";
        inorderTraversalRecursive(node->right);
    }
}

template <typename T>
void BinarySearchTree<T>::inorderTraversal() 
{
    inorderTraversalRecursive(root);
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::printTreeRecursive(TreeNode<T>* node, int depth) 
{
    if (node != nullptr) 
    {
        printTreeRecursive(node->right, depth + 1);

        for (int i = 0; i < depth; ++i) 
        {
            cout << "   ";
        }
        cout << node->key << endl;

        printTreeRecursive(node->left, depth + 1);
    }
}

template <typename T>
void BinarySearchTree<T>::printTree() 
{
    printTreeRecursive(root, 0);
}

template <typename T>
int BinarySearchTree<T>::getHeightRecursive(TreeNode<T>* node) 
{
    if (node == nullptr) 
    {
        return 0;
    }

    int leftHeight = getHeightRecursive(node->left);
    int rightHeight = getHeightRecursive(node->right);

    return max(leftHeight, rightHeight) + 1;
}

template <typename T>
int BinarySearchTree<T>::getHeight() 
{
    return getHeightRecursive(root);
}

template <typename T>
int BinarySearchTree<T>::countNodesRecursive(TreeNode<T>* node) 
{
    if (node == nullptr) 
    {
        return 0;
    }

    return countNodesRecursive(node->left) + countNodesRecursive(node->right) + 1;
}

template <typename T>
int BinarySearchTree<T>::countNodes() 
{
    return countNodesRecursive(root);
}

template <typename T>
void BinarySearchTree<T>::countNodesPerLevel(TreeNode<T>* node, vector<int>& levelCount, int level) 
{
    if (node != nullptr) 
    {
        levelCount[level]++;
        countNodesPerLevel(node->left, levelCount, level + 1);
        countNodesPerLevel(node->right, levelCount, level + 1);
    }
}

template <typename T>
void BinarySearchTree<T>::countNodesPerLevel(vector<int>& levelCount) 
{
    countNodesPerLevel(root, levelCount, 0);
}

template <typename T>
int BinarySearchTree<T>::balanceFactor(TreeNode<T>* node) 
{
    return (node != nullptr) ? getHeightRecursive(node->right) - getHeightRecursive(node->left) : 0;
}

template <typename T>
void BinarySearchTree<T>::fixHeight(TreeNode<T>* node) 
{
    int leftHeight = getHeightRecursive(node->left);
    int rightHeight = getHeightRecursive(node->right);
    node->height = max(leftHeight, rightHeight) + 1;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::rotateRight(TreeNode<T>* p) 
{
    TreeNode<T>* q = p->left;
    p->left = q->right;
    q->right = p;
    fixHeight(p);
    fixHeight(q);
    return q;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::rotateLeft(TreeNode<T>* q) 
{
    TreeNode<T>* p = q->right;
    q->right = p->left;
    p->left = q;
    fixHeight(q);
    fixHeight(p);
    return p;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::balance(TreeNode<T>* p) 
{
    fixHeight(p);
    if (balanceFactor(p) == 2) 
    {
        if (balanceFactor(p->right) < 0)
        {
            p->right = rotateRight(p->right);
        }
        return rotateLeft(p);
    }
    if (balanceFactor(p) == -2) 
    {
        if (balanceFactor(p->left) > 0) 
        {
            p->left = rotateLeft(p->left);
        }
        return rotateRight(p);
    }
    return p;
}
// Функция для вывода меню и взаимодействия с пользователем
void menu(BinarySearchTree<char>& charBST) 
{
    int choice;
    do {
        cout << "\nВыберите операцию:" << endl;
        cout << "1. Вставить элемент" << endl;
        cout << "2. Найти элемент" << endl;
        cout << "3. Удалить элемент" << endl;
        cout << "4. Вывести в порядке возрастания" << endl;
        cout << "5. Вывести структуру дерева" << endl;
        cout << "6. Получить высоту дерева" << endl;
        cout << "7. Получить количество узлов в дереве" << endl;
        cout << "8. Получить количество узлов на каждом уровне" << endl;
        cout << "0. Выйти" << endl;
        cout << "Введите номер операции: ";

        cin >> choice;

        switch (choice) 
        {
            case 1: 
            {
                char value;
                cout << "Введите элемент для вставки: ";
                cin >> value;
                charBST.insert(value);
                break;
            }
            case 2: 
            {
                char value;
                cout << "Введите элемент для поиска: ";
                cin >> value;
                TreeNode<char>* result = charBST.find(value);
                if (result != nullptr) 
                {
                    cout << "Элемент найден." << endl;
                }
                else 
                {
                    cout << "Элемент не найден." << endl;
                }
                break;
            }
            case 3: 
            {
                char value;
                cout << "Введите элемент для удаления: ";
                cin >> value;
                charBST.remove(value);
                break;
            }
            case 4: 
            {
                charBST.inorderTraversal();
                break;
            }
            case 5: 
            {
                charBST.printTree();
                break;
            }
            case 6: 
            {
                cout << "Высота дерева: " << charBST.getHeight() << endl;
                break;
            }
            case 7: 
            {
                cout << "Количество узлов в дереве: " << charBST.countNodes() << endl;
                break;
            }
            case 8: 
            {
                vector<int> levelCount(charBST.getHeight(), 0);
                charBST.countNodesPerLevel(levelCount);

                cout << "Количество узлов на каждом уровне: ";
                for (int i = 0; i < levelCount.size(); ++i) 
                {
                    cout << levelCount[i] << " ";
                }
                cout << endl;
                break;
            }
            case 0:
                cout << "Завершение программы." << endl;
                break;
            default:
                cout << "Некорректный выбор. Пожалуйста, попробуйте снова." << endl;
        }
    }while (choice != 0);
}

int main() 
{
    system("chcp 1251");
    BinarySearchTree<char> charBST;

    charBST.insert('А');
    charBST.insert('В');
    charBST.insert('Б');
    charBST.insert('Г');
    charBST.insert('Д');
    charBST.insert('Е');
    charBST.insert('Ж');
    charBST.insert('Я');
    charBST.insert('К');
    charBST.insert('У');
    charBST.insert('Ц');
    charBST.insert('Й');
    charBST.insert('Н');
    charBST.insert('Ш');
    menu(charBST);
}