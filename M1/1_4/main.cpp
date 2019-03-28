/**
 * Юнусов Нозимжон, АПО-13
 *
 * В круг выстроено N человек, пронумерованных числами от 1 до N.
 * Будем исключать каждого k-ого до тех пор, пока не уцелеет только один человек.
 * Например, если N=10, k=3, то сначала умрет 3-й, потом 6-й, затем 9-й, затем 2-й,
 * затем 7-й, потом 1-й, потом 8-й, за ним - 5-й, и потом 10-й. Таким образом, уцелеет 4-й.
 *
 * Необходимо определить номер уцелевшего.
 *
 * N, k ≤ 10000.
 */

/**
 * Описание решения 1
 *
 * Используются СД Связные списки
 * Создаются N узлов, зымыкаются начало с концом
 * поочередно удаляются каждые k элементов до тех пор, пока не останется 1 элемент
 */

/**
 * Замечание:
 *      можно было использовать односвязный список
 */

#include <iostream>
#include <assert.h>

using namespace std;

struct CNode {
    int Data;
    CNode* Next;
    CNode* Prev;
    CNode() : Data( 0 ), Next( nullptr ), Prev( nullptr ) {}
};

CNode* InsertAfter( CNode* node, int a );
void DeleteAt( CNode* node );
int linkedListFindSafePosition(int n, int k);

int findSafePositionFaster(int N, int k);
int findSafePosition(int N, int k);

int main() {
    int n, k;
    cin >> n >> k;

    cout << linkedListFindSafePosition(n, k) << endl;

    return 0;
}

int linkedListFindSafePosition(int n, int k){
    CNode *first = nullptr;
    CNode *current = nullptr;

    for (int i = 0; i < n; i++) {
        if (current==nullptr && first ==nullptr) {
            first = new CNode();
            first->Data = i+1;
            current=first;
        } else {
            current = InsertAfter(current, i+1);
        }
    }
    current->Next=first;
    first->Prev=current;

    CNode * tmpPtr = nullptr;

    current=first;
    while(n > 1){
        tmpPtr=current;
        for(int i=1; i<k; i++){
            tmpPtr=tmpPtr->Next;
        }
        current=tmpPtr->Next;
        DeleteAt(tmpPtr);
        n--;
    }
    int safetyPosition = current->Data;
    DeleteAt(current);
    return safetyPosition;
}

CNode* InsertAfter( CNode* node, int a )
{
    assert( node != nullptr );
    // Создаем новый элемент.
    CNode* newNode = new CNode();
    newNode->Data = a;
    newNode->Next = node->Next;
    newNode->Prev = node;
    // Обновляем Prev следующего элемента, если он есть.
    if( node->Next != nullptr ) {
        node->Next->Prev = newNode;
    }
    // Обновляем Next текущего элемента.
    node->Next = newNode;
    return newNode;
}

void DeleteAt( CNode* node )
{
    assert( node != nullptr );
    if( node->Prev != nullptr ) {
        node->Prev->Next = node->Next;
    }
    // Обновляем Prev следующего элемента, если он есть.
    if( node->Next != nullptr ) {
        node->Next->Prev = node->Prev;
    }
    delete node;
}


/**
 * Описание решения 2
 * Используется принципы динамического программирования:
 *  - задача делится на мелкие кусочки
 *  - каждое следующее вычисление использует результат предыдущего вычисления
 *
 */

int findSafePosition(int N, int k){
    if (N == 1){
        return 1;
    } else {
        return ((findSafePosition(N-1, k) + k - 1) % N) + 1;
    }
}

int findSafePositionFaster(int N, int k){
    if (N == 1) {
        return 0;
    } else if(N > 1 && N < k){
        return (findSafePositionFaster(N-1, k) + k) % N;
    } else if (k <= N) {
        int N1 = N - (int)((float)N/ (float)k) ;
        int res = findSafePositionFaster(N1, k) - (N % k);
        if (res < 0) res += N;
        else res+=res/(k-1);
        return res;
    }
}
