/*
 * candb.h
 *
 * Created: 04/03/2017 19:11:05
 *  Author: Marius
 */ 

#ifndef CANDB_H_
#define CANDB_H_

#include <stdint.h>
#include <compiler.h>

#define CANDB_TXMESSAGES_LENGTH 1

typedef struct {
	uint32_t id;
	uint8_t length;
	Union64 data;
	int32_t period;
	int32_t counter;
} CanMessage;

typedef struct {
	uint8_t length;
	uint8_t lsb;
	CanMessage* parent;
} CanSignal;

extern CanMessage* candb_txMessages[CANDB_TXMESSAGES_LENGTH];

void candb_init(void);
void candb_set_whitelist(CanMessage* list[], int32_t length);
uint32_t candb_send(CanMessage* msg);

//id, length, datah, datal, timestamp
void candb_set_rx_notify(void (*rxCallback)(uint32_t, uint8_t, uint32_t, uint32_t, uint32_t));

void candb_set_signal(CanSignal* sgnl, uint64_t value);
uint64_t candb_get_signal(CanSignal* sgnl);

extern CanMessage EXAMPLE1;
extern CanSignal EXAMPLE1_OilTemperature;
extern CanSignal EXAMPLE1_EngineRevs;
extern CanSignal EXAMPLE1_DriverDoorState;



#endif