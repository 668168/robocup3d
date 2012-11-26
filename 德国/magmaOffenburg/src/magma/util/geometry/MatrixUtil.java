/* Copyright 2009 Hochschule Offenburg
 * Klaus Dorer, Mathias Ehret, Stefan Glaser, Thomas Huber,
 * Simon Raffeiner, Srinivasa Ragavan, Thomas Rinklin,
 * Joachim Schilling, Ingo Schindler, Rajit Shahi
 *
 * This file is part of magmaOffenburg.
 *
 * magmaOffenburg is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * magmaOffenburg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with magmaOffenburg. If not, see <http://www.gnu.org/licenses/>.
 */
package magma.util.geometry;

import javax.vecmath.Matrix3d;

/**
 * @author Stefan Glaser
 * 
 */
public class MatrixUtil
{

	public static int[][] mul(int[][] A, int[][] B)
	{

		if (A[0].length != B.length) {
			throw new IllegalArgumentException(
					"Zeilenanzahl von B muss der Spaltenanzahl von A entsprechen");
		}

		int[][] C = new int[A.length][B[0].length];

		for (int i = 0; i < A.length; i++) {
			for (int j = 0; j < B[0].length; j++) {
				for (int k = 0; k < A[0].length; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}

		return C;
	}

	public static void printMatrix(int[][] m)
	{
		for (int i = 0; i < m.length; i++) {
			for (int j = 0; j < m[i].length; j++) {
				System.out.print(m[i][j] + " ");
			}
			System.out.println();
		}
	}

	// is symmetric
	public static boolean isSymmetric(double[][] A)
	{
		int N = A.length;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < i; j++) {
				if (A[i][j] != A[j][i])
					return false;
			}
		}
		return true;
	}

	// is symmetric
	public static boolean isSymmetric(Matrix3d matrix)
	{
		if (matrix.m01 == matrix.m10 && matrix.m02 == matrix.m20
				&& matrix.m12 == matrix.m21) {
			return true;
		}

		return false;
	}

	// is symmetric
	public static boolean isSquare(double[][] A)
	{
		int N = A.length;
		for (int i = 0; i < N; i++) {
			if (A[i].length != N)
				return false;
		}
		return true;
	}

	/**
	 * @description Cholesky factor L of psd matrix A = L L^T. Please Google
	 *              Cholesky for more help!
	 * @param double[][]
	 * @return double[][]
	 */
	public static double[][] cholesky(double[][] A)
	{
		if (!isSquare(A)) {
			throw new RuntimeException("Matrix is not square");
		}
		if (!isSymmetric(A)) {
			throw new RuntimeException("Matrix is not symmetric");
		}

		int N = A.length;
		double[][] L = new double[N][N];

		for (int i = 0; i < N; i++) {
			for (int j = 0; j <= i; j++) {
				double sum = 0.0;
				for (int k = 0; k < j; k++) {
					sum += L[i][k] * L[j][k];
				}
				if (i == j)
					L[i][i] = Math.sqrt(A[i][i] - sum);
				else
					L[i][j] = 1.0 / L[j][j] * (A[i][j] - sum);
			}
			if (L[i][i] <= 0) {
				throw new RuntimeException("Matrix not positive definite");
			}
		}
		return L;
	}

	/**
	 * @param matrix
	 * @return Matrix3d - Cholesky decomposed matrix
	 */
	public static Matrix3d cholesky(Matrix3d matrix)
	{
		if (!isSymmetric(matrix)) {
			throw new RuntimeException("Matrix is not symmetric");
		}

		Matrix3d res = new Matrix3d();
		double temp;

		res.m00 = Math.sqrt(matrix.m00);
		res.m01 = matrix.m01 / res.m00;
		res.m02 = matrix.m02 / res.m00;

		temp = matrix.m11 - res.m01 * res.m01;
		if (temp <= 0) {
			throw new RuntimeException("Matrix not positive definite");
		}
		res.m11 = Math.sqrt(temp);
		res.m12 = (matrix.m12 - res.m01 * res.m02) / res.m11;

		temp = matrix.m22 - res.m02 * res.m02 - res.m12 * res.m12;
		if (temp <= 0) {
			throw new RuntimeException("Matrix not positive definite");
		}
		res.m22 = Math.sqrt(temp);

		return res;
	}
}
