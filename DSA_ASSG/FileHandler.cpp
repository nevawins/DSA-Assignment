#include "FileHandler.h"
#include <fstream>
#include <sstream>

FileHandler::FileHandler(const std::string& actorsFile,
    const std::string& moviesFile,
    const std::string& castFile)
    : ACTORS_FILE(actorsFile), MOVIES_FILE(moviesFile), CAST_FILE(castFile) {}

void FileHandler::loadActors(Dictionary<int, Actor>& actors) {
    std::ifstream file(ACTORS_FILE);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open actors file.");
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, name, birthYearStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, name, ',');
        std::getline(ss, birthYearStr);

        Actor actor;
        actor.id = std::stoi(idStr);
        if (name.front() == '"') name = name.substr(1);
        if (name.back() == '"') name = name.substr(0, name.length() - 1);
        actor.name = name;
        actor.birthYear = std::stoi(birthYearStr);

        actors.insert(actor.id, actor);
    }
    file.close();
}

void FileHandler::loadMovies(Dictionary<int, Movie>& movies) {
    std::ifstream file(MOVIES_FILE);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open movies file.");
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string idStr, title, plot, yearStr;
        std::getline(ss, idStr, ',');
        std::getline(ss, title, ',');
        std::getline(ss, plot, ',');
        std::getline(ss, yearStr, ',');

        Movie movie;
        movie.id = std::stoi(idStr);
        movie.title = title;
        movie.plot = plot;
        movie.year = std::stoi(yearStr);

        movies.insert(movie.id, movie);
    }
    file.close();
}

void FileHandler::loadCast(Dictionary<int, LinkedList<int>>& cast) {
    std::ifstream file(CAST_FILE);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open cast file.");
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string actorIdStr, movieIdStr;
        std::getline(ss, actorIdStr, ',');
        std::getline(ss, movieIdStr, ',');

        int actorId = std::stoi(actorIdStr);
        int movieId = std::stoi(movieIdStr);

        LinkedList<int>* actorList = cast.find(movieId);
        if (!actorList) {
            LinkedList<int> newList;
            newList.append(actorId);
            cast.insert(movieId, newList);
        }
        else {
            actorList->append(actorId);
        }
    }
    file.close();
}

void FileHandler::saveActors(const Dictionary<int, Actor>& actors) {
    std::ofstream file(ACTORS_FILE);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open actors file for writing.");
    }

    file << "id,name,birth\n"; // Write header
    actors.traverse([&file](const int& key, const Actor& actor) {
        file << key << ",\"" << actor.name << "\"," << actor.birthYear << "\n";
        });

    file.close();
}

void FileHandler::saveMovies(const Dictionary<int, Movie>& movies) {
    std::ofstream file(MOVIES_FILE);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open movies file for writing.");
    }

    file << "id,title,plot,year\n"; // Write header
    movies.traverse([&file](const int& key, const Movie& movie) {
        file << key << ",\"" << movie.title << "\",\"" << movie.plot << "\"," << movie.year << "\n";
        });

    file.close();
}

void FileHandler::saveCast(const Dictionary<int, LinkedList<int>>& cast) {
    std::ofstream file(CAST_FILE);
    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open cast file for writing.");
    }

    file << "actor_id,movie_id\n"; // Write header
    cast.traverse([&file](const int& movieId, const LinkedList<int>& actorList) {
        auto current = actorList.getHead(); // Get head of the linked list
        while (current) {
            file << current->data << "," << movieId << "\n"; // actor_id, movie_id
            current = current->next;
        }
        });

    file.close();
}
