def prefixFunction(s: str):
    p = [0] * len(s)
    for i in range(1, len(s) - 1):
        k = p[i - 1]
        while k > 0 and s[i] != s[k]:
            k = p[k - 1]
        if s[i] == s[k]:
            k += 1
        p[i] = k
    return p


print(prefixFunction("abcabcd"))
