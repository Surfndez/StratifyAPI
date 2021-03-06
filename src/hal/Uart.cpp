/*! \file */ // Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc; see LICENSE.md for rights.
//Copyright 2011-2020 Tyler Gilbert and Stratify Labs, Inc


#include "hal/Uart.hpp"
using namespace hal;

Uart::Uart(port_t port) : Periph(CORE_PERIPH_UART, port) {}

int Uart::get(char & c){
	return ioctl(IoRequest(I_UART_GET), IoArgument(&c));
}

int Uart::put(char c){
	return ioctl(IoRequest(I_UART_PUT), IoIntArgument(c));
}

int Uart::flush(){
	return ioctl(IoRequest(I_UART_FLUSH));
}


UartInfo Uart::get_info() const {
	uart_info_t info;
	if( get_info(info) < 0 ){
		return UartInfo();
	}
	return UartInfo(info);
}
