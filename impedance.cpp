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

