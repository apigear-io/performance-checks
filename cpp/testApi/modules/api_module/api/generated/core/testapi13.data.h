#pragma once

#include "api/generated/api/api.h"


namespace Cpp
{
namespace Api
{

/**
* A helper structure for implementations of TestApi13. Stores all the properties.
*/
struct TestApi13Data
{
    int m_propInt {0};
    float m_propFloat {0.0f};
    std::string m_propString {std::string()};
};

}
}