#include "dht_sensor.h"
#include <math.h>


bool dht_read(float* temp, float* humid) {
  *humid = dht.readHumidity();
  *temp  = dht.readTemperature();

  return !(isnan(*humid) || isnan(*temp));
}
