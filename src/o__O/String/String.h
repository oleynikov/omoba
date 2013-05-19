#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>



namespace o__O
{


	class String;



	typedef std::vector<String> Strings;



    class String
    {
    
        public:
        
                                    String ( void );

                                    String ( const std::string& stdString );
            
                                    String ( const float floatNumber );
            
                                    String ( const int integerNumber );
        
            String&                 operator= ( const std::string& stdString );
			
			char&					operator[] ( const int characterPosition );
			
			const char&				operator[] ( const int characterPosition ) const;
			
			bool					operator== ( const std::string& stdString );
			
			bool					operator!= ( const std::string& stdString );
			
			int						getLength ( void );
            
            std::string&            toStdString ( void );
			
			float					toFloat ( void );
			
			int						toInt ( void );
        
            Strings					split ( char delimiter );
            
        private:
        
            std::string             string;
        
    };



};