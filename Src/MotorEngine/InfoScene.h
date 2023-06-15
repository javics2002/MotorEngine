#pragma once
#include <string>
#include <unordered_map>

namespace me {
    typedef std::string SceneName, EntityName, ComponentName, ParameterName, ParameterValue;

    typedef std::unordered_map<ParameterName, ParameterValue> Parameters;
    typedef std::unordered_map<ComponentName, Parameters> InfoEntity;
    typedef std::unordered_map<EntityName, InfoEntity> InfoScene;
}