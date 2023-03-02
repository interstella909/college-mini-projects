#This program calculates PI using the Gregory-Leibniz and using multithreading
#By Misael Valero
import threading

pi1=0
pi2=0
def calcular_pi1(iteracion):
    global pi1
    denominador1=1
    for i in range(iteracion):
        pi1 += 4/denominador1
        denominador1 += 4
    return pi1

def calcular_pi2(iteracion):
    global pi2
    denominador2=3
    for i in range(iteracion):
        pi2 += -4/denominador2
        denominador2 += 4
    return pi2

t1=threading.Thread(target=calcular_pi1,args=(500000,))
t2=threading.Thread(target=calcular_pi2,args=(500000,))

t1.start()
t2.start()

t1.join()
t2.join()

print(pi1+pi2)