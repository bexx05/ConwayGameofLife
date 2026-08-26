#include "ConwayCell.h"
#include "HighLifeCell.h"
#include "DayNightCell.h"
#include "Grid.h"
#include "exceptions.h"
#include <iostream>

int main()
{
    try
    {
        int rows, cols, choice;

        std::cout << "Enter number of rows (1-100): ";
        std::cin >> rows;

        std::cout << "Enter number of cols (1-100): ";
        std::cin >> cols;

        if (rows < 1 || rows > 100 || cols < 1 || cols > 100)
            throw GridInitializationException(rows, cols, 10);

        std::cout << "Select cell type:\n"
                  << "  1 - Conway\n"
                  << "  2 - HighLife\n"
                  << "  3 - DayNight\n"
                  << "Choice: ";
        std::cin >> choice;

        if (choice < 1 || choice > 3)
            throw InvalidCellTypeException(choice);

        Grid grid(rows, cols, 10);

        if      (choice == 1) grid.populate([](bool a){ return std::make_shared<ConwayCell>(a);   }, 0.3f);
        else if (choice == 2) grid.populate([](bool a){ return std::make_shared<HighLifeCell>(a); }, 0.3f);
        else                  grid.populate([](bool a){ return std::make_shared<DayNightCell>(a); }, 0.3f);

        grid.run();
    }
    catch (const GridInitializationException& e)
    {
        std::cerr << e << "\n";
    }
    catch (const InvalidCellTypeException& e)
    {
        std::cerr << e << "\n";
    }
    catch (const InvalidProbabilityException& e)
    {
        std::cerr << e << "\n";
    }
    catch (const std::exception& e)
    {
        std::cerr << "[Unexpected Error] " << e.what() << "\n";
    }

    return 0;
}