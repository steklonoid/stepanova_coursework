#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
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

    int i, j, n;    
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
            break;        
        default:
            break;
        }
    } while (i != 7);
    
    return 0;
}