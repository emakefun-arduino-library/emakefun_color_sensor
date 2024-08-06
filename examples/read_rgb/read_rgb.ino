/**
 * @example read_rgb.ino
 */

#include "color_sensor.h"

#define INFINITE_LOOP_ON_FAILURE InfiniteLoopOnFailure(__FUNCTION__, __LINE__)

namespace {

emakefun::ColorSensor g_color_sensor;

void InfiniteLoopOnFailure(const char* function, const uint32_t line_number) {
  Serial.println(String(F("entering an infinite loop due to failure in ")) + function + F(", at line number: ") + line_number);
  while (true) {
    yield();
  }
}

}  // namespace

void setup() {
  Serial.begin(115200);
  Serial.println(F("setup"));

  Wire.begin();

  Serial.println(String(F("color sensor lib version: ")) + emakefun::ColorSensor::kVersionMajor + "." +
                 emakefun::ColorSensor::kVersionMinor + "." + emakefun::ColorSensor::kVersionPatch);

  const auto ret = g_color_sensor.Initialize();

  if (emakefun::ColorSensor::kOK == ret) {
    Serial.println(F("color sensor initialization successful"));
  } else {
    Serial.println(String(F("color sensor device initialization failed: ")) + ret);
    INFINITE_LOOP_ON_FAILURE;
  }

  Serial.println(F("setup successful"));
}

void loop() {
  const uint32_t r = g_color_sensor.R();
  const uint32_t g = g_color_sensor.G();
  const uint32_t b = g_color_sensor.B();
  Serial.println(String("r: ") + r + ", g: " + g + ", b: " + b);
  delay(50);
}
