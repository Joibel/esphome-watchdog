# ESPHome watchdog

For complementing Athom smart plugs

## How It Works

- Exposes `/pet` HTTP GET endpoint
- Tracks last-pet timestamp internally
- Power-cycles the specified relay if no pet within timeout window
