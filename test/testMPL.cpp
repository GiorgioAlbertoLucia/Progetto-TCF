//
// Created by Francesco Marchisotti  on 26/08/22.
//

//clang++ -std=c++14 -I /Users/francescomarchisotti/.pyenv/versions/3.10.2/include/python3.10/ -I /Users/francescomarchisotti/.pyenv/versions/3.10.2/lib/python3.10/site-packages/numpy/core/include -L /Users/francescomarchisotti/.pyenv/versions/3.10-dev/lib/ -lpython3.10 test/testMPL.cpp -o exe/testMPL
// clang++ -std=c++14 test/testMPL.cpp -I /Library/Frameworks/Python.framework/Versions/3.9/include/python3.9 -I /Library/Frameworks/Python.framework/Versions/3.9/lib/python3.9/site-packages/numpy/core/include/ -L /Library/Frameworks/Python.framework/Versions/3.9/lib -lpython3.9 -lpthread -o exe/testMPL


#include "../matplotlib-cpp-master/matplotlibcpp.h"

#include <iostream>
#include <vector>

using namespace std;
//namespace plt = matplotlibcpp;

int main() {
	cout << "Hello World!" << endl;

	return 0;
}