#include <home_assistant_manager.h>
#include <esp_log.h>
#include <application.h>

#define TAG "HomeAssistantManager"

// HA 设备信息 JSON 文档
nlohmann::json json_this_device_doc_;

// Setup MQTT
MQTTRemote _mqtt_remote(CONFIG_MQTT_CLIENT_ID,
                        CONFIG_MQTT_HOST,
                        CONFIG_MQTT_PORT,
                        CONFIG_MQTT_USERNAME,
                        CONFIG_MQTT_PASSWORD,
                        {.rx_buffer_size = 256, .tx_buffer_size = 1024, .keep_alive_s = 10});

// Create the Home Assistant bridge. This is shared across all entities.
// We only have one per device/hardware. In our example, the name of our device is "livingroom".
// See constructor of HaBridge for more documentation.
HaBridge ha_bridge(_mqtt_remote, CONFIG_HA_DEVICE_NAME, json_this_device_doc_);

// // HA 实体
HaEntityButton _ha_entity_button(ha_bridge, "wake up", "");
HaEntityString _ha_device_status(ha_bridge, "状态", "device_status", {.with_attributes = true, .force_update = false});
HaEntityString _ha_xiaozhi_user_message(ha_bridge, "user", "user_message", {.with_attributes = true, .force_update = false});
HaEntityString _ha_xiaozhi_assistant_message(ha_bridge, "assistant", "assistant_message", {.with_attributes = true, .force_update = false});
HaEntityText _ha_xiaozhi_wake_word_invoke(ha_bridge, "指令", "wake_word",
                                          {.min_text_length = 0,
                                           .max_text_length = 255,
                                           .with_state_topic = false,
                                           .is_password = false,
                                           .force_update = false,
                                           .retain = false});

HomeAssistantManager::HomeAssistantManager()
{
    setupJsonForThisDevice();
}
HomeAssistantManager::~HomeAssistantManager()
{
}
void HomeAssistantManager::Start()
{
    // Start MQTT
    _mqtt_remote.start([](bool connected)
                       {
                           // Publish Home Assistant Configuration once connected to MQTT.
                           _ha_entity_button.publishConfiguration();
                           _ha_device_status.publishConfiguration();
                           _ha_xiaozhi_user_message.publishConfiguration();
                           _ha_xiaozhi_assistant_message.publishConfiguration();
                           _ha_xiaozhi_wake_word_invoke.publishConfiguration();

                           //   ha_entity_button.setOnPressed([this]() {
                           //     Schedule([this](){
                           //       OnWakeWordDetected("NONE");
                           //     });
                           //   });
                           //   ha_xiaozhi_wake_word_invoke.setOnText([this](std::string text) {
                           //     Schedule([this,text](){
                           //       OnWakeWordDetected(text);
                           //     });
                           //   });
                       });
}

HaEntityButton &HomeAssistantManager::GetWakeUpButtonEntity()
{
    return _ha_entity_button;
}

HaEntityString &HomeAssistantManager::GetDeviceStatusEntity()
{
    return _ha_device_status;
}

HaEntityString &HomeAssistantManager::GetUserMessageEntity()
{
    return _ha_xiaozhi_user_message;
}

HaEntityString &HomeAssistantManager::GetAssistantMessageEntity()
{
    return _ha_xiaozhi_assistant_message;
}

HaEntityText &HomeAssistantManager::GetWakeWordInvokeEntity()
{
    return _ha_xiaozhi_wake_word_invoke;
}

void HomeAssistantManager::setupJsonForThisDevice()
{
    json_this_device_doc_["identifiers"] = std::string(CONFIG_HA_MODEL) + "_" + std::string(CONFIG_MQTT_CLIENT_ID);
    json_this_device_doc_["name"] = CONFIG_HA_DEVICE_NAME;
    json_this_device_doc_["sw_version"] = "1.0.0";
    json_this_device_doc_["model"] = CONFIG_HA_MODEL;
    json_this_device_doc_["manufacturer"] = CONFIG_HA_MANUFACTURER;
}