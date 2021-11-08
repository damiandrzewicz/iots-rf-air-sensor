#include "RFAirSensorNode.h"
#include <Wire.h>

void RFAirSensorNode::setup()
{
    setPeriodicalWakeupMode(60000U);
    RFTemplateNode::setup();
    initBME280();
}

void RFAirSensorNode::work()
{
    RFTemplateNode::work();
    readBME280();
}

void RFAirSensorNode::initBME280()
{
    PRINTLND1F("Increasing SPI speed...");
    Wire.begin();
    Wire.setClock(400000); //Increase to fast I2C speed!

    PRINTLND1F("Starting BME280... Addr:"/* [0x%02X]", 0x76*/);

    bme280_.setI2CAddress(0x76);
    bme280_.beginI2C();
    

    PRINTLND1F("Setting BME280 in sleep mode...");
    bme280_.setMode(MODE_SLEEP);
}

void RFAirSensorNode::readBME280()
{
    bme280_.setMode(MODE_FORCED); //Wake up sensor and take reading

    while(bme280_.isMeasuring() == false) ; //Wait for sensor to start measurment
    while(bme280_.isMeasuring() == true) ; //Hang out while sensor completes the reading   

    appendSendBufferFloat(bme280_.readTempC());
    appendSendBufferFloat(bme280_.readFloatHumidity());
    appendSendBufferFloat(bme280_.readFloatPressure() / 100.0F, true);

    bme280_.setMode(MODE_SLEEP);
}