#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <queue>

// Rules and updates vectors to be used post separation
std::vector<std::pair<int, int>> rules; 
std::vector<std::vector<int>> updates;

// Function to check validity of update
bool isUpdateValid(const std::vector<int>& update) {
    for (const auto& rule : rules) {
        int x = rule.first, y = rule.second;

        auto itX = std::find(update.begin(), update.end(), x);
        auto itY = std::find(update.begin(), update.end(), y);

        if (itX != update.end() && itY != update.end() && itX > itY) {
            return false;
        }
    }
    return true;
}

// Function to get the middle page of an update
int getMiddlePage(const std::vector<int>& update) {
    return update[update.size() / 2];
}

// Function to reorder an update using topological sort
std::vector<int> reorderUpdate(const std::vector<int>& update) {
    // Build a graph for the update based on the rules
    std::unordered_map<int, std::vector<int>> graph;
    std::unordered_map<int, int> inDegree;
    std::unordered_set<int> updateSet(update.begin(), update.end());

    // Initialize graph and in-degree
    for (int page : update) {
        graph[page] = {};
        inDegree[page] = 0;
    }

    // Add edges based on rules
    for (const auto& rule : rules) {
        int x = rule.first, y = rule.second;
        if (updateSet.count(x) && updateSet.count(y)) {
            graph[x].push_back(y);
            inDegree[y]++;
        }
    }

    // Perform topological sort
    std::queue<int> q;
    for (const auto& [page, degree] : inDegree) {
        if (degree == 0) {
            q.push(page);
        }
    }

    std::vector<int> sortedUpdate;
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        sortedUpdate.push_back(curr);

        for (int neighbor : graph[curr]) {
            inDegree[neighbor]--;
            if (inDegree[neighbor] == 0) {
                q.push(neighbor);
            }
        }
    }

    return sortedUpdate;
}

// Function to sum middle pages of reordered incorrect updates
int sumMiddlePagesOfReorderedUpdates() {
    int total = 0;

    for (const auto& update : updates) {
        if (!isUpdateValid(update)) {
            std::vector<int> correctedUpdate = reorderUpdate(update);
            total += getMiddlePage(correctedUpdate);
        }
    }

    return total;
}

int main() {
    std::ifstream infile("input.txt");
    std::string line;

    bool readingUpdates = false;

    while (std::getline(infile, line)) {
        if (line.empty()) {
            readingUpdates = true;
            continue;
        }

        if (!readingUpdates) {
            std::replace(line.begin(), line.end(), '|', ' ');
            std::istringstream ruleStream(line);
            int x, y;
            ruleStream >> x >> y;
            rules.emplace_back(x, y);
        } else {
            std::vector<int> update;
            std::replace(line.begin(), line.end(), ',', ' ');
            std::istringstream updateStream(line);
            int page;
            while (updateStream >> page) {
                update.push_back(page);
            }
            updates.push_back(update);
        }
    }

    int result = sumMiddlePagesOfReorderedUpdates();
    std::cout << "Total sum of middle pages from reordered updates: " << result << std::endl;

    return 0;
}
