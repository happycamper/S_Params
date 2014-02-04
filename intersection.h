#ifndef INTERSECTION_H
#define INTERSECTION_H
#include <vector>
#include <map>
#include <Eigen/Dense>

using namespace std;
using Eigen::MatrixXcf;
class Intersection 
{
private:
	
	int rows;
	int cols;
	
	int num_internal_vertices;
	int num_conn_nodes;
	
	void initialize_values();
	vector<Port *> ports;
	vector<Impedance *> impedances;
	
	int intersection_number;
	
	int Ids;
	std::complex<float> calc_Int_Admit();

	void update_Local_Ids();

	map<int,Port *> portmap; //used to reference local id
	map<int,Impedance *> impmap; //used to reference local id	

public:
	Intersection();
	Intersection(int intNum){ init_values(); intersection_number = intNum;}
	Intersection(int,vector<Port *>,vector<Impedance *>);
	void init_values();
        
	int get_Internal_Vertices(){return num_internal_vertices;}
	int get_Conn_Nodes(){return num_conn_nodes;}
	int get_Intersection_Number(){return intersection_number;}
	
	std::complex<float> get_Intersection_Admit(){return calc_Int_Admit();}

	void set_Ports(vector<Port *>);
	void set_Impedances(vector<Impedance *>);

	void add_Port(Port *);
	void add_Impedance(Impedance *);	

	std::complex<float> calc_Diag_Xmat(int); //calculates the X[nn]k for X matrix
	std::complex<float> calc_Col_Xmat(int); //calculates the X[mn]k for X matrix

	MatrixXcf calc_X();

};

#endif
