/*
 * send.h
 *
 *  Created on: Jul 24, 2020
 *      Author: sereshotes
 */

#ifndef COMPONENTS_RADIO_INC_RADIO_H_
#define COMPONENTS_RADIO_INC_RADIO_H_


#include "mavlink_help2.h"
#define RADIO_SEND_ID_ARRAY(F) \
	F(0, MAVLINK_MSG_ID_ELECTRICAL_STATE, 15) \
	F(1, MAVLINK_MSG_ID_OWN_TEMP, 20) \
	F(2, MAVLINK_MSG_ID_THERMAL_STATE, 15) \
	F(3, MAVLINK_MSG_ID_PLD_BME280_DATA, 15) \
	F(4, MAVLINK_MSG_ID_PLD_ME2O2_DATA, 15) \
	F(5, MAVLINK_MSG_ID_PLD_MICS_6814_DATA, 15) \
	F(6, MAVLINK_MSG_ID_SINS_isc, 15) \
	F(7, MAVLINK_MSG_ID_GPS_UBX_NAV_SOL, 5)

#define RADIO_SEND_BAN(F) \
	F(MAVLINK_MSG_ID_TIMESTAMP)

#define RADIO_DEFAULT_PERIOD 30
#define RADIO_SLEEP_DEFAULT 2000
/*
 * Инициализирует отправку сообщений по радио с заданными через
 * RADIO_SEND_ID_ARRAY, RADIO_SEND_BAN, RADIO_DEFAULT_PERIOD их частотами.
 */
void radio_send_init(void);

void radio_send_suspend(void);

void radio_send_resume(void);

void radio_send_set_sleep_delay(int64_t sleep_delay);

#endif /* COMPONENTS_RADIO_INC_RADIO_H_ */
