#include <iostream>
#include <list>
using namespace std;
//
//int main() {
//
//
//	/*Таблица содержит данные об успеваемости студентов, в
//	качестве ключа используется фамилии студента.Разработать
//	функции включения, удаления и поиска записи по ключу
//	в хештаблице с двойным хешированием.*/
//
//
//
//
//	return 0;
//}


// Размер хеш-таблицы
#define TABLE_SIZE 13


// Используется во второй хэш-функции.
#define PRIME 7


struct student {

    string name;
    int math, code, history;
  
    student(string name, int math, int code, int history) {

        this->name = name;
        this->code = code;
        this->history = history;

    }

};


int StringToInt(string s) {


    int a = 0;

    for (int i = 0; i < s.length(); i++)
        a += (int)(s[i]);
    
    return a;

}

student AddToHash() {

    string name;
    int math, hist, code;

    cout << "(Name - Math - History - Code ) = ";
    cin >> name >> math >> hist >> code;


    return student(name, math, hist, code);
    

}

class DoubleHash

{
public:

    list <int> hashes;
    int hashTable [TABLE_SIZE];

    int curr_size;


    int hash1(int key)
    {
        return (key % TABLE_SIZE);
    }

    int hash2(int key)

    {
        return (PRIME - (key % PRIME));
    }

    DoubleHash()

    {

        curr_size = 0;

        for (int i = 0; i < TABLE_SIZE; i++)

            hashTable[i] = -1;

    }

    void insertHash(int key)

    {

        if (curr_size == TABLE_SIZE)  return;

        int index = hash1(key);

        if (hashTable[index] != -1)

        {

            int index2 = hash2(key);

            int i = 1;

            while (true)

            {

                int newIndex = (index + i * index2) %  TABLE_SIZE;

                if (hashTable[newIndex] == -1)
                {
                    hashTable[newIndex] = key;

                    break;
                }

                i++;

            }

        }



        // если не происходит столкновения

        else

            hashTable[index] = key;

        curr_size++;

    }



    // функция для отображения хеш-таблицы

    void displayHash()

    {

        for (int i = 0; i < TABLE_SIZE; i++)

        {

            if (hashTable[i] != -1)

                cout << i << " --> "

                << hashTable[i] << endl;

            else

                cout << i << endl;

        }

    }

};


// Код водителя

int main()

{
    DoubleHash h;

    list<student> st;

    st.push_back(student("Alex", 5, 5, 5));
    st.push_back(student("Blex", 5, 5, 5));
    st.push_back(student("Clex", 5, 5, 5));
    st.push_back(student("Flex", 5, 5, 5));

  
    auto iter = st.begin();

    while (iter != st.end())
    {
        h.insertHash(StringToInt((*iter).name));
        iter++;
    }

  

    int way;
    string name;
    bool check;
    while (true) {

        

        cout << "What to do? " <<
            endl << "1: Searth" <<
            endl << "2: Delete" <<
            endl << "3: Add" <<
            endl;

        cin >> way;

        switch (way)
        {

        case 1:
            cout << "Name = ";
            cin >> name;
            check = false;
            for (int i = 0; i < TABLE_SIZE; i++) 
                if (h.hashTable[i] == StringToInt(name)) {
                    check = true;
                    break;
               }

            if (check) cout << "Yes, there is";
            else cout << "Not exist";
            cout << endl;
            break;

        case 2: {
            
            cout << "Which element delete? ";
            cin >> name;

            auto it = st.begin();

            for (int i = 0; i < TABLE_SIZE; i++)
            {
                if (h.hashTable[i] == StringToInt(name)) {
                    h.hashTable[i] = -1;
                    st.erase(it, it);

                }
                if (h.hashTable[i]!=-1)
                it++;
            }
        }
            break;

        case 3:
            st.push_front(AddToHash());
            auto it = st.begin();
            h.insertHash(StringToInt((*it).name));
            break;
        }
        h.displayHash();
    }
   

    return 0;

}