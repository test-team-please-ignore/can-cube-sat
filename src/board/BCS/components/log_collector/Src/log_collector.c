/*
 * log_collector.c
 *
 *  Created on: Aug 19, 2020
 *      Author: sereshotes
 */

#include "log_collector.h"

#include "mavlink_help2.h"
#include "router.h"
#include "init_helper.h"
#include "shift_reg.h"

static log_collector_t _coll;

extern shift_reg_handler_t hsr;

static void log_collector_task(void *arg) {
	log_collector_t *coll = (log_collector_t *)arg;
	TickType_t xLastWakeTime;

	xLastWakeTime = xTaskGetTickCount();
	while (1) {
		mavlink_bcu_stats_t mbs = {0};
		mavlink_message_t msg = {0};
		struct timeval tv = {0};

		xSemaphoreTake(coll->mutex, portMAX_DELAY);
		gettimeofday(&tv, 0);
		mbs.time_s = tv.tv_sec;
		mbs.time_us = tv.tv_usec;

		mbs.sd_elapsed_time_from_msg 			= coll->log_data[LOG_COMP_ID_SD].ellapsed_time;
		mbs.sd_error_count 						= coll->log_data[LOG_COMP_ID_SD].error_count;
		mbs.sd_last_error 						= coll->log_data[LOG_COMP_ID_SD].last_error;
		mbs.sd_last_state 						= coll->log_data[LOG_COMP_ID_SD].last_state;

		mbs.sins_comm_elapsed_time_from_msg 	= coll->log_data[LOG_COMP_ID_SINC_COMM].ellapsed_time;
		mbs.sins_comm_error_count 				= coll->log_data[LOG_COMP_ID_SINC_COMM].error_count;
		mbs.sins_comm_last_error 				= coll->log_data[LOG_COMP_ID_SINC_COMM].last_error;
		mbs.sins_comm_last_state 				= coll->log_data[LOG_COMP_ID_SINC_COMM].last_state;

		if (hsr.mutex) {
			xSemaphoreTake(hsr.mutex, 0);
			mbs.shift_reg_last_state = *((uint32_t *)hsr.byte_arr);
			xSemaphoreGive(hsr.mutex);
		}
		mbs.shift_reg_elapsed_time_from_msg 	= coll->log_data[LOG_COMP_ID_SHIFT_REG].ellapsed_time;
		mbs.shift_reg_error_count 				= coll->log_data[LOG_COMP_ID_SHIFT_REG].error_count;
		mbs.shift_reg_last_error 				= coll->log_data[LOG_COMP_ID_SHIFT_REG].last_error;

		xSemaphoreGive(coll->mutex);
		mavlink_msg_bcu_stats_encode(mavlink_system, COMP_ANY_0, &msg, &mbs);
		its_rt_sender_ctx_t ctx = {0};
		ctx.from_isr = 0;
		its_rt_route(&ctx, &msg, 0);
		vTaskDelayUntil(&xLastWakeTime, LOG_COLLECTOR_SEND_PERIOD / portTICK_PERIOD_MS);
	}
}

void log_collector_init(log_collector_t * coll) {
	if (!coll) {
		coll = &_coll;
	}
	memset(coll, 0, sizeof(*coll));
	coll->mutex = xSemaphoreCreateMutex();
	xTaskCreate(log_collector_task, "Log collector", configMINIMAL_STACK_SIZE + 2500, coll, 2, 0);
}

void log_collector_add_to(log_collector_t *hlc, log_comp_id_t id, const log_data_t *data) {
	xSemaphoreTake(hlc->mutex, portMAX_DELAY);
	hlc->log_data[id] = *data;
	xSemaphoreGive(hlc->mutex);
}

void log_collector_add(log_comp_id_t id, const log_data_t *data) {
	xSemaphoreTake(_coll.mutex, portMAX_DELAY);
	_coll.log_data[id] = *data;
	xSemaphoreGive(_coll.mutex);
}
void log_collector_log_task(log_data_t *data) {
	while (1) {
		if (data && data->last_state == LOG_STATE_OFF) {
			vTaskDelete(0);
		}
		log_collector_add(LOG_COMP_ID_SHIFT_REG, data);
		vTaskDelay(LOG_COLLECTOR_ADD_PERIOD_COMMON / portTICK_PERIOD_MS);
	}
}
