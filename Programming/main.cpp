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

