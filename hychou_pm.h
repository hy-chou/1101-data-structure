#ifndef __PM_H__
#define __PM_H__

#include <vector>

using namespace std;

class PM
{
public:
    PM();

    int N;
    int **poison;
    int Core();
    std::vector<char> route;

private:
    int **damage;
    char **color;
    char **parent;
    void goForward();
    void goBack(int, int);
    void relax(int, int, char);
};

#endif
