from functools import reduce
tab = [[0 for j in range(7)] for i in range(502)];
tab[1] = [1,2,2,1,1,1,1];
for i in range(1,501):
    for j in range(7):
        for k in range(10):
            if(k != 7):
                tab[i+1][(10*j+k) % 7] += tab[i][j];
len = int(input());
while(len > 0):
    n = int(input());
    print(10**n - reduce(lambda x,y: x+y, tab[n][1:]) -1);
    len -= 1;
