#include <iostream>
#include <Eigen/Dense>
#include <complex>
using namespace std;
using Eigen::MatrixXcf;
int main()
{

	complex<float> c(.5,.5);
	int cols = 2;
	int rows = 2;
	MatrixXcf X(rows, cols);
	X(0,0) = c;
	X(0,1) = c;
	X(1,0) = c;
	X(1,1) = c;
	std::cout << X << std::endl;
}

