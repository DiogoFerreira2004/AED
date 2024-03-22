#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cmath>
#include <unordered_set>
#include <stack>
#include "Graph.hpp"


// Vertex implementations
Vertex::Vertex(const string& airport_code) {
    this->airportCode = airport_code;
}

string Vertex::getAirportCode() const {
    return airportCode;
}
const vector<Edge> &Vertex::getAdj() const {
    return adj;
}
bool Vertex::isVisited() const {
    return visited;
}
bool Vertex::isProcessing() const {
    return processing;
}
int Vertex::getNum() const {
    return num;
}
int Vertex::getLow() const {
    return low;
}

void Vertex::setAirportCode(string airport_code) {
    this->airportCode = airport_code;
}
void Vertex::setVisited(bool v) {
    this->visited = v;
}
void Vertex::setProcessing(bool p) {
    this->processing = p;
}
void Vertex::setNum(int num) {
    this->num = num;
}
void Vertex::setLow(int low) {
    this->low = low;
}
void Vertex::setAdj(const vector<Edge> &adj) {
    this->adj = adj;
}


// 3.ii
int Vertex::numDiffAirlines() const {
    unordered_set<string> airlineCodes;

    for (const Edge& elem : adj) {
        airlineCodes.insert(elem.getAirlineCode());
    }

    return airlineCodes.size();
}



// Edge Implementations
Edge::Edge(Vertex* dest, string airline_code) {
    this->dest = dest;
    this->airlineCode = airline_code;
}

Vertex *Edge::getDest() const {
    return dest;
}
string Edge::getAirlineCode() const {
    return airlineCode;
}

void Edge::setDest(Vertex* d) {
    this->dest = d;
}
void Edge::setAirlineCode(string airline_code) {
    this->airlineCode = airline_code;
}



// Graph Implementations
Graph::Graph() {
    vector<Vertex*> placeholder;
    this->airportSet = placeholder;
}


Graph::Graph(const string& file) {
    bool first = true;
    ifstream csv(file);
    string line;

    unordered_set<string> vertices_temp;

    string prevsource_, prevtarget_;

    while (getline(csv, line)) {
        if (!first) {
            string source_, target_, airline_;
            stringstream oneLine(line);
            getline(oneLine, source_, ',');
            getline(oneLine, target_, ',');
            getline(oneLine, airline_);

            if (source_ != prevsource_) {
                if (vertices_temp.find(source_) == vertices_temp.end()) {
                    airportSet.push_back(new Vertex(source_));
                    vertices_temp.insert(source_);
                }
            }

            if (target_ != prevtarget_) {
                if (vertices_temp.find(target_) == vertices_temp.end()) {
                    airportSet.push_back(new Vertex(target_));
                    vertices_temp.insert(target_);
                }
            }

            Vertex* sourceV = findVertex(source_);
            Vertex* destV = findVertex(target_);
            sourceV->addEdge(destV, airline_);
            prevsource_ = source_;
            prevtarget_ = target_;
        }
        else first = false;
    }
}


vector<Vertex*> Graph::getAirportSet() const {
    return airportSet;
};

int Graph::getNumVertex() const {
    return airportSet.size();
}


Vertex* Graph::findVertex(const string& airportCode) const {
    for (auto v : airportSet)
        if (v->airportCode == airportCode)
            return v;
    return NULL;
}


bool Graph::addVertex(const string& airportCode) {
    if (findVertex(airportCode) != NULL)
        return false;
    airportSet.push_back(new Vertex(airportCode));
    return true;
}

bool Graph::removeVertex(const string& airportCode) {
    for (auto it = airportSet.begin(); it != airportSet.end(); it++)
        if ((*it)->airportCode  == airportCode) {
            auto v = *it;
            airportSet.erase(it);
            for (auto u : airportSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}

bool Graph::addEdge(const string &source, const string &dest, const string& airline_code) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    v1->addEdge(v2, airline_code);
    return true;
}

void Vertex::addEdge(Vertex *d, const string& airlineCode) {
    adj.emplace_back(d, airlineCode);
}


bool Graph::removeEdge(const string &source, const string &dest) {
    auto v1 = findVertex(source);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

bool Vertex::removeEdgeTo(Vertex* dest) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == dest) {
            adj.erase(it);
            return true;
        }
    return false;
}



// 3.i
int Graph::numTotalFlights() const {
    int res = 0;
    for (Vertex* airport : airportSet) {
        for (const Edge& flight : airport->adj){
            res++;
        }
    }
    return res;
}

// 3.iii
int Graph::numFlightsPerCity(const vector<string>& airportsPerCity) const {
    int res = 0;

    for (const string& airportCode : airportsPerCity) {
        res += findVertex(airportCode)->adj.size();
    }

    return res;
}

int Graph::numFlightsPerAirline(const string &airlineCode) const {
    int counter = 0;

    for (Vertex* airport : airportSet) {
        for (const Edge& flight : airport->adj){
            if (flight.airlineCode == airlineCode) counter++;
        }
    }

    return counter;
}

// 3.iv
int Graph::numCountriesPerAirportDirect(const string& airportCode, const AllAirports& allAirports) const { // Direct flights
    unordered_set<string> countriesVisited;
    Vertex* currAirport = findVertex(airportCode);

    for (const Edge& edge : currAirport->adj) {
        Airport airport_temp = Airport(edge.dest->airportCode, "", "", "", 0, 0);
        countriesVisited.insert(allAirports.getAirports().find(airport_temp)->getCountry());
    }

    return countriesVisited.size();
}

int Graph::numCountriesPerCityDirect(const vector<string> &airportsPerCity, const AllAirports& allAirports) const {
    unordered_set<string> countriesVisited;

    for (const string& airportCode : airportsPerCity) {
        Vertex* currAirport = findVertex(airportCode);

        for (const Edge& edge : currAirport->adj) {
            Airport airport_temp = Airport(edge.dest->airportCode, "", "", "", 0, 0);
            countriesVisited.insert(allAirports.getAirports().find(airport_temp)->getCountry());
        }
    }
    return countriesVisited.size();
}


// 3.v
int Graph::numAirportsPerAirport(const string &airportCode) const {
    return dfs(airportCode).size()-1;
}

int Graph::numCitiesPerAirport(const string &airportCode, const AllAirports &allAirports) const {
    unordered_set<string> citiesVisited;
    vector<string> airportsVisited = dfs(airportCode);

    for (const string& visit : airportsVisited) {
        if (visit != airportCode) {
            Airport airport_temp = Airport(visit, "", "", "", 0, 0);
            citiesVisited.insert(allAirports.getAirports().find(airport_temp)->getCity());
        }
    }

    return citiesVisited.size();
}

int Graph::numCountriesPerAirport(const string& airportCode, const AllAirports& allAirports) const {
    unordered_set<string> countriesVisited;
    vector<string> airportsVisited = dfs(airportCode);

    for (const string& visit : airportsVisited) {
        if (visit != airportCode) {
            Airport airport_temp = Airport(visit, "", "", "", 0, 0);
            countriesVisited.insert(allAirports.getAirports().find(airport_temp)->getCountry());
        }
    }

    return countriesVisited.size();
}


// 3.vi
int Graph::numAirportsX(const string &airportCode, int x) const {
    return bfsWithStops(airportCode, x).size();
}

int Graph::numCitiesX(const string &airportCode, int x, const AllAirports& allAirports) const {
    unordered_set<string> citiesVisited;
    vector<string> airportsVisited = bfsWithStops(airportCode, x);

    for (const string& visit : airportsVisited) {
        Airport airport_temp = Airport(visit, "", "", "", 0, 0);
        citiesVisited.insert(allAirports.getAirports().find(airport_temp)->getCity());
    }

    return citiesVisited.size();
}

int Graph::numCountriesX(const string& airportCode, int x, const AllAirports& allAirports) const {
    unordered_set<string> countriesVisited;
    vector<string> airportsVisited = bfsWithStops(airportCode, x);

    for (const string& visit : airportsVisited) {
        Airport airport_temp = Airport(visit, "", "", "", 0, 0);
        countriesVisited.insert(allAirports.getAirports().find(airport_temp)->getCountry());
    }

    return countriesVisited.size();
}


vector<string> Graph::dfs() const {
    vector<string> res;
    for (auto v : airportSet)
        v->visited = false;
    for (auto v : airportSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}


// For 3.v
vector<string> Graph::dfs(const string& source) const {
    vector<string> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : airportSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}

// For 3.v
void Graph::dfsVisit(Vertex* v, vector<string>& res) const {
    v->visited = true;
    res.push_back(v->airportCode);
    for (auto &e: v->adj) {
        auto w = e.dest;
        if (!w->visited)
            dfsVisit(w, res);
    }
}



vector<string> Graph::bfs(const string& source) const {
    vector<string> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Vertex *> q;
    for (auto v : airportSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->airportCode);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}



vector<string> Graph::bfsWithStops(const string& source, int numLayovers) const {
    vector<string> res;
    queue<Vertex*> tempVisited;
    int stopLevel = 0;

    for (Vertex* v : airportSet) { // O(v), v number of Vertexes
        v->visited = false;
    }

    Vertex* sourceV = findVertex(source); // O(v), v number of Vertexes
    sourceV->visited = true;
    tempVisited.push(sourceV);
    // Purposefully not add source to res, because it's not a destination

    // O(v2 + e2), v2 number of Vertexes until depth of numLayovers+1, e2 number of edges of all Vertexes until depth of numLayovers+1
    while (stopLevel < numLayovers+1 and !tempVisited.empty()) { // +1 para visitar o inicio e o fim, sem os contar como layovers
        int initLevelSize = tempVisited.size();
        for (int i = 0; i < initLevelSize; i++) { // Percorre o nível todo
            for (const Edge& edge : tempVisited.front()->adj) {
                if (!edge.dest->visited) {
                    edge.dest->visited = true;
                    tempVisited.push(edge.dest);
                    res.push_back(edge.dest->airportCode);
                }
            }
            tempVisited.pop();
        }
        stopLevel++;
    }

    return res;
}


//3.vii
vector<pair<string, string>> Graph::diameter(int& maxDist) const {
    vector<pair<string, string>> res;
    unordered_map<Vertex*, int> vex_depth;
    queue<Vertex*> q;

    for (Vertex* airport : airportSet) { // O(V)
        q.push(airport);
        vex_depth[airport] = 0;

        while (!q.empty()) { // O(V + E) in the worse case
            Vertex* curr = q.front();
            for (const Edge& edge : curr->adj) {
                Vertex* neighbor = edge.dest;
                if (vex_depth[neighbor] == 0) {
                    q.push(neighbor);
                    vex_depth[neighbor] = vex_depth[curr] + 1;
                }
            }
            q.pop();
        }

        for (pair<Vertex*, int> vd : vex_depth) { // O(V) in the worse case
            if (vd.second > maxDist) {
                maxDist = vd.second;
                res.clear();
                res.emplace_back(airport->airportCode, vd.first->airportCode);
            }
            else if (vd.second == maxDist) {
                res.emplace_back(airport->airportCode, vd.first->airportCode);
            }
        }
        vex_depth.clear();
    }
    return res;
}


//3.viii
void Graph::topXAirports(int x) const {
    int i = 1;
    map<string, int> allAirportsTraffic = airportTrafficCapacity();

    multimap<int, string, greater<>> byValue;
    transform(allAirportsTraffic.begin(), allAirportsTraffic.end(),
              inserter(byValue, byValue.begin()),
              [](const pair<string,int>& pair) { return make_pair(pair.second, pair.first); });
    // Sorting has time complexity of O(n log n), where n is the size of allAirportsTraffic, which is the total amount of vertices in the Graph (V)

    cout << "Top " << x << " Airports (by total number of flights): \n";
    for (const auto& elem : byValue) {
        if (i <= x) {
            cout << i << ". " << "Airport " << elem.second << " with " << elem.first << " flights.\n";
            i++;
        }
    }
    if (x > byValue.size()) cout << "Note that " << byValue.size() << " is the maximum amount of airports stored in the dataset." << "\n";
}

map<string,int> Graph::airportTrafficCapacity() const {
    map<string, int> airportTraffic;

    // O(V + E), visits all vertices and all edges in the graph
    for (Vertex* airport : airportSet) {
        for (const Edge& edge : airport->adj) {
            airportTraffic[airport->airportCode]++;
            airportTraffic[edge.dest->airportCode]++;
        }
    }
    return airportTraffic;
}


//3.ix
unordered_set<string> Graph::articulationPoints() const {
    int i = 1;
    unordered_set<string> res;

    for (Vertex* v : airportSet) {
        v->visited = false;
        v->processing = false;
        v->num = -1;
        v->low = -1;
    }
    for (Vertex* v : airportSet) {
        if (v->num == -1) {
            dfsForArtPoints(v, res, i, v->airportCode);
        }
    }

    return res;
}

void Graph::dfsForArtPoints(Vertex* v, unordered_set<string>& artPoints, int& i, const string& ogVertContent) const {
    v->num = v->low = i;
    i++;
    v->processing = true;
    int children = 0;

    for (const Edge& edge : v->adj) {
        Vertex* w = edge.dest;
        if (w->num == -1) {
            children++;
            dfsForArtPoints(w,artPoints,i,ogVertContent);
            v->low = min(v->low, w->low);

            if (w->low >= v->num) {
                artPoints.insert(v->airportCode); // v is an articulation point
            }
        }
        else if (w->processing) {
            v->low = min(v->low, w->num);
        }
    }
    v->processing = false;
    if (v->airportCode == ogVertContent && children > 1) artPoints.insert(v->airportCode);
}


// 4. e 5.
void Graph::findBestOption(const string& source, const string& dest, int airlineFilter, const string& airlines, const AllAirports& allAirports) const {
    vector<string> inputs = {source, dest};
    vector<vector<string>> normalizedInputs = interpretInputs(inputs, allAirports);
    vector<string> normSource = normalizedInputs[0];
    vector<string> normDest = normalizedInputs[1];

    // Check validity of input, end execution if not valid
    if(!inputsValid(normSource, normDest)) return;

    // Prepare airline filters (they intervene in finding possible shortest paths)
    set<string> airlinesToFilter;
    if (airlineFilter == 1 or airlineFilter == 2) {
        airlinesToFilter = findAirlinesToFilter(airlines);
    }

    // Find all possible shortest paths
    vector<vector<string>> paths = findAllShortestPaths(normSource, normDest, airlineFilter, airlinesToFilter);

    // Check if there are any paths
    if (!existPaths(paths)) return;

    // User input: minimize number of airlines
    if (airlineFilter == 3) {
        vector<pair<TYPE_PATH, TYPE_MinAIRLINES>> res = findLeastAirlinesPerPath(paths);

        // check the path that uses the least amount of airports
        int minNumAirlines = INT_MAX;
        for (pair<TYPE_PATH, TYPE_MinAIRLINES> pair : res) {
            if (pair.second[0].size() < minNumAirlines) {
                minNumAirlines = pair.second[0].size();
            }
        }

        // Show the result
        filter3Printer(minNumAirlines, res, allAirports);
        return;
    }

    // Show the result
    bestOptionPrinter(paths, allAirports);
}

vector<vector<string>> Graph::interpretInputs(const vector<string>& inputs, const AllAirports& allAirports) const {
    vector<vector<string>> res;

    // Normalize inputs from the format in the menu to workable format
    for (const string& input : inputs) {
        if (isdigit(input[0]) or input[0] == '-') {
            res.push_back(interpretCoords(input, allAirports));
        }
        else if (input.rfind("AC.", 0) == 0) {
            res.push_back({input.substr(3)});
        }
        else if (input.rfind("AN.", 0) == 0) {
            res.push_back({interpretAirportName(input.substr(3), allAirports)});
        }
        else if (input.rfind("CN.", 0) == 0) {
            res.push_back(interpretCityName(input.substr(3), allAirports));
        }
    }

    // Empty input handling
    if (res.empty() or res[0].empty() or res[1].empty()) {
        vector<vector<string>> error_res;
        error_res.push_back(vector<string>{""}); // empty source input, to be detected by other functions
        error_res.push_back(vector<string>{""}); // empty dest input
        return error_res;
    }
    return res;
}

vector<string> Graph::interpretCoords(const string& input, const AllAirports& allAirports) const {
    vector<string> res;
    double minDist, dist;
    bool first = true;

    stringstream inputLine(input);
    string lat1, lon1;
    getline(inputLine, lat1, '_');
    getline(inputLine, lon1);

    for (const Airport& airport : allAirports.getAirports()) {
        if (!first) {
            dist = haversineFormula(stod(lat1), stod(lon1), airport.getLatitude(), airport.getLongitude());
            if (minDist > dist) {
                minDist = dist;
                res.clear();
                res.push_back(airport.getCode());
            }
            else if (minDist == dist) res.push_back(airport.getCode());
        }
        else {
            minDist = haversineFormula(stod(lat1), stod(lon1), airport.getLatitude(), airport.getLongitude());
            res.push_back(airport.getCode());
            first = false;
        }
    }

    return res;
}
double Graph::haversineFormula(double lat1, double lon1, double lat2, double lon2) const {
    lat1 *= (M_PI / 180.0);
    lon1 *= (M_PI / 180.0);
    lat2 *= (M_PI / 180.0);
    lon2 *= (M_PI / 180.0);

    double latDeg = lat2 - lat1;
    double lonDeg = lon2 - lon1;

    double aux = sin(latDeg / 2) * sin(latDeg / 2) +
               cos(lat1) * cos(lat2) *
               sin(lonDeg / 2) * sin(lonDeg / 2);

    double dist = 2 * atan2(sqrt(aux), sqrt(1 - aux));
    return 6371.0 * dist;
}

string Graph::interpretAirportName(const string& input, const AllAirports& allAirports) const {
    for (const Airport& airport : allAirports.getAirports()) {
        if (airport.getName() == input) return airport.getCode();
    }
    return "";
}

vector<string> Graph::interpretCityName(const string& input, const AllAirports& allAirports) const {
    return allAirports.airportsPerCity(input);
}


bool Graph::inputsValid(const vector<string> &normSource, const vector<string> &normDest) const {
    for (const string& srcAirport : normSource) {
        if (srcAirport.empty()) {
            cout << "THE INPUT IS INVALID OR IT DOESN'T EXIST IN THE DATASET. TRY AGAIN!" << endl;
            return false;
        }
    }
    for (const string& destAirport : normDest) {
        if (destAirport.empty()) {
            cout << "THE INPUT IS INVALID OR IT DOESN'T EXIST IN THE DATASET. TRY AGAIN!" << endl;
            return false;
        }
    }
    return true;
}


set<string> Graph::findAirlinesToFilter(const string& airlines) const {
    set<string> res;
    stringstream airlinesStream(airlines);
    string airline;

    while (getline(airlinesStream, airline, ',')) {
        res.insert(airline);
    }
    return res;
}


vector<vector<string>> Graph::findAllShortestPaths(const vector<string>& normSource, const vector<string>& normDest, int airlineFilter, const set<string>& airlinesToFilter) const {
    vector<vector<string>> paths;

    int shortestPath = INT_MAX;
    // Comparar as menores paths quando há vários aeroportos
    for (const string& srcAirport : normSource) {
        for (const string& destAirport : normDest) {
            vector<vector<string>> newPaths = bfsForAllShortestPaths(srcAirport, destAirport, airlineFilter, airlinesToFilter);
            for (const vector<string>& newPath : newPaths) {
                if (newPath.size() < shortestPath) {
                    shortestPath = newPath.size();
                    paths.clear();
                    paths.push_back(newPath);
                }
                else if (newPath.size() == shortestPath) {
                    paths.push_back(newPath);
                }
            }
        }
    };

    return paths;
}

vector<vector<string>> Graph::bfsForAllShortestPaths(const string& source, const string& dest, int airlineFilter, set<string> airlinesToFilter) const {
    queue<Vertex*> q;
    set<Vertex*> auxQ; // used to check if Vertex has already been added to the queue

    unordered_map<string, set<string>> parentsOfVert;
    unordered_map<string, int> levelOfVert;

    bool foundDest = false;

    for (Vertex* airport : airportSet) { // O(v), v are all vertices in the graph
        airport->visited = false;
        levelOfVert[airport->airportCode] = -1;
    }


    Vertex* sourceV = findVertex(source); // O(v), v are all vertices in the graph
    q.push(sourceV);
    auxQ.insert(sourceV);
    sourceV->visited = true;
    levelOfVert[source] = 0;

    // O(v2 + e2)), runs for all vertices and edges between source and dest (not including findVertex inside the loops)
    while (!q.empty()) {
        Vertex* currentV = q.front();

        if (currentV->airportCode == dest) {
            // Base Case: Found the dest node and processed all edges to it -> DONE
            foundDest = true;
            break;
        }

        for (const Edge& edge : currentV->adj) {
            if ( (airlinesToFilter.find(edge.airlineCode) == airlinesToFilter.end() and airlineFilter == 1) or (airlinesToFilter.find(edge.airlineCode) != airlinesToFilter.end() and airlineFilter == 2) ) {
                // didn't find airline in whitelist (airlineFilter == 1) or found airline in blacklist (airlineFilter == 2)
                continue;
            }
            Vertex* neighborV = edge.dest;
            if (!neighborV->visited) {
                if (auxQ.find(neighborV) == auxQ.end()) {
                    q.push(neighborV);
                    auxQ.insert(neighborV);
                }
                if (levelOfVert[currentV->airportCode] != levelOfVert[neighborV->airportCode]) {
                    parentsOfVert[neighborV->airportCode].insert(currentV->airportCode);
                    levelOfVert[neighborV->airportCode] = levelOfVert[currentV->airportCode] + 1;
                }
            }
        }
        q.pop();
        auxQ.erase(currentV);
        currentV->visited = true;
    }
    // No path found
    if (!foundDest) return {};

    // DFS from target node to the starting node;
    vector<vector<string>> res;
    list<string> path;
    dfsBackwards(dest, parentsOfVert, res, path);

    return res;
}

void Graph::dfsBackwards(const string& vert, unordered_map<string, set<string>>& parentsOfVert, vector<vector<string>>& res, list<string>& path) const {
    path.push_front(vert);
    if (parentsOfVert[vert].empty()) {
        // Base case: reached source vertex
        res.emplace_back(path.begin(), path.end());
    }
    for (const auto& parent : parentsOfVert[vert]) {
        dfsBackwards(parent, parentsOfVert, res, path);
    }
    // Remove the processed element from path
    path.pop_front();
}


bool Graph::existPaths(const vector<vector<string>>& paths) const {
    if (paths.empty()) {
        cout << "=================================================================================\n"
             << "Given the inputted source, destination and filters, there is no path available.\n"
             << "(This can be happen because of either of the inputs)\n";
        return false;
    }
    return true;
}


vector<pair<TYPE_PATH, TYPE_MinAIRLINES>> Graph::findLeastAirlinesPerPath(const vector<vector<string>>& paths) const {
    vector<pair<TYPE_PATH, TYPE_MinAIRLINES>> res;

    vector<vector<string>> airlinesPerPath;
    vector<vector<string>> airlinesCombs;
    vector<vector<string>> minAirlinesPerPath;

    for (const vector<string>& path : paths) {
        airlinesPerPath = airlineFinder(path);
        airlinesCombs = getAllCombinations(airlinesPerPath);
        minAirlinesPerPath = getLeastAirlines(airlinesCombs);

        res.emplace_back(path, minAirlinesPerPath);
    }

    return res;
}

vector<vector<string>> Graph::airlineFinder(const vector<string>& path) const {
    vector<vector<string>> pathAirlines;

    for (int i = 0; i < path.size()-1; i++) {
        Vertex* stop1 = findVertex(path[i]);
        vector<string> airlinesPerEdge;
        for (const Edge& edge : stop1->adj) {
            if (edge.dest->airportCode == path[i+1]) {
                airlinesPerEdge.push_back(edge.airlineCode);
            }
        }
        pathAirlines.push_back(airlinesPerEdge);
        airlinesPerEdge.clear();
    }
    return pathAirlines; //[[A,B],[C,D],[E,F]]
}

vector<vector<string>> Graph::getAllCombinations(const vector<vector<string>>& airlines) const{
    vector<vector<string>> result;
    vector<string> current;
    generateCombinations(airlines, current, result, 0);
    return result;
}

void Graph::generateCombinations(const vector<vector<string>>& airlines, vector<string>& current, vector<vector<string>>& result, int depth) const{
    if (depth == airlines.size()) {
        result.push_back(current);
        return;
    }

    for (const string& str : airlines[depth]) {
        current.push_back(str);
        generateCombinations(airlines, current, result, depth + 1);
        current.pop_back();
    }
}

vector<vector<string>> Graph::getLeastAirlines(const vector<vector<string>>& combinations) const {
    unordered_set<string> airlinesUsed_temp;
    vector<vector<string>> leastAirlinesUsed;
    bool first = true;

    for (const vector<string>& comb : combinations) {
        for (const string& airline : comb) {
            if (airlinesUsed_temp.find(airline) == airlinesUsed_temp.end()) {
                airlinesUsed_temp.insert(airline);
            }
        }
        if (!first) {
            if (airlinesUsed_temp.size() < leastAirlinesUsed.size()){
                leastAirlinesUsed.clear();
                leastAirlinesUsed.emplace_back(airlinesUsed_temp.begin(), airlinesUsed_temp.end());
            }
            else if (airlinesUsed_temp.size() == leastAirlinesUsed.size()) {
                leastAirlinesUsed.emplace_back(airlinesUsed_temp.begin(), airlinesUsed_temp.end());
            }
        }
        else {
            leastAirlinesUsed.emplace_back(airlinesUsed_temp.begin(), airlinesUsed_temp.end());
            first = false;
        }
        airlinesUsed_temp.clear();
    }

    return leastAirlinesUsed;
}


void Graph::filter3Printer(int minNumAirlines, const vector<pair<TYPE_PATH, TYPE_MinAIRLINES>>& res, const AllAirports& allAirports) const {
    int numPath = 1;
    cout << "=================================================================================\n"
         << "The best flight option(s), taking your filters into account, is: \n";
    for (const auto& elem : res) {
        if (elem.second[0].size() == minNumAirlines) { // check if it's a path that uses a minimum amount of airlines
            cout << "\n" << numPath++ << ". ";
            for (int i = 0; i < elem.first.size(); i++) { // print path
                cout << elem.first[i] << " (" << allAirports.nameOfCode(elem.first[i]) << ", "
                     << allAirports.cityOfCode(elem.first[i]) << ", " << allAirports.countryOfCode(elem.first[i])
                     << ")";
                if (i != elem.first.size() - 1) cout << " -> \n-> ";
            }

            for (int j = 0; j < elem.second.size(); j++) { // print information about airlines
                if (j == 0) cout << "\nAirlines used: ";
                for (int k = 0; k < elem.second[j].size(); k++) {
                    cout << elem.second[j][k];
                    if (k != elem.second[j].size() - 1) cout << ", ";
                }
                if (j != elem.second.size() - 1) cout << " or ";
                else if (j == elem.second.size() - 1) cout << "\n";
            }
        }
    }
    cout << "\nMinimum number of airlines: " << minNumAirlines << "\n";
}

void Graph::bestOptionPrinter(const vector<vector<string>>& paths, const AllAirports& allAirports) const {
    int numPath = 1;

    cout << "=================================================================================\n"
         << "The best flight option(s), taking your filters into account, is: \n";
    for (vector<string> path : paths) {
        cout << "\n" << numPath++ << ". ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] << " (" << allAirports.nameOfCode(path[i]) << ", " << allAirports.cityOfCode(path[i]) << ", " << allAirports.countryOfCode(path[i]) << ")";
            if (i != path.size() - 1) cout << " -> \n-> ";
        }
        cout << "\n";
    }
}
