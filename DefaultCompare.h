#ifndef __DEFAULTCOMPARE_H__
#define __DEFAULTCOMPARE_H__
/*
*	DefaultCompare.h
*
*
*/
namespace UTILITY {

	class DefaultCompare
	{
	public:
		/*
		*	Assumes < and == are overloaded.
		*/
		template <class AnyType> int operator()( const AnyType &o1, const AnyType &o2 ) const
		{
			if( o1 < o2 )
				return -1;
			else if( o1 == o2 )
				return 0;
			else // o1 > 02
				return 1;
		}
		/*
		*	Assumes < and == are overloaded.
		*/
		template <class AnyType> int operator()( AnyType &o1, AnyType &o2 ) const
		{
			if( o1 < o2 )
				return -1;
			else if( o1 == o2 )
				return 0;
			else // o1 > 02
				return 1;
		}

	};

}

#endif