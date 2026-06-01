#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
#define fi first
#define se second
#define INF 1e9
#define pii pair<int, int> 

class priorityQueue {
private:
    vector<pii> heap; //vertex, total time
    vector<int> pos;
    int size;
    int count;

    void swap(int i, int j){
        pii temp;
        temp = heap[i];
        heap[i]= heap[j];
        heap[j] = temp;
        pos[heap[i].fi] = i;
        pos[heap[j].fi] = j;
    }

    void minHeapify(int i){
        while(i > 1 && heap[i].se < heap[i/2].se) {swap(i, i/2);i/=2;}
    }

    bool cmp(pii &a, pii &b){
        if(a.se != b.se) return b.se > a.se;
        return b.fi > a.fi;
    }
    void reHeapify(int i){
        while (2*i <= count){
            int l=2*i, r=2*i+1;
            if(r <= count && !cmp(heap[l],heap[r])){swap(i,r); i = r; continue;}
            if(heap[i].se <=heap[l].se)break;
            swap(i, l);
            i = l;
        }
    }
public:
    priorityQueue(int s): size(s){
        heap.resize(s+1);
        pos.resize(s);
        count = 0;
        for(int &i:pos)i=-1;
    }

    void push(pii vertex){
        if(pos[vertex.fi] == -1){
            heap[++count] = vertex;
            pos[vertex.fi] = count;
            minHeapify(count);
        }
        else{
            heap[pos[vertex.fi]].se = vertex.se;
            minHeapify(pos[vertex.fi]);
        }
    }

    void pop(){
        pos[heap[1].fi]=-1;
        heap[1] = heap[count];
        if(count!=1)pos[heap[count].fi] = 1;
        count--;
        if(count > 0) reHeapify(1);
    }

    pii top(){return heap[1];}
    bool empty(){return (count == 0)?1:0;}

};

struct Graph{
    int amount;
    vector<int> time;
    vector<vector<pii>> adjList; //destination vertex, time 
};

int traffic(int time, int cycle){
    if(time <= 30) return time;
    return  (time%cycle ==0)? time :(time+cycle)/cycle*cycle;
}

struct resTime{
    int res;
    vector<int> path;
    int len;
};

resTime dijkstra(Graph &g, int src, int dest){
    vector<int> dist(g.amount, INF), prev(g.amount, -1);
    vector<bool> visited(g.amount, false);
    dist[src]=0;

    priorityQueue pq(g.amount);
    pq.push({src, 0});

    while(!pq.empty()){
        pii current = pq.top();
        int u = current.fi;
        pq.pop();
        if(visited[u]) continue;
        visited[u] = 1;
        if(u == dest) break;

        for(pii &adj: g.adjList[u]){
            int v = adj.fi;
            int w = adj.se;

            if(visited[v]) continue;

            int desTime = traffic(dist[u]+w, g.time[v]);
            if(desTime < dist[v]){
                dist[v] = desTime;
                prev[v] = u;
                pq.push({v,desTime});
            }
        }
    }

    vector<int> path(g.amount, -1);
    int len =1;
    for(int i = dest;i!=0;){
        path[prev[i]] = i;
        len++;
        i = prev[i];
    }

    resTime res;
    res.res = dist[dest];
    res.path = path;
    res.len = len;
    return res;
}

void preproc(string &s){
    for(int i = 0; i <= s.length(); i++){
        if(s[i] == ' ') s.erase(i, 1);
    }
}
int main(int argc, char* argv[]){
    ifstream infile(argv[1]);
    ofstream outfile(argv[2]);
    vector<string> s;
    string in;
    while(getline(infile, in)){
        preproc(in);
        s.push_back(in);
    }
    infile.close();
    int numg =stoi(s[0]);
    int index = 1;
    for(int i = 0;i<numg;i++){
        int numv =stoi(s[index++]);
        Graph g;
        g.amount =numv;
        g.adjList.resize(numv);
        g.time.resize(numv);
        
        int maxnum= numv;
        bool hasa =0;
        bool hasg =0;

        for(int j = 0; j<numv; j++){
            char c = s[index][0];
            maxnum = max(maxnum, c- 'A'+1);
            if(c == 'A') hasa =1;
            if(c == 'G') hasg =1;
            if(maxnum>g.time.size()){
                g.adjList.resize(maxnum);
                g.time.resize(maxnum);
            }
            s[index].erase(0,2);
            g.time[c - 'A'] = stoi(s[index++]);
        }

        while(index < s.size() && s[index][0] >= 'A' && s[index][0] <= 'Z'){
            char fir = s[index][0];
            s[index].erase(0,2);
            char sec = s[index][0];
            s[index].erase(0,2);
            int weig = stoi(s[index++]);
            g.adjList[fir-'A'].push_back({sec-'A', weig});
            g.adjList[sec-'A'].push_back({fir-'A', weig});
        }
        if(hasa && hasg){
            resTime res = dijkstra(g, 0, 'G'-'A');
            if(res.res == INF){
                cout << "No Path\n\n";
                outfile << "No Path\n\n";
                continue;
            }

            cout << res.res<< "\n";
            outfile << res.res << "\n";
            cout << char(0 + 'A') << " ";
            outfile << char(0+'A') << " ";
            for(int &i=res.path[0];;){
                cout << char(i + 'A') << " ";
                outfile << char(i+'A') << " ";
                i = res.path[i];
                if(i==-1)break;
            }
            cout << "\n";
            outfile << "\n";
        }
        else{
            cout << "No Path\n\n";
            outfile << "No Path\n\n";
        }
    }
    outfile.close();
    return 0;
}