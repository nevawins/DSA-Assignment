#pragma once
#ifndef MOVIE_H
#define MOVIE_H

#include <string>

struct Movie {
    int id;
    std::string title;
    std::string plot;
    int year;
};

#endif // MOVIE_H