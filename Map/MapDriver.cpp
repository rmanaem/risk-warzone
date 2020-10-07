#include <iostream>
using namespace std;
#include "./Map.h"
#include <vector>
#include <stack>

int main(){
    Graph validGraph;

    //create the South America continent
    Continent* southAmerica = validGraph.createContinent("South America");
    Territory venzuela("Venzuela", southAmerica);
    Territory brazil("Brazil", southAmerica);
    Territory argentina("Argentina", southAmerica);
    Territory peru("Peru", southAmerica);
    validGraph.insertAndConnectTwoTerritories(venzuela, brazil);// venzuela --> brazil
    validGraph.insertAndConnectTwoTerritories(argentina, peru);// argentina --> peru
    validGraph.connectTwoNodes(validGraph.getV()[0],validGraph.getV().end()[-1]);//venzuela --> peru
    validGraph.connectTwoNodes(validGraph.getV().end()[-1],validGraph.getV()[1]);//peru --> brazil

    //create the Africa continent
    Continent* africa = validGraph.createContinent("Africa");
    Territory northAfrica("North Africa", africa);
    Territory egypt("Egypt", africa);
    Territory eastAfrica("East Africa", africa);
    Territory congo("Congo", africa);
    Territory southAfrica("South Africa", africa);
    Territory mdagascar("Mdagascar", africa);
    validGraph.insertAndConnectTwoTerritories(northAfrica, egypt);//north africa --> egypt
    validGraph.insertAndConnectTwoTerritories(eastAfrica, congo);//east africa --> congo
    validGraph.insertAndConnectTwoTerritories(southAfrica, mdagascar);//south africa --> mdagascar
    validGraph.connectTwoNodes(validGraph.getV()[4], validGraph.getV()[7]);//north africa --> congo
    validGraph.connectTwoNodes(validGraph.getV()[7], validGraph.getV().end()[-2]);//congo --> south africa
    validGraph.connectTwoNodes(validGraph.getV()[5], validGraph.getV()[6]);//egypt --> east africa

    //connect between south america and africa
    validGraph.connectTwoNodes(validGraph.getV()[1], validGraph.getV()[4]);//brazil --> north africa

    for(Node* territory : validGraph.getV()){
        cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
            + " has the following edges:"<<endl;
        for(string edge : territory->getE()){
            cout<<edge<<"\t";
        }
        cout<<endl;
    }
    validGraph.validate();
    return 0;
}