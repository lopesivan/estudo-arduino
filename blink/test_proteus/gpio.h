#ifndef GPIO_H
#define GPIO_H

#include "address.h"
#include "configure.h"

/*
A pointer to an incomplete type (hides the implementation details).
*/
typedef struct gpio* gpio_ptr;

/*
Create a gpio and return a handle to it.
*/
gpio_ptr create_gpio (uint8_t id, const Address* address);

/*
Destroy the given gpio object.
All handles to it will be invalidated.
*/
/* void destroy_gpio(gpio_ptr gpio); */

int higt       (gpio_ptr gpio);
int input      (gpio_ptr gpio);
int output     (gpio_ptr gpio);
int low        (gpio_ptr gpio);
int pull_up    (gpio_ptr gpio);

bool is_pushed (gpio_ptr gpio);

#define PINX(X) \
    {\
        .ddr  = &DDR  ## X,\
        .port = &PORT ## X,\
        .pin  = &PIN  ## X,\
    }

#endif
