#pragma once

using LightCode = uint8_t;

namespace LightType
{
    enum : LightCode
    {
        NoLightSource = 0,
        PointLightSource = 1,
        DirectLightSource = 2,
        SpotLightSource = 3,
        SpotLightSmoothSource = 4,
    };
} // namespace LightType
