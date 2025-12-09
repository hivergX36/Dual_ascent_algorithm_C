#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include "Dictionnary.hpp"
using namespace std;

class Dual_ascent
{


    std::string name;
    Dictionnary<std::string, float> *dict;
    float x_opt;
    float lambda_opt;
    bool test_quadratic_program = true;
    bool test_linear_program = true;

    public:

    Dual_ascent(std::string name, int dictSize)
    {
        name = name;
        dict = new Dictionnary<std::string, float>(dictSize);
        x_opt = 0;
        lambda_opt = 0;
    }

    void readData(std::string namefile)
    {
        string a, b;
        float value;
        // function for parsing the file and filling dictionnary

        std::ifstream file(namefile);
        if (!file)
        {
            std::cerr << "Error opening file: " << name << std::endl;
            return;
        }

        while (file >> a >> b >> value)
        {
            dict->insert(a, value);
        }
        file.close();
    }

    void test_if_quadratic_program()
    {
        float a1 = dict->return_value("a1x2");
        float a2 = dict->return_value("a2x2");
        // One of the quadratic coefficients must be difference of zero
        if (a1 != 0 || a2 != 0)
        {
            test_quadratic_program = true;
        }
        else
        {
            test_quadratic_program = false;
        }
    }

    void test_if_linear_program()
    {
        float b2 = dict->return_value("b2x");
        if (b2 != 0)
        {
            test_linear_program = true;
        }
        else
        {
            test_linear_program = false;
        }
    }

    float calulate_solution_linear_programming()
    {
        float c2 = dict->return_value("c2");
        float b2 = dict->return_value("b2");
        float x = c2 / b2;
        return x;
    }

    float Min_Lagrangien_function(float lambda)
    {
        // L(x,lambda) = a1*x^2 + b1*x + c1 + lambda*(c2 - a2x^2 - b2x)
        // Derivative: L'(x,lambda) = 2*a1*x + b1 - 2*a2*lambda*x - b2*lambda
        // Solving for x: x = -(b1 - b2*lambda) / (2*(a1 - a2*lambda))
        float x = 0;
        float a1 = dict->return_value("a1x2");
        float b1 = dict->return_value("b1x");
        float a2 = dict->return_value("a2x2");
        float b2 = dict->return_value("b2x");

        float numerator = b2 * lambda - b1;
        ;
        float denominator = 2 * (a1 - lambda * a2);
        if (denominator != 0)
        {
            x = numerator / denominator;
        }
        else
        {
            std::cout << "Denominator is Null, we have a linear program with one constraint." << std::endl;
            x = 0; // or some default value or error handling
        }

        return x;
    }

    float update_lambda(float x, float lambda)
    {
        float c2 = dict->return_value("c2");
        float a2 = dict->return_value("a2x2");
        float b2 = dict->return_value("b2x");
        float constraint_value = c2 - a2 * x * x - b2 * x;
        float lambda_new = std::max(0.0f, lambda + 0.1f * constraint_value); // 0.1 is the step size
        return lambda_new;
    }

    void display_equations()
    {
        // display dictionnary content
        std::cout << "equations content:" << std::endl;
        dict->dictionnary_diplay_key_value();
    }

    void display_the_program()
    {
        std::cout << "Program for " + name + ":" << std::endl;
        std::cout << "Objective function: " << std::endl;
        std::cout << "Minimize P = ";
        std::cout << dict->return_value("a1x2") << "x^2 + ";
        std::cout << dict->return_value("b1x") << "x + ";
        std::cout << dict->return_value("c1");
        std::cout << std::endl;
        std::cout << "Subject to: " << std::endl;
        std::cout << dict->return_value("a2x2") << "x^2 + ";
        std::cout << dict->return_value("b2x") << "x >= ";
        std::cout << dict->return_value("c2");
        std::cout << std::endl;
    }

    void solve_dual_ascent()
    {
        float epsilon = 0.0000000001f;
        float previous_lambda = 0;
        int max_iterations = 1000000;
        int iteration = 0;
        float x_t = 0;
        float lambda_t = 0;
        test_if_quadratic_program();
        test_if_linear_program();
        if (!test_quadratic_program)
        {
            if (!test_linear_program)
            {
                std::cout << "This is not a quadratic program nor a linear program." << std::endl;
                return;
            }
            else
            {
                std::cout << "This is a linear program with one constraint." << std::endl;
                float x_opt = calulate_solution_linear_programming();
                std::cout << "Optimal solution x*: " << x_opt << std::endl;
                return;
            }
        }
        while (iteration < max_iterations)
        {
            // Step 1: Minimize L(x, lambda) with respect to x
            x_t = Min_Lagrangien_function(previous_lambda);

            // Step 2: Update lambda
            lambda_t = update_lambda(x_t, previous_lambda);
            std::cout << "Iteration " << iteration << ": x = " << x_t << ", lambda = " << lambda_t << std::endl;

            // Check for convergence
            if (std::abs(lambda_t - previous_lambda) < epsilon)
            {
                break;
            }
            previous_lambda = lambda_t;
            iteration++;
        }

        x_opt = x_t;
        lambda_opt = lambda_t;
    }

    void display_solution()
    {
        std::cout << "Dual Ascent Solution for " << name << ":" << std::endl;
        std::cout << "Optimal solution x*: " << x_opt << std::endl;
        std::cout << "Optimal Lagrange multiplier lambda*: " << lambda_opt << std::endl;
    }
};