/**
 * progress_screen.h
 *
 * Created on: 01-Sep-2023
 * Author: PSI2COB
 */

#ifndef _PROGRESS_SCREEN_H_
#define _PROGRESS_SCREEN_H_

/* System Includes*/
#include <stdio.h>
#include <time.h>
#include "../../lvgl/lvgl.h"

LV_IMG_DECLARE(icon_money)
LV_IMG_DECLARE(icon_power)
LV_IMG_DECLARE(img_cost)
LV_IMG_DECLARE(img_tot)

extern int PlugStatus1;
extern int PlugStatus2;
extern int PlugStatus3;

extern int HealthIcon1;
extern int HealthIcon2;
extern int HealthIcon3;

extern char cost_on_grid[10];

/*Project Includes*/
extern void create_progress_screen();
void create_progress_chart();
void charge_timer_start();
static void draw_event_cb(lv_event_t *e);
extern void pub_stop(lv_event_t *event);
static void add_data(lv_timer_t * timer);
static int32_t round_fixed_point(int32_t n, int8_t shift);
static void slider_x_event_cb(lv_event_t * e);
extern void charging_progress_state();
void updateCircularBuffer(int newValue);

#endif