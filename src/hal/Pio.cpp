//Copyright 2011-2016 Tyler Gilbert; All Rights Reserved


#include "hal/Pio.hpp"
using namespace hal;

Pio::Pio(port_t port) : Periph(CORE_PERIPH_PIO, port){}



int Pio::set_mask(u32 mask) const {
	return ioctl(I_PIO_SETMASK, MCU_INT_CAST(mask));
}

int Pio::clear_mask(u32 mask) const {
	return ioctl(I_PIO_CLRMASK, MCU_INT_CAST(mask));
}

int Pio::assign(u32 value) const {
	pio_attr_t attr;
	attr.o_pinmask = value;
	attr.o_flags = FLAG_CLEAR;
	return ioctl(I_PIO_SETATTR, &attr);
}

u32 Pio::get_value() const {
	return ioctl(I_PIO_GET);
}

int Pio::set_value(unsigned int value) const {
	return ioctl(I_PIO_SET, value);
}

