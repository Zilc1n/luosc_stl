#include <bits/stdc++.h>

using namespace std;

class base {
public:
    base() {
        cout << "base construct\n";
    }

    ~base() {
        cout << "base destroy\n";
    }
};

class A : protected base {
public:
    typedef base Base;
    A() {
        cout << "A construct\n";
    }
    ~A() {
        cout << "A de\n";
    }
};

int main() {
    A a = A();

    return 0;
}