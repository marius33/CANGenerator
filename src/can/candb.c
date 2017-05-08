/*
* candb.c
*
* Created: 04/03/2017 19:11:05
*  Author: Marius
*/

#include "candb.h"
#include <asf.h>
#include <string.h>


CanMessage* candb_txMessages[CANDB_TXMESSAGES_LENGTH];

CanMessage EXAMPLE1;
CanSignal EXAMPLE1_OilTemperature;
CanSignal EXAMPLE1_EngineRevs;
CanSignal EXAMPLE1_DriverDoorState;

can_mb_conf_t rx_mailbox;
can_mb_conf_t tx_mailbox;
sn65hvd234_ctrl_t transceiver;

int32_t whitelist[32];
int32_t whitelist_length;

void (*rx_callback)(uint32_t, uint8_t, uint32_t, uint32_t, uint32_t);

void CAN0_Handler(void)
{
	
	uint32_t ul_status;
	ul_status = can_mailbox_get_status(CAN0, 0);
	// 	can_mb_conf_t disableMailbox;
	// 	disableMailbox.ul_mb_idx = 1;
	// 	disableMailbox.uc_obj_type = CAN_MB_DISABLE_MODE;
	// 	can_mailbox_init(CAN0, &disableMailbox);
	// 	printf("%08d\r\n", CAN0->CAN_MB[1].CAN_MMR);
	//
	if ((ul_status & CAN_MSR_MRDY) == CAN_MSR_MRDY) {
		rx_mailbox.ul_mb_idx = 0;
		rx_mailbox.ul_status = ul_status;
		can_mailbox_read(CAN0, &rx_mailbox);
		printf("RX %x %d %0*x%0*x  %05d\r\n", rx_mailbox.ul_fid, rx_mailbox.uc_length, (rx_mailbox.uc_length>4)? 8 : rx_mailbox.uc_length*2, swap32(rx_mailbox.ul_datal), (rx_mailbox.uc_length>4)? (rx_mailbox.uc_length-4)*2 : 0, swap32(rx_mailbox.ul_datah), ul_status&CAN_TIMESTP_MTIMESTAMP_Msk);
		//rx_callback(rx_mailbox.ul_id, rx_mailbox.uc_length, rx_mailbox.ul_datah, rx_mailbox.ul_datal, can_get_timestamp_value(CAN0));
	}

}

void candb_transceiver_init(void)
{
	pmc_enable_periph_clk(ID_CAN0);
	can_init(CAN0, sysclk_get_cpu_hz(), CAN_BPS_500K);

	sn65hvd234_set_en(&transceiver, PIO_PD28_IDX);
	sn65hvd234_enable(&transceiver);

	// 	rx_mailbox.ul_mb_idx = 0;
	// 	rx_mailbox.uc_obj_type = CAN_MB_RX_MODE;
	// 	rx_mailbox.uc_id_ver = 0;
	// 	rx_mailbox.ul_id_msk = 0;
	// 	rx_mailbox.ul_fid = 0;

	tx_mailbox.ul_mb_idx = 1;
	tx_mailbox.uc_obj_type = CAN_MB_TX_MODE;
	tx_mailbox.uc_id_ver = 0;
	tx_mailbox.uc_tx_prio = 0;

	/*	can_mailbox_init(CAN0, &rx_mailbox);*/
	can_mailbox_init(CAN0, &tx_mailbox);

	// 	can_enable_interrupt(CAN0, CAN_IER_MB0);
	// 	NVIC_SetPriority(CAN0_IRQn, 6);
	// 	NVIC_EnableIRQ(CAN0_IRQn);

}

void candb_init(void){

	candb_transceiver_init();

	EXAMPLE1.id=33;
	EXAMPLE1.length = 5;
	EXAMPLE1.period = 100;
	EXAMPLE1.counter = 0;
	EXAMPLE1_OilTemperature.length = 16;
	EXAMPLE1_OilTemperature.lsb = 0;
	EXAMPLE1_OilTemperature.parent= &EXAMPLE1;
	candb_set_signal(&EXAMPLE1_OilTemperature, 63); //23 degrees C
	
	EXAMPLE1_EngineRevs.length = 16;
	EXAMPLE1_EngineRevs.lsb = 16;
	EXAMPLE1_EngineRevs.parent= &EXAMPLE1;
	candb_set_signal(&CanSignal EXAMPLE1_EngineRevs, 0); //0 rpm
	
	EXAMPLE1_DriverDoorState.length = 1;
	EXAMPLE1_DriverDoorState.lsb = 32;
	EXAMPLE1_DriverDoorState.parent= &EXAMPLE1;
	candb_set_signal(&EXAMPLE1_DriverDoorState, 1); //door closed

	candb_txMessages[0] = &EXAMPLE1;

}

uint32_t candb_send(CanMessage* msg)
{

	tx_mailbox.ul_id = CAN_MID_MIDvA(msg->id);
	tx_mailbox.uc_length = msg->length;

	uint32_t shift = 8-msg->length;
 	Union64 data = msg->data;
	memmove(data.u8+shift, data.u8, msg->length);

	tx_mailbox.ul_datah = swap32(data.u32[0]);
	tx_mailbox.ul_datal = swap32(data.u32[1]);

	uint32_t retVal = CAN_MAILBOX_NOT_READY;
	if((retVal = can_mailbox_write(CAN0, &tx_mailbox)) == CAN_MAILBOX_TRANSFER_OK){
		can_mailbox_send_transfer_cmd(CAN0, &tx_mailbox);
	}

	return retVal;

}

void candb_set_whitelist(CanMessage* list[], int32_t length)
{
	whitelist_length = length;
	for(int i=0; i<length; i++)
	whitelist[i] = list[i]->id;
}

void candb_set_rx_callback(void (*rxCallback)(uint32_t, uint8_t, uint32_t, uint32_t, uint32_t))
{
	rx_callback = rxCallback;
}

void candb_set_signal(CanSignal* sgnl, uint64_t data){
	uint64_t mask = (1<<sgnl->length)-1;
	mask <<= sgnl->lsb;
	data <<= sgnl->lsb;
	data &= mask;
	sgnl->parent->data.u64 &= ~mask;
	sgnl->parent->data.u64 |= data;
}

uint64_t candb_get_signal(CanSignal* sgnl){
	uint64_t mask = (1<<sgnl->length)-1;
	uint64_t data = sgnl->parent->data.u64;
	data >>= sgnl->lsb;
	return (data & mask);
}
