/* FILE NAME   : mth_vec2.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Math module.
 *               3D math vector 2D implementation module.
 */

#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include "mth_def.h"

 /* Math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
  class vec2
  {
  private:
    Type X, Y; // Vector coordinates

  public:
    /* Vector default constructor */
    vec2(void)
    {
    } /* End of 'vec2' constructor */
    /* Vector constructor by 3 coordinates */
    vec2(Type A, Type B) : X(A), Y(B)
    {
    } /* End of 'vec2' constructor */
    /* Vector constructor by 1 coordinate */
    explicit vec2(Type A) : X(A), Y(A)
    {
    } /* End of 'vec2' constructor */

    /* Sum two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2) result new vector.
     */
    vec2 operator+(const vec2& V) const
    {
      return vec2(X + V.X, Y + V.Y);
    } /* End of 'operator+' function */

    /* Sum a vector and a number function.
     * ARGUMENTS:
     *   - number for sum:
     *       Type N;
     * RETURNS:
     *   (vec2) result new vector.
     */
    vec2 operator+(Type N) const
    {
      return vec2(X + N, Y + N);
    } /* End of 'operator+' function */

    /* Sum one vector to another function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2 &) changed first vector.
     */
    vec2& operator+=(const vec2& V)
    {
      X += V.X;
      Y += V.Y;
      return *this;
    } /* End of 'operator+=' function */

    /* Sum vector and a number function.
     * ARGUMENTS:
     *   - number to sum:
     *       Type N;
     * RETURNS:
     *   (vec2 &) changed vector.
     */
    vec2& operator+=(Type N)
    {
      X += N;
      Y += N;
      return *this;
    } /* End of 'operator+=' function */


    /* Sub two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2) result new vector.
     */
    vec2 operator-(const vec2& V) const
    {
      return vec2(X - V.X, Y - V.Y);
    } /* End of 'operator-' function */

    /* Sub a vector and a number function.
     * ARGUMENTS:
     *   - number for sub:
     *       Type N;
     * RETURNS:
     *   (vec2) result new vector.
     */
    vec2 operator-(Type N) const
    {
      return vec2(X - N, Y - N);
    } /* End of 'operator-' function */

    /* Get negative of vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) result new vector.
     */
    vec2 operator-(VOID) const
    {
      return vec2(-X, -Y);
    } /* End of 'operator-' function */

    /* Sub one vector from another function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2 &) changed first vector.
     */
    vec2& operator-=(const vec2& V)
    {
      X -= V.X;
      Y -= V.Y;
      return *this;
    } /* End of 'operator-=' function */

    /* Sub vector and a number function.
     * ARGUMENTS:
     *   - number to sub:
     *       Type N;
     * RETURNS:
     *   (vec2 &) changed vector.
     */
    vec2& operator-=(Type N)
    {
      X -= N;
      Y -= N;
      return *this;
    } /* End of 'operator-=' function */


    /* Multiply two vectors (all components by each other) function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2) result new vector.
     */
    vec2 operator*(const vec2& V) const
    {
      return vec2(X * V.X, Y * V.Y);
    } /* End of 'operator*' function */

    /* Multiply vector by a number function.
     * ARGUMENTS:
     *   - number for multiplication:
     *       Type N;
     * RETURNS:
     *   (vec2) result new vector.
     */
    vec2 operator*(Type N) const
    {
      return vec2(X * N, Y * N);
    } /* End of 'operator*' function */

    /* Multiply two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2 &) changed first vector.
     */
    vec2& operator*=(const vec2& V)
    {
      X *= V.X;
      Y *= V.Y;
      return *this;
    } /* End of 'operator*=' function */

    /* Multiply vector by a number function.
     * ARGUMENTS:
     *   - number for multiplication:
     *       Type N;
     * RETURNS:
     *   (vec2 &) changed vector.
     */
    vec2& operator*=(Type N)
    {
      X *= N;
      Y *= N;
      return *this;
    } /* End of 'operator*=' function */

    /* Divise vector by a number function.
     * ARGUMENTS:
     *   - number for division:
     *       Type N;
     * RETURNS:
     *   (vec2) result new vector.
     */
    vec2 operator/(Type N) const
    {
      assert(N != 0);
      return vec2(X / N, Y / N);
    } /* End of 'operator/' function */

    /* Divise vector by a number function.
     * ARGUMENTS:
     *   - number for division:
     *       Type N;
     * RETURNS:
     *   (vec2 &) changed vector.
     */
    vec2& operator/=(Type N)
    {
      assert(N != 0);
      X /= N;
      Y /= N;
      return *this;
    } /* End of 'operator/=' function */


    /* Dot product of two vectors function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec2 &V;
     * RETURNS:
     *   (Type) result of operation.
     */
    Type operator&(const vec2& V) const
    {
      return X * V.X + Y * V.Y;
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
      return Y;
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
      assert(i >= 0 && i <= 1);
      return *(&X + i);
    } /* End of 'operator[]' function */

    /* Convert vec2 to different types function.
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
     *   (vec2 &) changed normalized vector.
     */
    inline vec2& Normalize(VOID)
    {
      Type len = !*this;

      if (len == 1 || len == 0)
        return *this;
      return *this /= len;
    } /* End of 'Normalize' function */

    /* Normalize a vector function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) result new normalized vector.
     */
    inline vec2 Normalizing(VOID)
    {
      Type len = !*this;

      if (len == 1 || len == 0)
        return *this;
      return *this / len;
    } /* End of 'Normalizing' function */

    /* Get distance betwenn two points (vectors) function.
     * ARGUMENTS:
     *   - reference to second vector:
     *       vec2 &V;
     * RETURNS:
     *   (vec2) result distance.
     */
    inline Type Distance(const vec2& V) const
    {
      return !(*this - V);
    } /* End of 'Distance' function */

    /* Reset vector (with zero) function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) result vector.
     */
    inline static vec2 Zero(VOID)
    {
      return vec2(0);
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
     *   (vec2) result vector.
     */
    inline static vec2 Rnd0(VOID)
    {
      return vec2(R0(), R0(), R0());
    } /* End of 'Rnd0' function */

    /* Set vector with rand numbers from -1 to 1 function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (vec2) result vector.
     */
    inline static vec2 Rnd1(VOID)
    {
      return vec2(R1(), R1(), R1());
    } /* End of 'Rnd1' function */

  }; /* End of 'vec2' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec2_h_ */

/* END OF 'mth_vec2.h' FILE */