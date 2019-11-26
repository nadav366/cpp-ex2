#include "Fractal.h"
#include <iostream>
#include <cmath>
#include <utility>

const char SPACE = ' ';
const char NEW_LINE = '\n';
const char FULL = '#';

const int EMPTY = 0;

/**
 * @brief constructor
 * @param degree The degree of painting to be drawn
 * @param lineSize The degree of painting to be drawn
 * @param pattern The degree of painting to be drawn
 */
Fractal::Fractal(int degree, int lineSize, std::string  pattern) :
        _degree(degree),
        _lineSize(lineSize),
        _numOfCell(std::pow(lineSize, degree)),
        _pattern(std::move(pattern))
{
    _allPic = new char *[_numOfCell];
    for (int i = 0; i < _numOfCell; ++i)
    {
        _allPic[i] = new char[_numOfCell];
    }
}

/**
 * @brief destructor
 */
Fractal::~Fractal()
{
    // Releases the memory of the entire two-dimensional array of painting
    for (int i = 0; i < _numOfCell; ++i)
    {
        delete[] _allPic[i];
    }
    delete[] _allPic;
}

/**
  * @brief move constructor
  * @param other Another object to move from
  */
Fractal::Fractal(Fractal && other) noexcept :
        _degree(other._degree),
        _lineSize(other._lineSize),
        _numOfCell(other._numOfCell)
{
    _pattern = other._pattern;
    other._pattern = nullptr;

    _allPic = other._allPic;
    other._allPic = nullptr;
}

/**
 * @brief copy assignment
 * @param other Another object to put from it
 * @return Another object to put from it
 */
Fractal & Fractal::operator=(const Fractal & other)
{
    if (&other != this)
    {
        *this = Fractal(other);
    }
    return *this;
}

/**
 * @brief move assignment
 * @param other Another object to move from it
 * @return Another object to put from it
 */
Fractal & Fractal::operator=(Fractal && other) noexcept
{
    if (&other != this)
    {
        *this = Fractal(other);
    }
    return *this;
}

/**
 * @brief A function that fills the two-dimensional array, drawing according to the
 *          pattern and degree, recursively
 * @param curDeg Current recursion rate
 * @param drawFlag Flag, whether to draw the template, or write a space anyway
 * @param row The current row drawn
 * @param col The current column drawn
 */
void Fractal::fillPic(int curDeg, bool drawFlag, int row, int col)
{
    // Recursion base case
    if (curDeg == EMPTY)
    {
        if (drawFlag)
        {
            _allPic[col][row] = FULL;
        }
        else
        {
            _allPic[col][row] = SPACE;
        }
        return;
    }

    int curCol = col * _lineSize, curRow = row * _lineSize;
    int index = EMPTY;
    // Run the recursion according to the template
    for (char c : _pattern)
    {
        if (c == NEW_LINE)
        {
            curCol++;
            index = EMPTY;
        }
        if (c == FULL)
        {
            fillPic(curDeg - 1, drawFlag, curRow + index, curCol);
            index++;
        }
        if (c == SPACE)
        {
            fillPic(curDeg - 1, false, curRow + index, curCol);
            index++;
        }
    }
}

/**
 * @brief A function that draws the fractal according to its data
 */
void Fractal::draw()
{
    fillPic(_degree);

    for (int i = 0; i < _numOfCell; ++i)
    {
        for (int j = 0; j < _numOfCell; ++j)
        {
            std::cout << _allPic[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/**
 * @brief A function that produces the appropriate fractal of the user's choice
 * @param input Selected fractal type number
 * @param degree The fractal degree
 * @return Pointing to a new fractal, according to the data
 * It is the user's responsibility to release the memory of the new fractal
 */
Fractal *Fractal::getFrac(int input, int degree)
{
    switch (input)
    {
        case 1:
            return new(std::nothrow) Carpet(degree);
        case 2:
            return new(std::nothrow) Sieve(degree);
        case 3:
            return new(std::nothrow) Cantor(degree);
        default:
            return nullptr;
    }
}

