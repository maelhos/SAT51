from termcolor import colored
import subprocess
from time import perf_counter_ns
import numpy as np
timeoutInSec = 5 # in seonds
def nsToTime(a):
    s = a // 1000
    ms = (a % 1000)
    mi = s//60
    s %= 60
    return f"{mi} min | {s} s | {ms} ms"

uf = [20] + list(range(50, 250, 25))

print(colored(f"[+] Welcome to SAT51 tester !!","blue"))
argvs = []

def end():
    for i in range(len(argvs)):
        print(colored(f"[+] serie of {uf[i]} variables had average time {argvs[i]} ms","blue"))
    exit()

def eng(n):
    if n == 1:
        return "First"
    elif n == 2:
        return "Second"
    elif n == 3:
        return "Third"
    elif n % 10 == 1:
        return str(n) +"st"
    elif n % 10 == 2:
        return str(n) +"nd"
    elif n % 10 == 3:
        return str(n) +"rd"
    else:
        return str(n) +"th"

ser = 1
for u in uf:
    print(colored(f"[+] {eng(ser)} serie of test on {u} variables:","blue"))
    cnf_file = subprocess.run(["ls", "test/uf" + str(u)], stdout=subprocess.PIPE).stdout.strip().decode().split("\n")
    timelist = []
    max_fn_len = 0
    for l in cnf_file:
        max_fn_len = max(max_fn_len, len(l))

    nb_succed = 0
    nb_files = 0
    for f in cnf_file:
        start = perf_counter_ns() // 1000000
        try:
            ret = subprocess.run(["./SAT51", "test/uf"+str(u)+"/" + f], stdout=subprocess.PIPE, timeout=timeoutInSec).stdout.strip().decode()
        except:
            print(colored("[!] TIMED OUUUTTTT","red"))
            end()
        t = perf_counter_ns()// 1000000 - start
        timelist.append(t)

        alignsapce = (max_fn_len-len(f))*" "
        if "SAT" in ret:
            print(colored("[-] " + f + alignsapce + " -> " + ret.replace("\n"," | ")[:20] + " ... in " + nsToTime(t), "green"))
            nb_succed += 1
        else:
            print(colored("[!] " + f + alignsapce + " FAIL -> " + ret.replace("\n"," | ")[:20] + " ... in " + nsToTime(t), "red"))
        nb_files += 1

    print(colored(f"[+] {eng(ser)} serie of test on {u} variables {nb_succed}/{nb_files} succes with average time {nsToTime(np.mean(timelist))} ms","blue"))
    argvs.append(np.mean(timelist))
    ser += 1

end()