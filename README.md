# Student Information Manager

This project provides a simple C++ console program for managing student records stored in a binary file using an object-oriented design.

## 环境准备
- 需要支持 **C++11 或 C++14** 的编译器，例如 Linux/macOS 上的 `g++`（来自 GCC 5+）或 Windows 上的 **MSYS2 MinGW** / **WSL** 中的 `g++`。
- 确保编译器在终端可用：`g++ --version` 应能输出版本信息。如果命令不存在，请先安装编译器（如 Debian/Ubuntu: `sudo apt-get install g++`).

## 编译步骤
1. 打开终端切换到本项目目录（包含 `main.cpp` 的文件夹）：
   ```bash
   cd /path/to/Assignment
   ```
2. 运行编译命令生成可执行文件 `student_manager`：
   ```bash
   g++ -std=c++14 -Wall -Wextra -pedantic -o student_manager main.cpp
   ```
   - 如果在 Windows PowerShell 中使用 MSYS2 MinGW，请先启动 "MSYS2 MinGW 64-bit" 终端再执行上述命令。
3. 成功后当前目录会出现 `student_manager`（Windows 下可能显示为 `student_manager.exe`）。

## 运行
1. 在编译生成的目录下执行程序：
   ```bash
   ./student_manager
   ```
   - Windows 下如果是 PowerShell，请使用 `./student_manager.exe`。
2. 程序启动后按提示输入下列命令：
   - `A`：输入学号、姓名、年龄、成绩后将学生追加到 `students.dat` 二进制文件。
   - `D`：输入学号后删除对应学生记录，并重写文件。
   - `S`：读取文件并显示所有已保存学生信息。
   - `Q`：退出程序。

数据保存在工作目录的 `students.dat` 文件中，若文件不存在，首次添加学生时会自动创建。
