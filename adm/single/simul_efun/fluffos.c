// 模拟 fluffos 新增 efun
#ifndef FLUFFOS

mixed abs(mixed n)
{
    if (!floatp(n) && !intp(n))
        return 0;

    return (n < 0) ? -n : n;
}

mixed element_of(mixed *arr)
{
    return arr[random(sizeof(arr))];
}

#endif

#ifndef __PACKAGE_TRIM__
// 去掉str两端的空格
string trim(string str)
{
    int len;

    while (str[0] == ' ')
        str = str[1.. < 1];
    while ((len = strlen(str) - 1) >= 0 && str[len] == ' ')
        str = str[0.. < 2];

    return str;
}

// 去掉str左端空格
string ltrim(string arg)
{
    for (int i = 0; i < strlen(arg); i++)
        if (arg[i..i] != " ")
            return arg[i..strlen(arg)];
    return "";
}
#endif

// FluffOS v2019 sockets 包没有 socket_set_option efun（v2021+ 才加上，主要用于 TLS）
// mudcore/inherit/Http.c 等通过裸名调用，这里提供 no-op stub 让其能编译加载
// 新版驱动里同名 efun 存在时会优先匹配，simul_efun 自然不会被调到
#if !efun_defined(socket_set_option)
int socket_set_option(int fd, int option, mixed value)
{
    return 0;
}
#endif
