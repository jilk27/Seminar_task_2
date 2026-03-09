// Seminar2.3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>

int main() {
    long long total_seconds;
    std::cin >> total_seconds;

     std::chrono::seconds seconds(total_seconds);

    auto hours = std::chrono::duration_cast<std::chrono::hours>(seconds);
    seconds -= hours;

    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(seconds);
    seconds -= minutes;

    std::cout << hours.count() << " hour ";
    std::cout << minutes.count() << " min ";
    std::cout << seconds.count() << " sec" << std::endl;

    return 0;
}