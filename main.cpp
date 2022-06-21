#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <Windows.h>
#include <conio.h>
#include "Dot.h"
#include "Сircle.h"
#include "Sector.h"
#include "Figura.h"
using namespace std;

// глобальная переменная хранит язык интерфейса программы
int language;

//функция локализации
string menu_locale(int menu_n, int loc)
{
    string res;
    switch (menu_n)
    {
    case 1:
        switch (loc)
        {
        case 1:
            res = "1. Dots\n2. Circles\n3. Sectors\n4. Find circle cluster\n5. Summury info\n6. Save DB\n7. Autotesting\n8. Exit\n";
            break;
        case 2:
            res = "1. Точки\n2. Круги\n3. Сектора\n4. Найти кластер кругов\n5. Общая информация\n6. Сохранить базу\n7. Автотестирование\n8. Выход\n";
            break;
        case 3:
            res = "1. Точки\n2. Кола\n3. Сектори\n4. Знайти кластер кіл\n5. Загальна інформація\n6. Зберегти базу\n7. Автотестування\n8. Вихід\n";
            break;
        }
        break;
    case 2:
        switch (loc)
        {
        case 1:
            res = "1.Add\n2.Show all\n3.Move\n4.Delete by index\n5.Delete all\n6.Previous menu\n";
            break;
        case 2:
            res = "1.Добавить\n2.Показать все\n3.Переместить\n4.Удалить по индексу\n5.Удалить все\n6.Предыдущее меню\n";
            break;
        case 3:
            res = "1.Додати\n2.Показати всі\n3.Перемістити\n4.Видалити за індексом\n5.Видалити всі\n6.Попереднє меню\n";
            break;
        }
        break;
    case 3:
        switch (loc)
        {
        case 1:
            res = "no objects";
            break;
        case 2:
            res = "нету объектов";
            break;
        case 3:
            res = "жодного об'єкта";
            break;
        }
    }
    return res;
}

template <typename T1, typename T2, typename T3>
void menu2(T1& cont, T2& el, T3& iter) //шаблонная функция менюшки
{   
    int j, index;
    float x, y;
    Dot* p; // объявляем указатель на базовый класс для реализации позднего связывания виртуальной функции moveTo

    do {
        system("cls");
        cout << "----------------------------------------\n";   // вывод меню
        cout << menu_locale(2, language);
        cout << "----------------------------------------\n";        
        cin >> j;           //запрос номера пункта меню
        switch (j)
        {
        case 1:
            cin >> el;      // вводим информацию об элементе, используя перегруженный операто ввода >>
            cont.addEl(el); //добавляем объект класса в контейнер
            break;
        case 2:
            if (cont.sizearr() == 0)    // проверяем размер контейнера, если = 0, выводим сообщение об отсутствии элементов
            {
                cout << menu_locale(3, language);
            }
            else
            {
                iter = cont.begin(); //ставим итератор на начало контейнера                
                int counter = 0;     //инициализация переменной для подсчета количества
                while (iter != cont.end()) //пока не дойдем до последнего елемента контейнера
                {
                    counter++;                        //считаем объекты контейнера
                    cout << counter << ". " << *iter; //перегруженная * из класса итератора возвращает ссылку на текущий элемент контейнера, 
                                                      //вывод элемента осуществляется через перегруженный оператор вывода <<
                    iter++;                           //перегруженная ++ сдвигает итератор  
                }
            }
            getch();    
            break;
        case 3:
            cout << "Enter index less then " << cont.sizearr()+1 << "\n"; // запрос индекса элемента в контейнере
            cin >> index;
            index--;
            if (index < cont.sizearr() && index >=0)    //проверка корректности ввода индекса 
            {           
                cout << cont[index] << "\n";    // вывод информации об элементе через перегруженный оператор элемента <<, 
                                                // также используется перегруженный оператор [ ] контейнера
                cout << "Enter new x: ";        // запрос новой x
                cin >> x;
                cout << "Enter new y: ";        // запрос новой y
                cin >> y;
                p = &cont[index];               // присваиваем указателю p адрес объекта элемента контейнера
                p->moveTo(x, y);                // вызов виртуальной функции, через механизм позднего связывания
                cout << "Checking:\n";
                cout << cont[index] << "\n";    //проверочный вывод
                getch();
            }
            break;
        case 4:            
            cout << "Enter index less then " << cont.sizearr() << "\n"; // запрос индекса элемента в контейнере
            cin >> index;
            if (index < cont.sizearr() && index >= 0)   //проверка корректности ввода индекса 
            {
                cont.removeByIndex(index); //метод класса контейнера
            }
            break;
        case 5:
            cont.removeAll(); //метод класса контейнера
            break;
        case 6:
            break;
        default:
            break;
        }
    } while (j != 6);    
}

template <typename T1, typename T2>
void loaddb(T1& cont, T2& el, string filename) //шаблонная функция загрузки данных из файла
{
    int n;
    fstream db;
    db.open(filename, ios::in | ios::binary);   //открываем бинарный файл на чтение
    if (db)
    {
        db.read((char*)&n, sizeof(int));        //читаем из файла в переменную n первую запись - количество записанных объектов
        for (int i = 0; i < n; i++)             // в цикле n раз 
        {
            db.read((char*)&el, sizeof(el));    //читаем из файла в переменную el записанные объекты
            cont.addEl(el);                     //добавляем в контейнер
        }
    }
    db.close();                                 //закрываем файл
}

template <typename T1, typename T2, typename T3>
void savedb(T1& cont, T2& el, T3& iter, string filename) //шаблонная функция сохранения данных в файл
{
    fstream db;
    db.open(filename, ios::out | ios::binary);  //открываем бинарный файл на запись
    int n = cont.sizearr();                     // получаем размер контейнера
    db.write((char*)&n, sizeof(int));           //записываем в файл первой записью размер контейнера
    iter = cont.begin();                        //ставим итератор на начало контейнера
    while (iter != cont.end())                  //пока итератор не достиг конца контейнера
    {
        el = *iter;                             //получаем элемент контейнера через перегруженную *
        db.write((char*)&el, sizeof(el));       //запись элемента в файл
        iter++;                                 //перегруженная ++ сдвигает итератор
    }
    db.close();
}
//функция определяет пересекаются ли две окружности
bool intersect(Circle c1, Circle c2)
{
    float dist = sqrt(pow((c2.getx() - c1.getx()), 2) + pow((c2.gety() - c1.gety()), 2));
    float sumrad = c1.getrad() + c2.getrad();
    return dist <= sumrad;
}

void find_clusters(Fig<Circle>& circles)
{
    // инициализация переменных
    vector<vector<Circle>> clusters;
    Fig<Circle> free_circles;
    Fig<Circle> first_wave;
    Fig<Circle> second_wave; 

    int i, j;
    free_circles = circles; //круги, которые еще не в кластерах - изначально все
    while (true)
    {
        if (free_circles.sizearr() != 0)    // если остались еще круги не в кластерах
        {
            vector<Circle> cluster;             // инициализируем новый кластер
            cluster.push_back(free_circles[0]); // добавляем в него первый свободный круг
            first_wave.removeAll();             //  очищаем вспомогательный массив 1
            first_wave.addEl(free_circles[0]);  // добавляем в него этот же свободный круг            
            free_circles.removeByIndex(0);      // т.к. круг включили в кластер, исключаем его из массива свободных кругов
            while (true)
            {
                FigIterator<Circle> iter1 = first_wave.begin(); //инициализация итератора для прохода по массиву 1
                while (iter1 != first_wave.end())
                {
                    Circle c1 = *iter1;                         // текущий круг из массива 1
                    FigIterator<Circle> iter2 = circles.begin();// инициализация итератора для прохода по всем кругам
                    while (iter2 != circles.end())
                    {
                        Circle c2 = *iter2;                     //текущий круг из массива всех кругов
                        if (free_circles.consist(c2))           // если с2 свободен (еще не в кластере)...
                        {
                            if (intersect(c1, c2))              //...проверяем его пересечение с кругом с1 из массива 1
                            {
                                second_wave.addEl(c2);          //если пересекается, добавляем его в массив 2                                
                            }
                        }
                        iter2++;
                    }
                    iter1++;
                }
                if (second_wave.sizearr() == 0)                 // если не нашли кругов с которыми пересекаются круги из массива 1
                {
                    break;                                      // прерываем - кластер заполнен
                }
                else
                {
                    first_wave = second_wave;                   // второй массив становится первым - в след. проходе цикла будем искать
                                                                // пересечения уже с кругами из этого массива
                    FigIterator<Circle> iter = second_wave.begin(); // и добавляем все круги из второго массива в кластер
                    while (iter != second_wave.end())
                    {
                        Circle c = *iter;
                        cluster.push_back(c);                   //добавляем в кластер и
                        free_circles.removeEl(c);               //исключаем из массива свободных кругов
                        iter++;
                    }
                    second_wave.removeAll();                    //для след прохода цикла очищаем массив 2
                }
            }
            clusters.push_back(cluster);                        // добавляем кластер в массив кластеров
        }
        else
        {
            break;                                              // если кругов среди свободных не осталось - все круги перебрали - выходим
        }
    }
    // вывод информации о кластерах
    for (i = 0; i < clusters.size(); i++)
    {
        cout << "Cluster " << i << ".\n";
        for (j = 0; j < clusters[i].size(); j++)
        {
            cout << "   " << clusters[i][j] << "";
        }
    }
}

//********************************************************************************
void Autotesting()
{
    cout << "Тестирование класса Dot\n";
    cout << "Конструктор по умолчанию <Dot d1>\n";
    Dot d1;
    cout << "Геттеры <d1.getx(), d1.gety()>\n";
    cout << d1.getx() << endl;
    cout << d1.gety() << endl;
    cout << "Сеттеры <d3.setx(8), d3.sety(9)>\n";
    d1.setx(8);
    d1.sety(9);
    cout << d1.getx() << endl;
    cout << d1.gety() << endl;
    cout << "Перегруженный оператор вывода <<\n";
    cout << d1 << "\n";
    cout << "Перегруженный оператор ввода >>\n";
    cin >> d1;
    cout << d1 << "\n";
    getch();
    cout << "Конструктор c параметрами <Dot d2(3, 4)>\n";
    Dot d2(3, 4);
    cout << d2 << "\n";
    cout << "Конструктор копирования <Dot d3 = d2;>\n";
    Dot d3 = d2;
    cout << d3 << "\n";            
    cout << "Перемещение <moveTo(11, 12)>\n";
    Dot* p;
    p = &d3;               
    p->moveTo(11, 12);
    cout << d3 << "\n";
    cout << "Перегруженный оператор + \n<Dot(7, 3) + Dot(3, 8)>\n";
    cout << Dot(7, 3) + Dot(3, 8) << "\n";
    cout << "Перегруженный оператор - \n<Dot(12, 12) - Dot(6, 2)>\n";
    cout << Dot(12, 12) + Dot(6, 2) << "\n";
    cout << "Перегруженный оператор * \n<Dot(1, 2) * 10>\n";
    cout << Dot(1, 2) * 10 << "\n";
    cout << "Перегруженный оператор / \n<Dot(12, 12) / 4>\n";
    cout << Dot(12, 12) / 4 << "\n";
    cout << "Перегруженный оператор сравнения == \n<Dot(1, 2) == Dot(1, 2)>\n";
    cout << (Dot(1, 2) == Dot(1, 2) ? "Equal" : "Not equal") << "\n";
    cout << "Перегруженный оператор сравнения != \n<Dot(1, 2) != Dot(1, 3)>\n";
    cout << (Dot(1, 2) != Dot(1, 3) ? "Not equal" : "Equal") << "\n";
    //////////////////// class circle ////////////////////
    /*Circle c1;
    Circle c2(1, 1, 2);
    cout << "By default constructor: x= " << c1.getx() << " y= " << c1.gety() << " rad= " << c1.getrad() << endl;
    cout << "By constructor with parametrs: x= " << c2.getx() << " y= " << c2.gety() << " rad= " << c2.getrad() << endl;
    Circle* cir = new Circle(3, 3, 3);
    delete cir; // вызывается деструктор для объекта cir

    int c;
    c1.setx(12);
    c1.sety(13);
    c1.setrad(10);
    c = c1.getx(); cout <<"c1 x = "<< c << endl;
    c = c1.gety(); cout << "c1 y = " << c << endl;
    c = c1.getrad(); cout << "c1 rad = " << c << endl;
    
    c1.moveTo(1, 1);
    cout << c1; // тестируем перегруженную <<
    cin >> c2;  // тестируем перегруженную >>
    cout << c2;
    if (c1 == c2)
        cout << "c1 and c2 are the same.\n";

    if (c1 != c2)
        cout << "c1 and c2 are not the same.\n ";
    //////////////////// class sector ///////////////////////
    Sector s1;
    Sector s2(2, 3, 6, 2, 3);
    cout << "By default constructor: x= " << s1.getx() << " y= " << s1.gety() << " rad= " << s1.getrad() << " a= " << s1.geta()<< " b= " << s1.getb() << endl;
    cout << "By constructor with parametrs: x= " << s1.getx() << " y= " << s1.gety() << " rad= " << s1.getrad() << " a= " << s1.geta() << " b= " << s1.getb() << endl;
    Sector* sec = new Sector(1, 1, 1, 1, 1);
    delete sec; // вызывается деструктор для объекта sec

    int s;
    s1.setx(44);
    s1.sety(45);
    s1.setrad(46);
    s1.seta(47);
    s1.setb(48);
    cout << s1; // тестируем перегруженную <<

    s1.moveTo(88, 6.3);
    cout << s1.getx() << endl;
    cout << s1.gety() << endl;

    cin >> s2; // тестируем перегруженную >>
    cout << s2;
    if (s1 == s2)
        cout << "s1 and s2 are the same.\n";

    if (s1 != s2)
        cout << "s1 and s2 are not the same.\n ";*/
    getch();
}
//********************************************************************************

int main()
{    
    // обьявление переменных
    Dot dot;                                            
    Circle circle;    
    Sector sector;

    Fig<Dot> dots;
    Fig<Circle> circles;
    Fig<Sector> sectors;

    FigIterator<Dot> dotiter = dots.begin();
    FigIterator<Circle> circleiter = circles.begin();
    FigIterator<Sector> sectoriter = sectors.begin();

    string dotsdb = "dots.data";
    string circlesdb = "circles.data";
    string sectorsdb = "sectors.data";

    fstream db;           
    
    // вызываем шаблонну функцию чтения данных из файла, последовательно для 3 контейнеров
    loaddb<Fig<Dot>, Dot>(dots, dot, dotsdb);               
    loaddb<Fig<Circle>, Circle>(circles, circle, circlesdb);
    loaddb<Fig<Sector>, Sector>(sectors, sector, sectorsdb);

    //меню выбора языка вывода меню
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);    
    cout << "1. English\n2. Русский \n3. Українська\n";
    cin >> language;

    int i, j, n;    
    do {
        // вывод меню верхнего уровня
        system("cls");              //очищаем экран
        cout << "----------------------------------------\n";
        cout << menu_locale(1, language);
        cout << "----------------------------------------\n";
        cin >> i;   //запрос номера пункта меню
        switch (i)
        {
        case 1:
            menu2<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter);                      //вызов функции вывода и действий подменю для точек
            break;
        case 2:
            menu2<Fig<Circle>, Circle, FigIterator<Circle>>(circles, circle, circleiter); //вызов функции вывода и действий подменю для кругов
            break;
        case 3:
            menu2<Fig<Sector>, Sector, FigIterator<Sector>>(sectors, sector, sectoriter); //вызов функции вывода и действий подменю для секторов
            break;
        case 4:
            find_clusters(circles);             // вызов функции поиска кластера пересекающихся окружностей            
            getch();
            break;
        case 5:
            cout << dots.sizearr() << " dots\n";        //выводим размер контейнера для точек
            cout << circles.sizearr() << " circles\n";  //выводим размер контейнера для кругов
            cout << sectors.sizearr() << " sectors\n";  //выводим размер контейнера для секторов
            getch();
            break;
        case 6:
            // вызываем шаблонну функцию записи данных в файл, последовательно для 3 контейнеров
            savedb<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter, dotsdb);                     
            savedb<Fig<Circle>, Circle, FigIterator<Circle>>(circles, circle, circleiter, circlesdb);
            savedb<Fig<Sector>, Sector, FigIterator<Sector>>(sectors, sector, sectoriter, sectorsdb);
            break;
        case 7:    
            Autotesting();
            break;  
        case 8:
            break;
        default:
            break;
        }
    } while (i != 8);
    
    return 0;
}