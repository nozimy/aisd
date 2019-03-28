/**
 * 7_3. Binary MSD для long long.
 * Дан массив неотрицательных целых 64-разрядных чисел.
 * Количество чисел не больше 10^6. Отсортировать массив
 * методом MSD по битам (бинарный QuickSort).
 */

/**
 * Описание решения
 *
 * Используется Binary Quicksort
 * 1. Сортируем по старшему биту.
 *    Используем Partition. Числа с нулевым битом в текущем разряде идут вначале,
 *    затем идут числа с единичным битом в разряде.
 * 2. Рекурсивно вызываем
 *    от левой части = 0xxxxxxx,
 *    от правой части = 1xxxxxxx.
 *
 * Время работы T(n,r) = O(rn),
 * доп. память M(n,r) = O(1),
 * где n – размер массива, r – количество разрядов.
 * Алгоритм локальный нестабильный
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;

bool isKthBitSet(long long num, int k);

class Comparator{
    const int bit;
public:
    explicit Comparator(int offset) : bit(offset) {}

    bool operator()(long long value) const
    {
        // знаковый бит
        if (bit == 63)
            // если число отрицательное, то true
            return value < 0;
        else
             //если бит равен 0, то true, иначе false
            return isKthBitSet(value, bit);
    }
};

int partition(long long *arr, int left, int right, Comparator isBitSet);
void msdSort(long long *arr, int lo, int hi, int msb = 63);


int main() {
    int n;
    cin >> n;
    auto *arr = new long long[n];
    for (int i=0; i < n; i++) {
        cin >> arr[i];
    }

    msdSort(arr, 0, n-1);

    for (int i=0; i < n; i++) {
        cout << arr[i] << ' ';
    }

    delete[] arr;
    return 0;
}

void msdSort(long long *arr, int lo, int hi, int msb){ // msb = most-significant bit
    if (lo < hi && msb >= 0)
    {
        int mid = partition(arr, lo, hi, Comparator(msb));
        msb--;
        msdSort(arr, lo, mid-1, msb);
        msdSort(arr, mid, hi, msb);
    }
}

int partition(long long *arr, int left, int right, Comparator isBitSet){
    int i = left, j = right;
    while (i <= j) {
        for(; i <= right && !(isBitSet(arr[i])); ++i) {}
        for(; j >= left && isBitSet(arr[j]); --j ) {}
        if( i < j ) {
            swap( arr[i++], arr[j--] );
        }
    }
    return i;
}

bool isKthBitSet(long long num, int k){
    return ((num >> k) & 1) != 0;
}