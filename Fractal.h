#ifndef CPP_EX2_FRACTAL_H
#define CPP_EX2_FRACTAL_H

#include <string>

/**
 * @brief A class which is a fractal painting
 */
class Fractal
{
private:
    /**    The degree of painting to be drawn                   */
    int _degree;
    /**   The size of the row in the specific fractal                    */
    int _lineSize;
    /**    The size of the line to be in the entire drawing                   */
    int _numOfCell;
    /**    The fractal pattern to draw                   */
    std::string _pattern;
    /**     A two-dimensional array that holds the entire painting                  */
    char **_allPic;

public:

    /**
     * @brief constructor
     * @param degree The degree of painting to be drawn
     * @param lineSize The degree of painting to be drawn
     * @param pattern The degree of painting to be drawn
     */
    Fractal(int degree, int lineSize, std::string  pattern);

    /**
     * @brief destructor
     */
    ~Fractal();

    /**
     * @brief copy constructor
     * @param other Another fractal object for copying
     */
    Fractal(const Fractal & other) : Fractal(other._degree, other._lineSize, other._pattern)
    {}

    /**
     * @brief move constructor
     * @param other Another object to move from
     */
    Fractal(Fractal && other) noexcept;

    /**
     * @brief copy assignment
     * @param other Another object to put from it
     * @return Another object to put from it
     */
    Fractal & operator=(const Fractal & other);

    /**
     * @brief move assignment
     * @param other Another object to move from it
     * @return Another object to put from it
     */
    Fractal & operator=(Fractal && other) noexcept;

    /**
     * @brief A function that fills the two-dimensional array, drawing according to the
     *          pattern and degree, recursively
     * @param curDeg Current recursion rate
     * @param drawFlag Flag, whether to draw the template, or write a space anyway
     * @param row The current row drawn
     * @param col The current column drawn
     */
    void fillPic(int curDeg, bool drawFlag = true, int row = 0, int col = 0);

    /**
     * @brief A function that draws the fractal according to its data
     */
    void draw();

    /**
     * @brief A function that produces the appropriate fractal of the user's choice
     * @param input Selected fractal type number
     * @param degree The fractal degree
     * @return Pointing to a new fractal, according to the data
     * It is the user's responsibility to release the memory of the new fractal
     */
    static Fractal *getFrac(int input, int degree);

};

/**
 * @brief Specific type of fractal-Sierpinski Carpet
 */
class Carpet : public Fractal
{
public:
    /**
     * @brief constructor
     * @param degree The fractal degree
     */
    Carpet(int degree) : Fractal(degree, 3, "###\n# #\n###")
    {}
};

/**
 * @brief Specific type of fractal-Sierpinski Sieve
 */
class Sieve : public Fractal
{
public:
    /**
     * @brief constructor
     * @param degree The fractal degree
     */
    Sieve(int degree) : Fractal(degree, 2, "##\n# ")
    {}
};

/**
 * @brief Specific type of fractal-Cantor Dust
 */
class Cantor : public Fractal
{
public:
    /**
     * @brief constructor
     * @param degree The fractal degree
     */
    Cantor(int degree) : Fractal(degree, 3, "# #\n   \n# #")
    {}
};

#endif //CPP_EX2_FRACTAL_H
