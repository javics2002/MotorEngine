#include "FactoryComponent.h"
#include "MotorEngine/MotorEngineError.h"
#include "MotorEngine/SceneManager.h"

using namespace me;

float FactoryComponent::Value(Parameters& params, const ParameterName& parameter, float defaultValue)
{
    if (params.count(parameter) > 0) {
        for (char c : params[parameter]) {
            if (!std::isdigit(c) && c != '.' && c != '-') {
                errorManager().throwMotorEngineError("Invalid parameter for " + parameter + " set.", " Value is not a float.");
                sceneManager().quit();
                return defaultValue;
            }
        }
        float value = std::strtol(params[parameter].c_str(), NULL, 16);
        return (value ==  FLT_MAX || value == FLT_MIN) ? defaultValue : std::stof(params[parameter]);
    }
    else {
#ifdef _DEBUG
        std::cout << "No value for parameter " << parameter << ". It was set to the default value " << defaultValue << std::endl;
#endif
        return defaultValue;
    }
}

int FactoryComponent::Value(Parameters& params, const ParameterName& parameter, int defaultValue)
{
    if (params.count(parameter) > 0) {
        for (char c : params[parameter]) {
            if (!std::isdigit(c) && c != '-') {
                errorManager().throwMotorEngineError("Invalid parameter for " + parameter + " set.", " Value is not a integer.");
                sceneManager().quit();
                return defaultValue;
            }
        }
        int value = std::strtol(params[parameter].c_str(), NULL, 16);
        return (value == INT_MAX || value == INT_MIN) ? defaultValue : std::stoi(params[parameter]);
    }
    else {
#ifdef _DEBUG
        std::cout << "No value for parameter " << parameter << ". It was set to the default value " << defaultValue << std::endl;
#endif
        return defaultValue;
    }
}

bool FactoryComponent::Value(Parameters& params, const ParameterName& parameter, bool defaultValue)
{
    if (params.count(parameter) > 0) {
        if (params[parameter].size() == 1 && std::isdigit(params[parameter][0])) {
            int value = std::stoi(params[parameter]);

            if ((value == 0) || (value == 1))
                return (bool)value;
        }
    
        errorManager().throwMotorEngineError("Invalid parameter for " + parameter + " set.", " Value is not a boolean.");
        sceneManager().quit();
        return defaultValue;
    }
    else {
#ifdef _DEBUG
        std::cout << "No value for parameter " << parameter << ". It was set to the default value " << defaultValue << std::endl;
#endif
        return defaultValue;
    }
}

std::string FactoryComponent::Value(Parameters& params, const ParameterName& parameter, std::string defaultValue)
{
    if (params.count(parameter) > 0) {
        return params[parameter];
    }
    else {
#ifdef _DEBUG
        std::cout << "No value for parameter " << parameter << ". It was set to the default value " << defaultValue << std::endl;
#endif
        return defaultValue;
    }
}

