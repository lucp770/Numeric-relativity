
"""

Descrição: Resolve numericamente pelo método de Runge-Kutta um sistema de EDOs
derivados a partir das equações de Einstein para a métrica de Schwarzchild.
Mostrando o Gráfico dos parametros A(r) e B(r) para a métrica ds² = -A(r)c²dt²+B(r)dr²

Autores: Lucas P. Francisco; Amanda G. Sato

"""

import numpy as np
from matplotlib import pyplot as plt

#defina as duas equações diferenciais
def eqA(A,B,r):#A,B e r são números
	return A*B/r-A/r

def eqB(A,B,r):
	return -B**2/r+B/r

#definindo as condições iniciais:
A0 = 0.013#valor próximo de zero que parece propiciar convergencia para B=100
B0 = 100#tomado como infinito


#O buraco negro possui raio 1, logo a solução só está definida no intervalo [1,inf]
r0=1
rmax=3
h=0.01#passo fixo

r=np.arange(r0,rmax+h/2.,h)

#defindo a matriz de soluções:
A = np.zeros_like(r)
B = np.zeros_like(r)

#definindo as condições iniciais:
A[0],B[0] = A0,B0



#método de Runge-Kutta de ordem 2
for n in range(1,len(r)):
	#primeiro calcular K1a e K1b, depois K2a e K2b
	K1a = eqA(A[n-1],B[n-1],r[n-1])
	K1b = eqB(A[n-1],B[n-1],r[n-1])

	K2a = eqA(A[n-1]+h*K1a,B[n-1]+h*K1b,r[n-1]+h)#
	K2b = eqB(A[n-1]+h*K1a,B[n-1]+h*K1b,r[n-1]+h)

	#Atualizando os valores de A e B
	A[n] = A[n-1]+.5*h*(K1a+K2a)#depende tanto de A e B
	B[n] = B[n-1]+.5*h*(K1b+K2b)


#solução analítica
A_analitico = (1 - (1/r))
B_analitico = (1 - (1/r))**(-1)

#gráfico:

plt.figure('Metrica em função da distância radial')
plt.subplot(1,2,1)
plt.plot(r,A,'ob',markersize =2,label='A Numérico')
plt.plot(r,A_analitico,'-k',label = 'A analítico')
plt.xlabel('$ r $')
plt.ylabel('$ A(r) $')
plt.legend()

plt.subplot(1,2,2)
plt.plot(r,B,'or',markersize = 2,label = 'B Numérico')
plt.plot(r,B_analitico,'-k',label = 'B analítico')
plt.xlabel('$ r $')
plt.ylabel('$ B(r) $')
plt.legend()

plt.show()
