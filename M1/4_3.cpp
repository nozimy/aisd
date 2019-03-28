/**
 * yunusov.nozim
 *
 * На вокзале есть некоторое количество тупиков, куда прибывают электрички.
 * Этот вокзал является их конечной станцией. Дано расписание движения
 * электричек, в котором для каждой электрички указано время ее прибытия,
 * а также время отправления в следующий рейс. Электрички в расписании
 * упорядочены по времени прибытия. Когда электричка прибывает, ее ставят
 * в свободный тупик с минимальным номером. При этом если электричка из
 * какого-то тупика отправилась в момент времени X, то электричку, которая
 * прибывает в момент времени X, в этот тупик ставить нельзя, а электричку,
 * прибывающую в момент X+1 — можно. В данный момент на вокзале достаточное
 * количество тупиков для работы по расписанию. Напишите программу, которая
 * по данному расписанию определяет, какое минимальное количество тупиков
 * требуется для работы вокзала.
 *
 * Формат ввода
 * Вначале вводится n - количество электричек в расписании.
 * Затем вводится n строк для каждой электрички, в строке - время
 * прибытия и время отправления. Время - натуральное число
 * от 0 до 1 000 000 000. Строки в расписании упорядочены
 * по времени прибытия.
 *
 * Формат вывода
 * Натуральное число - минимальное количеством тупиков.
 *
 */

/**
 * Описание решения
 *
 * В куче храним время отправления поездов
 * если время прибытия больше то удаляем корневой элемент в куче
 * размер кучи - количество необходимых тупиков
 */

#include <iostream>
#include <assert.h>

using namespace std;

template <typename T>
class Heap {
public:
    Heap<T>();
    ~Heap();

    // O(log n)
    void Insert(T element);

    // O(log n)
    T ExtractMin();

    // O(1)
    T PeakMin() const;
    size_t Size () const {return realSize;}

private:
    T* buffer;
    size_t bufferSize;
    size_t realSize;

    void buildHeap();
    void siftDown(int i);
    void siftUp(int i);
    void Grow();
    bool IsEmpty() const {return realSize == 0; }
    bool IsGrowRequired () const {return !IsEmpty() &&  realSize + 1 == bufferSize; }
};

int main () {
    int requiredRailwayTracks = 0;
    int lastArrival = 0;
    int n = 0;

    cin >> n;

    auto * heap = new Heap<int>();

    int arrival, departure;
    while((cin >> arrival >> departure)){
        if (arrival > lastArrival) {
            if (heap->Size() != 0 && arrival > heap->PeakMin()) {
                heap->ExtractMin();
            }
            heap->Insert(departure);
        } else {
            requiredRailwayTracks++;
        }

        lastArrival = arrival;
    }

    requiredRailwayTracks += heap->Size();

    cout << requiredRailwayTracks << endl;
}

template<typename T>
Heap<T>::Heap():
    buffer(nullptr), bufferSize(0), realSize(0) {
}

template<typename T>
void Heap<T>::Insert(T element) {
    if (bufferSize == 0) {
        buildHeap();
    }

    if (IsGrowRequired()) {
        Grow();
    }

    buffer[realSize++] = element;
    siftUp( realSize - 1 );
}

template<typename T>
void Heap<T>::buildHeap() {
    if (buffer == nullptr) {
        bufferSize = 2;
        buffer = new T[bufferSize];
    } else {
        for( int i = realSize / 2 - 1; i >= 0; --i ) {
            siftDown( i );
        }
    }
}

template <typename T>
void Heap<T>::siftDown(int i)
{
    int left = 2 * i + 1;
    int right = 2 * i + 2;
// Ищем меньшего сына, если такой есть.
    int largest = i;
    if( left < realSize && buffer[left] < buffer[i] )
        largest = left;
    if( right < realSize && buffer[right] < buffer[largest] )
        largest = right;
// Если меньший сын есть, то проталкиваем корень в него.
    if( largest != i ) {
        std::swap( buffer[i], buffer[largest] );
        siftDown( largest );
    }
}

template<typename T>
void Heap<T>::siftUp(int index) {
    while( index > 0 ) {
        int parent = ( index - 1 ) / 2;
        if( buffer[index] >= buffer[parent] )
            return;
        std::swap( buffer[index], buffer[parent] );
        index = parent;
    }
}


template<typename T>
T Heap<T>::ExtractMin() {
    assert( !realSize == 0 );
// Запоминаем значение корня.
    int result = buffer[0];
// Переносим последний элемент в корень.
    buffer[0] = buffer[realSize-1];
    realSize--;
// Вызываем SiftDown для корня.
    if( !realSize == 0 ) {
        siftDown( 0 );
    }
    return result;
}

template<typename T>
void Heap<T>::Grow() {
    size_t newSize = bufferSize * 2;
    int* newBuffer = new T[newSize];

    std::copy(buffer, buffer + realSize, newBuffer);

    delete[] buffer;
    buffer = newBuffer;
    bufferSize = newSize;
}

template<typename T>
Heap<T>::~Heap() {
    delete[] buffer;
}

template<typename T>
T Heap<T>::PeakMin() const {
    if (realSize == 0) {
        return -1;
    }
    return buffer[0];
}
