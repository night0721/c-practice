#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <ncurses.h>

#define MAX_URL_LENGTH 2048
#define MAX_PAGE_LENGTH 100000

// Function to fetch web page content using libcurl
size_t write_callback(void* ptr, size_t size, size_t nmemb, char* data) {
    strncpy(data, ptr, size * nmemb);
    return size * nmemb;
}

int main() {
    char url[MAX_URL_LENGTH];
    char page[MAX_PAGE_LENGTH];
    char error_buffer[CURL_ERROR_SIZE];
    int running = 1;

    // Initialize ncurses
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Initialize libcurl
    CURL* curl = curl_easy_init();
    if (!curl) {
        endwin();
        fprintf(stderr, "Error initializing libcurl.\n");
        return 1;
    }

    while (running) {
        mvprintw(0, 0, "Enter a URL (or 'q' to quit): ");
        getnstr(url, MAX_URL_LENGTH);

        if (strcmp(url, "q") == 0) {
            running = 0;
            break;
        }

        // Set the URL and perform the request
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, page);
        curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, error_buffer);

        CURLcode res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            endwin();
            fprintf(stderr, "Error fetching URL: %s\n", error_buffer);
            curl_easy_cleanup(curl);
            return 1;
        }

        // Print the fetched page in the terminal
        clear();
        mvprintw(0, 0, "Fetched page: %s\n\n", url);
        mvprintw(2, 0, "%s", page);
        mvprintw(LINES - 1, 0, "Press any key to continue...");
        refresh();

        getch(); // Wait for user input before fetching another URL
    }

    // Clean up
    curl_easy_cleanup(curl);
    endwin();
    return 0;
}
