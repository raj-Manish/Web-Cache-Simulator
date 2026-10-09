#ifndef LRUCACHE_H
#define LRUCACHE_H

#include <unordered_map>
#include <chrono>
#include <iostream>
#include "WebPage.h"

using namespace std;

class LRUNode{
public:

    string key;
    WebPage page;

    chrono::steady_clock::time_point time;

    LRUNode* next;
    LRUNode* prev;

    LRUNode(string k, WebPage p){

        key = k;
        page = p;

        time = chrono::steady_clock::now();

        next = NULL;
        prev = NULL;
    }
};


class LRUCache{
public:

    int cap;
    int ttl;

    unordered_map<string, LRUNode*> m;

    LRUNode* head = new LRUNode("", WebPage());
    LRUNode* tail = new LRUNode("", WebPage());


    LRUCache(int capacity, int timeToLive){

        cap = capacity;
        ttl = timeToLive;

        head->next = tail;
        tail->prev = head;
    }


    void to_delete(LRUNode* curr){

        LRUNode* peeche = curr->prev;
        LRUNode* aage = curr->next;

        peeche->next = aage;
        aage->prev = peeche;

        curr->next = NULL;
        curr->prev = NULL;
    }


    void to_add(LRUNode* curr){

        LRUNode* temp = head->next;

        head->next = curr;

        curr->prev = head;
        curr->next = temp;

        temp->prev = curr;
    }


    bool isExpired(LRUNode* curr){

        auto now = chrono::steady_clock::now();

        auto elapsed =
            chrono::duration_cast<chrono::seconds>(
                now - curr->time
            ).count();

        return elapsed >= ttl;
    }


    WebPage get(string url){

        if(!m.count(url)){
            return WebPage();
        }

        LRUNode* curr = m[url];


        // TTL check
        if(isExpired(curr)){

            m.erase(url);

            to_delete(curr);

            delete curr;

            return WebPage();
        }


        // Valid access
        // Refresh TTL
        curr->time = chrono::steady_clock::now();


        // Move to MRU
        to_delete(curr);
        to_add(curr);


        return curr->page;
    }


    void put(string url, WebPage page){

        // Already present
        if(m.count(url)){

            LRUNode* curr = m[url];

            curr->page = page;

            // Refresh TTL
            curr->time = chrono::steady_clock::now();

            // Move to MRU
            to_delete(curr);
            to_add(curr);

            return;
        }


        // Cache full
        if(m.size() == cap){

            // LRU node
            LRUNode* curr = tail->prev;

            m.erase(curr->key);

            to_delete(curr);

            delete curr;
        }


        // New node
        LRUNode* newNode =
            new LRUNode(url, page);

        // New node = MRU
        to_add(newNode);

        m[url] = newNode;
    }


    void showCache(){

        LRUNode* curr = head->next;

        cout << "\nLRU Cache (MRU -> LRU): ";

        while(curr != tail){

            cout << curr->key << " ";

            curr = curr->next;
        }

        cout << endl;
    }


    void clearCache(){

        LRUNode* curr = head->next;

        while(curr != tail){

            LRUNode* nextNode = curr->next;

            delete curr;

            curr = nextNode;
        }

        head->next = tail;
        tail->prev = head;

        m.clear();
    }
};

#endif