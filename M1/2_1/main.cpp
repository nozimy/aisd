/**
 * Юнусов Нозимжон АПО-13
 *
 * Дан отсортированный массив целых чисел A[0..n-1] и
 * массив целых чисел B[0..m-1]. Для каждого элемента
 * массива B[i] найдите минимальный индекс k минимального э
 * лемента массива A, равного или превосходящего B[i]: A[k] >= B[i].
 * Если такого элемента нет, выведите n. Время работы поиска k для
 * каждого элемента B[i]: O(log(k)). n, m ≤ 10000.
 */

/**
 * Описание решения
 *
 * Для каждого элемента B[i]
 *      - вначале ищется такая точка right в массиве A, где A[right] >= B[i].
 *      поиск начинается с 0 индекса. Шаг поиска каждый раз увеличивается в 2 раза: 0, 1, 2, 4, 8, 16...
 *      - если right > n, то right = n и поиск заканчивается. Запоминаются предпоследний и последний шаги: left, right
 *      - затем в области от left до  right  бинарным поиском ищется минимальный индекс k
 *      минимального элемента массива A, равного или превосходящего B[i]: A[k] >= B[i].
 *      - если такого элемента нет, выводится n.
 */


#include <iostream>
using namespace std;

int minBinarySearch(const int *arrayToSearch, int left, int right, int key);
int findMinGreaterEqual(const int *A, int n, int bElement);

int main() {
    int n, m = 0;

    cin >> n >> m;

    int i;
    int A[n-1];
    for(i = 0; i < n; i++){
        cin >> A[i];
    }
    int B[m-1];
    for(i = 0; i < m; i++){
        cin >> B[i];
    }

    for( i = 0; i < m; i++){
        cout << findMinGreaterEqual(A, n, B[i]) << ' ';
    }

    return 0;
}

int findMinGreaterEqual(const int *A, int n, int bElement){
    int left = 0, right = 0;
    while (A[right] < bElement && right < n) {
        if (right == 0) right = 2;
        else {
            left = right;
            right *= 2;
            if (right > n) right = n;
        }
    }

    int k = minBinarySearch(A, left, right, bElement);

    if (k == -1) {
        k = n;      // По условию задачи
    }
    return k;
}

int minBinarySearch(const int *arrayToSearch, int left, int right, int key){
    if (right >= left) {
        int mid = (right + left) / 2;

        if (arrayToSearch[mid] >= key){
            int test = minBinarySearch(arrayToSearch, left, mid - 1, key);
            if (test == -1) {
                return mid;
            } else {
                return test;
            }
        }

        return minBinarySearch(arrayToSearch, mid + 1, right, key);
    }

    return -1;
}