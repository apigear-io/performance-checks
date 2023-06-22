
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include "api/generated/core/testapi91.data.h"
#include <memory>

namespace Cpp {
namespace Api {

/**
* The TestApi91 implementation.
*/
class CPP_API_EXPORT TestApi91 : public ITestApi91
{
public:
    explicit TestApi91();
    ~TestApi91();
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
    * Access to a publisher, use it to subscribe for TestApi91 changes and signal emission.
    * @return The publisher for TestApi91.
    */
    ITestApi91Publisher& _getPublisher() const override;
private:
    /** The publisher for the TestApi91. */
    std::unique_ptr<ITestApi91Publisher> m_publisher;
    /** The helper structure to store all the properties for TestApi91. */
    TestApi91Data m_data;
};
} // namespace Api
} // namespace Cpp
