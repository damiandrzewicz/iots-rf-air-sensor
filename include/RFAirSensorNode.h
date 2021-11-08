#pragma once

#include "RFBaseNode.h"
#include "SparkFunBME280.h"

class RFAirSensorNode : public RFBaseNode
{
public:
    RFAirSensorNode() = default;

    virtual void setup() override;
    virtual void work() override;

protected:

    void initBME280();
    void readBME280();

private:
    BME280 bme280_;
};