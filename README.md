# FastIO

一个快读快写库，支持基本类型读写，指针地址写入，和 `cin` `cout` 用法类似。

虽然相对于原版函数式 `fread` 快读会有点慢，但还是比 `getchar` `putchar` 要快的。

# 1. 目录解释

```plaintext
fastio.cpp          # 测试代码
fastio.hpp          # FastIO 库源代码
fastio.beta.hpp     # FastIO 库源代码，使用 C++20
fastio.in           # 读写测试数据
```

# 2. 使用

-   `using namespace fastio;`

    使用 FastIO。

-   `using namespace fastio::symbols;`

    使用读写符号，如 `endl`。

-   `is >> n;`

    读取 `n`。

-   `is >> n >> m >> k;`

    读取 `n` `m` `k`。

-   `c = is.get();`

    读取一个字符到 `c`。

-   `is >> s;`

    读取一个字符串 `s`。

-   `is.getline(s);`

    读取一行到 `s`。

-   `is.getline(s, end);`

    读取字符到 `s`，一直读到 `end` 停止。

-   `is.get(s);`

    读取一行到 `s`，但是把换行符保留在流中。

-   `is.get(s, end);`

    读取字符到 `s`，一直读到 `end` 停止，但是把 `end` 保留在流中。

-   `is.ignore();`

    忽略一行。

-   `is.ignore(end);`

    忽略字符到 c 停止。

-   `while (is >> n) ;`

    一直读取直到末尾。

-   `is >> bin;` `is >> oct;` `is >> dec;` `is >> hex;`

    按 2、8、10、16 进制读取数。

-   `is >> ws;`

    忽略前导空格。

-   `is.setbase(n);`

    按 `base` 进制读取数 $(2 \le base \le 36)$。

-   `is >> reset;`

    取消前面的所有设置。

-   `os << n;`

    写入 `n`。

-   `os << n << m << k;`

    写入 `n` `m` `k`。

-   `os.put(c);`

    写入一个字符 `c`。

-   `os << flush;`

    刷新流。

-   `os << endl;`

    写入换行。

-   `os << ends;`

    写入空格。

-   `os << boolalpha;`

    设置写入 `bool` 时用 `true` `false`。

-   `os << noboolalpha;`

    设置写入 `bool` 时用 `0` `1`。

-   `os << showpos;`

    设置写入正数和 0 时前面加 `+` 号。

-   `os << noshowpos;`

    设置写入正数和 0 时前面不加 `+` 号。

-   `os << showpoint;`

    设置写入浮点数时总是添加小数点。

-   `os << noshowpoint;`

    设置写入浮点数时不总是添加小数点。

-   `os << fixed;`

    设置写入浮点数时严格保留 `setprecision` 时设置的位数。

-   `os << defaultfloat;`

    设置写入浮点数时不严格保留 `setprecision` 时设置的位数。

-   `os << bin;` `os << oct;` `os << dec;` `os << hex;`

    按 2、8、10、16 进制写入整数。

-   `os << lowercase;`

    写入特殊内容时使用大写。

-   `os << uppercase;`

    写入特殊内容时使用小写。

-   `os << showbase;`

    写入 2、8、16 进制的数时，在前面显示 `0b` `0` `0x`。

-   `os << noshowbase;`

    写入 2、8、16 进制的数时，不在前面显示 `0b` `0` `0x`。

-   `os << setbase(n);`

    按 `base` 进制写入数，超出范围默认 10 进制 $(2 \le base \le 36)$。

-   `os << setw(n);`

    设置下一次写入宽度若小于 `width`，就填补字符（下一次写入重置）。

-   `os << setfill(c);`

    设置 `setw` 填补的字符，默认为空格。

-   `os << left;`

    设置 `setw` 填补的字符在左边。

-   `os << right;`

    设置 `setw` 填补的字符在右边。

-   `os << setprecision(n);`

    设置浮点数保留位数，默认保留 3 位。

-   `os << reset;`

    取消前面的所有设置。

-   `ifstream ifs(s);`

    创建文件读流，文件路径为 `s`，和普通读流用法相同。

-   `ofstream ofs(s);`

    创建文件写流，文件路径为 `s`，和普通写流用法相同。

# 3. 接口

可以用接口来重载运算符。

**注意要用 `fastio::interface::istream` `fastio::interface::ostream` 来重载。**

以下是重载 `std::vector` 的示例程序。

```cpp
template <typename T, typename U>
auto &operator<<(fastio::interface::istream &is, vector<T, U> &a) {
    T n, m;
    is >> n;
    a.clear();
    while (n--) {
        is >> m;
        a.push_back(m);
    }
    return is;
}
template <typename T, typename U>
auto &operator<<(fastio::interface::ostream &os, const vector<T> &a) {
    for (const T &i : a) os << i << ' ';
    return os;
}
```
