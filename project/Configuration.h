#pragma once

#include <map>



namespace omoba
{


	
	class IComparable
	{
	
		virtual bool operator== ( const IComparable& rho ) = 0;
		
	};
	
	
	
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
			public IParameter<ParameterValueType>
	{
	
		public:
		
									IParameterDefaultable ( ParameterValueType& valueCurrent , ParameterValueType& valueDefault )
										:
											IParameter<ParameterValueType>  ( valueCurrent ),
											valueDefault                    ( valueDefault )
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
	


	template <typename ParameterValue>
	using NamedParameter = std::pair<IComparable,IParameter<ParameterValue> >;
	
	
	
	template <typename ParameterValue>
	using ParametersMap = std::map<IComparable,IParameter<ParameterValue> >;


	
	template <typename Comparable,typename ParameterValue>
	class IConfiguration
		:
			private ParametersMap<Comparable,ParameterValue>
	{
	
		public:
		
			class							ExcUndefinedParameterCalled { };
		
			bool							getParameterExists ( const Comparable& parameterId )
			{
			
				return	this->find(parameterId) == this->end()
							?
						false
							:
						true;
			
			}
			
			IParameter<ParameterValue>&		getParameter ( const Comparable& parameterId )
			{
			
				this->checkParameterExists();
				
				return this->find(parameterId)->second;
				
			}
			
			void							setParameter ( const Comparable& parameterId , const IParameter<ParameterValue>& parameter )
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
				
					this->insert(NamedParameter<ParameterValue>(parameterName,parameter));
				
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