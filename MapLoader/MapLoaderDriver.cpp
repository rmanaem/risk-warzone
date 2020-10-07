#include <iostream>
#include <dirent.h>
#include <sys/types.h>
#include <list>
#include <iterator>
#include "MapLoader.h"
using namespace std;
void showlist(list <string> g)
{
    g.pop_front();
    g.pop_front();
    list <string> :: iterator it;
    for(it = g.begin(); it != g.end(); ++it)
        cout  << *it <<endl;
    cout << '\n';
}
list<string> list_dir(const char *path) {
    list<string> results;
   struct dirent *entry;
   DIR *dir = opendir(path);
   
//   if (dir == NULL) {
//      return;
//   }
   while ((entry = readdir(dir)) != NULL) {
    results.push_back( entry->d_name);
   }
   //showlist(results);
   closedir(dir);
    return results;
}
 
  
int main() {

   list<string> toBeParsed =list_dir("/Users/talalbazerbachi/Documents/GitHub/Risk-Game/MapLoader/Maps/");
    toBeParsed.pop_front();
    toBeParsed.pop_front();
    MapLoader loader;
    list <string> :: iterator it;
    for(it = toBeParsed.begin(); it != toBeParsed.end(); ++it)
    loader.parseMap((*it));
}
