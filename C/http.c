#include <stdio.h>
#include <curl/curl.h>
#include "util.h"


int main() {
    CURL* curl;
    CURLcode res;
    clrscr();
    // Initialize libcurl
    curl_global_init(CURL_GLOBAL_DEFAULT);

    // Create a curl handle
    curl = curl_easy_init();

    if (curl) {
        // Set the URL to perform the GET request
        curl_easy_setopt(curl, CURLOPT_URL, "https://night0721-orange-giggle-4p6rq9j4xgh5qqj.github.dev/");

        // Perform the request
        res = curl_easy_perform(curl);
        printf("hi");
        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));

        // Cleanup
        curl_easy_cleanup(curl);
    }
    printf("CURL not initialized");

    // Cleanup global libcurl resources
    curl_global_cleanup();

    return 0;
}
