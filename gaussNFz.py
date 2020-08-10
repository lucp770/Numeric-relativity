"""
Descrição: Encontra as funções N(z) e F(z), onde:

ds² = -N(r)dt²+dr²/N(r)+r²(F(r)dt+dphi)² é a metrica btz, e foi realizada
a mudança de variavel, z = rh/r, sendo rh o raio do horizonte de eventos.

Autores: L.P. Francisco; A.G.Sato
"""


#import de bibliotecas
import numpy as np
import scipy.integrate as spi
import matplotlib.pyplot as plt


#determinação do raio Ads ( a constante cosmológica é -1/l²)
l = 1

#passo
h = .001

#com a transformação de variaveis o valor maximo da distancia é 1
zmax = 1
z = np.arange(0.0099, zmax + h, h)

#Array e condições iniciais para a função F(z)
F = np.zeros_like(z)
F[0] = 0
F[-1] = -1

#Array e condições iniciais para a função N(z)
N = np.zeros_like(z)
N[0] = 9950#infinito
N[-1] = 0

#variaveis auxiliares que aparecem na matriz de coeficientes
a = 2 + h/z[1:-1]
b = 1 + h/z[1:-1]

#matriz dos resultados para F
P = np.zeros_like(z[1:-1])
P[0] = P[0]-F[0]*b[0]
P[-1] = P[-1]-F[-1]

#matriz dos resultados para N
R = np.zeros_like(z[1:-1])+8*(h**2)/(z[1:-1])**4
R[0] = R[0]-N[0]*b[0]
R[-1] = R[-1]-N[-1]

#definindo a matriz de coeficientes
def coeficientes(a,b):
	W = np.zeros([len(z)-2,len(z)-2])
	for i in range(0,len(z)-3):
		W[i,i] = round(-a[i],3)
		W[i+1,i] = round(b[i+1],3)
		W[i,i+1]  =1
	W[len(z)-3,len(z)-3] = -a[len(z)-3]
	return W

W = coeficientes(a,b)
#sol = np.linalg.inv(W).dot(R)
#N[1:-1]  = np.linalg.inv(W).dot(R) 


############################# ELIMINAÇÃO GAUSSIANA #############################################################

def Gauss(W,R):
	for i in range(0,len(W)):
		for j in range(i,len(W)-1):
			m = W[j+1,i]/W[i,i]
			W[j+1,:] = W[j+1,:] - m*W[i,:]
			R[j+1] = R[j+1] - m*R[i]
		    
	return W,R

W,R = Gauss(W,R)
W,P = Gauss(W,P)

def Regress(W,R,N):
	N[-1] = R[-1]/W[-1,-1]
	for i in range(len(W)-1,0,-1):
		N[i] = (R[i]-N[i+1])/W[i,i]
	return N

N = Regress(W,R,N)
F = Regress(W,P,F)
# print(N[0:20])


################################################### GRÁFICO ####################################################

#Solução Analítica
Na = -2 + z**2 + 1/(z**2)
Fa = -z**2

ErroN,ErroF = N-Na,F-Fa

fig = plt.figure(figsize=(20, 20))

ax1 = fig.add_subplot(221) 

ax1.axhline(0, color='k') 
ax1.axvline(0, color='k')
ax1.set_xlabel('$z$') 
ax1.set_ylabel('$N(z)$') 
ax1.set_ylim(-10,1000)
ax1.plot(z, N, 'ob', markersize =.5 , label = 'N-numerico') 
ax1.plot(z, Na, '-c',label = 'N-Analítica')
ax1.legend()

ax2 = fig.add_subplot(222)

ax2.axhline(0, color='k')
ax2.axvline(0, color='k')
ax2.set_xlabel('$z$')
ax2.set_ylabel('$F(z)$')
ax2.set_ylim(-1.5,1.5)
ax2.plot(z, F, 'om', markersize =.5 , label = 'F-numerico')
ax2.plot(z, Fa, '-c',label = 'F-Analítica')
ax2.legend()


ax3 = fig.add_subplot(223)

ax3.axhline(0, color='k')
ax3.axvline(0, color='k')
ax3.set_xlabel('$z$')
ax3.set_ylabel('Erro de $N(z)$')
# ax3.set_ylim(-1.5,1.5)
ax3.plot(z[50:], ErroN[50:], 'or', markersize =.5 , label = 'ErroN')
# ax2.legend()

ax4 = fig.add_subplot(224)

ax4.axhline(0, color='k')
ax4.axvline(0, color='k')
ax4.set_xlabel('$z$')
ax4.set_ylabel('Erro de $F(z)$')
ax4.set_ylim(-0.01,0.01)
ax4.plot(z[5:], ErroF[5:], 'ok', markersize =.5 , label = 'ErroF')
ax4.legend()

#plt.tight_layout() 
plt.show()

#implementar grid refiniment analisys: plotar o erro, e verificar se ao dividir por 2 o passo h, o erro também cai pela metade;
#a inclinação do gráfico error x h deve ser 1 para um método de erro de primeira ordem.

#para implementar GRA pode-se escolher um ponto aleatório, e calcular o erro em função


