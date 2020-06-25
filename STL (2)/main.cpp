#include "train.h"

int main()
{
    std::cout << "STL. Class Train\n";
    std::vector<Train> trains;
    std::set<Train> temp;
    std::ifstream fin("Task1.txt");
    
    if (!fin)
    {
        std::cout << "Error open file!\n";
        return 0;
    }
    
    //создаем два итератора
    //первый итератор связываем с нашим файловым потоком
    //второй итератор используем как temp
    std::istream_iterator<Train> input(fin), cur;
    
    //читаем данные из файла в контейнер set (бинарное дерево поиска)
    //данные сортируются по ключу на этапе добавления
    std::copy(input, cur, std::inserter(temp, temp.begin()));
    
    //копируем данные из set в vector
    std::copy(temp.begin(), temp.end(), std::back_inserter(trains));
    
    //флаг для выхода из цикла true
    bool flag = true;
    
    while (flag)
    {
        int choise;
        std::cout << "\nCommands:\n"
        << "1. Print all train information\n"
        << "2. Print train information in destination\n"
        << "3. Print train information in time\n"
        << "4. Replace destination\n"
        << "0. Exit\n"
        << "\nEnter number coomand: ";
        std::cin >> choise;
        
        switch (choise)
        {
            case 0: //exit
            {
                flag = false;
                break;
            }
            case 1: //print all train information
            {
                if (trains.size())
                {
                    //копируем все данные из вектора в поток cout для вывода на консоль
                    std::copy(trains.begin(), trains.end(), std::ostream_iterator<Train>(std::cout));
                }
                else
                {
                    std::cout << "Train information is empty\n";
                }
                
                break;
            }
            case 2: //print train information in destination
            {
                std::cout << "Enter destination: ";
                std::string city;
                std::cin >> city;
                
                std::copy_if(trains.begin(), trains.end(), std::ostream_iterator<Train>(std::cout), [city] (const Train& train)
                             {
                    return train.getDestination() == city;
                });
                
                break;
            }
            case 3: //print train information in time
            {
                size_t s_hours, s_min, e_hours, e_min;
                std::cout << "Enter start time\nEnter hours: ";
                std::cin >> s_hours;
                std::cout << "Enter minuts: ";
                std::cin >> s_min;
                std::cout << "\nEnter end time\nEnter hours: ";
                std::cin >> e_hours;
                std::cout << "Enter minuts: ";
                std::cin >> e_min;
                
                std::copy_if(trains.begin(), trains.end(), std::ostream_iterator<Train>(std::cout), [s_hours, s_min, e_hours, e_min] (const Train& train)
                             {
                    if (train.getHours() >= s_hours && train.getHours() <= e_hours)
                    {
                        if (train.getHours() == s_hours)
                        {
                            return train.getMinutes() >= s_min? true : false;
                        }
                        else if (train.getHours() == e_hours)
                        {
                            return train.getMinutes() <= e_min? true : false;
                        }
                        else
                        {
                            return true;
                        }
                    }
                    else
                    {
                        return false;
                    }
                });
                
                break;
            }
            case 4: //replace destination
            {
                std::string city, city_new;
                std::cout << "Enter destination to find: ";
                std::cin >> city;
                std::cout << "Enter new destination: ";
                std::cin >> city_new;
                std::replace_if(trains.begin(), trains.end(),[city](const Train& train){ return train.getDestination() == city; }, city_new);
                break;
            }
            default:
            {
                std::cout << "Not number command!\n";
            }
        }
    }
    
    return 0;
}
