#ifndef MOVIE_SYSTEM_H
#define MOVIE_SYSTEM_H

#include <string>

class MovieSystem {
private:
    struct Actor {
        int id;
        char name[100];
        int birthYear;
        Actor* next;
    };

    struct Movie {
        int id;
        char title[100];
        char plot[2048];
        int year;
        Actor* actors;
        Movie* next;
    };
    struct Cast {
        int person_id;
        int movie_id;
        Cast* next;
    };

    Actor* actorHead;
    Movie* movieHead;
    Cast* castHead;
    const std::string ACTORS_FILE;
    const std::string MOVIES_FILE;
    const std::string CAST_FILE;

    // Private helper methods
    Actor* createActor(int id, const char* name, int birthYear);
    Movie* createMovie(int id, const char* title, const char* plot, int year);
    void loadActors();
    void loadMovies();
    void linkActorsToMovies();
    void saveActors();
    void saveMovies();

public:
    // Constructor to initialize member variables
    MovieSystem();

    // Main menu and data operations
    void menu();
    void loadData();
    void saveData();

    // Actor operations
    void addActor();
    void updateActorDetails();

    // Movie operations
    void addMovie();
    void updateMovieDetails();
    void addActorToMovie();

    // part ii
    void displayActorsByAgeRange(int minAge, int maxAge);
    void displayRecentMovies();
    void displayMoviesForActor(int actorId);
    void displayActorsInMovie(int movieId);
    void displayActorNetwork(int actorId);
};

#endif // MOVIE_SYSTEM_H