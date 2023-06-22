
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include "api/generated/core/testapi0.data.h"
#include <memory>

namespace Cpp {
namespace Api {

/**
* The TestApi0 implementation.
*/
class CPP_API_EXPORT TestApi0 : public ITestApi0
{
public:
    explicit TestApi0();
    ~TestApi0();
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
    * Access to a publisher, use it to subscribe for TestApi0 changes and signal emission.
    * @return The publisher for TestApi0.
    */
    ITestApi0Publisher& _getPublisher() const override;
private:
    /** The publisher for the TestApi0. */
    std::unique_ptr<ITestApi0Publisher> m_publisher;
    /** The helper structure to store all the properties for TestApi0. */
    TestApi0Data m_data;
};
} // namespace Api
} // namespace Cpp
