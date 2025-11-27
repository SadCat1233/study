from itertools import product

def truth_table(varnames, expr):
    rows = []
    for bits in product([0,1], repeat=len(varnames)):
        rows.append((*bits, expr(*bits)))
    return rows

def p_print(varnames, rows):
    head = ' '.join(varnames) + ' | f'
    print(head); print('-' * len(head))
    for *bits, val in rows:
        print(' '.join(map(str, bits)), '|', val)

varnames = ['A','B']
f = lambda A,B: (A & ((~B))) & 1
p_print(varnames, truth_table(varnames, f))
