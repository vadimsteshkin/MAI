#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include <iomanip>
#include <chrono>

struct Lesson {
    std::string faculty;
    std::string department;
    std::string group;
    std::string subject;
    std::string classroom;
    std::string date;
    std::string time;
    std::string teacher;
    int ordinalDay;
    int minutesFromMidnight;
    int dayOfWeek;
    Lesson* next;

    Lesson() : ordinalDay(-1), minutesFromMidnight(-1), dayOfWeek(-1), next(nullptr) {}
};

class Schedule {
private:
    Lesson* head;

public:
    Schedule() : head(nullptr) {}

    int convertDateToOrdinalDay(const std::string& date) {
        try {
            std::tm timeinfo = { 0 };
            std::istringstream ss(date);
            ss >> std::get_time(&timeinfo, "%d.%m.%Y");

            if (ss.fail()) {
                throw std::runtime_error("Ошибка при разборе даты.");
            }

            std::chrono::system_clock::time_point tp = std::chrono::system_clock::from_time_t(std::mktime(&timeinfo));
            auto duration = tp.time_since_epoch();
            auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);

            return hours.count() / 24 + 1;
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка при разборе даты: " << e.what() << std::endl;
            return -1;
        }
    }

    int convertTimeToMinutes(const std::string& time) {
        try {
            std::tm timeinfo = { 0 };
            std::istringstream ss(time);
            ss >> std::get_time(&timeinfo, "%H:%M");

            if (ss.fail()) {
                throw std::runtime_error("Ошибка при разборе времени.");
            }

            int minutes = timeinfo.tm_hour * 60 + timeinfo.tm_min;
            if (minutes >= 0) {
                return minutes;
            }
            else {
                throw std::runtime_error("Отрицательное значение минут");
            }
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка при разборе времени: " << e.what() << std::endl;
            return -1;
        }
    }

    int convertDateToDayOfWeek(const std::string& date) {
        try {
            std::tm timeinfo = { 0 };
            std::istringstream ss(date);
            ss >> std::get_time(&timeinfo, "%d.%m.%Y");

            if (ss.fail()) {
                throw std::runtime_error("Ошибка при разборе даты.");
            }

            // Добавим коррекцию на 1, чтобы учесть, что воскресенье - 1, понедельник - 2 и так далее
            return (timeinfo.tm_wday + 1) % 7;
        }
        catch (const std::exception& e) {
            std::cerr << "Ошибка при разборе даты: " << e.what() << std::endl;
            return -1;
        }
    }



    Lesson* findLessonByDateTime(const std::string& dateTime) {
        Lesson* current = head;
        while (current) {
            if (current->date + " " + current->time == dateTime) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    void addLesson(const Lesson& lesson) {
        Lesson* newLesson = new Lesson(lesson);
        newLesson->ordinalDay = convertDateToOrdinalDay(lesson.date);
        newLesson->minutesFromMidnight = convertTimeToMinutes(lesson.time);
        newLesson->dayOfWeek = convertDateToDayOfWeek(lesson.date);

        if (!head) {
            // Если список пуст, делаем новый урок единственным в списке
            newLesson->next = newLesson;  // Ссылка на самого себя
            head = newLesson;
        }
        else {
            // Вставляем новый урок в кольцевой список
            Lesson* current = head;
            while (current->next != head &&
                (newLesson->ordinalDay > current->next->ordinalDay ||
                    (newLesson->ordinalDay == current->next->ordinalDay &&
                        newLesson->minutesFromMidnight > current->next->minutesFromMidnight))) {
                current = current->next;
            }
            newLesson->next = current->next;
            current->next = newLesson;
        }
    }

    void printFullSchedule() {
        Lesson* current = head;

        if (!current) {
            std::cout << "Расписание пусто.\n";
            return;
        }

        Lesson* start = current; // Запоминаем начальный узел

        do {
            std::cout << "Факультет: " << current->faculty << "\n"
                << "Кафедра: " << current->department << "\n"
                << "Группа: " << current->group << "\n"
                << "Предмет: " << current->subject << "\n"
                << "Аудитория: " << current->classroom << "\n"
                << "Дата: " << current->date << "\n"
                << "Время: " << current->time << "\n"
                << "Преподаватель: " << current->teacher << "\n"
                << "День недели: " << current->dayOfWeek << "\n\n";

            current = current->next;
        } while (current != nullptr && current != start); // Проверка на повторное посещение узла

        if (!head) {
            std::cout << "Расписание пусто.\n";
        }
    }


    void findScheduleByTeacher(const std::string& teacherName) {
        Lesson* current = head;

        if (!current) {
            std::cout << "Расписание пусто.\n";
            return;
        }

        do {
            if (current->teacher == teacherName) {
                std::cout << "Факультет: " << current->faculty << "\n"
                    << "Кафедра: " << current->department << "\n"
                    << "Группа: " << current->group << "\n"
                    << "Предмет: " << current->subject << "\n"
                    << "Аудитория: " << current->classroom << "\n"
                    << "Дата: " << current->date << "\n"
                    << "Время: " << current->time << "\n"
                    << "Лектор: " << current->teacher << "\n"
                    << "День недели: " << current->dayOfWeek << "\n\n";
            }

            current = current->next;
        } while (current != nullptr);
    }
  
    void findScheduleByGroup(const std::string& groupName) {
        Lesson* current = head;

        if (!current) {
            std::cout << "Расписание пусто.\n";
            return;
        }

        do {
            if (current->group == groupName) {
                std::cout << "Факультет: " << current->faculty << "\n"
                    << "Кафедра: " << current->department << "\n"
                    << "Группа: " << current->group << "\n"
                    << "Предмет: " << current->subject << "\n"
                    << "Аудитория: " << current->classroom << "\n"
                    << "Дата: " << current->date << "\n"
                    << "Время: " << current->time << "\n"
                    << "Преподаватель: " << current->teacher << "\n"
                    << "День недели: " << current->dayOfWeek << "\n\n";
            }

            current = current->next;
        } while (current != nullptr);
    }
    void findAvailableClassrooms(const std::string& date, const std::string& time) {
        Lesson* current = head;

        if (!current) {
            std::cout << "Расписание пусто.\n";
            return;
        }

        int targetOrdinalDay = convertDateToOrdinalDay(date);
        int targetMinutesFromMidnight = convertTimeToMinutes(time);
        int targetDayOfWeek = convertDateToDayOfWeek(date);

        std::vector<std::string> occupiedClassrooms;

        do {
            if (current->date == date && current->time == time) {
                occupiedClassrooms.push_back(current->classroom);
            }

            current = current->next;
        } while (current != nullptr);

        std::cout << "Свободные аудитории:\n";
        
        const int totalClassrooms = 10;

        for (int i = 1; i <= totalClassrooms; ++i) {
            std::string classroomName = "Ауд." + std::to_string(i);
            auto it = std::find(occupiedClassrooms.begin(), occupiedClassrooms.end(), classroomName);

            if (it == occupiedClassrooms.end()) {
                std::cout << classroomName << "\n";
            }
        }
    }
   


    void findScheduleByDay(const std::string& date) {
        Lesson* current = head;

        if (!current) {
            std::cout << "Расписание пусто.\n";
            return;
        }

        do {
            if (current->date == date) {
                std::cout << "Факультет: " << current->faculty << "\n"
                    << "Кафедра: " << current->department << "\n"
                    << "Группа: " << current->group << "\n"
                    << "Предмет: " << current->subject << "\n"
                    << "Аудитория: " << current->classroom << "\n"
                    << "Дата: " << current->date << "\n"
                    << "Время: " << current->time << "\n"
                    << "Преподаватель: " << current->teacher << "\n"
                    << "День недели: " << current->dayOfWeek << "\n\n";
            }

            current = current->next;
        } while (current != nullptr);
    }

   
    void findNextLesson() {
        Lesson* current = head;

        if (!current) {
            std::cout << "Расписание пусто.\n";
            return;
        }

        auto now = std::chrono::system_clock::now();
        auto nowDuration = now.time_since_epoch();
        auto nowHours = std::chrono::duration_cast<std::chrono::hours>(nowDuration);

        int currentMinutesFromMidnight = nowHours.count() % (24 * 60);

        do {
            if (current->ordinalDay > convertDateToOrdinalDay(current->date) ||
                (current->ordinalDay == convertDateToOrdinalDay(current->date) &&
                    current->minutesFromMidnight > currentMinutesFromMidnight)) {
                std::cout << "Следующий урок:\n"
                    << "Факультет: " << current->faculty << "\n"
                    << "Кафедра: " << current->department << "\n"
                    << "Группа: " << current->group << "\n"
                    << "Предмет: " << current->subject << "\n"
                    << "Аудитория: " << current->classroom << "\n"
                    << "Дата: " << current->date << "\n"
                    << "Время: " << current->time << "\n"
                    << "Преподаватель: " << current->teacher << "\n"
                    << "День недели: " << current->dayOfWeek << "\n\n";
                return;
            }

            current = current->next;
        } while (current != nullptr);
    }

    void updateLessonDetails(const std::string& oldTeacher, const Lesson& newLesson) {
        Lesson* current = head;

        while (current != nullptr) {
            if (current->teacher == oldTeacher) {
                current->faculty = newLesson.faculty;
                current->department = newLesson.department;
                current->group = newLesson.group;
                current->subject = newLesson.subject;
                current->classroom = newLesson.classroom;
                current->date = newLesson.date;
                current->time = newLesson.time;
                current->teacher = newLesson.teacher;

                current->ordinalDay = convertDateToOrdinalDay(newLesson.date);
                current->minutesFromMidnight = convertTimeToMinutes(newLesson.time);
                current->dayOfWeek = convertDateToDayOfWeek(newLesson.date);

                std::cout << "Данные урока обновлены.\n";
                return;
            }

            current = current->next;
        }

        std::cout << "Урок с преподавателем " << oldTeacher << " не найден.\n";
    }


    void saveScheduleToFile(const std::string& filename) {
        std::ofstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла.\n";
            return;
        }

        Lesson* current = head;

        while (current != nullptr) {
            file << current->faculty << "," << current->department << "," << current->group << ","
                << current->subject << "," << current->classroom << "," << current->date << ","
                << current->time << "," << current->teacher << "\n";

            current = current->next;
        }

        file.close();
        std::cout << "Расписание сохранено в файле " << filename << ".\n";
    }

    
    void clearSchedule() {
        Lesson* current = head;
        Lesson* next = nullptr;

        while (current != nullptr) {
            next = current->next;
            delete current;
            current = next;
        }

        head = nullptr;
        std::cout << "Расписание очищено.\n";
    }

   
    void calculateWeeklyWorkload(const std::string& teacherName) {
        Lesson* current = head;
        int totalHours = 0;

        while (current != nullptr) {
            if (current->teacher == teacherName) {
                totalHours++;
            }

            current = current->next;
        }

        std::cout << "Общая недельная нагрузка для преподавателя " << teacherName << ": "
            << totalHours << " часов.\n";
    }

    
    void displayMenu() {
        int choice;

        do {
            std::cout << "Выберите действие:\n"
                << "1. Показать полное расписание\n"
                << "2. Найти расписание по группе\n"
                << "3. Найти расписание по дате\n"
                << "4. Найти следующий урок\n"
                << "5. Обновить данные урока\n"
                << "6. Сохранить расписание в файл\n"
                << "7. Очистить расписание\n"
                << "8. Рассчитать недельную нагрузку преподавателя\n"
                << "0. Выйти\n";

            std::cout << "Ваш выбор: ";
            std::cin >> choice;

            switch (choice) {
            case 1:
                printFullSchedule();
                break;
            case 2: {
                std::string groupName;
                std::cout << "Введите название группы: ";
                std::cin >> groupName;
                findScheduleByGroup(groupName);
                break;
            }
            case 3: {
                std::string date;
                std::cout << "Введите дату (в формате DD.MM.YYYY): ";
                std::cin >> date;
                findScheduleByDay(date);
                break;
            }
            case 4:
                findNextLesson();
                break;
            case 5: {
                std::string oldTeacher;
                std::cout << "Введите имя текущего преподавателя: ";
                std::cin >> oldTeacher;

                Lesson newLesson;
                std::cout << "Введите новые данные урока:\n";
             

                updateLessonDetails(oldTeacher, newLesson);
                break;
            }
            case 6: {
                std::string filename;
                std::cout << "Введите имя файла для сохранения расписания: ";
                std::cin >> filename;
                saveScheduleToFile(filename);
                break;
            }
            case 7:
                clearSchedule();
                break;
            case 8: {
                std::string teacherName;
                std::cout << "Введите имя преподавателя: ";
                std::cin >> teacherName;
                calculateWeeklyWorkload(teacherName);
                break;
            }
            case 0:
                std::cout << "Программа завершена.\n";
                break;
            default:
                std::cout << "Некорректный выбор. Пожалуйста, выберите снова.\n";
            }

        } while (choice != 0);
    }

    void removeLesson(const std::string& faculty, const std::string& department, const std::string& group,
        const std::string& subject, const std::string& classroom, const std::string& date,
        const std::string& time, const std::string& teacher) {
        if (!head) {
            std::cout << "Расписание пусто.\n";
            return;
        }

        Lesson* current = head;
        Lesson* prev = nullptr;

        while (current != nullptr &&
            (current->faculty != faculty ||
                current->department != department ||
                current->group != group ||
                current->subject != subject ||
                current->classroom != classroom ||
                current->date != date ||
                current->time != time ||
                current->teacher != teacher)) {
            prev = current;
            current = current->next;
        }

        if (current == nullptr) {
            std::cout << "Урок не найден.\n";
            return;
        }

        if (prev == nullptr) {
            head = current->next;
        }
        else {
            prev->next = current->next;
        }

        delete current;
        std::cout << "Урок удален.\n";
    }
    void readLessonFromCSV(const std::string& line, Lesson& lesson) {
        std::istringstream iss(line);
        std::getline(iss, lesson.faculty, ',');
        std::getline(iss, lesson.department, ',');
        std::getline(iss, lesson.group, ',');
        std::getline(iss, lesson.subject, ',');
        std::getline(iss, lesson.classroom, ',');
        std::getline(iss, lesson.date, ',');
        std::getline(iss, lesson.time, ',');
        std::getline(iss, lesson.teacher);
    }


    void readScheduleFromFile(const std::string& filename) {
        std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Ошибка открытия файла.\n";
            return;
        }

        Lesson lesson;
        std::string line;

        while (std::getline(file, line)) {
            readLessonFromCSV(line, lesson);
            addLesson(lesson);
        }

        file.close();
    }

};

int main() {
    system("chcp 1251");
    
    Schedule schedule;
    schedule.readScheduleFromFile("schedule.csv");

    std::cout << "Полное расписание на 18 недель:\n";
    schedule.printFullSchedule();

    schedule.findScheduleByTeacher("Сидоров");
    schedule.findScheduleByGroup("ПОИТ-21");
    schedule.findAvailableClassrooms("03.12.2023", "12:00");


    schedule.removeLesson("ФИТ", "ПОИТ", "ПОИТ-21", "Web-технологии", "Ауд.303", "03.12.2023", "12:00", "Сидоров");

    std::cout << "Обновленное расписание:\n";
    schedule.printFullSchedule();

    return 0;
}
