#include "movieSystem.h"
#include <iostream>
#include <fstream>
#include <cstring>

MovieSystem::MovieSystem() {
    actorHead = nullptr;
    movieHead = nullptr;
    castHead = nullptr;
}

MovieSystem::~MovieSystem() {
    while (actorHead != nullptr) {
        ActorNode* temp = actorHead;
        actorHead = actorHead->next;
        delete temp;
    }
    while (movieHead != nullptr) {
        MovieNode* temp = movieHead;
        movieHead = movieHead->next;
        delete temp;
    }
    while (castHead != nullptr) {
        CastNode* temp = castHead;
        castHead = castHead->next;
        delete temp;
    }
}

void MovieSystem::addActor(const Actor& actor) {
    ActorNode* newNode = new ActorNode;
    newNode->data = actor;
    newNode->next = nullptr;

    if (actorHead == nullptr) {
        actorHead = newNode;
    }
    else {
        ActorNode* current = actorHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void MovieSystem::addMovie(const Movie& movie) {
    MovieNode* newNode = new MovieNode;
    newNode->data = movie;
    newNode->next = nullptr;

    if (movieHead == nullptr) {
        movieHead = newNode;
    }
    else {
        MovieNode* current = movieHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void MovieSystem::addCast(const Cast& cast) {
    CastNode* newNode = new CastNode;
    newNode->data = cast;
    newNode->next = nullptr;

    if (castHead == nullptr) {
        castHead = newNode;
    }
    else {
        CastNode* current = castHead;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

bool MovieSystem::readMoviesFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening movies file: " << filename << std::endl;
        return false;
    }

    char line[4096];
    char* next_token = nullptr;
    // Skip header line
    file.getline(line, 4096);

    while (file.getline(line, 4096)) {
        Movie movie;
        char* token = strtok_s(line, ",", &next_token);
        if (token != nullptr) {
            movie.id = atoi(token);
            token = strtok_s(nullptr, ",", &next_token);
            if (token != nullptr) {
                strcpy_s(movie.title, sizeof(movie.title), token);
                token = strtok_s(nullptr, ",", &next_token);
                if (token != nullptr) {
                    strcpy_s(movie.plot, sizeof(movie.plot), token);
                    token = strtok_s(nullptr, ",", &next_token);
                    if (token != nullptr) {
                        movie.year = atoi(token);
                        addMovie(movie);
                    }
                }
            }
        }
    }
    file.close();
    return true;
}

bool MovieSystem::readActorsFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening actors file: " << filename << std::endl;
        return false;
    }

    char line[1024];
    char* next_token = nullptr;
    file.getline(line, 1024);  // Skip header

    while (file.getline(line, 1024)) {
        Actor actor;
        char* token = strtok_s(line, ",", &next_token);
        if (token != nullptr) {
            actor.id = atoi(token);
            token = strtok_s(nullptr, ",", &next_token);
            if (token != nullptr) {
                // Remove quotes from name
                while (*token == ' ' || *token == '"') token++; // Skip leading spaces and quotes
                strcpy_s(actor.name, sizeof(actor.name), token);
                if (actor.name[strlen(actor.name) - 1] == '"') {
                    actor.name[strlen(actor.name) - 1] = '\0'; // Remove trailing quote
                }

                token = strtok_s(nullptr, ",", &next_token);
                if (token != nullptr) {
                    actor.birth = atoi(token);
                    addActor(actor);
                }
            }
        }
    }
    file.close();
    return true;
}

bool MovieSystem::readCastFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening cast file: " << filename << std::endl;
        return false;
    }

    char line[1024];
    char* next_token = nullptr;
    // Skip header line
    file.getline(line, 1024);

    while (file.getline(line, 1024)) {
        Cast cast;
        char* token = strtok_s(line, ",", &next_token);
        if (token != nullptr) {
            cast.person_id = atoi(token);
            token = strtok_s(nullptr, ",", &next_token);
            if (token != nullptr) {
                cast.movie_id = atoi(token);
                addCast(cast);
            }
        }
    }
    file.close();
    return true;
}

void MovieSystem::displayAllData() {
    std::cout << "\nActors:\n";
    ActorNode* currentActor = actorHead;
    while (currentActor != nullptr) {
        std::cout << currentActor->data.id << ", "
            << currentActor->data.name << ", "
            << currentActor->data.birth << std::endl;
        currentActor = currentActor->next;
    }

    std::cout << "\nMovies:\n";
    MovieNode* currentMovie = movieHead;
    while (currentMovie != nullptr) {
        std::cout << currentMovie->data.id << ", "
            << currentMovie->data.title << ", "
            << currentMovie->data.plot << ","
            << currentMovie->data.year << std::endl;
        currentMovie = currentMovie->next;
    }

    std::cout << "\nCast:\n";
    CastNode* currentCast = castHead;
    while (currentCast != nullptr) {
        std::cout << currentCast->data.person_id << ", "
            << currentCast->data.movie_id << std::endl;
        currentCast = currentCast->next;
    }
}


void MovieSystem::displayActorsByAgeRange(int minAge, int maxAge) { // prompt user and pass in minAge and maxAge as parameters

    int currentYear = 2025; //set currentYear as 2025

    const int MAX_ACTORS = 100; //array size, can adjust or change to count later
    Actor* actorsInRange = new Actor[MAX_ACTORS]; //use dynamic array to store needed data temporarily
    int count = 0;

    //get actors in the age range from the stored linked list
    ActorNode* current = actorHead; //current now points to first node
    while (current != nullptr) {
        int age = currentYear - current->data.birth;
        if (age >= minAge && age <= maxAge) {
            actorsInRange[count] = current->data;
            count++;
        }
        current = current->next;
    }

    // Sort actors by age (bubble sort since we can't use STL sort)
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if ((currentYear - actorsInRange[j].birth) >
                (currentYear - actorsInRange[j + 1].birth)) {
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
        int age = currentYear - actorsInRange[i].birth;
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
    MovieNode* current = movieHead;
    bool foundMovies = false;
    while (current != nullptr) {
        if (current->data.year >= startYear) {
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
        if (current->data.year >= startYear) {
            // Create new node
            TempMovieNode* newNode = new TempMovieNode;
            newNode->moviePtr = &(current->data);

            // Insert in sorted position
            if (sortedHead == nullptr || sortedHead->moviePtr->year > current->data.year) {
                // Insert at beginning
                newNode->next = sortedHead;
                sortedHead = newNode;
            }
            else {
                // Find position to insert
                TempMovieNode* sortedCurrent = sortedHead;
                while (sortedCurrent->next != nullptr &&
                    sortedCurrent->next->moviePtr->year <= current->data.year) {
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
    ActorNode* actor = actorHead;
    while (actor != nullptr && actor->data.id != actorId) {
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

    // Find all movies this actor is in through cast list
    CastNode* castNode = castHead;
    while (castNode != nullptr) {
        if (castNode->data.person_id == actorId) {
            // Find corresponding movie
            MovieNode* movieNode = movieHead;
            while (movieNode != nullptr) {
                if (movieNode->data.id == castNode->data.movie_id) {
                    // Create new node
                    TempMovieNode* newNode = new TempMovieNode;
                    newNode->moviePtr = &(movieNode->data);

                    // Insert in alphabetically sorted position
                    if (sortedHead == nullptr ||
                        strcmp(sortedHead->moviePtr->title, movieNode->data.title) > 0) {
                        // Insert at beginning
                        newNode->next = sortedHead;
                        sortedHead = newNode;
                    }
                    else {
                        // Find position to insert
                        TempMovieNode* current = sortedHead;
                        while (current->next != nullptr &&
                            strcmp(current->next->moviePtr->title, movieNode->data.title) <= 0) {
                            current = current->next;
                        }
                        newNode->next = current->next;
                        current->next = newNode;
                    }
                    break;
                }
                movieNode = movieNode->next;
            }
        }
        castNode = castNode->next;
    }

    // Display actor name and their movies
    std::cout << "\nMovies starring " << actor->data.name << ":\n";
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
    MovieNode* movie = movieHead;
    while (movie != nullptr && movie->data.id != movieId) {
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

    // Find all actors in this movie through cast list
    CastNode* castNode = castHead;
    while (castNode != nullptr) {
        if (castNode->data.movie_id == movieId) {
            // Find corresponding actor
            ActorNode* actorNode = actorHead;
            while (actorNode != nullptr) {
                if (actorNode->data.id == castNode->data.person_id) {
                    // Create new node
                    TempActorNode* newNode = new TempActorNode;
                    newNode->actorPtr = &(actorNode->data);

                    // Insert in alphabetically sorted position
                    if (sortedHead == nullptr ||
                        strcmp(sortedHead->actorPtr->name, actorNode->data.name) > 0) {
                        // Insert at beginning
                        newNode->next = sortedHead;
                        sortedHead = newNode;
                    }
                    else {
                        // Find position to insert
                        TempActorNode* current = sortedHead;
                        while (current->next != nullptr &&
                            strcmp(current->next->actorPtr->name, actorNode->data.name) <= 0) {
                            current = current->next;
                        }
                        newNode->next = current->next;
                        current->next = newNode;
                    }
                    break;
                }
                actorNode = actorNode->next;
            }
        }
        castNode = castNode->next;
    }

    // Display movie title and its actors
    std::cout << "\nActors in \"" << movie->data.title << "\":\n";
    std::cout << "----------------------------------------\n";

    if (sortedHead == nullptr) {
        std::cout << "No actors found for this movie." << std::endl;
    }
    else {
        TempActorNode* current = sortedHead;
        while (current != nullptr) {
            std::cout << current->actorPtr->name << " (Birth Year: "
                << current->actorPtr->birth << ")" << std::endl;
            TempActorNode* temp = current;
            current = current->next;
            delete temp;  // Clean up as we go
        }
    }
}


void MovieSystem::displayActorNetwork(int actorId) {
    // First verify actor exists
    ActorNode* sourceActor = actorHead;
    while (sourceActor != nullptr && sourceActor->data.id != actorId) {
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

    // Find all movies the source actor is in
    CastNode* castNode = castHead;
    while (castNode != nullptr) {
        if (castNode->data.person_id == actorId) {
            int movieId = castNode->data.movie_id;

            // Find all other actors in this movie (direct connections)
            CastNode* costarCast = castHead;
            while (costarCast != nullptr) {
                if (costarCast->data.movie_id == movieId &&
                    costarCast->data.person_id != actorId) {

                    // Find actor details
                    ActorNode* costar = actorHead;
                    while (costar != nullptr && costar->data.id != costarCast->data.person_id) {
                        costar = costar->next;
                    }
                    if (costar != nullptr) {
                        // Add to sorted list if not already present
                        bool alreadyExists = false;
                        ConnectedActor* check = sortedHead;
                        while (check != nullptr) {
                            if (check->actorPtr->id == costar->data.id) {
                                alreadyExists = true;
                                break;
                            }
                            check = check->next;
                        }

                        if (!alreadyExists) {
                            ConnectedActor* newNode = new ConnectedActor;
                            newNode->actorPtr = &(costar->data);
                            newNode->isDirect = true;

                            // Insert alphabetically
                            if (sortedHead == nullptr ||
                                strcmp(sortedHead->actorPtr->name, costar->data.name) > 0) {
                                newNode->next = sortedHead;
                                sortedHead = newNode;
                            }
                            else {
                                ConnectedActor* current = sortedHead;
                                while (current->next != nullptr &&
                                    strcmp(current->next->actorPtr->name, costar->data.name) <= 0) {
                                    current = current->next;
                                }
                                newNode->next = current->next;
                                current->next = newNode;
                            }

                            // Now find indirect connections through this costar
                            CastNode* costarMovies = castHead;
                            while (costarMovies != nullptr) {
                                if (costarMovies->data.person_id == costar->data.id) {
                                    int indirectMovieId = costarMovies->data.movie_id;

                                    // Find all actors in this movie
                                    CastNode* indirectCast = castHead;
                                    while (indirectCast != nullptr) {
                                        if (indirectCast->data.movie_id == indirectMovieId &&
                                            indirectCast->data.person_id != actorId &&
                                            indirectCast->data.person_id != costar->data.id) {

                                            // Find indirect actor details
                                            ActorNode* indirectActor = actorHead;
                                            while (indirectActor != nullptr &&
                                                indirectActor->data.id != indirectCast->data.person_id) {
                                                indirectActor = indirectActor->next;
                                            }

                                            if (indirectActor != nullptr) {
                                                // Check if already in list
                                                bool exists = false;
                                                ConnectedActor* checkIndirect = sortedHead;
                                                while (checkIndirect != nullptr) {
                                                    if (checkIndirect->actorPtr->id == indirectActor->data.id) {
                                                        exists = true;
                                                        break;
                                                    }
                                                    checkIndirect = checkIndirect->next;
                                                }

                                                if (!exists) {
                                                    ConnectedActor* newIndirectNode = new ConnectedActor;
                                                    newIndirectNode->actorPtr = &(indirectActor->data);
                                                    newIndirectNode->isDirect = false;

                                                    // Insert alphabetically
                                                    if (sortedHead == nullptr ||
                                                        strcmp(sortedHead->actorPtr->name, indirectActor->data.name) > 0) {
                                                        newIndirectNode->next = sortedHead;
                                                        sortedHead = newIndirectNode;
                                                    }
                                                    else {
                                                        ConnectedActor* current = sortedHead;
                                                        while (current->next != nullptr &&
                                                            strcmp(current->next->actorPtr->name, indirectActor->data.name) <= 0) {
                                                            current = current->next;
                                                        }
                                                        newIndirectNode->next = current->next;
                                                        current->next = newIndirectNode;
                                                    }
                                                }
                                            }
                                        }
                                        indirectCast = indirectCast->next;
                                    }
                                }
                                costarMovies = costarMovies->next;
                            }
                        }
                    }
                }
                costarCast = costarCast->next;
            }
        }
        castNode = castNode->next;
    }

    // Display results
    std::cout << "\nNetwork for " << sourceActor->data.name << ":\n";
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