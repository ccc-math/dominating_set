#include "data_types/graph.hpp"
using namespace std;


Graph::Graph(int vertices) {
        numVertices = vertices;
        NumEdges = 0;
        adjList.resize(vertices, {}); // graph with no edge
};

Graph::Graph(const Graph&  G) {
    numVertices = G.getNumVertices();
    adjList.resize(numVertices, {});
    for(int i = 0; i < numVertices; i++){
        for(int v : G.getNeighbours(i)){
            adjList[i].push_back(v);
        }
    }
};


Graph::Graph(std::string filename){
    // Open filename
    ifstream file;
    file.open(filename);
    // Check if the file is successfully opened
    if (!file.is_open()) {
        cerr << "Error opening the file! " << filename << endl;
        exit ( EXIT_FAILURE );
    }

    vector<vector<int>> edges = {}; // the set of all edges (needed to find the number of edges which is not given in the instance files for some reasons)
    int size = 0;
    string line;
    int has_read = 0;
    int node1 = 0;
    int node2 = 0;
    // Read a new line until EOF
    while (getline(file, line)) {
        std::stringstream s (line);
        string word;
        int word_count = 1;
        
        while(s >> word ){
            switch(word_count){
                case 1:

                    if(word.compare("p")!=0){
                        node1 = stoi(word);
                    }
                    break;
                case 2:

                    if(has_read == 1){
                        node2 = stoi(word);
                        this->addEdge(node1, node2);
                    }
                    break;
                case 3:
                    numVertices = stoi(word);
                    adjList.resize(numVertices, {});
                    break;
                case 4:                    

                    NumEdges = stoi(word);
                    has_read=1;
                    break;
            }
            word_count++;
            
        }

            
    }
    
    // Close the file
    file.close();
    // We now construct the graph
};


void Graph::addEdge(int u, int v) {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            if(v != u){
                adjList[u].push_back(v);
                adjList[v].push_back(u);
            }
        } else {
            std::cout << "Invalid vertex!" << std::endl; //Error
            exit ( EXIT_FAILURE );
        }
    };


int findPosElement(int e, vector<int> v){ // return the first position of an element in a vector
    for(int i = 0; i < v.size(); i++){
        if(e == v[i])
            return i;
    }
    return -1;
}

void Graph::disconnectVertex(int u){  // Delete all the edges aroud u
    for(int v : this->getNeighbours(u)){
        int pos = findPosElement(u, this->getNeighbours(v)); // locate u in the adj list of v
        if (pos >= 0){
          std::swap(adjList[v][pos], adjList[v][adjList[v].size() - 1]);
          adjList[v].pop_back();
        }
    } 
    adjList[u] = {};
}

bool Graph::hasEdge(int u, int v) const {
        if (u >= 0 && u < numVertices && v >= 0 && v < numVertices) {
            if(not(findPosElement(u,adjList[v])))
            {
                return false;
            }
            else {
                return true;
            }
        }
        return false;
    };

void Graph::printGraph_console() const {
        std::cout << "Adjacency list:" << std::endl;
        for (int i = 0; i < numVertices; ++i){
            std::cout << i << " :";
            for(int e : adjList[i]){
                std::cout << " " << e;
            }
            std::cout << std::endl;
        }
    };

int Graph::vertexCount()const  {
        return numVertices;
    };



int Graph::getNumVertices() const{
    return this->numVertices;
};


std::vector<int> Graph::getNeighbours(int v) const{
    return this->adjList[v];
};


bool Graph::isIsolated(int v)const {
    return this->adjList[v].size() == 0;
}

int Graph::getDegree(int v)const {
    return this->adjList[v].size();
}


