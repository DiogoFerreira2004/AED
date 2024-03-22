#ifndef AED2_GRAPH_HPP
#define AED2_GRAPH_HPP

#include <cstddef>
#include <vector>
#include <queue>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include "Airport.hpp"
#include "Airline.hpp"
#include "AllAirports.hpp"
using namespace std;

typedef vector<string> TYPE_PATH;
typedef vector<vector<string>> TYPE_MinAIRLINES;


class Vertex;
class Edge;
class Graph;

/// @brief Class for Vertices of a graph (Graph class).
/// @details Each Vertex object represents an Airport object through its airportCode.
/// @see Airport.hpp
/// @see AllAirports.hpp
class Vertex {
private:
    /// @brief Airport's code to find the associated Airport object.
	string airportCode;
    /// @brief All the outgoing Edge objects of the Vertex object.
	vector<Edge> adj;
    /// @brief Auxiliary field used in DFS and BFS algorithms.
    /// @details Used to, during a DFS or BFS traversal, know if a Vertex object has been iterated through (visited) already
	bool visited;
    /// @brief Auxiliary field used in other Graph algorithms.
    /// @details Used to know if a Vertex object is current being processed during a traversal.
    /// @see Graph::articulationPoints()
    bool processing;
    /// @brief Auxiliary field used in other Graph algorithms.
    /// @details Represents the order in which Vertex object are visited during a traversal.
    /// @see Graph::articulationPoints()
    int num;
    /// @brief Auxiliary field used in other Graph algorithms.
    /// @details Represents the lowest-order Vertex object reachable from the current Vertex object being processed during a traversal.
    /// @see Graph::articulationPoints()
    int low;

    /*!
     * @brief Adds an outgoing Edge object to the adj member variable.
     * @param dest Pointer to the Vertex object the Edge object connects to.
     * @param airline_code Airline code associated with the Edge object.
     * @note Time complexity: O(n), where n is the size of the airportSet member variable of the Graph class.
     * @see Graph::findVertex()
     */
    void addEdge(Vertex* dest, const string& airline_code);

    /*!
     * @brief Removes an outgoing Edge object from the adj member variable.
     * @details Iterates through the adj member variable, looking for the Edge object whose destination (other Vertex object where it's connect to) corresponds to dest parameter; If it finds the Edge, removes it;
     * @param dest Pointer to the Vertex object the Edge object connects to.
     * @returns true if the Edge object was found; <br>
     *          false if it wasn't;
     * @note Time complexity: O(n), where n is the size of the adj member variable;
     */
	bool removeEdgeTo(Vertex* dest);
public:
    /*!
     * @brief Parametrized constructor of the Vertex class.
     * @details Initializes the member variable with its respective parameter. The adj member variable is initialized using the addEdge() function. The other member variables are only used for specific algorithms, so they are initialized as needed;
     * @param airport_code Const reference to a string corresponding to the airportCode member variable
     * @note Time complexity: O(1).
     */
	Vertex(const string& airport_code);


    /*!
     * @brief Getter for the code of the airport the Vertex object refers to.
     * @returns String with the airport code.
     */
    string getAirportCode() const;

    /*!
     * @brief Getter for the vector of outgoing Edge objects.
     * @returns Vector of Edge objects.
     */
    const vector<Edge>& getAdj() const;

    /*!
     * @brief Getter for the visited state of the Vertex object.
     * @returns Boolean with the visited state.
     */
    bool isVisited() const;

    /*!
     * @brief Getter for the processing state of the Vertex object.
     * @returns Boolean with the processing state.
     */
    bool isProcessing() const;

    /*!
     * @brief Getter for the num member variable.
     * @returns Int with the num value.
     */
    int getNum() const;

    /*!
     * @brief Getter for the airport's code.
     * @returns Int with the low value.
     */
    int getLow() const;


    /*!
     * @brief Sets the value of the airportCode member variable.
     * @param airport_code String containing the new airport code.
     */
    void setAirportCode(string airport_code);

    /*!
     * @brief Sets the value of the adj member variable.
     * @param adj vector of Edge objects containing the new outgoing Edge objects.
     */
    void setAdj(const vector<Edge>& adj);

    /*!
     * @brief Sets the value of the visited member variable.
     * @param v boolean containing the new visited state.
     */
    void setVisited(bool v);

    /*!
     * @brief Sets the value of the processing member variable.
     * @param p boolean containing the new processing state.
     */
    void setProcessing(bool p);

    /*!
     * @brief Sets the value of the num member variable.
     * @param num int containing the new num value.
     */
    void setNum(int num);

    /*!
     * @brief Sets the value of the low member variable.
     * @param low int containing the new low value.
     */
    void setLow(int low);


    /*!
     * @brief Function that aids the implementation of exercise 3.ii.
     * @returns Total number of different airlines that an airport's outgoing flights use.
     * @note Time complexity: O(n), where n is the size of the adj member variable.
     */
    int numDiffAirlines() const;


    friend class Graph;
};


/// @brief Class for edges of a graph (Graph class).
/// @details Each Edge object represents a flight through the combination of: its source airport (airportCode in Vertex object), its destination airport (dest member variable) and airline (airlineCode member variable).
/// @see Airline.hpp
/// @see AllAirlines.hpp
class Edge {
private:
    /// @brief Pointer to the destination Vertex object (airport) of an Edge object.
	Vertex* dest;
    /// @brief Airline's code to find the Airline object associated with this flight.
	string airlineCode;
public:
    /*!
     * @brief Parametrized constructor of the Edge class.
     * @details Initializes the member variable with its respective parameter. The adj member variable is initialized using the addEdge() function. The other member variables are only used for specific algorithms, so they are initialized as needed;
     * @note Time complexity: O(1).
     */
	Edge(Vertex* dest, string airline_code);


    /*!
     * @brief Getter for the dest member variable.
     * @returns Pointer to the destination Vertex object.
     */
    Vertex* getDest() const;

    /*!
     * @brief Getter for the airline's code.
     * @returns String with the airline code.
     */
    string getAirlineCode() const;


    /*!
     * @brief Sets the value of the dest member variable.
     * @param dest Pointer to the new destination Vertex object.
     */
    void setDest(Vertex* dest);

    /*!
     * @brief Sets the value of the airlineCode member variable.
     * @param airline_code String containing the new airline code.
     */
    void setAirlineCode(string airline_code);


    friend class Graph;
	friend class Vertex;
};


/// @brief Class to represent a graph.
/// @see Vertex
/// @see Edge
class Graph {
private:
    /// @brief Member variable that stores all the Vertices of a Graph object.
	vector<Vertex*> airportSet;

    /*!
     * @brief Auxiliary function that aids the implementation of exercise 3.v.
     * @details Performs a DFS traversal: Visits a vertex (v) and its adjacent, recursively. Updates the res parameter with the list of visited Vertex contents.
     * @param v Pointer to the current Vertex object being visited.
     * @param res Gets updated with the list of visited Vertex's contents (ends up with the contents of all the visited vertices, ordered in dfs order)
     * @see dfs(const string& source)
     * @note Time complexity: O(V + E), where V corresponds to the source vertex and all its adjacents (which is all the vertices in the graph, in the worst case), and E corresponds to the number of outgoing edges from the source vertex and all its adjacents (which is all the edges in the graph, in the worst case).
     */
    void dfsVisit(Vertex* v, vector<string>& res) const;


    /*!
     * @brief Auxiliary function that aids the implementation of exercise 3.vi.
     * @details Performs a BFS traversal: starts at a specific source Vertex. Explores all vertices until it reaches a depth of numLayovers (included), given that the starting Vertex (source airport) and the destination Vertex (destination airport) don't count as layovers.
     * @param source Content of the source vertex.
     * @param numLayovers Number of layovers the flight should have.
     * @returns Vector with the airportCode of all vertices (airports) reachable in numLayovers amount of layovers.
     * @note Time complexity: O(V + v2 + e2), where V corresponds to all the vertices in the graph, v2 corresponds to all vertices until depth == numLayovers, and e2 corresponds to all edges until depth == numLayovers.
     * @see numAirportsX()
     * @see numCitiesX()
     * @see numCountriesX()
     */
    vector<string> bfsWithStops(const string& source, int numLayovers) const;


    /*!
     * @brief Auxiliary function that aids the implementation of exercise 3.viii.
     * @details Counts the amount of outgoing and ingoing edges for each vertex in the graph.
     * @returns Map containing the content of each vertex (airportCode) assigned to its respective number of outgoing and ingoing edges.
     * @note Time complexity: O(V + E), where V corresponds to the number of Vertices in the graph and E corresponds to the number of edges in the graph.
     * @see topXAirports()
     */
    map<string,int> airportTrafficCapacity() const;


    /*!
     * @brief Auxiliary function that aids the implementation of exercise 3.ix.
     * @details Modified Tarjan algorithm to find all the articulation points of the graph. <br>
     *          Articulation points are vertices whose removal increases the number of connected components/isolates parts of graph. <br>
     * @param v Pointer to the current Vertex object being processed during the DFS
     * @param artPoints Stores all the unique vertex contents (airportCodes) that represent an articulation point.
     * @param i Used to keep track of the order in which the vertices are visited during the DFS traversal and assign a unique number (Vertex object's num member variable) to each Vertex
     * @param ogVertContent Used to identify the "root" of the DFS, to know if it is also an articulation point or not.
     * @note Time complexity: O(V + E), where V corresponds to the number of Vertices in the graph and E corresponds to the number of edges in the graph.
     * @see articulationPoints()
     */
    void dfsForArtPoints(Vertex* v, unordered_set<string>& artPoints, int& i, const string& ogVertContent) const;


    /*!
     * @brief Auxiliary function that aids the implementation of exercises 4 and 5.
     * @details Given the source and destination inputs, interprets them according to how they are formatted (format is detailed in Menu12SrcDest::print())
     * @param inputs Contains the source and destination inputs
     * @param allAirports Used to access information about the airports.
     * @returns Vector containing 2 elements: all airport codes found from a given source input and all airport codes found from a given destination input.
     * @note Time complexity: the loop runs 2 times, because there are always only 2 inputs (source and destination). One of the functions below is called for each input, depending its type.
     *       - O(«complexity of interpretCoords()»), for an input that contains coordinates;
     *       - O(1), for an input that contains an airport code
     *       - O(«complexity of interpretAirportName()»), for input an that contains an airport name;
     *       - O(«complexity of interpretCityName()»), for input an that contains a city name;
     * @see interpretCoords()
     * @see interpretAirportName()
     * @see interpretCity()
     * @see findBestOption()
     */
    vector<vector<string>> interpretInputs(const vector<string>& inputs, const AllAirports& allAirports) const;

    /*!
     * @brief Auxiliary function for interpretInputs().
     * @details If one of the inputs (source or destination) contains latitude and longitude values, it finds the airport (or set of airports) that is closest to the location, using the Haversine Formula.
     * @param input One of the inputs (source or destination)
     * @param allAirports Used to access information about the airports.
     * @returns All airport codes found from interpreting one of the inputs.
     * @note Time complexity: O(n), where n is the total number of airports (Airport objects in allAirports).
     * @see haversineFormula()
     * @see interpretInputs()
     */
    vector<string> interpretCoords(const string& input, const AllAirports& allAirports) const;
    /*!
     * @brief Auxiliary function for interpretCoords().
     * @details Given latitude and longitude values for 2 locations, finds the distance between those places in kilometers.
     * @param lat1,lon1 Coordinates of location 1.
     * @param lat2,lon2 Coordinates of location 2.
     * @returns Distance between the 2 locations.
     * @note Time complexity: O(1).
     * @see interpretInputs()
     */
    double haversineFormula(double lat1, double lon1, double lat2, double lon2) const;

    /*!
     * @brief Auxiliary function for interpretInputs().
     * @details If one of the inputs (source or destination) has an airport name, it finds the airport's code.
     * @param input One of the inputs (source or destination)
     * @param allAirports Used to access information about the airports.
     * @returns The airport's code if there is an airport with the inputted name. <br>
     *          Empty string otherwise.
     * @note Time complexity: O(n), where n is the total number of airports (Airport objects in allAirports).
     * @see interpretInputs()
     */
    string interpretAirportName(const string& input, const AllAirports& allAirports) const;

    /*!
     * @brief Auxiliary function for interpretInputs().
     * @details If one of the inputs (source or destination) has the name of a city, it finds codes of all the airports in that city.
     * @param input One of the inputs (source or destination)
     * @param allAirports Used to access information about the airports.
     * @returns The codes of all the airports in that city.
     * @note Time complexity: O(n), where n is the total number of airports (Airport objects in allAirports).
     * @see AllAirports::airportsPerCity()
     * @see interpretInputs()
     */
    vector<string> interpretCityName(const string& input, const AllAirports& allAirports) const;


    /*!
     * @brief Auxiliary function for findBestOption().
     * @details Checks the validity of both inputs.
     * @param normSource airportCodes that correspond to the source input.
     * @param normDest airportCodes that correspond to the destination input.
     * @returns false if any of the inputs is invalid (one of the airport codes is an empty string).
     *          true if both are valid.
     * @note Time complexity: O(m+n), where m is the total number of source airports and n is the total number of destination airports (usually a very small number, between 1 and 10 each).
     * @see findBestOption()
     */
    bool inputsValid(const vector<string> &normSource, const vector<string> &normDest) const;


    /*!
     * @brief Auxiliary function for findBestOption().
     * @details Finds all the airlines codes inputted during the execution of Menu::Menu12Filters.
     * @param airlines Input with comma-separated airline codes.
     * @returns All the unique airline codes inputted.
     * @note Time complexity: O(n), where n is the total number of airline codes inputted.
     * @see findBestOption()
     */
    set<string> findAirlinesToFilter(const string& airlines) const;


    /*!
     * @brief Auxiliary function for findBestOption().
     * @details Runs bfsForAllShortestPaths for each combination of source-destination airports and checks if they are the shortest path among the combinations already ran
     * @param normSource airportCodes that correspond to the source input.
     * @param normDest airportCodes that correspond to the destination input.
     * @param airlineFilter int corresponding to the filter option selected during the execution of Menu::Menu12: <br>
     *                      1 - Whitelist filter <br>
     *                      2 - Blacklist filter <br>
     *                      3 - Minimize the amount of different airlines used <br>
     *                      4 - No filters
     * @param airlinesToFilter All the unique airline codes inputted.
     * @returns All the shortest paths from normSource to normDest.
     * @note Time complexity: O(s * d * («complexity of bfsForAllShortestPaths()» + n)). <br>
     *       - where s is the number of source airports, d is the number of destination airports and n is the number of shortest paths from all combinations of source-destination airports.
     * @see bfsForAllShortestPaths()
     * @see findBestOption()
     */
    vector<vector<string>> findAllShortestPaths(const vector<string>& normSource, const vector<string>& normDest, int airlineFilter, const set<string>& airlinesToFilter) const;
    /*!
     * @brief Auxiliary function for findAllShortestPaths().
     * @details Finds all the shortest paths between source and dest.
     * @param source airportCodes that correspond to the source input.
     * @param dest airportCodes that correspond to the destination input.
     * @param airlineFilter int corresponding to the filter option selected during the execution of Menu::Menu12: <br>
     *                      1 - Whitelist filter <br>
     *                      2 - Blacklist filter <br>
     *                      3,4 don't affect the function
     * @param airlinesToFilter All the unique airline codes inputted.
     * @returns All the shortest paths from source to dest.
     * @note Time complexity: O(V + v2 + e2 + «complexity of dfsBackwards()»). <br>
     *       - where V is the number of vertices, v2 is the number of vertices explored from source to dest (at worse case it's the same as V) and e2 is the number of edges explored from source to dest (at worst case it's all of them, E).
     * @see findVertex()
     * @see dfsBackwards()
     * @see findAllShortestPaths()
     * @see findBestOption()
     */
    vector<vector<string>> bfsForAllShortestPaths(const string& source, const string& dest, int airlineFilter, set<string> airlinesToFilter) const;
    /*!
     * @brief Auxiliary function for bfsForAllShortestPaths().
     * @details DFS traversal backtracks from dest to source (only Vertex without parents in parentsofDest) and forms paths by consecutively storing all the parents.
     * @param vert Content of the vertex currently being processed
     * @param parentsOfVert Maps a vertex's content to all of its parents.
     * @param res Where the resulting paths are stored.
     * @param path Used to form each individual path.
     * @note Time complexity: O(V). <br>
     *       - where V is the total number of vertices taking all the paths into account.
     * @see bfsForAllShortestPaths()
     * @see findBestOption()
     */
    void dfsBackwards(const string& vert, unordered_map<string, set<string>>& parentsOfVert, vector<vector<string>>& res, list<string>& path) const;

    /*!
     * @brief Auxiliary function for findBestOption().
     * @details Checks if there are any paths.
     * @param paths All the shortest paths found by bfsForAllShortestPaths().
     * @returns false if paths is empty. <br>
     *          true otherwise.
     * @note Time complexity: O(1).
     * @see bfsForAllShortestPaths()
     * @see findBestOption()
     */
    bool existPaths(const vector<vector<string>>& paths) const;


    /*!
     * @brief Auxiliary function for findBestOption().
     * @details For each path in paths, finds the combination of airlines that contains the least amount of airlines.
     * @param paths All the shortest paths found by bfsForAllShortestPaths().
     * @returns Vector with all the paths and their respective combination of least amount of airlines.
     * @note Time complexity: O( n*(«complexity of airlineFinder()» + «complexity of getAllCombinations()» + «complexity of getLeastAirlines()») ).
     * @see airlineFinder()
     * @see getAllCombinations()
     * @see getLeastAirlines()
     * @see bfsForAllShortestPaths()
     * @see findBestOption()
     */
    vector<pair<TYPE_PATH, TYPE_MinAIRLINES>> findLeastAirlinesPerPath(const vector<vector<string>>& paths) const;
    /*!
     * @brief Auxiliary function for findLeastAirlinesPerPath().
     * @details For each path, finds the possible airlines in each Edge.
     * @param path One of the shortest paths found by bfsForAllShortestPaths().
     * @returns All the possible airlines for each Edge.
     * @note Time complexity: O(n), where n is the size of the path.
     * @see findLeastAirlinesPerPath()
     */
    vector<vector<string>> airlineFinder(const vector<string>& path) const;
    /*!
     * @brief Auxiliary function for findLeastAirlinesPerPath().
     * @details Prepares the necessary data structures for the algorithm to process all the combinations of airlines.
     * @param airlines All the possible airlines for each Edge of a path.
     * @returns All the possible combinations of airlines of a path.
     * @note Time complexity: O(«complexity of generateCombinations()»).
     * @see generateCombinations()
     * @see findLeastAirlinesPerPath()
     */
    vector<vector<string>> getAllCombinations(const vector<vector<string>>& airlines) const;
    /*!
     * @brief Auxiliary function for getAllCombinations().
     * @details Generates all combinations given all the possible airlines for each Edge of a path.
     * @param airlines All the possible airlines for each Edge of a path.
     * @param current Current combination being generated.
     * @param result Stores all the generated combinations.
     * @param depth Keeps track of the depth of the recursion (max depth is the last Edge of the path).
     * @note Time complexity: O(ni^k): <br>
     *       - where ni is the number of airlines for the ith Edge and k is the number of Edges per path.
     * @see generateCombinations()
     * @see findLeastAirlinesPerPath()
     */
    void generateCombinations(const vector<vector<string>>& airlines, vector<string>& current, vector<vector<string>>& result, int depth) const;
    /*!
     * @brief Auxiliary function for getAllCombinations().
     * @details From all the airline combinations of a path, chooses the combination which has the least amount of unique airlines.
     * @param combinations All the possible combinations of airlines of a path.
     * @returns Combination with the least amount of unique airlines.
     * @note Time complexity: O(m*n) where m is the number of combinations in combinations and n is the number airlines per combination.
     * @see findLeastAirlinesPerPath()
     */
    vector<vector<string>> getLeastAirlines(const vector<vector<string>>& combinations) const;


    /*!
     * @brief Auxiliary function for findBestOption().
     * @details Prints all the shortest paths that use the least amount (minNumAirlines) of airlines.
     * @param minNumAirlines Minimum amount of unique airlines used from all the paths (calculated in findBestOption()).
     * @param res Vector with all the paths and their respective combination of least amount of airlines.
     * @param allAirports Used to access information about the airports.
     * @note Time complexity: O(1).
     * @see findBestOption()
     */
    void filter3Printer(int minNumAirlines, const vector<pair<TYPE_PATH, TYPE_MinAIRLINES>>& res, const AllAirports& allAirports) const;

    /*!
     * @brief Auxiliary function for findBestOption().
     * @details Prints all the shortest paths.
     * @param paths Vector with all the shortest paths.
     * @param allAirports Used to access information about the airports.
     * @note Time complexity: O(1).
     * @see findBestOption()
     */
    void bestOptionPrinter(const vector<vector<string>>& paths, const AllAirports& allAirports) const;
public:
    /*!
     * @brief Default constructor of the Graph class.
     * @details Initializes the airportSet member variable with an empty placeholder.
     * @note Time complexity: O(1).
     */
    Graph();

    /*!
     * @brief Parameterized constructor of the AllAirlines class.
     * @details Initializes the airportSet member variable with the required data, by reading it from a file.
     * @param file String containing the path to the .csv file.
     * @note Time complexity: O(n*«complexity of findVertex()»), where n is the number lines in the flights.csv file.
     * @see addVertex()
     * @see addEdge()
     */
    Graph(const string& file);


    /*!
     * @brief Getter for the airportSet member variable.
     * @returns Vector with all the vertices in the graph.
     */
    vector<Vertex*> getAirportSet() const;

    /*!
     * @brief Getter for the total number of vertices in the graph.
     * @returns Int with the number of vertices in the graph.
     */
    int getNumVertex() const;


    /*!
     * @brief Auxiliary function to find a vertex with a given content.
     * @param airportCode Content of the Vertex object.
     * @returns Pointer to vertex object if it was found. <br>
     *          NULL otherwise.
     * @note Time complexity: O(V), where V is the total number of vertices in the graph.
     */
    Vertex* findVertex(const string& airportCode) const;

    /*!
     * @brief Auxiliary function to add a Vertex into graph.
     * @param airportCode Content of the Vertex object.
     * @returns true if successful. <br>
     *          false if a vertex with that content already exists.
     * @note Time complexity: O(n), where n is the total number of vertices in the graph.
     */
	bool addVertex(const string& airportCode);

    /*!
     * @brief Auxiliary function to remove a Vertex from the graph.
     * @details Removes a Vertex with a given content from the graph, and all its outgoing and incoming edges.
     * @param airportCode Content of the Vertex object.
     * @returns true if successful. <br>
     *          false if a Vertex with that content doesn't exist.
     * @note Time complexity: O(n), where n is the total number of vertices in the graph.
     */
	bool removeVertex(const string& airportCode);

    /*!
     * @brief Auxiliary function to add an edge to the graph.
     * @details Adds an edge to the graph, given the contents of the source and destination Vertices, as well as the Edge content.
     * @param source Source of the Edge object.
     * @param dest Destination of the Edge object.
     * @param airlineCode Content of the Edge object.
     * @returns true if successful. <br>
     *          false if the source or destination vertex does not exist.
     * @note Time complexity: O(«complexity of findVertex()»).
     * @see findVertex()
     */
	bool addEdge(const string& source, const string& dest, const string& airlineCode);

    /*!
     * @brief Auxiliary function to remove an Edge from the graph.
     * @details The edge is identified by the source Vertex's (source) and destination Vertex's (dest) contents.
     * @param source Content of the source Vertex object.
     * @param dest Content of the dest Vertex object
     * @returns true if successful. <br>
     *          false if the Edge doesn't exist.
     * @note Time complexity: O(n), where n is the total number of vertices in the graph
     */
	bool removeEdge(const string& source, const string& dest);


    /*!
     * @brief Function that implements one of the functionalities of exercise 3.i.
     * @details The edge is identified by the source Vertex's (source) and destination Vertex's (dest) contents.
     * @returns Int value with the total amount of Edge object in the graph (total amount of flights).
     * @note Time complexity: O(V + E), where V corresponds to the number of vertices in the graph and E corresponds to the number of edges in the graph.
     */
    int numTotalFlights() const;

    /*!
     * @brief Function that implements one of the functionalities of exercise 3.iii.
     * @param airportsPerCity Vector containing the airportCode of all airports in the inputted city.
     * @returns Int value with the total amount of outgoing Edge objects of each airport in airportsPerCity (total number of flights per city).
     * @note Time complexity: O(n*«complexity of findVertex()»), where n corresponds to the number of airports in the inputted city.
     * @see findVertex()
     */
    int numFlightsPerCity(const vector<string>& airportsPerCity) const;

    /*!
     * @brief Function that implements one of the functionalities of exercise 3.iii.
     * @param airlineCode Inputted code of the airline.
     * @returns Int value with the total amount of Edge objects whose content is airlineCode (total flights per airline).
     * @note Time complexity: O(V + E), where V corresponds to the number of vertices in the graph and E corresponds to the number of edges in the graph.
     * @see findVertex()
     */
    int numFlightsPerAirline(const string& airlineCode) const;


    /*!
     * @brief Function that implements one of the functionalities of exercise 3.iv.
     * @param airportCode Inputted code of the airport.
     * @param allAirports Used to access information about the airports.
     * @returns Int value with the total amount of countries that the inputted airport flies directly to.
     * @note Time complexity: O(«complexity of findVertex()» + E), where E corresponds to the number of outgoing edges from the Vertex whose content is airportCode.
     * @see findVertex()
     */
    int numCountriesPerAirportDirect(const string& airportCode, const AllAirports& allAirports) const;

    /*!
     * @brief Function that implements one of the functionalities of exercise 3.iv.
     * @param airportsPerCity Vector containing the airportCode of all airports in the inputted city.
     * @param allAirports Used to access information about the airports.
     * @returns Int value with the total amount of countries that all airports from the inputted city fly directly to.
     * @note Time complexity: O(V + E), where V corresponds to the number of vertices in the graph and E corresponds to the number of edges in the graph.
     * @see findVertex()
     */
    int numCountriesPerCityDirect(const vector<string>& airportsPerCity, const AllAirports& allAirports) const;

    /*!
     * @brief Function that implements one of the functionalities of exercise 3.v.
     * @param airportCode Inputted code of the airport.
     * @returns Int value with the total amount of airports that the inputted airport flies to (with layovers).
     * @note Time complexity: O(«complexity of dfs(const string& source)»).
     * @see dfs(const string& source)
     */
    int numAirportsPerAirport(const string& airportCode) const;

    /*!
     * @brief Function that implements one of the functionalities of exercise 3.v.
     * @param airportCode Inputted code of the airport.
     * @param allAirports Used to access information about the airports.
     * @returns Int value with the total amount of cities that the inputted airport flies to (with layovers).
     * @note Time complexity: O(«complexity of dfs(const string& source)» + V), where V is the amount of airports (vertices) visited through the dfs traversal (which is all of them)
     * @see dfs(const string& source)
     */
    int numCitiesPerAirport(const string& airportCode, const AllAirports& allAirports) const;

    /*!
     * @brief Function that implements one of the functionalities of exercise 3.v.
     * @param airportCode Inputted code of the airport.
     * @param allAirports Used to access information about the airports.
     * @returns Int value with the total amount of countries that the inputted airport flies to (with layovers).
     * @note Time complexity: O(«complexity of dfs(const string& source)» + V), where V is the amount of airports (vertices) visited through the dfs traversal (which is all of them)
     * @see dfs(const string& source)
     */
    int numCountriesPerAirport(const string& airportCode, const AllAirports& allAirports) const;


    /*!
     * @brief Function that implements one of the functionalities of exercise 3.vi.
     * @param airportCode Inputted code of the airport.
     * @param x Number of layovers.
     * @returns Int value with the total amount of airports that the inputted airport flies to in a maximum of x layovers.
     * @note Time complexity: O(«complexity of bfsWithStops()»).
     * @see bfsWithStops()
     */
    int numAirportsX(const string& airportCode, int x) const;

    /*!
     * @brief Function that implements one of the functionalities of exercise 3.vi.
     * @param airportCode Inputted code of the airport.
     * @param x Number of layovers.
     * @param allAirports Used to access information about the airports.
     * @returns Int value with the total amount of cities that the inputted airport flies to in a maximum of x layovers.
     * @note Time complexity: O(«complexity of bfsWithStops()» + v), where v is the amount of airports (vertices) visited through the bfsWithStops traversal (always lower than the total amount of vertices).
     * @see bfsWithStops()
     */
    int numCitiesX(const string& airportCode, int x, const AllAirports& allAirports) const;

    /*!
     * @brief Function that implements one of the functionalities of exercise 3.vi.
     * @param airportCode Inputted code of the airport.
     * @param x Number of layovers.
     * @param allAirports Used to access information about the airports.
     * @returns Int value with the total amount of countries that the inputted airport flies to in a maximum of x layovers.
     * @note Time complexity: O(«complexity of bfsWithStops()» + v), where v is the amount of airports (vertices) visited through the bfsWithStops traversal (always lower than the total amount of vertices).
     * @see bfsWithStops()
     */
    int numCountriesX(const string& airportCode, int x, const AllAirports& allAirports) const;


    /*!
     * @brief Function that performs a dfs traversal of the whole graph.
     * @returns Vector with the contents of the all the vertices by dfs order.
     * @note Not used.
     * @note Time complexity: O(«complexity of dfsVisit()»).
     * @see dfsVisit()
     */
	vector<string> dfs() const;

    /*!
     * @brief Function that performs a dfs traversal, starting on the source Vertex.
     * @param source Content of the source Vertex.
     * @returns Vector with the contents of the visited vertices by dfs order.
     * @note Time complexity: O(«complexity of dfsVisit()»).
     * @see dfsVisit()
     */
    vector<string> dfs(const string& source) const;

    /*!
     * @brief Function that performs a bfs traversal, starting on the source Vertex.
     * @param source Content of the source Vertex.
     * @returns Vector with the contents of the visited vertices by bfs order.
     * @note Not used.
     * @note Time complexity: O(V + E), where V corresponds to the source vertex and all its adjacents (which is all the vertices in the graph, in the worst case), and E corresponds to the number of outgoing edges from the source vertex and all its adjacents (which is all the edges in the graph, in the worst case).
     */
	vector<string> bfs(const string& source) const;

    /*!
     * @brief Function that implements the functionality of exercise 3.vii.
     * @details Calculates the diameter of the graph, which is the longest of all the shortest paths between any two vertices.
     * @param maxDist Reference to an integer that will be updated with the maximum distance of the diameter.
     * @return Vector of pairs, where each pair contains two airport codes representing the endpoints of a diameter.
     * @note Time complexity: O(V * (V + E)), where V is the number of vertices and E is the number of edges in the graph.
     */
    vector<pair<string, string>> diameter(int& maxDist) const;

    /*!
     * @brief Function that implements the functionality of exercise 3.viii.
     * @details Calculates the total traffic capacity (number of outgoing and incoming flights) for each airport in the graph and then identifies the top K airports (based on sorting them in descending order of traffic capacity). <br>
     *          It also prints the results.
     * @param x Int representing the number of top airports to display.
     * @note Time complexity: O(«complexity of airportTrafficCapacity()» + V log V + k), where V is the number of vertices in the graph and k is the inputted number of airports.
     */
    void topXAirports(int x) const;

    /*!
     * @brief Function that implements the functionality of exercise 3.ix.
     * @details Finds the articulation points of the graph.
     * @result
     * @note Time complexity: O(«complexity of dfsForArtPoints()»).
     * @see dfsForArtPoints()
     */
    unordered_set<string> articulationPoints() const;

    /*!
     * @brief Function that implements the functionality of exercises 4. and 5.
     * @details Finds the shortest paths between source and dest, with the possibility of applying filters
     * @param source airportCodes that correspond to the source input.
     * @param dest airportCodes that correspond to the destination input.
     * @param airlineFilter int corresponding to the filter option selected during the execution of Menu::Menu12: <br>
     *                      1 - Whitelist filter <br>
     *                      2 - Blacklist filter <br>
     *                      3 - Minimize the amount of different airlines used <br>
     *                      4 - No filters
     * @param airlines Inputted airline codes.
     * @param allAirports Used to access information about the airports.
     * @note Time complexity if filter 1 or 2 is applied: O(F1+F2+F3+F4+F5+F8). <br>
     *       Time complexity if filter 3 is applied: O(F1+F2+F4+F5+F6+F7). <br>
     *       Time complexity if filter 4 is applied: O(F1+F2+F4+F5+F8).
     * @see interpretInputs() - F1, each F value represents the time complexity of the algorithm.
     * @see inputsValid() - F2
     * @see findAirlinesToFilter() - F3
     * @see findAllShortestPaths() - F4
     * @see existPaths() - F5
     * @see findLeastAirlinesPerPath() - F6
     * @see filter3Printer() - F7
     * @see bestOptionPrinter() - F8
     */
    void findBestOption(const string& source, const string& dest, int airlineFilter, const string& airlines, const AllAirports& allAirports) const;
};

#endif /* AED2_GRAPH_HPP */