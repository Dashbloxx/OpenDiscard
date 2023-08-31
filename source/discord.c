#include <curl/curl.h>
#include <cJSON.h>
#include <stdlib.h>
#include <stdio.h>

#include "discord.h"

size_t write_callback(void * contents, size_t size, size_t nmemb, void * userp)
{
    return size * nmemb;
}

int discord_send_webhook(char * webhook, char * content)
{
    CURL * curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    cJSON * payload = cJSON_CreateObject();
    cJSON_AddStringToObject(payload, "content", content);

    char * payload_raw = cJSON_PrintUnformatted(payload);

    curl = curl_easy_init();
    if (curl)
    {
        struct curl_slist * headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");

        curl_easy_setopt(curl, CURLOPT_URL, webhook);
        curl_easy_setopt(curl, CURLOPT_POST, 1);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, payload_raw);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK)
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    cJSON_Delete(payload);
    free(payload_raw);

    curl_global_cleanup();
}

int discord_check_token(char * token)
{
    CURL * curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if(curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://discordapp.com/api/v6/users/@me/guilds");

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, "Content-Type: application/json");
        char auth_header[256];
        snprintf(auth_header, sizeof(auth_header), "authorization: %s", token);
        headers = curl_slist_append(headers, auth_header);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);

        res = curl_easy_perform(curl);

        if(res == CURLE_OK)
        {
            int response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
            return response_code;
        }
        else
        {
            fprintf(stderr, "error: request failed: %s\n", curl_easy_strerror(res));
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();
    return 0;
}