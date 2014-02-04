#ifndef CIRCUIT_HANDLER_H
#define CIRCUIT_HANDLER_H 
#include <complex>
#include <Eigen/Dense>
#include <vector>

using Eigen::MatrixXcf;

class Circuit_Handler{

private:
	
	int x_Rows;
	int x_Cols;

	int c_Rows;
	int c_Cols;
	int num_of_nodes;

	vector<Port *> ports;
	vector<Impedance *> impedances;
	vector<Intersection *> intersections;

	void calc_X_Rows();
	void calc_X_Cols();
	void calc_Num_Nodes();
	

public:
	
	void init_values();
	int get_Num_Nodes(){return num_of_nodes;}
	int get_X_Rows(){return x_Rows;}
	int get_X_Cols(){return x_Cols;}
	int get_C_Rows(){return c_Rows;}
	int get_C_Cols(){return c_Cols;}

	MatrixXcf calc_X();

	Circuit_Handler();
	Circuit_Handler(vector<Intersection *>,vector<Port *>,vector<Impedance *>);
};

#endif
