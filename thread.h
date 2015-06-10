/** \file thread.h
 *  \brief Simple pseudo thread class that allows "parallel" timed execution of multiple tasks.
 *
 *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
 *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
 *  \date	11.12.2013
 *  \version	1.1
 */
#ifndef __THREAD_H__
#define __THREAD_H__

#include "Arduino.h"

#ifndef ulong
typedef unsigned long ulong;	//!< Short term for unsigned long
#endif // ulong
#ifndef uint
typedef unsigned int uint;	//!< Short term for unsigned int
#endif // uint
#ifndef uchar
typedef unsigned char uchar;	//!< Short term for unsigned char
#endif // uchar

#define ULONG_MAX 4294967295
#define ULONG_MEAN 0.5 * ULONG_MAX 

/** \class thread
 *  \brief Simple pseudo thread class that allows "parallel" timed execution of multiple tasks.
 *
 *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
 *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
 *  \date	11.12.2013
 *  \version	1.1
 */
class thread
{
private:
  ulong _time;       //!< Target time set by user [us]
  ulong _last;       //!< Start time [us]
  int timeout;
  bool error;
   
  /**
   *  \brief Virtual class that needs to be replaced in sibling. Holds the actual computation.
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  virtual void computation() = 0;
public:
  /**
   *  \brief Constructor: Does nothing 
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  thread() : _time(0), timeout(-1), error(false)
  {
    setMicros(0);
  }
  
  /**
   *  \brief Constructor: Starts timer and sets target time
   *
   *  \param[in]  time    Target time in micro seconds
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  thread( ulong time) : _time(time), timeout(-1), error(false)
  {
    setMicros( time);
  }
  
  /**
   *  \brief Checks time and executes computation. This function MUST be used to execute something.
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  void execute()
  {
    ulong _now = micros();
    long passed = (long)(_now - (_last+_time));
    if( passed >= 0)
    {
      if( timeout >= 0 && passed >= timeout)
      {
        error = true;  
      }
        
      _last = _now;
      computation();  
    }
  }
    
  /**
   *  \brief Set critical timeout
   *
   *  \param[in]  to    Timeout in micro seconds
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	11.12.2013
   *  \version	1.0
   */
  void setTimeout( int to)
  {
    timeout = to;  
  }
  
  /**
   *  \brief Get critical timeout
   *
   *  \return Timeout in micro seconds
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	11.12.2013
   *  \version	1.0
   */
  int getTimeout()
  {
    return timeout;  
  }
  
  /**
   *  \brief Set error flag
   *
   *  \param[in]  err    Error flag (default is true)
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	11.12.2013
   *  \version	1.0
   */
  void setError( bool err = true)
  {
    error = err;
  }
  
  /**
   *  \brief Reset error.
   *
   *  Set flag to false
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	11.12.2013
   *  \version	1.0
   */
  void resetError()
  {
    setError( false);
  }
  
  /**
   *  \brief Get error flag
   *
   *  \return  Error flag
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	11.12.2013
   *  \version	1.0
   */
  bool getError()
  {
    return error;  
  }
      
  /**
   *  \brief Set target time in micro seconds
   *
   *  \param[in]  time    Target time in micro seconds
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  void setMicros( ulong time)
  {
    _time = time;  
    _last = micros();
  }
  
  /**
   *  \brief Set target time in milli seconds
   *
   *  \param[in]  time    Target time in milli seconds
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  void setMillis( ulong time)
  {
    setMicros(1000 * time);  
  }
  
  /**
   *  \brief Set target time in seconds
   *
   *  \param[in]  time    Target time in seconds
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  void setSeconds( ulong time)
  {
    setMicros(1000000 * time);  
  }
  
  /**
   *  \brief Set target frequency in Hz
   *
   *  \param[in]  frequency    Target frequency in Hz
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  void setHz( double frequency)
  {
    setMicros(1000000./frequency);  
  }
  
  /**
   *  \brief Get target time in micro seconds
   *
   *  \return Target time in micro seconds 
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  ulong getMicros()
  {
    return _time;  
  }
  
  /**
   *  \brief Get target time in milli seconds
   *
   *  \return Target time in milli seconds 
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  ulong getMillis()
  {
    return (ulong)ceil((double)getMicros() / 1000.);
  }
  
  /**
   *  \brief Get target time in seconds
   *
   *  \return Target time in seconds 
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  ulong getSeconds()
  {
    return (ulong)ceil((double)getMicros() / 1000000.);
  }
  
  /**
   *  \brief Get target frequency in Hz
   *
   *  \return Target frequency in Hz
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  double getHz()
  {
    return (ulong)(1./ceil((double)getMicros() / 1000000.));
  }
};

#endif // __THREAD_H__
