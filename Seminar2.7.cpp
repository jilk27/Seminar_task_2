// Seminar2.7.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <string>

class VirtualThread {
private:
    std::vector<std::string> tasks;
    size_t currentIndex;

public:
    VirtualThread(std::initializer_list<std::string> taskList)
        : tasks(taskList), currentIndex(0) {
    }

    bool hasNext() const {
        return currentIndex < tasks.size();
    }

    void runNextTask(int threadId) {
        if (!hasNext()) return;

        std::string task = tasks[currentIndex];

        std::cout << "Thread " << threadId
            << " start " << task << std::endl;

        std::cout << "Thread " << threadId
            << " over " << task << std::endl;

        currentIndex++;
    }
};

class HyperThreadingSimulator {
private:
    VirtualThread thread1;
    VirtualThread thread2;

public:
    HyperThreadingSimulator()
        : thread1({ "Task A", "Task C" }),
        thread2({ "Task B", "Task D" }) {
    }

    void execute() {
        bool running = true;

        while (running) {
            running = false;

            if (thread1.hasNext()) {
                thread1.runNextTask(1);
                running = true;
            }

            if (thread2.hasNext()) {
                thread2.runNextTask(2);
                running = true;
            }
        }
    }
};

int main() {
    HyperThreadingSimulator simulator;
    simulator.execute();

    return 0;
}
