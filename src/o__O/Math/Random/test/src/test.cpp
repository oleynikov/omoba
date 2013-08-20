#include <iostream>
#include "../../Random.hpp"



bool test_random_000 ( void )
{

	int random = o__O::Math::Random::getInt(1,2);

	return
	(
		random == 1
			||
		random == 2
	);

}

bool test_random_001 ( void )
{

	int random = o__O::Math::Random::getInt(-5,-2);

	return
	(
		random == -5
			||
		random == -4
			||
		random == -3
			||
		random == -2
	);

}

bool test_random_002 ( void )
{

	try
	{
	
		o__O::Math::Random::getInt(2,1);
		
	}
	
	catch ( o__O::Math::ExcInvalidRange )
	{
	
		return true;
	
	}

	return false;
	
}

bool test_coinFlip_000 ( void )
{

	bool coinFlip = o__O::Math::Random::coinFlip();

	return
	(
		coinFlip == true
			||
		coinFlip == false
	);
	
}

bool test_coinFlip_001 ( void )
{

	bool coinFlip = o__O::Math::Random::coinFlip(10);

	return
	(
		coinFlip == true
			||
		coinFlip == false
	);
	
}



int main(void)
{
	
	std::cout << ( test_random_000()	? "SUCCESS" : "FAIL" ) << std::endl;
	std::cout << ( test_random_001()	? "SUCCESS" : "FAIL" ) << std::endl;
	std::cout << ( test_random_002()	? "SUCCESS" : "FAIL" ) << std::endl;
	std::cout << ( test_coinFlip_000()	? "SUCCESS" : "FAIL" ) << std::endl;
	std::cout << ( test_coinFlip_001()	? "SUCCESS" : "FAIL" ) << std::endl;
	
	return 0;
	
}