#include "master/master.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc == 2) {
        cout << "starting master with " << atoi(argv[1]) << " slaves" << std::endl;
        http::server::Master myMaster("localhost", "8080", "./home/", atoi(argv[1]));
        myMaster.run();
    }
    else {
        http::server::Master myMaster("localhost", "8080", "./home/", 1);
        myMaster.run();
    }
}
