/* -*- mode: c++; c-basic-offset: 4; indent-tabs-mode: nil -*-

   this file is part of rcssserver3D
   Fri May 9 2003
   Copyright (C) 2002,2003 Koblenz University
   Copyright (C) 2004 RoboCup Soccer Server 3D Maintenance Group
   $Id: random.h 56 2009-03-17 18:03:47Z hedayat $

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/
#ifndef SALT_RANDOM_H
#define SALT_RANDOM_H

#include <boost/random.hpp>
#include <boost/version.hpp>
#include "salt_defines.h"

namespace salt
{
#if 0
}
#endif

/** A wrapper to a boost random number generator.
 *
 * This class was created so that the underlying generator can be exchanged
 * easily. Making this class a singleton prevents initializing the generator
 * more than once (which can be expensive).
 *
 * The only thing users should do with this class is to set the seed of the
 * generator. To actually create random numbers, use one of the Random
 * Number Generator Classes that map the numbers to a specific distribution
 * and provide an operator()() to access random numbers.
 */
class RandomEngine : public boost::mt19937
{
public:
    typedef boost::mt19937::result_type result_type;

    static RandomEngine& instance()
    { static RandomEngine the_instance; return the_instance; }

    static RandomEngine&
#if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x520)
    // Work around overload resolution problem (Gennadiy E. Rozental)
    instance(const result_type& value)
#else
    instance(result_type value)
#endif
    { instance().seed( value ); return instance(); }

    // For GCC, moving this function out-of-line prevents inlining, which may
    // reduce overall object code size.  However, MSVC does not grok
    // out-of-line definitions of member function templates.
    template<class Generator>
    static RandomEngine& instance(Generator& gen)
    { instance().seed( gen ); return instance(); }
private:
    RandomEngine() : boost::mt19937() { }
};

#if (defined(BOOST_VERSION) && (BOOST_VERSION >= 103100))
#include <boost/random/variate_generator.hpp>

/** This random number generator should be used to produce
 *  uniformly distributed random numbers.
 */
template<class RealType = double>
class UniformRNG : public boost::variate_generator<salt::RandomEngine,
                                                   boost::uniform_real<RealType> >
{
public:
    UniformRNG(RealType min = RealType(0), RealType max = RealType(1))
        : boost::variate_generator<RandomEngine, boost::uniform_real<RealType> >
    (salt::RandomEngine::instance(), boost::uniform_real<RealType>(min,max))
    {}
};

/** A random number generator producing normally distributed numbers.
 */
template<class RealType = double>
class NormalRNG : public boost::variate_generator<salt::RandomEngine,
                                                  boost::normal_distribution<RealType> >
{
public:
    NormalRNG(double mean, double sigma = (1))
        : boost::variate_generator<RandomEngine,
                                   boost::normal_distribution<RealType> >
    (salt::RandomEngine::instance(), boost::normal_distribution<RealType>(mean,sigma))
    {}
};

/** A random number generator with an exponential distribution.
 *
 * exponential distribution: p(x) = lambda * exp(-lambda * x)
 */
template<class RealType = double>
class ExponentialRNG : public boost::variate_generator<salt::RandomEngine,
                                                       boost::exponential_distribution<RealType> >
{
public:
    ExponentialRNG(double lambda = RealType(1))
        : boost::variate_generator<RandomEngine,
                                   boost::exponential_distribution<RealType> >
    (salt::RandomEngine::instance(),
     boost::exponential_distribution<RealType>(lambda))
    {}
};

#else // BOOST_VERSION >= 103100

/** This random number generator should be used to produce
 *  uniformly distributed random numbers.
 */
template<class RealType = double>
class UniformRNG : public boost::uniform_real<salt::RandomEngine,RealType>
{
public:
    UniformRNG(RealType min = RealType(0), RealType max = RealType(1))
        : boost::uniform_real<RandomEngine,RealType>
    (salt::RandomEngine::instance(),min,max)
    {}
};

/** A random number generator producing normally distributed numbers.
 */
template<class RealType = double>
class NormalRNG : public boost::normal_distribution<salt::RandomEngine>
{
public:
    NormalRNG(double mean, double sigma = (1))
        : boost::normal_distribution<salt::RandomEngine>
    (salt::RandomEngine::instance(),mean,sigma)
    {}
};

/** A random number generator with an exponential distribution.
 *
 * exponential distribution: p(x) = lambda * exp(-lambda * x)
 */
template<class RealType = double>
class ExponentialRNG : public boost::exponential_distribution<salt::RandomEngine>
{
public:
    ExponentialRNG(double lambda = RealType(1))
        : boost::exponential_distribution<salt::RandomEngine>
    (salt::RandomEngine::instance(),lambda)
    {}
};

#endif

} // namespace salt

#endif // SALT_RANDOM_H
