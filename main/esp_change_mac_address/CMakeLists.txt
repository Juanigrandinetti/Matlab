idf_component_register(SRCS "src/mac.c"
                    INCLUDE_DIRS "include"
                    REQUIRES esp_system esp_wifi esp_event esp_log nvs_flash)
