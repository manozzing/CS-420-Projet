#!/usr/bin/python
from sys import argv
from multiprocessing import cpu_count
from timeit import timeit

def even_factors(x):
    for i in range(2, x + 1, 2):
        if x % i == 0 and i % 2 == 0:
            yield i

reps = 4
size = 1024 if len(argv) == 1 else int(argv[1])
##
# For the campus cluster benchmark
# cores = sorted([1, cpu_count() + 4, cpu_count() + 8, cpu_count() + 16] + list(even_factors(cpu_count())))
# Since the campus cluster exhibits strange cpu_count() behavior
cores = [1, 2, 4, 8, 16, 20, 24, 32, 40, 64]

def run_advection(OMP=False, tc=None):
    args = "./project -nx %d -ny %d" % (size, size)
    if (OMP):
        args += " -O"
    if (tc):
        args += " -n %d" % tc
    return timeit(stmt="subprocess.call(\"%s\", shell=True)" % args, setup="import subprocess", number=reps) / reps

print "Generating a {0}x{0} mandelbrot with core counts: {1}".format(size, cores)
serial = run_mandelbrot()
print "The serial version ran for",serial,"s."

print ""
for core in cores:
    time = run_mandelbrot(False, core)
    print "The parallel version, with",core,"core(s), ran for",time,"s, a speedup of %.3fx." % (serial/time)

print ""
for core in cores:
    time = run_mandelbrot(True, core)
    print "The OpenMP version, with",core,"core(s), ran for",time,"s, a speedup of %.3fx." % (serial/time)
