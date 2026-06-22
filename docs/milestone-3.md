# Milestone 3: Feature Completion

This document outlines the completed features, bug fixes, and architecture improvements implemented for Milestone 3 of the **Movie Information Fetcher** application.

## 1. Accomplished Features

*   **Persistent Search History**: Hooked automatic reading and writing of movie queries to `history.txt`. The application loads the history into memory on startup and updates it immediately when new movies are successfully searched or when the program shuts down.
*   **Interactive History Submenu**: Redesigned the search history list into a looping interactive menu. Users can now view the history list and type a movie number to print its full details, entering `0` to return to the main loop.
*   **Robust Manual JSON Parsing**: Refactored the extraction function `APIClient::extractJSONValue` to parse character-by-character, allowing it to correctly handle spaces around colons and safely skip escaped quotation marks (`\"`) in JSON values.
*   **Specific API Error Feedback**: Extracted the `"Error"` field from OMDb API error responses (such as "Movie not found!" or "Invalid API key") and displayed them directly to the user rather than printing a generic fallback message.
*   **URL Query Encoding**: Implemented a URL-encoding utility to dynamically convert special characters (such as space to `+`, and ampersands to `%26`) inside title queries, preventing API command breaks.
*   **UI Borders & Word Wrapping**: Added structured ASCII border boxes and a custom word-wrap utility to format movie titles, ratings, directors, and long plots within standard console widths without breaking words.
*   **Whitespace and Empty Input Validation**: Implemented checks in the input stream to ignore empty inputs or spacing.

## 2. Refactoring & Code Quality Improvements

*   **Destructor & History Persistence Separation**: Decoupled local memory destruction from disk file truncation by introducing a boolean flag to `App::clearHistory(bool clearDisk)`. This resolved a bug where the destructor's local cleanup block would wipe the disk storage on application exit.
*   **Input Stream Management**: Retained robust stream clearing in Visual Studio to handle non-numeric choices gracefully and avoid infinite loop menu states.
*   **Git Repository Cleanup**: Updated `.gitignore` to omit Visual Studio debug caches (`x64/`, `Debug/`, `Release/`, `*.tlog`, `*.idb`) and untracked existing cached compiler logs from the Git index.
