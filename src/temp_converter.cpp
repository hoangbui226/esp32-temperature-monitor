#include "temp_converter.h"

void tempConverter(float *temp, char *unit, bool isFahrenheit) {
    if (isFahrenheit) {
        *temp = *temp * 9.0f / 5.0f + 32.0f;
        *unit = 'F';
    } else {
        *unit = 'C';
    }
}
