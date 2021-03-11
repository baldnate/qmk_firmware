# baldnate's sweet16 multipad

## features

- 3 layers, controlled by half-second holds of the first three keys of the top row
  - numeric keypad, crammed into a 4x4 layout
    - includes num lock via holding 7 once on this layer
  - macro pad
    - i use this for controlling OBS and related software
  - emote pad
    - mix of emotes from my channel
- reset via half-second hold of the forth key of the top row
- 11 underglow LEDs, currently used to indicate active layer

## build details

1. build out as usual with 1up directions (not realizing that underglow is indeed supported on the v1 board)
1. mount the standoffs on an old wood and jute coaster you made almost a decade ago
1. pine for leds, both for semantic color (layer indications), but also for decoration
1. root around in the QMK repo, find out that someone else _did_ add leds to the v1 board
1. not wanting to depop all the keyswitches, awkwardly solder leads onto the led strip connection
1. after proving that it works with 4 leds, add two more strips to give side and bottom underglow (top underglow impractical due to the positioning of the pro micro)

[build album with notes](https://imgur.com/a/PAtFrHK)

## notes

- wish there was a cooked in "tap or hold" concept like in oryx, rather than me rolling it myself
- otherwise, i'm pretty happy with where i landed