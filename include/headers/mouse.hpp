#pragma once

#ifndef mouse_hpp
#define mouse_hpp

#include <math.h>   
#include <iostream>

// MOUSE-RELATED FUNCTIONS
// check if mouse is in the triangle by using piecewise inequality using slope of triangle and treating the screen as a graph
bool checkIfMouseIsInTriangle(int mouseX, int mouseY, int side_length, int referenceX, int referenceY);

#endif /* mouse_hpp */