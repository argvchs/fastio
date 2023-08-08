#include <algorithm>
#include <cctype>
#include <cmath>
#include <concepts>
#include <cstddef>
#include <cstdio>
#include <cstring>
#include <string>
#include <string_view>
#include <type_traits>
namespace fastio {
namespace symbols {
enum symbol {
    endl,
    ends,
    flush,
    dec,
    bin,
    oct,
    hex,
    left,
    right,
    boolalpha,
    noboolalpha,
    showbase,
    noshowbase,
    showpoint,
    noshowpoint,
    showpos,
    noshowpos,
    skipws,
    uppercase,
    lowercase,
    reset
};
struct setbase {
    int base;
    setbase(int n) : base(n) {}
};
struct setfill {
    char fill;
    setfill(char c) : fill(c) {}
};
struct setprecision {
    int precision;
    setprecision(int n) : precision(n) {}
};
struct setw {
    int width;
    setw(int n) : width(n) {}
};
}
namespace interface {
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;
template <typename T>
concept signed_integral = std::signed_integral<T> || std::same_as<T, i128>;
template <typename T>
concept unsigned_integral = std::unsigned_integral<T> || std::same_as<T, u128>;
template <typename T>
concept integral = signed_integral<T> || unsigned_integral<T>;
template <typename T>
concept floating_point = std::floating_point<T>;
template <typename T>
struct make_unsigned {
    using type = std::make_unsigned_t<T>;
};
template <>
struct make_unsigned<i128> {
    using type = u128;
};
template <>
struct make_unsigned<u128> {
    using type = u128;
};
template <typename T>
using make_unsigned_t = typename make_unsigned<T>::type;
struct noncopyable {
    noncopyable() = default;
    virtual ~noncopyable() = default;
    noncopyable(const noncopyable &) = delete;
    noncopyable &operator=(const noncopyable &) = delete;
};
class istream : public noncopyable {
  private:
    int base = 10;
    bool pre = false, eof = false, fail = false;
    char now = '\0';
    int todigit(char c) {
        if (::isdigit(c)) return c - '0';
        else if (isupper(c)) return c - 'A' + 10;
        else if (islower(c)) return c - 'a' + 10;
        else return base;
    }
    bool isdigit(char c) { return todigit(c) < base; }
    virtual char vget() = 0;

  public:
    char get() {
        if (!pre)
            if ((now = vget()) == EOF) eof = true;
        pre = false;
        return now;
    }
    explicit operator bool() { return !fail; }
    bool operator!() { return fail; }
    template <integral T>
    istream &operator>>(T &n) {
        bool f = false;
        char c;
        while (!isdigit(c = get()) && !eof)
            if (isgraph(c) && signed_integral<T>) f = c == '-';
        if (eof) {
            fail = true;
            return *this;
        }
        pre = true, n = 0;
        while (isdigit(c = get())) n = n * base + todigit(c);
        if (f) n = -n;
        pre = true;
        return *this;
    }
    template <floating_point T>
    istream &operator>>(T &n) {
        bool f = false;
        char c;
        while (!isdigit(c = get()) && !eof)
            if (isgraph(c)) f = c == '-';
        if (eof) {
            fail = true;
            return *this;
        }
        pre = true, n = 0;
        while (isdigit(c = get())) n = n * base + todigit(c);
        if (c == '.') {
            T pow = 1;
            while (isdigit(c = get())) n += todigit(c) / (pow *= base);
        }
        if (f) n = -n;
        pre = true;
        return *this;
    }
    istream &operator>>(char &c) {
        while (isspace(c = get()) && !eof)
            ;
        if (eof) {
            fail = true;
            return *this;
        }
        return *this;
    }
    istream &operator>>(bool &f) {
        i64 n;
        *this >> n;
        f = n != 0;
        return *this;
    }
    template <int N>
    istream &operator>>(char (&s)[N]) {
        int len = 0;
        char c;
        while (isspace(c = get()) && !eof)
            ;
        if (eof) {
            fail = true;
            return *this;
        }
        pre = true;
        while (isgraph(c = get()) && len < N) s[len++] = c;
        pre = true, s[len] = '\0';
        return *this;
    }
    istream &operator>>(std::string &s) {
        char c;
        while (isspace(c = get()) && !eof)
            ;
        if (eof) {
            fail = true;
            return *this;
        }
        s.clear();
        pre = true;
        while (isgraph(c = get())) s.push_back(c);
        pre = true;
        return *this;
    }
    istream &operator>>(symbols::symbol a) {
        if (a == symbols::bin) base = 2;
        else if (a == symbols::oct) base = 8;
        else if (a == symbols::dec) base = 10;
        else if (a == symbols::hex) base = 16;
        else if (a == symbols::skipws) {
            char c;
            *this >> c;
            pre = 1;
        } else if (a == symbols::reset) base = 10;
        return *this;
    }
    istream &operator>>(symbols::setbase a) {
        base = std::max(std::min(a.base, 36), 2);
        return *this;
    }
    istream &ignore(char end = '\n') {
        char c;
        while ((c = get()) != end && !eof)
            ;
        if (eof) {
            fail = true;
            return *this;
        }
        return *this;
    }
    template <int N>
    istream &getline(char (&s)[N], char end = '\n') {
        int len = 0;
        char c;
        if (eof) {
            fail = true;
            return *this;
        }
        while ((c = get()) != end && !eof && len < N) s[len++] = c;
        if (s[len - 1] == '\r' && end == '\n') --len;
        s[len] = '\0';
        return *this;
    }
    istream &getline(std::string &s, char end = '\n') {
        char c;
        if (eof) {
            fail = true;
            return *this;
        }
        s.clear();
        while ((c = get()) != end && !eof) s.push_back(c);
        if (s.back() == '\r' && end == '\n') s.pop_back();
        return *this;
    }
};
class ostream : public noncopyable {
  private:
    int base = 10, precision = 6, width = 0;
    i64 eps = 1e6;
    bool adjust = true, boolalpha = false, showbase = false, showpoint = false, showpos = false,
         kase = false;
    char setfill = ' ';
    void fill(int n) {
        if (width > n) vfill(setfill, width - n);
        width = 0;
    }
    char toalpha(int n) {
        if (n < 10) return n + '0';
        else return n - 10 + (kase ? 'A' : 'a');
    }
    i64 quickpow(i64 n, int m) {
        i64 res = 1;
        while (m) {
            if (m & 1) res *= n;
            m >>= 1, n *= n;
        }
        return res;
    }
    virtual void vput(char) = 0;
    virtual void vputs(const char *, int) = 0;
    virtual void vfill(char, int) = 0;
    virtual void vflush() = 0;

  public:
    ostream &put(char c) {
        vput(c);
        return *this;
    }
    ostream &flush() {
        vflush();
        return *this;
    }
    template <integral T>
    ostream &operator<<(T n) {
        static char buf[105];
        char *p = buf + 100, *q = buf + 100;
        bool f = n < 0;
        if (f) n = -n;
        make_unsigned_t<T> m = n;
        if (!m) *p-- = '0';
        while (m) *p-- = toalpha(m % base), m /= base;
        if (showbase) {
            if (base == 2) *p-- = kase ? 'B' : 'b', *p-- = '0';
            else if (base == 16) *p-- = kase ? 'X' : 'x', *p-- = '0';
            else if (base == 8) *p-- = '0';
        }
        if (f) *p-- = '-';
        else if (showpos) *p-- = '+';
        if (adjust) fill(q - p);
        vputs(p + 1, q - p);
        if (!adjust) fill(q - p);
        return *this;
    }
    template <floating_point T>
    ostream &operator<<(T n) {
        static char buf1[105], buf2[105];
        char *p1 = buf1 + 100, *q1 = buf1 + 100, *p2 = buf2 + 100, *q2 = buf2 + 100;
        bool f = n < 0;
        if (f) n = -n;
        i64 m1 = std::floor(n), m2 = std::round((n - m1) * eps);
        int len = precision;
        if (m2 >= eps) ++m1, m2 = 0;
        if (!m1) *p1-- = '0';
        while (m1) *p1-- = toalpha(m1 % base), m1 /= base;
        while (len--) *p2-- = toalpha(m2 % base), m2 /= base;
        if (showbase) {
            if (base == 2) *p1-- = kase ? 'B' : 'b', *p1-- = '0';
            else if (base == 16) *p1-- = kase ? 'X' : 'x', *p1-- = '0';
            else if (base == 8) *p1-- = '0';
        }
        if (f) *p1-- = '-';
        else if (showpos) *p1-- = '+';
        if (showpoint) *p2-- = '.';
        else {
            while (*q2 == '0' && p2 != q2) --q2;
            if (p2 != q2) *p2-- = '.';
        }
        if (adjust) fill((q1 - p1) + (q2 - p2));
        vputs(p1 + 1, q1 - p1);
        vputs(p2 + 1, q2 - p2);
        if (!adjust) fill((q1 - p1) + (q2 - p2));
        return *this;
    }
    ostream &operator<<(char c) {
        if (adjust) fill(1);
        vput(c);
        if (!adjust) fill(1);
        return *this;
    }
    ostream &operator<<(const char *s) {
        int n = strlen(s);
        if (adjust) fill(n);
        vputs(s, n);
        if (!adjust) fill(n);
        return *this;
    }
    ostream &operator<<(const std::string &s) {
        int n = s.size();
        if (adjust) fill(n);
        vputs(s.data(), n);
        if (!adjust) fill(n);
        return *this;
    }
    ostream &operator<<(std::string_view sv) {
        int n = sv.size();
        if (adjust) fill(n);
        vputs(sv.data(), n);
        if (!adjust) fill(n);
        return *this;
    }
    ostream &operator<<(bool f) {
        if (boolalpha) {
            if (kase) return *this << (f ? "TRUE" : "FALSE");
            else return *this << (f ? "true" : "false");
        } else return *this << (f ? "1" : "0");
    }
    ostream &operator<<(const void *p) {
        int n = base;
        bool f = showbase;
        base = 16, showbase = true;
        *this << (u64)p;
        base = n, showbase = f;
        return *this;
    }
    ostream &operator<<(std::nullptr_t) { return *this << (kase ? "NULLPTR" : "nullptr"); }
    ostream &operator<<(symbols::symbol a) {
        if (a == symbols::endl) vput('\n');
        else if (a == symbols::ends) vput(' ');
        else if (a == symbols::flush) vflush();
        else if (a == symbols::dec) eps = quickpow(base = 10, precision);
        else if (a == symbols::bin) eps = quickpow(base = 2, precision);
        else if (a == symbols::oct) eps = quickpow(base = 8, precision);
        else if (a == symbols::hex) eps = quickpow(base = 16, precision);
        else if (a == symbols::left) adjust = false;
        else if (a == symbols::right) adjust = true;
        else if (a == symbols::boolalpha) boolalpha = true;
        else if (a == symbols::noboolalpha) boolalpha = false;
        else if (a == symbols::showbase) showbase = true;
        else if (a == symbols::noshowbase) showbase = false;
        else if (a == symbols::showpoint) showpoint = true;
        else if (a == symbols::noshowpoint) showpoint = false;
        else if (a == symbols::showpos) showpos = true;
        else if (a == symbols::noshowpos) showpos = false;
        else if (a == symbols::uppercase) kase = true;
        else if (a == symbols::lowercase) kase = false;
        else if (a == symbols::reset) {
            base = 10, precision = 6, width = 0, eps = 1e6;
            adjust = true;
            boolalpha = showpos = showpoint = showbase = kase = false;
            setfill = ' ';
        }
        return *this;
    }
    ostream &operator<<(symbols::setbase a) {
        base = std::max(std::min(a.base, 36), 2);
        eps = quickpow(base, precision);
        return *this;
    }
    ostream &operator<<(symbols::setfill a) {
        setfill = a.fill;
        return *this;
    }
    ostream &operator<<(symbols::setprecision a) {
        precision = std::max(a.precision, 0);
        eps = quickpow(base, precision);
        return *this;
    }
    ostream &operator<<(symbols::setw a) {
        width = std::max(a.width, 0);
        return *this;
    }
};
}
const int SIZ = 0xfffff;
class istream : public interface::istream {
  private:
    char buf[SIZ], *p = buf, *q = buf;
    char vget() override {
        if (p == q) {
            int len = fread(buf, 1, SIZ, stream);
            if (!len) return EOF;
            p = buf, q = buf + len;
        }
        return *p++;
    }

  protected:
    FILE *stream = stdin;

  public:
    virtual ~istream() { fclose(stream); }
};
class ifstream : public istream {
  public:
    ifstream(FILE *p) { istream::stream = p; }
    ifstream(const char *s) { istream::stream = fopen(s, "r"); }
};
class ostream : public interface::ostream {
  private:
    char buf[SIZ], *p = buf;
    void vput(char c) override {
        if (p - buf >= SIZ) vflush();
        *p++ = c;
    }
    void vputs(const char *s, int n) override {
        int used = p - buf, len = 0;
        while (n - len + used >= SIZ) {
            memcpy(buf + used, s + len, SIZ - used);
            p = buf + SIZ;
            vflush();
            len += SIZ - used, used = 0;
        }
        memcpy(buf + used, s + len, n - len);
        p = buf + used + n - len;
    }
    void vfill(char c, int n) override {
        int used = p - buf, len = 0;
        while (n - len + used >= SIZ) {
            memset(buf + used, c, SIZ - used);
            p = buf + SIZ;
            vflush();
            len += SIZ - used, used = 0;
        }
        memset(buf + used, c, n - len);
        p = buf + used + n - len;
    }
    void vflush() override {
        fwrite(buf, 1, p - buf, stream);
        p = buf;
        fflush(stream);
    }

  protected:
    FILE *stream = stdout;

  public:
    virtual ~ostream() {
        vflush();
        fclose(stream);
    }
};
class ofstream : public ostream {
  public:
    ofstream(FILE *p) { ostream::stream = p; }
    ofstream(const char *s) { ostream::stream = fopen(s, "w"); }
};
istream is;
ostream os;
};