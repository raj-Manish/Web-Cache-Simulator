# Web Cache Simulator

A high-performance C++ simulation of web caching mechanisms comparing **LRU (Least Recently Used)** and **LFU (Least Frequently Used)** eviction policies, featuring real-time **TTL (Time-To-Live)** cache expiration and persistent storage simulation.

---

## 🚀 Features

- **LRU Cache Implementation**:
  - $O(1)$ lookup, insertion, and deletion using an `std::unordered_map` and a custom Doubly Linked List.
  - Automatically moves recently accessed items to the head and evicts the least recently used item from the tail.

- **LFU Cache Implementation**:
  - $O(1)$ frequency-based cache with tie-breaking via LRU policy.
  - Uses frequency buckets (`LFUList`) and hash maps to track page frequencies and recency.

- **TTL (Time-To-Live) Expiration**:
  - Tracks timestamp for each cached page using `std::chrono::steady_clock`.
  - Stale pages beyond the configured TTL are automatically expired and treated as cache misses.

- **Simulated Persistent Storage**:
  - Simulates backend storage retrieval from a pipe-delimited flat-file database (`pages.txt`).

- **Interactive CLI & Analytics**:
  - Command-line interface to interactively simulate web page visits.
  - Compares cache performance in real-time by tracking total requests, hits, misses, and hit ratios for both LRU and LFU.

---

## 🛠️ Tech Stack

- **Language**: C++ (C++11 or higher)
- **Standard Library (STL)**: `<unordered_map>`, `<chrono>`, `<fstream>`, `<sstream>`, `<iostream>`, `<string>`
- **Compiler**: GCC / MinGW-w64 (`g++`)
- **Architecture**: Modular header-only data structures (`LRUCache.h`, `LFUCache.h`, `Storage.h`, `WebPage.h`)

---

## 📁 Project Structure

```text
├── LFUCache.h      # LFU Cache implementation with frequency buckets and TTL
├── LRUCache.h      # LRU Cache implementation with Doubly Linked List and TTL
├── Storage.h       # Simulated backend file storage reader
├── WebPage.h       # Data model representing a web page (URL, Title, Content)
├── pages.txt       # Flat-file database containing sample web pages
├── main.cpp        # CLI menu and cache simulation driver
├── .gitignore      # Git ignore configuration
└── README.md       # Project documentation
```

---

## 💻 Getting Started

### Prerequisites

- A modern C++ compiler (such as `g++` via MinGW-w64 on Windows or GCC on Linux/macOS).

### Compilation

Compile the project using `g++`:

```bash
g++ -std=c++17 main.cpp -o main
```

### Running the Simulator

Execute the compiled binary:

```bash
# On Windows
.\main.exe

# On Linux / macOS
./main
```

### Usage Instructions

1. Enter your desired **cache capacity** and **TTL in seconds** when prompted.
2. Select options from the interactive menu:
   - `1`: **Visit URL** (e.g., `google.com`, `github.com`, `leetcode.com`)
   - `2`: **Show Caches** (view current state of both LRU and LFU caches)
   - `3`: **Show Statistics** (inspect hit count, miss count, and hit ratio)
   - `4`: **Clear Caches** (reset both caches)
   - `5`: **Exit**

---

## 📊 Sample Output

```text
Enter cache capacity: 3
Enter TTL (seconds): 10

================================
       Web Cache Simulator
================================
1. Visit URL
2. Show Caches
3. Show Statistics
4. Clear Caches
5. Exit

Enter choice: 1
Enter URL: google.com
[Cache Miss] Fetching from storage...
Added to LRU and LFU caches.
```

---

## 📄 License

This project is licensed under the MIT License - feel free to use and modify for learning and projects!
