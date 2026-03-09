// Seminar2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <chrono>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int sum = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < n; i++) {
        sum += i;
    }

    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);

    std::cout << "Summa " << n << " numbs needs " << duration.count() << " ms" << std::endl;

}
