/* FILE NAME   : mth_matr.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Math module.
 *               3D math matrix implementation module.
 */

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mth_def.h"

 /* Pi math constant */
#define PI 3.14159265358979323846

/* Degrees to radians conversion */
#define D2R(A) ((A) * (PI / 180.0))
#define Degree2Radian(a) D2R(a)

/* Radians to degrees conversion */
#define R2D(A) ((A) * (180.0 / PI))
#define Radian2Degree(a) R2D(a)

/* Math namespace */
namespace mth
{
  /* Matrix representation type */
  template<typename Type>
  class matr
  {
    template<typename Type1>
    friend class camera;
  public:
    Type A[4][4]; // Matrix elements

  public:
    /* Matrix default constructor */
    matr(void)
    {
    }
    /* Matrix constructor by 16 elements */
    matr(Type A00, Type A01, Type A02, Type A03,
      Type A10, Type A11, Type A12, Type A13,
      Type A20, Type A21, Type A22, Type A23,
      Type A30, Type A31, Type A32, Type A33)
    {
      A[0][0] = A00;
      A[0][1] = A01;
      A[0][2] = A02;
      A[0][3] = A03;
      A[1][0] = A10;
      A[1][1] = A11;
      A[1][2] = A12;
      A[1][3] = A13;
      A[2][0] = A20;
      A[2][1] = A21;
      A[2][2] = A22;
      A[2][3] = A23;
      A[3][0] = A30;
      A[3][1] = A31;
      A[3][2] = A32;
      A[3][3] = A33;
    } /* End of 'matr' constructor */

    /* Matrix constructor by array */
    matr(Type a[4][4])
    {
      A[0][0] = a[0][0];
      A[0][1] = a[0][1];
      A[0][2] = a[0][2];
      A[0][3] = a[0][3];
      A[1][0] = a[1][0];
      A[1][1] = a[1][1];
      A[1][2] = a[1][2];
      A[1][3] = a[1][3];
      A[2][0] = a[2][0];
      A[2][1] = a[2][1];
      A[2][2] = a[2][2];
      A[2][3] = a[2][3];
      A[3][0] = a[3][0];
      A[3][1] = a[3][1];
      A[3][2] = a[3][2];
      A[3][3] = a[3][3];
    } /* End of 'matr' constructor */

    /* Multiply two matrixes function.
     * ARGUMENTS:
     *   - reference to second matrix:
     *       matr &A;
     * RETURNS:
     *   (matr) result new matrix.
     */
    matr operator*(const matr& M) const
    {
      return matr(
        A[0][0] * M.A[0][0] + A[0][1] * M.A[1][0] + A[0][2] * M.A[2][0] + A[0][3] * M.A[3][0],
        A[0][0] * M.A[0][1] + A[0][1] * M.A[1][1] + A[0][2] * M.A[2][1] + A[0][3] * M.A[3][1],
        A[0][0] * M.A[0][2] + A[0][1] * M.A[1][2] + A[0][2] * M.A[2][2] + A[0][3] * M.A[3][2],
        A[0][0] * M.A[0][3] + A[0][1] * M.A[1][3] + A[0][2] * M.A[2][3] + A[0][3] * M.A[3][3],

        A[1][0] * M.A[0][0] + A[1][1] * M.A[1][0] + A[1][2] * M.A[2][0] + A[1][3] * M.A[3][0],
        A[1][0] * M.A[0][1] + A[1][1] * M.A[1][1] + A[1][2] * M.A[2][1] + A[1][3] * M.A[3][1],
        A[1][0] * M.A[0][2] + A[1][1] * M.A[1][2] + A[1][2] * M.A[2][2] + A[1][3] * M.A[3][2],
        A[1][0] * M.A[0][3] + A[1][1] * M.A[1][3] + A[1][2] * M.A[2][3] + A[1][3] * M.A[3][3],

        A[2][0] * M.A[0][0] + A[2][1] * M.A[1][0] + A[2][2] * M.A[2][0] + A[2][3] * M.A[3][0],
        A[2][0] * M.A[0][1] + A[2][1] * M.A[1][1] + A[2][2] * M.A[2][1] + A[2][3] * M.A[3][1],
        A[2][0] * M.A[0][2] + A[2][1] * M.A[1][2] + A[2][2] * M.A[2][2] + A[2][3] * M.A[3][2],
        A[2][0] * M.A[0][3] + A[2][1] * M.A[1][3] + A[2][2] * M.A[2][3] + A[2][3] * M.A[3][3],

        A[3][0] * M.A[0][0] + A[3][1] * M.A[1][0] + A[3][2] * M.A[2][0] + A[3][3] * M.A[3][0],
        A[3][0] * M.A[0][1] + A[3][1] * M.A[1][1] + A[3][2] * M.A[2][1] + A[3][3] * M.A[3][1],
        A[3][0] * M.A[0][2] + A[3][1] * M.A[1][2] + A[3][2] * M.A[2][2] + A[3][3] * M.A[3][2],
        A[3][0] * M.A[0][3] + A[3][1] * M.A[1][3] + A[3][2] * M.A[2][3] + A[3][3] * M.A[3][3]
      );
    } /* End of 'operator*' function */

    /* Get determ of 3x3 matrix function.
     * ARGUMENTS:
     *   - matrix elements:
     *       Type &A11, Type &A12, Type &A13,
     *       Type &A21, Type &A22, Type &A23,
     *       Type &A31, Type &A32, Type &A33;
     * RETURNS:
     *   (Type) result of operation.
     */
    Type GetDeterm3x3(Type A11, Type A12, Type A13,
      Type A21, Type A22, Type A23,
      Type A31, Type A32, Type A33) const
    {
      return (A11 * A22 * A33 -
        A11 * A23 * A32 -
        A12 * A21 * A33 +
        A12 * A23 * A31 +
        A13 * A21 * A32 -
        A13 * A22 * A31);
    } /* End of 'GetDeterm3x3' function */

    /* Get determ of 4x4 matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result of operation.
     */
    Type operator!(VOID) const
    {
      return A[0][0] * GetDeterm3x3(A[1][1], A[1][2], A[1][3], A[2][1], A[2][2], A[2][3], A[3][1], A[3][2], A[3][3]) -
        A[0][1] * GetDeterm3x3(A[1][0], A[1][2], A[1][3], A[2][0], A[2][2], A[2][3], A[3][0], A[3][2], A[3][3]) +
        A[0][2] * GetDeterm3x3(A[1][0], A[1][1], A[1][3], A[2][0], A[2][1], A[2][3], A[3][0], A[3][1], A[3][3]) - -
        A[0][3] * GetDeterm3x3(A[1][0], A[1][1], A[1][2], A[2][0], A[2][1], A[2][2], A[3][0], A[3][1], A[3][2]);
    } /* End of 'operator!' function */

    /* Get identity matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline matr Identity(VOID) const
    {
      return matr(1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
    } /* End of 'Identity' function */

    /* Get inverse matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline matr Inverse(VOID) const
    {
      Type det = !*this;
      matr M;

      if (det == 0)
        return Identity();

      /* Build adjoint matrix */
      M.A[0][0] =
        +GetDeterm3x3(A[1][1], A[1][2], A[1][3],
          A[2][1], A[2][2], A[2][3],
          A[3][1], A[3][2], A[3][3]) / det;

      M.A[1][0] =
        -GetDeterm3x3(A[1][0], A[1][2], A[1][3],
          A[2][0], A[2][2], A[2][3],
          A[3][0], A[3][2], A[3][3]) / det;

      M.A[2][0] =
        +GetDeterm3x3(A[1][0], A[1][1], A[1][3],
          A[2][0], A[2][1], A[2][3],
          A[3][0], A[3][1], A[3][3]) / det;

      M.A[3][0] =
        -GetDeterm3x3(A[1][0], A[1][1], A[1][2],
          A[2][0], A[2][1], A[2][2],
          A[3][0], A[3][1], A[3][2]) / det;

      M.A[0][1] =
        -GetDeterm3x3(A[0][1], A[0][2], A[0][3],
          A[2][1], A[2][2], A[2][3],
          A[3][1], A[3][2], A[3][3]) / det;

      M.A[1][1] =
        +GetDeterm3x3(A[0][0], A[0][2], A[0][3],
          A[2][0], A[2][2], A[2][3],
          A[3][0], A[3][2], A[3][3]) / det;

      M.A[2][1] =
        -GetDeterm3x3(A[0][0], A[0][1], A[0][3],
          A[2][0], A[2][1], A[2][3],
          A[3][0], A[3][1], A[3][3]) / det;

      M.A[3][1] =
        +GetDeterm3x3(A[0][0], A[0][1], A[0][2],
          A[2][0], A[2][1], A[2][2],
          A[3][0], A[3][1], A[3][2]) / det;

      M.A[0][2] =
        +GetDeterm3x3(A[0][1], A[0][2], A[0][3],
          A[1][1], A[1][2], A[1][3],
          A[3][1], A[3][2], A[3][3]) / det;

      M.A[1][2] =
        -GetDeterm3x3(A[0][0], A[0][2], A[0][3],
          A[1][0], A[1][2], A[1][3],
          A[3][0], A[3][2], A[3][3]) / det;

      M.A[2][2] =
        +GetDeterm3x3(A[0][0], A[0][1], A[0][3],
          A[1][0], A[1][1], A[1][3],
          A[3][0], A[3][1], A[3][3]) / det;

      M.A[3][2] =
        -GetDeterm3x3(A[0][0], A[0][1], A[0][2],
          A[1][0], A[1][1], A[1][2],
          A[3][0], A[3][1], A[3][2]) / det;

      M.A[0][3] =
        +GetDeterm3x3(A[0][1], A[0][2], A[0][3],
          A[1][1], A[1][2], A[1][3],
          A[2][1], A[2][2], A[2][3]) / det;

      M.A[1][3] =
        -GetDeterm3x3(A[0][0], A[0][2], A[0][3],
          A[1][0], A[1][2], A[1][3],
          A[2][0], A[2][2], A[2][3]) / det;

      M.A[2][3] =
        +GetDeterm3x3(A[0][0], A[0][1], A[0][3],
          A[1][0], A[1][1], A[1][3],
          A[2][0], A[2][1], A[2][3]) / det;

      M.A[3][3] =
        -GetDeterm3x3(A[0][0], A[0][1], A[0][2],
          A[1][0], A[1][1], A[1][2],
          A[2][0], A[2][1], A[2][2]) / det;

      return M;
    } /* End of 'Inverse' function */


    /* Get transpose matrix function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline matr Transpose(VOID) const
    {
      matr M;

      for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
          M.A[i][j] = A[j][i];
      return M;
    } /* End of 'Transpose' function */

    /* Rotate matrix by OX function.
     * ARGUMENTS:
     *   - angle to rotate in degrees:
     *       Type AngleInDegrees;
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline static  matr RotateX(Type AngleInDegrees)
    {
      Type
        AngleInRadians = Degree2Radian(AngleInDegrees),
        si = sin(AngleInRadians), co = cos(AngleInRadians);

      return matr(1, 0, 0, 0,
        0, co, si, 0,
        0, -si, co, 0,
        0, 0, 0, 1);
    } /* End of 'RotateX' function */

    /* Rotate matrix by OY function.
     * ARGUMENTS:
     *   - angle to rotate in degrees:
     *       Type AngleInDegrees;
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline static matr RotateY(Type AngleInDegrees)
    {
      Type
        AngleInRadians = Degree2Radian(AngleInDegrees),
        si = sin(AngleInRadians), co = cos(AngleInRadians);

      return matr(co, 0, -si, 0,
        0, 1, 0, 0,
        si, 0, co, 0,
        0, 0, 0, 1);
    } /* End of 'RotateY' function */

    /* Rotate matrix by OZ function.
     * ARGUMENTS:
     *   - angle to rotate in degrees:
     *       Type AngleInDegrees;
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline static matr RotateZ(Type AngleInDegrees)
    {
      Type
        AngleInRadians = Degree2Radian(AngleInDegrees),
        si = sin(AngleInRadians), co = cos(AngleInRadians);

      return matr(co, si, 0, 0,
        -si, co, 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1);
    } /* End of 'RotateZ' function */

    /* Rotate matrix function.
     * ARGUMENTS:
     *   - angle to rotate in degrees:
     *       Type AngleInDegrees;
     *   - vector to rotate:
     *       vec3<Type> &V;
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline matr Rotate(Type AngleInDegrees, const vec3<Type>& V) const
    {
      Type
        AngleInRadians = Degree2Radian(AngleInDegrees),
        si = sin(AngleInRadians), co = cos(AngleInRadians);

      vec3<Type> R = V;
      return matr(
        co + R.X * R.X * (1 - co),
        R.X * R.Y * (1 - co) + R.Z * si,
        R.X * R.Z * (1 - co) - R.Y * si, 0,
        R.Y * R.X * (1 - co) - R.Z * si,
        co + R.Y * R.Y * (1 - co),
        R.Y * R.Z * (1 - co) + R.X * si, 0,
        R.Z * R.X * (1 - co) + R.Y * si,
        R.Z * R.Y * (1 - co) - R.X * si,
        co + R.Z * R.Z * (1 - co), 0,
        0, 0, 0, 1);
    } /* End of 'Rotate' function */

    /* Scale matrix function.
     * ARGUMENTS:
     *   - vector to scale:
     *       vec3<Type> &S;
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline matr Scale(const vec3<Type>& S) const
    {
      return matr(S[0], 0, 0, 0,
        0, S[1], 0, 0,
        0, 0, S[2], 0,
        0, 0, 0, 1);
    } /* End of 'Scale' function */

    /* Translate matrix function.
     * ARGUMENTS:
     *   - vector to translate:
     *       vec3<Type> &T;
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline matr Translate(const vec3<Type>& T) const
    {
      return matr(1, 0, 0, 0,
        0, 1, 0, 0,
        0, 0, 1, 0,
        T[0], T[1], T[2], 1);
    } /* End of 'Translate' function */

    /* Transform point of vector function.
     * ARGUMENTS:
     *   - vector to transform point:
     *       vec3<Type> &V;
     * RETURNS:
     *   (vec3) result new vector.
     */
    inline vec3<Type> TransformPoint(const vec3<Type>& V) const
    {
      return vec3<Type>(
        V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0] + A[3][0],
        V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1] + A[3][1],
        V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2] + A[3][2]);
    } /* End of 'TransformPoint' function */

    /* Transform vector function.
     * ARGUMENTS:
     *   - vector to transform:
     *       vec3<Type> &V;
     * RETURNS:
     *   (vec3) result new vector.
     */
    inline vec3<Type> TransformVector(const vec3<Type>& V) const
    {
      return vec3<Type>(
        V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0],
        V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1],
        V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2]);
    } /* End of 'TransformVector' function */

    /* Transform vector of normal function.
     * ARGUMENTS:
     *   - vector to transform:
     *       vec3<Type> &V;
     * RETURNS:
     *   (vec3) result new vector.
     */
    inline vec3<Type> TransformNormal(const vec3<Type>& V) const
    {
      matr M = A.Inverse();

      return vec3<Type>(
        V[0] * M.A[0][0] + V[1] * M.A[1][0] + V[2] * M.A[2][0],
        V[0] * M.A[0][1] + V[1] * M.A[1][1] + V[2] * M.A[2][1],
        V[0] * M.A[0][2] + V[1] * M.A[1][2] + V[2] * M.A[2][2]);
    } /* End of 'TransformNormal' function */

    /* Transform matrix 4x4 function.
     * ARGUMENTS:
     *   - vector to transform:
     *       vec3<Type> &V;
     * RETURNS:
     *   (vec3) result new vector.
     */
    inline vec3<Type> Transform4x4(const vec3<Type>& V) const
    {
      Type w = V[0] * A[0][3] + V[1] * A[1][3] + V[2] * A[2][3] + A[3][3];

      return vec3<Type>(
        (V[0] * A[0][0] + V[1] * A[1][0] + V[2] * A[2][0] + A[3][0]) / w,
        (V[0] * A[0][1] + V[1] * A[1][1] + V[2] * A[2][1] + A[3][1]) / w,
        (V[0] * A[0][2] + V[1] * A[1][2] + V[2] * A[2][2] + A[3][2]) / w);
    } /* End of 'Transform4x4' function */

    /* View for camera matrix function.
     * ARGUMENTS:
     *   - vector for position:
     *       vec3 Loc;
     *   - vector for looking at:
     *       vec3 At;
     *   - vector lokking up:
     *       vec3 Up1;
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline static matr View(const vec3<Type>& Loc, const vec3<Type>& At, const vec3<Type>& Up1)
    {
      vec3<Type>
        Dir = (At - Loc).Normalizing(),
        Right = (Dir % Up1).Normalizing(),
        Up = (Right % Dir).Normalizing();
      return matr(Right.X, Up.X, -Dir.X, 0,
        Right.Y, Up.Y, -Dir.Y, 0,
        Right.Z, Up.Z, -Dir.Z, 0,
        -(Loc & Right), -(Loc & Up), (Loc & Dir), 1);
    } /* End of 'View' function */

    /* Ortho projection matrix function.
     * ARGUMENTS:
     *   - coordinates:
     *       Type Left, Type Right, Type Bottom, Type Top, Type Near, Type Far;
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline static matr Ortho(Type Left, Type Right, Type Bottom,
      Type Top, Type Near, Type Far)
    {
      return matr(2 / (Right - Left), 0, 0, 0,
        0, 2 / (Top - Bottom), 0, 0,
        0, 0, -2 / (Far - Near), 0,
        -(Right + Left) / (Right - Left), -(Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), 1);
    } /* End of 'Ortho' function */

    /* View frustum matrix function.
     * ARGUMENTS:
     *   - coordinates:
     *       Type l, Type r, Type b, Type t, Type n, Type f;
     * RETURNS:
     *   (matr) result new matrix.
     */
    inline static matr Frustum(Type l, Type r, Type b,
      Type t, Type n, Type f)
    {
      return matr((2 * n) / (r - l), 0, 0, 0,
        0, (2 * n) / (t - b), 0, 0,
        (r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n), -1,
        0, 0, (-2 * n * f) / (f - n), 0);
    } /* End of 'Frustum' function */
  }; /* End of 'matr' class */
} /* end of 'mth' namespace */

#endif /* __mth_matr_h_ */

/* END OF 'mth_matr.h' FILE */