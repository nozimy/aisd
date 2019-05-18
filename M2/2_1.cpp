
/**
 * Дано число N < 106 и последовательность целых чисел из [-231..231]
 * длиной N. Требуется построить бинарное дерево, заданное наивным
 * порядком вставки. Т.е., при добавлении очередного числа K в дерево
 * с корнем root, если root→Key ≤ K, то узел K добавляется в правое
 * поддерево root; иначе в левое поддерево root. Рекурсия запрещена.
 *
 * 2_1. Выведите элементы в порядке in-order (слева направо).
 */

#include <iostream>

using namespace std;

template <class T>
class Stack {
public:
    Stack(): buffer(8), elements(0) { array = new T[buffer]; };
    Stack(const Stack&) = delete;
    Stack(Stack&&) = delete;
    ~Stack() { delete []array; };

    Stack& operator=(const Stack&) = delete;
    Stack& operator=(Stack&&) = delete;

    void push(T data) {
        if (++elements < buffer) reAlloc(buffer *= 2);
        array[elements - 1] = data;
    }

    T pop() {
        if(buffer >= 16 && elements == (buffer / 4)) reAlloc(buffer /= 2);
        return array[--elements];
    }

    bool empty() { return elements == 0; }
    int size() { return elements; }

private:
    int buffer;
    int elements;
    T* array;

    void reAlloc(int newBuffer) {
        auto* temp = new T[newBuffer];

        for (int i=0; i < elements; i++)
            temp[i] = array[i];

        delete []array;
        array = temp;
    }
};

struct BinaryNode {
    BinaryNode(): left(nullptr), right(nullptr) {}
    int Data;
    BinaryNode* left;
    BinaryNode* right;
};

void visit(BinaryNode* node){
    if (node != nullptr){
        cout << node->Data << ' ';
    }
}

template <class TPtr>
void TraverseDFSInOrder(TPtr root){ // TODO: рекурсия запрещена
//    if (node == nullptr){
//        return;
//    }
//    TraverseDFSInOrder(node->left);
//    visit(node);
//    TraverseDFSInOrder(node->right);

    Stack<TPtr> stack;

    while (root != nullptr || !stack.empty()){

        if (!stack.empty()){

            root = stack.pop();
            visit(root);

            if (root->right != nullptr) root = root->right;
            else root = nullptr;
        }

        while (root != nullptr){
            stack.push(root);
            root = root->left;
        }
    }
}

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

void DeleteBinaryTree(BinaryNode* node){
    if (node == nullptr){
        return;
    }
    DeleteBinaryTree(node->left);
    DeleteBinaryTree(node->right);
    delete node;
}

int main(){
    int N;
    int K;
    BinaryNode* root = nullptr;
    cin >> N;

    for (int i = 0; i < N; ++i){
        cin >> K;
        NaiveInsert(&root, K);
    }

    TraverseDFSInOrder(root);

    DeleteBinaryTree(root);

    return 0;
}