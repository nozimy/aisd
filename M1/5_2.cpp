//
// Created by nozim on 20.03.19.
//

/**
 * Task 5_2. Современники.
 *
 * Группа людей называется современниками если был такой момент,
 * когда они могли собраться вместе. Для этого в этот момент каждому
 * из них должно было  уже исполниться 18 лет, но ещё не исполниться 80 лет.
 * Дан список Жизни Великих Людей. Необходимо получить максимальное количество
 * современников. В день 18летия человек уже может принимать участие в
 * собраниях, а в день 80летия и в день смерти уже не может.
 *
 * Замечание.
 * Человек мог не дожить до 18-летия, либо умереть в день 18-летия.
 * В этих случаях принимать участие в собраниях он не мог.
 */

/**
 * Описание решения
 * Формируем 2 даты: [дата начала и дата конца) возможности увидеть современников
 * Дата конца: день 80летия или день смерти
 * Дата начала: день 18летия
 */

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

#define DATE_TYPE_BEGIN 'b'
#define DATE_TYPE_END 'd'
#define UPPER_LIMIT_AGE 80;
#define LOWER_LIMIT_AGE 18;

struct Date {
public:
    int day;
    int month;
    int year;
    char type;

    Date(): day(0), month(0), year(0), type(DATE_TYPE_BEGIN) {}
    Date(int d, int m, int y, char t){
        day = d;
        month = m;
        year = y;
        type = t;
    }
};

bool isLess(Date& a, Date& b){
    if (a.year != b.year)
        return a.year < b.year;
    else if (a.month != b.month)
        return a.month < b.month;
    else if (a.day != b.day)
        return a.day < b.day;
    else if (a.type != b.type)
        return a.type > b.type;
    else return false;
}

template <typename T, typename TComparator>
void merge(T* arr, int left, int mid, int right, TComparator less) {
    int i, j, k;
    int leftLen = mid - left + 1;
    int rightLen =  right - mid;

    T lefts[leftLen], rights[rightLen];

    for (i = 0; i < leftLen; i++)
        lefts[i] = arr[left + i];

    for (j = 0; j < rightLen; j++)
        rights[j] = arr[mid + 1 + j];

    i = j = 0;
    k = left;

    while (i < leftLen && j < rightLen) {

        if (less(lefts[i], rights[j]))
            arr[k++] = lefts[i++];
        else
            arr[k++] = rights[j++];
    }

    while (i < leftLen)
        arr[k++] = lefts[i++];

    while (j < rightLen)
        arr[k++] = rights[j++];
}

template <typename T, typename TComparator>
void mergeSort(T* arr, int left, int right, TComparator comparator){
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid, comparator);
        mergeSort(arr, mid + 1, right, comparator);

        merge(arr, left, mid, right, comparator);
    }
}

int countMaxPeopleInMeeting(Date *arr, int size){
    int peopleInMeeting = 0;
    int maxPeople = 0;

    for (int i =0; i < size; i++) {
        if (arr[i].type == DATE_TYPE_BEGIN) {
            peopleInMeeting++;
        } else {
            peopleInMeeting--;
        }
        if (peopleInMeeting > maxPeople) {
            maxPeople = peopleInMeeting;
        }
    }

    return maxPeople;
}

int main () {
    int n = 0;
    int realSize = 0;
    cin >> n;

    Date* dates = new Date[n * 2];

    Date *birthD  = new Date();
    Date *deathD  = new Date();

    while(cin >> birthD->day >> birthD->month >> birthD->year >> deathD->day >> deathD->month >> deathD->year){

        birthD->year += UPPER_LIMIT_AGE;     // для проверки на 80
        if (isLess(*birthD, *deathD)) {
            deathD->day = birthD->day;
            deathD->month = birthD->month;
            deathD->year = birthD->year;  // урезаем до 80 лет
        }
        birthD->year -= UPPER_LIMIT_AGE;         // восстанавливаем

        birthD->year += LOWER_LIMIT_AGE;
        // Дожил ли человек до 18 лет
        if (isLess(*birthD, *deathD)) { // Если есть 18, то добавляем в массив
            dates[realSize].type = DATE_TYPE_BEGIN;
            dates[realSize].day = birthD->day;
            dates[realSize].month = birthD->month;
            dates[realSize].year = birthD->year;
            realSize++;

            dates[realSize].type = DATE_TYPE_END;
            dates[realSize].day = deathD->day;
            dates[realSize].month = deathD->month;
            dates[realSize].year = deathD->year;
            realSize++;
        }
    }

    mergeSort(dates, 0, realSize-1, isLess);

    cout << countMaxPeopleInMeeting(dates, realSize) << endl;

    delete birthD;
    delete deathD;
    delete[] dates;
    return 0;
}
