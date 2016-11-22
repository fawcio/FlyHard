/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Sławomir Cielepak
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <gtest/gtest.h>
#include "Units.hpp"

namespace SFGame
{

TEST(UnitsSystemTests, NewtonsThirdLaw)
{
	auto distance = 7_m;
	auto time = 1_s;
	auto mass = 80.7_kg;
	auto accelerationMPS = distance/(time*time);
	auto accelerationG = 0.7138013490845498_G;

	// Cross compare with literals
	EXPECT_EQ(0.7138013490845498_G, accelerationMPS);
	EXPECT_EQ(7_mps2, accelerationG);

	// Quantities are exactly the same.
	EXPECT_FLOAT_EQ(accelerationMPS.getValue(), accelerationG.getValue());

	// Calculate force
	auto forceN = mass*accelerationMPS;
	auto forceLbf = mass*accelerationG;

	// Cross compare with literals
	EXPECT_EQ(126.99457195702645_lbf, forceN);
	EXPECT_EQ(564.9_N, forceLbf);

	// Again quantities are exactly the same
	EXPECT_FLOAT_EQ(forceN.getValue(), forceLbf.getValue());

	// Compare casted values
	EXPECT_FLOAT_EQ(564.9, forceN.as(newton));
	EXPECT_FLOAT_EQ(564.9, forceLbf.as(newton));
	EXPECT_FLOAT_EQ(126.99457195702645, forceN.as(poundforce));
	EXPECT_FLOAT_EQ(126.99457195702645, forceLbf.as(poundforce));

	// Comparison with finite precision
	EXPECT_NEAR(forceN.as(poundforce), 126.99457, 0.00001);
}

}
