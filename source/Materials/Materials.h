#pragma once

#include <Precomz/precomz.h>

#include <json/json.h>

// Logger file
#include "../Core/LogFile.h"

using json = nlohmann::json;

class Materials
{
private:
    json JsonParser;

public:
    Materials(/* args */)
    { 
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
