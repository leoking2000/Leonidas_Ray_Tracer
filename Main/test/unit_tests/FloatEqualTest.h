#pragma once
#include <iostream>
#include <assert.h>

#include "test.h"
#include "LRT.h"

void FloatEqualTest()
{
	std::cout << "Float Equal Test.....";

	/** Regular large numbers */
	assert( LRT::Equal(1000000.0f, 1000001.0f));
	assert( LRT::Equal(1000001.0f, 1000000.0f));
	assert(!LRT::Equal(10000.0f  , 10001.0f));
	assert(!LRT::Equal(10001.0f  , 10000.0f));

	/** Negative large numbers */
	assert( LRT::Equal(-1000000.0f, -1000001.0f));
	assert( LRT::Equal(-1000001.0f, -1000000.0f));
	assert(!LRT::Equal(-10000.0f  , -10001.0f));
	assert(!LRT::Equal(-10001.0f  , -10000.0f));

	/** Numbers around 1 */
	assert( LRT::Equal(1.000001f, 1.000002f));
	assert( LRT::Equal(1.000002f, 1.000001f));
	assert(!LRT::Equal(1.0002f  , 1.0001f));
	assert(!LRT::Equal(1.0001f  , 1.0002f));

	/** Numbers around -1 */
	assert( LRT::Equal(-1.000001f, -1.000002f));
	assert( LRT::Equal(-1.000002f, -1.000001f));
	assert(!LRT::Equal(-1.0002f  , -1.0001f));
	assert(!LRT::Equal(-1.0001f  , -1.0002f));

	/** Numbers between 0 and 1 */
	assert( LRT::Equal(0.000000001000001f, 0.000000001000002f));
	assert( LRT::Equal(0.000000001000002f, 0.000000001000001f));
	assert(!LRT::Equal(0.000000000001002f, 0.000000000001001f));
	assert(!LRT::Equal(0.000000000001001f, 0.000000000001002f));

	/** Numbers between -1 and 0 */
	assert( LRT::Equal(-0.000000001000001f, -0.000000001000002f));
	assert( LRT::Equal(-0.000000001000002f, -0.000000001000001f));
	assert(!LRT::Equal(-0.000000000001002f, -0.000000000001001f));
	assert(!LRT::Equal(-0.000000000001001f, -0.000000000001002f));

	/** Small differences away from zero */
	assert(LRT::Equal( 0.3f,  0.30000003f));
	assert(LRT::Equal(-0.3f, -0.30000003f));

	/** Comparisons involving zero */
	assert( LRT::Equal(0.0f, 0.0f));
	assert( LRT::Equal(0.0f, -0.0f));
	assert( LRT::Equal(-0.0f, -0.0f));
	assert(!LRT::Equal(0.00000001f, 0.0f));
	assert(!LRT::Equal(0.0f, 0.00000001f));
	assert(!LRT::Equal(-0.00000001f, 0.0f));
	assert(!LRT::Equal(0.0f, -0.00000001f));

	assert( LRT::Equal(0.0f, 1e-40f, 0.01f));
	assert( LRT::Equal(1e-40f, 0.0f, 0.01f));
	assert(!LRT::Equal(1e-40f, 0.0f, 0.000001f));
	assert(!LRT::Equal(0.0f, 1e-40f, 0.000001f));

	assert(LRT::Equal(0.0f, -1e-40f, 0.1f));
	assert(LRT::Equal(-1e-40f, 0.0f, 0.1f));
	assert(!LRT::Equal(-1e-40f, 0.0f, 0.00000001f));
	assert(!LRT::Equal(0.0f, -1e-40f, 0.00000001f));

	/** Comparisons of numbers on opposite sides of 0 */
	assert(!LRT::Equal(1.000000001f, -1.0f));
	assert(!LRT::Equal(-1.0f, 1.000000001f));
	assert(!LRT::Equal(-1.000000001f, 1.0f));
	assert(!LRT::Equal(1.0f, -1.000000001f));

	std::cout << "OK\n";
}