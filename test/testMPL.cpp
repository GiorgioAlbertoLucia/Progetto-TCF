//
// Created by Francesco Marchisotti  on 26/08/22.
//

//clang++ -std=c++14 -I /Users/francescomarchisotti/.pyenv/versions/3.10.2/include/python3.10/ -I /Users/francescomarchisotti/.pyenv/versions/3.10.2/lib/python3.10/site-packages/numpy/core/include -L /Users/francescomarchisotti/.pyenv/versions/3.10-dev/lib/ -lpython3.10 test/testMPL.cpp -o exe/testMPL

//#include "../matplotlib-cpp-master/matplotlibcpp.h"

#include <iostream>
#include <vector>

using namespace std;
//namespace plt = matplotlibcpp;

class Prova {
public:
	explicit Prova(int n) : n(n) {};

	void print() {
		cout << "prova" << n << ".print()" << endl;
	}
private:
	int n;
};

void f(Prova *p1, Prova &p2) {
	p1->print();
	p2.print();
}

int main() {
	cout << "Hello World!" << endl;

	Prova prova1(1), prova2(2);

	f(&prova1, prova2);

	return 0;
}