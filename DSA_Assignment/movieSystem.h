#ifndef MOVIE_SYSTEM_H
#define MOVIE_SYSTEM_H

// Basic structure definitions
struct Movie {
    int id;
    char title[100];    // Fixed-size array instead of std::string
    char plot[2048];     // Fixed-size array instead of std::string
    int year;
};

struct Actor {
    int id;
    char name[100];     // Fixed-size array instead of std::string
    int birth;
};

struct Cast {
    int person_id;
    int movie_id;
};

// Node structures for linked lists
struct ActorNode {
    Actor data;
    ActorNode* next;
};

struct MovieNode {
    Movie data;
    MovieNode* next;
};

struct CastNode {
    Cast data;
    CastNode* next;
};

class MovieSystem {
private:
    ActorNode* actorHead;
    MovieNode* movieHead;
    CastNode* castHead;

    // Private helper methods
    void addActor(const Actor& actor);
    void addMovie(const Movie& movie);
    void addCast(const Cast& cast);

public:
    // Constructor and Destructor
    MovieSystem();
    ~MovieSystem();

    // File reading methods
    bool readActorsFromFile(const char* filename);    // Changed from std::string to const char*
    bool readMoviesFromFile(const char* filename);    // Changed from std::string to const char*
    bool readCastFromFile(const char* filename);      // Changed from std::string to const char*

    // Display method (for testing)
    void displayAllData();

    void displayActorsByAgeRange(int minAge, int maxAge);
    void displayRecentMovies();
    void displayMoviesForActor(int actorId);
    void displayActorsInMovie(int movieId);
    void displayActorNetwork(int actorId);
};


#endif