//
// Created by Francesco Marchisotti  on 26/08/22.
//

//clang++ -std=c++14 -I /Users/francescomarchisotti/.pyenv/versions/3.10.2/include/python3.10/ -I /Users/francescomarchisotti/.pyenv/versions/3.10.2/lib/python3.10/site-packages/numpy/core/include -L /Users/francescomarchisotti/.pyenv/versions/3.10-dev/lib/ -lpython3.10 test/testMPL.cpp -o exe/testMPL
// clang++ -std=c++14 test/testMPL.cpp -I /Library/Frameworks/Python.framework/Versions/3.9/include/python3.9 -I /Library/Frameworks/Python.framework/Versions/3.9/lib/python3.9/site-packages/numpy/core/include/ -L /Library/Frameworks/Python.framework/Versions/3.9/lib -lpython3.9 -lpthread -o exe/testMPL


#include "../matplotlib-cpp-master/matplotlibcpp.h"

#include <iostream>
#include <vector>

using namespace std;
namespace plt = matplotlibcpp;

/*
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

*/


int main()
{

	int n = 5000; // 5000 data points
  	std::vector<double> x(n), y(n), z(n), w(n, 2);
  	for (int i = 0; i < n; ++i) {
  	  x.at(i) = i * i;
  	  y.at(i) = sin(2 * M_PI * i / 360.0);
  	  z.at(i) = log(i);
  	}

  	matplotlibcpp::figure(); // declare a new figure (optional if only one is used)

  	//plt::plot(x, y); // automatic coloring: tab:blue
  	//plt::show(false);
  	//plt::plot(x, w, "r--");                 // red dashed line
  	//plt::plot(x, z, {{"label", "log(x)"}}); // legend label "log(x)"
//
  	//plt::xlim(0, 1000 * 1000);    // x-axis interval: [0, 1e6]
  	//plt::title("Standard usage"); // set a title
  	//plt::legend();                // enable the legend
//
  	//plt::savefig("graphs/standard.pdf"); // save the figure
  	//plt::show();


	
}