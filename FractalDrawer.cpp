#include "Fractal.h"
#include <fstream>
#include <vector>
#include <iostream>

const int NUM_OF_PARM = 2;
const int MAX_DEGREE = 6;
const int MIN_DEGREE = 1;
const int MAX_CHOICE = 3;
const int MIN_CHOICE = 1;

const std::string ERROR_NUM_OF_PARM = "Usage: FractalDrawer <file path>";
const std::string ERROR_INVALID = "Invalid input";
const std::string ERROR_ALLOC = "Memory allocation failed";

const char SEPARATOR = ',';
const char NEW_LINE = '\n';
const char NEW_LINE_EXTRA = '\r';
const char FIRST_NUM = '0';

/**
 * @brief A function that addresses a file error, and a controlled shutdown of the software
 * @param myFile Reference to the instructions file
 * @param allFrac Reference to the fractal vector
 * @return The error code that the software should return
 */
int closeAndDel(std::ifstream & myFile, const std::vector<Fractal *> & allFrac,
                const std::string & errMsg)
{
    myFile.close();
    for (auto frac : allFrac)
    {
        delete frac;
    }
    std::cerr << errMsg << std::endl;
    return EXIT_FAILURE;
}

/**
 * @brief Main function
 * @param argc The number of arguments the software receives
 * @param argv An array of strings - parameters that the software receives
 * @return0 in case of success, 1 otherwise
 */
int main(int argc, const char *argv[])
{
    //Checking a number of valid arguments
    if (argc != NUM_OF_PARM)
    {
        std::cerr << ERROR_NUM_OF_PARM << std::endl;
        return EXIT_FAILURE;
    }

    // Open the file
    std::ifstream myFile;
    myFile.open(argv[1]);
    if (!myFile.is_open())
    {
        std::cerr << ERROR_INVALID << std::endl;
        return EXIT_FAILURE;
    }

    // Setting Variables
    std::vector<Fractal *> allFrac;
    std::string line;
    int firscWord, secWord;
    char sper, endLine;

    // Getting all the lines
    while ((firscWord = myFile.get()) != EOF)
    {
        firscWord -= FIRST_NUM;
        sper = myFile.get();
        secWord = myFile.get() - FIRST_NUM;
        if ((endLine = myFile.get()) == NEW_LINE_EXTRA)
        {
            endLine = myFile.get();
        }

        // Check that the input is valid
        if (firscWord < MIN_CHOICE || firscWord > MAX_CHOICE ||
            secWord < MIN_DEGREE || secWord > MAX_DEGREE ||
            sper != SEPARATOR ||
            (endLine != NEW_LINE && endLine != EOF))
        {
            return closeAndDel(myFile, allFrac, ERROR_INVALID);
        }

        // Create a new object, and add a locator
        allFrac.insert(allFrac.begin(), Fractal::getFrac(firscWord, secWord));
        if(!allFrac[0])
        {
            return closeAndDel(myFile, allFrac, ERROR_ALLOC);
        }
    }

    // Print all fractals
    for (auto frac : allFrac)
    {
        frac->draw();
        delete frac;
    }
    myFile.close();
    return EXIT_SUCCESS;
}

