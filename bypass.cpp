// DRGcore – HieuDRG – Shadow License v99
// Compile: g++ bypass.cpp -o bypass -std=c++17 -lcurl
#include <iostream>
#include <string>
#include <regex>
#include <curl/curl.h>

static size_t WriteCB(void* contents, size_t size, size_t nmemb, std::string* userp){
    userp->append((char*)contents, size*nmemb);
    return size*nmemb;
}

std::string fetch(const std::string& url){
    CURL* curl = curl_easy_init();
    std::string read;
    if(curl){
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCB);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &read);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 10L);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if(res!=CURLE_OK) return "";
    }
    return read;
}

std::string bypassShort(const std::string& url){
    std::string body = fetch("https://api.allorigins.win/get?url="+url);
    std::regex re(R"(href=["'](https?:\/\/[^"']+)["'])");
    std::smatch m;
    if(std::regex_search(body,m,re)) return m[1];
    return "No destination found";
}

int main(int argc, char* argv[]){
    if(argc<2){
        std::cout << "Usage: ./bypass <link_or_key>\n";
        return 0;
    }
    std::string input = argv[1];
    std::string out = bypassShort(input);
    std::cout << "DRGcore result: " << out << '\n';
    return 0;
}
