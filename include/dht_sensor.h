#pragma once
#include <DHT.h>

extern DHT dht;
bool dht_read(float* temp, float* humid);
