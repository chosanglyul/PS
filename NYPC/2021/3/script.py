import os
import time
import subprocess

os.system('g++ -o C C.cpp')
processes = []
infiles = []
outfiles = []
for j in range(0, 16):
    for i in range(11, 12):
        infile = open(f'input_{i}.txt', 'r')
        outfile = open(f'result/{i:02}_{j:02}_out.txt', 'w')
        proc = subprocess.Popen(['C', f'result/{i:02}_{j:02}_res'], stdin=infile, stdout=outfile)
        processes.append(proc)
        infiles.append(infile)
        outfiles.append(outfiles)
    time.sleep(1)

for proc in processes:
    proc.communicate()
for infile in infiles:
    infile.close()
for outfile in outfiles:
    outfile.close()