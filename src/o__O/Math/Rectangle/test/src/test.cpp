#include <iostream>
#include "../../Rectangle.hpp"



bool test_constructor_001 ( void )
{

	o__O::Math::PointI2 pointA {2,2};
	o__O::Math::PointI2 pointB {3,3};
	o__O::Math::RectangleI2 rectangle(pointA,pointB);

	return
	(
		rectangle[0] == o__O::Math::PointI2 {2,2}
			&&
		rectangle[1] == o__O::Math::PointI2 {3,2}
			&&
		rectangle[2] == o__O::Math::PointI2 {3,3}
			&&
		rectangle[3] == o__O::Math::PointI2 {2,3}
	);

}



int main ( void )
{

	std::cout << ( test_constructor_001()									? "SUCCESS" : "FAIL" ) << std::endl;

	return 0;

}