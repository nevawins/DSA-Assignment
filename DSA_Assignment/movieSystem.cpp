#include "MovieSystem.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

MovieSystem::MovieSystem()
    : actorHead(nullptr),
    movieHead(nullptr),
    ACTORS_FILE("actors.csv"),
    MOVIES_FILE("movies.csv"),
    CAST_FILE("cast.csv") {}

MovieSystem::Actor* MovieSystem::createActor(int id, const char* name, int birthYear) {
    Actor* newActor = new Actor;
    newActor->id = id;
    strcpy_s(newActor->name, sizeof(newActor->name), name);
    newActor->birthYear = birthYear;
    newActor->next = nullptr;
    return newActor;
}

MovieSystem::Movie* MovieSystem::createMovie(int id, const char* title, const char* plot, int year) {
    Movie* newMovie = new Movie;
    newMovie->id = id;
    strcpy_s(newMovie->title, sizeof(newMovie->title), title);
    strcpy_s(newMovie->plot, sizeof(newMovie->plot), plot);
    newMovie->year = year;
    newMovie->actors = nullptr;
    newMovie->next = nullptr;
    return newMovie;
}

void MovieSystem::loadActors() {
    std::ifstream file(ACTORS_FILE);
    if (!file.is_open()) {
        std::cout << "Error: Could not open actors file.\n";
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, birthYearStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, birthYearStr, ',');

        Actor* newActor = createActor(std::stoi(idStr), name.c_str(), std::stoi(birthYearStr));
        newActor->next = actorHead;
        actorHead = newActor;
    }
    file.close();
}

void MovieSystem::loadMovies() {
    std::ifstream file(MOVIES_FILE);
    if (!file.is_open()) {
        std::cout << "Error: Could not open movies file.\n";
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, plot, yearStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, title, ',');
        std::getline(ss, plot, ',');
        std::getline(ss, yearStr, ',');

        Movie* newMovie = createMovie(std::stoi(idStr), title.c_str(), plot.c_str(), std::stoi(yearStr));
        newMovie->next = movieHead;
        movieHead = newMovie;
    }
    file.close();
}

void MovieSystem::linkActorsToMovies() {
    std::ifstream file(CAST_FILE);
    if (!file.is_open()) {
        std::cout << "Error: Could not open cast file.\n";
        return;
    }
    std::string line;
    std::getline(file, line);
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string actorIdStr, movieIdStr;
        std::getline(ss, actorIdStr, ',');
        std::getline(ss, movieIdStr, ',');

        int actorId = std::stoi(actorIdStr);
        int movieId = std::stoi(movieIdStr);

        Actor* actor = actorHead;
        while (actor && actor->id != actorId) {
            actor = actor->next;
        }
        if (!actor) continue;

        Movie* movie = movieHead;
        while (movie && movie->id != movieId) {
            movie = movie->next;
        }
        if (!movie) continue;

        Actor* actorCopy = createActor(actor->id, actor->name, actor->birthYear);
        actorCopy->next = movie->actors;
        movie->actors = actorCopy;
    }
    file.close();
}

void MovieSystem::saveActors() {
    std::ofstream file(ACTORS_FILE);
    if (!file.is_open()) {
        std::cout << "Error: Could not open actors file for writing.\n";
        return;
    }
    file << "id,name,birth\n";
    Actor* current = actorHead;
    while (current) {
        file << current->id << ",\"" << current->name << "\"," << current->birthYear << "\n";
        current = current->next;
    }
    file.close();
}

void MovieSystem::saveMovies() {
    std::ofstream file(MOVIES_FILE);
    if (!file.is_open()) {
        std::cout << "Error: Could not open movies file for writing.\n";
        return;
    }
    file << "id,title,plot,year\n";
    Movie* current = movieHead;
    while (current) {
        file << current->id << ",\"" << current->title << "\",\"" << current->plot << "\","
            << current->year << "\n";
        current = current->next;
    }
    file.close();
}

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

    Actor* current = actorHead;
    while (current) {
        if (current->id == id) {
            std::cout << "Error: An actor with this ID already exists.\n";
            return;
        }
        current = current->next;
    }

    Actor* newActor = createActor(id, name, birthYear);
    newActor->next = actorHead;
    actorHead = newActor;

    std::cout << "Actor added successfully!\n";
}

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

    Movie* current = movieHead;
    while (current) {
        if (current->id == id) {
            std::cout << "Error: A movie with this ID already exists.\n";
            return;
        }
        current = current->next;
    }

    Movie* newMovie = createMovie(id, title, plot, year);
    newMovie->next = movieHead;
    movieHead = newMovie;

    std::cout << "Movie added successfully!\n";
}

void MovieSystem::addActorToMovie() {
    int actorId, movieId;

    std::cout << "Enter Actor ID: ";
    std::cin >> actorId;
    std::cout << "Enter Movie ID: ";
    std::cin >> movieId;

    Actor* actor = actorHead;
    while (actor && actor->id != actorId) {
        actor = actor->next;
    }
    if (!actor) {
        std::cout << "Error: Actor not found.\n";
        return;
    }

    Movie* movie = movieHead;
    while (movie && movie->id != movieId) {
        movie = movie->next;
    }
    if (!movie) {
        std::cout << "Error: Movie not found.\n";
        return;
    }

    Actor* actorCopy = createActor(actor->id, actor->name, actor->birthYear);
    actorCopy->next = movie->actors;
    movie->actors = actorCopy;

    std::cout << "Actor added to movie successfully!\n";
}

void MovieSystem::updateActorDetails() {
    int id, birthYear;
    char name[50];

    std::cout << "Enter Actor ID to update: ";
    std::cin >> id;

    Actor* actor = actorHead;
    while (actor && actor->id != id) {
        actor = actor->next;
    }
    if (!actor) {
        std::cout << "Error: Actor not found.\n";
        return;
    }

    std::cout << "Enter new Actor Name: ";
    std::cin.ignore();
    std::cin.getline(name, 50);

    std::cout << "Enter new Actor Birth Year: ";
    std::cin >> birthYear;

    strcpy_s(actor->name, sizeof(actor->name), name);
    actor->birthYear = birthYear;

    std::cout << "Actor details updated successfully!\n";
}

void MovieSystem::updateMovieDetails() {
    int id, year;
    char title[50], plot[200];

    std::cout << "Enter Movie ID to update: ";
    std::cin >> id;

    Movie* movie = movieHead;
    while (movie && movie->id != id) {
        movie = movie->next;
    }
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

    strcpy_s(movie->title, sizeof(movie->title), title);
    strcpy_s(movie->plot, sizeof(movie->plot), plot);
    movie->year = year;

    std::cout << "Movie details updated successfully!\n";
}

void MovieSystem::loadData() {
    loadActors();
    loadMovies();
    linkActorsToMovies();
    std::cout << "Data loaded successfully!\n";
}

void MovieSystem::saveData() {
    saveActors();
    saveMovies();
    std::cout << "Data saved successfully!\n";
}

void MovieSystem::displayActorsByAgeRange(int minAge, int maxAge) {
    int currentYear = 2025;
    const int MAX_ACTORS = 100;
    Actor* actorsInRange = new Actor[MAX_ACTORS];
    int count = 0;

    // Get actors in the age range from the stored linked list
    Actor* current = actorHead;  // Changed from ActorNode* to Actor*
    while (current != nullptr) {
        int age = currentYear - current->birthYear;  // Changed from birth to birthYear
        if (age >= minAge && age <= maxAge) {
            actorsInRange[count] = *current;  // Copy the entire Actor struct
            count++;
        }
        current = current->next;
    }

    // Sort actors by age (bubble sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if ((currentYear - actorsInRange[j].birthYear) >
                (currentYear - actorsInRange[j + 1].birthYear)) {
                // Swap actors
                Actor temp = actorsInRange[j];
                actorsInRange[j] = actorsInRange[j + 1];
                actorsInRange[j + 1] = temp;
            }
        }
    }

    // Display the sorted results
    std::cout << "\nActors aged " << minAge << " to " << maxAge << ":\n";
    for (int i = 0; i < count; i++) {
        int age = currentYear - actorsInRange[i].birthYear;
        std::cout << actorsInRange[i].name << " (Age: " << age << ")\n";
    }

    // Clean up
    delete[] actorsInRange;
}

void MovieSystem::displayRecentMovies() {
    const int currentYear = 2025;
    const int yearsToLookBack = 3;
    const int startYear = currentYear - yearsToLookBack;

    // First check if we have any recent movies
    Movie* current = movieHead;
    bool foundMovies = false;
    while (current != nullptr) {
        if (current->year >= startYear) {
            foundMovies = true;
            break;
        }
        current = current->next;
    }

    if (!foundMovies) {
        std::cout << "No movies found in the past " << yearsToLookBack << " years." << std::endl;
        return;
    }

    // Create a new sorted linked list for recent movies
    struct TempMovieNode {
        Movie* moviePtr;
        TempMovieNode* next;
    };
    TempMovieNode* sortedHead = nullptr;

    // Go through original list and insert into sorted list
    current = movieHead;
    while (current != nullptr) {
        if (current->year >= startYear) {
            // Create new node
            TempMovieNode* newNode = new TempMovieNode;
            newNode->moviePtr = current;    // Changed from &(current->data)

            // Insert in sorted position
            if (sortedHead == nullptr || sortedHead->moviePtr->year > current->year) {
                // Insert at beginning
                newNode->next = sortedHead;
                sortedHead = newNode;
            }
            else {
                // Find position to insert
                TempMovieNode* sortedCurrent = sortedHead;
                while (sortedCurrent->next != nullptr &&
                    sortedCurrent->next->moviePtr->year <= current->year) {
                    sortedCurrent = sortedCurrent->next;
                }
                newNode->next = sortedCurrent->next;
                sortedCurrent->next = newNode;
            }
        }
        current = current->next;
    }

    // Display sorted results
    std::cout << "\nMovies from " << startYear << " to " << currentYear << ":\n";
    std::cout << "----------------------------------------\n";
    TempMovieNode* displayNode = sortedHead;
    while (displayNode != nullptr) {
        std::cout << displayNode->moviePtr->year << ": "
            << displayNode->moviePtr->title << std::endl;
        TempMovieNode* temp = displayNode;
        displayNode = displayNode->next;
        delete temp;  // Clean up as we go
    }
}

void MovieSystem::displayMoviesForActor(int actorId) {
    // First verify actor exists
    Actor* actor = actorHead;
    while (actor != nullptr && actor->id != actorId) {
        actor = actor->next;
    }
    if (actor == nullptr) {
        std::cout << "Actor not found." << std::endl;
        return;
    }

    // Create a temporary linked list to store movies
    struct TempMovieNode {
        Movie* moviePtr;
        TempMovieNode* next;
    };
    TempMovieNode* sortedHead = nullptr;

    // Find all movies this actor is in
    Movie* currentMovie = movieHead;
    while (currentMovie != nullptr) {
        // Check if actor is in this movie's cast
        Actor* castMember = currentMovie->actors;
        while (castMember != nullptr) {
            if (castMember->id == actorId) {
                // Create new node
                TempMovieNode* newNode = new TempMovieNode;
                newNode->moviePtr = currentMovie;

                // Insert in alphabetically sorted position
                if (sortedHead == nullptr ||
                    strcmp(sortedHead->moviePtr->title, currentMovie->title) > 0) {
                    // Insert at beginning
                    newNode->next = sortedHead;
                    sortedHead = newNode;
                }
                else {
                    // Find position to insert
                    TempMovieNode* current = sortedHead;
                    while (current->next != nullptr &&
                        strcmp(current->next->moviePtr->title, currentMovie->title) <= 0) {
                        current = current->next;
                    }
                    newNode->next = current->next;
                    current->next = newNode;
                }
                break;  // Found the actor in this movie, no need to check other cast members
            }
            castMember = castMember->next;
        }
        currentMovie = currentMovie->next;
    }

    // Display actor name and their movies
    std::cout << "\nMovies starring " << actor->name << ":\n";
    std::cout << "----------------------------------------\n";

    if (sortedHead == nullptr) {
        std::cout << "No movies found for this actor." << std::endl;
    }
    else {
        TempMovieNode* current = sortedHead;
        while (current != nullptr) {
            std::cout << current->moviePtr->title << " (" << current->moviePtr->year << ")" << std::endl;
            TempMovieNode* temp = current;
            current = current->next;
            delete temp;  // Clean up as we go
        }
    }
}

void MovieSystem::displayActorsInMovie(int movieId) {
    // First verify movie exists
    Movie* movie = movieHead;
    while (movie != nullptr && movie->id != movieId) {
        movie = movie->next;
    }
    if (movie == nullptr) {
        std::cout << "Movie not found." << std::endl;
        return;
    }

    // Create a temporary linked list to store actors in sorted order
    struct TempActorNode {
        Actor* actorPtr;
        TempActorNode* next;
    };
    TempActorNode* sortedHead = nullptr;

    // Go through the movie's actor list
    Actor* currentActor = movie->actors;
    while (currentActor != nullptr) {
        // Create new node
        TempActorNode* newNode = new TempActorNode;
        newNode->actorPtr = currentActor;

        // Insert in alphabetically sorted position
        if (sortedHead == nullptr ||
            strcmp(sortedHead->actorPtr->name, currentActor->name) > 0) {
            // Insert at beginning
            newNode->next = sortedHead;
            sortedHead = newNode;
        }
        else {
            // Find position to insert
            TempActorNode* current = sortedHead;
            while (current->next != nullptr &&
                strcmp(current->next->actorPtr->name, currentActor->name) <= 0) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
        currentActor = currentActor->next;
    }

    // Display movie title and its actors
    std::cout << "\nActors in \"" << movie->title << "\":\n";
    std::cout << "----------------------------------------\n";

    if (sortedHead == nullptr) {
        std::cout << "No actors found for this movie." << std::endl;
    }
    else {
        TempActorNode* current = sortedHead;
        while (current != nullptr) {
            std::cout << current->actorPtr->name << " (Birth Year: "
                << current->actorPtr->birthYear << ")" << std::endl;
            TempActorNode* temp = current;
            current = current->next;
            delete temp;  // Clean up as we go
        }
    }
}

void MovieSystem::displayActorNetwork(int actorId) {
    // First verify actor exists
    Actor* sourceActor = actorHead;
    while (sourceActor != nullptr && sourceActor->id != actorId) {
        sourceActor = sourceActor->next;
    }
    if (sourceActor == nullptr) {
        std::cout << "Actor not found." << std::endl;
        return;
    }

    // Temporary node to store connected actors
    struct ConnectedActor {
        Actor* actorPtr;
        bool isDirect;  // true if direct connection, false if indirect
        ConnectedActor* next;
    };
    ConnectedActor* sortedHead = nullptr;

    // First, find all movies that have the source actor
    Movie* currentMovie = movieHead;
    while (currentMovie != nullptr) {
        Actor* actorInMovie = currentMovie->actors;
        bool sourceActorInMovie = false;

        // Check if source actor is in this movie
        while (actorInMovie != nullptr) {
            if (actorInMovie->id == actorId) {
                sourceActorInMovie = true;
                break;
            }
            actorInMovie = actorInMovie->next;
        }

        if (sourceActorInMovie) {
            // Add all other actors in this movie as direct connections
            actorInMovie = currentMovie->actors;
            while (actorInMovie != nullptr) {
                if (actorInMovie->id != actorId) {
                    // Check if already in network
                    bool alreadyExists = false;
                    ConnectedActor* check = sortedHead;
                    while (check != nullptr) {
                        if (check->actorPtr->id == actorInMovie->id) {
                            alreadyExists = true;
                            break;
                        }
                        check = check->next;
                    }

                    if (!alreadyExists) {
                        ConnectedActor* newNode = new ConnectedActor;
                        newNode->actorPtr = actorInMovie;
                        newNode->isDirect = true;

                        // Insert alphabetically
                        if (sortedHead == nullptr ||
                            strcmp(sortedHead->actorPtr->name, actorInMovie->name) > 0) {
                            newNode->next = sortedHead;
                            sortedHead = newNode;
                        }
                        else {
                            ConnectedActor* current = sortedHead;
                            while (current->next != nullptr &&
                                strcmp(current->next->actorPtr->name, actorInMovie->name) <= 0) {
                                current = current->next;
                            }
                            newNode->next = current->next;
                            current->next = newNode;
                        }

                        // Find indirect connections through this direct connection
                        Movie* indirectMovie = movieHead;
                        while (indirectMovie != nullptr) {
                            Actor* indirectActor = indirectMovie->actors;
                            bool directActorInMovie = false;

                            // Check if direct connection is in this movie
                            while (indirectActor != nullptr) {
                                if (indirectActor->id == actorInMovie->id) {
                                    directActorInMovie = true;
                                    break;
                                }
                                indirectActor = indirectActor->next;
                            }

                            if (directActorInMovie) {
                                indirectActor = indirectMovie->actors;
                                while (indirectActor != nullptr) {
                                    if (indirectActor->id != actorId &&
                                        indirectActor->id != actorInMovie->id) {
                                        bool exists = false;
                                        ConnectedActor* checkIndirect = sortedHead;
                                        while (checkIndirect != nullptr) {
                                            if (checkIndirect->actorPtr->id == indirectActor->id) {
                                                exists = true;
                                                break;
                                            }
                                            checkIndirect = checkIndirect->next;
                                        }

                                        if (!exists) {
                                            ConnectedActor* newIndirectNode = new ConnectedActor;
                                            newIndirectNode->actorPtr = indirectActor;
                                            newIndirectNode->isDirect = false;

                                            // Insert alphabetically
                                            if (sortedHead == nullptr ||
                                                strcmp(sortedHead->actorPtr->name, indirectActor->name) > 0) {
                                                newIndirectNode->next = sortedHead;
                                                sortedHead = newIndirectNode;
                                            }
                                            else {
                                                ConnectedActor* current = sortedHead;
                                                while (current->next != nullptr &&
                                                    strcmp(current->next->actorPtr->name, indirectActor->name) <= 0) {
                                                    current = current->next;
                                                }
                                                newIndirectNode->next = current->next;
                                                current->next = newIndirectNode;
                                            }
                                        }
                                    }
                                    indirectActor = indirectActor->next;
                                }
                            }
                            indirectMovie = indirectMovie->next;
                        }
                    }
                }
                actorInMovie = actorInMovie->next;
            }
        }
        currentMovie = currentMovie->next;
    }

    // Display results
    std::cout << "\nNetwork for " << sourceActor->name << ":\n";
    std::cout << "----------------------------------------\n";

    if (sortedHead == nullptr) {
        std::cout << "No connections found." << std::endl;
    }
    else {
        std::cout << "Direct Connections:\n";
        ConnectedActor* current = sortedHead;
        bool hasDirectConnections = false;
        while (current != nullptr) {
            if (current->isDirect) {
                std::cout << "- " << current->actorPtr->name << std::endl;
                hasDirectConnections = true;
            }
            current = current->next;
        }
        if (!hasDirectConnections) {
            std::cout << "None\n";
        }

        std::cout << "\nIndirect Connections:\n";
        current = sortedHead;
        bool hasIndirectConnections = false;
        while (current != nullptr) {
            if (!current->isDirect) {
                std::cout << "- " << current->actorPtr->name << std::endl;
                hasIndirectConnections = true;
            }
            ConnectedActor* temp = current;
            current = current->next;
            delete temp;  // Clean up as we go
        }
        if (!hasIndirectConnections) {
            std::cout << "None\n";
        }
    }
}

void MovieSystem::menu() {
    loadData();
    int choice;
    do {
        std::cout << "\nAdministrator Menu:\n";
        std::cout << "1. Add Actor\n";
        std::cout << "2. Add Movie\n";
        std::cout << "3. Add Actor to Movie\n";
        std::cout << "4. Update Actor Details\n";
        std::cout << "5. Update Movie Details\n";
        std::cout << "6. Display Actors in Age Range\n";
        std::cout << "7. Display all movies made in the past 3 years\n";
        std::cout << "8. Display Movies for Actor\n";
        std::cout << "9. Display Actors in Movie\n";
        std::cout << "10. Display Actor Network\n";
        std::cout << "11. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 11.\n";  // Updated range
            continue;
        }

        switch (choice) {
        case 1:
            addActor();
            break;
        case 2:
            addMovie();
            break;
        case 3:
            addActorToMovie();
            break;
        case 4:
            updateActorDetails();
            break;
        case 5:
            updateMovieDetails();
            break;
        case 6: {
            int minAge, maxAge;
            std::cout << "Enter minimum age: ";
            std::cin >> minAge;
            std::cout << "Enter maximum age: ";
            std::cin >> maxAge;
            displayActorsByAgeRange(minAge, maxAge);
            break;
        }
        case 7:
            displayRecentMovies();
            break;
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
            saveData();
            std::cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice. Please enter a number between 1 and 11.\n";  // Updated range
        }
    } while (choice != 11);
}