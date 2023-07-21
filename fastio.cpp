#include "fastio.h"
#include <numbers>
using namespace fastio;
using namespace symbols;
ifstream ifs("fastio.in");
ofstream ofs("fastio.out");
int main() {
    int n;
    unsigned m;
    bool f;
    char c, s[105];
    double d;
    ifs >> n >> m >> f >> c >> s >> d;
    ofs << n << ends << m << ends << f << ends << c << ends << s << ends << d << endl;
    ifs.ignore().getline(s);
    ofs << s << endl;
    ofs << showbase << showpos;
    ofs << bin << INT_MAX << endl;
    ofs << oct << INT_MAX << ends << INT_MIN << ends << UINT_MAX << endl;
    ofs << hex << INT_MAX << ends << INT_MIN << ends << UINT_MAX << endl;
    ofs << dec << INT_MAX << ends << INT_MIN << ends << UINT_MAX << endl;
    ofs << noshowbase << noshowpos;
    ofs << boolalpha << true << ends << false << noboolalpha << endl;
    ofs << uppercase << new int << ends << lowercase << new int << endl;
    ofs << nullptr << endl;
    ofs << setfill('0') << setprecision(15);
    ofs << left << setw(20) << std::numbers::pi << endl;
    ofs << right << setw(20) << std::numbers::pi << endl;
    // while (ifs >> n) ofs << n << endl;
    return 0;
}