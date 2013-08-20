#include "../../../../Tester/Tester.hpp"
#include "../../Point.hpp"



bool test_defaultConstructor_000 ( void )
{
	
	try
	{
	
		o__O::Math::Point<int,0> point;
		
	}
	
	catch ( o__O::Math::ExcInvalidDimension exception )
	{
	
		return true;
	
	}
	
	return false;

}

bool test_defaultConstructor_001 ( void )
{
	
	o__O::Math::Point<float,1> point;

	return
	(
		point[0] == 0
	);

}

bool test_defaultConstructor_002 ( void )
{
	
	o__O::Math::Point<int,5> point;

	return
	(
		point[0] == 0
			&&
		point[1] == 0
			&&
		point[2] == 0
			&&
		point[3] == 0
			&&
		point[4] == 0
	);

}

bool test_constructorFromInitializerList_000 ( void )
{

	o__O::Math::PointF3 point {1.5,2,5};
	
	return
	(
		point[0] == float(1.5)
			&&
		point[1] == float(2)
			&&
		point[2] == float(5)
	);

}

bool test_constructorFromInitializerList_001 ( void )
{

	try
	{
	
		o__O::Math::PointF3 point {1.5,2,5,6};
		
	}
	catch ( o__O::Math::ExcDimensionMismatch )
	{
	
		return true;
		
	}
	
	return false;
	
}

bool test_constructorFromInitializerList_002 ( void )
{

	o__O::Math::PointI3 point {1.5,2.3,5.6};
	
	return
	(
		point[0] == 1
			&&
		point[1] == 2
			&&
		point[2] == 5
	);
	
}

bool test_constructorFromInitializerList_003 ( void )
{

	o__O::Math::PointF3 point {1,2,5};
	
	return
	(
		point[0] == 1
			&&
		point[1] == 2
			&&
		point[2] == 5
	);
	
}

bool test_constructorFromCoordinates_000 ( void )
{

	o__O::Math::Point<int,3> point {4,5,6};
	
	return
	(
		point[0] == 4
			&&
		point[1] == 5
			&&
		point[2] == 6
	);

}

bool test_constructorFromCoordinates_001 ( void )
{

	o__O::Math::Point<float,3> point {4.1,5.43,6.56};
	
	return
	(
		point[0] == 4.1f
			&&
		point[1] == 5.43f
			&&
		point[2] == 6.56f
	);

}

bool test_constructorFromCoordinates_002 ( void )
{

	try
	{
	
		o__O::Math::Point<float,5> point {4.1,5.43,6.56};
		
	}
	catch ( o__O::Math::ExcDimensionMismatch )
	{
	
		return true;
		
	}
	
	return false;

}

bool test_constructorFromCoordinates_003 ( void )
{

	try
	{
	
		o__O::Math::Point<float,5> point {4.1,5.43,6.56,65,6,6,6,6,66};
		
	}
	catch ( o__O::Math::ExcDimensionMismatch )
	{
	
		return true;
		
	}
	
	return false;

}

bool test_constructorFromPoint_000 ( void )
{

	o__O::Math::Point<int,3> pointA {4,5,6};
	o__O::Math::Point<int,3> pointB = pointA;
	
	return
	(
		pointB[0] == 4
			&&
		pointB[1] == 5
			&&
		pointB[2] == 6
	);

}

bool test_constructorFromPoint_001 ( void )
{

	o__O::Math::Point<float,3> pointA {4.1,5.43,6.56};
	o__O::Math::Point<float,3> pointB(pointA);
	
	return
	(
		pointB[0] == 4.1f
			&&
		pointB[1] == 5.43f
			&&
		pointB[2] == 6.56f
	);

}

bool test_constructorFromDifferentPoint_000 ( void )
{

	o__O::Math::Point<float,3> pointA {4.1,5.43,6.56};
	o__O::Math::Point<int,3> pointB(pointA);
	
	return
	(
		pointB[0] == 4
			&&
		pointB[1] == 5
			&&
		pointB[2] == 6
	);

}

bool test_operatorAssignment_000 ( void )
{

	o__O::Math::Point<int,3> pointA {4,5,6};
	o__O::Math::Point<int,3> pointB;

	pointB = pointA;
	
	return
	(
		pointB[0] == 4
			&&
		pointB[1] == 5
			&&
		pointB[2] == 6
	);

}

bool test_operatorAssignment_001 ( void )
{

	o__O::Math::Point<float,3> pointA {4.1,5.43,6.56};
	o__O::Math::Point<float,3> pointB;
	
	pointB = pointA;
	
	return
	(
		pointB[0] == 4.1f
			&&
		pointB[1] == 5.43f
			&&
		pointB[2] == 6.56f
	);

}

bool test_operatorEqual_001 ( void )
{

	o__O::Math::Point<int,5> pointA {4,5,3,6,7};
	o__O::Math::Point<int,5> pointB {4,5,3,6,7};
	
	return
	(
		pointA == pointB
	);

}

bool test_operatorNotEqual_000 ( void )
{

	o__O::Math::Point<int,5> pointA {4,5,3,6,7};
	o__O::Math::Point<int,5> pointB {4,5,3,6,8};
	
	return
	(
		pointA != pointB
	);

}

bool test_getDimension_001 ( void )
{

	o__O::Math::Point<int,5> point {4,5,3,6,7};

	return
	(
		point.getDimension() == 5
	);

}

bool test_getDimension_002 ( void )
{
	
	o__O::Math::Point<float,7> point {4,5,3,6,7,5,5};

	return
	(
		point.getDimension() == 7
	);

}

bool test_operatorPlus_000 ( void )
{

	o__O::Math::Point<int,5> pointA {4,5,-3,6,7};
	o__O::Math::Point<int,5> pointB {4,-1,3,2,-3};
	o__O::Math::Point<int,5> pointC = pointA + pointB;
	
	return
	(
		pointC[0] == 8
			&&
		pointC[1] == 4
			&&
		pointC[2] == 0
			&&
		pointC[3] == 8
			&&
		pointC[4] == 4 
	);

}

bool test_operatorMinus_000 ( void )
{

	o__O::Math::Point<int,5> pointA {4,5,-3,6,7};
	o__O::Math::Point<int,5> pointB {4,-1,3,2,-3};
	o__O::Math::Point<int,5> pointC = pointA - pointB;
	
	return
	(
		pointC[0] == 0
			&&
		pointC[1] == 6
			&&
		pointC[2] == -6
			&&
		pointC[3] == 4
			&&
		pointC[4] == 10
	);

}

bool test_getDistanceTo_000 ( void )
{

	o__O::Math::Point<int,2> pointA {1,1};
	o__O::Math::Point<int,2> pointB {1,5};

	return
	(
		pointA.getDistanceTo(pointB) == 4
	);

}

bool test_getDistanceTo_001 ( void )
{
	
	o__O::Math::Point<int,2> pointA {0,0};
	o__O::Math::Point<int,2> pointB {1,1};
	
	return
	(
		pointA.getDistanceTo(pointB) == float(sqrt(2))
	);

}

bool test_getDistanceTo_002 ( void )
{
	
	o__O::Math::Point<int,2> pointA {-1,1};
	o__O::Math::Point<int,2> pointB {1,-1};

	return
	(
		pointA.getDistanceTo(pointB) == float(sqrt(2)*2)
	);

}

bool test_getDistanceTo_003 ( void )
{

	o__O::Math::Point<int,2> pointA {2,2};
	o__O::Math::Point<int,2> pointB {-2,-2};

	return
	(
		pointA.getDistanceTo(pointB) == float(sqrt(2)*4)
	);

}

bool test_operatorMultiply_000 ( void )
{

	o__O::Math::Point<int,2> pointA {-1,5};
	o__O::Math::Point<int,2> pointB = pointA * -1;

	return
	(
		pointB[0] == 1
			&&
		pointB[1] == -5
	);

}

bool test_operatorMultiply_001 ( void )
{

	o__O::Math::Point<float,3> pointA {-1.4,4.6,-5.2};
	o__O::Math::Point<float,3> pointB = pointA * -0.5;
	
	return
	(
		pointB[0] == float(0.7)
			&&
		pointB[1] == float(-2.3)
			&&
		pointB[2] == float(2.6)
	);

}

bool test_validateDimensionMatch_000 ( void )
{

	o__O::Math::PointI2 pointA {5,6};
	o__O::Math::PointF2 pointB {5.3,6.3};

	try
	{
		pointA.validateDimensionMatch(pointB);
	}
	catch ( o__O::Math::ExcDimensionMismatch )
	{
		return false;
	}

	return true;

}

bool test_validateDimensionMatch_001 ( void )
{

	o__O::Math::PointI2 pointA {5,6};
	o__O::Math::PointF3 pointB {5.3,6.3,5};

	try
	{
		pointA.validateDimensionMatch(pointB);
	}
	catch ( o__O::Math::ExcDimensionMismatch )
	{
		return true;
	}

	return false;

}



int main ( void )
{
/*
	o__O::Tester::addTest
	(
		//test_validateDimensionMatch_001
		[]()
		{
			o__O::Math::PointI2 pointA {5,6};
			o__O::Math::PointF3 pointB {5.3,6.3,5};

			try
			{
				pointA.validateDimensionMatch(pointB);
			}
			catch ( o__O::Math::ExcDimensionMismatch )
			{
				return true;
			}

			return false;
		}
	);

	RUN_ALL_TESTS;
*/

	std::cout << ( test_defaultConstructor_000()						? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_defaultConstructor_001()						? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_defaultConstructor_002()						? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_constructorFromInitializerList_000()			? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_constructorFromInitializerList_001()			? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_constructorFromInitializerList_002()			? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_constructorFromInitializerList_003()			? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_constructorFromCoordinates_000()				? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_constructorFromCoordinates_001()				? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_constructorFromCoordinates_002()				? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_constructorFromCoordinates_003()				? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_constructorFromPoint_000()						? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_constructorFromPoint_001()						? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_constructorFromDifferentPoint_000()				? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_operatorAssignment_000()						? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_operatorAssignment_001()						? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_operatorEqual_001()								? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_operatorNotEqual_000()							? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getDimension_001()								? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getDimension_002() 								? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_operatorPlus_000() 								? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_operatorMinus_000() 							? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getDistanceTo_000()								? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getDistanceTo_001()								? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getDistanceTo_002() 							? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getDistanceTo_003() 							? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_operatorMultiply_000()							? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_operatorMultiply_001()							? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_validateDimensionMatch_000()					? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_validateDimensionMatch_001()					? "SUCCESS" : "FAIL" ) << std::endl;

	return 0;

}