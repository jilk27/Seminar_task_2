// Seminar2.6.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

class VirtualThread {
private:
    int arr[4];
public:
    void addInMas() {
        for (int i = 0; i < 4; i++) {
            int f;
            std::cin >> f;
            arr[i] = f;
        }
    }

    void run(int ind) {
        int fac = 1;

        for (int i = 1; i < arr[ind]; i++) {
            fac *= i;
        }

        std::cout << arr[ind] << "! = " << fac << std::endl;
    }
};

class HyperThreadingSimulator {
public:
    VirtualThread a;
    VirtualThread b;

    void execute() {
        for (int i = 0; i < 4; i++) {
            if (i % 2 == 0) {
                std::cout << "First thread work: ";
                a.run(i);
            }
            else {
                std::cout << "Second thread work: ";
                b.run(i);
            }
        }
    }
};

int main()
{
    HyperThreadingSimulator first;

    first.a.addInMas();
    first.b.addInMas();
    first.execute();

    std::cout << "Hello World!\n";
}
