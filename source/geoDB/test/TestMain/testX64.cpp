
#include <ostream>
#include<istream>
#include<iostream>
#include<geoBasicType.h>
using namespace std;
int run_main(int argc, char** argv)
{

	cout <<" geoNULL size :" << sizeof(geoNull) << endl;

	cout << " geoBool size :" << sizeof(geoBool) << endl;
	cout << " geoInt8 size :" << sizeof(geoInt8) << endl;
	cout << " geoUInt8 size :" << sizeof(geoUInt8) << endl;
	cout << " geoInt16 size :" << sizeof(geoInt16) << endl;
	cout << " geoUInt16 size :" << sizeof(geoUInt16) << endl;
	cout << " geoInt32 size :" << sizeof(geoInt32) << endl;
	cout << " geoUInt32 size :" << sizeof(geoUInt32) << endl;
	cout << " geoInt64 size :" << sizeof(geoInt64) << endl;
	cout << " geoUInt64 size :" << sizeof(geoUInt64) << endl;
	cout << " geoFloat size :" << sizeof(geoFloat) << endl;
	cout << " geoDouble size :" << sizeof(geoDouble) << endl;

	cout << " int size :" << sizeof(int) << endl;
	cout << " long size :" << sizeof(long) << endl;
	cout << " geoBlob size :" << sizeof(geoBlob) << endl;


	cout << " geoString size :" << sizeof(geoString) << endl;
	cout << " geoVariant size :" << sizeof(geoVariant) << endl;
	cout << " geoData size :" << sizeof(geoData) << endl;

	return 0;

}

int main(int argc, char** argv)
{
	run_main(argc, argv);

	return 0;
}