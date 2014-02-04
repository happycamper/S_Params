#include "impedance.h"

Impedance::Impedance(){
	init_values();
}

void Impedance::init_values(){
	std::complex<float> temp(1.0,1.0);
	impedance = temp;
	imp_type = lumped;
}

void Impedance::set_node_xid(int node, int id){
	
	if(node == 1){
		node1_xid = id;
	}else if(node == 2){
		node2_xid = id;
	}else{
		node1_xid = 0;
		node2_xid = 0; //default to 0 if we don't get 1 or 2	
	}

}

int Impedance::get_Node_Xid(int node){
	if(node == 1){
		return node1_xid;	
	}else if(node == 2){
		return node2_xid;	
	}else{
		return 0;	
	}
}

int Impedance::get_Node_Global_Id(int id){
                if(id == 1){
                        return node1_Global_Id;
                }else if(id == 2){
                        return node2_Global_Id;
                }else{
                        return 0;
                }

}

void Impedance::add_Intersection(int X_id){
	intersections->push_back(X_id);
}

vector<int>* Impedance::get_Intersections(){
	return intersections;
}

MatrixXcf Impedance::get_Cmat(){
	if(imp_type == lumped){
		MatrixXcf cret(2,2);
		std::complex<float> gamma(0.33333333,0.0);
		std::complex<float> tau(0.66666666,0.0);
		cret(0,0) = gamma;
		cret(1,1) = gamma;
		cret(1,0) = tau;
		cret(0,1) = tau;
		return cret;	
	}else if(imp_type == t_line){
		MatrixXcf cret(2,2);
		std::complex<float> zero(0.0,0.0);
		float prop_alpha = exp(-1.0*Alpha);
		std::complex<float> propagation = std::complex<float>(prop_alpha,0.0)*std::complex<float>(std::polar(1.0,-1.0*2.0*PI*Length));
		cret(0,0) = zero;
		cret(1,1) = zero;
		cret(1,0) = propagation;
		cret(0,1) = propagation;	
		return cret;
	}else{
		MatrixXcf cret(2,2);
                std::complex<float> zero(0.0,0.0);
		cret(0,0) = zero;
		cret(0,1) = zero;
		cret(1,0) = zero;
		cret(1,1) = zero;
		return cret;	
	}

}
