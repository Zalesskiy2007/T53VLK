/* FILE NAME   : mth_vec4.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Math module.
 *               3D math vector 4D implementation module.
 */

#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include "mth_def.h"

 /* Math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
  class vec4
  {
  private:
    Type X, Y, Z, W; // Vector coordinates

  public:
    /* Vector default constructor */
    vec4(void)
    {
    } /* End of 'vec4' constructor */
    /* Vector constructor by 4 coordinates */
    vec4(Type A, Type B, Type C, Type D) : X(A), Y(B), Z(C), W(D)
    {
    } /* End of 'vec4' constructor */
    /* Vector constructor by 1 coordinate */
    explicit vec4(Type A) : X(A), Y(A), Z(A), W(A)
    {
    } /* End of 'vec4' constructor */
    /* Vector constructor from 3 components */
    vec4(const vec3<Type>& V) : X(V.X), Y(V.Y), Z(V.Z), W(1)
    {
    } /* End of 'vec4' constructor */
    /* Vector constructor from 3 components and forth different component */
    vec4(const vec3<Type>& V, Type A) : X(V.X), Y(V.Y), Z(V.Z), W(A)
    {
    } /* End of 'vec4' constructor */

    /* Sum two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4) result new vector.
     */
    vec4 operator+(const vec4& V) const
    {
      return vec4(X + V.X, Y + V.Y, Z + V.Z, W + V.W);
    } /* End of 'operator+' function */

    /* Sum a vector and a number function.
     * ARGUMENTS:
     *   - number for sum:
     *       Type N;
     * RETURNS:
     *   (vec4) result new vector.
     */
    vec4 operator+(Type N) const
    {
      return vec4(X + N, Y + N, Z + N, W + N);
    } /* End of 'operator+' function */

    /* Sum one vector to another function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4 &) changed first vector.
     */
    vec4& operator+=(const vec4& V)
    {
      X += V.X;
      Y += V.Y;
      Z += V.Z;
      W += V.W;
      return *this;
    } /* End of 'operator+=' function */

    /* Sum vector and a number function.
     * ARGUMENTS:
     *   - number to sum:
     *       Type N;
     * RETURNS:
     *   (vec4 &) changed vector.
     */
    vec4& operator+=(Type N)
    {
      X += N;
      Y += N;
      Z += N;
      W += N;
      return *this;
    } /* End of 'operator+=' function */


    /* Sub two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4) result new vector.
     */
    vec4 operator-(const vec4& V) const
    {
      return vec4(X - V.X, Y - V.Y, Z - V.Z, W - V.W);
    } /* End of 'operator-' function */

    /* Sub a vector and a number function.
     * ARGUMENTS:
     *   - number for sub:
     *       Type N;
     * RETURNS:
     *   (vec4) result new vector.
     */
    vec4 operator-(Type N) const
    {
      return vec4(X - N, Y - N, Z - N, W - N);
    } /* End of 'operator-' function */

    /* Get negative of vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result new vector.
     */
    vec4 operator-(VOID) const
    {
      return vec4(-X, -Y, -Z, -W);
    } /* End of 'operator-' function */

    /* Sub one vector from another function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4 &) changed first vector.
     */
    vec4& operator-=(const vec4& V)
    {
      X -= V.X;
      Y -= V.Y;
      Z -= V.Z;
      W -= V.W;
      return *this;
    } /* End of 'operator-=' function */

    /* Sub vector and a number function.
     * ARGUMENTS:
     *   - number to sub:
     *       Type N;
     * RETURNS:
     *   (vec4 &) changed vector.
     */
    vec4& operator-=(Type N)
    {
      X -= N;
      Y -= N;
      Z -= N;
      W -= N;
      return *this;
    } /* End of 'operator-=' function */


    /* Multiply two vectors (all components by each other) function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4) result new vector.
     */
    vec4 operator*(const vec4& V) const
    {
      return vec4(X * V.X, Y * V.Y, Z * V.Z, W * V.W);
    } /* End of 'operator*' function */

    /* Multiply vector by a number function.
     * ARGUMENTS:
     *   - number for multiplication:
     *       Type N;
     * RETURNS:
     *   (vec4) result new vector.
     */
    vec4 operator*(Type N) const
    {
      return vec4(X * N, Y * N, Z * N, W * N);
    } /* End of 'operator*' function */

    /* Multiply two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4 &) changed first vector.
     */
    vec4& operator*=(const vec4& V)
    {
      X *= V.X;
      Y *= V.Y;
      Z *= V.Z;
      W *= V.W;
      return *this;
    } /* End of 'operator*=' function */

    /* Multiply vector by a number function.
     * ARGUMENTS:
     *   - number for multiplication:
     *       Type N;
     * RETURNS:
     *   (vec4 &) changed vector.
     */
    vec4& operator*=(Type N)
    {
      X *= N;
      Y *= N;
      Z *= N;
      W *= N;
      return *this;
    } /* End of 'operator*=' function */

    /* Divise vector by a number function.
     * ARGUMENTS:
     *   - number for division:
     *       Type N;
     * RETURNS:
     *   (vec4) result new vector.
     */
    vec4 operator/(Type N) const
    {
      assert(N != 0);
      return vec4(X / N, Y / N, Z / N, W / N);
    } /* End of 'operator/' function */

    /* Divise vector by a number function.
     * ARGUMENTS:
     *   - number for division:
     *       Type N;
     * RETURNS:
     *   (vec4 &) changed vector.
     */
    vec4& operator/=(Type N)
    {
      assert(N != 0);
      X /= N;
      Y /= N;
      Z /= N;
      W /= N;
      return *this;
    } /* End of 'operator/=' function */


    /* Dot product of two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec4 &V;
     * RETURNS:
     *   (Type) result of operation.
     */
    Type operator&(const vec4& V) const
    {
      return X * V.X + Y * V.Y + Z * V.Z + W * V.W;
    } /* End of 'operator&' function */


     /* Get length of vector function.
      * ARGUMENTS: None.
      * RETURNS:
      *   (Type) result length of vector.
      */
    Type operator!(VOID) const
    {
      Type len = *this & *this;

      if (len == 1 || len == 0)
        return len;
      return sqrt(len);
    } /* End of 'operator!' function */

    /* Get length in square of vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result length in square of vector.
     */
    Type operator~(VOID) const
    {
      return *this & *this;
    } /* End of 'operator~' function */

    /* Get componet of vector by index function.
     * ARGUMENTS:
     *   - index number;:
     *       INT i;
     * RETURNS:
     *   (Type) result vector component.
     */
    Type operator[](INT i) const
    {
      if (i == 0)
        return X;
      if (i == 1)
        return Y;
      if (i == 2)
        return Z;
      return W;
    } /* End of 'operator[]' function */

    /* Get componet of vector by index - lvalue - function.
     * ARGUMENTS:
     *   - index number;:
     *       INT i;
     * RETURNS:
     *   (Type) result vector component.
     */
    Type& operator[](INT i)
    {
      assert(i >= 0 && i <= 3);
      return *(&X + i);
    } /* End of 'operator[]' function */

    /* Convert vec4 to different types function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result vector.
     */
    operator Type* (VOID)
    {
      return (Type*)&X;
    } /* End of 'operator Type*' function */

    /* Normalize a vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4 &) changed normalized vector.
     */
    inline vec4& Normalize(VOID)
    {
      Type len = !*this;

      if (len == 1 || len == 0)
        return *this;
      return *this /= len;
    } /* End of 'Normalize' function */

    /* Normalize a vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result new normalized vector.
     */
    inline vec4 Normalizing(VOID)
    {
      Type len = !*this;

      if (len == 1 || len == 0)
        return *this;
      return *this / len;
    } /* End of 'Normalizing' function */

    /* Get distance betwenn two points (vectors) function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec4 &V;
     * RETURNS:
     *   (vec4) result distance.
     */
    inline Type Distance(const vec4& V) const
    {
      return !(*this - V);
    } /* End of 'Distance' function */

    /* Reset vector (with zero) function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result vector.
     */
    inline static vec4 Zero(VOID)
    {
      return vec4(0);
    } /* End of 'Zero' function */

    /* Get rand number from 0 to 1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) random number from 0 to 1.
     */
    inline static Type R0(void)
    {
      return rand() / (Type)RAND_MAX;
    } /* End of 'R0' function */

    /* Get rand number from -1 to 1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) random number from -1 to 1.
     */
    inline static Type R1(void)
    {
      return 2.0 * rand() / (Type)RAND_MAX - 1;
    } /* End of 'R1' function */

    /* Set vector with rand numbers from 0 to 1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result vector.
     */
    inline static vec4 Rnd0(VOID)
    {
      return vec4(R0(), R0(), R0());
    } /* End of 'Rnd0' function */

    /* Set vector with rand numbers from -1 to 1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec4) result vector.
     */
    inline static vec4 Rnd1(VOID)
    {
      return vec4(R1(), R1(), R1());
    } /* End of 'Rnd1' function */
  }; /* End of 'vec4' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec4_h_ */

/* END OF 'mth_vec4.h' FILE */