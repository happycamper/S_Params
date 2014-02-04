#include "circuit_handler.h"

Circuit_Handler::Circuit_Handler(){
	init_values();

}

void Circuit_Handler::init_values(){
	x_Rows = 0;
	x_Cols = 0;
	c_Rows = 0;
	c_Cols = 0;
	num_of_nodes = 0;
}

Circuit_Handler::Circuit_Handler(vector<Intersection *> n_intersections,vector<Port *> n_ports,vector<Impedance *> n_impedances){

		intersections = n_intersections;
		impedances = n_impedances;
		ports = n_ports;
		calc_X_Rows();
		calc_X_Cols();
		calc_Num_Nodes();
}

void Circuit_Handler::calc_X_Rows(){
	x_Rows = 0;
	Intersection *tempi;
	for (vector<Intersection *>::iterator it = intersections.begin() ; it != intersections.end(); ++it){
                        tempi = *it;
                        x_Rows += tempi->calc_X().rows();
        }
}

void Circuit_Handler::calc_X_Cols(){
        x_Rows = 0;
        Intersection *tempi;
        for (vector<Intersection *>::iterator it = intersections.begin() ; it != intersections.end(); ++it){
                        tempi = *it;
                        x_Cols += tempi->calc_X().cols();
        }
}

void Circuit_Handler::calc_Num_Nodes(){
        num_of_nodes = 0;
        Intersection *tempi;
        for (vector<Intersection *>::iterator it = intersections.begin() ; it != intersections.end(); ++it){
                        tempi = *it;
                        num_of_nodes += tempi->get_Conn_Nodes();
        }
}

MatrixXcf Circuit_Handler::calc_X(){
	int startrow = 0;
	int startcol = 0;
	MatrixXcf tempM;

	MatrixXcf X(num_of_nodes,num_of_nodes);
	X.setZero();
	Intersection *tempi;
	for (vector<Intersection *>::iterator it = intersections.begin() ; it != intersections.end(); ++it){
                        tempi = *it;
			tempM = tempi->calc_X();	
			X.block(startrow,startcol,tempM.rows(),tempM.cols()) = tempM;
			startrow += tempM.rows();
			startcol += tempM.cols();
        }

	return X;
}
