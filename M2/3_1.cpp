
/**
 * Дано число N < 10^6 и последовательность пар целых чисел из [-231..231] длиной N.
 * Построить декартово дерево из N узлов, характеризующихся парами чисел {Xi, Yi}.
 * Каждая пара чисел {Xi, Yi} определяет ключ Xi и приоритет Yi в декартовом дереве.
 * Добавление узла в декартово дерево выполняйте второй версией алгоритма, рассказанного на лекции:
 *      При добавлении узла (x, y) выполняйте спуск по ключу до узла P
 *      с меньшим приоритетом. Затем разбейте найденное поддерево по
 *      ключу x так, чтобы в первом поддереве все ключи меньше x, а во
 *      втором больше или равны x. Получившиеся два дерева сделайте дочерними
 *      для нового узла (x, y). Новый узел вставьте на место узла P.
 *
 * Построить также наивное дерево поиска по ключам Xi методом из задачи 2.
 *
 * 3_1. Вычислить разницу глубин наивного дерева поиска и декартового дерева. Разница может быть отрицательна.
 */

#include <iostream>
#include <queue>

using namespace std;

struct TreapNode {
    TreapNode(): left(nullptr), right(nullptr){}
    TreapNode(long x, long y): key(x), priority(y), left(nullptr), right(nullptr){}
    long key;
    long priority;
    TreapNode* left;
    TreapNode* right;
};

void Split(TreapNode* currentNode, long key, TreapNode*& left, TreapNode*& right){
    if (currentNode == nullptr){
        left = nullptr;
        right = nullptr;
    } else if (currentNode->key <= key) {
        Split(currentNode->right, key, currentNode->right, right);
        left = currentNode;
    } else {
        Split(currentNode->left, key, left, currentNode->left);
        right = currentNode;
    }
}

void InsertTreapNode(TreapNode*& node, long key, long priority){
    if (node == nullptr) {
        node = new TreapNode(key, priority);
        return;
    }
    if (node->priority < priority) {
        auto newNode = new TreapNode(key, priority);
        Split(node, key, newNode->left, newNode->right);
        node = newNode;
        return;
    }
    if (node->key > key) {
        InsertTreapNode(node->left, key, priority);
    } else {
        InsertTreapNode(node->right, key, priority);
    }
}

struct BinaryNode {
    BinaryNode(): left(nullptr), right(nullptr) {}
    int Data;
    BinaryNode* left;
    BinaryNode* right;
};

void NaiveInsert(BinaryNode** node, int K){
    BinaryNode** tmpNode = node;

    while (*tmpNode != nullptr){
        if ((*tmpNode)->Data <= K){
            tmpNode = &(*tmpNode)->right;
        } else {
            tmpNode = &(*tmpNode)->left;
        }
    }

    auto* newNode = new BinaryNode();
    newNode->Data = K;
    *tmpNode = newNode;
}

template <typename T>
void DeleteTree(T* node){
    if (node == nullptr){
        return;
    }
    DeleteTree(node->left);
    DeleteTree(node->right);
    delete node;
}

template <typename T>
int getMaxDepth(T *t) // TODO: рекурсия запрещена
{
    if (t == nullptr)
        return 0;
    return max(getMaxDepth(t->left), getMaxDepth(t->right)) + 1;
}


// Итеративный метод подсчета глубины дерева
template <typename T>
int treeHeight(T *root)
{
    if (root == nullptr)
        return 0;

    queue<T *> q;

    q.push(root);
    int height = 0;

    while (1)
    {
        int nodeCount = q.size(); //  количество узлов в текущем уровне
        if (nodeCount == 0)
            return height;

        height++;

        while (nodeCount > 0)
        {
            T *node = q.front(); // Выводим из очереди все узлы текущего уровня
            q.pop();
            // ставим в очередь все узлы следующего уровня
            if (node->left != nullptr)
                q.push(node->left);
            if (node->right != nullptr)
                q.push(node->right);
            nodeCount--;
        }
    }
}

int main(){
    int N;
    long key, priority;
    TreapNode* root = nullptr;
    BinaryNode* rootBinary = nullptr;

    cin >> N;

    for (int i = 0; i < N; ++i){
        cin >> key >> priority;
        InsertTreapNode(root, key, priority);
        NaiveInsert(&rootBinary, key);
    }

//    cout << std::abs(getMaxDepth<TreapNode>(root) - getMaxDepth<BinaryNode>(rootBinary));
    cout << std::abs(treeHeight<TreapNode>(root) - treeHeight<BinaryNode>(rootBinary));

    DeleteTree<TreapNode>(root);
    DeleteTree<BinaryNode>(rootBinary);

    return 0;
}