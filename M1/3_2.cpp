/**
 *  yunusov.nozim
 *
 * Реализовать дек с динамическим зацикленным буфером.
 * Обрабатывать команды push * и pop *.
 *
 * Формат ввода
 * В первой строке количество команд n. n ≤ 1000000.
 *
 * Каждая команда задаётся как 2 целых числа: a b.
 * a = 1 - push front
 * a = 2 - pop front
 * a = 3 - push back
 * a = 4 - pop back
 *
 * Если дана команда pop *, то число b - ожидаемое значение.
 * Если команда pop * вызвана для пустой структуры данных, то ожидается “-1”.
 *
 * Пример 1
 * 3
 * 1 44
 * 3 50
 * 2 44
 */

#include <iostream>
#include <assert.h>
#include <cstring>

using namespace std;

//todo: включи шаблоны
class MyDeque {
public:
    explicit MyDeque();
    ~MyDeque();

    void PushFront(int newElement);
    void PushBack(int newElement);
    int PopFront();
    int PopBack();

    void print_deque() const {
        std::cout << "front: " << front << "; back: " << back << std::endl;
        std::cout << "length: " << length << std::endl;
        for (size_t i = 0; i < bufferSize; ++i) {
            std::cout << "|" << buffer[i];
        }
        std::cout << std::endl;
    }

private:
    int* buffer;
    size_t bufferSize;
    size_t front;  // first element index
    size_t back;   // last element index
    const size_t initialBufferSize = 2;
    size_t length;

    bool IsEmpty() const {return length == 0; }
    void copyToNewBuffer(int *newBuff);
    void increaseBuffer();
    void initBuffer();
};

int execCommand(MyDeque* deck, int command, int operand);

int main() {
    const string  YES = "YES";
    const string  NO = "NO";
    int n;
    int command = 0;
    int operand = 0;
    string result = YES;
    int commandResult = -1;

    auto * deck = new MyDeque();

    cin >> n;
    for(int i = 0; i < n; ++i){
        cin >> command >> operand;
        commandResult = execCommand(deck, command, operand);
        if ((command == 2 || command == 4) && operand != commandResult) {
            result = NO;
        }
    }

    cout << result << endl;
}

int execCommand(MyDeque* deck, int command, int operand){
    int popResult = -1;
    switch (command){
        case 1:
            deck->PushFront(operand);
            break;
        case 2:
            popResult = deck->PopFront();
            break;
        case 3:
            deck->PushBack(operand);
            break;
        case 4:
            popResult = deck->PopBack();
            break;
        default:break;
    }
    return popResult;
}

MyDeque::MyDeque() :
        buffer(nullptr),
        bufferSize (0),
        front(0),
        back(0),
        length(0) {}

MyDeque::~MyDeque() {
    delete[] buffer;
}

void MyDeque::PushBack(int newElement) {
    if (bufferSize == 0) {
        initBuffer();
    }

    if (front == back) {
        front = bufferSize - 1;
    }

    size_t newBack = (back + 1) % bufferSize;

    if (newBack == front) {
        increaseBuffer();
        newBack = (back + 1) % bufferSize;
    }

    buffer[back] = newElement;
    length++;
    back = newBack;
}

int MyDeque::PopFront() {
    if (IsEmpty()) return -1;

    front = (front + 1) % bufferSize;
    int result = buffer[front];
    buffer[front] = -1;
    length--;
    return result;
}

void MyDeque::PushFront(int newElement) {

    if (bufferSize == 0) {
        initBuffer();
    }

    if (front == back) {
        back += 1;
    }

    size_t newFront = ((front - 1) + bufferSize) % bufferSize;

    if (newFront == back) {
        increaseBuffer();
        newFront = ((front - 1) + bufferSize) % bufferSize;
    }

//    front = ((front - 1) + bufferSize) % bufferSize; // from array.length-1 to 0, if front == 0 then front = array.length-1
    buffer[front] = newElement;
    length++;
    front = newFront;
}

int MyDeque::PopBack() {
    if (IsEmpty()) return -1;

    back = ((back - 1) + bufferSize) % bufferSize;
    int result = buffer[back];
    buffer[back] = -1;
    length--;
    return result;
}

void MyDeque::copyToNewBuffer(int *newBuff){
    if (front < back) {
        std::copy(buffer + front, buffer + back, newBuff + front);
    } else {
        std::copy(buffer + front, buffer + bufferSize, newBuff + front);
        std::copy(buffer, buffer + back, newBuff + bufferSize);
    }
}

void MyDeque::increaseBuffer() {
    size_t newSize = bufferSize * initialBufferSize;
    int* newBuffer = new int[newSize];

    copyToNewBuffer(newBuffer);

    if (front > back) {
        back = bufferSize + back;
    }

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newSize;
}

void MyDeque::initBuffer() {
    bufferSize = initialBufferSize;
    buffer = new int[bufferSize];
}