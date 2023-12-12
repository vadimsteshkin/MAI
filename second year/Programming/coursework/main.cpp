#include <iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>

using namespace std;

struct Lecture {
    string faculty;
    string department;
    string group;
    string subject;
    string classroom;
    string dateAndTime;
    string lecturer;
    int weekNumber;
    Lecture* next;

    Lecture(string fac, string dept, string grp, string subj,
            string room, string dateTime, string lec, int week)
        : faculty(fac), department(dept), group(grp), subject(subj),
          classroom(room), dateAndTime(dateTime), lecturer(lec), weekNumber(week), next(nullptr) {}
};

class Schedule {
private:
    Lecture* head;

public:
    Schedule() : head(nullptr) {}

    void addLectureToWeek(const Lecture& lecture) {
        Lecture* newLecture = new Lecture(lecture);
        if (!head) {
            head = newLecture;
            newLecture->next = newLecture;
        } else {
            Lecture* current = head;
            while (current->next != head) {
                current = current->next;
            }
            current->next = newLecture;
            newLecture->next = head;
        }
    }

    void findLecturesInWeek(const string& dateTime, int weekNumber) {
        if (!head) {
            cout << "Расписание пусто.\n";
            return;
        }

        Lecture* current = head;
        do {
            if (current->dateAndTime == dateTime && current->weekNumber == weekNumber) {
                cout << "Найдено занятие:\n"
                     << "Факультет: " << current->faculty << "\n"
                     << "Кафедра: " << current->department << "\n"
                     << "Группа: " << current->group << "\n"
                     << "Предмет: " << current->subject << "\n"
                     << "Аудитория: " << current->classroom << "\n"
                     << "Дата и время: " << current->dateAndTime << "\n"
                     << "Преподаватель: " << current->lecturer << "\n"
                     << "Неделя: " << current->weekNumber << "\n\n";
                return;
            }
            current = current->next;
        } while (current != head);

        cout << "Занятие не найдено для указанной даты, времени и номера недели.\n";
    }

    void displaySchedule() {
        if (!head) {
            cout << "Расписание пусто.\n";
            return;
        }

        Lecture* current = head;
        do {
            cout << "Факультет: " << current->faculty << "\n"
                 << "Кафедра: " << current->department << "\n"
                 << "Группа: " << current->group << "\n"
                 << "Предмет: " << current->subject << "\n"
                 << "Аудитория: " << current->classroom << "\n"
                 << "Дата и время: " << current->dateAndTime << "\n"
                 << "Преподаватель: " << current->lecturer << "\n"
                 << "Неделя: " << current->weekNumber << "\n\n";
            current = current->next;
        } while (current != head);
    }

    void addLectureFromUserInput() {
        string faculty, department, group, subject, classroom, dateAndTime, lecturer;
        int weekNumber;

        cout << "Введите факультет: ";
        cin >> faculty;
        cout << "Введите кафедру: ";
        cin >> department;
        cout << "Введите группу: ";
        cin >> group;
        cout << "Введите предмет: ";
        cin >> subject;
        cout << "Введите аудиторию: ";
        cin >> classroom;
        cout << "Введите дату и время (например, 2023-11-19 10:00): ";
        cin.ignore(); // Игнорируем символ новой строки после предыдущего ввода
        getline(cin, dateAndTime);
        cout << "Введите преподавателя: ";
        getline(cin, lecturer);
        cout << "Введите номер недели: ";
        cin >> weekNumber;

        addLectureToWeek({faculty, department, group, subject, classroom, dateAndTime, lecturer, weekNumber});
    }

    // Метод для загрузки занятий из базы данных MySQL
    void loadFromDatabase(const string& host, const string& user, const string& password, const string& database) {
        try {
            sql::mysql::MySQL_Driver* driver = sql::mysql::get_mysql_driver_instance();
            std::unique_ptr<sql::Connection> con(driver->connect(host, user, password));
            con->setSchema(database);

            std::unique_ptr<sql::Statement> stmt(con->createStatement());
            std::unique_ptr<sql::ResultSet> res(stmt->executeQuery("SELECT * FROM lectures"));

            while (res->next()) {
                string faculty = res->getString("faculty");
                string department = res->getString("department");
                string group = res->getString("group");
                string subject = res->getString("subject");
                string classroom = res->getString("classroom");
                string dateAndTime = res->getString("date_and_time");
                string lecturer = res->getString("lecturer");
                int weekNumber = res->getInt("week_number");

                addLectureToWeek({faculty, department, group, subject, classroom, dateAndTime, lecturer, weekNumber});
            }
        } catch (sql::SQLException& e) {
            cout << "# ERR: SQLException in " << __FILE__;
            cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
            cout << "# ERR: " << e.what();
            cout << " (MySQL error code: " << e.getErrorCode();
            cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        }
    }

    // Метод для отображения текстового меню
    void displayMenu() {
        int choice;
        do {
            cout << "===== Меню =====\n";
            cout << "1. Добавить занятие\n";
            cout << "2. Отобразить расписание\n";
            cout << "3. Поиск занятия\n";
            cout << "0. Выход\n";
            cout << "Выберите опцию: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    addLectureFromUserInput();
                    break;
                case 2:
                    displaySchedule();
                    break;
                case 3:
                    searchLectureMenu();
                    break;
                case 0:
                    cout << "До свидания!\n";
                    break;
                default:
                    cout << "Неверный ввод. Попробуйте еще раз.\n";
            }
        } while (choice != 0);
    }

    // Метод для отображения подменю для поиска занятия
    void searchLectureMenu() {
        string dateTime;
        int weekNumber;

        cout << "Введите дату и время для поиска (например, 2023-11-19 10:00): ";
        cin.ignore();
        getline(cin, dateTime);
        cout << "Введите номер недели для поиска: ";
        cin >> weekNumber;

        findLecturesInWeek(dateTime, weekNumber);
    }
};

int main() {
    Schedule schedule;

    // Загружаем занятия из базы данных MySQL
    schedule.loadFromDatabase("your_host", "your_user", "your_password", "your_database");

    // Отображаем текстовое меню
    schedule.displayMenu();

    return 0;
}
