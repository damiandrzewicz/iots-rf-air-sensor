#pragma once

#include "RFTemplateNode.h"
#include "SparkFunBME280.h"

class RFExampleNode : public RFTemplateNode
{
public:
    RFExampleNode() = default;

    virtual void setup() override;

    virtual void work() override;

protected:
    void initRadio() override;
    void readBME280();

private:
    BME280 _bme280;
};