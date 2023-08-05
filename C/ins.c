#include "lib/json/json.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

static void print_depth_shift(int depth)
{
    int j;
    for (j = 0; j < depth; j++) {
        printf(" ");
    }
}

static void process_value(json_value* value, int depth);

static void process_object(json_value* value, int depth)
{
    int length, x;
    if (value == NULL) {
        return;
    }
    length = value->u.object.length;
    for (x = 0; x < length; x++) {
        print_depth_shift(depth);
        printf("object[%d].name = %s\n", x, value->u.object.values[x].name);
        process_value(value->u.object.values[x].value, depth + 1);
    }
}

static void process_array(json_value* value, int depth)
{
    int length, x;
    if (value == NULL) {
        return;
    }
    length = value->u.array.length;
    //printf("array\n");
    for (x = 0; x < length; x++) {
        process_value(value->u.array.values[x], depth);
    }
}

static void process_value(json_value* value, int depth)
{
    if (value == NULL) {
        return;
    }
    if (value->type != json_object) {
        print_depth_shift(depth);
    }
    switch (value->type) {
    case json_none:
        printf("none\n");
        break;
    case json_null:
        printf("null\n");
        break;
    case json_object:
        process_object(value, depth + 1);
        break;
    case json_array:
        process_array(value, depth + 1);
        break;
    case json_integer:
        printf("int: %10ld\n", (long)value->u.integer);
        break;
    case json_double:
        printf("double: %f\n", value->u.dbl);
        break;
    case json_string:
        //printf("string: %s\n", value->u.string.ptr);
        break;
    case json_boolean:
        printf("bool: %d\n", value->u.boolean);
        break;
    }
}

static char* getTime() {
    time_t now = time(NULL);
    struct tm* tm = localtime(&now);
    char* time_str = malloc(sizeof(char) * 20); // Allocate 20 bytes for the formatted time string
    if (time_str == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    strftime(time_str, 20, "%Y-%m-%d %H:%M:%S", tm); // Pass the correct size (20) for the buffer
    time_str[19] = '\0'; // Null-terminate the string at the 19th index to remove the ".000Z" suffix
    time_str[10] = ' '; // Replace the "T" with a space
    return time_str;
}

static void appendReadme(char* value) {
    FILE* f = fopen("./README.md", "a");
    if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
    char* timestamp = getTime();
    fprintf(f, "%s %s\n\n", timestamp, value);
	fclose(f);
}

static void compare_arrays(json_value* prev_array, json_value* current_array, const char* type, int is_following)
{
    if (is_following)
    {
        for (int i = 0; i < prev_array->u.array.length; i++)
        {
            const char* user = prev_array->u.array.values[i]->u.string.ptr;
            int found = 0;
            for (int j = 0; j < current_array->u.array.length; j++)
            {
                if (strcmp(user, current_array->u.array.values[j]->u.string.ptr) == 0)
                {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                char* formattedStr = (char*) malloc(100 * sizeof(char));
                if (formattedStr == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                snprintf(formattedStr, 100, "Removed Follow By: `%s`\n", user);
                appendReadme(formattedStr);
                printf("Removed Follow By: %s\n", user);
                free(formattedStr);
            }
        }

        for (int i = 0; i < current_array->u.array.length; i++)
        {
            const char* user = current_array->u.array.values[i]->u.string.ptr;
            int found = 0;
            for (int j = 0; j < prev_array->u.array.length; j++)
            {
                if (strcmp(user, prev_array->u.array.values[j]->u.string.ptr) == 0)
                {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                char* formattedStr = (char*)malloc(100 * sizeof(char));
                if (formattedStr == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                snprintf(formattedStr, 100, "Following: `%s`\n", user);
                appendReadme(formattedStr);
                printf("Following: %s\n", user);
                free(formattedStr);
            }  
        }
    }
    else
    {
        for (int i = 0; i < prev_array->u.array.length; i++)
        {
            const char* user = prev_array->u.array.values[i]->u.string.ptr;
            int found = 0;
            for (int j = 0; j < current_array->u.array.length; j++)
            {
                if (strcmp(user, current_array->u.array.values[j]->u.string.ptr) == 0)
                {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                char* formattedStr = (char*)malloc(100 * sizeof(char));
                if (formattedStr == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                snprintf(formattedStr, 100, "Unfollowed By: `%s`\n", user);
                appendReadme(formattedStr);
                printf("Unfollowed By: %s\n", user);
                free(formattedStr);
            }
        }

        for (int i = 0; i < current_array->u.array.length; i++)
        {
            const char* user = current_array->u.array.values[i]->u.string.ptr;
            int found = 0;
            for (int j = 0; j < prev_array->u.array.length; j++)
            {
                if (strcmp(user, prev_array->u.array.values[j]->u.string.ptr) == 0)
                {
                    found = 1;
                    break;
                }
            }
            if (!found) {
                char* formattedStr = (char*)malloc(100 * sizeof(char));
                if (formattedStr == NULL) {
                    printf("Memory allocation failed.\n");
                    exit(1);
                }
                snprintf(formattedStr, 100, "New Follower: `%s`\n", user);
                appendReadme(formattedStr);
                printf("New Follower: %s\n", user);
                free(formattedStr);
            }
        }
    }
}

int main(int argc, char** argv)
{
    char* filename;
    FILE* fp;
    struct stat filestatus;
    int file_size;
    char* file_contents;
    json_char* json;
    json_value* value;

    if (argc != 2) {
        fprintf(stderr, "%s <file_json>\n", argv[0]);
        return 1;
    }
    filename = argv[1];

    if (stat(filename, &filestatus) != 0) {
        fprintf(stderr, "File %s not found\n", filename);
        return 1;
    }
    file_size = filestatus.st_size;
    file_contents = (char*)malloc(filestatus.st_size);
    if (file_contents == NULL) {
        fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
        return 1;
    }

    fp = fopen(filename, "rt");
    if (fp == NULL) {
        fprintf(stderr, "Unable to open %s\n", filename);
        fclose(fp);
        free(file_contents);
        return 1;
    }

    if (fread(file_contents, file_size, 1, fp) != 1) {
        fprintf(stderr, "Unable to read content of %s\n", filename);
        fclose(fp);
        free(file_contents);
        return 1;
    }
    fclose(fp);

    json = (json_char*)file_contents;
    value = json_parse(json, file_size);

    if (value == NULL) {
        fprintf(stderr, "Unable to parse data\n");
        free(file_contents);
        exit(1);
    }

    
    json_value* current_followers = NULL;
    json_value* current_following = NULL;
    json_value* prev_followers = NULL;
    json_value* prev_following = NULL;

    for (int i = 0; i < value->u.object.length; i++)
    {
        const char* date_key = value->u.object.values[i].name;
        json_value* data = value->u.object.values[i].value;

        for (int j = 0; j < data->u.object.length; j++)
        {
            const char* type_key = data->u.object.values[j].name;
            json_value* type_data = data->u.object.values[j].value;
            if (strcmp(type_key, "followers") == 0)
            {
                process_array(type_data, 0);

                if (prev_followers != NULL)
                {
                    compare_arrays(prev_followers, type_data, type_key, 0);
                }

                prev_followers = type_data;
            }
            else if (strcmp(type_key, "following") == 0)
            {
                process_array(type_data, 0);

                if (prev_following != NULL)
                {
                    compare_arrays(prev_following, type_data, type_key, 1);
                }
                prev_following = type_data;
            }
        }
    }
    json_value_free(value);
    free(file_contents);
    return 0;
}