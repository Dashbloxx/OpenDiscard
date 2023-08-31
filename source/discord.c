#include <curl/curl.h>
#include <cJSON.h>
#include <stdlib.h>

#include "discord.h"

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