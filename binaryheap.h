#pragma once
#ifndef __BINARYHEAP_H__
#define __BINARYHEAP_H__
/*
 *		BinaryHeap.h
 *
 *		BinaryHeap implementation. Used whenever a priority queue is needed but
 *		is faster. Comparer must be a functor that will return 1, or -1 depending
 *		whether on which of its arguments is the maximum or minimum. To implement
 *		a minimum binary heap Comparer must return 1, or -1 depending on which of
 *		its arguments is the minimum. To implement a maximum binary heap Comparer
 *		must return 1, or -1 depending on which of its arguments is the maximum.
 *		If both arguments are equal, then Comparer must return 0. To improve 
 *		performance AnyType could be a pointer and thus completely avoid the neccesary
 *		array swaps where copying occurs.
 *		
 *		Also note it is possible for the Comparer functor to return positive integers
 *		for 1, and negative integers for -1.
 *		
 *		insert( )		-	O(log N)
 *		remove( )		-	O(log N)
 *		get( )			-   O(1)
 *		getSize( )		-	O(1)
 *
 *		4/29/05 - Coded by Joseph A. Marrero
 */
#include "DefaultCompare.h"


namespace UTILITY {

template <class AnyType, class Comparer = DefaultCompare>
class BinaryHeap
{
public:

	BinaryHeap( ) : arraySize( 32 ), size( 0 ), currentPosition( 1 )
	{
		dataHeap = new AnyType[ 32 ];
		memset( dataHeap, 0, sizeof( AnyType ) );

	}

	BinaryHeap( const unsigned int intialSize ) : arraySize( intialSize ), size( 0 ), currentPosition( 1 )
	{
		dataHeap = new AnyType[ intialSize ];
		memset( dataHeap, 0, sizeof( AnyType ) );
	}

	~BinaryHeap( )
	{
		if( dataHeap != 0 )
			delete [] dataHeap;
	}

	unsigned int getSize( ) const { return size; }
	bool isEmpty( ) const { return size <= 0; }

	bool increaseHeapSize( const unsigned int newHeapSize )
	{
		if( newHeapSize < arraySize )
			return false;
		AnyType *newDataHeap = new AnyType[ newHeapSize ];	  // 2s + 1  because s could be 0

		for( unsigned int idx = 1; idx <= size; idx++ )
			newDataHeap[ idx ] = dataHeap[ idx ];

		delete [] dataHeap;
		//dataHeap = NULL;	// unneccessary since it will be overwritten
		dataHeap = newDataHeap;
		arraySize = newHeapSize;
		return true;
	}

	void insert( const AnyType &Data )
	{
		if( size == arraySize - 1 )
			doubleSize( );
		
		int hole = size;
		dataHeap[ 0 ] = Data;
		for( ; getMinOrMax( Data, dataHeap[ hole / 2 ] ) < 0; hole /= 2 )
			dataHeap[ hole ] = dataHeap[ hole / 2 ];
		dataHeap[ hole ] = Data;
	}

	void remove( )
	{
		if( size <= 0 ) return;
		dataHeap[ 1 ] = dataHeap[ size-- ];
		#ifdef _DEBUG
		memset( dataHeap + size + 1, 0, sizeof( AnyType ) );
		#endif
		percolateDown( 1 );
	}

	AnyType get( ) const
	{
		return dataHeap[ 1 ];
	}

	void clear( )
	{
		memset( dataHeap, 0, sizeof(AnyType) * arraySize );
		size = 0;
	}

	BinaryHeap<AnyType, Comparer> &operator=( const BinaryHeap<AnyType, Comparer> &cpBinaryHeap )
	{
		
		arraySize = cpBinaryHeap.arraySize;
		currentPosition = cpBinaryHeap.currentPosition;
		getMinOrMax = cpBinaryHeap.getMinOrMax;
		size = cpBinaryHeap.size;

		delete [] dataHeap;
		//dataHeap = NULL;	// unneccessary since it will be overwritten
		dataHeap = new AnyType[ arraySize ];
		for( unsigned int idx = 1; idx <= size; idx++ )
			dataHeap[ idx ] = cpBinaryHeap.dataHeap[ idx ];

		return *this;
	}

private:
	void swap( unsigned int i, unsigned int j )
	{
		if( 0 <= i && i < arraySize && 0 <= j && j < arraySize )
		{
			AnyType temp = dataHeap[ i ];
			dataHeap[ i ] = dataHeap[ j ];
			dataHeap[ j ] = temp;
		}
	}
	void doubleSize( )
	{	
		arraySize = 2 * size + 2;
		AnyType *newDataHeap = new AnyType[ arraySize ];	  // 2s + 2  because s could be 0 and nothing will ever be at index 0
		
		for( unsigned int idx = 1; idx <= size; idx++ )
			newDataHeap[ idx ] = dataHeap[ idx ];

		delete [] dataHeap;
		//dataHeap = NULL;	// unneccessary since it will be overwritten
		dataHeap = newDataHeap;
	}
	unsigned int getParent( ) const
	{
		//unsigned int index = currentPosition >> 1; // p / 2
		//return ( index < size + 1 ? index : 0 );
		return currentPosition >> 1;
	}
	unsigned int leftChild( )
	{
		//unsigned int index = currentPosition << 1;// p = 2 * p
		//return ( index < size + 1 ? index : 0 );
		return currentPosition << 1;
	}
	unsigned int rightChild( )
	{
		//unsigned int index =  (currentPosition << 1) + 1; // p = 2 * p + 1
		//return ( index < size + 1 ? index : 0 );
		return (currentPosition << 1) + 1;
	}

	void percolateDown( int hole )
	{
		int child;
		AnyType tmp = dataHeap[ hole ];

		for( ; hole * 2 <= size; hole = child )
		{
			child = hole * 2;
			if( child != size && getMinOrMax( dataHeap[ child + 1], dataHeap[ child ] ) < 0 )
				child++;
			if( getMinOrMax( dataHeap[ child ], tmp ) < 0 )
				dataHeap[ hole ] = dataHeap[ child ];
			else
				break;
		}

		dataHeap[ hole ] = tmp;
	}

private:
	AnyType *dataHeap;
	Comparer getMinOrMax;
	unsigned int size,
				 arraySize,
				 currentPosition;
};

}// end of namespace
#endif