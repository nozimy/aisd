/*

Группа людей называется современниками если был такой момент, когда они могли собраться вместе.
Для этого в этот момент каждому из них должно было уже исполниться 18 лет, но ещё не исполниться 80 лет.
Дан список Жизни Великих Людей. Необходимо получить максимальное количество современников.
В день 18летия человек уже может принимать участие в собраниях, а в день 80летия и в день смерти уже не может.
Замечание. Человек мог не дожить до 18-летия, либо умереть в день 18-летия. В этих случаях принимать участие в
собраниях он не мог.

*/

#include <iostream>
#include <assert.h>
#include <vector>
#include <string>

using namespace std;

class Event;
class Person;
template <typename T> class Heap;

class Event {
public:
    Event();
    Event(int year, int month, int day, int type);
    bool less(const Event& event);
    string to_string();
    void add_years(int years);

    int year;
    int month;
    int day;
    int type;
    // type:
    // 0 - birth day
    // 1 - die day
};

Event::Event() {
}

Event::Event(int year, int month, int day, int type) {
    this->year = year;
    this->month = month;
    this->day = day;
    this->type = type;
}

bool Event::less(const Event& event) {
    return (year < event.year) ||
           (year == event.year && month < event.month) ||
           (year == event.year && month == event.month && day < event.day) ||
           (year == event.year && month == event.month && day == event.day && type > event.type);
}

string Event::to_string() {
    string res = ::to_string(year) + " " + ::to_string(month) + " " + ::to_string(day) + " " + ::to_string(type) + "\n";
    return res;
}

void Event::add_years(int years) {
    year += years;
}

template <typename T>
class Heap {
public:
    Heap(): size(0) {
    }

    Heap(vector<T>& arr) {
        size = arr.size();
        buffer = arr;

        for(int i = size/2 - 1; i >= 0; i--)
            sift_down(i);
    }

    int get_size() {
        return size;
    }

    T top() {
        assert(size > 0);
        return buffer[0];
    }

    T pop_top() {
        assert(size > 0);
        T elem = buffer[0];
        size--;
        if(size > 0) {
            swap(buffer[0], buffer[size]);
            sift_down(0);
        }

        return elem;
    }

    void add(T& elem) {
        buffer.push_back(elem);
        sift_up(size);
        size++;
    }

    void sift_up(int index) {
        while(index > 0) {
            int parent = (index - 1) / 2;
            if(buffer[index].less(buffer[parent]))
                return;
            swap(buffer[index], buffer[parent]);
            index = parent;
        }
    }

    void sift_down(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int largest = index;
        if(left < size && buffer[largest].less(buffer[left]))
            largest = left;
        if(right < size && buffer[largest].less(buffer[right]))
            largest = right;
        if(largest != index) {
            swap(buffer[largest], buffer[index]);
            sift_down(largest);
        }
    }

    void draw() {
        cout<<"--------------";
        cout<<endl;
        for(int i=0; i < size; i++)
            cout<<buffer[i].to_string();
        cout<<endl;
    }

    void sort() {
        int old_size = size;
        while(size > 1) {
            swap(buffer[0], buffer[size-1]);
            --size;
            sift_down(0);
        }
        size = old_size;
    }

    int calculate_max_online() {
        int cur = 0, max_online = 0;
        for(int i = 0; i < size; i++) {
            if(buffer[i].type == 0) {
                cur++;
            }
            if(buffer[i].type == 1) {
                cur--;
            }
            if(cur > max_online)
                max_online = cur;
        }

        return max_online;
    }

private:
    vector <T> buffer;
    int size;
};

class Person {
public:
    Person(Event& birth, Event& death) {
        this->birth = birth;
        this->birth.add_years(18);
        this->death = death;
    }

    bool is_mature();
    Event end_of_meeting();


    Event birth;
    Event death;
};

bool Person::is_mature() {
    if(death.less(birth)) return false;
    return true;
}

Event Person::end_of_meeting() {
    Event birth_plus_eighty(birth.year+80-18, birth.month, birth.day, 1);
    if(birth_plus_eighty.less(death))
        return birth_plus_eighty;
    return death;
}

void get_dates(vector <Event>& v) {
    int n;
    cin>>n;
    for(int i = 0; i < n; i++) {
        int b_day, b_month, b_year, d_day, d_month, d_year;
        cin>>b_day>>b_month>>b_year>>d_day>>d_month>>d_year;
        Event birth(b_year, b_month, b_day, 0);
        Event death(d_year, d_month, d_day, 1);
        Person person(birth, death);
        if(person.is_mature()) {
            v.push_back(person.birth);
            v.push_back(person.end_of_meeting());
        }
    }
}

int main() {
    vector<Event> v;
    get_dates(v);

    cout << v.size() << endl;

    Heap<Event> heap(v);
    heap.sort();
    int max_online = heap.calculate_max_online();
    cout<<max_online<<endl;

    return 0;
}