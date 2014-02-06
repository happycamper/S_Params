#include "impedance.h"
#include "port.h"
#include "impedance.cpp"
#include "port.cpp"
#include "intersection.h"
#include "intersection.cpp"
#include "circuit_handler.h"
#include "circuit_handler.cpp"
#include <iostream> 
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
	
	ofstream filestream;
	filestream.open("test.csv");
	filestream << "S11,S14,S17,S41,S44,S47,S71,S74,S77\n";	
//	filestream.close();
	//frequency sweep
	for(int div = 1; div < 20; ++div){
	float templength = (float)16.0/(2.0*div);
//	vector<Port *> portsG;
	vector<Impedance *> impedancesG;
	vector<Intersection *> intersectionsG;
	

	//declaration of ports
//	Port *p1 = new Port(1,std::complex<float>(50.0,0));
//	Port *p2 = new Port(2,std::complex<float>(50.0,0));
//	Port *p3 = new Port(3,std::complex<float>(50.0,0));

//	p1->set_Node_Xid(1); //sets the intersection id
//	p2->set_Node_Xid(2);
//	p3->set_Node_Xid(3);

//	portsG.push_back(p1);
//	portsG.push_back(p2);
//	portsG.push_back(p3);
	Impedance *p1 = new Impedance((Impedance::IMPEDANCE_TYPES) 0, std::complex<float>(50.0,0),"P_1");
	Impedance *p2 = new Impedance((Impedance::IMPEDANCE_TYPES) 0, std::complex<float>(50.0,0),"P_2");
	Impedance *p3 = new Impedance((Impedance::IMPEDANCE_TYPES) 0, std::complex<float>(50.0,0),"P_3");

	Impedance *i1 = new Impedance((Impedance::IMPEDANCE_TYPES) 2, std::complex<float>(71.0,0),templength,"T_1"); //first tline
	Impedance *i2 = new Impedance((Impedance::IMPEDANCE_TYPES) 2, std::complex<float>(71.0,0),templength,"T_2"); //second tline
	Impedance *i3 = new Impedance((Impedance::IMPEDANCE_TYPES) 1, std::complex<float>(100.0,0),"T_3"); //first tline
		
	//vector<Port *> ports;
	//vector<Port *> ports2;
	//vector<Port *> ports3;
	//ports.push_back(p1);
	//ports2.push_back(p2);
	//ports3.push_back(p3);

	vector<Impedance *> X1impedances;
	vector<Impedance *> X2impedances;
	vector<Impedance *> X3impedances;
	
	X1impedances.push_back(p1);
	X2impedances.push_back(p2);
	X3impedances.push_back(p3);

	X1impedances.push_back(i1);
	X1impedances.push_back(i2);
	X2impedances.push_back(i1);
	X2impedances.push_back(i3);
	X3impedances.push_back(i2);
	X3impedances.push_back(i3);
	//X1impedances.push_back(i3);

	Intersection *X1 = new Intersection(1);
	Intersection *X2 = new Intersection(2);
	Intersection *X3 = new Intersection(3);

	//X1->set_Ports(ports);
	X1->set_Impedances(X1impedances);
	
	//X2->set_Ports(ports2);
	X2->set_Impedances(X2impedances);

	//X3->set_Ports(ports3);
	X3->set_Impedances(X3impedances);
	
	impedancesG.push_back(p1);
	impedancesG.push_back(p2);
	impedancesG.push_back(p3);
	impedancesG.push_back(i1);
	impedancesG.push_back(i2);
	impedancesG.push_back(i3);

	intersectionsG.push_back(X1);
	intersectionsG.push_back(X2);
	intersectionsG.push_back(X3);

	Circuit_Handler *ch = new Circuit_Handler(intersectionsG,impedancesG);
		
//	ch->calc_S();	
	//temp = i->get_Type();
	MatrixXcf R = ch->get_Port_Scattering_Abs();
	cout << R << endl;  
	for(int m = 0; m < R.rows(); ++m){
                for(int n = 0; n < R.cols(); ++n){
                        std::complex<float> j = R(m,n);
                     //   Sabs(m,n) = std::abs(j);
                      filestream << std::real(j) << ",";
                }
        }
	
	filestream << "\n";
	
	}
	filestream.close();	
	return 0;
}
