#include "MovieSystem.h"
#include <iostream>
#include <fstream>

MovieSystem::MovieSystem()
    : actors(100), movies(100), cast(100),
    fileHandler("actors.csv", "movies.csv", "cast.csv") {
}


// a. Add new actor
void MovieSystem::addActor() {
    int id, birthYear;
    char name[50];

    std::cout << "Enter Actor ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter Actor Name: ";
    std::cin.getline(name, 50);

    std::cout << "Enter Actor Birth Year: ";
    std::cin >> birthYear;

    if (actors.find(id)) {
        std::cout << "Error: An actor with this ID already exists.\n";
        return;
    }

    Actor actor;
    actor.id = id;
    actor.name = name;
    actor.birthYear = birthYear;

    actors.insert(id, actor);
    std::cout << "Actor added successfully!\n";
}

// b. Add new movie
void MovieSystem::addMovie() {
    int id, year;
    char title[50], plot[200];

    std::cout << "Enter Movie ID: ";
    std::cin >> id;
    std::cin.ignore();

    std::cout << "Enter Movie Title: ";
    std::cin.getline(title, 50);

    std::cout << "Enter Movie Plot: ";
    std::cin.getline(plot, 200);

    std::cout << "Enter Movie Release Year: ";
    std::cin >> year;

    if (movies.find(id)) {
        std::cout << "Error: A movie with this ID already exists.\n";
        return;
    }

    Movie movie;
    movie.id = id;
    movie.title = title;
    movie.plot = plot;
    movie.year = year;

    movies.insert(id, movie);
    std::cout << "Movie added successfully!\n";
}

// c. Add an actor to a movie
void MovieSystem::addActorToMovie() {
    int actorId, movieId;
    std::cout << "Enter Actor ID: ";
    std::cin >> actorId;
    std::cout << "Enter Movie ID: ";
    std::cin >> movieId;

    if (!actors.find(actorId)) {
        std::cout << "Error: Actor not found.\n";
        return;
    }

    if (!movies.find(movieId)) {
        std::cout << "Error: Movie not found.\n";
        return;
    }

    LinkedList<int>* actorList = cast.find(movieId);
    if (!actorList) {
        LinkedList<int> newList;
        newList.append(actorId);
        cast.insert(movieId, newList);
    }
    else {
        actorList->append(actorId);
    }

    std::cout << "Actor added to movie successfully!\n";
}

// d. Update actor details
void MovieSystem::updateActorDetails() {
    int id, birthYear;
    char name[50];

    std::cout << "Enter Actor ID to update: ";
    std::cin >> id;

    Actor* actor = actors.find(id);
    if (!actor) {
        std::cout << "Error: Actor not found.\n";
        return;
    }

    std::cout << "Enter new Actor Name: ";
    std::cin.ignore();
    std::cin.getline(name, 50);

    std::cout << "Enter new Actor Birth Year: ";
    std::cin >> birthYear;

    actor->name = name;
    actor->birthYear = birthYear;

    std::cout << "Actor details updated successfully!\n";
}

// d. Update movie details
void MovieSystem::updateMovieDetails() {
    int id, year;
    char title[50], plot[200];

    std::cout << "Enter Movie ID to update: ";
    std::cin >> id;

    Movie* movie = movies.find(id);
    if (!movie) {
        std::cout << "Error: Movie not found.\n";
        return;
    }

    std::cout << "Enter new Movie Title: ";
    std::cin.ignore();
    std::cin.getline(title, 50);

    std::cout << "Enter new Movie Plot: ";
    std::cin.getline(plot, 200);

    std::cout << "Enter new Movie Release Year: ";
    std::cin >> year;

    movie->title = title;
    movie->plot = plot;
    movie->year = year;

    std::cout << "Movie details updated successfully!\n";
}

// e. Display actors by age range
void MovieSystem::displayActorsByAgeRange(int minAge, int maxAge) {
    int currentYear = 2025;
    const int MAX_ACTORS = 100; // Maximum number of actors to display
    Actor* actorsInRange = new Actor[MAX_ACTORS];
    int count = 0;

    // Collect actors within the age range
    for (int i = 0; i < actors.getTableSize(); ++i) {
        auto current = actors.getTable()[i];
        while (current) {
            int age = currentYear - current->value.birthYear;
            if (age >= minAge && age <= maxAge) {
                actorsInRange[count] = current->value;
                count++;
                if (count >= MAX_ACTORS) break; // Prevent overflow
            }
            current = current->next;
        }
    }

    // Selection sort by age (ascending order)
    for (int i = 0; i < count - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < count; ++j) {
            if ((currentYear - actorsInRange[j].birthYear) < (currentYear - actorsInRange[minIndex].birthYear)) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Actor temp = actorsInRange[i];
            actorsInRange[i] = actorsInRange[minIndex];
            actorsInRange[minIndex] = temp;
        }
    }

    // Display actors
    std::cout << "\nActors aged " << minAge << " to " << maxAge << ":\n";
    for (int i = 0; i < count; ++i) {
        int age = currentYear - actorsInRange[i].birthYear;
        std::cout << actorsInRange[i].name << " (Age: " << age << ")\n";
    }

    delete[] actorsInRange; // Free memory
}

// f. Display recent movies
void MovieSystem::displayRecentMovies() {
    const int currentYear = 2025;
    const int yearsToLookBack = 3;
    const int startYear = currentYear - yearsToLookBack;
    const int MAX_MOVIES = 100; // Maximum number of movies to display
    Movie* recentMovies = new Movie[MAX_MOVIES];
    int count = 0;

    // Collect movies from the past 3 years
    for (int i = 0; i < movies.getTableSize(); ++i) {
        auto current = movies.getTable()[i];
        while (current) {
            if (current->value.year >= startYear) {
                recentMovies[count] = current->value;
                count++;
                if (count >= MAX_MOVIES) break; // Prevent overflow
            }
            current = current->next;
        }
    }

    // Selection sort by year (ascending order)
    for (int i = 0; i < count - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < count; ++j) {
            if (recentMovies[j].year < recentMovies[minIndex].year) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Movie temp = recentMovies[i];
            recentMovies[i] = recentMovies[minIndex];
            recentMovies[minIndex] = temp;
        }
    }

    // Display movies
    std::cout << "\nMovies from " << startYear << " to " << currentYear << ":\n";
    for (int i = 0; i < count; ++i) {
        std::cout << recentMovies[i].year << ": " << recentMovies[i].title << "\n";
    }

    delete[] recentMovies; // Free memory
}

// g. Display movies for actors
void MovieSystem::displayMoviesForActor(int actorId) {
    Actor* actor = actors.find(actorId);
    if (!actor) {
        std::cout << "Actor not found.\n";
        return;
    }

    const int MAX_MOVIES = 100; // Maximum number of movies to display
    Movie** moviesForActor = new Movie * [MAX_MOVIES];
    int count = 0;

    // Collect movies for the actor
    for (int i = 0; i < cast.getTableSize(); ++i) {
        auto current = cast.getTable()[i];
        while (current) {
            auto actorList = current->value.getHead();
            while (actorList) {
                if (actorList->data == actorId) {
                    Movie* movie = movies.find(current->key);
                    if (movie) {
                        moviesForActor[count] = movie;
                        count++;
                        if (count >= MAX_MOVIES) break; // Prevent overflow
                    }
                }
                actorList = actorList->next;
            }
            current = current->next;
        }
    }

    // Selection sort by title (alphabetical order)
    for (int i = 0; i < count - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < count; ++j) {
            if (moviesForActor[j]->title < moviesForActor[minIndex]->title) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Movie* temp = moviesForActor[i];
            moviesForActor[i] = moviesForActor[minIndex];
            moviesForActor[minIndex] = temp;
        }
    }

    // Display movies
    std::cout << "\nMovies starring " << actor->name << ":\n";
    for (int i = 0; i < count; ++i) {
        std::cout << moviesForActor[i]->title << "\n";
    }

    delete[] moviesForActor; // Free memory
}

// h. Display actors in a movie
void MovieSystem::displayActorsInMovie(int movieId) {
    Movie* movie = movies.find(movieId);
    if (!movie) {
        std::cout << "Movie not found.\n";
        return;
    }

    const int MAX_ACTORS = 100; // Maximum number of actors to display
    Actor** actorsInMovie = new Actor * [MAX_ACTORS];
    int count = 0;

    // Collect actors in the movie
    LinkedList<int>* actorList = cast.find(movieId);
    if (actorList) {
        auto current = actorList->getHead();
        while (current) {
            Actor* actor = actors.find(current->data);
            if (actor) {
                actorsInMovie[count] = actor;
                count++;
                if (count >= MAX_ACTORS) break; // Prevent overflow
            }
            current = current->next;
        }
    }

    // Selection sort by name (alphabetical order)
    for (int i = 0; i < count - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < count; ++j) {
            if (actorsInMovie[j]->name < actorsInMovie[minIndex]->name) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Actor* temp = actorsInMovie[i];
            actorsInMovie[i] = actorsInMovie[minIndex];
            actorsInMovie[minIndex] = temp;
        }
    }

    // Display actors
    std::cout << "\nActors in \"" << movie->title << "\":\n";
    for (int i = 0; i < count; ++i) {
        std::cout << actorsInMovie[i]->name << "\n";
    }

    delete[] actorsInMovie; // Free memory
}

// i. Display actor network
void MovieSystem::displayActorNetwork(int actorId) {
    Actor* sourceActor = actors.find(actorId);
    if (!sourceActor) {
        std::cout << "Actor not found.\n";
        return;
    }

    const int MAX_CONNECTIONS = 100; // Maximum number of connections to display
    Actor** directConnections = new Actor * [MAX_CONNECTIONS];
    Actor** indirectConnections = new Actor * [MAX_CONNECTIONS];
    int directCount = 0, indirectCount = 0;

    // Find direct connections
    for (int i = 0; i < cast.getTableSize(); ++i) {
        auto current = cast.getTable()[i];
        while (current) {
            auto actorList = current->value.getHead();
            while (actorList) {
                if (actorList->data == actorId) {
                    auto coActors = current->value.getHead();
                    while (coActors) {
                        if (coActors->data != actorId) {
                            Actor* coActor = actors.find(coActors->data);
                            if (coActor) {
                                directConnections[directCount] = coActor;
                                directCount++;
                                if (directCount >= MAX_CONNECTIONS) break; // Prevent overflow
                            }
                        }
                        coActors = coActors->next;
                    }
                }
                actorList = actorList->next;
            }
            current = current->next;
        }
    }

    // Find indirect connections
    for (int i = 0; i < directCount; ++i) {
        for (int j = 0; j < cast.getTableSize(); ++j) {
            auto current = cast.getTable()[j];
            while (current) {
                auto actorList = current->value.getHead();
                while (actorList) {
                    if (actorList->data != actorId) {
                        Actor* indirectActor = actors.find(actorList->data);
                        if (indirectActor) {
                            bool isDirect = false;
                            for (int k = 0; k < directCount; ++k) {
                                if (directConnections[k] == indirectActor) {
                                    isDirect = true;
                                    break;
                                }
                            }
                            if (!isDirect) {
                                indirectConnections[indirectCount] = indirectActor;
                                indirectCount++;
                                if (indirectCount >= MAX_CONNECTIONS) break; // Prevent overflow
                            }
                        }
                    }
                    actorList = actorList->next;
                }
                current = current->next;
            }
        }
    }

    // Selection sort by name (alphabetical order)
    for (int i = 0; i < directCount - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < directCount; ++j) {
            if (std::string(directConnections[j]->name) < std::string(directConnections[minIndex]->name)) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Actor* temp = directConnections[i];
            directConnections[i] = directConnections[minIndex];
            directConnections[minIndex] = temp;
        }
    }

    for (int i = 0; i < indirectCount - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < indirectCount; ++j) {
            if (indirectConnections[j]->name < indirectConnections[minIndex]->name) {
                minIndex = j;
            }
        }
        if (minIndex != i) {
            Actor* temp = indirectConnections[i];
            indirectConnections[i] = indirectConnections[minIndex];
            indirectConnections[minIndex] = temp;
        }
    }

    // Display connections
    std::cout << "\nNetwork for " << sourceActor->name << ":\n";
    std::cout << "Direct Connections:\n";
    for (int i = 0; i < directCount; ++i) {
        std::cout << "- " << directConnections[i]->name << "\n";
    }

    std::cout << "\nIndirect Connections:\n";
    for (int i = 0; i < indirectCount; ++i) {
        std::cout << "- " << indirectConnections[i]->name << "\n";
    }

    delete[] directConnections; // Free memory
    delete[] indirectConnections; // Free memory
}

void MovieSystem::menu() {
    // First load the data
    try {
        fileHandler.loadActors(actors);
        fileHandler.loadMovies(movies);
        fileHandler.loadCast(cast);
        std::cout << "Data loaded successfully.\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << "Warning: " << e.what() << " Starting with empty database.\n";
    }

    int choice = 0;
    do {
        std::cout << "\nAdministrator Menu:\n";
        std::cout << "1. Add Actor\n";
        std::cout << "2. Add Movie\n";
        std::cout << "3. Add Actor to Movie\n";
        std::cout << "4. Update Actor Details\n";
        std::cout << "5. Update Movie Details\n";
        std::cout << "6. Display Actors in Age Range\n";
        std::cout << "7. Display Recent Movies\n";
        std::cout << "8. Display Movies for Actor\n";
        std::cout << "9. Display Actors in Movie\n";
        std::cout << "10. Display Actor Network\n";
        std::cout << "11. Exit\n";
        std::cout << "Enter your choice: ";

        if (!(std::cin >> choice)) {
            std::cin.clear(); // Clear error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Discard invalid input
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: addActor(); break;
        case 2: addMovie(); break;
        case 3: addActorToMovie(); break;
        case 4: updateActorDetails(); break;
        case 5: updateMovieDetails(); break;
        case 6: {
            int minAge, maxAge;
            std::cout << "Enter minimum age: ";
            std::cin >> minAge;
            std::cout << "Enter maximum age: ";
            std::cin >> maxAge;
            displayActorsByAgeRange(minAge, maxAge);
            break;
        }
        case 7: displayRecentMovies(); break;
        case 8: {
            int actorId;
            std::cout << "Enter actor ID: ";
            std::cin >> actorId;
            displayMoviesForActor(actorId);
            break;
        }
        case 9: {
            int movieId;
            std::cout << "Enter movie ID: ";
            std::cin >> movieId;
            displayActorsInMovie(movieId);
            break;
        }
        case 10: {
            int actorId;
            std::cout << "Enter actor ID: ";
            std::cin >> actorId;
            displayActorNetwork(actorId);
            break;
        }
        case 11:
            // Save data before exiting
            try {
                fileHandler.saveActors(actors);
                fileHandler.saveMovies(movies);
                fileHandler.saveCast(cast);
                std::cout << "Data saved successfully.\n";
            }
            catch (const std::runtime_error& e) {
                std::cout << "Error saving data: " << e.what() << "\n";
            }
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 11.\n";
        }
    } while (choice != 11);
}