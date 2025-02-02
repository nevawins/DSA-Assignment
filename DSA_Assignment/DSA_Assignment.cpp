#include "MovieSystem.h"
#include <iostream>

void displayActorsByAge(MovieSystem& system);
void displayMoviesActorStarredIn(MovieSystem& system);
void displayActorStarringInMovie(MovieSystem& system);
void displayActorConnections(MovieSystem& system);


int main() {
    MovieSystem system;

    // Load all data
    system.readActorsFromFile("actors.csv");
    system.readMoviesFromFile("movies.csv");
    system.readCastFromFile("cast.csv");

    // Display loaded data for testing
    system.displayAllData();

    // part e) Display actors by age, user input age range
    //displayActorsByAge(system);

    // part f)
    //system.displayRecentMovies();

    // part g)
    //displayMoviesActorStarredIn(system);

    // part h)
    //displayActorStarringInMovie(system);

    // part i)
    displayActorConnections(system);

    return 0;
}

void displayActorConnections(MovieSystem& system) {
    int actorId;
    std::cout << "Enter actor ID: ";
    std::cin >> actorId;
    system.displayActorNetwork(actorId);
}


void displayActorStarringInMovie(MovieSystem& system) {
    int movieId;
    std::cout << "Enter movie ID: ";
    std::cin >> movieId;
    system.displayActorsInMovie(movieId);
}


void displayMoviesActorStarredIn(MovieSystem& system) {
    int actorId;
    std::cout << "Enter actor ID: ";
    std::cin >> actorId;
    system.displayMoviesForActor(actorId);
}

void displayActorsByAge(MovieSystem& system) {
    int minAge, maxAge;
    std::cout << "Enter minimum age: ";
    std::cin >> minAge;
    std::cout << "Enter maximum age: ";
    std::cin >> maxAge;

    system.displayActorsByAgeRange(minAge, maxAge);
}