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
#pragma once

#include <ratio>
#include <cmath>

#include "Constants.hpp"

/**
 * @brief Units example
 *
 * Length someLen = 7.4_cm;
 *
 * std::cout << "Length: " << someLen.as(pixel) << " px == " << someLen.as(millimetre) << " mm == "
 *			 << someLen.as(inch) << " inches == " << someLen.as(metre) << " m\n";
 *
 * Acceleration a = 7_G;
 * Mass m = 80.7_kg;
 *
 * Force f = m * a;
 *
 * std::cout << m.as(kg) << "kg on " << a.as(mps2) << " mps2 produces force equal to " << f.as(newton) << " N\n";
 * std::cout << m.as(pound) << "lbs on " << a.as(G) << " G produces force equal to " << f.as(newton) << " N\n";
 *
 */


namespace SFGame
{

/*!
 * @brief The Quantity class is the prototype template container class, that just holds a double value. The
 * class SHOULD NOT BE INSTANTIATED directly by itself, rather use the quantity types defined below.
 */
template<typename MassDim, typename LengthDim, typename TimeDim, typename AngleDim>
class Quantity
{
private:
	double value;

public:
	constexpr Quantity() : value(0.0) {}
	constexpr Quantity(double val) : value(val) {}
	constexpr Quantity(long double val) : value(static_cast<double>(val)) {}

	// The intrinsic operations for a quantity with a unit is addition and subtraction
	constexpr Quantity const& operator+=(const Quantity& rhs)
	{
		value += rhs.value;
		return *this;
	}
	constexpr Quantity const& operator-=(const Quantity& rhs)
	{
		value -= rhs.value;
		return *this;
	}

	// Returns the value of the quantity in multiples of the specified unit
	constexpr double as(const Quantity& rhs) const
	{
		return value / rhs.value;
	}

	// returns the raw value of the quantity (should not be used)
	constexpr double getValue() const
	{
		return value;
	}
};

// Predefined (physical unit) quantity types:
// ------------------------------------------
#define QUANTITY_TYPE(_Mdim, _Ldim, _Tdim, _Adim, name) \
	typedef Quantity<std::ratio<_Mdim>, std::ratio<_Ldim>, std::ratio<_Tdim>, std::ratio<_Adim>> name

// Replacement of "double" type
QUANTITY_TYPE(0, 0, 0, 0, Number);

// Physical quantity types
QUANTITY_TYPE(1, 0, 0, 0, Mass);
QUANTITY_TYPE(0, 1, 0, 0, Length);
QUANTITY_TYPE(0, 2, 0, 0, Area);
QUANTITY_TYPE(0, 3, 0, 0, Volume);
QUANTITY_TYPE(0, 0, 1, 0, Time);
QUANTITY_TYPE(0, 1, -1, 0, Speed);
QUANTITY_TYPE(0, 1, -2, 0, Acceleration);
QUANTITY_TYPE(0, 1, -3, 0, QJerk);
QUANTITY_TYPE(0, 0, -1, 0, Frequency);
QUANTITY_TYPE(1, 1, -2, 0, Force);
QUANTITY_TYPE(1, -1, -2, 0, Pressure);

// Angle type:
QUANTITY_TYPE(0, 0, 0, 1, Angle);


// Standard arithmetic operators:
// ------------------------------
template <typename M, typename L, typename T, typename A>
constexpr Quantity<M, L, T, A>
	operator+(const Quantity<M, L, T, A>& lhs, const Quantity<M, L, T, A>& rhs)
{
	return Quantity<M, L, T, A>(lhs.getValue() + rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr Quantity<M, L, T, A>
	operator-(const Quantity<M, L, T, A>& lhs, const Quantity<M, L, T, A>& rhs)
{
	return Quantity<M, L, T, A>(lhs.getValue() - rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr Quantity<M, L, T, A>
	operator-(const Quantity<M, L, T, A>& rhs)
{
	return Quantity<M, L, T, A>(rhs.getValue());
}

template <typename M1, typename L1, typename T1, typename A1,
		  typename M2, typename L2, typename T2, typename A2>
constexpr Quantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>,
					std::ratio_add<T1, T2>, std::ratio_add<A1, A2>>
	operator*(const Quantity<M1, L1, T1, A1>& lhs, const Quantity<M2, L2, T2, A2>& rhs)
{
	return Quantity<std::ratio_add<M1, M2>, std::ratio_add<L1, L2>,
					 std::ratio_add<T1, T2>, std::ratio_add<A1, A2>>
					(lhs.getValue()*rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr Quantity<M, L, T, A>
	operator*(const double& lhs, const Quantity<M, L, T, A>& rhs)
{
	return Quantity<M, L, T, A>(lhs*rhs.getValue());
}

template <typename M1, typename L1, typename T1, typename A1,
		  typename M2, typename L2, typename T2, typename A2>
constexpr Quantity<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>,
					std::ratio_subtract<T1, T2>, std::ratio_subtract<A1, A2>>
	operator/(const Quantity<M1, L1, T1, A1>& lhs, const Quantity<M2, L2, T2, A2>& rhs)
{
	return Quantity<std::ratio_subtract<M1, M2>, std::ratio_subtract<L1, L2>,
					 std::ratio_subtract<T1, T2>, std::ratio_subtract<A1, A2>>
					(lhs.getValue() / rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr Quantity<std::ratio_subtract<std::ratio<0>, M>, std::ratio_subtract<std::ratio<0>, L>,
					std::ratio_subtract<std::ratio<0>, T>, std::ratio_subtract<std::ratio<0>, A>>
	operator/(double x, const Quantity<M, L, T, A>& rhs)
{
	return Quantity<std::ratio_subtract<std::ratio<0>, M>, std::ratio_subtract<std::ratio<0>, L>,
					 std::ratio_subtract<std::ratio<0>, T>, std::ratio_subtract<std::ratio<0>, A>>
					(x / rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr Quantity<M, L, T, A>
	operator/(const Quantity<M, L, T, A>& rhs, double x)
{
	return Quantity<M, L, T, A>(rhs.getValue() / x);
}


// Comparison operators for quantities:
// ------------------------------------
template <typename M, typename L, typename T, typename A>
constexpr bool operator==(const Quantity<M, L, T, A>& lhs, const Quantity<M, L, T, A>& rhs)
{
	return (lhs.getValue() == rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr bool operator!=(const Quantity<M, L, T, A>& lhs, const Quantity<M, L, T, A>& rhs)
{
	return (lhs.getValue() != rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr bool operator<=(const Quantity<M, L, T, A>& lhs, const Quantity<M, L, T, A>& rhs)
{
	return (lhs.getValue() <= rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr bool operator>=(const Quantity<M, L, T, A>& lhs, const Quantity<M, L, T, A>& rhs)
{
	return (lhs.getValue() >= rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr bool operator< (const Quantity<M, L, T, A>& lhs, const Quantity<M, L, T, A>& rhs)
{
	return (lhs.getValue()<rhs.getValue());
}

template <typename M, typename L, typename T, typename A>
constexpr bool operator> (const Quantity<M, L, T, A>& lhs, const Quantity<M, L, T, A>& rhs)
{
	return (lhs.getValue()>rhs.getValue());
}


// Predefined units:
// -----------------

// Predefined mass units:
constexpr Mass kg(1.0);                        // SI base unit
constexpr Mass gramme = 0.001 * kg;
constexpr Mass tonne = 1000 * kg;
constexpr Mass ounce = 0.028349523125 * kg;
constexpr Mass pound = 16 * ounce;
constexpr Mass stone = 14 * pound;

// Predefined length-derived units
constexpr Length metre(1.0);                   // SI base unit
constexpr Length decimetre = metre / 10;
constexpr Length centimetre = metre / 100;
constexpr Length millimetre = metre / 1000;
constexpr Length kilometre = 1000 * metre;
constexpr Length inch = 2.54 * centimetre;
constexpr Length foot = 12 * inch;
constexpr Length yard = 3 * foot;
constexpr Length mile = 5280 * foot;
constexpr Length pixel = cWorldScale*cDpi*millimetre;

constexpr Area kilometre2 = kilometre*kilometre;
constexpr Area metre2 = metre*metre;
constexpr Area decimetre2 = decimetre*decimetre;
constexpr Area centimetre2 = centimetre*centimetre;
constexpr Area millimetre2 = millimetre * millimetre;
constexpr Area inch2 = inch*inch;
constexpr Area foot2 = foot*foot;
constexpr Area mile2 = mile*mile;

constexpr Volume kilometre3 = kilometre2*kilometre;
constexpr Volume metre3 = metre2*metre;
constexpr Volume decimetre3 = decimetre2*decimetre;
constexpr Volume litre = decimetre3;
constexpr Volume centimetre3 = centimetre2*centimetre;
constexpr Volume millimetre3 = millimetre2 * millimetre;
constexpr Volume inch3 = inch2*inch;
constexpr Volume foot3 = foot2*foot;
constexpr Volume mile3 = mile2*mile;

// Predefined time-derived units:
constexpr Time second(1.0);                  // SI base unit
constexpr Time msecond = 0.001 * second;
constexpr Time usecond = 0.000001 * second;
constexpr Time minute = 60 * second;
constexpr Time hour = 60 * minute;
constexpr Time day = 24 * hour;

constexpr Frequency Hz(1.0);

// Predefined mixed units:
constexpr Acceleration mps2(1.0);
constexpr Acceleration G = 9.80665*mps2;

constexpr Force newton(1.0);
constexpr Force poundforce = pound*G;
constexpr Force kilopond = kg*G;

constexpr Pressure Pascal(1.0);
constexpr Pressure bar = 100000 * Pascal;
constexpr Pressure psi = pound*G / inch2;


// Physical unit literals:
// -----------------------

// literals for length units
constexpr Length operator"" _mm(long double x) { return static_cast<double>(x)*millimetre; }
constexpr Length operator"" _cm(long double x) { return static_cast<double>(x)*centimetre; }
constexpr Length operator"" _m(long double x) { return static_cast<double>(x)*metre; }
constexpr Length operator"" _km(long double x) { return static_cast<double>(x)*kilometre; }
constexpr Length operator"" _mi(long double x) { return static_cast<double>(x)*mile; }
constexpr Length operator"" _yd(long double x) { return static_cast<double>(x)*yard; }
constexpr Length operator"" _ft(long double x) { return static_cast<double>(x)*foot; }
constexpr Length operator"" _in(long double x) { return static_cast<double>(x)*inch; }
constexpr Length operator"" _mm(unsigned long long int x) { return static_cast<double>(x)*millimetre; }
constexpr Length operator"" _cm(unsigned long long int  x) { return static_cast<double>(x)*centimetre; }
constexpr Length operator"" _m(unsigned long long int  x) { return static_cast<double>(x)*metre; }
constexpr Length operator"" _km(unsigned long long int  x) { return static_cast<double>(x)*kilometre; }
constexpr Length operator"" _mi(unsigned long long int  x) { return static_cast<double>(x)*mile; }
constexpr Length operator"" _yd(unsigned long long int  x) { return static_cast<double>(x)*yard; }
constexpr Length operator"" _ft(unsigned long long int  x) { return static_cast<double>(x)*foot; }
constexpr Length operator"" _in(unsigned long long int  x) { return static_cast<double>(x)*inch; }

constexpr Length operator"" _px(long double x) { return static_cast<double>(x)*pixel; }
constexpr Length operator"" _px(unsigned long long int  x) { return static_cast<double>(x)*pixel; }

// literals for speed units
constexpr Speed operator"" _mps(long double x) { return Speed(x); }
constexpr Speed operator"" _miph(long double x) { return static_cast<double>(x)*mile / hour; }
constexpr Speed operator"" _kmph(long double x) { return static_cast<double>(x)*kilometre / hour; }
constexpr Speed operator"" _mps(unsigned long long int x)
								{ return Speed(static_cast<long double>(x)); }
constexpr Speed operator"" _miph(unsigned long long int x)
								 { return static_cast<double>(x)*mile / hour; }
constexpr Speed operator"" _kmph(unsigned long long int x)
								 { return static_cast<double>(x)*kilometre / hour; }

// literal for frequency unit
constexpr Frequency operator"" _Hz(long double x) { return Frequency(x); }
constexpr Frequency operator"" _Hz(unsigned long long int x)
								   { return Frequency(static_cast<long double>(x)); }

// literals for time units
constexpr Time operator"" _s(long double x) { return Time(x); }
constexpr Time operator"" _ms(long double x) { return static_cast<double>(x)*msecond; }
constexpr Time operator"" _us(long double x) { return static_cast<double>(x)*usecond; }
constexpr Time operator"" _min(long double x) { return static_cast<double>(x)*minute; }
constexpr Time operator"" _h(long double x) { return static_cast<double>(x)*hour; }
constexpr Time operator"" _day(long double x) { return static_cast<double>(x)*day; }
constexpr Time operator"" _s(unsigned long long int x) { return Time(static_cast<double>(x)); }
constexpr Time operator"" _ms(unsigned long long int x) { return static_cast<double>(x)*msecond; }
constexpr Time operator"" _us(unsigned long long int x) { return static_cast<double>(x)*usecond; }
constexpr Time operator"" _min(unsigned long long int x) { return static_cast<double>(x)*minute; }
constexpr Time operator"" _h(unsigned long long int x) { return static_cast<double>(x)*hour; }
constexpr Time operator"" _day(unsigned long long int x) { return static_cast<double>(x)*day; }

// literals for mass units
constexpr Mass operator"" _kg(long double x) { return Mass(x); }
constexpr Mass operator"" _g(long double x) { return static_cast<double>(x)*gramme; }
constexpr Mass operator"" _t(long double x) { return static_cast<double>(x)*tonne; }
constexpr Mass operator"" _oz(long double x) { return static_cast<double>(x)*ounce; }
constexpr Mass operator"" _lb(long double x) { return static_cast<double>(x)*pound; }
constexpr Mass operator"" _st(long double x) { return static_cast<double>(x)*stone; }
constexpr Mass operator"" _kg(unsigned long long int x) { return Mass(static_cast<double>(x)); }
constexpr Mass operator"" _g(unsigned long long int x) { return static_cast<double>(x)*gramme; }
constexpr Mass operator"" _t(unsigned long long int x) { return static_cast<double>(x)*tonne; }
constexpr Mass operator"" _oz(unsigned long long int x) { return static_cast<double>(x)*ounce; }
constexpr Mass operator"" _lb(unsigned long long int x) { return static_cast<double>(x)*pound; }
constexpr Mass operator"" _st(unsigned long long int x) { return static_cast<double>(x)*stone; }

// literals for acceleration units
constexpr Acceleration operator"" _mps2(long double x) { return Acceleration(x); }
constexpr Acceleration operator"" _mps2(unsigned long long int x) { return Acceleration(static_cast<double>(x)); }
constexpr Acceleration operator"" _G(long double x) { return static_cast<double>(x)*G; }
constexpr Acceleration operator"" _G(unsigned long long int x) { return static_cast<double>(x)*G; }

// literals for force units
constexpr Force operator"" _N(long double x) { return Force(x); }
constexpr Force operator"" _N(unsigned long long int x) { return Force(static_cast<double>(x)); }
constexpr Force operator"" _lbf(long double x) { return static_cast<double>(x)*poundforce; }
constexpr Force operator"" _lbf(unsigned long long int x) { return static_cast<double>(x)*poundforce; }
constexpr Force operator"" _kp(long double x) { return static_cast<double>(x)*kilopond; }
constexpr Force operator"" _kp(unsigned long long int x) { return static_cast<double>(x)*kilopond; }

// literals for pressure units
constexpr Pressure operator"" _Pa(long double x) { return Pressure(x); }
constexpr Pressure operator"" _Pa(unsigned long long int x)
								  { return Pressure(static_cast<double>(x)); }
constexpr Pressure operator"" _bar(long double x) { return static_cast<double>(x)*bar; }
constexpr Pressure operator"" _bar(unsigned long long int x) { return static_cast<double>(x)*bar; }
constexpr Pressure operator"" _psi(long double x) { return static_cast<double>(x)*psi; }
constexpr Pressure operator"" _psi(unsigned long long int x) { return static_cast<double>(x)*psi; }


// Angular unit literals:
// ----------------------
constexpr long double operator"" _pi(long double x)
	{ return static_cast<double>(x) * 3.1415926535897932384626433832795; }
constexpr long double operator"" _pi(unsigned long long int x)
	{ return static_cast<double>(x) * 3.1415926535897932384626433832795; }

// Predefined angle units:
constexpr Angle radian(1.0);
constexpr Angle degree = static_cast<double>(2_pi / 360.0) * radian;

// literals for angle units
constexpr Angle operator"" _rad(long double x) { return Angle(x); }
constexpr Angle operator"" _rad(unsigned long long int x) { return Angle(static_cast<double>(x)); }
constexpr Angle operator"" _deg(long double x) { return static_cast<double>(x)*degree; }
constexpr Angle operator"" _deg(unsigned long long int x) { return static_cast<double>(x)*degree; }

// Conversion macro, which utilizes the string literals
#define ConvertTo(_x, _y) (_x).Convert(1.0_##_y)



// Typesafe mathematical operations:
// ---------------------------------
template <typename M, typename L, typename T, typename A>
constexpr Quantity<std::ratio_divide<M, std::ratio<2>>, std::ratio_divide<L, std::ratio<2>>,
					std::ratio_divide<T, std::ratio<2>>, std::ratio_divide<A, std::ratio<2>>>
	Qsqrt(const Quantity<M, L, T, A>& num)
{
	return Quantity<std::ratio_divide<M, std::ratio<2>>, std::ratio_divide<L, std::ratio<2>>,
					 std::ratio_divide<T, std::ratio<2>>, std::ratio_divide<A, std::ratio<2>>>
					(sqrt(num.getValue()));
}

// Typesafe trigonometric operations
inline double sin(const Angle &num)
{
	return std::sin(num.getValue());
}
inline double cos(const Angle &num)
{
	return std::cos(num.getValue());
}
inline double tan(const Angle &num)
{
	return std::tan(num.getValue());
}

}
