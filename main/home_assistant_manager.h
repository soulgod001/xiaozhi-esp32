#ifndef HOME_ASSISTANT_MANAGER_H
#define HOME_ASSISTANT_MANAGER_H
#include <cstring>

#include <nlohmann/json.hpp>
#include <MQTTRemote.h>
#include <HaBridge.h>
#include <entities/HaEntityBoolean.h>
#include <entities/HaEntityButton.h>
#include <entities/HaEntityString.h>
#include <entities/HaEntityText.h>
#include <entities/HaEntityNumber.h>

class HomeAssistantManager {
public:
    static HomeAssistantManager& GetInstance() {
        static HomeAssistantManager instance;
        return instance;
    }
    // 删除拷贝构造函数和赋值运算符
    HomeAssistantManager(const HomeAssistantManager&) = delete;
    HomeAssistantManager& operator=(const HomeAssistantManager&) = delete;
    void Start();
    HaEntityButton& GetWakeUpButtonEntity();
    HaEntityString& GetDeviceStatusEntity();
    HaEntityString& GetUserMessageEntity();
    HaEntityString& GetAssistantMessageEntity();
    HaEntityText& GetWakeWordInvokeEntity();
    HaEntityNumber& GetBrightnessEntity();
    HaEntityNumber& GetVolumeEntity();

private:
    HomeAssistantManager();
    ~HomeAssistantManager();
    void setupJsonForThisDevice();

};

#endif // HOME_ASSISTANT_MANAGER_H
