# Project and Portfolio I: Computer Science
**Student:** Basil Mohamed

## Movie Information Fetcher
This repository contains the ongoing development of the **Movie Information Fetcher**, a C++ console application that connects to the OMDb API to fetch and display real-world movie data.

---

### Week 1 Progress

During Week 1, the core foundation of the project was established, completing both Milestone 1 and Milestone 2 ahead of schedule:

*   **Repository Setup:** 
    *   Created the required directory structure (`/dev`, `/docs`, `/images`).
    *   Configured the `.gitignore` to hide local Visual Studio configuration files (`.vs/`).
*   **Milestone 1 (Proposal & Design):** 
    *   Drafted the project idea, planned out the classes, data structures (vectors/pointers), and the core user loop.
    *   Documentation available in `docs/Milestone1_Proposal.md`.
*   **Milestone 2 (Core System Prototype):** 
    *   Implemented the `Movie` data class.
    *   Implemented the `APIClient` class to handle networking using C++ system calls (`curl.exe`) to parse JSON without heavy external libraries.
    *   Implemented the `App` class to handle the interactive user menu and track search history using a `std::vector<Movie*>`.
    *   Code available in the `dev/` directory.
*   **Version Control:**
    *   Completed the Version Control research document (`docs/BasilMohamed-version-control.md`).
    *   Learned to stage and commit code sequentially using Git.


### Week 2 Progress

During Week 2, the application's structure and robustness were improved for Milestone 2:

*   **Project Relocation**: Relocated the Visual Studio solution (`.slnx`) and project files (`.vcxproj`, `.vcxproj.filters`, `.vcxproj.user`) inside the `dev/` directory to conform with the course structure requirements.
*   **Input Validation**: Implemented robust input validation in the menu loop (`App::run()`) to handle invalid non-numeric inputs (like text or symbols) cleanly. The application now displays an error message, resets the stream, discards the bad input, and re-prompts the user instead of entering an infinite loop. 


### Week 3 Progress

During Week 3, the application was completed for Milestone 3 (Feature Completion):

*   **Persistent Search History**: Added automated file I/O to serialize search history to `history.txt` on exit and restore it on startup, keeping disk persistence separate from memory cleanup.
*   **Interactive History Viewer**: Upgraded the search history list into an interactive menu that lets users select past searches by number to view their full details.
*   **Robust Manual JSON Parsing**: Rewrote the JSON extractor to handle escaped quotes (`\"`) and spaces around colons, and propagated specific OMDb error messages to the user.
*   **URL Encoding**: Implemented standard URL encoding for titles to correctly query movies with spaces and special characters (like `&`).
*   **Visual Layout & Word-Wrapping**: Added clean ASCII border boxes and custom text word-wrapping to format details beautifully on standard console dimensions, alongside empty input checks.


### Week 4 Progress

During Week 4, the application was finalized for Milestone 4 (Final Submission):

*   **Dynamic API Key Caching**: Decoupled the API key from source code by loading it from `api_key.txt` or prompting the user on first-run and persisting it.
*   **API Key Protection**: Added `api_key.txt` to `.gitignore` to ensure credentials are never committed.
*   **Deliberate Input Handling**: Removed the unsafe `std::cin.ignore()` blanket fixes, replacing them with a custom line-by-line integer parser (`App::readIntegerInput`) that prevents stream corruption and handles EOF gracefully.
*   **Network Failure Resilience**: Fixed the bug where network failures led to empty `"N/A"` movie entries in search history by validating raw response payloads before parsing.
*   **Final Release Documentation & Packaging**: Created `docs/Milestone4.md` and generated compilation and features validation screenshots in `docs/validation/`.


