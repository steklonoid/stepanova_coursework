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
                cont.removeEl(index); //метод класса контейнера
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
        iter++;                                  //перегруженная ++ сдвигает итератор
    }
    db.close();
}

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

    int i, n;
    do {
        // вывод меню верхнего уровня
        system("cls");              //очищаем экран
        cout << "----------------------------------------\n";
        cout << "1. Dots\n2. Circles\n3. Sectors\n4. Find circle cluster\n5. Summury info\n6. Save DB\n7. Exit\n"; 
        cout << "----------------------------------------\n";
        cin >> i;   //запрос номера пункта меню
        switch (i)
        {
        case 1:
            menu2<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter, "dot");                      //вызов функции вывода и действий подменю для точек
            break;
        case 2:
            menu2<Fig<Circle>, Circle, FigIterator<Circle>>(circles, circle, circleiter, "circle"); //вызов функции вывода и действий подменю для кругов
            break;
        case 3:
            menu2<Fig<Sector>, Sector, FigIterator<Sector>>(sectors, sector, sectoriter, "sector"); //вызов функции вывода и действий подменю для секторов
            break;
        case 4:
            break;
        case 5:
            cout << dots.sizearr() << " dots\n";      //выводим размер контейнера для точек
            cout << circles.sizearr() << " circles\n";//выводим размер контейнера для кругов
            cout << sectors.sizearr() << " sectors\n";//выводим размер контейнера для секторов
            getch();
            break;
        case 6:
            // вызываем шаблонну функцию записи данных в файл, последовательно для 3 контейнеров
            savedb<Fig<Dot>, Dot, FigIterator<Dot>>(dots, dot, dotiter, dotsdb);                     
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