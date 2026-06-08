# Milestone 1: Proposal & Design

## 1. Project Idea
**Movie Information Fetcher** - A C++ console application that allows users to search for movies or TV shows and retrieves real-world data such as release year, director, plot summary, and review scores using the OMDb (Open Movie Database) API.

## 2. Description of What the Program Does
The program will run an interactive, menu-driven loop in the terminal. When a user enters a movie title, the application will reach out to the OMDb API, download the movie's data in JSON format, parse the information, and display it cleanly to the user. The application will also maintain a history of all the movies searched during the session so the user can look back at their previous queries.

## 3. Planned Classes
To ensure proper Object-Oriented Design and file separation, the project will use the following classes:
*   **`Movie`**: A data class representing a single movie. It will store attributes like `title`, `year`, `director`, `plot`, and `rating`. It will include a `display()` method to print its information to the screen.
*   **`APIClient`**: A utility class responsible for networking. It will construct the correct API URL, perform the HTTP request, receive the JSON response, parse it, and dynamically allocate new `Movie` objects to return to the application.
*   **`MovieApp`**: The core controller class. It will manage the menu loop, handle user input, interact with the `APIClient`, and store the user's search history.

## 4. Planned Data Structures and Memory Management
*   **Vector**: The `MovieApp` class will maintain a 1D vector of pointers to track search history: `std::vector<Movie*> searchHistory;`.
*   **Pointers & Dynamic Memory**: When the `APIClient` successfully fetches a movie, it will use `new Movie(...)` to dynamically allocate it in memory and return a pointer. This pointer is stored in the vector. When the program exits (or clears history), the `MovieApp` will iterate through the vector and call `delete` on each pointer to prevent memory leaks.

## 5. User Interaction
The program will be menu-driven. The user will be greeted with a menu offering the following options:
1.  **Search for a Movie**: Prompts the user for a title, fetches data, and displays it.
2.  **View Search History**: Prints a summarized list of all previously searched movies.
3.  **Clear Search History**: Deletes the saved history (and frees the memory).
4.  **Exit Program**: Safely exits and cleans up all dynamic memory.
