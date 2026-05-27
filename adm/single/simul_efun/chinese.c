
string chinese_number(int i)
{
    return CHINESE_D->chinese_number(i);
}

string to_chinese(string str)
{
    return CHINESE_D->chinese(str);
}

// 覆盖 mudcore/system/kernel/simul_efun/charset.c 里的 is_chinese()。
// mudcore 原版走 pcre_match("^\\p{Han}+$")，要求 PCRE 编译时启用
// --enable-unicode-properties (UCP)。FluffOS v2019 自带 packages 不开 UCP，
// 结果 \p{Han} 永远不匹配，任何中文姓名都被判 0，创角直接卡死。
// FluffOS v2019 内部字符串走 ICU/Unicode（strlen 返回码点数，str[i] 返回码点），
// 这里改成逐码点判定 CJK 区段，端口 6666 (UTF-8) 和 5566 (GBK) 都不依赖 PCRE。
// 参见 https://github.com/fxq45/yanhuang-mudlib/issues/5
int is_chinese(string str)
{
    int len, i, cp;

    if (!str)
        return 0;

    len = strlen(str);
    if (len < 1)
        return 0;

    for (i = 0; i < len; i++)
    {
        cp = str[i];

        // CJK 统一汉字 U+4E00-U+9FFF（绝大多数日常字符在此区段）
        if (cp >= 0x4E00 && cp <= 0x9FFF)
            continue;

        // CJK 统一汉字扩展 A U+3400-U+4DBF
        if (cp >= 0x3400 && cp <= 0x4DBF)
            continue;

        // CJK 兼容汉字 U+F900-U+FAFF
        if (cp >= 0xF900 && cp <= 0xFAFF)
            continue;

        // CJK 统一汉字扩展 B/C/D/E/F U+20000-U+2FA1F
        if (cp >= 0x20000 && cp <= 0x2FA1F)
            continue;

        // 其它码点（ASCII、拉丁、假名、谚文、标点等）都判定为非中文
        return 0;
    }

    return 1;
}
