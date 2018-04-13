#include<iostream>
#include<fstream>
#include<string>
//#include"dijkstra.h"
using namespace std;

class pixel
{
    public:
    int vertex_no, pixel_value;
};

int main()
{
    char id1,id2;
    int h, w, maxvalue,i;
    pixel **t1;
    ifstream fp;
    fp.open("test.pgm", ios::in);
    fp >> id1 >> id2;
    fp >> h >> w >> maxvalue;
    t1 = new pixel *[w];
    for(i = 0; i < h; i++)
        t1[i] = new pixel [h];
    for(i = 0; i < w; i++)
        for(int j = 0; j < h; j++)
        {
            fp >> t1[i][j].pixel_value;
            t1[i][j].vertex_no = (i * w)+ j;
        }
    //cout<<h<<"\t"<<w<<"\t"<<maxvalue;
    fp.close();
    for(i = 0; i < h; i++)
        for(j = 0; j < w-1; j++)
        {
            gh.addEdge(t1[i][j].vertex_no, t1[i][j+1].vertex_no, abs(t1[i][j].pixel_value - t1[[i][j+1].vertex_no));
            if(i == 0)
            {
                gh.addEdge(t1[i][j].vertex_no, t1[i+1][j+1].vertex_no, abs(t1[i][j].pixel_value - t1[[i+1][j+1].vertex_no));
            }
            else if(i == h-1)
            {
                gh.addEdge(t1[i][j].vertex_no, t1[i-1][j+1].vertex_no, abs(t1[i][j].pixel_value - t1[[i-1][j+1].vertex_no));
            }
            else
            {
                gh.addEdge(t1[i][j].vertex_no, t1[i-1][j+1].vertex_no, abs(t1[i][j].pixel_value - t1[[i-1][j+1].vertex_no));
                gh.addEdge(t1[i][j].vertex_no, t1[i+1][j+1].vertex_no, abs(t1[i][j].pixel_value - t1[[i+1][j+1].vertex_no));
            }
        }
    for(i = 0; i < w; i++)
    {
        for(int j = 0; j < h; j++)
                cout << t1[i][j].pixel_value << "\t";
        cout << endl;
    }
}
