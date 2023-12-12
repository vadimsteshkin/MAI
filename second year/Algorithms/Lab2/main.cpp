#include <iostream>
#include <queue>

using namespace std;

// Структура узла дерева
template <typename T>
struct TreeNode {
    T key;
    TreeNode* left;
    TreeNode* right;

    TreeNode(T value) : key(value), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева поиска
template <typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    // Вспомогательные функции для рекурсивных операций
    void insertRecursive(TreeNode<T>*& node, T value);
    TreeNode<T>* findRecursive(TreeNode<T>* node, T value);
    TreeNode<T>* deleteRecursive(TreeNode<T>*& node, T value);
    void inorderTraversalRecursive(TreeNode<T>* node);
    void printTreeRecursive(TreeNode<T>* node, int depth);
    int getHeightRecursive(TreeNode<T>* node);
    int countNodesRecursive(TreeNode<T>* node);
    void countNodesPerLevel(TreeNode<T>* node, vector<int>& levelCount, int level);

public:
    BinarySearchTree() : root(nullptr) {}

    // Основные функции
    void insert(T value);
    TreeNode<T>* find(T value);
    void remove(T value);
    void inorderTraversal();
    void printTree();
    int getHeight();
    int countNodes();

    // Дополнительная функция для подсчета элементов на каждом уровне
    void countNodesPerLevel(vector<int>& levelCount);
};

// Реализация основных функций
template <typename T>
void BinarySearchTree<T>::insertRecursive(TreeNode<T>*& node, T value) {
    if (node == nullptr) {
        node = new TreeNode<T>(value);
    } else {
        if (value < node->key) {
            insertRecursive(node->left, value);
        } else if (value > node->key) {
            insertRecursive(node->right, value);
        }
    }
}

template <typename T>
void BinarySearchTree<T>::insert(T value) {
    insertRecursive(root, value);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::findRecursive(TreeNode<T>* node, T value) {
    if (node == nullptr || node->key == value) {
        return node;
    }

    if (value < node->key) {
        return findRecursive(node->left, value);
    } else {
        return findRecursive(node->right, value);
    }
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::find(T value) {
    return findRecursive(root, value);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::deleteRecursive(TreeNode<T>*& node, T value) {
    if (node == nullptr) {
        return node;
    }

    if (value < node->key) {
        node->left = deleteRecursive(node->left, value);
    } else if (value > node->key) {
        node->right = deleteRecursive(node->right, value);
    } else {
        if (node->left == nullptr) {
            TreeNode<T>* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            TreeNode<T>* temp = node->left;
            delete node;
            return temp;
        }

        TreeNode<T>* temp = node->right;
        while (temp->left != nullptr) {
            temp = temp->left;
        }

        node->key = temp->key;
        node->right = deleteRecursive(node->right, temp->key);
    }

    return node;
}

template <typename T>
void BinarySearchTree<T>::remove(T value) {
    root = deleteRecursive(root, value);
}

template <typename T>
void BinarySearchTree<T>::inorderTraversalRecursive(TreeNode<T>* node) {
    if (node != nullptr) {
        inorderTraversalRecursive(node->left);
        cout << node->key << " ";
        inorderTraversalRecursive(node->right);
    }
}

template <typename T>
void BinarySearchTree<T>::inorderTraversal() {
    inorderTraversalRecursive(root);
    cout << endl;
}

template <typename T>
void BinarySearchTree<T>::printTreeRecursive(TreeNode<T>* node, int depth) {
    if (node != nullptr) {
        printTreeRecursive(node->right, depth + 1);

        for (int i = 0; i < depth; ++i) {
            cout << "   ";
        }
        cout << node->key << endl;

        printTreeRecursive(node->left, depth + 1);
    }
}

template <typename T>
void BinarySearchTree<T>::printTree() {
    printTreeRecursive(root, 0);
}

template <typename T>
int BinarySearchTree<T>::getHeightRecursive(TreeNode<T>* node) {
    if (node == nullptr) {
        return 0;
    }

    int leftHeight = getHeightRecursive(node->left);
    int rightHeight = getHeightRecursive(node->right);

    return max(leftHeight, rightHeight) + 1;
}

template <typename T>
int BinarySearchTree<T>::getHeight() {
    return getHeightRecursive(root);
}

template <typename T>
int BinarySearchTree<T>::countNodesRecursive(TreeNode<T>* node) {
    if (node == nullptr) {
        return 0;
    }

    return countNodesRecursive(node->left) + countNodesRecursive(node->right) + 1;
}

template <typename T>
int BinarySearchTree<T>::countNodes() {
    return countNodesRecursive(root);
}

template <typename T>
void BinarySearchTree<T>::countNodesPerLevel(TreeNode<T>* node, vector<int>& levelCount, int level) {
    if (node != nullptr) {
        levelCount[level]++;
        countNodesPerLevel(node->left, levelCount, level + 1);
        countNodesPerLevel(node->right, levelCount, level + 1);
    }
}

template <typename T>
void BinarySearchTree<T>::countNodesPerLevel(vector<int>& levelCount) {
    countNodesPerLevel(root, levelCount, 0);
}

int main() {
    setlocale(0, "");
    BinarySearchTree<char> charBST;

    // Пример использования
    charBST.insert('г');
    charBST.insert('в');
    charBST.insert('е');
    charBST.insert('б');
    charBST.insert('д');
    charBST.insert('а');
    charBST.insert('ж');

    cout << "Обход в порядке возрастания: ";
    charBST.inorderTraversal();

    cout << "Структура дерева:" << endl;
    charBST.printTree();

    cout << "Высота дерева: " << charBST.getHeight() << endl;
    cout << "Количество узлов в дереве: " << charBST.countNodes() << endl;

    vector<int> levelCount(charBST.getHeight(), 0);
    charBST.countNodesPerLevel(levelCount);

    cout << "Количество узлов на каждом уровне: ";
    for (int i = 0; i < levelCount.size(); ++i) {
        cout << levelCount[i] << " ";
    }

    return 0;
}
