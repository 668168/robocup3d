/*
 *  Little Green BATS (2008), AI department, University of Groningen
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
 *  Date: 	November 1, 2008
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

#ifndef __INC_BATS_MATRIX4D_HH_
#define __INC_BATS_MATRIX4D_HH_

//#include "vector3.hh"   // Vector stuff is not yet implemented!
#include <cassert>
#include <ostream>
#include "../Vector4/vector4.hh"
#include "../Vector3/vector3.hh"

namespace bats {

  /** \brief A Four Dimensional Matrix
   *
   * The Matrix4D class.
   *  | 0 4  8 12 |
   *  | 1 5  9 13 |
   *  | 2 6 10 14 |
   *  | 3 7 11 15 |
   
   *  | (0, 0)  (0, 1)  (0, 2) (0, 3) |
   *  | (1, 0)  (1, 1)  (1, 2) (1, 3) |
   *  | (2, 0)  (2, 1)  (2, 2) (2, 3) |
   *  | (3, 0)  (3, 1)  (3, 2) (3, 3) |
   */
  class Matrix4D
  {
    float d_values[16]; // in opengl compatible column-major order.

    void destroy()
    {
    }

    void copy(Matrix4D const &other)
    {
      memcpy(reinterpret_cast<char*>(d_values),
             reinterpret_cast<char const *>(other.d_values),
             sizeof(float)*16);
    }

    // @param values should be an array of 16 floats!
    Matrix4D(double values[])
    {
      memcpy(reinterpret_cast<char*>(d_values),
             reinterpret_cast<char const *>(values),
             sizeof(float)*16);
    }
    
  public:

    Matrix4D(Matrix4D const &other) { copy(other); }

    /**
     *  Initialize the matrix to identity.
     */
    Matrix4D()
    {
      // Initialize to identity.
      for (unsigned i = 0; i < 4; ++i)
        for (unsigned j = 0; j < 4; ++j)
          d_values[i + j * 4] = i == j ? 1.0 : 0.0;
    }

    /**
     *  Initialize the matrix with base vectors
     */
    Matrix4D(Vector3D const& right, Vector3D const& forward, Vector3D const& up, Vector3D const& trans = Vector3D(0,0,0))
    {
      set(0,0,right[0]);
      set(1,0,right[1]);
      set(2,0,right[2]);
      set(3,0,0);
      
      set(0,1,forward[0]);
      set(1,1,forward[1]);
      set(2,1,forward[2]);
      set(3,1,0);

      set(0,2,up[0]);
      set(1,2,up[1]);
      set(2,2,up[2]);
      set(3,2,0);
      
      set(0,3,trans[0]);
      set(1,3,trans[1]);
      set(2,3,trans[2]);
      set(3,3,1);
      
    }
    
    virtual ~Matrix4D() { destroy(); }
      
    Matrix4D &operator=(Matrix4D const &other)
    {
      if (this != &other) {
        destroy();
        copy(other);
      }
      return *this;
    }

    /**
     *  This makes the matrix transparantly
     *  usable with opengl matrix methods.
     */
    operator float *()
    {
      return d_values;
    }

    /**
     *  Sets a matrix cell to a given value.
     *
     *  @param i Row number (0-3)
     *  @param j Column number (0-3)
     *  @param value Value the cell is set to
     */
    void set(unsigned i, unsigned j, float value)
    {
      assert(i < 4 && j < 4);
      d_values[i + 4 * j] = value;
    }

    /**
     *  @returns the value of a matrix cell.
     *  
     *  @param i Row number (0-3)
     *  @param j Column number (0-3)
     */
    float get(unsigned i, unsigned j) const
    {
      assert(i < 4 && j < 4);
      return d_values[i + 4 * j];
    }
    
    /**
     *  @returns the value of a matrix cell.
     *  
     *  @param i Cell index (0-15)
     */
    float get(unsigned i) const
    {
      assert(i < 16);
      return d_values[i];
    }
    
    /**
     * @returns the first column, which represents a coordinate system's right direction
     */
    Vector3D right() const
    {
      return Vector3D(get(0,0),get(1,0),get(2,0));
    }
    
    /**
     * @returns the second column, which represents a coordinate system's front direction
     */
    Vector3D front() const
    {
      return Vector3D(get(0,1),get(1,1),get(2,1));
    }
    
    /**
     * @returns the third column, which represents a coordinate system's up direction
     */
    Vector3D up() const
    {
      return Vector3D(get(0,2),get(1,2),get(2,2));
    }
    
    /**
     * @returns the fourth column, which represents a coordinate system's translation
     */
    Vector3D trans() const
    {
      return Vector3D(get(0,3),get(1,3),get(2,3));
    }
    
    /**
     * @returns the inverse of this matrix
     */
    Matrix4D inverse() const
    {
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

    /**
     *  Summate matrix a and matrix b together and put the
     *  answer in matrix res.
     */
    static void sum(Matrix4D &res, Matrix4D const &a, Matrix4D const &b)
    {
      for (unsigned i = 0; i < 16; ++i)
        res.d_values[i] = a.d_values[i] + b.d_values[i];
    }

    /**
     *  Substract matrix a drom matrix b and put the
     *  answer in matrix res.
     */
    static void sub(Matrix4D &res, Matrix4D const &a, Matrix4D const &b)
    {
      for (unsigned i = 0; i < 16; ++i)
        res.d_values[i] = a.d_values[i] - b.d_values[i];
    }

    /**
     * Multiply this matrix with a 4-dimensional vector
     */
    Vector4F operator*(Vector4F const& vec) const
    {
      Vector4F res;
      mul(res, *this, vec);
      return res;
    }
    
    /** Multiply matrix A with vector b
     *
     * \f$ \vec c = A \vec b \f$ <BR>
     * \f$ c_i = \sum_{j = 0}^2 a_{i,j} \cdot b_j \f$
     */
    static void mul(Vector4F &res, Matrix4D const &a, Vector4F const &b)
    {
      res.setX(a.d_values[0] * b.d_values[0] +
               a.d_values[4] * b.d_values[1] +
               a.d_values[8] * b.d_values[2] +
               a.d_values[12] * b.d_values[3]);

      res.setY(a.d_values[1] * b.d_values[0] +
               a.d_values[5] * b.d_values[1] +
               a.d_values[9] * b.d_values[2] +
               a.d_values[13] * b.d_values[3]);

      res.setZ(a.d_values[2] * b.d_values[0] +
               a.d_values[6] * b.d_values[1] +
               a.d_values[10] * b.d_values[2] +
               a.d_values[14] * b.d_values[3]);

      res.setW(a.d_values[3] * b.d_values[0] +
               a.d_values[7] * b.d_values[1] +
               a.d_values[11] * b.d_values[2] +
               a.d_values[15] * b.d_values[3]);
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


    
    /** Matrix Multiplication
     *
     *  Multiplies the matrix with other and returns the answer.
     */
    Matrix4D operator*(Matrix4D const& mat) const
    {
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
    static void mul(Matrix4D &res, Matrix4D const &a, Matrix4D const &b)
    {
      for (unsigned i = 0; i < 4; i++)
        for (unsigned j = 0; j < 4; j++)
        {
          unsigned idx = i + j * 4;
          res.d_values[idx] = 0;
          for (unsigned k = 0; k < 4; k++)
            res.d_values[idx] += a.d_values[i + k * 4] * b.d_values[k + j * 4];
        }
    }
    
    /**  Matrix Transposition,
     *
     *  Transposes matrix mat and puts the result in matrix res.
     */
    static void transpose(Matrix4D &res, Matrix4D const &mat)
    {
      for (unsigned i = 0; i < 4; ++i)
        for (unsigned j = 0; j < 4; ++j)
          res.d_values[i + 4 * j] = mat.d_values[j + 4 * i];
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
    Matrix4D transposed() const
    {
      Matrix4D res;
      transpose(res,*this);
      return res;
    }

    /*  SHOULD BE IMPLEMENTED!
      Vector3<T> operator*(Vector3<T> const &other)
      {
      Vector3<T> res;
      mul(res,*this,other);
      return res;
      }
    */

    /** Multiply matrix by scalar \a v */
    Matrix4D operator*(float v) const
    {
      Matrix4D res;
      for (unsigned i = 0; i < 16; i++)
        res[i] = d_values[i] * v;
      return res;
    }

    /** Divide matrix by scalar \a v */
    Matrix4D operator/(float v) const
    {
      return *this * (1.0 / v);
    }

    /** Add this matrix to another matrix
     *
     * \f$ C = A + B \\ c_{ij} = a_{ij} + b_{ij} \f$
     */
    Matrix4D operator+(Matrix4D const &other) const
    {
      Matrix4D res;
      sum(res,*this,other);
      return res;
    }
    
    /** Subtract another matrix from this matrix
     *
     * \f$ C = A - B \\ c_{ij} = a_{ij} - b_{ij} \f$
     */
    Matrix4D operator-(Matrix4D const &other) const
    {
      Matrix4D res;
      sub(res,*this,other);
      return res;
    }
    
    /**
     * @returns a translation matrix for translation \a t
     */
    static Matrix4D translation(Vector3D const& t)
    {
      Matrix4D mat;
      mat.set(0, 3, t[0]);
      mat.set(1, 3, t[1]);
      mat.set(2, 3, t[2]);
      
      return mat;
    }
    
    /**
     * @param r Rotation around the x, y and z-axis in radians     
     * @returns a rotation matrix for rotation around the x, y and z-axis of angles given by \a r
     */
    static Matrix4D rotation(Vector3D const& r)
    {
      Matrix4D x;
      x.set(1, 1, cos(r[0]));
      x.set(1, 2, -sin(r[0]));
      x.set(2, 1, sin(r[0]));
      x.set(2, 2, cos(r[0]));

      Matrix4D y;
      y.set(0, 0, cos(r[1]));
      y.set(0, 2, sin(r[1]));
      y.set(2, 0, -sin(r[1]));
      y.set(2, 2, cos(r[1]));

      Matrix4D z;
      z.set(0, 0, cos(r[2]));
      z.set(0, 1, -sin(r[2]));
      z.set(1, 0, sin(r[2]));
      z.set(1, 1, cos(r[2]));
      
      return x * y * z;
    }
    
    /**
     * @param axis Axis of rotation
     * @param r Angle of rotation in radians
     * @returns a rotation matrix for rotation of around \a axis
     */
    static Matrix4D rotation(Vector3D const& axis, double r)
    {
      double c = cos(r);
      double s = sin(r);
      double t = 1 - c;
      Matrix4D m;
      
      m.set(0, 0, t * axis[0] * axis[0] + c);
      m.set(0, 1, t * axis[0] * axis[1] - s * axis[2]);
      m.set(0, 2, t * axis[0] * axis[2] + s * axis[1]);
      
      m.set(1, 0, t * axis[0] * axis[2] + s * axis[2]);
      m.set(1, 1, t * axis[1] * axis[1] + c);
      m.set(1, 2, t * axis[1] * axis[2] - s * axis[0]);
      
      m.set(2, 0, t * axis[0] * axis[2] - s * axis[1]);
      m.set(2, 1, t * axis[1] * axis[2] + s * axis[0]);
      m.set(2, 2, t * axis[2] * axis[2] + c);
      
      return m;
    }
  };

  /**
   * Insertion operator for writing a matrix to a stream
   */
  std::ostream& operator<<(std::ostream &out, bats::Matrix4D const & mat);

};



#endif // __INC_BATS_MATRIX4D_HH_
