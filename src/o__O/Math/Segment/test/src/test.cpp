#include <iostream>
#include "../../Segment.hpp"



bool test_constructor_000 ( void )
{

	o__O::Math::PointI2 pointA {5,5};
	o__O::Math::PointI2 pointB {5,5};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);
	
	return
	(
		segment[0] == pointA
			&&
		segment[1] == pointB
	);

}

bool test_constructor_001 ( void )
{

	o__O::Math::PointI2 pointA {5,5};
	o__O::Math::PointI2 pointB {-5,-3};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);
	
	return
	(
		segment[0] == pointA
			&&
		segment[1] == pointB
	);

}

bool test_getLength_000 ( void )
{

	o__O::Math::PointI2 pointA {5,5};
	o__O::Math::PointI2 pointB {0,5};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);
	
	return
	(
		segment.getLength() == int(5)
	);

}

bool test_getLength_001 ( void )
{

	o__O::Math::PointI2 pointA {2,4};
	o__O::Math::PointI2 pointB {2,5};

	o__O::Math::Segment<int,2> segment(pointA,pointB);

	return
	(
		segment.getLength() == int(1)
	);
	
}

bool test_getLength_002 ( void )
{

	o__O::Math::PointI2 pointA {-1,-1};
	o__O::Math::PointI2 pointB {1,1};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);

	return
	(
		segment.getLength() == float(sqrt(2)*2)
	);

}

bool test_getInteriorPoint_000 ( void )
{

	o__O::Math::PointI2 pointA {2,0};
	o__O::Math::PointI2 pointB {2,100};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);
	
	return
	(
		segment.getInteriorPoint(17,0) == o__O::Math::PointF2 {2,17}
	);

}

bool test_getInteriorPoint_001 ( void )
{

	o__O::Math::PointI2 pointA {3,0};
	o__O::Math::PointI2 pointB {3,100};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);
	
	return
	(
		segment.getInteriorPoint(17,1) == o__O::Math::PointF2 {3,83}
	);

}

bool test_getInteriorPoint_002 ( void )
{

	o__O::Math::PointI2 pointA {0,0};
	o__O::Math::PointI2 pointB {10,0};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);
	
	return
	(
		segment.getInteriorPoint(2,0) == o__O::Math::PointF2 {2,0}
	);

}

bool test_getInteriorPoint_003 ( void )
{

	o__O::Math::PointI2 pointA {0,0};
	o__O::Math::PointI2 pointB {9,0};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);
	
	return
	(
		segment.getInteriorPoint(2,1) == o__O::Math::PointF2 {7,0}
	);

}

bool test_getInteriorPoint_004 ( void )
{

	o__O::Math::PointI2 pointA {0,0};
	o__O::Math::PointI2 pointB {10,0};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);

	return
	(
		segment.getInteriorPoint(2,1) == o__O::Math::PointF2 {8,0}
	);

}

bool test_getInteriorPoint_005 ( void )
{

	o__O::Math::PointI2 pointA {0,0};
	o__O::Math::PointI2 pointB {10,0};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);

	return
	(
		segment.getInteriorPoint(3,0) == o__O::Math::PointF2 {3,0}
	);
	
}

bool test_getInteriorPoint_006 ( void )
{

	o__O::Math::PointI2 pointA {-2,2};
	o__O::Math::PointI2 pointB {2,-2};
	
	o__O::Math::Segment<int,2> segment(pointA,pointB);

	return
	(
		segment.getInteriorPoint(sqrt(2),1) == o__O::Math::PointF2 {1,-1}
	);

}

bool test_getInteriorPoints_000 ( void )
{

	o__O::Math::PointI2 pointA {0,0};
	o__O::Math::PointI2 pointB {0,10};
	o__O::Math::SegmentI2 segment(pointA,pointB);
	
	o__O::Math::SegmentI2::SegmentPointsF points = segment.getInteriorPoints(2);
	
	return
	(
		points.size() == 3
			&&
		points[0] == o__O::Math::PointI2 {0,0}
			&&
		points[1] == o__O::Math::PointF2 {0,5}
			&&
		points[2] == o__O::Math::PointI2 {0,10}
	);
	
}

bool test_getInteriorPoints_001 ( void )
{

	o__O::Math::PointI2 pointA {2,2};
	o__O::Math::PointI2 pointB {2,10};
	o__O::Math::SegmentI2 segment(pointA,pointB);
	
	o__O::Math::SegmentI2::SegmentPointsF points = segment.getInteriorPoints(4);

	return
	(
		points.size() == 5
			&&
		points[0] == o__O::Math::PointI2 {2,2}
			&&
		points[1] == o__O::Math::PointI2 {2,4}
			&&
		points[2] == o__O::Math::PointI2 {2,6}
			&&
		points[3] == o__O::Math::PointI2 {2,8}
			&&
		points[4] == o__O::Math::PointI2 {2,10}
	);
	
}



int main ( void )
{

	std::cout << ( test_constructor_000()				? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_constructor_001()				? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getLength_000()					? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getLength_001()					? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getLength_002()					? "SUCCESS" : "FAIL" ) << std::endl;

	std::cout << ( test_getInteriorPoint_000()			? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_getInteriorPoint_001()			? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_getInteriorPoint_002()			? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_getInteriorPoint_003()			? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_getInteriorPoint_004()			? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_getInteriorPoint_005()			? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_getInteriorPoint_006()			? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_getInteriorPoints_000()			? "SUCCESS" : "FAIL" ) << std::endl;
	
	std::cout << ( test_getInteriorPoints_001()			? "SUCCESS" : "FAIL" ) << std::endl;
	
	return 0;
}