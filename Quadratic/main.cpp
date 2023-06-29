#include "functions.h"

int main()
{
    //all_unit_tests_for_quadratic ();

    double a = NAN;
    double b = NAN;
    double c = NAN;

    int input_check = scan_coefficients(&a, &b, &c);
    if (input_check == UNCORRECT_INPUT)
    {
        printf ("Uncorrect input!\n");
        return 0;
    }

    assert(std::isfinite(a));
    assert(std::isfinite(b));
    assert(std::isfinite(c));

    double x1 = NAN;
    double x2 = NAN;
    int nSolutions = -2;

    solve_all (a, b, c, &x1, &x2, &nSolutions);

    show_roots(nSolutions, x1, x2);

    return 0;
}
