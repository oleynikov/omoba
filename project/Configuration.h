#pragma once

#include <map>



namespace omoba
{


	
	template <typename ParameterValue>
	class IParameter
	{
	
		public:
		
								IParameter ( ParameterValue& valueCurrent )
										:
											valueCurrent ( valueCurrent )
			{
			
			}
		
			ParameterValue&		getValueCurrent ( void ) const
			{
			
				return this->valueCurrent;
			
			}
			
			void				setValueCurrent ( ParameterValue& valueCurrent )
			{
			
				this->valueCurrent = valueCurrent;
			
			}
			
		private:
		
			ParameterValue		valueCurrent;
			
	};
	
	
	
	template <typename ParameterValue>
	class IParameterDefaultable
		:
			public IParameter<ParameterValue>
	{
	
		public:
		
									IParameterDefaultable ( ParameterValue& valueCurrent , ParameterValue& valueDefault )
										:
											IParameter<ParameterValue>  ( valueCurrent ),
											valueDefault                    ( valueDefault )
			{
			
			}
			
			ParameterValue&		getValueDefault ( void ) const
			{
			
				return this->valueDefault;
			
			}
			
			void					setValueDefault ( ParameterValue& valueDefault )
			{
			
				this->valueDefault = valueDefault;
			
			}
			
			void					resetValueCurrent ( void )
			{
			
				this->valueCurrent = this->valueDefault;
				
			}

		private:
	
			ParameterValue		valueDefault;
	
	};
	

/*
c++11

	template <typename ParameterKey,typename ParameterValue>
	using NamedParameter = std::pair<ParameterKey,IParameter<ParameterValue> >;
	
	
	
	template <typename ParameterKey,typename ParameterValue>
	using ParametersMap = std::map<ParameterKey,IParameter<ParameterValue> >;
*/

	
	template <typename ParameterKey,typename ParameterValue>
	class IConfiguration
		:
			private std::map<ParameterKey,IParameter<ParameterValue> >
	{
	
		public:
		
			class							ExcUndefinedParameterCalled { };
		
			bool							getParameterExists ( const ParameterKey& parameterId )
			{
			
				return	this->find(parameterId) == this->end()
							?
						false
							:
						true;
			
			}
			
			IParameter<ParameterValue>&		getParameter ( const ParameterKey& parameterId )
			{
			
				this->checkParameterExists();
				
				return this->find(parameterId)->second;
				
			}
			
			void							setParameter ( const ParameterKey& parameterId , const IParameter<ParameterValue>& parameter )
			{
			
				//	Checking if parameter exists
				try
				{
				
					this->checkParameterExists();

					this->find(parameterId)->second = parameter;
				
				}
				
				//	Parameter doesn't exist yet
				catch ( ExcUndefinedParameterCalled exception )
				{

					this->insert(std::pair<ParameterKey,IParameter<ParameterValue> >(parameterId,parameter));
				
				}
				
			}
			
			void							deleteParameter ( const std::string parameterName , bool strict = true )
			{
			
				if ( strict )
					this->checkParameterExists();

				this->erase(parameterName);
			
			}
			
		private:

			void 							checkParameterExists ( const std::string parameterName ) const
			{
			
				if ( ! this->getParameterExists(parameterName) )
					throw ExcUndefinedParameterCalled();
			
			}

	};
	

	
	template <typename ParameterKey,typename ParameterValue>
	class IConfigurable
	{
	
		public:
		
			IConfiguration<ParameterKey,ParameterValue>&		getConfiguration ( void )
			{
			
				return this->configuration;
			
			}
			
			void												setConfiguration ( const IConfiguration<ParameterKey,ParameterValue>& configuration )
			{
			
				this->configuration = configuration;
			
			}
		
		private:
			IConfiguration<ParameterKey,ParameterValue>			configuration;
	
	};
	


};