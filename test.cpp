#include "impedance.h"
#include "port.h"
#include "impedance.cpp"
#include "port.cpp"
#include "intersection.h"
#include "intersection.cpp"
#include <iostream> 
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
	//declaration of ports
	Port *p1 = new Port(1,std::complex<float>(50.0,0));
	Port *p2 = new Port(2,std::complex<float>(50.0,0));
	Port *p3 = new Port(3,std::complex<float>(50.0,0));

	p1->set_Node_Xid(1); //sets the intersection id
	p1->set_Node_Xid(2);
	p1->set_Node_Xid(3);

	Impedance *i1 = new Impedance((Impedance::IMPEDANCE_TYPES) 1, std::complex<float>(71.0,0)); //first tline
	Impedance *i2 = new Impedance((Impedance::IMPEDANCE_TYPES) 1, std::complex<float>(71.0,0)); //second tline
	Impedance *i3 = new Impedance((Impedance::IMPEDANCE_TYPES) 0, std::complex<float>(100.0,0)); //first tline
	
	vector<Port *> ports;
	vector<Port *> ports2;
	vector<Port *> ports3;
	ports.push_back(p1);
	ports2.push_back(p2);
	ports3.push_back(p3);

	vector<Impedance *> X1impedances;
	vector<Impedance *> X2impedances;
	vector<Impedance *> X3impedances;

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

	X1->set_Ports(ports);
	X1->set_Impedances(X1impedances);
	
	X2->set_Ports(ports2);
	X2->set_Impedances(X2impedances);

	X3->set_Ports(ports3);
	X3->set_Impedances(X3impedances);
		

	//temp = i->get_Type();
	cout << X2->calc_X() << endl;  
	
	return 0;
}
