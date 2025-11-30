#include "pch.h"
#include "CppUnitTest.h"
#include <cmath>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

// Declare the function under test (the test project must link Lab 5.3.cpp)
extern double k(double x);

namespace UnitTest53
{
	TEST_CLASS(UnitTest53)
	{
	public:

		TEST_METHOD(TestSeriesBranch_ForSmallX)
		{
			// x with |x| < 1 should use the series sum: sum_{i=0..5} x^i / i!
			double x = 0.5;
			double expected = 1.6486979166666666; // precomputed partial sum for x=0.5
			double actual = k(x);
			Assert::AreEqual(expected, actual, 1e-12, L"Series branch returned unexpected value for x=0.5");
		}

		TEST_METHOD(TestFormulaBranch_AtBoundaryAndAbove)
		{
			// x = 1.0 should take the formula branch (fabs(x) >= 1)
			double x = 1.0;
			double expected = (std::exp(x) + std::sin(x)) / (std::cos(x * x) + 1.0);
			double actual = k(x);
			Assert::AreEqual(expected, actual, 1e-12, L"Formula branch mismatch for x=1.0");

			// also test a value > 1
			x = 2.0;
			expected = (std::exp(x) + std::sin(x)) / (std::cos(x * x) + 1.0);
			actual = k(x);
			Assert::AreEqual(expected, actual, 1e-12, L"Formula branch mismatch for x=2.0");
		}

		TEST_METHOD(TestCompositeFunction_fz_AtZero)
		{
			// f(z) = k(z^2 + 1) - k(z^2 - 1) + 2*k(z)
			// Use z = 0.0 and compute expected using direct math (avoids calling k for expected)
			double z = 0.0;

			// k(1) and k(-1) use formula branch because |1| >= 1 and |-1| >= 1
			double k1 = (std::exp(1.0) + std::sin(1.0)) / (std::cos(1.0 * 1.0) + 1.0);
			double km1 = (std::exp(-1.0) + std::sin(-1.0)) / (std::cos((-1.0) * (-1.0)) + 1.0);
			double expected = k1 - km1 + 2.0 * 1.0; // k(0) = series with x=0 => 1.0

			double actual = k(z * z + 1.0) - k(z * z - 1.0) + 2.0 * k(z);
			Assert::AreEqual(expected, actual, 1e-12, L"Composite f(z) mismatch at z=0.0");
		}
	};
}