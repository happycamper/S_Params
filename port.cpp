#include "port.h"

Port::Port(){
	init_values();
}

void Port::init_values(){
	impedance = std::complex<float>(1.0,0.0);
	UNIQUE_ID = 0;
	node1_xid = 0;
}

void Port::set_Node_Xid(int id){
	node1_xid = id;	

}

int Port::get_Node_Xid(){
	return node1_xid;
}

void Port::set_Unique_Id(int id){
	UNIQUE_ID = id;
}

int Port::get_Unique_Id(){
	return UNIQUE_ID;
}

void Port::set_X_Local_Id(int id){
	x_Local_Id = id;
}
