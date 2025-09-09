#ifndef __HOMEASSISTANT_CONFIG_H__
#define __HOMEASSISTANT_CONFIG_H__

const char mqtt_client_id[] = "xiaozhi_esp32_test";//MQTT中的topic名称，需要保证唯一
const char mqtt_host[] = "";//mqtt的ip地址
const int mqtt_port = 1883;//mqtt的端口号
const char mqtt_username[] = "";
const char mqtt_password[] = "";
const char ha_device_name[] = "xiaozhi_esp32_test";//显示在HA中的设备名称
const char ha_model[]="xiaozhi";//显示在HA中的设备型号
const char ha_manufacturer[]="lingyutech";//显示在HA中的制造商

#endif // __HOMEASSISTANT_CONFIG_H__