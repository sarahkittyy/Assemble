# Assemble Game Notes (6.26.19)

Tile based factory building game.

## Gui markup

* Game: 700 x 500 window in top-left.
* Two GUI windows:
    * Bottom: 800 x 100, for building elements
    * Right: 100 x 500, for money, statistics, achievements, etc.
* Bottom window:
    * Buttons, with 32x32 icons.
* On button highlight: small (100x100 or smaller) window
    for tower info (cost, description)
* On tower click:
    * Select tower
    * Right GUI displays tower info, stats, sell, upgrades.
    
## Gameplay info
    
* Hotkeys
    * ESC / Click in gui `->` deselect tower.
    * Shift `->` hold to place many
    * S `->` Sell
    
* Map design
    * Tiles are 32x32, start on a 8x8 grid of these tiles.
    * Expansions are purchaseable.
    * Many tiles are resources
        * Stone
        * Iron
        * Coal
        * Copper
    * Zoomable / Pannable
    * Multi layer map
        * Background (water)
        * Base (Environment ontop of water)
        * Locking layer (Blacked out / locked tiles)
        * Resource / Detail (Coal, Stone)

* Buildings
    * Separate, non-tile objects.
            
* Tick-based update system. (N ticks / second, one update / tick)
    
## Base buildings

* Drill
    * Mines stone, iron, coal, copper, etc.
    * Outputs to one side.
* Conveyor
    * Takes a resource from any side, moves it to it's singular output side.
* Furnace
    * Given N coal and N of a resource, smelts the resources.
    * Outputs to one side.
    
## Resources

* Stone
* Coal
* Iron
* Copper

Resources render on the floor / belts as small sprites (8x8?)

## Resource Properties

* Value

## Building properties

Buildings are:

* Rotateable

Properties:

* Have input and output side(s).