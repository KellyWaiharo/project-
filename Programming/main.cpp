#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits> // Add this line for numeric_limits

enum Gender { MALE, FEMALE };
enum ActivityType { SPORT, CLUB };

struct Club {
    std::string name;
    int capacity;
    int male_count;
    int female_count;
};

struct Sport {
    std::string name;
    int capacity;
    int male_count;
    int female_count;
};

struct Student {
    std::string firstname;
    std::string surname;
    Gender gender;
    int age;
    int bbit_group;
    std::vector<ActivityType> activities;
};

std::vector<Club> clubs;
std::vector<Sport> sports;
std::vector<Student> students;

void add_student(const std::string& firstname, const std::string& surname, Gender gender, int age, int bbit_group) {
    students.push_back({firstname, surname, gender, age, bbit_group, {}});
}

void add_club(const std::string& name, int capacity) {
    clubs.push_back({name, capacity, 0, 0});
}

void add_sport(const std::string& name, int capacity) {
    sports.push_back({name, capacity, 0, 0});
}

bool is_valid_club_allocation(const Club& club) {
    return club.male_count <= club.capacity / 2 && club.female_count <= club.capacity / 2;
}

bool is_valid_sport_allocation(const Sport& sport) {
    return sport.male_count <= sport.capacity * 3 / 4 && sport.female_count <= sport.capacity / 4;
}

void allocate_activity(Student& student, Club& club) {
    if (club.male_count + club.female_count < club.capacity) {
        club.male_count += student.gender == Gender::MALE ? 1 : 0;
        club.female_count += student.gender == Gender::FEMALE ? 1 : 0;
        student.activities.push_back(ActivityType::CLUB);
    }
}

void allocate_activity(Student& student, Sport& sport) {
    if (sport.male_count + sport.female_count < sport.capacity) {
        sport.male_count += student.gender == Gender::MALE ? 1 : 0;
        sport.female_count += student.gender == Gender::FEMALE ? 1 : 0;
        student.activities.push_back(ActivityType::SPORT);
    }
}

void allocate_activity(Student& student) {
    if (student.activities.size() < 1) {
        for (auto& club : clubs) { // Change const auto& to auto&
            if (club.capacity > 0 && is_valid_club_allocation(club)) {
                allocate_activity(student, club);
                break;
            }
        }
    }
}




void allocate_activities(Student& student) {
    if (student.activities.size() < 2) {
        for (auto& sport : sports) { // Change const auto& to auto&
            if (sport.capacity > 0 && is_valid_sport_allocation(sport)) {
                allocate_activity(student, sport);
                break;
            }
        }
    }
}


void print_menu() {
    std::cout << "1. Add Student\n"
              << "2. View Students (ALL and per group) \n"
              << "3. View Clubs/ Societies \n"
              << "4. View Sports \n"
              << "5. View Grouped Students \n"
              << "6. Save all Files \n"
              << "7. Exit \n";
}

void print_students(const std::vector<Student>& students) {
    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << "Student " << i + 1 << ":\n"
                  << "Firstname: " << students[i].firstname << "\n"
                  << "Surname: " << students[i].surname << "\n"
                  << "Gender: " << (students[i].gender == Gender::MALE ? "Male" : "Female") << "\n"
                  << "Age: " << students[i].age << "\n"
                  << "BBIT Group: " << students[i].bbit_group << "\n"
                  << "Activities: ";
        for (const auto& activity : students[i].activities) {
            std::cout << (activity == ActivityType::CLUB ? "Club" : "Sport") << " ";
        }
        std::cout << "\n\n";
    }
}

void print_clubs(const std::vector<Club>& clubs) {
    for (size_t i = 0; i < clubs.size(); ++i) {
        std::cout << "Club " << i + 1 << ":\n"
                  << "Name: " << clubs[i].name << "\n"
                  << "Capacity: " << clubs[i].capacity << "\n"
                  << "Male Count: " << clubs[i].male_count << "\n"
                  << "Female Count: " << clubs[i].female_count << "\n\n";
    }
}

void print_sports(const std::vector<Sport>& sports) {
    for (size_t i = 0; i < sports.size(); ++i) {
        std::cout << "Sport " << i + 1 << ":\n"
                  << "Name: " << sports[i].name << "\n"
                  << "Capacity: " << sports[i].capacity << "\n"
                  << "Male Count: " << sports[i].male_count << "\n"
                  << "Female Count: " << sports[i].female_count << "\n\n";
    }
}

void save_data(const std::vector<Student>& students, const std::vector<Club>& clubs, const std::vector<Sport>& sports) {
    std::ofstream file("data.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file for writing.\n";
        return;
    }

    file << "Firstname,Surname,Gender,Age,BBIT Group,Activities\n";
    for (const auto& student : students) {
        file << student.firstname << "," << student.surname << ","
             << (student.gender == Gender::MALE ? "Male" : "Female") << "," << student.age << ","
             << student.bbit_group << ",";
        for (const auto& activity : student.activities) {
            file << (activity == ActivityType::CLUB ? "Club" : "Sport") << " ";
        }
        file << "\n";
    }

    file << "Club Name,Capacity,Male Count,Female Count\n";
    for (const auto& club : clubs) {
        file << club.name << "," << club.capacity << "," << club.male_count << "," << club.female_count << "\n";
    }

    file << "Sport Name,Capacity,Male Count,Female Count\n";
    for (const auto& sport : sports) {
        file << sport.name << "," << sport.capacity << "," << sport.male_count << "," << sport.female_count << "\n";
    }

    file.close();
    std::cout << "Data saved successfully.\n";
}

int main() {
    add_club("Journalism Club", 60);
    add_club("Red Cross Society", 60);
    add_club("AISEC", 60);
    add_club("Business Club", 60);
    add_club("Computer Science Club", 60);
    add_sport("Rugby", 20);
    add_sport("Athletics", 20);
    add_sport("Swimming", 20);
    add_sport("Soccer", 20);

    add_student("John", "Doe", Gender::MALE, 18, 1);
    add_student("Jane", "Doe", Gender::FEMALE, 18, 1);
    add_student("Mike", "Smith", Gender::MALE, 18, 2);
    add_student("Emma", "Johnson", Gender::FEMALE, 18, 2);
    add_student("Tom", "Brown", Gender::MALE, 18, 3);
    add_student("Lucy", "Davis", Gender::FEMALE, 18, 3);

    allocate_activities(students[0]);
    allocate_activities(students[1]);
    allocate_activities(students[2]);
    allocate_activities(students[3]);
    allocate_activities(students[4]);

    print_menu();
    int choice;
    std::cin >> choice;

    while (choice != 7) {
        switch (choice) {
            case 1: {
                std::string firstname, surname;
                int age, bbit_group;
                Gender gender;
                std::cout << "Enter firstname: ";
                std::cin >> firstname;
                std::cout << "Enter surname: ";
                std::cin >> surname;
                std::cout << "Enter age: ";
                std::cin >> age;

                // Clear the input buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Enter BBIT group: ";
                std::cin >> bbit_group;
                std::cout << "Enter gender (MALE/FEMALE): ";
                char gender_char;
                std::cin >> gender_char;
                gender = (gender_char == 'M' ? Gender::MALE : Gender::FEMALE);
                add_student(firstname, surname, gender, age, bbit_group);
                break;
            }


            case 2: {
                print_students(students);
                break;
            }
            case 3: {
                print_clubs(clubs);
                break;
            }
            case 4: {
                print_sports(sports);
                break;
            }
            case 5: {
                for (size_t i = 0; i < students.size(); ++i) {
                    std::cout << "Student " << i + 1 << ":\n"
                              << "Firstname: " << students[i].firstname << "\n"
                              << "Surname: " << students[i].surname << "\n"
                              << "Gender: " << (students[i].gender == Gender::MALE ? "Male" : "Female") << "\n"
                              << "Age: " << students[i].age << "\n"
                              << "BBIT Group: " << students[i].bbit_group << "\n"
                              << "Activities: ";
                    for (const auto& activity : students[i].activities) {
                        std::cout << (activity == ActivityType::CLUB ? "Club" : "Sport") << " ";
                    }
                    std::cout << "\n\n";
                }
                break;
            }
            case 6: {
                save_data(students, clubs, sports);
                break;
            }
            default: {
                std::cout << "Invalid choice. Please try again.\n";
                break;
            }
        }

        std::cin >> choice;}

return 0;
}
