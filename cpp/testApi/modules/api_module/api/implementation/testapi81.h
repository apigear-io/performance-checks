
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include "api/generated/core/testapi81.data.h"
#include <memory>

namespace Cpp {
namespace Api {

/**
* The TestApi81 implementation.
*/
class CPP_API_EXPORT TestApi81 : public ITestApi81
{
public:
    explicit TestApi81();
    ~TestApi81();
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
    * Access to a publisher, use it to subscribe for TestApi81 changes and signal emission.
    * @return The publisher for TestApi81.
    */
    ITestApi81Publisher& _getPublisher() const override;
private:
    /** The publisher for the TestApi81. */
    std::unique_ptr<ITestApi81Publisher> m_publisher;
    /** The helper structure to store all the properties for TestApi81. */
    TestApi81Data m_data;
};
} // namespace Api
} // namespace Cpp
