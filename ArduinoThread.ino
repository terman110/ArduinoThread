/** \file threadBlink
 *  \brief Small example to show how to use \ref thread.h .
 *
 *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
 *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
 *  \date	21.11.2013
 *  \version	1.0
 */ 
#include "thread.h"

/** \class _blink
 *  \brief Small class that intializes a pin and executes a blinking patter by set time
 *
 *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
 *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
 *  \date	21.11.2013
 *  \version	1.0
 */
class _blink : public thread
{
  int _pin;         //!< LED pin
  bool _state;      //!< Current LED state
  
  /**
   *  \brief Actual program code that will be called by parten class \ref thread in void loop().
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  void computation()
  {
    if( _state)
      digitalWrite(_pin, LOW);
    else
      digitalWrite(_pin, HIGH);
    _state = !_state;
  }  
public:
  /**
   *  \brief Constructor: Initializes pin and sets time
   *
   *  \author	Jan Beneke <beneke@ito.uni-stuttgart.de>
   *  \author	Universitaet Stuttgart - Institut fuer Technische Optik
   *  \date	21.11.2013
   *  \version	1.0
   */
  _blink( ulong time, int pin) : _state(LOW), _pin(pin)
  {
    this->setMicros( time);
    pinMode(_pin, OUTPUT);
  }
};

int _n = 4;                           //!< Number of connected pins
int _pins[] = {3,5,6,9};              //!< Pins
ulong _time[] = {1E6,5E5,8E5,2E5};    //!< Target times
_blink* t_blink[4];                   //!< Class object

//! Create class objects and initialize
void setup()
{
  for( int i = 0; i < 4; i++)
    t_blink[i] = new _blink(_time[i], _pins[i]);
}

//! Execute loop
void loop()
{
  for( int i = 0; i < 4; i++)
    t_blink[i]->execute();
}

