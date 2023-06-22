
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include "api/generated/core/testapi79.data.h"
#include <memory>

namespace Cpp {
namespace Api {

/**
* The TestApi79 implementation.
*/
class CPP_API_EXPORT TestApi79 : public ITestApi79
{
public:
    explicit TestApi79();
    ~TestApi79();
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
    * Access to a publisher, use it to subscribe for TestApi79 changes and signal emission.
    * @return The publisher for TestApi79.
    */
    ITestApi79Publisher& _getPublisher() const override;
private:
    /** The publisher for the TestApi79. */
    std::unique_ptr<ITestApi79Publisher> m_publisher;
    /** The helper structure to store all the properties for TestApi79. */
    TestApi79Data m_data;
};
} // namespace Api
} // namespace Cpp
