#ifndef  APP_H
#define  APP_H
#include "main.h"

#define TIME  1000
#define MINUTE  60

extern unsigned long tmr;
extern unsigned int  rpm;

extern unsigned long ir_count; 
extern bool ir_detect_flag;

void display_digital_with_bar(int rpm);
void display_compact_rpm(int rpm);
void display_minimal_rpm(int rpm);
void app_run(void);
#endif // APP_H