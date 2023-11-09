/* FILE NAME   : mth_vec3.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Math module.
 *               3D math vector 3D implementation module.
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mth_def.h"

 /* Math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
  class vec3
  {
    template<typename Type1>
    friend class matr;
    template<typename Type2>
    friend class vec4;
  private:
    Type X, Y, Z; // Vector coordinates

  public:
    /* Vector default constructor */
    vec3(void)
    {
    } /* End of 'vec3' constructor */
    /* Vector constructor by 3 coordinates */
    vec3(Type A, Type B, Type C) : X(A), Y(B), Z(C)
    {
    } /* End of 'vec3' constructor */
    /* Vector constructor by 1 coordinate */
    explicit vec3(Type A) : X(A), Y(A), Z(A)
    {
    } /* End of 'vec3' constructor */

    /* Sum two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec3 &V;
     * RETURNS:
     *   (vec3) result new vector.
     */
    vec3 operator+(const vec3& V) const
    {
      return vec3(X + V.X, Y + V.Y, Z + V.Z);
    } /* End of 'operator+' function */

    /* Sum a vector and a number function.
     * ARGUMENTS:
     *   - number for sum:
     *       Type N;
     * RETURNS:
     *   (vec3) result new vector.
     */
    vec3 operator+(Type N) const
    {
      return vec3(X + N, Y + N, Z + N);
    } /* End of 'operator+' function */

    /* Sum one vector to another function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec3 &V;
     * RETURNS:
     *   (vec3 &) changed first vector.
     */
    vec3& operator+=(const vec3& V)
    {
      X += V.X;
      Y += V.Y;
      Z += V.Z;
      return *this;
    } /* End of 'operator+=' function */

    /* Sum vector and a number function.
     * ARGUMENTS:
     *   - number to sum:
     *       Type N;
     * RETURNS:
     *   (vec3 &) changed vector.
     */
    vec3& operator+=(Type N)
    {
      X += N;
      Y += N;
      Z += N;
      return *this;
    } /* End of 'operator+=' function */


    /* Sub two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec3 &V;
     * RETURNS:
     *   (vec3) result new vector.
     */
    vec3 operator-(const vec3& V) const
    {
      return vec3(X - V.X, Y - V.Y, Z - V.Z);
    } /* End of 'operator-' function */

    /* Sub a vector and a number function.
     * ARGUMENTS:
     *   - number for sub:
     *       Type N;
     * RETURNS:
     *   (vec3) result new vector.
     */
    vec3 operator-(Type N) const
    {
      return vec3(X - N, Y - N, Z - N);
    } /* End of 'operator-' function */

    /* Get negative of vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) result new vector.
     */
    vec3 operator-(VOID) const
    {
      return vec3(-X, -Y, -Z);
    } /* End of 'operator-' function */

    /* Sub one vector from another function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec3 &V;
     * RETURNS:
     *   (vec3 &) changed first vector.
     */
    vec3& operator-=(const vec3& V)
    {
      X -= V.X;
      Y -= V.Y;
      Z -= V.Z;
      return *this;
    } /* End of 'operator-=' function */

    /* Sub vector and a number function.
     * ARGUMENTS:
     *   - number to sub:
     *       Type N;
     * RETURNS:
     *   (vec3 &) changed vector.
     */
    vec3& operator-=(Type N)
    {
      Y -= N;
      Z -= N;
      X -= N;
      return *this;
    } /* End of 'operator-=' function */


    /* Multiply two vectors (all components by each other) function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec3 &V;
     * RETURNS:
     *   (vec3) result new vector.
     */
    vec3 operator*(const vec3& V) const
    {
      return vec3(X * V.X, Y * V.Y, Z * V.Z);
    } /* End of 'operator*' function */

    /* Multiply vector by a number function.
     * ARGUMENTS:
     *   - number for multiplication:
     *       Type N;
     * RETURNS:
     *   (vec3) result new vector.
     */
    vec3 operator*(Type N) const
    {
      return vec3(X * N, Y * N, Z * N);
    } /* End of 'operator*' function */

    /* Multiply two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec3 &V;
     * RETURNS:
     *   (vec3 &) changed first vector.
     */
    vec3& operator*=(const vec3& V)
    {
      X *= V.X;
      Y *= V.Y;
      Z *= V.Z;
      return *this;
    } /* End of 'operator*=' function */

    /* Multiply vector by a number function.
     * ARGUMENTS:
     *   - number for multiplication:
     *       Type N;
     * RETURNS:
     *   (vec3 &) changed vector.
     */
    vec3& operator*=(Type N)
    {
      X *= N;
      Y *= N;
      Z *= N;
      return *this;
    } /* End of 'operator*=' function */

    /* Divise vector by a number function.
     * ARGUMENTS:
     *   - number for division:
     *       Type N;
     * RETURNS:
     *   (vec3) result new vector.
     */
    vec3 operator/(Type N) const
    {
      assert(N != 0);
      return vec3(X / N, Y / N, Z / N);
    } /* End of 'operator/' function */

    /* Divise vector by a number function.
     * ARGUMENTS:
     *   - number for division:
     *       Type N;
     * RETURNS:
     *   (vec3 &) changed vector.
     */
    vec3& operator/=(Type N)
    {
      assert(N != 0);
      X /= N;
      Y /= N;
      Z /= N;
      return *this;
    } /* End of 'operator/=' function */


    /* Dot product of two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec3 &V;
     * RETURNS:
     *   (Type) result of operation.
     */
    Type operator&(const vec3& V) const
    {
      return X * V.X + Y * V.Y + Z * V.Z;
    } /* End of 'operator&' function */

    /* Cross product of two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec3 &V;
     * RETURNS:
     *   (vec3) result new vector.
     */
    vec3 operator%(const vec3& V) const
    {
      return vec3(Y * V.Z - Z * V.Y,
        -(X * V.Z - Z * V.X),
        X * V.Y - Y * V.X);
    } /* End of 'operator%' function */


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
     *   - index number:
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
      return Z;
    } /* End of 'operator[]' function */

    /* Get componet of vector by index - lvalue - function.
     * ARGUMENTS:
     *   - index number:
     *       INT i;
     * RETURNS:
     *   (Type) result vector component.
     */
    Type& operator[](INT i)
    {
      assert(i >= 0 && i <= 2);
      return *(&X + i);
    } /* End of 'operator[]' function */

    /* Convert vec3 to different types function.
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
     *   (vec3 &) changed normalized vector.
     */
    inline vec3& Normalize(VOID)
    {
      Type len = !*this;

      if (len == 1 || len == 0)
        return *this;
      return *this /= len;
    } /* End of 'Normalize' function */

    /* Normalize a vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) result new normalized vector.
     */
    inline vec3 Normalizing(VOID) const
    {
      Type len = !*this;

      if (len == 1 || len == 0)
        return *this;
      return *this / len;
    } /* End of 'Normalizing' function */

    /* Get distance betwenn two points (vectors) function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec3 &V;
     * RETURNS:
     *   (vec3) result distance.
     */
    inline Type Distance(const vec3& V) const
    {
      return !(*this - V);
    } /* End of 'Distance' function */

    /* Reset vector (with zero) function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) result vector.
     */
    inline static vec3 Zero(VOID)
    {
      return vec3(0);
    } /* End of 'Zero' function */

    /* Get rand number from 0 to 1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) random number from 0 to 1.
     */
    inline static Type R0(VOID)
    {
      return rand() / (Type)RAND_MAX;
    } /* End of 'R0' function */

    /* Get rand number from -1 to 1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) random number from -1 to 1.
     */
    inline static Type R1(VOID)
    {
      return 2.0 * rand() / (Type)RAND_MAX - 1;
    } /* End of 'R1' function */

    /* Set vector with rand numbers from 0 to 1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) result vector.
     */
    inline static vec3 Rnd0(VOID)
    {
      return vec3(R0(), R0(), R0());
    } /* End of 'Rnd0' function */

    /* Set vector with rand numbers from -1 to 1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec3) result vector.
     */
    inline static vec3 Rnd1(VOID)
    {
      return vec3(R1(), R1(), R1());
    } /* End of 'Rnd1' function */

    /* Find maximum number from two function.
     * ARGUMENTS:
     *   - numbers:
     *       Type A, Type B;
     * RETURNS:
     *   (Type) result number.
     */
    inline static Type MaxC2(Type A, Type B)
    {
      return A > B ? A : B;
    } /* End of 'MaxC2' function */

    /* Find maximum component of function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (Type) result component.
     */
    inline Type MaxC3(VOID) const
    {
      return MaxC2(MaxC2(X, Y), Z);
    } /* End of 'MaxC3' function */


  }; /* End of 'vec3' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */