#ifndef IMPEDANCE_H
#define IMPEDANCE_H
#include <complex>
#include <vector>
#include <Eigen/Dense>
#include <cmath>
#include <string>
#define PI 3.1415926535897932384626433832795

using namespace std;
using Eigen::MatrixXcf;

class Impedance{

private:

	//float real_imp;
	//float img_imp;
	std::complex<float> impedance;
	//int node1_xid; //sets the intersection id of the node
	//int node2_xid; //sets the intersection id of the node
	
	vector<int> *intersections;

	int num_of_ports;	


	//int node1_Global_Id;
	//int node2_Global_Id;	
	const char *UID;
		
	int x_Local_Id;

	float Alpha;
	float Beta;
	float Length;


public:
	
 	enum IMPEDANCE_TYPES {port = 0, lumped, t_line, c_line, q_line, coupled_line};
	IMPEDANCE_TYPES imp_type;

	void init_values();
	void check_imp_type(IMPEDANCE_TYPES type);


	//functions relating to complex numbers
	
	float get_Real(){return std::real(impedance);}
	float get_Img(){return std::imag(impedance);}
	float get_Phase(){return std::arg(impedance);}
	float get_Abs(){return std::abs(impedance);}
	std::complex<float> get_Imp(){return impedance;}
	std::complex<float> get_Inv(){return std::complex<float>(1.0,0)/impedance;}
	
	//////////////////////////////////////////////
	void set_X_Local_Id(int id){ x_Local_Id = id;}
	int get_X_Local_Id(){ return x_Local_Id;}
	//int get_Node_Global_Id(int);
	int get_Num_of_Ports(){return num_of_ports;}
        Impedance::IMPEDANCE_TYPES get_Lumped(){return lumped;}
	int get_Type(){return imp_type;}
	void set_Uid(const char *uid){ UID = uid;}
	const char* get_Uid(){return UID;}

	void set_Alpha(float alpha){ Alpha = alpha;}
	void set_Beta(float beta){ Beta = beta;}
	float get_Alpha(){return Alpha;}
	float get_Beta(){return Beta;}
	void init_Lumped();
	void init_T_Line();
	void init_Port();

	//void set_node_xid(int, int);
	//int get_Node_Xid(int);

	
	
	void add_Intersection(int);
	vector<int>* get_Intersections();

	MatrixXcf get_Cmat();


	Impedance();//default constructor
        Impedance(IMPEDANCE_TYPES type, std::complex<float> n_imp,const char *uid){ //primarily for lumped or port
               	impedance = n_imp;
		UID = uid; 
		check_imp_type(type);
        }

	Impedance(IMPEDANCE_TYPES type, std::complex<float> n_imp,float nlength,const char *uid){ //for tline,cline,qline
                impedance = n_imp;
		UID = uid;
                check_imp_type(type);
		Length = nlength;
        }


};

void Impedance::check_imp_type(IMPEDANCE_TYPES type){
        if(type == lumped){
                imp_type = lumped;
		init_Lumped();
        }else if(type == t_line){
                imp_type = t_line;
		init_T_Line();
        }else if(type == port){
                imp_type = port;
		init_Port();
        }
}

#endif
