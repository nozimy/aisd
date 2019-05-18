//
// Created by nozim on 30.03.19.
//
/*
двойное пробирование

размер шага зависит и от ключа

h(k, i) = h1(k) + i * h2(k)

сделать h1 нечетным

*/
/**
 * Реализуйте структуру данных типа “множество строк” на основе
 * динамической хеш-таблицы с открытой адресацией. Хранимые строки
 * непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления
 * значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми. Перехеширование
 * выполняйте при добавлении элементов в случае, когда коэффициент
 * заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции добавления строки
 * в множество, удаления строки из множества и проверки принадлежности
 * данной строки множеству.
 *
 * 1_2. Для разрешения коллизий используйте двойное хеширование.
 *
 */

#include <iostream>
#include <string>
#include <vector>

using namespace std;

const size_t DEFAULT_SIZE = 8;
const size_t RESIZE_FACTOR = 2;
const double MAX_ALPHA = 0.75;
const int FACTOR_GORNER = 13;
const int FACTOR_GORNER_2 = 71;

template <typename T>
struct HashNode
{
    HashNode(const T &key): key(key), isDeleted(true){}
    T key;
    bool isDeleted;
};

size_t Hash(const std::string &s, size_t size)
{
    size_t hash = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        hash = (hash * FACTOR_GORNER + s[i] )  % size;
    }
    return hash;
}

size_t Hash2(const std::string &s, size_t size)
{
    size_t hash = 0;
    for (size_t i = 0; i < s.size(); i++)
    {
        hash = (hash * FACTOR_GORNER_2 + s[i] )  % size;
    }

    if (hash % 2 == 0) {
        hash = (hash + 1) % size;
    }
    return hash;
}

template <class T>
class HashTable {
public:
    HashTable(size_t size = DEFAULT_SIZE): table(size, nullptr), elements_size(0){}
    ~HashTable(){}

    bool Add(const T& key)
    {
        if (Has(key))
            return false;

        for( int i = 0; i < table.size(); ++i ) {
            size_t hash = DoubleHash(key, i, table.size());
//            if(table[hash] != nullptr && !table[hash]->isDeleted && table[hash]->key == key){
//                return false;
//            }
            if( table[hash] == nullptr || table[hash]->isDeleted) {
                if (table[hash] == nullptr) {
                    table[hash] = new HashNode<T>(key);
                } else {
                    table[hash]->key = key;
                }
                table[hash]->isDeleted = false;
                elements_size++;
                break;
            }
        }

        if (elements_size >= MAX_ALPHA * table.size())
            grow();

        return true;
    }

    bool Delete(const T &key)
    {

        if (!Has(key))
            return false;

        for( int i = 0; i < table.size(); ++i ) {
            size_t hash = DoubleHash(key, i,table.size());
            if (table[hash] == nullptr){
                return false;
            } else if(!table[hash]->isDeleted && table[hash]->key == key) {
                table[hash]->isDeleted = true;
                elements_size--;
                return true;
            }
        }
        return false;
    }

    bool Has(const T &key)
    {
        for( int i = 0; i < table.size(); ++i ) {
            size_t hash = DoubleHash(key, i, table.size());

            if (table[hash] == nullptr){
                return false;
            } else if(!table[hash]->isDeleted && table[hash]->key == key) {
                return true;
            }
        }
        return false;
    }

    void displayHash()
    {
        for (int i = 0; i < table.size(); i++)
        {
            if (table[i] != nullptr)
                if (!table[i]->isDeleted)
                    cout << i << " --> "
                         << table[i]->key << endl;
                else
                    cout << i << " --> "
                         << table[i]->key << " isDeleted" << endl;
            else
                cout << i << endl;
        }
    }

private:
    std::vector<HashNode<T>*> table;
    size_t elements_size;

    void grow()
    {
        std::vector<HashNode<T>*> newTable(table.size() * RESIZE_FACTOR, nullptr);

        for (size_t i = 0; i < table.size(); i++)
        {
            HashNode<T> *node = table[i];
            if (node != nullptr && !node->isDeleted)
            {
                for (int j=0; j < newTable.size(); j++) {
                    size_t newHash = DoubleHash(node->key, j, newTable.size());
                    if(newTable[newHash] == nullptr) {
                        newTable[newHash] = node;
                        break;
                    }
                }
            }
        }
        table = std::move(newTable);
    }

    size_t DoubleHash(const std::string &s, int probe, size_t tableSize){
        return (Hash(s, tableSize) + probe * Hash2(s, tableSize)) % tableSize;
    }
};

template <class T>
void performCommand(HashTable<T>& hashTable, T& key, char command);

int main(){
    HashTable<string> hashTable;
    char command;
    string key;

    while(cin >> command >> key){
//        if (command == '.') break;
        if (command == '/') {
            hashTable.displayHash();
        } else {
            performCommand<string>(hashTable, key, command);
        }
    }

    return 0;
}

template <class T>
void performCommand(HashTable<T>& hashTable, T& key, char command){
    switch (command) {
        case '+':
            cout << (hashTable.Add(key) ? "OK" : "FAIL") << endl;
            break;
        case '-':
            cout << (hashTable.Delete(key) ? "OK" : "FAIL") << endl;
            break;
        case '?':
            cout << (hashTable.Has(key) ? "OK" : "FAIL") << endl;
            break;
    }
}
