#include "fastio.hpp"
#include <limits>
#include <string>
using namespace fastio;
using namespace symbols;
using u32 = unsigned;
using f64 = double;
ifstream ifs("fastio.in");
ofstream ofs("fastio.out");
int main() {
    int n;
    u32 m;
    bool f;
    char c, s[105];
    f64 d;
    std::string t;
    ifs >> n >> m >> f >> c >> s >> d;
    ofs << n << ends << m << ends << f << ends << c << ends << s << ends << d << endl;
    ifs.ignore() >> ws;
    ifs.get(t);
    ofs << t << endl;
    ofs << showbase << showpos;
    ofs << bin << std::numeric_limits<int>::max() << endl;
    ofs << oct << std::numeric_limits<int>::max() << endl;
    ofs << dec << std::numeric_limits<int>::max() << endl;
    ofs << hex << std::numeric_limits<int>::max() << endl;
    ofs << reset;
    ofs << boolalpha << true << ends << false << noboolalpha << endl;
    ofs << uppercase << new int << lowercase << endl;
    ofs << nullptr << endl;
    ofs << 3.14 << ends << fixed << 3.14 << defaultfloat << endl;
    ofs << std::numeric_limits<f64>::infinity() << ends;
    ofs << std::numeric_limits<f64>::quiet_NaN() << endl;
    ofs << setfill('0');
    ofs << setw(20) << left << "left" << endl;
    ofs << setw(20) << right << "right" << endl;
    while (ifs >> n) ofs << n << endl;
    return 0;
}