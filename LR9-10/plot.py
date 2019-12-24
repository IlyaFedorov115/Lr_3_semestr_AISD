import matplotlib.pyplot as plt

x = [0.0328, 0.4440, 0.9784, 1.6778, 4.1312, 4.7896, 4.8144, 5.4640, 5.5928, 6.3488, 6.3584]
y = [-5.6456, -2.2113, -0.0446, 0.2889, 7.5487, 18.9187, 19.4780, 38.1016, 42.7838, 77.8960, 78.4322]
f = {}
for i in range(len(x)):
    f[x[i]] = y[i]

def dif(curx):
    return (f[curx[1]] - f[curx[0]])/(curx[1] - curx[0]) if len(curx) == 2 else (dif(curx[1:]) - dif(curx[:-1]))/(curx[-1]- curx[0])

def inewton(n, x0):
    s = y[0]
    for i in range(1, n+1):
        mul = 1
        for j in range(i):
            mul *= x0-x[j]
        mul *= dif(x[:(i+1)])
        s += mul
    return s

def aitken(x0, a, b):
    f1 = y[a] if b - a == 1 else aitken(x0, a, b - 1)
    f2 = y[b] if b - a == 1 else aitken(x0, a + 1, b)
    return (1/(x[b]-x[a])) * ((x0-x[a])*f2 - (x0-x[b])*f1)


dots = [x[0]]
while dots[-1] < x[-1]:
    dots.append(dots[-1]+0.1)
dots[-1] = x[-1]

newton_y = [inewton(10, i) for i in dots]
aitken_y = [aitken(i, 0 ,10) for i in dots]

plt.plot(x, y)
plt.plot(dots, newton_y)
plt.plot([2.7176], inewton(10, 2.7176), color='red', marker='o', markersize=3)
print(inewton(10, 2.7176))
#plt.plot(dots, aitken_y)
#plt.plot([6.2212], aitken(6.2212, 0, 10), color='red', marker='o', markersize=3)
#print(aitken(6.2212, 0, 10))

#plt.plot(dots, aitken_y)
#plt.plot([1.9], aitken(1.9, 0, 10), color='red', marker='o', markersize=3)
#print(aitken(1.9, 0, 10))
plt.plot(x, y)
plt.plot(dots, aitken_y)
plt.plot([2.7176], aitken(2.7176, 0, 10), color='red', marker='o', markersize=3)
print(aitken(2.7176, 0, 10))
plt.show()

