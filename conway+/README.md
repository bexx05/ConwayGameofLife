# Conway's Game of Life — Templates & Patterns

Builds on the [base implementation](../conway) with a generic logging component and three design patterns, without touching the core simulation logic.

## What's new

- **`GenerationLog<T>`** — template class backed by a ring-buffer `vector<T>`; `record()`, `latest()`, `minValue()` / `maxValue()`, and a member function template `filter(Pred)`. Full specialization for `std::string` (sequential output vs. numeric stats), plus a free function template `average<T>()`.
- **Observer** — `ISimulationObserver` decouples `Grid` from reporting; `ConsoleStatsObserver` subscribes to per-generation updates.
- **Factory** — `ICellFactory` with `ConwayCellFactory` / `HighLifeCellFactory` / `DayNightCellFactory`, replacing ad-hoc lambdas for cell creation.
- **Singleton** — `SimulationConfig::instance()` holds shared simulation parameters (grid size, cell type, density).

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

Same prompts as the base version (grid size, cell type). Per-generation stats print to console via the registered observer; on exit, a running average of living cells and a log of simulation events (`simulation started` / `ended`) are printed.
