#include <stdio.h>

#define vertexCount   5
#define INF           999999
#define UNKNOWN       -1
#define KNOWN         1
#define NOT_FOUND     -1

int graph[vertexCount][vertexCount] = {
                       //     A     B   C    D    E
                    /*A*/ { INF,   5,   5, INF,   5},
                    /*B*/ { 5  , INF, INF,   3, INF},
                    /*C*/ { 5  , INF, INF,   4,   6},
                    /*D*/ { INF,   3,   4, INF, INF},
                    /*E*/ { 5  , INF,   6, INF, INF},};


///*Ziyaret edilen nodelar, maliyet ve önceki node dizileri tanimlandi
int known[vertexCount];
int costs[vertexCount];
int previos_point[vertexCount];

void InitializeArrays();
int FindSmallestCostVertexAmongUnknowns();


///*Dizileri baslatiyor
///*Her dugumu ziyaret edilmemis olarak ayarliyor
///*Maliyetlerini sonsuz yapiyor, önceki noktayi ziyaret edilmemis yapiyor
void InitializeArrays()
{
    int i;

    for (i = 0; i < vertexCount; ++i) {
        known[i] = UNKNOWN;
        costs[i] = INF;
        previos_point[i] = UNKNOWN;
    }
}

///*En dusuk maliyetli dugumu buluyor
int FindSmallestCostVertexAmongUnknowns()
{
    int i;
    ///*En kucugu önce sonsuz maliyetli yapiyoruz
    int smallest = INF;
    ///*En kucuk olani önce bulunamadi olarak ayarliyoruz
    int smallest_index = NOT_FOUND;

    for (i = 0; i < vertexCount; ++i) {
        ///*Dugum ziyaret edilmemis ve maliyeti en kucuk olandan kucukse
        if (UNKNOWN == known[i] && costs[i] < smallest) {
            ///*En kucuk indexi ve en kucuk maliyeti tut
            smallest_index = i;
            smallest = costs[i];
        }
    }
    ///*En kucuk maliyetli indexi dondur
    return  smallest_index;
}

///*Baslangic node unu aliyoruz
void DijkstrasShortestPath(int source)
{
    int vertex;
    int neighbor;

    ///*Baslangic node unun maliyetini 0 yapiyoruz
    costs[source] = 0;

    ///*Ziyaret edilmemis en kucuk maliyetli indexi buluyoruz
    vertex = FindSmallestCostVertexAmongUnknowns();
    printf("The first vertex chosen is %d\n", vertex);

    ///*Ziyaret edilmemis node oldugu surece
    while (NOT_FOUND != vertex) {
        ///*Secilen node u ziyaret edilmis olarak isaretle
        known[vertex] = KNOWN;

        printf("After vertex %d has been declared as known.\n", vertex);


        ///* Komsu nodelari kontrol edip maliyetlerini ekliyoruz
        for (neighbor = 0; neighbor < vertexCount; ++neighbor) {
            ///* Ziyaret edilmemis komsu varsa
            if ((INF != graph[vertex][neighbor]) &&  (UNKNOWN == known[neighbor]))
                ///*Komsu bulduysan ve daha dusuk bir maliyetli yol ise komsunun maliyetini guncelle
                if ( (costs[vertex] + graph[vertex][neighbor]) < costs[neighbor]) {
                    costs[neighbor] = (costs[vertex] + graph[vertex][neighbor]);
                    previos_point[neighbor] = vertex;
                }
        }
        vertex = FindSmallestCostVertexAmongUnknowns();
    }

}
int main()
{
    InitializeArrays();
    DijkstrasShortestPath(3);

    return 0;
}
