#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <locale.h>

using namespace std;

// Структура объявления
struct Ad {
    int number;
    string title;
    float cost;
    string city;
    string phone;
};

// Перегрузка оператора << для класса Ad
std::ostream& operator<<(std::ostream& os, const Ad& ad) {
    os << "Номер объявления: " << ad.number << endl;
    os << "Заголовок объявления: " << ad.title << endl;
    os << "Стоимость: " << ad.cost << endl;
    os << "Город: " << ad.city << endl;
    os << "Телефон: " << ad.phone << endl;
    return os;
}

// Функция для добавления записи в базу данных
void addRecord(list<Ad>& ads) {
    Ad newAd;
    cout << "Введите заголовок объявления: ";
    getline(cin >> ws, newAd.title);
    cout << "Введите стоимость: ";
    cin >> newAd.cost;
    cout << "Введите город: ";
    getline(cin >> ws, newAd.city);
    cout << "Введите телефон: ";
    getline(cin >> ws, newAd.phone);

    // Генерация уникального номера объявления
    if (ads.empty()) {
        newAd.number = 1;
    }
    else {
        int lastNumber = ads.back().number;
        newAd.number = lastNumber + 1;
    }

    ads.push_back(newAd);
    cout << "Запись добавлена." << endl;
}

// Функция для удаления записи из базы данных
void deleteRecord(list<Ad>& ads, int number) {
    auto it = ads.begin();
    while (it != ads.end()) {
        if (it->number == number) {
            it = ads.erase(it);
            cout << "Запись удалена." << endl;
            return;
        }
        else {
            ++it;
        }
    }

    cout << "Запись с номером " << number << " не найдена." << endl;
}

// Функция для вывода информации о всех объявлениях заданного города
void printAdsByCity(const list<Ad>& ads, const string& city) {
    bool found = false;
    for (const auto& ad : ads) {
        if (ad.city == city) {
            cout << "Номер объявления: " << ad.number << endl;
            cout << "Заголовок объявления: " << ad.title << endl;
            cout << "Стоимость: " << ad.cost << endl;
            cout << "Город: " << ad.city << endl;
            cout << "Телефон: " << ad.phone << endl;
            cout << "--------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Объявления в городе " << city << " не найдены." << endl;
    }
}

// Функция для вывода информации о объявлениях с ценой ниже заданной
void printAdsByCost(const list<Ad>& ads, float maxCost) {
    bool found = false;
    for (const auto& ad : ads) {
        if (ad.cost < maxCost) {
            cout << "Номер объявления: " << ad.number << endl;
            cout << "Заголовок объявления: " << ad.title << endl;
            cout << "Стоимость: " << ad.cost << endl;
            cout << "Город: " << ad.city << endl;
            cout << "Телефон: " << ad.phone << endl;
            cout << "--------------------------" << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Объявления со стоимостью ниже " << maxCost << " не найдены." << endl;
    }
}

// Функция для просмотра всех записей в базе данных
void viewRecords(const list<Ad>& ads) {
    if (ads.empty()) {
        cout << "База данных пуста." << endl;
        return;
    }

    for (const auto& ad : ads) {
        cout << "Номер объявления: " << ad.number << endl;
        cout << "Заголовок объявления: " << ad.title << endl;
        cout << "Стоимость: " << ad.cost << endl;
        cout << "Город: " << ad.city << endl;
        cout << "Телефон: " << ad.phone << endl;
        cout << "--------------------------" << endl;
    }
}

// Функция для изменения записи в базе данных
void editRecord(list<Ad>& ads, int number) {
    for (auto& ad : ads) {
        if (ad.number == number) {
            cout << "Введите новый заголовок объявления: ";
            getline(cin >> ws, ad.title);
            cout << "Введите новую стоимость: ";
            cin >> ad.cost;
            cout << "Введите новый город: ";
            getline(cin >> ws, ad.city);
            cout << "Введите новый телефон: ";
            getline(cin >> ws, ad.phone);
            cout << "Запись изменена." << endl;
            return;
        }
    }

    cout << "Запись с номером " << number << " не найдена." << endl;
}

// Функция для сохранения базы данных в файл
void saveToFile(const list<Ad>& ads, const string& filename) {
    ofstream file(filename, ios::binary);
    if (file.is_open()) {
        for (const auto& ad : ads) {
            file.write(reinterpret_cast<const char*>(&ad), sizeof(Ad));
        }
        file.close();
        cout << "База данных сохранена в файле " << filename << "." << endl;
    }
    else {
        cout << "Ошибка открытия файла " << filename << " для сохранения базы данных." << endl;
    }
}

// Функция для экспорта базы данных в текстовый файл CSV формата
void exportToCSV(const list<Ad>& ads, const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        for (const auto& ad : ads) {
            file << ad.number << ";" << ad.title << ";" << ad.cost << ";" << ad.city << ";" << ad.phone << "\n";
        }
        file.close();
        cout << "База данных экспортирована в файл " << filename << " в формате CSV." << endl;
    }
    else {
        cout << "Ошибка открытия файла " << filename << " для экспорта базы данных." << endl;
    }
}

// Функция для изменения настроек через интерфейс программы
void changeSettings() {
    string configFilename = "config.txt";
    string databaseFilename;
    string licenseKey;

    // Проверка наличия конфигурационного файла
    ifstream configFile(configFilename);
    if (configFile.is_open()) {
        // Чтение настроек из конфигурационного файла
        string line;
        while (getline(configFile, line)) {
            if (line.substr(0, 3) == "DB=") {
                databaseFilename = line.substr(3);
            }
            else if (line.substr(0, 4) == "KEY=") {
                licenseKey = line.substr(4);
            }
        }

        configFile.close();
    }
    else {
        // Создание нового конфигурационного файла
        ofstream newConfigFile(configFilename);
        if (newConfigFile.is_open()) {
            newConfigFile << "DB=mybd.dat" << endl;
            newConfigFile << "KEY=01AFC56" << endl;
            newConfigFile.close();
            databaseFilename = "mybd.dat";
            licenseKey = "01AFC56";
            cout << "Создан новый конфигурационный файл." << endl;
        }
        else {
            cout << "Ошибка создания конфигурационного файла." << endl;
            return;
        }
    }

    // Остальной код функции...
}

int main() {
    string configFilename = "config.txt";
    string databaseFilename;
    string licenseKey;
    string city;
    string exportFilename;
    setlocale(LC_ALL, "Russian");

    // Чтение настроек из конфигурационного файла
    ifstream configFile(configFilename);
    if (configFile.is_open()) {
        string line;
        while (getline(configFile, line)) {
            if (line.substr(0, 3) == "DB=") {
                databaseFilename = line.substr(3);
            }
            else if (line.substr(0, 4) == "KEY=") {
                licenseKey = line.substr(4);
            }
        }

        configFile.close();
    }
    else {
        cout << "Ошибка чтения конфигурационного файла." << endl;
        //return 1;
    }

    cout << "Имя файла базы данных: " << databaseFilename << endl;
    cout << "Лицензионный ключ: " << licenseKey << endl;

    // Загрузка базы данных из файла
    list<Ad> ads;
    ifstream databaseFile(databaseFilename, ios::binary);
    if (databaseFile.is_open()) {
        while (!databaseFile.eof()) {
            Ad ad;
            databaseFile.read(reinterpret_cast<char*>(&ad), sizeof(Ad));
            if (!databaseFile.eof()) {
                ads.push_back(ad);
            }
        }
        databaseFile.close();
        cout << "База данных загружена из файла." << endl;
    }
    else {
        cout << "Файл базы данных не найден. Создан новый файл." << endl;
    }

    int choice;
    do {
        cout << "--------------------------" << endl;
        cout << "Меню:" << endl;
        cout << "1. Добавить запись" << endl;
        cout << "2. Удалить запись" << endl;
        cout << "3. Вывести информацию обо всех объявлениях заданного города" << endl;
        cout << "4. Вывести информацию о объявлениях с ценой меньше заданной" << endl;
        cout << "5. Просмотреть все записи" << endl;
        cout << "6. Изменить запись" << endl;
        cout << "7. Сохранить базу данных в файл" << endl;
        cout << "8. Экспортировать базу данных в файл CSV" << endl;
        cout << "9. Изменить настройки" << endl;
        cout << "0. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
        case 1:
            addRecord(ads);
            break;
        case 2:
            int number;
            cout << "Введите номер записи для удаления: ";
            cin >> number;
            deleteRecord(ads, number);
            break;
        case 3:
           
            cout << "Введите город: ";
            getline(cin >> ws, city);
            printAdsByCity(ads, city);
            break;
        case 4:
            float maxCost;
            cout << "Введите максимальную стоимость: ";
            cin >> maxCost;
            printAdsByCost(ads, maxCost);
            break;
        case 5:
            viewRecords(ads);
            break;
        case 6:
            int editNumber;
            cout << "Введите номер записи для изменения: ";
            cin >> editNumber;
            editRecord(ads, editNumber);
            break;
        case 7:
            saveToFile(ads, databaseFilename);
            break;
        case 8:
            
            cout << "Введите имя файла для экспорта в формате CSV: ";
            cin >> exportFilename;
            exportToCSV(ads, exportFilename);
            break;
        case 9:
            changeSettings();
            break;
        case 0:
            break;
        default:
            cout << "Неверный выбор. Попробуйте еще раз." << endl;
        }
    } while (choice != 0);

    return 0;
}
