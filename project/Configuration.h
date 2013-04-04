#pragma once

#include <map>



namespace omoba
{


	
	template <typename KeyType>
	class IKey
	{
	
		
	
	
	
	}
	
	
	
	template <typename ParameterValueType>
	class IParameter
	{
	
		public:
		
									IParameter ( ParameterValueType& valueCurrent )
										:
											valueCurrent ( valueCurrent )
			{
			
			}
		
			ParameterValueType&		getValueCurrent ( void ) const
			{
			
				return this->valueCurrent;
			
			}
			
			void					setValueCurrent ( ParameterValueType& valueCurrent )
			{
			
				this->valueCurrent = valueCurrent;
			
			}
			
		private:
		
			ParameterValueType		valueCurrent;
			
	};
	
	
	
	template <typename ParameterValueType>
	class IParameterDefaultable
		:
			public IParameter
	{
	
		public:
		
									IParameterDefaultable ( ParameterValueType& valueCurrent , ParameterValueType& valueDefault )
										:
											valueCurrent ( valueCurrent ),
											valueDefault ( valueDefault )
			{
			
			}
			
			ParameterValueType&		getValueDefault ( void ) const
			{
			
				return this->valueDefault;
			
			}
			
			void					setValueDefault ( ParameterValueType& valueDefault )
			{
			
				this->valueDefault = valueDefault;
			
			}
			
			void					resetValueCurrent ( void )
			{
			
				this->valueCurrent = this->valueDefault;
				
			}

		private:
	
			ParameterValueType		valueDefault;
	
	};
	


	template <typename ParameterValueType>
	using NamedParameter = std::pair<std::string,IParameter<ParameterValueType> >;
	
	
	
	template <typename ParameterValueType>
	using ParametersMap = std::map<NamedParameter<ParameterValueType> >;


	
	template <typename ParameterValueType>
	class IConfiguration
		:
			private ParametersMap<ParameterValueType>
	{
	
		public:
		
			class								ExcUndefinedParameterCalled { };
		
			bool								getParameterExists ( const std::string parameterName )
			{
			
				return	this->find(parameterName) == this->end()
							?
						false
							:
						true;
			
			}
			
			IParameter<ParameterValueType>&		getParameter ( const std::string parameterName )
			{
			
				this->checkParameterExists();
				
				return this->find(parameterName)->second;
				
			}
			
			void								setParameter ( const IParameter<ParameterValueType>& parameter )
			{
			
				//	Checking if parameter exists
				try
				{
				
					this->checkParameterExists();

					this->find(parameterName)->second = parameter;
				
				}
				
				//	Parameter doesn't exist yet
				catch ( ExcUndefinedParameterCalled exception )
				{
				
					this->insert(NamedParameter<ParameterValueType>(parameterName,parameter));
				
				}
				
			}
			
			void								deleteParameter ( const std::string parameterName , bool strict = true )
			{
			
				if ( strict )
					this->checkParameterExists();

				this->erase(parameterName);
			
			}
			
		private:

			void 								checkParameterExists ( const std::string parameterName ) const
			{
			
				if ( ! this->getParameterExists(parameterName) )
					throw ExcUndefinedParameterCalled();
			
			}

	};
	

	
	template <typename ParameterValueType>
	class IConfigurable
	{
	
		public:
		
			IConfiguration<ParameterValueType>&		getConfiguration ( void )
			{
			
				return this->configuration;
			
			}
		
		private:
			IConfiguration<ParameterValueType>		configuration;
	
	};
	

	
	typedef std::pair<std::string,float>	Parameter;


	
	class Configuration
		:
			private std::map<std::string,float>
	{

		public:

			bool			getParameterExists ( const std::string parameterName );
			
			QVariant		getParameterValue ( const std::string parameterName ) const;

			void			setParameterValue ( const std::string parameterName , const float parameterValue );
			
			void			deleteParameter ( const std::string parameterName );
			
			class			ExcUndefinedParameterCalled { };
			
		private:

			void 			checkParameterExists ( const int attributeId ) const;
			
	};

};