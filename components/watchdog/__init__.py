import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import web_server
from esphome.const import CONF_ID
from esphome.core import coroutine_with_priority

watchdog_ns = cg.esphome_ns.namespace("watchdog")
WatchdogComponent = watchdog_ns.class_("WatchdogComponent", cg.Component)

CONF_RELAY_ID = "relay_id"
CONF_TIMEOUT = "timeout"

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(WatchdogComponent),
        cv.Required(CONF_RELAY_ID): cv.use_id(cg.EntityBase),
        cv.Optional(CONF_TIMEOUT, default="5min"): cv.positive_time_period_milliseconds,
    }
).extend(cv.COMPONENT_SCHEMA)

CODEOWNERS = ["@Joibel"]
VERSION = "1.0.0"

@coroutine_with_priority(40.0)
async def to_code(config):
    var = cg.new_Pvariable(config[cv.GenerateID()])
    await cg.register_component(var, config)

    relay_id = config[CONF_RELAY_ID]
    relay = await cg.get_variable(relay_id)
    cg.add(var.set_relay(relay))

    timeout_ms = config[CONF_TIMEOUT]
    cg.add(var.set_timeout(timeout_ms))

    # Ensure web_server is available
    wb = await cg.get_variable(web_server.CONF_WEB_SERVER)
    cg.add(var.set_web_server(wb))
