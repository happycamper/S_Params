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

Circuit_Handler::Circuit_Handler(vector<Intersection *> n_intersections,vector<Impedance *> n_impedances){

		intersections = n_intersections;
		impedances = n_impedances;
		calc_X_Rows();
		calc_X_Cols();
		calc_Num_Nodes();
		calc_Num_Ports();
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

void Circuit_Handler::calc_Num_Ports(){
	num_of_ports = 0;
	Impedance *tempi;
	for (vector<Impedance *>::iterator it = impedances.begin() ; it != impedances.end(); ++it){
                        tempi = *it;
			if(tempi->get_Type() == 0){
				++num_of_ports;
			}
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

//so far, calc C does max 2 port elements
MatrixXcf Circuit_Handler::calc_C(){
	MatrixXcf C(num_of_nodes,num_of_nodes);
	MatrixXcf tempC(1,1);
	C.setZero(); //will be sparse anyways
	map<int,Impedance *> tempMap;
	Intersection *tempInt;
	Impedance *tempImp;
	gnc = 1;//global node counter, used to assign global numbers to nodes
	int rowstart = 0;//references C Matrix
	int colstart = 0;//references C matrix
	//start by loading intersections in the way we calc'd X[X1,X3,X5]
	for (vector<Intersection *>::iterator it = intersections.begin() ; it != intersections.end(); ++it){
                        tempInt = *it; //get first intersection
			tempMap = tempInt->get_Mapped_Impedances(); //return list of impedances
			for(int i = 1; i< tempInt->get_Conn_Nodes() + 1; ++i){
				vector<int> tempV; //to store previous node info
				vector<int> existing; //to add to node info
				if(tempMap.find(i) != tempMap.end()){ //impedance should exist here
					tempImp = tempMap[i]; //get impedance
					if(tempImp->get_Type() == 0){ //0 for port
						ports.push_back(gnc);	
					}
					int numports = tempImp->get_Num_of_Ports(); //2 or 1 port
					tempC.resize(numports,numports); //get ready to receive C
					tempC = tempImp->get_Cmat(); //get impedance C matrix

					//look to see if we have seen this impedance before
					if(global_tracker.find(tempImp->get_Uid()) != global_tracker.end()){
						//if we have, get its previous node list
						existing = global_tracker[tempImp->get_Uid()];
						
						for(vector<int>::iterator et = existing.begin(); et != existing.end(); ++et){
				//sort through old nodes and insert C matrix accordingly

							int oldport = *et;
							int oldref = oldport -1;
							C(oldref,colstart) = tempC(0,1);
							C(rowstart,oldref) = tempC(1,0);
							C(rowstart,colstart) = tempC(1,1);
							
						}
						existing.push_back(gnc); //lets capture this node
						//add impedance with node list back to tree
						global_tracker[tempImp->get_Uid()] = existing;		
					}else{
						//if we haven't seen before, just get reflection coeff
						C(rowstart,colstart) = tempC(0,0);
						tempV.push_back(gnc);
						global_tracker[tempImp->get_Uid()] = tempV;
					}
						
				}
				++rowstart;
				++colstart;
				++gnc;	
			}
        }
	return C;	
	
}

MatrixXcf Circuit_Handler::calc_S(){
	MatrixXcf S(num_of_nodes,num_of_nodes);
	MatrixXcf I = MatrixXcf::Identity(num_of_nodes,num_of_nodes);
	MatrixXcf X = calc_X();
	MatrixXcf C = calc_C();
	num_of_ports = ports.size();
	MatrixXcf temp2(num_of_nodes,num_of_nodes);

	MatrixXcf temp(num_of_nodes,num_of_nodes);
	temp = C*X;
	temp = I - temp;
	temp2 = temp.inverse();
	S = X*temp2;
	
	return S;
	
}

MatrixXcf Circuit_Handler::get_Port_Scattering(){
	MatrixXcf S(num_of_nodes,num_of_nodes);
//	int srowscols = ports.size();
	MatrixXcf Scatter(num_of_ports,num_of_ports);
	S = calc_S();
	int m = 0;
	 for(vector<int>::iterator it = ports.begin(); it != ports.end(); ++it){
		int port1 = *it;
		int matrow = port1-1;	
		int n = 0;	
		for(vector<int>::iterator et = ports.begin(); et != ports.end(); ++et){		
			int port2 = *et;
			int matcol = port2-1; //offset for matrix
			Scatter(m,n) = S(matrow,matcol);
			++n;			
		}
		++m;
	}
	return Scatter;
}
