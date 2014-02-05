#include "intersection.h"
#include <vector>
using namespace std;

Intersection::Intersection(){
	init_values();

}

Intersection::Intersection(int num, vector<Impedance *> nimpedances){
		init_values();
	//	set_Ports(nports);
		set_Impedances(nimpedances);
		intersection_number = num;
}


void Intersection::init_values(){
	num_internal_vertices = 0;
	num_conn_nodes = 0;
	intersection_number = 0;
	Ids = 1;
}

/*void Intersection::set_Ports(vector<Port *> tports){
	ports = tports;
	num_conn_nodes += ports.size();
}*/

void Intersection::set_Impedances(vector<Impedance *> timpedances){
	impedances = timpedances;
	num_conn_nodes += impedances.size();
}

/*void Intersection::add_Port(Port *nport){
	ports.push_back(nport);
}*/

void Intersection::add_Impedance(Impedance *nimp){
	impedances.push_back(nimp);
}	

void Intersection::update_Local_Ids(){
//	Port *temp_port;
	Impedance *tempi;
//	portmap.clear();//reinitializes variables
	impmap.clear();
	Ids = 1;
/*	for (vector<Port *>::iterator it = ports.begin() ; it != ports.end(); ++it){
                        temp_port= *it;
			temp_port->set_X_Local_Id(Ids);
			portmap[temp_port->get_X_Local_Id()] = temp_port;
			++Ids;
        }*/

        //look for the attached impedances and add to total admittance  
        for (vector<Impedance *>::iterator it = impedances.begin() ; it != impedances.end(); ++it){
                        tempi = *it;
			tempi->set_X_Local_Id(Ids);
			impmap[tempi->get_X_Local_Id()] = tempi;
			++Ids;
        }

}


std::complex<float> Intersection::calc_Int_Admit(){
	std::complex<float> temp(0.0,0.0);
	Impedance *tempi;  //holding variable
	//Port *temp_port; //holding variable
	//look for attached ports to the intersection and get the impedance	
	/*for (vector<Port *>::iterator it = ports.begin() ; it != ports.end(); ++it){
                        temp_port= *it;
                        temp += temp_port->get_Inv();
        }*/

	//look for the attached impedances and add to total admittance	
	for (vector<Impedance *>::iterator it = impedances.begin() ; it != impedances.end(); ++it){
			tempi = *it;
			temp += tempi->get_Inv();	
	}
	return temp;
}

//Calculation block for X[nn]k diagonal reflection coefficients
std::complex<float> Intersection::calc_Diag_Xmat(int local_id){
	std::complex<float> returnval(0.0,0.0);
	if(impmap.find(local_id) != impmap.end()){
		 Impedance *temp_imp = impmap[local_id];
                returnval = (std::complex<float>(2.0,0)/(temp_imp->get_Imp()*get_Intersection_Admit())) - std::complex<float>(1.0,0);
		return returnval;
	}else{
		return returnval;
	}
}


std::complex<float> Intersection::calc_Col_Xmat(int local_id){
	 std::complex<float> returnval(0.0,0.0);
         if(impmap.find(local_id) != impmap.end()){
                 Impedance *temp_imp = impmap[local_id];
                returnval = (std::complex<float>(2.0,0)/(temp_imp->get_Imp()*get_Intersection_Admit()));
                return returnval;
        }else{
                return returnval;
        }	
}

MatrixXcf Intersection::calc_X(){
	update_Local_Ids();
        int cols = num_conn_nodes;
        int rows = num_conn_nodes;
	int Id_Ref = 1;
	
	MatrixXcf X(rows, cols);	
	for(int n = 0; n < num_conn_nodes; ++n){
		for(int m = 0; m < num_conn_nodes; ++m){	
			if(m == n){
				X(m,n) = calc_Diag_Xmat(Id_Ref);
			}else{
				X(m,n) = calc_Col_Xmat(Id_Ref);
			}	
		}
		++Id_Ref;
	}

	return X;
}

