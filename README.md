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
