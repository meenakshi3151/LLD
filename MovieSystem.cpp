#include <bits/stdc++.h>
using namespace std;

/* ===================== MOVIE ===================== */

class Movie {
public:
    unordered_map<string, int> userIdToRating;
    double avgRating = 0.0;
    int ratedBy = 0;
    string name;
    string genre;

    Movie(string movieName, string movieGenre) {
        name = movieName;
        genre = movieGenre;
    }

    string getMovieName() {
        return name;
    }

    string getMovieGenre() {
        return genre;
    }

    void rateMovie(int currRating, const string& userId) {
        // If user already rated, update average properly
        if (userIdToRating.find(userId) != userIdToRating.end()) {
            int oldRating = userIdToRating[userId];
            avgRating = (avgRating * ratedBy - oldRating + currRating) / ratedBy;
        } else {
            avgRating = (avgRating * ratedBy + currRating) / (ratedBy + 1);
            ratedBy++;
        }
        userIdToRating[userId] = currRating;
    }

    double getMovieAvgRating() {
        return avgRating;
    }
};

/* ===================== MOVIE HANDLER ===================== */

class MovieHandler {
public:
    unordered_map<string, Movie*> movies;
    unordered_map<string, vector<Movie*>> genreToMovie;

    void createMovie(string movieId, string movieName, string movieGenre) {
        if (movies.find(movieId) != movies.end()) {
            cout << "Movie already exists!\n";
            return;
        }

        Movie* movie = new Movie(movieName, movieGenre);
        movies[movieId] = movie;
        genreToMovie[movieGenre].push_back(movie);

        cout << "Movie added successfully!\n";
    }

    vector<Movie*> getMovieInGenre(string genre, int ratingThreshold) {
        vector<Movie*> result;
        if (genreToMovie.find(genre) == genreToMovie.end())
            return result;

        for (Movie* movie : genreToMovie[genre]) {
            if (movie->getMovieAvgRating() >= ratingThreshold) {
                result.push_back(movie);
            }
        }
        return result;
    }

    void displayMovieDetails(Movie* movie) {
        if (!movie) return;

        cout << "Name: " << movie->getMovieName() << endl;
        cout << "Genre: " << movie->getMovieGenre() << endl;
        cout << "Average Rating: " << movie->getMovieAvgRating() << endl;
        cout << "----------------------------------\n";
    }

    void displayAllMovies() {
        for (auto& it : movies) {
            displayMovieDetails(it.second);
        }
    }
};

/* ===================== USER ===================== */

class User {
public:
    string id;
    string name;
    vector<string> favouriteGenres;
    string password;
    bool isLogin = false;

    User(string userId, string userName,
         vector<string> movieGenres, string userPassword) {
        id = userId;
        name = userName;
        favouriteGenres = movieGenres;
        password = userPassword;
    }

    string getUserPassword() {
        return password;
    }

    vector<string> getUserGenres() {
        return favouriteGenres;
    }

    void setLogin(bool status) {
        isLogin = status;
    }

    bool getLogin() {
        return isLogin;
    }
};

/* ===================== USER FACTORY ===================== */

class UserFactory {
public:
    unordered_map<string, User*> users;

    void createUser(string userId, string userName,
                    vector<string> movieGenres, string userPassword) {
        if (users.find(userId) != users.end()) {
            cout << "User already exists!\n";
            return;
        }

        users[userId] = new User(userId, userName, movieGenres, userPassword);
        cout << "User created successfully!\n";
    }

    void loginUser(string userId, string password, MovieHandler* mh) {
        if (users.find(userId) == users.end()) {
            cout << "User not found!\n";
            return;
        }

        User* user = users[userId];
        if (user->getUserPassword() != password) {
            cout << "Incorrect password!\n";
            return;
        }

        user->setLogin(true);
        cout << "User logged in successfully!\n";
        mh->displayAllMovies();
    }

    void logoutUser(string userId) {
        if (users.find(userId) == users.end()) {
            cout << "User not found!\n";
            return;
        }

        User* user = users[userId];
        if (!user->getLogin()) {
            cout << "User not logged in!\n";
            return;
        }

        user->setLogin(false);
        cout << "User logged out successfully!\n";
    }

    void getRecommendations(string userId, int threshold, MovieHandler* mh) {
        if (users.find(userId) == users.end()) return;

        User* user = users[userId];
        vector<string> genres = user->getUserGenres();

        cout << "\nRecommended Movies:\n";
        for (string& g : genres) {
            vector<Movie*> movies = mh->getMovieInGenre(g, threshold);
            for (Movie* m : movies) {
                mh->displayMovieDetails(m);
            }
        }
    }

    void rateMovie(int rating, string userId, Movie* movie) {
        if (!movie) return;
        movie->rateMovie(rating, userId);
    }
};

/* ===================== MAIN ===================== */

int main() {
    MovieHandler* movieHandler = new MovieHandler();
    UserFactory* userFactory = new UserFactory();

    // Create movies
    movieHandler->createMovie("M1", "Inception", "SciFi");
    movieHandler->createMovie("M2", "Interstellar", "SciFi");
    movieHandler->createMovie("M3", "Titanic", "Romance");

    // Create users
    userFactory->createUser("U1", "Alice", {"SciFi", "Romance"}, "alice123");
    userFactory->createUser("U2", "Bob", {"SciFi"}, "bob123");

    // Login users
    userFactory->loginUser("U1", "alice123", movieHandler);
    userFactory->loginUser("U2", "bob123", movieHandler);

    // Rate movies
    userFactory->rateMovie(5, "U1", movieHandler->movies["M1"]);
    userFactory->rateMovie(4, "U1", movieHandler->movies["M3"]);
    userFactory->rateMovie(5, "U2", movieHandler->movies["M1"]);
    userFactory->rateMovie(5, "U2", movieHandler->movies["M2"]);

    // Show recommendations
    userFactory->getRecommendations("U2", 4, movieHandler);

    // Logout
    userFactory->logoutUser("U1");
    userFactory->logoutUser("U2");

    return 0;
}
