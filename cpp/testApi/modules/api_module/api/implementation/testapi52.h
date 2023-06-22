
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include "api/generated/core/testapi52.data.h"
#include <memory>

namespace Cpp {
namespace Api {

/**
* The TestApi52 implementation.
*/
class CPP_API_EXPORT TestApi52 : public ITestApi52
{
public:
    explicit TestApi52();
    ~TestApi52();
public:
    void setPropInt(int propInt) override;
    int getPropInt() const override;
    
    void setPropFloat(float propFloat) override;
    float getPropFloat() const override;
    
    void setPropString(const std::string& propString) override;
    const std::string& getPropString() const override;
    
    int funcInt(int paramInt) override;
    std::future<int> funcIntAsync(int paramInt) override;
        
    float funcFloat(float paramFloat) override;
    std::future<float> funcFloatAsync(float paramFloat) override;
        
    std::string funcString(const std::string& paramString) override;
    std::future<std::string> funcStringAsync(const std::string& paramString) override;
        
    /**
    * Access to a publisher, use it to subscribe for TestApi52 changes and signal emission.
    * @return The publisher for TestApi52.
    */
    ITestApi52Publisher& _getPublisher() const override;
private:
    /** The publisher for the TestApi52. */
    std::unique_ptr<ITestApi52Publisher> m_publisher;
    /** The helper structure to store all the properties for TestApi52. */
    TestApi52Data m_data;
};
} // namespace Api
} // namespace Cpp
