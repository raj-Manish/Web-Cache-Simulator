#ifndef LFUCACHE_H
#define LFUCACHE_H

#include <unordered_map>
#include <chrono>
#include <iostream>
#include "WebPage.h"

using namespace std;


// =========================
// LFU Node
// =========================

class LFUNode{
public:

    string key;
    WebPage page;

    int cnt;

    chrono::steady_clock::time_point time;

    LFUNode* prev;
    LFUNode* next;


    LFUNode(string k, WebPage p, int c){

        key = k;
        page = p;

        cnt = c;

        time = chrono::steady_clock::now();

        prev = NULL;
        next = NULL;
    }
};


// =========================
// Doubly Linked List
// Nodes having same frequency
// =========================

class LFUList{
public:

    LFUNode* head;
    LFUNode* tail;

    int sz;


    LFUList(){

        head = new LFUNode("", WebPage(), -1);
        tail = new LFUNode("", WebPage(), -1);

        head->next = tail;
        tail->prev = head;

        sz = 0;
    }


    void deleteNode(LFUNode* curr){

        LFUNode* peeche = curr->prev;
        LFUNode* aage = curr->next;

        peeche->next = aage;
        aage->prev = peeche;

        curr->prev = NULL;
        curr->next = NULL;

        sz--;
    }


    void insertInFront(LFUNode* curr){

        LFUNode* temp = head->next;

        head->next = curr;

        curr->prev = head;
        curr->next = temp;

        temp->prev = curr;

        sz++;
    }
};


// =========================
// LFU Cache
// =========================

class LFUCache{
public:

    int cap;
    int ttl;

    int minfreq;
    int currsz;


    unordered_map<string, LFUNode*> keyNode;

    unordered_map<int, LFUList*> freqList;


    LFUCache(int capacity, int timeToLive){

        cap = capacity;
        ttl = timeToLive;

        minfreq = 0;
        currsz = 0;
    }


    bool isExpired(LFUNode* curr){

        auto now = chrono::steady_clock::now();

        auto elapsed =
            chrono::duration_cast<chrono::seconds>(
                now - curr->time
            ).count();

        return elapsed >= ttl;
    }


    void updatefreqList(LFUNode* curr){

        int oldFreq = curr->cnt;


        // Remove from old frequency list
        LFUList* oldList =
            freqList[oldFreq];

        oldList->deleteNode(curr);


        // If minimum frequency list becomes empty
        if(minfreq == oldFreq &&
           oldList->sz == 0){

            minfreq++;
        }


        int newFreq = oldFreq + 1;

        LFUList* nextList;


        if(freqList.count(newFreq)){

            nextList =
                freqList[newFreq];
        }
        else{

            nextList = new LFUList();

            freqList[newFreq] =
                nextList;
        }


        curr->cnt++;


        // Recently accessed node
        // comes in front
        nextList->insertInFront(curr);
    }


    WebPage get(string url){

        // Not present
        if(!keyNode.count(url)){
            return WebPage();
        }


        LFUNode* curr =
            keyNode[url];


        // TTL expired
        if(isExpired(curr)){

            keyNode.erase(url);

            LFUList* list =
                freqList[curr->cnt];

            list->deleteNode(curr);

            currsz--;

            delete curr;

            return WebPage();
        }


        // Valid access

        // Refresh TTL
        curr->time =
            chrono::steady_clock::now();


        // Increase frequency
        updatefreqList(curr);


        return curr->page;
    }


    void put(string url, WebPage page){

        if(cap == 0){
            return;
        }


        // Already present
        if(keyNode.count(url)){

            LFUNode* curr =
                keyNode[url];

            curr->page = page;


            // Refresh TTL
            curr->time =
                chrono::steady_clock::now();


            // Increase frequency
            updatefreqList(curr);

            return;
        }


        // Cache full
        if(currsz == cap){

            LFUList* list =
                freqList[minfreq];


            // LRU among minimum-frequency nodes
            LFUNode* curr =
                list->tail->prev;


            keyNode.erase(curr->key);

            list->deleteNode(curr);

            delete curr;

            currsz--;
        }


        // New node starts with frequency 1
        int mincnt = 1;


        LFUList* currList;


        if(freqList.count(mincnt)){

            currList =
                freqList[mincnt];
        }
        else{

            currList =
                new LFUList();

            freqList[mincnt] =
                currList;
        }


        LFUNode* curr =
            new LFUNode(
                url,
                page,
                mincnt
            );


        currList->insertInFront(curr);

        keyNode[url] = curr;

        currsz++;

        minfreq = 1;
    }


    void showCache(){

        cout << "\nLFU Cache:" << endl;


        for(auto &it : freqList){

            if(it.second->sz == 0){
                continue;
            }


            cout << "Freq "
                 << it.first
                 << " -> ";


            LFUNode* curr =
                it.second->head->next;


            while(curr !=
                  it.second->tail){

                cout << curr->key
                     << " ";

                curr = curr->next;
            }


            cout << endl;
        }
    }


    void clearCache(){

        for(auto &it : keyNode){

            delete it.second;
        }

        keyNode.clear();


        for(auto &it : freqList){

            delete it.second;
        }

        freqList.clear();


        currsz = 0;
        minfreq = 0;
    }
};

#endif