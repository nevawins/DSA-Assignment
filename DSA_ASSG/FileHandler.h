#pragma once
#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include "Dictionary.h"
#include "Actor.h"
#include "Movie.h"

class FileHandler {
private:
    const std::string ACTORS_FILE;
    const std::string MOVIES_FILE;
    const std::string CAST_FILE;

public:
    FileHandler(const std::string& actorsFile = "actors.csv",
        const std::string& moviesFile = "movies.csv",
        const std::string& castFile = "cast.csv");

    void loadActors(Dictionary<int, Actor>& actors);
    void loadMovies(Dictionary<int, Movie>& movies);
    void loadCast(Dictionary<int, LinkedList<int>>& cast);

    void saveActors(const Dictionary<int, Actor>& actors);
    void saveMovies(const Dictionary<int, Movie>& movies);
    void saveCast(const Dictionary<int, LinkedList<int>>& cast);
};

#endif // FILE_HANDLER_H

