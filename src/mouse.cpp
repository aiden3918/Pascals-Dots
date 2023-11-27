#include <math.h>
#include <iostream>
#include <mouse.hpp>

// MOUSE-RELATED FUNCTIONS

// check if mouse is in the triangle by using piecewise inequality using slope of triangle and treating the screen as a graph
bool checkIfMouseIsInTriangle(int mouseX, int mouseY, int side_length, int referenceX, int referenceY) {
    // due to SDL's origin being on the top left, y increases as it goes down, x increases as it goes right
    // slopes, y-intercepts, and inequalities are flipped compared to the cartesian plane

    // b = y - mx
    int leftSideYIntercept = int(referenceY + (sqrt(3) * referenceX));
    int rightSideYIntercept = int(referenceY - (sqrt(3) * referenceX));
    std::cout << "Left hand side y-int: " << leftSideYIntercept << std::endl;
    std::cout << "Right hand side y-int: " << rightSideYIntercept << std::endl;

    if (mouseY > referenceY + int(sqrt(3) / 2 * side_length)) return false; // mouse cannot be under or over triangle
    // right side and left side of triangle are checked with different inequalities
    if (mouseX < referenceX) {
        return mouseY > int((-1 * sqrt(3) * mouseX) + leftSideYIntercept);
    } else {
        return mouseY > int((sqrt(3) * mouseX) + rightSideYIntercept);
    }
}