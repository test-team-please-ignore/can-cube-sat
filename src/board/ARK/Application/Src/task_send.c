/*
 * task_send.c
 *
 *  Created on: Apr 25, 2020
 *      Author: sereshotes
 */

#include "main.h"

#include "mavlink_help2.h"
#include "its-time.h"
#include "uplink.h"
#include "task_ds.h"
#include "task_ina.h"
#include "stdlib.h"
#include "inttypes.h"



static int tsend_therm_period = 1000 / TDS_TEMP_MAX_COUNT;
static int tsend_elect_period = 2000 / (TINA_COUNT + 1);

static int ds_updated;
static int ina_updated;


typedef enum {
    STATE_WAIT,
    STATE_SENDING,
} send_state_t;

static send_state_t estate;
static send_state_t tstate;

static its_time_t ds_read_time;
static its_time_t ina_read_time;


void ds_callback(void) {
    ds_updated = 1;
    its_gettimeofday(&ds_read_time);
}
void ina_callback(void) {
    ina_updated = 1;
    its_gettimeofday(&ina_read_time);
}

void task_send_init(void *arg) {
    tds18b20_add_callback(ds_callback);
    tina219_add_ina_callback(ina_callback);
}


void eupdate() {
    static float current[TINA_COUNT];
    static float voltage[TINA_COUNT];
    static uint32_t prev = 0;
    static its_time_t tim;
    uint32_t now = HAL_GetTick();
    if (estate == STATE_WAIT && now - prev >= tsend_elect_period) {
        printf("INFO: send ina\n");
        prev = now;

        tina_value_t *tv;
        int *is_valid;
        int count = tina219_get_value(&tv, &is_valid);
        for (int i = 0; i < count; i++) {
            if (is_valid[i]) {
                current[i] = tv[i].current;
                voltage[i] = tv[i].voltage;
            } else {
                current[i] = NAN;
                voltage[i] = NAN;
            }
        }
        estate = STATE_SENDING;
        ina_updated = 0;
        tim = ina_read_time;

    }
    if (estate == STATE_SENDING) {
        static int is_gened = 0;
        static int ina_index = 0;
        static mavlink_message_t msg;
        if (!is_gened) {
            mavlink_electrical_state_t mest = {0};
            mest.time_s = tim.sec;
            mest.time_us = tim.usec * 1000;

            mest.current = current[ina_index];
            mest.voltage = voltage[ina_index];

            mavlink_msg_electrical_state_encode(mavlink_system, ina_index, &msg, &mest);
        }
        if (uplink_packet(&msg) > 0) {
            ina_index++;
            is_gened = 0;
            if (ina_index >= TINA_COUNT) {
                estate = STATE_WAIT;
                ina_index = 0;
            }

        }
    }
}

void tupdate() {
    static float temp[TDS_TEMP_MAX_COUNT];
    static its_time_t tim;
    static uint32_t prev = 0;
    static int ds_count = 0;
    if (ds_count != 0) {
        tsend_therm_period = 1000 / ds_count;
    }
    if (tstate == STATE_WAIT && ds_updated && HAL_GetTick() - prev >= tsend_therm_period) {
        printf("INFO: send ds\n");

        its_time_t timm;
        its_gettimeofday(&timm);
        prev = HAL_GetTick();
        tstate = STATE_SENDING;
        ds_updated = 0;

        float *arr;
        int *is_valid;
        ds_count = tds18b20_get_value(&arr, &is_valid);
        for (int i = 0; i < ds_count; i++) {
            if (is_valid[i]) {
                temp[i] = arr[i];
            } else {
                temp[i] = NAN;
            }
        }

        tim = ds_read_time;
    }
    if (tstate == STATE_SENDING) {
        static int is_gened = 0;
        static mavlink_message_t msg;
        static int ds_index = 0;
        if (!is_gened) {
            mavlink_thermal_state_t mtst = {0};
            mtst.time_s = tim.sec;
            mtst.time_us = tim.usec * 1000;
            mtst.temperature = temp[ds_index];

            mavlink_msg_thermal_state_encode(mavlink_system, ds_index, &msg, &mtst);
        }
        if (uplink_packet(&msg) > 0) {
            ds_index++;
            is_gened = 0;
            if (ds_index >= ds_count) {
                tstate = STATE_WAIT;
                ds_index = 0;
            }

        }
    }
}


void task_send_update(void *arg) {
    static uint32_t prev = 0;
    if (HAL_GetTick() - prev >= 1000){
        prev = HAL_GetTick();
        static its_time_t tim;
        its_gettimeofday(&tim);
        printf("TIME: %"PRIu32".%03"PRIu32"\n", (uint32_t)tim.sec, (uint32_t)tim.usec);
    }
    eupdate();
    tupdate();

}

