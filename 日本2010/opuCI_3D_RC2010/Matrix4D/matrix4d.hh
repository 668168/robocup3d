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

/**
 *  Little Green Bats Robocup Code!
 *
 *  Look in the source tree for license information!
 *  \todo Waarom heet deze Matrix4D en niet Matrix16F?
 */

#ifndef __INC_BATS_MATRIX4D_HH_
#define __INC_BATS_MATRIX4D_HH_

//#include "vector3.hh"   // Vector stuff is not yet implemented!
#include <cassert>
#include <ostream>
#include "vector4.hh"

namespace bats {

/** \brief A Four Dimensional Matrix
 *
 * The Matrix4D class.
 */
class Matrix4D {
	float d_values[16]; // in opengl compatible column-major order.

	void destroy() {
	}

	void copy(Matrix4D const &other) {
		memcpy(reinterpret_cast<char*> (d_values),
				reinterpret_cast<char const *> (other.d_values), sizeof(float)
						* 16);
	}

	// @param values should be an array of 16 floats!
	Matrix4D(double values[]) {
		memcpy(reinterpret_cast<char*> (d_values),
				reinterpret_cast<char const *> (values), sizeof(float) * 16);
	}

public:

	Matrix4D(Matrix4D const &other) {
		copy(other);
	}

	/**
	 *  Initialize the matrix to identity.
	 */
	Matrix4D() {
		// Initialize to identity.
		for (unsigned i = 0; i < 4; ++i)
			for (unsigned j = 0; j < 4; ++j)
				d_values[i + j * 4] = i == j ? 1.0 : 0.0;
	}

	virtual ~Matrix4D() {
		destroy();
	}

	Matrix4D &operator=(Matrix4D const &other) {
		if (this != &other) {
			destroy();
			copy(other);
		}
		return *this;
	}

	/* DEPRICATED!
	 float &operator[](unsigned index)
	 {
	 assert(index < 16);
	 return d_values[index];
	 }
	 */

	/**
	 *  This makes the matrix transparantly
	 *  usable with opengl matrix methods.
	 */
	operator float *() {
		return d_values;
	}

	/*  DEPRICATED!
	 void set(unsigned index, float value)
	 {
	 assert(index < 16);
	 d_values[index] = value;
	 }
	 */

	/**
	 *  Sets a matrix cell to value.
	 *
	 *  @param i is the column.
	 *  @param j is the row.
	 *  @param value the value the cell is set to.
	 */
	void set(unsigned i, unsigned j, float value) {
		assert(i < 4 && j < 4);
		d_values[i + 4 * j] = value;
	}

	/**
	 *  @returns the values of a matrix cell.
	 *
	 *  @param i is the column.
	 *  @param j is the row.
	 */
	float get(unsigned i, unsigned j) const {
		assert(i < 4 && j < 4);
		return d_values[i + 4 * j];
	}

	float get(unsigned i) const {
		assert(i < 16);
		return d_values[i];
	}

	Matrix4D inverse() const {
		Matrix4D res;

		// Transpose Rotation part
		for (unsigned i = 0; i < 3; ++i)
			for (unsigned j = 0; j < 3; ++j)
				res.d_values[i + 4 * j] = d_values[j + 4 * i];
		res[15] = 1.0;
		res[3] = res[7] = res[11] = res[12] = res[13] = res[14] = 0.0;

		// Negate Translate part and rotate by new rotation
		Vector4F trans(-d_values[12], -d_values[13], -d_values[14], 1.0);
		trans = res * trans;

		// Put in Translate part
		res.d_values[12] = trans.getX();
		res.d_values[13] = trans.getY();
		res.d_values[14] = trans.getZ();

		return res;
	}
	/*  SHOULD BE IMPLEMENTED!
	 float determinant() const
	 {
	 return
	 d_values[0] * d_values[4] * d_values[8] +
	 d_values[1] * d_values[5] * d_values[6] +
	 d_values[2] * d_values[3] * d_values[7] -
	 d_values[2] * d_values[4] * d_values[6] -
	 d_values[1] * d_values[3] * d_values[8] -
	 d_values[0] * d_values[5] * d_values[7];
	 }
	 */

	Matrix4D inverse2() const {
		Matrix4D res;

		double a0 = d_values[0] * d_values[5] - d_values[1] * d_values[4];
		double a1 = d_values[0] * d_values[9] - d_values[1] * d_values[8];
		double a2 = d_values[0] * d_values[13] - d_values[1] * d_values[12];
		double a3 = d_values[4] * d_values[9] - d_values[5] * d_values[8];
		double a4 = d_values[4] * d_values[13] - d_values[5] * d_values[12];
		double a5 = d_values[8] * d_values[13] - d_values[9] * d_values[12];
		double b0 = d_values[2] * d_values[7] - d_values[3] * d_values[6];
		double b1 = d_values[2] * d_values[11] - d_values[3] * d_values[10];
		double b2 = d_values[2] * d_values[15] - d_values[3] * d_values[14];
		double b3 = d_values[6] * d_values[11] - d_values[7] * d_values[10];
		double b4 = d_values[6] * d_values[15] - d_values[7] * d_values[14];
		double b5 = d_values[10] * d_values[15] - d_values[11] * d_values[14];

		double det = a0 * b5 - a1 * b4 + a2 * b3 + a3 * b2 - a4 * b1 + a5 * b0;

		if (fabs(det) != 0) {
			double inv = 1 / det;

			res.d_values[0] = inv * (+d_values[5] * b5 - d_values[9] * b4
					+ d_values[13] * b3);
			res.d_values[1] = inv * (-d_values[1] * b5 + d_values[9] * b2
					- d_values[13] * b1);
			res.d_values[2] = inv * (+d_values[1] * b4 - d_values[5] * b2
					+ d_values[13] * b0);
			res.d_values[3] = inv * (-d_values[1] * b3 + d_values[5] * b1
					- d_values[9] * b0);

			res.d_values[4] = inv * (-d_values[4] * b5 + d_values[8] * b4
					- d_values[12] * b3);
			res.d_values[5] = inv * (+d_values[0] * b5 - d_values[8] * b2
					+ d_values[12] * b1);
			res.d_values[6] = inv * (-d_values[0] * b4 + d_values[4] * b2
					- d_values[12] * b0);
			res.d_values[7] = inv * (+d_values[0] * b3 - d_values[4] * b1
					+ d_values[8] * b0);

			res.d_values[8] = inv * (+d_values[7] * a5 - d_values[11] * a4
					+ d_values[15] * a3);
			res.d_values[9] = inv * (-d_values[3] * a5 + d_values[11] * a2
					- d_values[15] * a1);
			res.d_values[10] = inv * (+d_values[3] * a4 - d_values[7] * a2
					+ d_values[15] * a0);
			res.d_values[11] = inv * (-d_values[3] * a3 + d_values[7] * a1
					- d_values[11] * a0);

			res.d_values[12] = inv * (-d_values[6] * a5 + d_values[10] * a4
					- d_values[14] * a3);
			res.d_values[13] = inv * (+d_values[2] * a5 - d_values[10] * a2
					+ d_values[14] * a1);
			res.d_values[14] = inv * (-d_values[2] * a4 + d_values[6] * a2
					- d_values[14] * a0);
			res.d_values[15] = inv * (+d_values[2] * a3 - d_values[6] * a1
					+ d_values[10] * a0);

			return res;
		}

		return Matrix4D();
	}

	/**
	 *  Summate matrix a and matrix b together and put the
	 *  answer in matrix res.
	 */
	static void sum(Matrix4D &res, Matrix4D const &a, Matrix4D const &b) {
		for (unsigned i = 0; i < 16; ++i)
			res.d_values[i] = a.d_values[i] + b.d_values[i];
	}

	/**
	 *  Substract matrix a drom matrix b and put the
	 *  answer in matrix res.
	 */
	static void sub(Matrix4D &res, Matrix4D const &a, Matrix4D const &b) {
		for (unsigned i = 0; i < 16; ++i)
			res.d_values[i] = a.d_values[i] - b.d_values[i];
	}

	Vector4F operator*(Vector4F vec) {
		Vector4F res;
		mul(res, *this, vec);
		return res;
	}

	/** Multiply matrix A with vector b
	 *
	 * \f$ \vec c = A \vec b \f$ <BR>
	 * \f$ c_i = \sum_{j = 0}^2 a_{i,j} \cdot b_j \f$
	 */
	static void mul(Vector4F &res, Matrix4D const &a, Vector4F const &b) {
		res.setX(a.d_values[0 + 0 * 4] * b.d_values[0] + a.d_values[0 + 1 * 4]
				* b.d_values[1] + a.d_values[0 + 2 * 4] * b.d_values[2]
				+ a.d_values[0 + 3 * 4] * b.d_values[3]);

		res.setY(a.d_values[1 + 0 * 4] * b.d_values[0] + a.d_values[1 + 1 * 4]
				* b.d_values[1] + a.d_values[1 + 2 * 4] * b.d_values[2]
				+ a.d_values[1 + 3 * 4] * b.d_values[3]);

		res.setZ(a.d_values[2 + 0 * 4] * b.d_values[0] + a.d_values[2 + 1 * 4]
				* b.d_values[1] + a.d_values[2 + 2 * 4] * b.d_values[2]
				+ a.d_values[2 + 3 * 4] * b.d_values[3]);

		res.setW(a.d_values[3 + 0 * 4] * b.d_values[0] + a.d_values[3 + 1 * 4]
				* b.d_values[1] + a.d_values[3 + 2 * 4] * b.d_values[2]
				+ a.d_values[3 + 3 * 4] * b.d_values[3]);
	}

	/** Multiply transposed vector b to matrix A
	 *
	 * \f$ \vec c = \vec b^float A \f$
	 * \f$ c_i = \sum_{j = 0}^2 b_j cdot a_{j, i} \f$
	 */
	/*  SHOULD BE IMPLEMENTED!
	 static void mulTVect(Vector3<T> &c, Vector3<T> const &b, Matrix4D const &a)
	 {
	 c.d_values[0*1 + 0] =
	 a.d_values[0*3 + 0] * b.d_values[0] +
	 a.d_values[1*3 + 0] * b.d_values[1] +
	 a.d_values[2*3 + 0] * b.d_values[2];

	 c.d_values[1*1 + 0] =
	 a.d_values[0*3 + 1] * b.d_values[0] +
	 a.d_values[1*3 + 1] * b.d_values[1] +
	 a.d_values[2*3 + 1] * b.d_values[2];

	 c.d_values[2*1 + 0] =
	 a.d_values[0*3 + 2] * b.d_values[0] +
	 a.d_values[1*3 + 2] * b.d_values[1] +
	 a.d_values[2*3 + 2] * b.d_values[2];
	 }
	 */

	Matrix4D operator*(Matrix4D const& mat) const {
		Matrix4D res;
		mul(res, *this, mat);
		return res;
	}

	/** Matrix multiplication
	 *
	 * Multiply matrix \a A with matrix \a B.<BR>
	 * \f$ C = A \cdot B \f$<BR>
	 * \f$ c_{i,j} = \sum_{k = 1}^3 a_{k, j} \cdot b_{i, k} \f$
	 */
	static void mul(Matrix4D &res, Matrix4D const &a, Matrix4D const &b) {
		for (unsigned i = 0; i < 4; i++)
			for (unsigned j = 0; j < 4; j++) {
				unsigned idx = i + j * 4;
				res.d_values[idx] = 0;
				for (unsigned k = 0; k < 4; k++)
					res.d_values[idx] += a.d_values[k + j * 4] * b.d_values[i
							+ k * 4];
			}
	}

	/**  Matrix Transposition,
	 *
	 *  Transposes matrix mat and puts the result in matrix res.
	 */
	static void transpose(Matrix4D &res, Matrix4D const &mat) {
		for (unsigned i = 0; i < 4; ++i)
			for (unsigned j = 0; j < 4; ++j)
				res.d_values[i * 4 + j] = mat.d_values[j * 4 + i];
	}

	/*  DEPRICATED?
	 static void div(Matrix4D &res, Matrix4D const &a, Matrix4D const &b)
	 {
	 for (unsigned i = 0; i < 9; ++i)
	 res[i] = a[i] / b[i];
	 }
	 */

	/**
	 *  @returns the transposed matrix.
	 */
	Matrix4D transposed() const {
		Matrix4D res;
		transpose(res, *this);
		return res;
	}

	/** Matrix Multiplication
	 *
	 *  Multiplies the matrix with other and returns the answer.
	 */
	Matrix4D operator*(Matrix4D const &other) {
		Matrix4D res;
		mul(res, *this, other);
		return res;
	}

	/*  SHOULD BE IMPLEMENTED! */

	Vector3F operator*(Vector3F const &other) {
		Vector4F res;
		Vector4F oth(other.getX(), other.getY(), other.getZ(), 1);
		mul(res, *this, oth);
		Vector3F reslt(res.getX(), res.getY(), res.getZ());
		return reslt;
	}

	/** Multiply matrix by scalar \a v */
	Matrix4D operator*(float v) {
		Matrix4D res;
		for (unsigned i = 0; i < 16; i++)
			res[i] = d_values[i] * v;
		return res;
	}

	/** Divide matrix by scalar \a v */
	Matrix4D operator/(float v) {
		return *this * (1.0 / v);
	}

	/** Add this matrix to another matrix
	 *
	 * \f$ C = A + B \\ c_{ij} = a_{ij} + b_{ij} \f$
	 */
	Matrix4D operator+(Matrix4D const &other) {
		Matrix4D res;
		sum(res, *this, other);
		return res;
	}

	/** Subtract another matrix from this matrix
	 *
	 * \f$ C = A - B \\ c_{ij} = a_{ij} - b_{ij} \f$
	 */
	Matrix4D operator-(Matrix4D const &other) {
		Matrix4D res;
		sub(res, *this, other);
		return res;
	}

	static Matrix4D translation(Vector3D t) {
		Matrix4D mat;
		mat.set(3, 0, t[0]);
		mat.set(3, 1, t[1]);
		mat.set(3, 2, t[2]);

		return mat;
	}

	//calculation can be optimized
	static Matrix4D rotation(Vector3D r) {

		/*double A = cos(r[0]);
		 double B = sin(r[0]);
		 double c = cos(r[1]);
		 double D = sin(r[1]);
		 double E = cos(r[2]);
		 double F = sin(r[2]);

		 double AD = A * D;
		 double BD = B * D;

		 Matrix4D rot;

		 rot.set(0,0, C * E);
		 rot.set(0,1,-C * F);
		 rot.set(0,2,D);
		 rot.set(1,0,BD * E + A * F);
		 rot.set(1,1,-BD * F + A * E);
		 rot.set(1,2,-B * C);
		 rot.set(2,0,-AD * E + B * F);
		 rot.set(2,1,AD * F + B * E);
		 rot.set(2,2,A * C);

		 return rot;*/

		Matrix4D x;
		x.set(1, 1, cos(r[0]));
		x.set(1, 2, sin(r[0]));
		x.set(2, 1, -sin(r[0]));
		x.set(2, 2, cos(r[0]));

		Matrix4D y;
		y.set(0, 0, cos(r[1]));
		y.set(0, 2, -sin(r[1]));
		y.set(2, 0, sin(r[1]));
		y.set(2, 2, cos(r[1]));

		Matrix4D z;
		z.set(0, 0, cos(r[2]));
		z.set(0, 1, sin(r[2]));
		z.set(1, 0, -sin(r[2]));
		z.set(1, 1, cos(r[2]));

		return x * y * z;
	}
};

std::ostream& operator<<(std::ostream &out, bats::Matrix4D const & mat);

}
;

#endif // __INC_BATS_MATRIX4D_HH_
