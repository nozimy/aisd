/**
 * 7_3. Binary MSD для long long.
 * Дан массив неотрицательных целых 64-разрядных чисел.
 * Количество чисел не больше 10^6. Отсортировать массив
 * методом MSD по битам (бинарный QuickSort).
 */

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <functional>
using namespace std;

void CountingSort2(long long *a, int n, long long  k);
int digitAt(long long num, int exp);
void MSDSort(long long *arr, int n);
void MSDSort2(long long *arr, int n);

int main() {
    int n;
    cin >> n;
    auto *arr = new long long[n];
    for (int i=0; i < n; i++) {
        cin >> arr[i];
    }

//    CountingSort2(arr, n, 1000000);
//    MSDSort(arr, n);
    MSDSort2(arr, n);

    for (int i=0; i < n; i++) {
        cout << arr[i] << ' ';
    }

//    cout << endl << (arr[0] / 1) % 10;
    //    int exp = 1;
//    for (; arr[0] / (exp*10) > 0; exp *= 10){}
//    cout << endl << exp;

    delete[] arr;
    return 0;
}

long long getMax(const long long *arr, int n){
    long long max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

void countSort(long long *arr, int n, int exp){
    auto * count = new int[10];
    for(int  i = 0; i < 10; ++i ){
        count[i] = 0;
    }
    for( int i = 0; i < n; ++i ) {
        ++count[ digitAt(arr[i], exp) ];
    }

    cout << "count before:" << endl;
    for(int r = 0; r < 10; r++){
        cout << count[r] << ' ';
    }
    cout << endl;

    for( int  i = 1; i < 10; ++i ) {
        count[i] += count[i - 1];
    }

    cout << "count after:" << endl;
    for(int r = 0; r < 10; r++){
        cout << count[r] << ' ';
    }
    cout << endl;

    auto * output = new long long [n];
    for (int i = n - 1; i >= 0; i--){
        output[--count[ digitAt(arr[i], exp) ] ] = arr[i];
    }

    cout << "count:" << endl;
    for(int r = 0; r < 10; r++){
        cout << count[r] << ' ';
    }
    cout << endl;

    delete[] count;
    std::copy(output, output+n, arr);
    delete[] output;
}

void countSort2(long long *arr, long long *output, int lo, int hi, int exp){
    if (hi <= lo) {
        return;
    }
    int radix = 10;
    auto * count = new int[radix];
    for(int  i = 0; i < radix; ++i ){
        count[i] = 0;
    }
    for( int i = lo; i < hi; ++i ) {
        ++count[ digitAt(arr[i], exp) ];
    }
    for( int  i = 1; i < radix; ++i ) {
        count[i] += count[i - 1];
    }
    for (int i = hi - 1; i >= lo; i--){
        output[--count[ digitAt(arr[i], exp) ] ] = arr[i];
    }
    std::copy(output+lo, output+hi, arr+lo);

    exp /= 10;
    if (exp > 0) {
        for(int r = 0; r < radix-1; r++){
            countSort2(arr, output, lo + count[r], lo + count[r+1], exp);
        }
    }
    delete[] count;
}

void MSDSort2(long long *arr, int n) {
    long long max = getMax(arr, n);
    int exp = 1;
    for (; max / (exp*10) > 0; exp *= 10){}

    auto * output = new long long [n];
    countSort2(arr, output, 0, n, exp);
}

void MSDSort(long long *arr, int n){
    long long max = getMax(arr, n);
    int exp = 1;
    for (; max / (exp*10) > 0; exp *= 10){}

    for (; exp > 0; exp /= 10){
        countSort(arr, n, exp);
    }
}

void CountingSort2(long long *a, int n, long long  k) {
    auto * c = new long long [k];
    for(long long  i = 0; i < k; ++i )
        c[i] = 0;
    for( int i = 0; i < n; ++i )
        ++c[a[i]];                          //
    long long sum = 0;
    for( long long  i = 0; i < k; ++i ) {
        long long  tmp = c[i];
        c[i] = sum; // Начала групп.
        sum += tmp;
    }
    auto * b = new long long [n];
    for( int i = 0; i < n; ++i ) {
        b[c[a[i]]++] = a[i];                //
    }
    delete[] c;
    std::copy(b, b+n, a);
    delete[] b;
}

int digitAt(long long num, int exp){
    return (int)(num/exp)%10;
}

