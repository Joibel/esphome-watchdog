#pragma once
#include "esphome.h"
#include "esphome/components/switch/switch.h"
#include "esphome/components/web_server/web_server.h"

namespace esphome {
namespace watchdog {

class WatchdogComponent : public Component {
 public:
  void set_relay(switch_::Switch *relay) { this->relay_ = relay; }
  void set_timeout(uint32_t timeout_ms) { this->timeout_ms_ = timeout_ms; }

  void setup() override;
  void loop() override;
  float get_setup_priority() const override { return setup_priority::AFTER_WIFI; }

 private:
  switch_::Switch *relay_;
  uint32_t timeout_ms_;
  uint32_t last_pet_time_;
};

}  // namespace watchdog
}  // namespace esphome
