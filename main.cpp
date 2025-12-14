#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>

class Student {
public:
    Student() = default;
    Student(int id, std::string name, int age, float score)
        : id_(id), name_(std::move(name)), age_(age), score_(score) {}

    void inputFromUser() {
        std::cout << "学号: ";
        std::cin >> id_;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "姓名: ";
        std::getline(std::cin, name_);

        std::cout << "年龄: ";
        std::cin >> age_;

        std::cout << "成绩: ";
        std::cin >> score_;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    void display() const {
        std::cout << "学号: " << id_ << ", 姓名: " << name_ << ", 年龄: " << age_ << ", 成绩: " << score_ << '\n';
    }

    void writeToStream(std::ostream &out) const {
        out.write(reinterpret_cast<const char *>(&id_), sizeof(id_));
        std::size_t nameSize = name_.size();
        out.write(reinterpret_cast<const char *>(&nameSize), sizeof(nameSize));
        out.write(name_.data(), static_cast<std::streamsize>(nameSize));
        out.write(reinterpret_cast<const char *>(&age_), sizeof(age_));
        out.write(reinterpret_cast<const char *>(&score_), sizeof(score_));
    }

    static bool readFromStream(std::istream &in, Student &student) {
        if (!in.read(reinterpret_cast<char *>(&student.id_), sizeof(student.id_))) {
            return false;
        }

        std::size_t nameSize = 0;
        if (!in.read(reinterpret_cast<char *>(&nameSize), sizeof(nameSize))) {
            return false;
        }

        std::string buffer(nameSize, '\0');
        if (nameSize > 0) {
            if (!in.read(&buffer[0], static_cast<std::streamsize>(nameSize))) {
                return false;
            }
        }
        student.name_.swap(buffer);

        if (!in.read(reinterpret_cast<char *>(&student.age_), sizeof(student.age_))) {
            return false;
        }

        if (!in.read(reinterpret_cast<char *>(&student.score_), sizeof(student.score_))) {
            return false;
        }

        return true;
    }

    int id() const { return id_; }

private:
    int id_{};
    std::string name_;
    int age_{};
    float score_{};
};

class StudentManager {
public:
    explicit StudentManager(std::string filePath) : filePath_(std::move(filePath)) {}

    void addStudent() {
        Student student;
        student.inputFromUser();

        std::ofstream out(filePath_, std::ios::binary | std::ios::app);
        if (!out) {
            std::cerr << "无法打开文件进行写入。\n";
            return;
        }

        student.writeToStream(out);
        std::cout << "学生信息已保存。\n";
    }

    void deleteStudent() {
        std::cout << "输入要删除的学生学号: ";
        int targetId = 0;
        std::cin >> targetId;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        auto students = loadAll();
        auto it = std::remove_if(students.begin(), students.end(), [targetId](const Student &s) {
            return s.id() == targetId;
        });

        if (it == students.end()) {
            std::cout << "未找到该学号的学生。\n";
            return;
        }

        students.erase(it, students.end());
        rewriteAll(students);
        std::cout << "删除成功。\n";
    }

    void showAll() {
        auto students = loadAll();
        if (students.empty()) {
            std::cout << "没有学生信息。\n";
            return;
        }

        std::cout << "当前学生信息：\n";
        for (const auto &student : students) {
            student.display();
        }
    }

private:
    std::vector<Student> loadAll() const {
        std::vector<Student> students;
        std::ifstream in(filePath_, std::ios::binary);
        if (!in) {
            return students;
        }

        while (true) {
            Student student;
            if (!Student::readFromStream(in, student)) {
                break;
            }
            students.push_back(std::move(student));
        }
        return students;
    }

    void rewriteAll(const std::vector<Student> &students) {
        std::ofstream out(filePath_, std::ios::binary | std::ios::trunc);
        if (!out) {
            std::cerr << "无法打开文件进行覆盖写入。\n";
            return;
        }
        for (const auto &student : students) {
            student.writeToStream(out);
        }
    }

    std::string filePath_;
};

void printMenu() {
    std::cout << "\n===== 学生信息管理系统 =====\n";
    std::cout << "A - 添加学生\n";
    std::cout << "D - 删除学生\n";
    std::cout << "S - 显示所有学生\n";
    std::cout << "Q - 退出程序\n";
    std::cout << "请选择操作: ";
}

int main() {
    StudentManager manager("students.dat");
    char command = '\0';

    while (true) {
        printMenu();
        if (!(std::cin >> command)) {
            break;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (std::toupper(command)) {
        case 'A':
            manager.addStudent();
            break;
        case 'D':
            manager.deleteStudent();
            break;
        case 'S':
            manager.showAll();
            break;
        case 'Q':
            std::cout << "程序结束。\n";
            return 0;
        default:
            std::cout << "无效指令，请重新输入。\n";
            break;
        }
    }

    return 0;
}
