#include <iostream>
#include <fstream>
#include <vector>
#include "hychou_pm.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        cout << "usage: pm <input_file> <output_file>" << endl;
        return 1;
    }

    // INPUT //
    PM tool;
    fstream f;

    f.open(argv[1], ios::in);
    f >> tool.N;
    tool.poison = new int *[tool.N];
    for (int i = 0; i < tool.N; ++i)
    {
        tool.poison[i] = new int[tool.N];
        for (int j = 0; j < tool.N; ++j)
            f >> tool.poison[i][j];
    }
    f.close();

    // CORE //
    int C = tool.Core();

    // OUTPUT //

    f.open(argv[2], ios::out);
    f << C << ' ' << tool.route.size() + 1 << std::endl;
    while (tool.route.size())
    {
        f << tool.route.back();
        tool.route.pop_back();
    }
    f << std::endl;
    f.close();

    for (int i = 0; i < tool.N; ++i)
        delete[] tool.poison[i];
    delete[] tool.poison;

    return 0;
}
