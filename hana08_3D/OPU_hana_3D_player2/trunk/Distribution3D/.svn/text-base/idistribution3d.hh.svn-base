/*
 *  Little Green BATS (2007), AI department, University of Groningen
 *
 *  Authors: 	Martin Klomp (martin@ai.rug.nl)
 *		Mart van de Sanden (vdsanden@ai.rug.nl)
 *		Sander van Dijk (sgdijk@ai.rug.nl)
 *		A. Bram Neijt (bneijt@gmail.com)
 *		Matthijs Platje (mplatje@gmail.com)
 *
 *	All students of AI at the University of Groningen
 *  at the time of writing. See: http://www.ai.rug.nl/
 *
 *  Date: 	July 27, 2007
 *
 *  Website:	http://www.littlegreenbats.nl
 *
 *  Comment:	Please feel free to contact us if you have any 
 *		problems or questions about the code.
 *
 *
 *  License: 	This program is free software; you can redistribute 
 *		it and/or modify it under the terms of the GNU General
 *		Public License as published by the Free Software 
 *		Foundation; either version 3 of the License, or (at 
 *		your option) any later version.
 *
 *   		This program is distributed in the hope that it will
 *		be useful, but WITHOUT ANY WARRANTY; without even the
 *		implied warranty of MERCHANTABILITY or FITNESS FOR A
 *		PARTICULAR PURPOSE.  See the GNU General Public
 *		License for more details.
 *
 *   		You should have received a copy of the GNU General
 *		Public License along with this program; if not, write
 *		to the Free Software Foundation, Inc., 59 Temple Place - 
 *		Suite 330, Boston, MA  02111-1307, USA.
 *
 */















#ifndef __INC_BATS_IDISTRIBUTION_HH_
#define __INC_BATS_IDISTRIBUTION_HH_

#include "refable.hh"
#include "vector3.hh"
#include "matrix9.hh"
#include "rf.hh"

namespace bats {

  class IDistribution3D;

  /** \brief The common distribution interface
   *
   * The IDistribution class is an interface for distributions, mainly probability distributions, but can also be used for intentions.
   */
  class IDistribution3D : public RefAble
  {
  public:
    IDistribution3D() {}
    virtual ~IDistribution3D() {}
      
    /** Initialize distribution
     *
     * Initialize the distribution given a normal distribution \f$ N(\mu, \Sigma) \f$
     */
    virtual void init(Vector3D const &mu, Matrix9D const &sigma) = 0;

    /** Get Mu
     *
     * Retrieve \f$ \mu \f$: the mean/average/expected value of the distribution. \f$ \mu \f$ is the point with the highest probability
     * @returns a 3D Vector that mu will be placed into
     */
    virtual Vector3D getMu() const = 0;
        
    /** Get Sigma
     *
     * Retrieve \f$ \Sigma \f$: the covariance matrix/expected deviationof the distribution. This will be an estimation when the distribution is non-normal
     * @returns a 3x3 Matrix that Sigma will be placed into
     */
    virtual Matrix9D getSigma() const = 0;
        
    /** Get P(x).
     *
     * Retrieve P(x): the probability of X = x
     * @param x 3D Vector containing the coordinates of x
     * @return P(x) with \f$ 0 \leq P(x) \leq 1 \f$
     */
    virtual double getP(Vector3D const &x) const = 0;

    /** Get X.
     *
     * Retrieve a random value x dependant on the distribution.
     * @returns a 3D Vector that the random value will be placed in
     */
    virtual Vector3D getX() const = 0;
      
    /** Predict distribution.
     *
     * Predict/move the distribution given a specific movement model
     * @param movementModel The <B>relative</B> movement model used to update the distribution.
     */
    virtual void predict(rf<IDistribution3D> const &movementModel) = 0;
      
    /** Update distribution.
     *
     * Update the distribution given a measurement and the measurement model for that measurement
     * @param measurementModel The measurement model where mu is the measured position (position of detected object - own position relative to object and Sigma the uncertainty of the measurement.
     */
    virtual void update(rf<IDistribution3D> const &measurementModel) = 0;
  };

};

#endif // __INC_BATS_DISTRIBUTION_HH_
