#include "FactoryComponent.h"
#include "Utils/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"

using namespace me;

float FactoryComponent::Value(Parameters& params, const ParameterName& parameter, float defaultValue)
{
    return params.count(parameter) ? std::stof(params[parameter]) : defaultValue;
}

int FactoryComponent::Value(Parameters& params, const ParameterName& parameter, int defaultValue)
{
    return params.count(parameter) ? std::stoi(params[parameter]) : defaultValue;
}

bool FactoryComponent::Value(Parameters& params, const ParameterName& parameter, bool defaultValue)
{

    return params.count(parameter) ? (bool) std::stoi(params[parameter]) : defaultValue;
}

std::string FactoryComponent::Value(Parameters& params, const ParameterName& parameter, std::string defaultValue)
{
    return params.count(parameter) ? params[parameter] : defaultValue;
}

