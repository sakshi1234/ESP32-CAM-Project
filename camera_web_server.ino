#include "esp_camera.h"
#include <WiFi.h>

// ===================
// Camera Model
// ===================
#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"

// ===================
// WiFi Credentials (Your Data)
// ===================
const char *ssid = "Orange";
const char *password = "Yellow@123";

// ===================
void startCameraServer();
// ===================

void setup() {
  Serial.begin(115200);
  Serial.setDebugOutput(false);

  // ===================
  // Camera Configuration
  // ===================
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  // ===================
  // FIX FB-OVF ERROR
  // ===================
  if(psramFound()){
    config.frame_size = FRAMESIZE_VGA;   // Stable
    config.jpeg_quality = 12;
    config.fb_count = 1;
  } else {
    config.frame_size = FRAMESIZE_QVGA;  // Lower if needed
    config.jpeg_quality = 15;
    config.fb_count = 1;
  }

  // ===================
  // Initialize Camera
  // ===================
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) {
    Serial.printf("Camera init failed: 0x%x", err);
    return;
  }

  // ===================
  // Connect WiFi
  // ===================
  WiFi.begin(ssid, password);
  Serial.print("Connecting to WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi Connected!");

  // ===================
  // Start Camera Server
  // ===================
  startCameraServer();

  Serial.print("📷 Camera Ready! Open: http://");
  Serial.println(WiFi.localIP());
}

void loop() {
  delay(10000);
}
