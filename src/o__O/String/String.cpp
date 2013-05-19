#include "String.h"

using namespace o__O;

						String::String ( void )
{
	
}

						String::String ( const std::string& stdString )
{
	
	this->string = stdString;
	
}

						String::String ( const float floatNumber )
{
	
	std::stringstream stringStream;
	stringStream << floatNumber;
	this->string = stringStream.str();
	
}

						String::String ( const int integerNumber )
{
	
	std::stringstream stringStream;
	stringStream << integerNumber;
	this->string = stringStream.str();
	
}

String&					String::operator= ( const std::string& stdString )
{
	
	this->string = stdString;
	return *this;
	
}

char&					String::operator[] ( const int characterPosition )
{

	return this->string[characterPosition];

}

const char&				String::operator[] ( const int characterPosition ) const
{

	return this->string[characterPosition];

}

bool					String::operator== ( const std::string& stdString )
{

	return this->toStdString() == stdString;

}

bool					String::operator!= ( const std::string& stdString )
{

	return ! ( this->toStdString() == stdString );

}

int						String::getLength ( void )
{

	return this->toStdString().size();

}

std::string&			String::toStdString ( void )
{
	
	return this->string;
	
}

float					String::toFloat ( void )
{

	return atof(this->string.data());
	
}

int						String::toInt ( void )
{

	return strtod(this->string.data(),NULL);
	
}

Strings					String::split ( char delimiter )
{
	
	//  Creating the result vector
	Strings result;
	
	//  Calculating the size of the input string
	int stringSize = this->string.size();

	//  We are not going to add empty strings to the output vector
	if ( stringSize > 0 )
	{
		
		// searching for the position of the first delimiter.
		int firstDelimiterPosition = this->string.find_first_of(delimiter);
		
		//  No delimiters are in the string
		if ( firstDelimiterPosition == -1 )
		{
			
			//  The result is the whole string
			result.push_back(this->string);
			
		}

		//  The delimiter is the last and not the only character in the string
		else if ( firstDelimiterPosition == stringSize - 1 && stringSize > 1 )
		{
			
			//  The result is the string without the last character
			std::string firstStringPiece = this->string;
			firstStringPiece.resize(firstDelimiterPosition);
			result.push_back(firstStringPiece);

		}

		//  The delimiter is the first character in the string
		else
		{
			
			//  If the first character of the input is NOT a `delimiter`
			//  we are going to add the first fragment to the output
			if ( firstDelimiterPosition > 0 )
			{
				
				std::string firstFragment = string.substr(0,firstDelimiterPosition);
				result.push_back ( firstFragment );
				
			}
			
			//	Then we cut off the first fragment and the first delimiter and call the `split`
			//	function again with `input` string containing the rest of the string
			String stringTail = this->string.substr(firstDelimiterPosition+1,stringSize-firstDelimiterPosition-1);
			std::vector<String> stringTailArray = stringTail.split(delimiter);
			result.insert(result.end(),stringTailArray.begin(),stringTailArray.end());
			
		}
		
	}
	
	return result;
	
}