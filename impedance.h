#ifndef IMPEDANCE_H
#define IMPEDANCE_H
#include <complex>

class Impedance{

private:

	//float real_imp;
	//float img_imp;
	std::complex<float> impedance;
	int node1_xid; //sets the intersection id of the node
	int node2_xid; //sets the intersection id of the node


	int node1_Global_Id;
	int node2_Global_Id;	
	
	int x_Local_Id;


public:
	
 	enum IMPEDANCE_TYPES {lumped = 0, t_line};
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
	int get_Node_Global_Id(int);

        Impedance::IMPEDANCE_TYPES get_Lumped(){return lumped;}
	int get_Type(){return imp_type;}


	void set_node_xid(int, int);
	int get_Node_Xid(int);


	Impedance();
        Impedance(IMPEDANCE_TYPES type, std::complex<float> n_imp){
               	impedance = n_imp; 
		check_imp_type(type);
        }


};

void Impedance::check_imp_type(IMPEDANCE_TYPES type){
        if(type == lumped){
                imp_type = lumped;
        }else if(type == t_line){
                imp_type = t_line;
        }else{
                imp_type = lumped;
        }
}

#endif
