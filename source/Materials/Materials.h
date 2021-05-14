#pragma once

#include "../precomz.h"

// Logger file
#include "../Core/LogFile.h"

using json = nlohmann::json;

class Materials
{
private:
    json JsonParser;
    std::string identity = "Materials";
    Logger::LogFile log;
public:
    Materials(/* args */)
    { log.Init(identity);
        std::ifstream FileParser("../source/Materials/MaterialsProperty.json");
        FileParser >> JsonParser;
    }

    ~Materials() = default;

    std::vector<json, std::allocator<json>> getMaterialArrayProperties(const char *Material, const char *Property)
    {
        return JsonParser[Material][Property].get<json::array_t>();
    };

    float getMaterialFloatProperties(const char *Material, const char *Property)
    {
        return JsonParser[Material][Property].get<float_t>();
    };
};
