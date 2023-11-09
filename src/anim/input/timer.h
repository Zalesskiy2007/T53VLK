/* FILE NAME   : timer.h
 * PROGRAMMER  : MZ2
 * LAST UPDATE : 01.09.2023
 * PURPOSE     : Animation 3D render with OpenGL project.
 *               Animation input system module.
 *               Timer handle module.
 */

#ifndef __timer_h_
#define __timer_h_

#include "def.h"

 /* Project namespace */
namespace mzgl
{
  /* Timer representation type */
  class timer
  {
  private:
    UINT64
      StartTime,     // Start program tile
      OldTime,       // Previous frame time
      OldTimeFPS,    // Old time FPS measurement
      PauseTime,     // Time during pause period
      TimePerSec,    // Timer resolution
      FrameCounter;  // Frame counter

  public:
    DBL
     GlobalTime = 0, GlobalDeltaTime = 0,  //// global time and interframe interval
      Time = 0, DeltaTime = 0,              // Time with pause and interframe interval
      FPS;                                  // Frames per second value
    BOOL IsPause;                           // Pause flag

    /* Timer default constructor */
    timer(VOID)
    {
      LARGE_INTEGER t;

      QueryPerformanceFrequency(&t);
      TimePerSec = t.QuadPart;
      QueryPerformanceCounter(&t);
      StartTime = OldTime = OldTimeFPS = t.QuadPart;
      FrameCounter = 0;
      IsPause = FALSE;
      FPS = 30.0;
      PauseTime = 0;
    } /* End of 'timer' constructor */

    /* Timer response function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Response(VOID)
    {
      LARGE_INTEGER t;

      QueryPerformanceCounter(&t);
      /*// global time */
     // globalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
     // globalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
      /* Time with pause */
      if (IsPause)
      {
        DeltaTime = 0;
        PauseTime += t.QuadPart - OldTime;
      }
      else
      {
        DeltaTime =// globalDeltaTime;
        Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }
      /* FPS */
      FrameCounter++;
      if (t.QuadPart - OldTimeFPS > TimePerSec)
      {
        FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
        OldTimeFPS = t.QuadPart;
        FrameCounter = 0;
      }
      OldTime = t.QuadPart;
    } /* End of 'Response' function */
  }; /* End of 'timer' class */

} /* end of 'mzgl' namespace */

#endif /* __timer_h_ */

/* END OF 'timer.h' FILE */