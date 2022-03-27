//
// Created by Ruslan Abdullin on 27.03.2022.
//

#include<sstream>
#include<fstream>
#include<vector>
#include<iostream>

using namespace std;

#define array vector<vector<float>>
#define push(a, b) output.emplace_back(a, b)

#ifndef SSAD_APPROXIMATION_H

    array read();
    void write(const vector<pair<string, array>> &output);
    array multiplication(array a, array b);
    array transpose(const array &a);
    array inverse(array m);
    array getX(array a, array b);

#define SSAD_APPROXIMATION_H

#endif //SSAD_APPROXIMATION_H
