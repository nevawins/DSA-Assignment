#pragma once
#ifndef MOVIE_SYSTEM_H
#define MOVIE_SYSTEM_H

#include "Dictionary.h"
#include "FileHandler.h"
#include "Actor.h"
#include "Movie.h"
#include "Cast.h"

class MovieSystem {
private:
    Dictionary<int, Actor> actors; // Dictionary for actors
    Dictionary<int, Movie> movies; // Dictionary for movies
    Dictionary<int, LinkedList<int>> cast; // Dictionary for cast relationships
    FileHandler fileHandler;

public:
    // Only declare the constructor here, don't define it
    MovieSystem();
    // Remove the destructor if you don't need special cleanup

    void menu();
    void addActor();
    void addMovie();
    void addActorToMovie();
    void updateActorDetails();
    void updateMovieDetails();
    void displayActorsByAgeRange(int minAge, int maxAge);
    void displayRecentMovies();
    void displayMoviesForActor(int actorId);
    void displayActorsInMovie(int movieId);
    void displayActorNetwork(int actorId);
};

#endif // MOVIE_SYSTEM_H