#include <iostream>
#include "./Map.h"
#include <vector>
#include <stack>
using namespace std;

/*
Quick instruction:
If you want to see the third illustation being validated, the second one should be fixed.
To do so, just remove the comment from line 88 (i.e. establish the brazil --> north africa connection).
*/
int main(){
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ valid Map illustration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    Map* validMap = new Map();

    //create the South America continent
    Continent* southAmerica = validMap->createContinent("South America");
    Territory* venzuela = new Territory("Venzuela", southAmerica);
    Territory* brazil = new Territory("Brazil", southAmerica);
    Territory* argentina = new Territory("Argentina", southAmerica);
    Territory* peru = new Territory("Peru", southAmerica);
    validMap->insertAndConnectTwoTerritories(*venzuela, *brazil);// venzuela --> brazil
    validMap->insertAndConnectTwoTerritories(*argentina, *peru);// argentina --> peru
    validMap->connectTwoNodes(validMap->getV()[0],validMap->getV().end()[-1]);//venzuela --> peru
    validMap->connectTwoNodes(validMap->getV().end()[-1],validMap->getV()[1]);//peru --> brazil

    //create the Africa continent
    Continent* africa = validMap->createContinent("Africa");
    Territory* northAfrica = new Territory("North Africa", africa);
    Territory* egypt = new Territory("Egypt", africa);
    Territory* eastAfrica = new Territory("East Africa", africa);
    Territory* congo = new Territory("Congo", africa);
    Territory* southAfrica = new Territory("South Africa", africa);
    Territory* mdagascar = new Territory("Mdagascar", africa);
    validMap->insertAndConnectTwoTerritories(*northAfrica, *egypt);//north africa --> egypt
    validMap->insertAndConnectTwoTerritories(*eastAfrica, *congo);//east africa --> congo
    validMap->insertAndConnectTwoTerritories(*southAfrica, *mdagascar);//south africa --> mdagascar
    validMap->connectTwoNodes(validMap->getV()[4], validMap->getV()[7]);//north africa --> congo
    validMap->connectTwoNodes(validMap->getV()[7], validMap->getV().end()[-2]);//congo --> south africa
    validMap->connectTwoNodes(validMap->getV()[5], validMap->getV()[6]);//egypt --> east africa

    //connect between south america and africa
    validMap->connectTwoNodes(validMap->getV()[1], validMap->getV()[4]);//brazil --> north africa

    // for(Node* territory : validMap->getV()){
    //     cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
    //         + " has the following edges:"<<endl;
    //     for(string edge : territory->getE()){
    //         cout<<edge<<"\t";
    //     }
    //     cout<<endl;
    // }

    validMap->validate();

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ invalid Map illustration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //Unconnected graph

    Map* invalidMap = new Map();

    //create the South America continent
    Continent* southAmericaInvalid = invalidMap->createContinent("South America");
    Territory* venzuelaInvalid = new Territory("Venzuela", southAmericaInvalid);
    Territory* brazilInvalid = new Territory("Brazil", southAmericaInvalid);
    Territory* argentinaInvalid = new Territory("Argentina", southAmericaInvalid);
    Territory* peruInvalid = new Territory("Peru", southAmericaInvalid);
    invalidMap->insertAndConnectTwoTerritories(*venzuelaInvalid, *brazilInvalid);// venzuela --> brazil
    invalidMap->insertAndConnectTwoTerritories(*argentinaInvalid, *peruInvalid);// argentina --> peru
    invalidMap->connectTwoNodes(invalidMap->getV()[0],invalidMap->getV().end()[-1]);//venzuela --> peru
    invalidMap->connectTwoNodes(invalidMap->getV().end()[-1],invalidMap->getV()[1]);//peru --> brazil

    //create the Africa continent
    Continent* africaInvalid = invalidMap->createContinent("Africa");
    Territory* northAfricaInvalid = new Territory("North Africa", africaInvalid);
    Territory* egyptInvalid = new Territory("Egypt", africaInvalid);
    Territory* eastAfricaInvalid = new Territory("East Africa", africaInvalid);
    Territory* congoInvalid = new Territory("Congo", africaInvalid);
    Territory* southAfricaInvalid = new Territory("South Africa", africaInvalid);
    Territory* mdagascarInvalid = new Territory("Mdagascar", africaInvalid);
    invalidMap->insertAndConnectTwoTerritories(*northAfricaInvalid, *egyptInvalid);//north africa --> egypt
    invalidMap->insertAndConnectTwoTerritories(*eastAfricaInvalid, *congoInvalid);//east africa --> congo
    invalidMap->insertAndConnectTwoTerritories(*southAfricaInvalid, *mdagascarInvalid);//south africa --> mdagascar
    invalidMap->connectTwoNodes(invalidMap->getV()[4], invalidMap->getV()[7]);//north africa --> congo
    invalidMap->connectTwoNodes(invalidMap->getV()[7], invalidMap->getV().end()[-2]);//congo --> south africa
    invalidMap->connectTwoNodes(invalidMap->getV()[5], invalidMap->getV()[6]);//egypt --> east africa

    // No connection between south america and africa
    invalidMap->connectTwoNodes(invalidMap->getV()[1], invalidMap->getV()[4]);//brazil --> north africa

    // for(Node* territory : invalidMap->getV()){
    //     cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
    //         + " has the following edges:"<<endl;
    //     for(string edge : territory->getE()){
    //         cout<<edge<<"\t";
    //     }
    //     cout<<endl;
    // }

    invalidMap->validate();
    
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ invalid Map illustration ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
    //Unconnected sub-graph

    Map* Invalid11Map = new Map();

    //create the South America continent
    Continent* southAmericaInvalid1 = Invalid11Map->createContinent("South America");
    Territory* venzuelaInvalid1 = new Territory("Venzuela", southAmericaInvalid1);
    Territory* brazilInvalid1 = new Territory("Brazil", southAmericaInvalid1);
    Territory* argentinaInvalid1 = new Territory("Argentina", southAmericaInvalid1);
    Territory* peruInvalid1 = new Territory("Peru", southAmericaInvalid1);
    Invalid11Map->insertAndConnectTwoTerritories(*venzuelaInvalid1, *brazilInvalid1);// venzuela --> brazil
    // Invalid11Map->insertATerritory(*venzuelaInvalid1);
    // Invalid11Map->insertATerritory(*brazilInvalid1);
    Invalid11Map->insertAndConnectTwoTerritories(*argentinaInvalid1, *peruInvalid1);// argentina --> peru
    Invalid11Map->connectTwoNodes(Invalid11Map->getV()[0],Invalid11Map->getV().end()[-1]);//venzuela --> peru
    Invalid11Map->connectTwoNodes(Invalid11Map->getV().end()[-1],Invalid11Map->getV()[1]);//peru --> brazil

    // for(Node* territory : Invalid11Map->getV()){
    //     cout<<territory->getData().getTerritoryName() + " belongs to " + territory->getData().getContinent()->getContinentName()
    //         + " has the following edges:"<<endl;
    //     for(string edge : territory->getE()){
    //         cout<<edge<<"\t";
    //     }
    //     cout<<endl;
    // }
    Invalid11Map->validate();

    delete validMap; validMap = nullptr;
    delete invalidMap; invalidMap = nullptr;
    delete Invalid11Map; Invalid11Map = nullptr;

    return 0;
}