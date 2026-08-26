#include "exceptions.h"

InvalidCellTypeException::InvalidCellTypeException(int choice)
    : std::invalid_argument("Invalid cell type: " + std::to_string(choice) +
                            ". Expected 1 (Conway), 2 (HighLife), or 3 (DayNight).")
{
}

std::ostream& operator<<(std::ostream& os, const InvalidCellTypeException& e)
{
    os << "[InvalidCellTypeException] " << e.what();
    return os;
}

GridInitializationException::GridInitializationException(int rows, int cols, int cellSize)
    : std::invalid_argument("Invalid grid parameters: rows=" + std::to_string(rows) +
                            ", cols="     + std::to_string(cols) +
                            ", cellSize=" + std::to_string(cellSize) +
                            ". All values must be between 1 and 100.")
{
}

std::ostream& operator<<(std::ostream& os, const GridInitializationException& e)
{
    os << "[GridInitializationException] " << e.what();
    return os;
}

InvalidProbabilityException::InvalidProbabilityException(float probability)
    : std::out_of_range("Invalid probability: " + std::to_string(probability) +
                        ". Must be in the range [0.0, 1.0].")
{
}

std::ostream& operator<<(std::ostream& os, const InvalidProbabilityException& e)
{
    os << "[InvalidProbabilityException] " << e.what();
    return os;
}