/*! \file */ //Copyright 2011-2016 Tyler Gilbert; All Rights Reserved


#ifndef PWM_HPP_
#define PWM_HPP_

#include <sos/dev/pwm.h>
#include "PinAssignment.hpp"
#include "Periph.hpp"

namespace hal {

/*! \brief PWM Pin Assignment
 * \details This class allows simple manipulation of the pwm_pin_assignment_t.
 */
class PwmPinAssignment : public PinAssignment<pwm_pin_assignment_t>{};

/*! \brief PWM Class
 * \details This class implements PWM outputs.
 *
 * Here is an example of how to use the Pwm class
 *
 * \code
 * #include <sapi/hal.hpp>
 *
 * Pwm pwm(1); //use PWM port 1
 * PwmPinAssignment pin_assignment;
 * pin_assignment->channel[0] = mcu_pin(1,20); //Use Pin 1.20
 * pwm.init(Pwm::FLAG_SET_TIMER | Pwm::FLAG_IS_ENABLED, 24000000, 1000, pin_assignment);
 * pwm.set_channel(2, 500);
 *
 * \endcode
 *
 *
 */
class Pwm : public Periph<pwm_info_t, pwm_attr_t, 'p'> {
public:
	Pwm(port_t port);

	enum {
		FLAG_SET_TIMER /*! See \ref PWM_FLAG_SET_TIMER */ = PWM_FLAG_SET_TIMER,
		FLAG_IS_ACTIVE_HIGH /*! See \ref PWM_FLAG_IS_ACTIVE_HIGH */ = PWM_FLAG_IS_ACTIVE_HIGH,
		FLAG_IS_ACTIVE_LOW /*! See \ref PWM_FLAG_IS_ACTIVE_LOW */ = PWM_FLAG_IS_ACTIVE_LOW,
		FLAG_SET_CHANNELS /*! See \ref PWM_FLAG_SET_CHANNELS */ = PWM_FLAG_SET_CHANNELS,
		FLAG_CLEAR_CHANNELS /*! See \ref PWM_FLAG_CLEAR_CHANNELS */ = PWM_FLAG_CLEAR_CHANNELS,
		FLAG_IS_ENABLED /*! See \ref PWM_FLAG_IS_ENABLED */ = PWM_FLAG_IS_ENABLED
	};

	int set_channel(u32 loc, u32 value) const {
		return Periph::set_channel(loc, value, I_PWM_SETCHANNEL);
	}

	int set_channel(const mcu_channel_t & channel) const {
		return Periph::set_channel(channel, I_PWM_SETCHANNEL);
	}

	int enable() const {
		return ioctl(I_PWM_ENABLE);
	}

	int disable() const {
		return ioctl(I_PWM_DISABLE);
	}

	int set_attr(u32 o_flags, u32 freq, u32 period, const pwm_pin_assignment_t * pin_assignment = 0) const {
		pwm_attr_t attr;
		attr.o_flags = o_flags;
		if( pin_assignment != 0 ){
			memcpy(&attr.pin_assignment, pin_assignment, sizeof(pwm_pin_assignment_t));
		} else {
			memset(&attr.pin_assignment, 0xff, sizeof(pwm_pin_assignment_t));
		}
		attr.freq = freq;
		attr.period = period;
		return set_attr(attr);
	}

	int set_channels(const pwm_pin_assignment_t * pin_assignment){
		return set_attr(FLAG_SET_CHANNELS, 0, 0, pin_assignment);
	}

	int init(u32 o_flags, u32 freq, u32 period, const pwm_pin_assignment_t * pin_assignment = 0){

		if( open() < 0 ){
			return -1;
		}

		return set_attr(o_flags, freq, period, pin_assignment);
	}

	using Periph::init;
	using Periph::set_attr;

#ifdef __MCU_ONLY__
	//using Pblock::write;
	//int write(const void * buf, int nbyte);
	int close();
#endif


private:

};

};

#endif /* PWM_HPP_ */
