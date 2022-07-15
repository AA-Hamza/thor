#include "master/master.hpp"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 5)
    {
        std::cerr << "Usage: " << argv[0] << " <addr> <port> <root-dir> <num-of-workers>" << std::endl;
        exit(-1);
    }
    thor::server::Master myMaster(argv[1], argv[2], argv[3], atoi(argv[4]));
    myMaster.run();
}
