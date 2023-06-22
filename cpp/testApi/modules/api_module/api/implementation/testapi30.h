
#pragma once
#include "api/generated/api/api.h"
#include "api/generated/api/common.h"
#include "api/generated/core/testapi30.data.h"
#include <memory>

namespace Cpp {
namespace Api {

/**
* The TestApi30 implementation.
*/
class CPP_API_EXPORT TestApi30 : public ITestApi30
{
public:
    explicit TestApi30();
    ~TestApi30();
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
    * Access to a publisher, use it to subscribe for TestApi30 changes and signal emission.
    * @return The publisher for TestApi30.
    */
    ITestApi30Publisher& _getPublisher() const override;
private:
    /** The publisher for the TestApi30. */
    std::unique_ptr<ITestApi30Publisher> m_publisher;
    /** The helper structure to store all the properties for TestApi30. */
    TestApi30Data m_data;
};
} // namespace Api
} // namespace Cpp
