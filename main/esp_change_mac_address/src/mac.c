#include <stdio.h>
#include "esp_system.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "nvs_flash.h"

// Cantidad de bytes que contiene una dirección MAC
#define MAC_ADDR_SIZE 6

// Función para obtener la dirección MAC precargada en la memoria del esp32
void get_mac_address()
{
    uint8_t mac[MAC_ADDR_SIZE];
    esp_wifi_get_mac(ESP_IF_WIFI_STA, mac);
    printf("Dirección MAC original: %02x:%02x:%02x:%02x:%02x:%02x", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
}

// Función para modificar la dirección MAC del esp32
int set_mac_address(uint8_t *mac)
{
    esp_err_t err = esp_wifi_set_mac(ESP_IF_WIFI_STA, mac);
    if (err == ESP_OK)
    {
        fflush(stdout);
        printf("[MAC ADDRESS] La dirección MAC de la placa ESP32 ha sido actualizada satisfactoriamente!\n[MAC ADDRESS]Nueva dirección MAC: %02x:%02x:%02x:%02x:%02x:%02x\n", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
        return 1;
    } else
    {
        printf("[MAC ADDRESS] Error al modificar la dirección MAC de la placa ESP32");
        return 0;
    }
}

void nvs_ini()
{
    // Inicializar la memoria flash no volatil (NVS) del sistema 
    esp_err_t ret = nvs_flash_init();
	if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND)
	{
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();

    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_start());
}