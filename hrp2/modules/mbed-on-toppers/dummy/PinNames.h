#pragma once

typedef int PinName;
typedef int PinMode;
typedef int PinDirection;
typedef int gpio_t;

#define     __IO    volatile 

enum {
    NC,
    PIN_INPUT,
    PIN_OUTPUT,
};
