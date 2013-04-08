#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace o__O
{
    
    class String
    {
    
        public:
        
                                    String ( void );

                                    String ( const std::string& stdString );
            
                                    String ( const float floatString );
            
                                    String ( const int integerString );
        
            String&                 operator= ( const std::string& stdString );
            
            std::string&            getStdString ( void );
        
            std::vector<String>     split ( char delimiter );
            
        private:
        
            std::string             string;
        
    };
    
};