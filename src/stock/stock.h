/* FILE NAME   : stock.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Animation system module.
 *               Stock handle module.
 */

#ifndef __stock_h_
#define __stock_h_

#include "def.h"

#include <vector>

 /* Project namespace */
namespace mzgl
{
  /* Stock representation type */
  template<typename Type>
  class stock : public std::vector<Type>
  {
  public:
    /* Stock default constructor */
    stock(VOID)
    {
    } /* End of 'stock' constructor */

    /* Add new element to stock function.
     * ARGUMENTS:
     *   - reference to new element:
     *       Type &X;
     * RETURNS:
     *   (stock &) result stock (with one element added).
     */
    stock& operator<<(const Type& X)
    {
      this->push_back(X);
      return *this;
    } /* End of 'operator<<' function */

    /* Walk throw stock function.
     * ARGUMENTS:
     *   - type of stock elements:
     *       WalkType Walk;
     * RETURNS: None.
     */
    template<class WalkType>
    VOID Walk(WalkType Walk)
    {
      for (auto& X : *this)
        Walk(X);
    } /* End of 'Walk' function */
  }; /* End of 'stock' class */
} /* end of 'mzgl' namespace */


#endif /* __stock_h_ */

/* END OF 'stock.h' FILE */