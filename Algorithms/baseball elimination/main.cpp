#include <iostream>
#include <limits.h>
#include <string.h>
#include <queue>
#include <fstream>
#include <stdlib.h>
using namespace std;

#define MAX_FLOW 100
class Teams{
    int team_number; ///amount of teams
    int *scores; ///current scores of each team
    int **matches;///matrix showing matches remaining
  public:
    Teams(string); ///read file and initialize class variables
    ~Teams();
    bool bfs(int, int**, int[]);
    //template <size_t size_g>
    int FordFulkerson(int, int**); //(&graph)[size_g][size_g]);
    bool check_win(int);
    void get_output(string, bool = false);


};

Teams::Teams(string filename){
    ifstream infile;
    infile.open(filename);
    if(!infile.good()){
        cout << "Input file not found" << endl;
        exit(0);
    }
    infile >> team_number;
    ///initilize arrays
    scores = new int[team_number];
    matches = new int*[team_number];
    for(int i =0; i<team_number; i++){
        matches[i] = new int[team_number];
    }

    ///reading file
    for(int i =0; i<team_number; i++){///read scores
        infile >> scores[i];
    }
    for(int i =0; i<team_number; i++){///read matches
        for(int j=0; j<team_number;j++){
            infile >> matches[i][j];
        }
    }
}

Teams::~Teams(){
    delete scores;
    delete[] matches;
}

///return true if there is path from s to t (assumd first and last node).  Also saves path taken in parent[] array
bool Teams::bfs(int graph_size, int **rGraph, int parent[]){
    bool *visited; ///array keeping track of visited nodes
    visited = new bool[graph_size]{0}; ///initialize every index as 0

    int s = 0; ///starting node
    int t = graph_size -1; ///ending node

    queue <int> q; ///queue used for BFS loop
    q.push(s);
    visited[s] = true;
    parent[s] = -1; ///don't set as 0 since s node has 0 index


    while (!q.empty()) ///BFS loop
    {
        int u = q.front();
        q.pop();
        for (int v=0; v<graph_size; v++){
            if (visited[v]==false && rGraph[u][v] > 0){ ///checking if there is path and that the node has not been visited
                ///updating queue, parent and visited
                q.push(v);
                parent[v] = u;
                visited[v] = true;
            }
        }
    }

    bool result = visited[t]; ///if BFS could reach t node from s node then return true
    delete visited;
    return result;
}

/// Finds and returns the max flow in the given graph from s to t (assumed first and last node)
int Teams::FordFulkerson(int graph_size, int **graph)
{
    int u, v;
    int s = 0; ///s is assumed to be first node
    int t = graph_size -1; ///t is assumed to be last node

    int **rGraph;  ///residual graph.  rGraph[x][y] shows the egde capacity from node i to node j
    rGraph = new int*[graph_size];
    ///initializing rGraph
    for(int i=0; i<graph_size; i++){
        rGraph[i] = new int[graph_size];
    }
    for (u = 0; u < graph_size; u++)
        for (v = 0; v < graph_size; v++)
             rGraph[u][v] = graph[u][v];

    int *parent;  /// This array is modified by BFS algorithm to show the path taken
    parent = new int[graph_size];

    int max_flow = 0;  /// max flow of the graph

    while (bfs(graph_size, rGraph, parent)){///using BFS find a path then finding max flow through this path
        int path_flow = INT_MAX; ///initialize max flow as a large number
        for (v=t; v!=s; v=parent[v]){///checking flow of each path
            u = parent[v];
            path_flow = min(path_flow, rGraph[u][v]);///select smallest flow as our path flow
        }
        ///update forward and reverse edges of residual graph on the path taken by BFS
        for (v=t; v != s; v=parent[v]){
            u = parent[v];
            rGraph[u][v] -= path_flow; ///forward edge
            rGraph[v][u] += path_flow; ///reverse edge
        }

        /// update max_flow
        max_flow += path_flow;
    }

    delete[] rGraph;
    delete parent;
    return max_flow;
}

bool Teams::check_win(int team){

    ///generating flow graph (in matrix form) for team
    int graph_size;
    int match_count = 0; ///total number of unique matches remaining that do not include the team we are checking
                        ///(the same two teams with multiple matches will increment match_count by 1)
                        ///we are assuming team we are checking has won all matches
    int max_score = scores[team-1]; ///maximum possible score that the team we are checking can get (team wins all matches)

    int max_flow = 0;  ///the max possible flow for flow_graph (defined below)

    for(int i=0;i<team_number-1;i++){///calculating match_count,max_wins and max_flow.
                                    ///We are checking upper diagonal of graph matrix
        for(int j=i+1; j<team_number;j++){
            if(matches[i][j]!=0){
                if(j != team-1 && i != team-1){
                    match_count++;
                    max_flow += matches[i][j];
                }
                else
                    max_score += matches[i][j];
            }
        }
    }

    graph_size = team_number + match_count + 1; ///team_count -1 + match_count + 2(for s and t)

    int** flow_graph; ///the flow graph that we will run Ford Fulkerson algo on to check if win is possible for team
    ///initialize flow_graph
    flow_graph = new int*[graph_size];
    for(int i =0; i<graph_size; i++){
        flow_graph[i] = new int[graph_size]{0};
    }

    int temp = 1;
    int match = 1;
    for(int i=0;i<team_number-1;i++){///filling out s connections and inner connections
        int fi = 0; ///since flow_graph matrix does not include the current team's matches, therefore for the indices
        if(i>team-1) fi = 1;///i and j should get 1 subtracted from them when they are larger then the current team's index
        for(int j=i+1; j<team_number;j++){
            int fj = 0;
            if(j>team-1) fj = 1;
            if(matches[i][j]!=0){
                if(j != team-1 && i != team-1){
                    flow_graph[0][temp++] = matches[i][j]; ///setting connections of s node
                    flow_graph[match][i+match_count-fi+1] = matches[i][j]; ///can also be = to INT_MAX
                    flow_graph[match++][j+match_count-fj+1] = matches[i][j]; ///can also be = to INT_MAX
                }
            }
        }
    }

    int j = 0;
    for(int i = 1+match_count; i<graph_size-1; i++){///setting connections to t node
        if(j == team-1) j++;
        flow_graph[i][graph_size-1] = max_score - scores[j++]; ///this is equal to the max number of wins team j can get
    }                                                        ///such that it cannot surpass current team's
                                                            ///max possible score (max_score)
    /*for(int i=0;i<graph_size;i++){
        for(int j=0; j<graph_size;j++){
            cout << flow_graph[i][j]<< " ";
        }
        cout << endl;
    }*/

    ///finished making flow graph.  Now we need to run Ford Fulkerson algoritm on flow graph
    ///if result of Ford Fulkerson algoritm == max_flow then it is possible for the current team to be first place
    ///if not then it is impossible
    return (FordFulkerson(graph_size, flow_graph) == max_flow);
}
void Teams::get_output(string output, bool print){
    ofstream outFile(output);
    for(int i=1; i<=team_number; i++){
        bool result = check_win(i);
        if (print) cout << result << " ";
        else outFile << result << " ";
    }
    if(print) cout << endl;
}

int main(int argc, char* argv[]){
    string input;
    string output;
    bool print = true; ///if output not specified print to screen
    if(argc < 2){
        cout << "Usage is <input file> <output file(optional)> " << endl;
        exit(0);
    }
    else{
        input = argv[1];
        if (argc >2){
            output = argv[2];
            print = false;
        }
    }

    Teams team(input);
    team.get_output(output, print);
    return 0;
}
