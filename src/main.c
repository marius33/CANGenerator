
#include <asf.h>
#include <stdbool.h>
#include "can/candb.h"

inline void set_led(bool v){
	ioport_set_pin_level(PIO_PD29_IDX, v);
}

inline bool get_led(void){
	return ioport_get_pin_level(PIO_PD29_IDX);
}

void timer_init(void){

	sysclk_enable_peripheral_clock(ID_TC0);
	tc_init(TC0, 0, TC_CMR_TCCLKS_TIMER_CLOCK4);
	tc_start(TC0, 0);

}

void adc_init(void){
	struct afec_config afec_cfg;
	afec_enable(AFEC0);
	afec_get_config_defaults(&afec_cfg);
	afec_init(AFEC0, &afec_cfg);
	afec_channel_set_analog_offset(AFEC0, 0, 2048);
	afec_channel_set_analog_offset(AFEC0, 1, 2048);
	afec_channel_set_analog_offset(AFEC0, 2, 2048);
	afec_channel_set_analog_offset(AFEC0, 3, 2048);

	afec_set_trigger(AFEC0, AFEC_TRIG_SW);
	afec_channel_enable(AFEC0, AFEC_CHANNEL_0);
	afec_channel_enable(AFEC0, AFEC_CHANNEL_1);
	afec_channel_enable(AFEC0, AFEC_CHANNEL_2);
	afec_channel_enable(AFEC0, AFEC_CHANNEL_3);
}

static uint32_t tc0_cv0 = 0;
uint8_t tick(uint32_t period){

	uint32_t tc0_cv = tc_read_cv(TC0, 0);
	uint32_t dt = tc0_cv - tc0_cv0;
	uint8_t ticks = dt/period;

	if(ticks){
		uint32_t offset = dt%period;
		tc0_cv0 = tc0_cv-offset;
	}

	return ticks;

}

static inline void setCarState(uint8_t state, bool hasKey){

	switch(state){
		//BATTERY
		case 0: {

		}
		break;
		//ACC
		case 1: {
			if(hasKey){

			}
			else{

			}

		}
		break;
		//IGN with engine off
		case 2: {

		}
		break;
		//IGN with engine on
		case 3: {

		}
		break;
	}

}

static inline void setCrashStatus(bool crash){

	if(crash){
		if(/**/.counter == -1)
		/**/.counter = 0;

	}
	else{
		/**/.counter = -1;

	}
	
}

static inline void setHoodState(bool open){
	if(open)

	else

}

static inline void setTailGateState(bool open){
	if(open)

	else

}

static inline void setDriverDoorState(bool open){
	if(open)

	else

}

static inline void setPassengerDoorState(bool open){
	if(open)

	else

}

static inline void setRearLeftDoorState(bool open){
	if(open)

	else

}

static inline void setRearRightDoorState(bool open){
	if(open)

	else

}

static inline void setBrakeState(bool pedalDown){
	if(pedalDown){

	}
	else{

	}
}

static inline void setIndicatorLightsState(bool left, bool right, bool hazards){

	//indicator position <|>
	if(left)

	else if(right)

	else


	//indicator lights
	if(hazards)

	else if(left)

	else if(right)

	else

	
}

static inline void setHighBeamState(bool on){
	if(on){

	}
	else{

	}
}

static inline void setLowBeamState(bool on){
	if(on){

	}
	else{

	}
}

static inline void setFrontFogLightsState(bool on){
	if(on){

	}
	else{

	}
}

static inline void setGearLeverState(uint32_t contacts, bool isAutomatic){

	switch(contacts){
		case 0b1110: {
			
		}
		break;
		case 0b1101: {

		}
		break;
		case 0b1011: {

		}
		break;
		case 0b0111: {

		}
		break;
	}
}

static inline void setVehicleSpeed(uint32_t adcValue){

}

static inline void setAcceleratorPedalPosition(uint32_t adcValue){
	
}

static inline void setSteeringWheelAngle(uint32_t adcValue){

}

static inline void setRheostat(uint32_t adcValue){

}


int main (void)
{

	wdt_disable(WDT);
	sysclk_init();
	irq_initialize_vectors();
	cpu_irq_enable();
	board_init();
	adc_init();
	timer_init();
	//stdio_usb_init();
	candb_init();

	uint8_t ticks;
	uint32_t ledCounter = 0;
	uint32_t taskCounter = 0;
	bool taskGoAhead = false;

	afec_start_software_conversion(AFEC0);

	while(true)
	{

		if(ticks = tick(750)){

			taskGoAhead = true;
			
			for(int i=0; i<CANDB_TXMESSAGES_LENGTH; i++){
				if(candb_txMessages[i]->counter >= ticks)
				candb_txMessages[i]->counter -= ticks;
				else if(candb_txMessages[i]->counter > 0)
				candb_txMessages[i]->counter = 0;
			}
			
			if(ledCounter>ticks)
			ledCounter -= ticks;
			else
			ledCounter = 0;

			if(ledCounter<250)
			set_led(false);
			else
			set_led(true);

		}


		for(int i=0; i<CANDB_TXMESSAGES_LENGTH; i++){
			if(candb_txMessages[i]->counter==0){
				if(candb_send(candb_txMessages[i]) == CAN_MAILBOX_TRANSFER_OK){
					candb_txMessages[i]->counter = candb_txMessages[i]->period;

					if(taskGoAhead){
						switch(taskCounter){

							case 0:
							{
								setGearLeverState(ioport_get_port_level(IOPORT_PIOA, 0xF), ioport_get_pin_level(PIO_PD15_IDX));
							}
							break;
							case 1:
							{
								setCarState((ioport_get_port_level(IOPORT_PIOA, 0x3C0)>>10), ioport_get_pin_level(PIO_PD14_IDX));
							}
							break;
							case 2:
							{
								setCrashStatus(ioport_get_pin_level(PIO_PD3_IDX));
							}
							break;
							case 3:
							{
								setTailGateState(ioport_get_pin_level(PIO_PA31_IDX));
							}
							break;
							case 4:
							{
								setIndicatorLightsState(ioport_get_pin_level(PIO_PD5_IDX),
								ioport_get_pin_level(PIO_PD6_IDX),
								ioport_get_pin_level(PIO_PD7_IDX));
							}
							break;
							case 5:
							{
								setHoodState(ioport_get_pin_level(PIO_PA30_IDX));
							}
							break;
							case 6:
							{
								setDriverDoorState(ioport_get_pin_level(PIO_PA6_IDX));
							}
							break;
							case 7:
							{
								setPassengerDoorState(ioport_get_pin_level(PIO_PD8_IDX));
							}
							break;
							case 8:
							{
								setRearLeftDoorState(ioport_get_pin_level(PIO_PA28_IDX));
							}
							break;
							case 9:
							{
								setRearRightDoorState(ioport_get_pin_level(PIO_PD9_IDX));
							}
							break;
							case 10:
							{
								setHighBeamState(ioport_get_pin_level(PIO_PA9_IDX));
							}
							break;
							case 11:
							{
								setLowBeamState(ioport_get_pin_level(PIO_PD17_IDX));
							}
							break;
							case 12:
							{
								setFrontFogLightsState(ioport_get_pin_level(PIO_PA4_IDX));
							}
							break;
							case 13:
							{
								if(afec_get_interrupt_status(AFEC0) & (1 << AFEC_CHANNEL_0)){
									setVehicleSpeed(afec_channel_get_value(AFEC0, AFEC_CHANNEL_0));
								}
							}
							break;
							case 14:
							{
								if(afec_get_interrupt_status(AFEC0) & (1 << AFEC_CHANNEL_1)){
									setAcceleratorPedalPosition(afec_channel_get_value(AFEC0, AFEC_CHANNEL_1));
								}
							}
							break;
							case 15:
							{
								if(afec_get_interrupt_status(AFEC0) & (1 << AFEC_CHANNEL_2)){
									setSteeringWheelAngle(afec_channel_get_value(AFEC0, AFEC_CHANNEL_2));
								}
							}
							break;
							case 16:
							{
								if(afec_get_interrupt_status(AFEC0) & (1 << AFEC_CHANNEL_3)){
									setRheostat(afec_channel_get_value(AFEC0, AFEC_CHANNEL_3));
									afec_start_software_conversion(AFEC0);
								}
							}
							break;
						}

						if(taskCounter == 16)
						taskCounter = 0;
						else
						taskCounter++;

						taskGoAhead = false;
					}

					if(ledCounter==0){
						set_led(true);
						ledCounter = 500;
					}

					break;
				}
			}
		}
	}

}