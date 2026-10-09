#include <bits/stdc++.h>

#include "WebPage.h"
#include "Storage.h"
#include "LRUCache.h"
#include "LFUCache.h"

using namespace std;


int main(){

    int capacity;
    int ttl;


    cout << "Enter cache capacity: ";
    cin >> capacity;


    cout << "Enter TTL (seconds): ";
    cin >> ttl;


    Storage storage;

    LRUCache lru(capacity, ttl);

    LFUCache lfu(capacity, ttl);


    int totalRequests = 0;

    int lruHits = 0;
    int lruMisses = 0;

    int lfuHits = 0;
    int lfuMisses = 0;


    while(true){

        cout << "\n================================" << endl;
        cout << "       Web Cache Simulator" << endl;
        cout << "================================" << endl;

        cout << "1. Visit URL" << endl;
        cout << "2. Show Caches" << endl;
        cout << "3. Show Statistics" << endl;
        cout << "4. Clear Caches" << endl;
        cout << "5. Exit" << endl;


        cout << "\nEnter choice: ";

        int choice;
        cin >> choice;


        // ==========================================
        // Visit URL
        // ==========================================

        if(choice == 1){

            string url;

            cout << "Enter URL: ";
            cin >> url;


            totalRequests++;


            // -------------------------
            // LRU
            // -------------------------

            WebPage lruPage =
                lru.get(url);


            bool lruHit =
                (lruPage.url != "");


            if(lruHit){
                lruHits++;
            }
            else{
                lruMisses++;
            }


            // -------------------------
            // LFU
            // -------------------------

            WebPage lfuPage =
                lfu.get(url);


            bool lfuHit =
                (lfuPage.url != "");


            if(lfuHit){
                lfuHits++;
            }
            else{
                lfuMisses++;
            }


            // -------------------------
            // Load from storage
            // only if at least one
            // cache missed
            // -------------------------

            if(!lruHit || !lfuHit){

                WebPage page =
                    storage.getPage(url);


                if(page.url == ""){

                    cout << "\nPage not found!"
                         << endl;

                    continue;
                }


                // Only missed cache
                // gets the page

                if(!lruHit){
                    lru.put(url, page);
                }


                if(!lfuHit){
                    lfu.put(url, page);
                }
            }


            // -------------------------
            // Result
            // -------------------------

            cout << "\n========== Result ==========" << endl;


            cout << "LRU : ";

            if(lruHit){
                cout << "Cache Hit";
            }
            else{
                cout << "Cache Miss";
            }

            cout << endl;


            cout << "LFU : ";

            if(lfuHit){
                cout << "Cache Hit";
            }
            else{
                cout << "Cache Miss";
            }

            cout << endl;
        }


        // ==========================================
        // Show caches
        // ==========================================

        else if(choice == 2){

            lru.showCache();

            lfu.showCache();
        }


        // ==========================================
        // Statistics
        // ==========================================

        else if(choice == 3){

            cout << "\n================================"
                 << endl;

            cout << "       Cache Comparison"
                 << endl;

            cout << "================================"
                 << endl;


            cout << "\nLRU Cache" << endl;

            cout << "Hits   : "
                 << lruHits << endl;

            cout << "Misses : "
                 << lruMisses << endl;


            if(totalRequests > 0){

                double ratio =
                    (double)lruHits /
                    totalRequests * 100;


                cout << "Hit Ratio : "
                     << ratio
                     << "%" << endl;
            }


            cout << "\nLFU Cache" << endl;

            cout << "Hits   : "
                 << lfuHits << endl;

            cout << "Misses : "
                 << lfuMisses << endl;


            if(totalRequests > 0){

                double ratio =
                    (double)lfuHits /
                    totalRequests * 100;


                cout << "Hit Ratio : "
                     << ratio
                     << "%" << endl;
            }
        }


        // ==========================================
        // Clear
        // ==========================================

        else if(choice == 4){

            lru.clearCache();

            lfu.clearCache();

            cout << "\nBoth caches cleared!"
                 << endl;
        }


        // ==========================================
        // Exit
        // ==========================================

        else if(choice == 5){

            cout << "\nExiting Web Cache Simulator..."
                 << endl;

            break;
        }


        else{

            cout << "\nInvalid choice!"
                 << endl;
        }
    }


    return 0;
}