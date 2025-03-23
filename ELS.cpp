#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <climits>  


  using namespace std;

    class Graph{

  private:
       int n; 
       int edgeCnt=0;
     unordered_map<int,unordered_set<int>> adj; 
    unordered_map<int,int> vertMp;           
      vector<int> revMp;                     

public:
    Graph() : n(0), edgeCnt(0) {}

    void addEdge(int u,int v){

        if(u == v){
         return; 
     } 
     
        if(vertMp.find(u)==vertMp.end()){
            vertMp[u] =n++;
              revMp.push_back(u);
        }

        if(vertMp.find(v)==vertMp.end()){
             vertMp[v]=n++;
            revMp.push_back(v);

        }


        int mapdU=vertMp[u], mapdV =vertMp[v];
             adj[mapdU].insert(mapdV);
               adj[mapdV].insert(mapdU);
               
               edgeCnt++;
   // cerr<<"Added an edge"<<u <<"-"<<v<<"(Mapped:"<<mapdU<<"-"<<mapdV<<")\n";       

             }

     bool ldFile(const string& filename){
           ifstream file(filename);

         if(!file.is_open()){
            cerr<<"Cant open the file "<<filename<< endl;
           
               return false;
       
            }

            string line;
        int edgeCount=0; 

        while(getline(file,line)){
            if (line.empty()||line[0]=='#') continue;  


            istringstream iss(line);

            int u, v;

            if(iss>>u>>v){
           addEdge(u, v);
                edgeCount++;
                  }else{
                     cerr<< "Skipped malformed line -"<<line<<endl;
                 }
             }

              file.close();
        cout<<"The file is loaded now"<<edgeCount<<"edges.\n";
        
             return true;
           }

       int VertCnt() const{
       
            return n;
         }
         
       int getEdgeCnt() const{
           return edgeCnt;
          }
  

     const unordered_set<int>& getNeigh(int v) const{
        static unordered_set<int> emptySet; 

         auto it=adj.find(v);
        return(it!=adj.end())?it->second:emptySet;
       
         }

             vector<int> degenOrder() const{
                 vector<int> ordg;
                  vector<int> degr(n);
                vector<bool> remvd(n,false);


        for(int i= 0;i<n;i++) degr[i]=adj.at(i).size();
        cerr<<"Computing degeneracy order...\n";

        for (int i=0;i<n;i++){
             int minVert=-1,minDegr=INT_MAX;

            for (int v=0;v<n;v++){
                if (!remvd[v]&& degr[v]<minDegr){
                   
                   minDegr= degr[v];
                   minVert= v;
               
             }
           
            }

            if(minVert==-1) break;
            ordg.push_back(minVert);
            remvd[minVert] = true;

        //  cerr<<"Picked vertex"<< minVert<<"with degree"<< minDegr<<"\n";

            for(int neigh:adj.at(minVert)){
                if(!remvd[neigh]){
               
                  degr[neigh]--;
                 }
          
           }
        }

        reverse(ordg.begin(),ordg.end()); 
        cerr<<"Degeneracy order is computed.\n";
        return ordg;
      }

       };

          struct CliqueStats{
             int largCliqSize = 0;
              int totMaxCliq= 0;
              int degenOrdSize=0;
              unordered_map<int, int> sizeDistn;
           };

          

              class BronKerbosch{
               private:
              const Graph& graph;
                CliqueStats stats;

     void bronKerbDegen(unordered_set<int>&R,unordered_set<int>& P,unordered_set<int>& X){
        if(P.empty() && X.empty()){

            stats.totMaxCliq++;
            stats.largCliqSize=max(stats.largCliqSize,(int)R.size());
            stats.sizeDistn[R.size()]++;
           
         //  cerr<<"Found a maximal clique of size"<< R.size()<<"\n";
           
         return;
       }
       
       auto P_it=P.begin();
    while (P_it!=P.end()){
        int v=*P_it;
        R.insert(v);


        unordered_set<int> newP, newX;
            for(int w :P){
                if(graph.getNeigh(v).count(w)) newP.insert(w);
                
              }
                
            for(int w:X){
                 if(graph.getNeigh(v).count(w)) newX.insert(w);

            }
            
            bronKerbDegen(R,newP,newX);
           
          R.erase(v);
          P_it = P.erase(P_it);
         
           X.insert(v);
          }
   
      }

     public:
       BronKerbosch(const Graph& g):graph(g){}

        CliqueStats findMaxiCliq(){
          stats = CliqueStats();

        vector<int> order= graph.degenOrder();
        stats.degenOrdSize=order.size();
        
      cerr<<"Running Bron-Kerbosch algorithm..\n";
 
        for (int i= 0;i<order.size();i++){
            int v=order[i];
            unordered_set<int> R={v}, P, X;

            for (int j=i + 1;j<order.size();j++){
                int u = order[j];

                if(graph.getNeigh(v).count(u)){
                 P.insert(u);
           }
         }
          for(int j=0;j<i;j++){
                int u=order[j];
                if (graph.getNeigh(v).count(u)){
                 X.insert(u);
           }
                }
           
             bronKerbDegen(R,P,X);
          }

       cerr<<"The Bron Kerbosc algorithm is completed.\n";
            return stats;
           }
      };

       void procData(const string& filename){
    cout<<"Processing the  dataset"<<filename<<endl;

       Graph graph;
         if(!graph.ldFile(filename)) {
           cerr<<"Failed to load graph"<<filename<<endl;
       
            return;
          }

    cout<<"Graph loaded with"<<graph.VertCnt()<<" vertices"<<endl;
 
 
      BronKerbosch bronKerbosch(graph);
       auto start=chrono::high_resolution_clock::now();
         CliqueStats stats=bronKerbosch.findMaxiCliq();
        auto end=chrono::high_resolution_clock::now();

             chrono::duration<double> elapd=end - start;

       cout<<"\nBron Kerbosc Algorithm gives"<<endl;
       cout<<"no. of vertices are:"<<graph.VertCnt()<<endl;
       cout<<"no. of edges are:"<<graph.getEdgeCnt()<<endl;
       cout<<"No of elements in the degeneracy ordering:"<<stats.degenOrdSize<<endl;
       cout<<"The largest clique size is- "<<stats.largCliqSize<<endl;
        cout<<"The total maximal cliques are"<<stats.totMaxCliq<<endl;
          cout <<"The execution time is "<<elapd.count()<<"secs"<<endl;
       
       cout<<"\n Clique Size distribution:\n";
        for(const auto &pair:stats.sizeDistn){
           cout<<"Clique size is:"<<pair.first<<":"<<pair.second<<"occurences\n";
       }
     }
 
       int main(int argc,char* argv[]){
            if (argc < 2){
               cout <<"Use is-"<<argv[0]<<"<datasetFile>"<< endl;
       
                 return 1;
               }

           procData(argv[1]);
   
             return 0;
         }
