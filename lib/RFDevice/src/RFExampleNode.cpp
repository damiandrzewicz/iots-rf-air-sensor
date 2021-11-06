#include "RFExampleNode.h"
#include <Wire.h>

void RFExampleNode::initRadio()
{
    auto nodeID = buildNodeUniqueIdByte();
    auto networkID = 101;

    if(getRadio().initialize(RF69_868MHZ, nodeID, networkID))
    {
        PRINTD1F("initialized radio... nodeId: [");
        PRINTD2(nodeID, DEC);
        PRINTD1F("], networkId:[");
        PRINTD2(networkID, DEC);
        PRINTLND1F("]");

        getRadio().setHighPower(); //must include this only for RFM69HW/HCW!
        getRadio().encrypt("sampleEncryptKey");
        getRadio().setPowerLevel(0);
        getRadio().setFrequency(869000000);
        getRadio().sleep();
        PRINTLND1F("radio started in sleep mode!");
    }
    else{
        PRINTLND1F("radio initialize failed!");
    }
}


void RFExampleNode::setup()
{
    RFTemplateNode::setup();

    PRINTLND1F("Increasing SPI speed...");
    Wire.begin();
    Wire.setClock(400000); //Increase to fast I2C speed!

    PRINTLND1F("Starting BME280... Addr:"/* [0x%02X]", 0x76*/);

    _bme280.setI2CAddress(0x76);
    _bme280.beginI2C();
    

    PRINTLND1F("Setting BME280 in sleep mode...");
    _bme280.setMode(MODE_SLEEP);
}

void RFExampleNode::work()
{
    RFTemplateNode::work();
    readBME280();
}

void RFExampleNode::readBME280()
{
    _bme280.setMode(MODE_FORCED); //Wake up sensor and take reading

    while(_bme280.isMeasuring() == false) ; //Wait for sensor to start measurment
    while(_bme280.isMeasuring() == true) ; //Hang out while sensor completes the reading   

    appendSendBufferFloat(_bme280.readTempC());
    appendSendBufferFloat(_bme280.readFloatHumidity());
    appendSendBufferFloat(_bme280.readFloatPressure() / 100.0F, true);

    _bme280.setMode(MODE_SLEEP);
}