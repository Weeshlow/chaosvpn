#include "curl/curl.h"
#include <string.h>
#include <stdlib.h>
#include "main.h"
#include "http.h"


void *myrealloc(void *ptr, size_t size) {
	if(ptr)
		return realloc(ptr, size);
	else
		return malloc(size);
}

size_t WriteMemoryCallback(void *ptr, size_t size, size_t nmemb, void *data) {
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)data;

	mem->memory = myrealloc(mem->memory, mem->size + realsize + 1);
	if (mem->memory) {
		memcpy(&(mem->memory[mem->size]), ptr, realsize);
		mem->size += realsize;
		mem->memory[mem->size] = 0;
	}
	return realsize;
}

int http_request(char *url, struct buffer *response) {
	CURL *curl;
	CURLcode res;
	struct MemoryStruct chunk;

	chunk.memory=NULL;
	chunk.size = 0;

	curl_global_init(CURL_GLOBAL_DEFAULT);
	curl = curl_easy_init();

	if(!curl) {
		printf("unable to load libcurl\n");
		return 1;
	}

	curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1);
	curl_easy_setopt(curl, CURLOPT_URL, url);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);
	curl_easy_setopt(curl, CURLOPT_USERAGENT, "ChaosVPNclient/2.0");

	res = curl_easy_perform(curl);
	response->text = chunk.memory;

	curl_easy_cleanup(curl);

	return 0;
}

