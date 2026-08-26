# Conway's Game of Life

A C++/SFML implementation of Conway's Game of Life, structured around a small class hierarchy so rule sets stay swappable.

## Rule sets

| Type | Rules |
|---|---|
| Conway | B3/S23 |
| HighLife | B36/S23 |
| Day & Night | B3678/S34678 |

## Design

- `Cell` — abstract base; non-virtual interface (`nextState`) delegates to virtual `survives()` / `born()`.
- `ConwayCell`, `HighLifeCell`, `DayNightCell` — rule-specific derived classes.
- `Grid` — owns `vector<vector<shared_ptr<Cell>>>`, drives `update()` / `draw()`.
- Custom exception hierarchy validates input (grid size, cell type, probability).
- Static `livingCellCount`, tracked via constructor/destructor, exposed through a static getter.
- `dynamic_pointer_cast` used at runtime for per-type statistics.

## Requirements

- C++17
- SFML 2.5+

## Build

```bash
mkdir build && cd build
cmake ..
make
```

## Usage

```bash
./game_of_life
```

You'll be prompted for:
1. Grid rows and columns (1–100)
2. Cell type (1 = Conway, 2 = HighLife, 3 = Day & Night)

The SFML window then opens — `Escape` or the close button exits.
