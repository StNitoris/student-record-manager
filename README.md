# Student Information Manager

This project provides a simple C++ console program for managing student records stored in a binary file using an object-oriented design.

## Build
Compile with any C++17 compiler, for example:

```bash
g++ -std=c++17 -Wall -Wextra -pedantic -o student_manager main.cpp
```

## Usage
Run the compiled program and choose one of the following commands when prompted:

- `A`：输入学号、姓名、年龄、成绩后将学生追加到 `students.dat` 二进制文件。
- `D`：输入学号后删除对应学生记录，并重写文件。
- `S`：读取文件并显示所有已保存学生信息。
- `Q`：退出程序。

The program stores data in `students.dat` in the working directory. If the file does not exist, it will be created when you add the first student.
