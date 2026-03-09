#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <chrono>
#include <thread>
#include <algorithm>

class Task {
public:
    int value;
    int priority;
    int duration_ms;
    int steps;
    int currentStep;
    std::string name;

    Task(int val, int prio, int dur, int st, const std::string& taskName)
        : value(val), priority(prio), duration_ms(dur), steps(st), currentStep(0), name(taskName) {
    }

    bool isCompleted() const {
        return currentStep >= steps;
    }

    int getCurrentResult() const {
        double progress = static_cast<double>(currentStep) / steps;
        return static_cast<int>(value * value * progress);
    }
};

class VirtualThread {
private:
    std::vector<Task> tasks;
    std::mt19937 gen;

public:
    VirtualThread(unsigned int seed) : gen(seed) {}

    void addTask(const Task& task) {
        tasks.push_back(task);
    }

    bool hasTasks() const {
        return !tasks.empty();
    }

    Task* getHighestPriorityTask() {
        if (tasks.empty()) return nullptr;

        auto highestPrio = std::max_element(tasks.begin(), tasks.end(),
            [](const Task& a, const Task& b) {
                return a.priority < b.priority;
            });

        return &(*highestPrio);
    }

    void runStep(int threadId) {
        if (!hasTasks()) return;

        Task* currentTask = getHighestPriorityTask();

        int stepDuration = currentTask->duration_ms / currentTask->steps;
        std::this_thread::sleep_for(std::chrono::milliseconds(stepDuration));

        currentTask->currentStep++;
        int result = currentTask->getCurrentResult();

        std::cout << "Virtual Thread " << threadId
            << " | Step " << currentTask->currentStep << "/" << currentTask->steps
            << " | Task: " << currentTask->name
            << " | Value: " << currentTask->value
            << " | Priority: " << currentTask->priority
            << " | Result: " << result << std::endl;

        if (currentTask->isCompleted()) {
            tasks.erase(std::remove_if(tasks.begin(), tasks.end(),
                [currentTask](const Task& t) { return &t == currentTask; }),
                tasks.end());
        }
    }
};

class HyperThreadingSimulator {
private:
    VirtualThread a;
    VirtualThread b;

public:
    HyperThreadingSimulator()
        : a(std::random_device{}()),
        b(std::random_device{}() + 1) {
    }

    void generateRandomTasks() {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> valueDist(1, 50);
        std::uniform_int_distribution<> priorityDist(1, 10);
        std::uniform_int_distribution<> durationDist(200, 1000);
        std::uniform_int_distribution<> stepsDist(2, 5);

        for (int i = 0; i < 3; i++) {
            Task task1(
                valueDist(gen),
                priorityDist(gen),
                durationDist(gen),
                stepsDist(gen),
                "Task" + std::to_string(i + 1)
            );
            a.addTask(task1);

            Task task2(
                valueDist(gen),
                priorityDist(gen),
                durationDist(gen),
                stepsDist(gen),
                "Task" + std::to_string(i + 4)
            );
            b.addTask(task2);
        }
    }

    void execute() {
        bool running = true;

        while (running) {
            running = false;

            if (a.hasTasks()) {
                a.runStep(1);
                running = true;
            }

            if (b.hasTasks()) {
                b.runStep(2);
                running = true;
            }
        }

    }
};

int main() {
    HyperThreadingSimulator simulator;

    simulator.generateRandomTasks();

    simulator.execute();

    return 0;

}
