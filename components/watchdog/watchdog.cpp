#include "watchdog.h"
#include "esphome/core/log.h"

namespace esphome {
namespace watchdog {

static const char *const TAG = "watchdog";

void WatchdogComponent::setup() {
  this->last_pet_time_ = millis();

  // Register /pet endpoint
  this->web_server_->on("/pet", HTTP_GET, [this](AsyncWebServerRequest *req) {
    this->last_pet_time_ = millis();
    ESP_LOGD(TAG, "Pet received at %lums", this->last_pet_time_);
    req->send(200, "text/plain", "OK");
  });

  ESP_LOGI(TAG, "Watchdog setup complete. Timeout: %lums", this->timeout_ms_);
}

void WatchdogComponent::loop() {
  const uint32_t now = millis();
  const uint32_t elapsed = now - this->last_pet_time_;

  if (this->last_pet_time_ == 0) {
    return;  // Not initialized yet
  }

  if (elapsed > this->timeout_ms_) {
    ESP_LOGW(TAG, "Timeout (%lums > %lums) – power cycling relay", elapsed, this->timeout_ms_);
    this->relay_->turn_off();
    delay(3000);
    this->relay_->turn_on();
    this->last_pet_time_ = now;
    ESP_LOGI(TAG, "Relay cycled at %lums", now);
  }
}

}  // namespace watchdog
}  // namespace esphome
