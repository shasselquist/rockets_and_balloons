
#include "Adafruit_MLX90393.h"
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"


#define MLX90393_CS 10
// Used for software SPI
#define LIS3DH_CLK 13
#define LIS3DH_MISO 12
#define LIS3DH_MOSI 11
// Used for hardware & software SPI
#define LIS3DH_CS 10
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define cardSelect 4


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_MLX90393 msensor = Adafruit_MLX90393();
Adafruit_LIS3DH lis = Adafruit_LIS3DH();
Adafruit_BME680 bme; // I2C
File logfile;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);

  /* Wait for serial on USB platforms. */
  while (!Serial) {
      delay(10);
  }
  msensor.begin_I2C();
  if (! lis.begin(0x18)) {   // change this to 0x19 for alternative i2c address
    Serial.println("Couldnt start");
    while (1) yield();
  }
  bme.begin();
  
  // Begin megnetometer set up
  // Set the gain here.
  // Options are found in the basic demo.
  msensor.setGain(MLX90393_GAIN_2_5X);

  //Set resolution.
  msensor.setResolution(MLX90393_X, MLX90393_RES_19);
  msensor.setResolution(MLX90393_Y, MLX90393_RES_19);
  msensor.setResolution(MLX90393_Z, MLX90393_RES_16);

  // Set oversampling
  msensor.setOversampling(MLX90393_OSR_2);

  // Set digital filtering
  msensor.setFilter(MLX90393_FILTER_6);

  //Now lets do accelerometer setup:
  lis.setRange(LIS3DH_RANGE_16_G);
  lis.setDataRate(LIS3DH_DATARATE_50_HZ);

  //Finally, BME sensor setup.
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms

  //And now the SD card setup:
  if (!SD.begin(cardSelect)) {
    Serial.println("Card init. failed!");
    error(2);
  }
  char filename[15];
  strcpy(filename, "/ANALOG00.TXT");
  for (uint8_t i = 0; i < 100; i++) {
    filename[7] = '0' + i/10;
    filename[8] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  logfile = SD.open(filename, FILE_WRITE);

}

void loop() {
  // put your main code here, to run repeatedly:
  //magentometer variables
  float mx, my, mz;
  msensor.readData(&mx, &my, &mz);
  Serial.print(mx, 8); Serial.print(",");
  Serial.print(my, 8); Serial.print(",");
  Serial.print(mz, 8); Serial.print(",");
  lis.read();
  Serial.print(lis.x); Serial.print(",");
  Serial.print(lis.y); Serial.print(",");
  Serial.print(lis.z); Serial.print(",");
  bme.performReading();
  Serial.print(bme.temperature); Serial.print(",");
  Serial.print(bme.pressure); Serial.print(",");
  Serial.print(bme.humidity); Serial.print(",");
  Serial.print(bme.gas_resistance); Serial.print(",");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA)); Serial.println(",");
  delay(100);

}
