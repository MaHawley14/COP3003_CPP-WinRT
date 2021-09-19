// Matthew Hawley
// CPP-WinRT.cpp : This file contains the 'main' function
//Program execution begins and ends there

#include <iostream>
#include "pch.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Web::Syndication;

int main() {
    
    // initializes the thread in the Windows Runtime; default, in a multithreaded apartment
    // also initializes COM.
    winrt::init_apartment();

    // stack-allocate two objects: represent the uri of the Windows blog, and a syndication client
    // construct the uri with a simple wide string literal
    Uri rssFeedUri{ L"https://blogs.windows.com/feed" };
    SyndicationClient syndicationClient;
    
    // asynchronous Windows Runtime function, code receives an asynchronous operation object from RetrieveFeedAsync
    // calls get on that object to block the calling thread and wait for the result
    SyndicationFeed syndicationFeed = syndicationClient.RetrieveFeedAsync(rssFeedUri).get();
    
    // SyndicationFeed.Items is a range, defined by iterators returned from begin and end functions
    // enumerate Items with either a range-based for statement, or with the std::for_each template function
    for (const SyndicationItem syndicationItem : syndicationFeed.Items()) {
        
        // Gets feed's title text, as a winrt::hstring object
        //The hstring is then output, via the c_str function
        winrt::hstring titleAsHstring = syndicationItem.Title().Text();
        std::wcout << titleAsHstring.c_str() << std::endl;
    }
}