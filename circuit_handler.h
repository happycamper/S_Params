#ifndef CIRCUIT_HANDLER_H
#define CIRCUIT_HANDLER_H 
#include <complex>
#include <Eigen/Dense>
#include <vector>
#include <map>

using Eigen::MatrixXcf;

class Circuit_Handler{

private:
	
	int x_Rows;
	int x_Cols;

	int c_Rows;
	int c_Cols;
	int num_of_nodes;//total number of nodes
	int gnc;//this assigns the global node count 

//	vector<Port *> ports;
	vector<Impedance *> impedances;
	vector<Intersection *> intersections;

	map<const char*,vector<int> > global_tracker;//helps find impedances in graph based 
				            //on UID and global assigned number

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
	MatrixXcf calc_C();
	MatrixXcf calc_S();

	Circuit_Handler();
	Circuit_Handler(vector<Intersection *>,vector<Impedance *>);
};

#endif
