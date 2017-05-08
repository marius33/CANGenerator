/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="http://www.atmel.com/design-support/">Atmel Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#define DIGITAL_INPUT_MODE (IOPORT_MODE_PULLUP | IOPORT_MODE_DEBOUNCE)
#define ANALOG_INPUT_MODE

static inline void ioport_set_pin_peripheral_mode(int pin, int mode)
{
	ioport_set_pin_mode(pin, mode);
	ioport_disable_pin(pin);
}

static inline void ioport_set_pin_input_mode(int pin, int mode){
	ioport_set_pin_dir(pin, IOPORT_DIR_INPUT);
	ioport_set_pin_mode(pin, mode);
}

void board_init(void)
{
	ioport_init();

	//can tx
	ioport_set_pin_peripheral_mode(PIO_PB2_IDX, IOPORT_MODE_MUX_A);
	//can rx
	ioport_set_pin_peripheral_mode(PIO_PB3_IDX, IOPORT_MODE_MUX_A);
	//can enable
	ioport_set_pin_dir(PIO_PD28_IDX, IOPORT_DIR_OUTPUT);

	//white led
	ioport_set_pin_dir(PIO_PD29_IDX, IOPORT_DIR_OUTPUT);
	ioport_set_pin_level(PIO_PD29_IDX, false);

	/* USB enabled by default */

	
	//TOP-RIGHT header
	ioport_set_pin_input_mode(PIO_PD1_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD2_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA29_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD3_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD4_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD5_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD6_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD7_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA31_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA30_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA6_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD8_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA28_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD9_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PB5_IDX, DIGITAL_INPUT_MODE);

	//TOP-LEFT header
	ioport_set_pin_input_mode(PIO_PB14_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PB13_IDX, DIGITAL_INPUT_MODE);

	//RIGHT header
	//ioport_set_pin_input_mode(PIO_PD15_IDX, ANALOG_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PB4_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA0_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD10_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA1_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD11_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA2_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD12_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA3_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PB7_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD13_IDX, DIGITAL_INPUT_MODE);

	//erase pin
// 	ioport_enable_pin(PIO_PB12_IDX);
// 	ioport_set_pin_input_mode(PIO_PB12_IDX, DIGITAL_INPUT_MODE);

	ioport_set_pin_input_mode(PIO_PD14_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PB6_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD16_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA4_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA9_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD17_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA5_IDX, DIGITAL_INPUT_MODE);

	//BOTTOM header
	ioport_set_pin_input_mode(PIO_PA13_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA16_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA23_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD27_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA15_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA14_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD25_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD26_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD24_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA24_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD23_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA25_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD22_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA26_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD21_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA11_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD20_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA10_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD19_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA12_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD13_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PA27_IDX, DIGITAL_INPUT_MODE);

	//LEFT header
	ioport_set_pin_input_mode(PIO_PD0_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD31_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PB2_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PB3_IDX, DIGITAL_INPUT_MODE);
	ioport_set_pin_input_mode(PIO_PD30_IDX, DIGITAL_INPUT_MODE);

// 	ioport_disable_pin(PIO_PA19_IDX);
// 	ioport_set_pin_input_mode(PIO_PA18_IDX, IOPORT_MODE_PULLDOWN);

}
