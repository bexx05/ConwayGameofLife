//
// Created by Rebeca on 29/04/2026.
//

#ifndef UNTITLED_GRID_H
#define UNTITLED_GRID_H

#pragma once
#include <vector>
#include <memory>
#include <functional>
#include <SFML/Graphics.hpp>
#include "Cell.h"

class Grid
{
public:
    Grid(int rows, int cols, int cellSize);
    ~Grid();

    // Factory signature: given an initial alive state, produce a shared Cell.
    // main() passes a lambda that constructs the chosen derived type.
    // e.g.  grid.populate([](bool a){ return std::make_shared<ConwayCell>(a); }, 0.3f);
    using CellFactory = std::function<std::shared_ptr<Cell>(bool alive)>;

    void populate(CellFactory factory, float aliveProbability);
    void run();   // SFML event + render loop
    void printCellTypeStats() const;

private:
    void update();
    void draw();
    int  countNeighbors(int row, int col) const;

    int rows_;
    int cols_;
    int cellSize_;

    std::vector<std::vector<std::shared_ptr<Cell>>> cells_;
    sf::RenderWindow window_;
};

#endif //UNTITLED_GRID_H