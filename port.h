#ifndef PORT_H
#define PORT_H 
#include <complex>
//could use class inheritance from impedance, but port is small
class Port{

private:

	//float real_imp;
	//float img_imp;
	std::complex<float> impedance;
	int node1_xid; //port only has 1 node
	int UNIQUE_ID;
	
	int x_Local_Id;


public:
	
	//functions relating to complex numbers
	void init_values();
	float get_Real(){return std::real(impedance);}
	float get_Img(){return std::imag(impedance);}
	float get_Phase(){return std::arg(impedance);}
	float get_Abs(){return std::abs(impedance);}
	std::complex<float> get_Imp(){return impedance;}
	std::complex<float> get_Inv(){return std::complex<float>(1.0,0)/impedance;}

	void set_X_Local_Id(int);
	void set_Node_Xid(int);
	void set_Unique_Id(int);
	int get_Node_Xid();
	int get_Unique_Id();
	int get_X_Local_Id(){return x_Local_Id;}


	Port();
        Port(int id,std::complex<float> n_imp){
               	impedance = n_imp; 
		UNIQUE_ID = id;
        }
};

#endif
