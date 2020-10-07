#include <iostream>
using namespace std;
#include "./Map.h"
#include <vector>
#include <stack>

/*
Quick instruction:
If you want to see the third illustation being validated, the second one should be fixed.
To do so, just remove the comment from line 88 (i.e. establish the brazil --> north africa connection).
*/
int main(){
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ valid Graph illustration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
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

    // for(Node* territory : validGraph.getV()){
    //     cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
    //         + " has the following edges:"<<endl;
    //     for(string edge : territory->getE()){
    //         cout<<edge<<"\t";
    //     }
    //     cout<<endl;
    // }
    validGraph.validate();


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ invalid Graph illustration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //Unconnected graph

    Graph invalidGraph;

    //create the South America continent
    Continent* southAmericaInvalid = invalidGraph.createContinent("South America");
    Territory venzuelaInvalid("Venzuela", southAmericaInvalid);
    Territory brazilInvalid("Brazil", southAmericaInvalid);
    Territory argentinaInvalid("Argentina", southAmericaInvalid);
    Territory peruInvalid("Peru", southAmericaInvalid);
    invalidGraph.insertAndConnectTwoTerritories(venzuelaInvalid, brazilInvalid);// venzuela --> brazil
    invalidGraph.insertAndConnectTwoTerritories(argentinaInvalid, peruInvalid);// argentina --> peru
    invalidGraph.connectTwoNodes(invalidGraph.getV()[0],invalidGraph.getV().end()[-1]);//venzuela --> peru
    invalidGraph.connectTwoNodes(invalidGraph.getV().end()[-1],invalidGraph.getV()[1]);//peru --> brazil

    //create the Africa continent
    Continent* africaInvalid = invalidGraph.createContinent("Africa");
    Territory northAfricaInvalid("North Africa", africaInvalid);
    Territory egyptInvalid("Egypt", africaInvalid);
    Territory eastAfricaInvalid("East Africa", africaInvalid);
    Territory congoInvalid("Congo", africaInvalid);
    Territory southAfricaInvalid("South Africa", africaInvalid);
    Territory mdagascarInvalid("Mdagascar", africaInvalid);
    invalidGraph.insertAndConnectTwoTerritories(northAfricaInvalid, egyptInvalid);//north africa --> egypt
    invalidGraph.insertAndConnectTwoTerritories(eastAfricaInvalid, congoInvalid);//east africa --> congo
    invalidGraph.insertAndConnectTwoTerritories(southAfricaInvalid, mdagascarInvalid);//south africa --> mdagascar
    invalidGraph.connectTwoNodes(invalidGraph.getV()[4], invalidGraph.getV()[7]);//north africa --> congo
    invalidGraph.connectTwoNodes(invalidGraph.getV()[7], invalidGraph.getV().end()[-2]);//congo --> south africa
    invalidGraph.connectTwoNodes(invalidGraph.getV()[5], invalidGraph.getV()[6]);//egypt --> east africa

    // No connection between south america and africa
    // invalidGraph.connectTwoNodes(invalidGraph.getV()[1], invalidGraph.getV()[4]);//brazil --> north africa

    // for(Node* territory : invalidGraph.getV()){
    //     cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
    //         + " has the following edges:"<<endl;
    //     for(string edge : territory->getE()){
    //         cout<<edge<<"\t";
    //     }
    //     cout<<endl;
    // }
    invalidGraph.validate();
    

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ invalid Graph illustration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //Unconnected sub-graph

    Graph Invalid11Graph;

    //create the South America continent
    Continent* southAmericaInvalid1 = Invalid11Graph.createContinent("South America");
    Territory venzuelaInvalid1("Venzuela", southAmericaInvalid1);
    Territory brazilInvalid1("Brazil", southAmericaInvalid1);
    Territory argentinaInvalid1("Argentina", southAmericaInvalid1);
    Territory peruInvalid1("Peru", southAmericaInvalid1);
    //Invalid11Graph.insertAndConnectTwoTerritories(venzuelaInvalid1, brazilInvalid1);// venzuela --> brazil
    Invalid11Graph.insertATerritory(venzuelaInvalid1);
    Invalid11Graph.insertATerritory(brazilInvalid1);
    Invalid11Graph.insertAndConnectTwoTerritories(argentinaInvalid1, peruInvalid1);// argentina --> peru
    //Invalid11Graph.connectTwoNodes(Invalid11Graph.getV()[0],Invalid11Graph.getV().end()[-1]);//venzuela --> peru
    Invalid11Graph.connectTwoNodes(Invalid11Graph.getV().end()[-1],Invalid11Graph.getV()[1]);//peru --> brazil

    // for(Node* territory : Invalid11Graph.getV()){
    //     cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
    //         + " has the following edges:"<<endl;
    //     for(string edge : territory->getE()){
    //         cout<<edge<<"\t";
    //     }
    //     cout<<endl;
    // }
    Invalid11Graph.validate();
    
    return 0;
}