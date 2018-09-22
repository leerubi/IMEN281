#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include <cmath>
#include <ctime>
#include <functional>
using namespace std;
class Node {
    string nodeID;      // 노드의 이름
    int x;              // x 좌표 값
    int y;              // y 좌표 값
    bool check;         // permanetNodes 컨테이너에 담겼는지 체크
    string preNode;     // 이전 노드의 이름
    double s_dis;       // 시작 노드로부터 해당 노드까지의 거리
    double s_dis_e;     // 시작 노드로부터 해당 노드까지의 거리 + 해당 노드로부터 종점 노드로까지의 거리
public:
    Node() {}
    Node(string _nodeID, int _x, int _y, bool _check, string _preNode, double _s_dis, double _s_dis_e)
    : nodeID(_nodeID), x(_x), y(_y), check(_check), preNode(_preNode), s_dis(_s_dis), s_dis_e(_s_dis_e) {}
    string get_nodeID() { return nodeID; }
    int getX() const { return x; }
    int getY() const { return y; }
    bool isPermanent() const { return check; }
    string get_preNode() const { return preNode; }
    double get_s_dis() const { return s_dis; }
    double get_s_dis_e() const { return s_dis_e; }
    void checkPermanent(bool check) { this->check = check; }
    void set_s_dis(double s_dis) { this->s_dis = s_dis; }
    void set_s_dis_e(double s_dis_e) { this->s_dis_e = s_dis_e; }
    void set_preNode(string preNode) { this->preNode = preNode; }
    bool operator>(const Node& node) const {
        if (s_dis_e != node.get_s_dis_e())
            return s_dis_e > node.get_s_dis_e();
        else
            return s_dis > node.get_s_dis();
    }
    bool operator<(const Node& node) const {
        if (s_dis_e != node.get_s_dis_e())
            return s_dis_e < node.get_s_dis_e();
        else
            return s_dis < node.get_s_dis();
    }
};

class Edge {
    string end_nodeID;  // 엣지의 시작 노드의 이름
    double distance;    // 엣지의 길이
public:
    Edge() {}
    Edge(string _end_nodeID, double _distance)
    : end_nodeID(_end_nodeID), distance(_distance) {}
    string get_end_nodeID() const { return end_nodeID; }
    double get_distance() const { return distance; }
};

class Graph {
    map<string, Node> nodes;              // node를 저장하는 맵
    map<string, vector<Edge>> edges;      // node 별 edge를 벡터에 저장한 맵
    priority_queue<Node, vector<Node>, greater<Node>> newReachableNodes; // reachable한 node를 저장하는 우선큐위큐
    vector<string> permanentNodes;        // permanent node의 ID를 저장하는 벡터
public:
    void read_nodefile(string filename);  // nodefile을 읽어 node 객체 생성 및 nodes 컨테이너에 저장하는 메소드
    void read_edgefile(string filename);  // edgefile을 읽어 edge 객체 생성 및 edges 컨테이너에 저장하는 메소드
    void find_SP_dijkstra(string start_nodeID, string end_nodeID);      // Dijkstra 알고리즘으로 최단 경로를 구하는 메소드
    void find_SP_Astar(string start_nodeID, string end_nodeID);         // A* 알고리즘으로 최단 경로를 구하는 메소드
    void write_file(string filename, string start_nodeID, string end_nodeID, double runTime); // 최단 경로를 파일로 출력하는 메소드
};

void Graph::read_nodefile(string filename) {  // Node input 파일 읽고 맵에 저장
    ifstream fin(filename);
    if (!fin.is_open())
        throw - 1;
    string dummy;
    getline(fin, dummy);    // 첫번째 줄 처리
    
    string nodeID, _x, _y;
    int x, y;
    while (!fin.eof()) {    // 인풋 파일 읽어서 Node 객체 생성 및 맵에 저장
        getline(fin, nodeID, '\t');
        if (nodeID == "")   // 맥에서만 필요한 듯?
            break;
        getline(fin, _x, '\t');
        getline(fin, _y);
        x = stoi(_x);
        y = stoi(_y);
        nodes.insert(pair<string, Node>(nodeID, Node(nodeID, x, y, false, "", 999999, 0)));
    }
    fin.close();
}

void Graph::read_edgefile(string filename) {  // Edge input 파일 읽고 2차원 벡터에 저장
    ifstream fin(filename);
    if (!fin.is_open())
        throw - 2;
    string dummy;
    getline(fin, dummy);
    
    string edgeID, start_nodeID, end_nodeID;
    double _distance, distance, x1, x2, y1, y2;
    while (!fin.eof()) {
        getline(fin, edgeID, '\t');
        getline(fin, start_nodeID, '\t');
        getline(fin, end_nodeID);
        x1 = nodes[start_nodeID].getX();
        x2 = nodes[end_nodeID].getX();
        y1 = nodes[start_nodeID].getY();
        y2 = nodes[end_nodeID].getY();
        _distance = sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));
        int p = pow(10, 2);
        distance = floor((_distance*p) + 0.5f) / p;        // 소수점 둘째자리까지 반올림
        edges[start_nodeID].push_back(Edge(end_nodeID, distance));
        edges[end_nodeID].push_back(Edge(start_nodeID, distance));
    }
    fin.close();
}
void Graph::find_SP_dijkstra(string start_nodeID, string end_nodeID) {
    // exeption: start_nodeID가 없는 경우
    if (nodes.find(start_nodeID) == nodes.end())
        throw 's';
    
    // Step 1
    nodes[start_nodeID].checkPermanent(true);                                       // start_node에 permanent 표시 후
    nodes[start_nodeID].set_s_dis(0);                                               // ... 자기 자신으로부터의 거리로 0 저장 후
    permanentNodes.push_back(start_nodeID);                                         // ... ID만 permanentNodes에 저장
    for (int i = 0; i < edges[start_nodeID].size(); i++) {
        string reachable_nodeID = edges[start_nodeID][i].get_end_nodeID();          // start_node와 인접한 노드에 대해
        nodes[reachable_nodeID].set_s_dis(edges[start_nodeID][i].get_distance());   // ... start_node로부터의 거리를 s_dis에 저장
        nodes[reachable_nodeID].set_preNode(start_nodeID);                          // ... 이전 노드로 start_node를 저장
        newReachableNodes.push(nodes[reachable_nodeID]);                            // ...  newReachableNodes에 넣음
    }
    while (true) {
        // exeption: path가 없는 경우
        if (newReachableNodes.size() <= 0)
            throw 'p';
        // Step 2
        Node permanentNode = newReachableNodes.top();               // newReachableNodes에서 s_dis가 가장 작은 node를
        nodes[(permanentNode.get_nodeID())].checkPermanent(true);   // ... permanent 표시 후
        permanentNodes.push_back(permanentNode.get_nodeID());       // ... node ID만 permanentNodes에 저장하고
        newReachableNodes.pop();                                    //  ... s_dis가 가장 작은 node를 newReachableNodes로부터 삭제
        // Step 3
        if (permanentNode.get_nodeID() == end_nodeID)
            return;
        // Step 4
        map<string, Node>::iterator iter;
        for (int i = 0; i < edges[(permanentNode.get_nodeID())].size(); i++) {
            string reachable_nodeID = edges[permanentNode.get_nodeID()][i].get_end_nodeID();    // 방금 저장된 permanent node와 인접한 노드 중
            if (!nodes[reachable_nodeID].isPermanent()) {                                       // ... permanent node가 아닌 노드에 대해
                double temp = nodes[reachable_nodeID].get_s_dis();                              // ... 최소값 갱신 후
                nodes[reachable_nodeID].set_s_dis(min(temp, nodes[permanentNode.get_nodeID()].get_s_dis() + edges[permanentNode.get_nodeID()][i].get_distance()));
                if (temp != nodes[reachable_nodeID].get_s_dis()) {
                    if (nodes[reachable_nodeID].get_preNode() == "") {                          // newReachableNodes에 들어있지 않다면
                        nodes[reachable_nodeID].set_preNode(permanentNode.get_nodeID());        // ... preNode 갱신 후
                        newReachableNodes.push(nodes[reachable_nodeID]);                        // ... newReachableNodes에 넣어줌
                    }
                    else                                                                        // newReachableNodes에 들어있다면
                        nodes[reachable_nodeID].set_preNode(permanentNode.get_nodeID());       // ... preNode 갱신만 함
                }
            }
        }
    }
}

void Graph::find_SP_Astar(string start_nodeID, string end_nodeID) {
    // exeption: start_nodeID가 없는 경우
    if (nodes.find(start_nodeID) == nodes.end())
        throw 's';
    
    // Step 1
    nodes[start_nodeID].checkPermanent(true);                                       // start_node에 permanent 표시 후
    nodes[start_nodeID].set_s_dis(0);                                               // ... 자기 자신으로부터의 거리로 0 저장 후
    permanentNodes.push_back(start_nodeID);                                         // ... ID만 permanentNodes에 저장
    for (int i = 0; i < edges[start_nodeID].size(); i++) {
        string reachable_nodeID = edges[start_nodeID][i].get_end_nodeID();          // start_node와 인접한 노드에 대해
        nodes[reachable_nodeID].set_s_dis(edges[start_nodeID][i].get_distance());   // ... start_node로부터의 거리를 s_dis에 저장
        nodes[reachable_nodeID].set_preNode(start_nodeID);                          // ... 이전 노드로 start_node를 저장
        double s_dis = nodes[reachable_nodeID].get_s_dis();
        double x1, x2, y1, y2, s_dis_e;
        x1 = nodes[reachable_nodeID].getX();
        x2 = nodes[end_nodeID].getX();
        y1 = nodes[reachable_nodeID].getY();
        y2 = nodes[end_nodeID].getY();
        s_dis_e = sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));
        nodes[reachable_nodeID].set_s_dis_e(s_dis + s_dis_e);                       // ... s_dis_e 갱신 후
        newReachableNodes.push(nodes[reachable_nodeID]);                            // ... newReachableNodes에 넣음
    }
    while (true) {
        // exeption: path가 없는 경우
        if (newReachableNodes.size() <= 0)
            throw 'p';
        // Step 2
        Node permanentNode = newReachableNodes.top();            // newReachableNodes에서 s_dis가 가장 작은 node를
        nodes[permanentNode.get_nodeID()].checkPermanent(true);  // ... permanent 표시 후
        permanentNodes.push_back(permanentNode.get_nodeID());    // ... node ID만 permanentNodes에 저장하고
        newReachableNodes.pop();                                 //  ... s_dis_e가 가장 작은 node를 newReachableNodes로부터 삭제
        // Step 3
        if (permanentNode.get_nodeID() == end_nodeID)
            return;
        // Step 4
        map<string, Node>::iterator iter;
        for (int i = 0; i < edges[(permanentNode.get_nodeID())].size(); i++) {
            string reachable_nodeID = edges[permanentNode.get_nodeID()][i].get_end_nodeID();    // 방금 저장된 permanent node와 인접한 노드 중
            if (!nodes[reachable_nodeID].isPermanent()) {                                       // ... permanent node가 아닌 노드에 대해
                double temp = nodes[reachable_nodeID].get_s_dis();                              // ... 최소값 갱신 후
                nodes[reachable_nodeID].set_s_dis(min(temp, nodes[permanentNode.get_nodeID()].get_s_dis() + edges[permanentNode.get_nodeID()][i].get_distance()));
                if (temp != nodes[reachable_nodeID].get_s_dis()) {
                    if (nodes[reachable_nodeID].get_preNode() == "") {                          // newReachableNodes에 들어있지 않다면
                        nodes[reachable_nodeID].set_preNode(permanentNode.get_nodeID());        // ... preNode 갱신 후
                        double s_dis = nodes[reachable_nodeID].get_s_dis();
                        double x1, x2, y1, y2, s_dis_e;
                        x1 = nodes[reachable_nodeID].getX();
                        x2 = nodes[end_nodeID].getX();
                        y1 = nodes[reachable_nodeID].getY();
                        y2 = nodes[end_nodeID].getY();
                        s_dis_e = sqrt(((x2 - x1)*(x2 - x1)) + ((y2 - y1)*(y2 - y1)));
                        nodes[reachable_nodeID].set_s_dis_e(s_dis + s_dis_e);                   // ... s_dis_e 갱신 후
                        newReachableNodes.push(nodes[reachable_nodeID]);                        // ... newReachableNodes에 넣어줌
                    }
                    else                                                                        // newReachableNodes에 들어있다면
                        nodes[reachable_nodeID].set_preNode(permanentNode.get_nodeID());        // ... preNode 갱신만 함
                }
            }
        }
    }
}


void Graph::write_file(string filename, string start_nodeID, string end_nodeID, double runTime) {
    ofstream fout(filename);
    vector <string> path;
    string temp = end_nodeID;
    while (nodes[temp].get_preNode() != "") {
        path.push_back(temp);
        temp = nodes[temp].get_preNode();
    }
    
    fout << "최단거리 = " << nodes[end_nodeID].get_s_dis()
    << ", 계산 시간 = " << runTime << "ms"
    << " , start_node_id = " << start_nodeID
    << ", end_node_id = " << end_nodeID << endl;
    fout << "nodeID" << "\t" << "x-coordinate" << "\t" << "y-coordinate" << "\t" << "distance_to_next_node" << endl;
    reverse(path.begin(), path.end());
    fout << nodes[start_nodeID].get_nodeID() << "\t" << nodes[start_nodeID].getX() << "\t" << nodes[start_nodeID].getY() << "\t";
    for (int i = 0; i<path.size(); i++) {
        fout << nodes[path[i]].get_s_dis() << endl;
        fout << nodes[path[i]].get_nodeID() << "\t" << nodes[path[i]].getX() << "\t" << nodes[path[i]].getY() << "\t";
    }
    fout.close();
}

int main(int argc, const char * argv[]) {
    if (argc != 7) {
        cout << "아래와 같은 형식으로 입력하세요." << endl;
        cout << "<node file name> <edge file name> <start node ID> <end node ID> <algorithm_type: 1 = Dijkstra, 2 = A*> <solution file name>" << endl;
        return -1;
    }
    Graph graph;
    clock_t startTime, endTime;
    double runTime;
    try {
        int type = stoi(argv[5]);
        if (type == 1) {
            startTime = clock();
            graph.read_nodefile(argv[1]);
            graph.read_edgefile(argv[2]);
            graph.find_SP_dijkstra(argv[3], argv[4]);
            endTime = clock();
            runTime = (double)(endTime - startTime) / (CLOCKS_PER_SEC / 1000);
        }
        else if (type == 2) {
            startTime = clock();
            graph.read_nodefile(argv[1]);
            graph.read_edgefile(argv[2]);
            graph.find_SP_Astar(argv[3], argv[4]);
            endTime = clock();
            runTime = (double)(endTime - startTime) / (CLOCKS_PER_SEC / 1000);
        }
        else
            throw - 3;
        graph.write_file(argv[6], argv[3], argv[4], runTime);
    }
    catch (int exception) {
        if (exception == -1)
            cout << argv[1] << " 이 열리지 않음" << endl;
        else if (exception == -2)
            cout << argv[2] << " 이 열리지 않음" << endl;
        else if (exception == -3)
            cout << "알고리즘 타입은 1 또는 2입니다." << endl;
    }
    catch (char exception) {
        if (exception == 's')
            cout << "No start_node!" << endl;
        else if (exception == 'p')
            cout << "No path!" << endl;
    }
    return 0;
}


