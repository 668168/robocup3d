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















#ifndef __INC_BATS_MATRIX9_HH_
#define __INC_BATS_MATRIX9_HH_

#include "vector3.hh"
#include <cstring>

namespace bats {

  /** \brief A Three Dimensional Matrix
   *
   *  This is a Matrix template class of size 3x3 in column major order:
   *  | 0 3 6 |
   *  | 1 4 7 |
   *  | 2 5 8 |
   *
   *  | (0, 0)  (0, 1)  (0, 2) |
   *  | (1, 0)  (1, 1)  (1, 2) |
   *  | (2, 0)  (2, 1)  (2, 2) |
   */
  template <class T>
  class Matrix9
  {
    T d_values[9];

    void destroy() {}

    void copy(Matrix9<T> const &other)
    {
      memcpy(reinterpret_cast<char*>(d_values),
             reinterpret_cast<char const *>(other.d_values),
             sizeof(T)*9);
    }

    Matrix9(double values[])
    {
      memcpy(reinterpret_cast<char*>(d_values),
             reinterpret_cast<char const *>(values),
             sizeof(T)*9);
    }
    
  public:

    Matrix9(Matrix9<T> const &other) { copy(other); }

    /**
     *  Initializes the matrix to zero's.
     *
     *  \todo initialize to identity?
     */
    Matrix9()
    {
      for (unsigned i = 0; i < 9; ++i)
        d_values[i] = 0.0;
    }

    ~Matrix9() { destroy(); }
      
    Matrix9 &operator=(Matrix9<T> const &other)
    {
      if (this != &other) {
        destroy();
        copy(other);
      }
      return *this;
    }

    /**
     *  @returns the values of cell number index in a
     *  column-major order. Thus cell (i,j) is index
     *  j+3*i where i is the column and j is the row.
     */
    T &operator[](unsigned index)
    {
      assert(index < 9);
      return d_values[index];
    }

    /**
     *  Set the value of cell index to value.
     *  @see operator[]
     */
    void set(unsigned index, T value)
    {
      assert(index < 9);
      d_values[index] = value;
    }

    /**
     *  Sets the value of cell with row i and column j
     *  to value.
     */
    void set(unsigned i, unsigned j, T value)
    {
      assert(i < 3 && j < 3);
      set(i + 3 * j, value);
    }
    
    void set(unsigned j, Vector3<T> vec)
    {
      assert(j < 3);
      d_values[j * 3 + 0] = vec[0];
      d_values[j * 3 + 1] = vec[1];
      d_values[j * 3 + 2] = vec[2];
    }
    
    /**
     *  @returns the value of cell with row i and column j.
     */
    T get(unsigned i, unsigned j) const
    {
      assert(i < 3 && j < 3);
      return get(i + 3 * j);
    }

    /**
     *  @returns the value at cell index.
     *  @see operator[]
     */
    T get(unsigned index) const
    {
      assert(index < 9);
      return d_values[index];
    }

    /**
     * Calculates the minor of elemeny (i, j), ie the determinant of the matrix without row i and column j
     */
    double minorDet(unsigned i, unsigned j)
    {
      // remaining rows
      unsigned i1 = i == 0 ? 1 : 0;
      unsigned i2 = i == 1 ? 2 : 1;

      // remaining columns
      unsigned j1 = j == 0 ? 1 : 0;
      unsigned j2 = j == 1 ? 2 : 1;
      
      return get(i1, j1) * get(i2, j2) - get(i1, j2) * get(i2, j1);
    }

    /**
     *  @returns the determinant of the matrix.
     */
    T determinant() const
    {
      return
        get(0, 0) * minorDet(0, 0) -
        get(1, 0) * minorDet(1, 0) +
        get(2, 0) * minorDet(2, 0);
    }

    /**
     *  Calculates the inverse of matrix mat with determinant det and
     *  puts it in res.
     */
    static void inverse(Matrix9<T> &res, Matrix9<T> &mat)
    {
      res.d_values[0] = mat.minorDet(0, 0);
      res.d_values[1] = mat.minorDet(1, 0);
      res.d_values[2] = mat.minorDet(2, 0);
  
      res.d_values[3] = mat.minorDet(0, 1);
      res.d_values[4] = mat.minorDet(1, 1);
      res.d_values[5] = mat.minorDet(2, 1);
  
      res.d_values[6] = mat.minorDet(0, 2);
      res.d_values[7] = mat.minorDet(1, 2);
      res.d_values[8] = mat.minorDet(2, 2);

      double det =
        mat.get(0, 0) * res.d_values[0] -
        mat.get(1, 0) * res.d_values[1] +
        mat.get(2, 0) * res.d_values[2];
        
      res = res / det;
    }

    /**
     *  @returns the inverse of the matrix.
     */
    Matrix9<T> inverse()
    {
      Matrix9<T> res;
      inverse(res, *this);
      return res;
    }

    /**
     *  Adds matrix a to matrix b and puts the result in res.
     */
    static void add(Matrix9<T> &res, Matrix9<T> const &a, Matrix9<T> const &b)
    {
      for (unsigned i = 0; i < 9; ++i)
        res[i] = a[i] + b[i];
    }

    /**
     *  Substracs matrix b from matrix a and puts the result in res.
     */
    static void sub(Matrix9<T> &res, Matrix9<T> const &a, Matrix9<T> const &b)
    {
      for (unsigned i = 0; i < 9; ++i)
        res[i] = a[i] - b[i];
    }

    /** Multiply matrix A with vector b
     *
     * \f$ \vec c = A \vec b \f$ <BR>
     * \f$ c_i = \sum_{j = 0}^2 a_{i,j} \cdot b_j \f$
     */
    static void mul(Vector3<T> &res, Matrix9<T> const &a, Vector3<T> const &b)
    {
      res[0] = 
        a.d_values[0] * b.d_values[0] +
        a.d_values[3] * b.d_values[1] +
        a.d_values[6] * b.d_values[2];

      res[0] = 
        a.d_values[1] * b.d_values[0] +
        a.d_values[4] * b.d_values[1] +
        a.d_values[7] * b.d_values[2];

      res[0] = 
        a.d_values[2] * b.d_values[0] +
        a.d_values[5] * b.d_values[1] +
        a.d_values[7] * b.d_values[2];
    }

    /** Multiply transposed vector b to matrix A
     *
     * \f$ \vec c = \vec b^T A \f$
     * \f$ c_i = \sum_{j = 0}^2 b_j cdot a_{j, i} \f$
     */
    static void mulTVect(Vector3<T> &c, Vector3<T> const &b, Matrix9<T> const &a)
    {
      c[0] = 
        b.d_values[0] * a.d_values[0] +
        b.d_values[1] * a.d_values[1] +
        b.d_values[2] * a.d_values[2];
        
      c[1] = 
        b.d_values[0] * a.d_values[3] +
        b.d_values[1] * a.d_values[4] +
        b.d_values[2] * a.d_values[5];
        
      c[2] = 
        b.d_values[0] * a.d_values[6] +
        b.d_values[1] * a.d_values[7] +
        b.d_values[2] * a.d_values[8];
    }


    /** Matrix multiplication
     *
     * Multiply matrix \a A with matrix \a B.<BR>
     * \f$ C = A \cdot B \f$<BR>
     * \f$ c_{i,j} = \sum_{k = 1}^3 a_{k, j} \cdot b_{i, k} \f$
     */
    static void mul(Matrix9<T> &res, Matrix9<T> const &a, Matrix9<T> const &b)
    {
      for (unsigned i = 0; i < 3; i++)
        for (unsigned j = 0; j < 3; j++)
        {
          unsigned idx = i + j * 3;
          res.d_values[idx] = 0;
          for (unsigned k = 0; k < 3; k++)
            res.d_values[idx] += a.get(i, k) * b.get(k, j);
        }
    }

    /**
     *  Calculates the transposed of matrix mat and puts the result in res.
     */    
    static void transpose(Matrix9<T> &res, Matrix9<T> const &mat)
    {
      for (unsigned i = 0; i < 3; ++i)
        for (unsigned j = 0; j < 3; ++j)
          res.d_values[i*3+j] = mat.d_values[j*3+i];
    }

    /*
    static void div(Matrix9<T> &res, Matrix9<T> const &a, Matrix9<T> const &b)
    {
      for (unsigned i = 0; i < 9; ++i)
        res[i] = a[i] / b[i];
    }
    */

    /**
     *  @returns the transposed of the matrix.
     */
    Matrix9<T> transposed() const
    {
      Matrix9<T> res;
      transpose(res,*this);
      return res;
    }

    /**
     *  @returns the multiplication of this matrix to other.
     */
    Matrix9<T> operator*(Matrix9<T> const &other)
    {
      Matrix9<T> res;
      mul(res,*this,other);
      return res;
    }

    /**
     *  @returns the multiplication of this matrix to vector other.
     */
    Vector3<T> operator*(Vector3<T> const &other)
    {
      Vector3<T> res;
      mul(res,*this,other);
      return res;
    }

    /** Multiply matrix by scalar \a v */
    Matrix9<T> operator*(T v)
    {
      Matrix9<T> res;
      for (unsigned i = 0; i < 9; i++)
        res[i] = d_values[i] * v;
      return res;
    }

    /** Devide matrix by scalar \a v */
    Matrix9<T> operator/(T v)
    {
      return *this * (1.0 / v);
    }

    /** Add this matrix to another matrix
     *
     * \f$ C = A + B \\ c_{ij} = a_{ij} + b_{ij} \f$
     */
    Matrix9<T> operator+(Matrix9<T> const &other)
    {
      Matrix9<T> res;
      for (unsigned i = 0; i < 9; i++)
        res[i] = d_values[i] + other.d_values[i];
      return res;
    }
    
    /** Subtract another matrix from this matrix
     *
     * \f$ C = A - B \\ c_{ij} = a_{ij} - b_{ij} \f$
     */
    Matrix9<T> operator-(Matrix9<T> const &other)
    {
      Matrix9<T> res;
      for (unsigned i = 0; i < 9; i++)
        res[i] = d_values[i] - other.d_values[i];
      return res;
    }
    
  };

  /**
   *  The matrix class with doubles as values.
   *
   *  \todo make it a float, will that make it faster or just make it stupid?
   */
  typedef Matrix9<float> Matrix9D;

};

#endif // __INC_BATS_MATRIX9_HH_
