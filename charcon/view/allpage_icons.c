/**
 * allpage_icons.c
 *
 * Created on: 11-Sep-2023
 * Author: PSI2COB
 */

#include "../../lvgl/lvgl.h"
#include "health_check.h"
#include "styles.h"
#include "launch_screen.h"
#include "progress_screen.h"
#include "colors.h"
#include "allpage_icons.h"
#include "admin_page.h"
#include "admin_access.h"
#include "../../sub.h"
#include "../controller/controller.h"
#include <time.h>
#include <stdio.h>
#include <unistd.h>
// #include "../../cJSON/cJSON.h"

// #define GSM_FILE_PATH "/home/position.json"

// Global variables
lv_obj_t *img_profile;
lv_obj_t *img_wifi;
lv_obj_t *img_network;
lv_obj_t *img_location;
lv_obj_t *header_rect;
lv_obj_t *back_rect;
lv_obj_t *header_text;
lv_obj_t *label_location;
lv_obj_t *label_guest;
lv_obj_t *label_time;
lv_obj_t *img_footer;
lv_obj_t *bg_object;
lv_obj_t *img_charger;
lv_obj_t *bosch_footer;
lv_obj_t *label_plug;
lv_obj_t *img_plug;
lv_obj_t *img_health;
lv_obj_t *img_settings;
lv_obj_t *img_cloud;
lv_obj_t *img_home;
lv_obj_t *img_log;
lv_obj_t *img_vsecc;
lv_obj_t *img_charcon;
lv_obj_t *img_signal1;
lv_obj_t *img_signal2;
lv_obj_t *img_signal3;
lv_obj_t *img_signal4;
lv_obj_t *img_signal5;
lv_obj_t *img_mc;
lv_obj_t *sw_text;
lv_obj_t *home_text;
lv_obj_t *log_text;
lv_obj_t *vsecc_text;
lv_obj_t *charcon_text;
lv_obj_t *mc_text;
lv_obj_t *guest_btn;
lv_obj_t *img_cloud_connection;
lv_obj_t *img_arrow;
lv_timer_t *login_task;
lv_timer_t *task_timer;

char admin_text[50];

const int CONST_AdminLoginPage = 7;
const int CONST_SoftwareUpdate = 8;
const int CONST_VseccSettings = 9;
const int CONST_CharconSettings = 10;
const int CONST_MasterControl = 11;
const int CONST_AdminLogsPage = 12;

int gsm_signal_value;

char datetime_str[30];
char *position_value;

void get_current_datetime(char *datetime_str) 
{
    time_t t;
    struct tm *tm_info;

    time(&t);
    tm_info = localtime(&t);

    // Add IST offset (+5 hours and +30 minutes)
    tm_info->tm_hour += 5;
    tm_info->tm_min += 30;

    // Handle overflow
    if (tm_info->tm_min >= 60) {
        tm_info->tm_hour += 1;
        tm_info->tm_min -= 60;
    }


    strftime(datetime_str, 30, "%H:%M", tm_info);
}

void allpage_status(lv_obj_t * obj)
{
    img_charger = lv_img_create(obj);
    lv_img_set_src(img_charger, &charger);
    lv_obj_align(img_charger, LV_ALIGN_CENTER, 0, 0);
    lv_obj_clear_flag(img_charger, LV_OBJ_FLAG_HIDDEN);

    img_profile = lv_img_create(obj);
    lv_img_set_src(img_profile, &icon_profile);
    lv_obj_align(img_profile, LV_ALIGN_TOP_RIGHT, -160, -10);

    img_wifi = lv_img_create(obj);
    lv_img_set_src(img_wifi, &icon_wifi);
    lv_img_set_zoom(img_wifi, 230);
    lv_obj_align(img_wifi, LV_ALIGN_TOP_RIGHT, -115, -14);

    img_signal1 = lv_img_create(obj);
    lv_img_set_src(img_signal1, &img_network_1);
    lv_obj_align(img_signal1, LV_ALIGN_TOP_RIGHT, -96, 11);

    img_signal2 = lv_img_create(obj);
    lv_img_set_src(img_signal2, &img_network_2);
    lv_obj_align(img_signal2, LV_ALIGN_TOP_RIGHT, -90, 8);

    img_signal3 = lv_img_create(obj);
    lv_img_set_src(img_signal3, &img_network_3);
    lv_obj_align(img_signal3, LV_ALIGN_TOP_RIGHT, -84, 6);

    img_signal4 = lv_img_create(obj);
    lv_img_set_src(img_signal4, &img_network_4);
    lv_obj_align(img_signal4, LV_ALIGN_TOP_RIGHT, -78, 3);

    img_signal5 = lv_img_create(obj);
    lv_img_set_src(img_signal5, &img_network_5);
    lv_obj_align(img_signal5, LV_ALIGN_TOP_RIGHT, -72, 0);

    label_time = lv_label_create(obj);
    lv_obj_align(label_time, LV_ALIGN_TOP_RIGHT, 0, -5);
    lv_obj_add_style(label_time, &style_text_time, LV_STATE_DEFAULT);

    img_footer = lv_img_create(obj);
    lv_img_set_src(img_footer, &bosch_logo);
    lv_obj_set_size(img_footer, 850, 200);
    lv_img_set_zoom(img_footer, 64);
    lv_obj_align(img_footer, LV_ALIGN_BOTTOM_RIGHT, 300, 50);

    img_location = lv_img_create(obj);
    lv_img_set_src(img_location, &icon_location);
    lv_obj_align(img_location, LV_ALIGN_TOP_LEFT, 10, -10);

    label_location = lv_label_create(obj);
    lv_obj_align(label_location, LV_ALIGN_TOP_LEFT, 50, -7);
    lv_obj_add_style(label_location, &style_text_time, LV_STATE_DEFAULT);

    header_rect = lv_obj_create(obj);
    lv_obj_set_size(header_rect, 550, 50);
    lv_obj_align(header_rect, LV_ALIGN_TOP_MID, 0, -30);
    lv_obj_set_scrollbar_mode(header_rect, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(header_rect, &style_header_bar, LV_STATE_DEFAULT);
    lv_obj_add_event_cb(header_rect, header_icons_display, LV_EVENT_CLICKED, NULL);

    header_text = lv_label_create(header_rect);
    lv_label_set_text(header_text, "............");
    lv_obj_align(header_text, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_style(header_text, &style_header_text, LV_STATE_DEFAULT);

    back_rect = lv_obj_create(obj);
    lv_obj_set_size(back_rect, 200, 30);
    lv_obj_add_flag(back_rect, LV_OBJ_FLAG_HIDDEN);
    lv_obj_align_to(back_rect, header_rect, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_obj_set_scrollbar_mode(back_rect, LV_SCROLLBAR_MODE_OFF);
    lv_obj_add_style(back_rect, &style_header_bar, LV_STATE_DEFAULT);

    img_arrow = lv_img_create(back_rect);
    lv_img_set_src(img_arrow, &arrow_up);
    lv_img_set_zoom(img_arrow, 200);
    lv_obj_align(img_arrow, LV_ALIGN_CENTER, 0, 0);


    if (strcmp(admin_text, "Admin") == 0)
    {
        label_guest = lv_label_create(obj);
        lv_label_set_text(label_guest, "Admin");
        lv_obj_add_flag(label_guest, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_align(label_guest, LV_ALIGN_TOP_RIGHT, -200, -5);
        lv_obj_add_style(label_guest, &style_text_time, LV_STATE_DEFAULT);
        lv_obj_add_event_cb(label_guest, scr_login, LV_EVENT_CLICKED, NULL);
    }
    else
    {
        label_guest = lv_label_create(obj);
        lv_label_set_text(label_guest, "Guest");
        lv_obj_add_flag(label_guest, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_align(label_guest, LV_ALIGN_TOP_RIGHT, -200, -5);
        lv_obj_add_style(label_guest, &style_text_time, LV_STATE_DEFAULT);
        lv_obj_add_event_cb(label_guest, scr_login, LV_EVENT_CLICKED, NULL);
    }

    //////////// All Page Icons //////////////////

    img_plug = lv_img_create(obj);
    lv_obj_align(img_plug, LV_ALIGN_BOTTOM_LEFT, 8, 12);

    label_plug = lv_label_create(obj);
    lv_obj_align(label_plug, LV_ALIGN_BOTTOM_LEFT, 90, -5);
    lv_obj_add_style(label_plug, &style_text_plug, LV_STATE_DEFAULT);

    img_health = lv_img_create(obj);
    lv_obj_align(img_health, LV_ALIGN_TOP_RIGHT, 5, 30);

    img_cloud_connection = lv_img_create(obj);
    lv_img_set_zoom(img_cloud_connection, 240);
    lv_obj_align(img_cloud_connection, LV_ALIGN_TOP_RIGHT, 8, 115);

    task_timer = lv_timer_create(health_check_status, 1000, NULL);
    lv_timer_ready(task_timer);
    lv_timer_handler();
    lv_timer_set_repeat_count(task_timer, -1);
}

void health_check_status(lv_obj_t * obj)
{
    ///////////// Fetch System Time /////////////
    get_current_datetime(datetime_str);
    lv_label_set_text(label_time, datetime_str);

    ///////////// Health Icon Status ///////////////
    if(HealthIcon == 1) {
        lv_img_set_src(img_health, &red_failure);
    } else if(HealthIcon == 2) {
        lv_img_set_src(img_health, &white_confg);
    } else if(HealthIcon == 3) {
        lv_img_set_src(img_health, &icon_good);
    }

    /////////// Charger Plug Status ///////////////

    if(PlugStatus == 0) {
        lv_img_set_src(img_plug, &icon_not_plug);
        lv_style_set_text_color(&style_text_plug, LV_COLOR_WHITE);
        lv_label_set_text(label_plug, "NOT PLUGGED");
    } else if(PlugStatus == 1) {
        lv_img_set_src(img_plug, &icon_connect);
        lv_style_set_text_color(&style_text_plug, LV_COLOR_GREEN);
        lv_label_set_text(label_plug, "CONNECTED");
    } else if(PlugStatus == 2) {
        lv_img_set_src(img_plug, &icon_charging);
        lv_style_set_text_color(&style_text_plug, lv_color_hex(0x98d4fc));
        lv_label_set_text(label_plug, "CHARGING");
    } else if(PlugStatus == 3) {
        lv_img_set_src(img_plug, &icon_connect_error);
        lv_style_set_text_color(&style_text_plug, lv_color_hex(0xFF0404));
        lv_label_set_text(label_plug, "CONNECTION ERROR");
    }

    /////////// Cloud Status /////////////////
    if(CloudConnection == 0) {
        lv_img_set_src(img_cloud_connection, &cloud_failure);
    } else if(CloudConnection == 1) {
        lv_img_set_src(img_cloud_connection, &cloud_connect);
    }


    // get_position();
}

// void get_position()
// {
//     FILE *file = fopen(GSM_FILE_PATH, "r");

//     if (file == NULL)
//     {

//         fprintf(stderr, "Error opening JSON file.\n");

//         return 1;
//     }

//     fseek(file, 0, SEEK_END);

//     long file_size = ftell(file);

//     fseek(file, 0, SEEK_SET);

//     char *json_data = (char *)malloc(file_size + 1);

//     fread(json_data, 1, file_size, file);

//     fclose(file);

//     // Parse JSON data using cJSON

//     cJSON *json = cJSON_Parse(json_data);

//     free(json_data);

//     // Check if parsing was successful

//     if (json == NULL)
//     {

//         const char *error_ptr = cJSON_GetErrorPtr();

//         if (error_ptr != NULL)
//         {

//             fprintf(stderr, "Error before: %s\n", error_ptr);
//         }

//         cJSON_Delete(json);

//         return 1;
//     }

//     // Extract values from JSON and store them in variables
//     cJSON *position = cJSON_GetObjectItemCaseSensitive(json, "position");
//     cJSON *latitude = cJSON_GetObjectItemCaseSensitive(json, "latitude");
//     cJSON *longitude = cJSON_GetObjectItemCaseSensitive(json, "longitude");
//     cJSON *gsmSignal = cJSON_GetObjectItemCaseSensitive(json, "GSMsignal");

//     if (cJSON_IsString(position) && cJSON_IsNumber(latitude) &&
//         cJSON_IsNumber(longitude) && cJSON_IsNumber(gsmSignal))
//     {

//         position_value = strdup(position->valuestring);

//         double latitude_value = latitude->valuedouble;

//         double longitude_value = longitude->valuedouble;

//         gsm_signal_value = gsmSignal->valueint;

//         ////////// GSM Signal ////////////////
//         get_gsm_signal();

//         /////////// Location ///////
//         lv_label_set_text(label_location, position_value);

//         // Print the extracted values

//         printf("Position: %s\n", position_value);
//         printf("Latitude: %f\n", latitude_value);
//         printf("Longitude: %f\n", longitude_value);
//         printf("GSM Signal: %d\n", gsm_signal_value);

//         // Remember to free the allocated memory

//         free(position_value);
//     }
//     else
//     {

//         fprintf(stderr, "Error: Invalid JSON format.\n");
//     }

//     // Clean up cJSON objects

//     cJSON_Delete(json);

//     return 0;
// }

// void get_gsm_signal()
// {
//     if (gsm_signal_value == 0)
//     {
//         lv_obj_set_style_img_recolor(img_signal1, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal1, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal2, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal2, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal3, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal3, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal4, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal4, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal5, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal5, LV_OPA_COVER, LV_STATE_DEFAULT);

//     }
//     else if (gsm_signal_value == 1)
//     {
//         lv_obj_set_style_img_recolor(img_signal1, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal1, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal2, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal2, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal3, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal3, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal4, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal4, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal5, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal5, LV_OPA_COVER, LV_STATE_DEFAULT);

//     }
//     else if (gsm_signal_value == 2)
//     {
//         lv_obj_set_style_img_recolor(img_signal1, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal1, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal2, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal2, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal3, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal3, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal4, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal4, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal5, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal5, LV_OPA_COVER, LV_STATE_DEFAULT);

//     }
//     else if (gsm_signal_value == 3)
//     {
//         lv_obj_set_style_img_recolor(img_signal1, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal1, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal2, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal2, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal3, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal3, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal4, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal4, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal5, lv_color_hex(0x3A3A3A), LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal5, LV_OPA_COVER, LV_STATE_DEFAULT);

//     }
//     else if (gsm_signal_value == 4)
//     {
//         lv_obj_set_style_img_recolor(img_signal1, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal1, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal2, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal2, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal3, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal3, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal4, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal4, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal5, LV_COLOR_WHITE, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal5, LV_OPA_COVER, LV_STATE_DEFAULT);

//     }
//     else
//     {
//         lv_obj_set_style_img_recolor(img_signal1, LV_COLOR_RED, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal1, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal2, LV_COLOR_RED, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal2, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal3, LV_COLOR_RED, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal3, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal4, LV_COLOR_RED, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal4, LV_OPA_COVER, LV_STATE_DEFAULT);

//         lv_obj_set_style_img_recolor(img_signal5, LV_COLOR_RED, LV_STATE_DEFAULT);
//         lv_obj_set_style_img_recolor_opa(img_signal5, LV_OPA_COVER, LV_STATE_DEFAULT);

//     }
// }

//////////////////////////// Header Icons ///////////////////////////////

void header_icons_display()
{
    lv_obj_set_size(header_rect, 550, 80);
    lv_obj_add_flag(header_text, LV_OBJ_FLAG_HIDDEN);
    lv_obj_remove_event_cb(header_rect, header_icons_display);

    lv_obj_clear_flag(back_rect, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_event_cb(back_rect, header_icons_close, LV_EVENT_CLICKED, NULL);

    //////// Settings icon
    img_settings = lv_img_create(header_rect);
    lv_img_set_src(img_settings, &settings_icon);
    lv_obj_align(img_settings, LV_ALIGN_TOP_LEFT, 0, -5);

    /////// Software update
    img_cloud = lv_img_create(header_rect);
    lv_img_set_src(img_cloud, &cloud_icon);
    lv_obj_align(img_cloud, LV_ALIGN_TOP_LEFT, 65, -5);
    lv_obj_add_flag(img_cloud, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(img_cloud, scr_sw_update, LV_EVENT_PRESSED, NULL);

    sw_text = lv_label_create(header_rect);
    lv_label_set_text(sw_text, "SW Update");
    lv_obj_align_to(sw_text, img_cloud, LV_ALIGN_OUT_BOTTOM_MID, 7, 1);
    lv_obj_add_style(sw_text, &style_icon_text, LV_STATE_DEFAULT);

    //////// Home icon
    img_home = lv_img_create(header_rect);
    lv_img_set_src(img_home, &home_icon);
    lv_obj_align(img_home, LV_ALIGN_TOP_RIGHT, -5, -5);
    lv_obj_add_flag(img_home, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(img_home, home_screen, LV_EVENT_PRESSED, NULL);

    home_text = lv_label_create(header_rect);
    lv_label_set_text(home_text, "Home");
    lv_obj_align_to(home_text, img_home, LV_ALIGN_OUT_BOTTOM_MID, 3, 2);
    lv_obj_add_style(home_text, &style_icon_text, LV_STATE_DEFAULT);

    //////// Log icon
    img_log = lv_img_create(header_rect);
    lv_img_set_src(img_log, &log_icon);
    lv_obj_align(img_log, LV_ALIGN_TOP_RIGHT, -75, -2);

    log_text = lv_label_create(header_rect);
    lv_label_set_text(log_text, "Logs");
    lv_obj_align_to(log_text, img_log, LV_ALIGN_OUT_BOTTOM_MID, 8, 2);
    lv_obj_set_style_text_color(log_text, lv_color_hex(0xB0ACAC), LV_STATE_DEFAULT);
    lv_obj_add_style(log_text, &style_icon_text, LV_STATE_DEFAULT);

    /////// Vsecc icon
    img_vsecc = lv_img_create(header_rect);
    lv_img_set_src(img_vsecc, &vsecc_icon);
    lv_obj_align(img_vsecc, LV_ALIGN_TOP_LEFT, 150, -4);

    vsecc_text = lv_label_create(header_rect);
    lv_label_set_text(vsecc_text, "v.SECC");
    lv_obj_align_to(vsecc_text, img_vsecc, LV_ALIGN_OUT_BOTTOM_MID, 5, 3);
    lv_obj_set_style_text_color(vsecc_text, lv_color_hex(0xB0ACAC), LV_STATE_DEFAULT);
    lv_obj_add_style(vsecc_text, &style_icon_text, LV_STATE_DEFAULT);

    /////// Charcon and MC icon
    img_charcon = lv_img_create(header_rect);
    lv_img_set_src(img_charcon, &charcon_icon);
    lv_obj_align(img_charcon, LV_ALIGN_CENTER, 0, -4);

    charcon_text = lv_label_create(header_rect);
    lv_label_set_text(charcon_text, "CharCon");
    lv_obj_align_to(charcon_text, img_charcon, LV_ALIGN_OUT_BOTTOM_MID, 3, 3);
    lv_obj_set_style_text_color(charcon_text, lv_color_hex(0xB0ACAC), LV_STATE_DEFAULT);
    lv_obj_add_style(charcon_text, &style_icon_text, LV_STATE_DEFAULT);

    img_mc = lv_img_create(header_rect);
    lv_img_set_src(img_mc, &charcon_icon);
    lv_obj_align(img_mc, LV_ALIGN_CENTER, 90, -4);

    mc_text = lv_label_create(header_rect);
    lv_label_set_text(mc_text, "Master Control");
    lv_obj_align_to(mc_text, img_mc, LV_ALIGN_OUT_BOTTOM_MID, 3, 3);
    lv_obj_set_style_text_color(mc_text, lv_color_hex(0xB0ACAC), LV_STATE_DEFAULT);
    lv_obj_add_style(mc_text, &style_icon_text, LV_STATE_DEFAULT);

    if(strcmp(admin_text, "Admin") == 0) {

        lv_obj_set_style_img_recolor(img_log, LV_COLOR_WHITE, LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor_opa(img_log, LV_OPA_COVER, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(log_text, LV_COLOR_WHITE, LV_STATE_DEFAULT);

        lv_obj_set_style_img_recolor(img_vsecc, LV_COLOR_WHITE, LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor_opa(img_vsecc, LV_OPA_COVER, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(vsecc_text, LV_COLOR_WHITE, LV_STATE_DEFAULT);

        lv_obj_set_style_img_recolor(img_charcon, LV_COLOR_WHITE, LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor_opa(img_charcon, LV_OPA_COVER, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(charcon_text, LV_COLOR_WHITE, LV_STATE_DEFAULT);

        lv_obj_set_style_img_recolor(img_mc, LV_COLOR_WHITE, LV_STATE_DEFAULT);
        lv_obj_set_style_img_recolor_opa(img_mc, LV_OPA_COVER, LV_STATE_DEFAULT);
        lv_obj_set_style_text_color(mc_text, LV_COLOR_WHITE, LV_STATE_DEFAULT);

        //////// Settings
        lv_obj_add_flag(img_vsecc, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(img_vsecc, scr_vsecc_set, LV_EVENT_PRESSED, NULL);

        lv_obj_add_flag(img_charcon, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(img_charcon, scr_charcon_set, LV_EVENT_PRESSED, NULL);

        lv_obj_add_flag(img_mc, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(img_mc, scr_mc_set, LV_EVENT_PRESSED, NULL);

        lv_obj_add_flag(img_log, LV_OBJ_FLAG_CLICKABLE);
        lv_obj_add_event_cb(img_log, scr_log_set, LV_EVENT_PRESSED, NULL);
    }
}

void header_icons_close()
{

    lv_obj_add_flag(back_rect, LV_OBJ_FLAG_HIDDEN);
    lv_obj_set_size(header_rect, 550, 50);
    lv_obj_clear_flag(header_text, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(img_cloud, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(img_settings, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(sw_text, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(img_home, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(home_text, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(img_log, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(log_text, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(vsecc_text, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(img_vsecc, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(charcon_text, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(img_charcon, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(mc_text, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(img_mc, LV_OBJ_FLAG_HIDDEN);

    lv_obj_remove_event_cb(back_rect, header_icons_close);
    lv_obj_add_event_cb(header_rect, header_icons_display, LV_EVENT_CLICKED, NULL);
}

/////////////////// Header Icons Admin Call backs /////////////////

void scr_login()
{
    header_page = CONST_AdminLoginPage;
}


void scr_sw_update()
{
    header_page = CONST_SoftwareUpdate;
}

void scr_vsecc_set()
{
    header_page = CONST_VseccSettings;
}

void scr_charcon_set()
{
    header_page = CONST_CharconSettings;
}

void scr_mc_set()
{
    header_page = CONST_MasterControl;
}

void scr_log_set()
{
    header_page = CONST_AdminLogsPage;
}