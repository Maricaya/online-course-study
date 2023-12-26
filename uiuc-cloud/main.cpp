#include <iostream>
#include <vector>
#include <set>
#include <random>

class Node {
public:
    Node(int id) : id(id) {}

    void addNeighbor(Node *neighbor) {
        neighbors.insert(neighbor);
    }

    void gossip() {
        if (message.empty()) {
            return;
        }

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, neighbors.size() - 1);
        int index = dis(gen);
        auto it = std::next(neighbors.begin(), index);
        (*it)->receive(message);
    }

    void receive(const std::string &msg) {
        if (message.empty()) {
            message = msg;
            std::cout << "Node " << id << " received message: " << message << std::endl;
            gossip();
        }
    }

private:
    int id;
    std::set<Node *> neighbors;
    std::string message;
};

int main() {
    std::vector<Node> nodes;
    for (int i = 0; i < 10; ++i) {
        nodes.emplace_back(i);
    }

    for (int i = 0; i < 10; ++i) {
        for (int j = i + 1; j < 10; ++j) {
            nodes[i].addNeighbor(&nodes[j]);
            nodes[j].addNeighbor(&nodes[i]);
        }
    }

    nodes[0].receive("Hello, world!");
    nodes[0].gossip();

    return 0;
}