#include <iostream>
#include <fstream>
#include <conio.h>
#include "Dot.h"
#include "Сircle.h"
#include "Sector.h"
#include "Figura.h"
using namespace std;

template <typename T1, typename T2, typename T3>
void menu2(T1& cont, T2& el, T3& iter, string name) //шаблонная функция менюшки
{   
    int j, index;
    float x, y;
    Dot* p; // объявляем указатель на базовый класс для реализации позднего связывания виртуальной функции moveTo

    do {
        system("cls");
        cout << "----------------------------------------\n";   // вывод меню
        cout << "1.Add " << name << "\n2.Show all " << name << "s\n3.Move " << name << " \n4.Delete " << name << " by index\n5.Delete all " << name << "s\n6.Previous menu\n";
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
                cout << " no any " << name << "s";
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
            cout << "Enter index less then " << cont.sizearr() << "\n"; // запрос индекса элемента в контейнере
            cin >> index;
            if (index < cont.sizearr() && index >=0)    //проверка корректности ввода индекса 
            {                
                cout << cont[index] << "\n";    // вывод информации об элементе через перегруженный оператор элемента <<, 
                                                // также используется перегруженный оператор [ ] контейнера
                cout << "Enter new x: ";        // запрос новой x
                cin >> x;
                cout << "Enter new y: ";        // запрос новой y
                cin >> y;
                p = &cont[index];               // присваиваем указателю p адрес объекта элемента контейнера
                p->moveTo(x, y);                // вызов виртуальной функции
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
                cont.removeEl(index); //метод из класса контейнера
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
    db.open(filename, ios::out | ios::binary);
    int n = cont.sizearr();
    db.write((char*)&n, sizeof(int));
    iter = cont.begin();
    while (iter != cont.end())
    {
        el = *iter;
        db.write((char*)&el, sizeof(el));
        iter++;
    }
    db.close();
}

int main()
{   
    Dot dot;                                           // обьявление переменных 
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

    fstream db;                                       //

    loaddb<Fig<Dot>, Dot>(dots, dot, dotsdb);               //чтение данных из файлов
    loaddb<Fig<Circle>, Circle>(circles, circle, circlesdb);//
    loaddb<Fig<Sector>, Sector>(sectors, sector, sectorsdb);//

    int i, n;
    do {
        
        system("cls");                                                                                             //очищаем экран
        cout << "----------------------------------------\n";
        cout << "1. Dots\n2. Circles\n3. Sectors\n4. Find circle cluster\n5. Summury info\n6. Save DB\n7. Exit\n"; //вывод меню
        cout << "----------------------------------------\n";
        cin >> i; 
        switch (i)
        {
        case 1:
            menu2<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter, "dot");                      //вызов функции вывода и действий подменю
            break;
        case 2:
            menu2<Fig<Circle>, Circle, FigIterator<Circle>>(circles, circle, circleiter, "circle"); //
            break;
        case 3:
            menu2<Fig<Sector>, Sector, FigIterator<Sector>>(sectors, sector, sectoriter, "sector"); //
            break;
        case 4:
            break;
        case 5:
            cout << dots.sizearr() << " dots\n";      //выводим размер класса контейнера?
            cout << circles.sizearr() << " circles\n";
            cout << sectors.sizearr() << " sectors\n";
            getch();
            break;
        case 6:
            savedb<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter, dotsdb);                      //сохраняем данные в файл
            savedb<Fig<Circle>, Circle, FigIterator<Circle>>(circles, circle, circleiter, circlesdb);
            savedb<Fig<Sector>, Sector, FigIterator<Sector>>(sectors, sector, sectoriter, sectorsdb);
            break;
        case 7:                                    
            break;        
        default:
            break;
        }
    } while (i != 7);
    
    return 0;
}