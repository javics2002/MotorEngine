#include "FactoryComponent.h"

using namespace me;

float me::FactoryComponent::Value(Parameters& params, const ParameterName& parameter, float defaultValue)
{
    return params.count(parameter) ? std::stof(params[parameter]) : defaultValue;
}

int me::FactoryComponent::Value(Parameters& params, const ParameterName& parameter, int defaultValue)
{
    return params.count(parameter) ? std::stoi(params[parameter]) : defaultValue;
}

bool me::FactoryComponent::Value(Parameters& params, const ParameterName& parameter, bool defaultValue)
{
    return params.count(parameter) ? (bool) std::stoi(params[parameter]) : defaultValue;
}

std::string me::FactoryComponent::Value(Parameters& params, const ParameterName& parameter, std::string defaultValue)
{
    auto ci = params.count(parameter);
    return params.count(parameter) ? params[parameter] : defaultValue;
}

