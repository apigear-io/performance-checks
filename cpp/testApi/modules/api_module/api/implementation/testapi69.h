
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include "api/generated/core/testapi69.data.h"
#include <memory>

namespace Cpp {
namespace Api {

/**
* The TestApi69 implementation.
*/
class CPP_API_EXPORT TestApi69 : public ITestApi69
{
public:
    explicit TestApi69();
    ~TestApi69();
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
    * Access to a publisher, use it to subscribe for TestApi69 changes and signal emission.
    * @return The publisher for TestApi69.
    */
    ITestApi69Publisher& _getPublisher() const override;
private:
    /** The publisher for the TestApi69. */
    std::unique_ptr<ITestApi69Publisher> m_publisher;
    /** The helper structure to store all the properties for TestApi69. */
    TestApi69Data m_data;
};
} // namespace Api
} // namespace Cpp
