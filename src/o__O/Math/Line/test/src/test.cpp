#include <iostream>
#include "../../Line.hpp"



bool test_checkIsInteriorPoint_000 ( void )
{

	o__O::Math::PointI2 pointA {1,1};
	o__O::Math::PointI2 pointB {2,2};
	o__O::Math::PointI2 pointC {5,5};
	o__O::Math::LineI2 line(pointA,pointB);
	
	try
	{
	
		line.checkIsInteriorPoint(pointC);
		
	}
	catch ( o__O::Math::ExcNotAnInteriorPoint )
	{
	
		return false;
	
	}
	
	return true;

}

bool test_checkIsInteriorPoint_001 ( void )
{

	o__O::Math::PointI2 pointA {1,1};
	o__O::Math::PointI2 pointB {2,2};
	o__O::Math::PointI2 pointC {5,6};
	o__O::Math::LineI2 line(pointA,pointB);
	
	try
	{
	
		line.checkIsInteriorPoint(pointC);
		
	}
	catch ( o__O::Math::ExcNotAnInteriorPoint )
	{
	
		return true;
	
	}
	
	return false;

}



int main ( void )
{

	std::cout << ( test_checkIsInteriorPoint_000()						? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_checkIsInteriorPoint_001()						? "SUCCESS" : "FAIL" ) << std::endl;

	return 0;
}