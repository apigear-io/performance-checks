
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include "api/generated/core/testapi94.data.h"
#include <memory>

namespace Cpp {
namespace Api {

/**
* The TestApi94 implementation.
*/
class CPP_API_EXPORT TestApi94 : public ITestApi94
{
public:
    explicit TestApi94();
    ~TestApi94();
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
    * Access to a publisher, use it to subscribe for TestApi94 changes and signal emission.
    * @return The publisher for TestApi94.
    */
    ITestApi94Publisher& _getPublisher() const override;
private:
    /** The publisher for the TestApi94. */
    std::unique_ptr<ITestApi94Publisher> m_publisher;
    /** The helper structure to store all the properties for TestApi94. */
    TestApi94Data m_data;
};
} // namespace Api
} // namespace Cpp
