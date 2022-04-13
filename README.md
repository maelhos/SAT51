# SAT51

The official solver to the patisfiability problem

![InductorGen Logo](/logo/logo_small.png)

## Installation

## Linux Installation

You can download SAT51 by cloning the [Git Repo](https://github.com/maelhos/SAT51).
SAT51 only requires **make** and **gcc** which can be install on a debian-like via :

``` bash
 ❯❯❯ sudo apt update
 ❯❯❯ sudo apt -y install gcc make
```

And then simply :

``` bash
 ❯❯❯ sudo make CLEAN
 ❯❯❯ sudo make
```

## Windows Installation

Windows is'nt supported **yet** but very well might be in the future but WSL2 works fine.

## Syntax

SAT51 follows the traditional DIMACS format for input file as well as output (even for the help message...)

## Usage

``` bash
usage: ./SAT51 [options] <file>.cnf

Optional arguments:
  -h, --help            
            show this help message and exit
  -a, --algo
            - QUINE (does not use heuristics)
            - DPLL
            - CDCL (by default)
  -h, --heuristics
            - MF (Most Frequent literal)
            - MS (Minimum size clause of the literal)
            - RD (Random, can be randomly the best or the worse)
            - WL (Watched literals, default for DPLL)
            - VS (VSIDS Branching, CDCL only and default for it)
  -t, --threads 
            Number of cores to use (default 1), 0 to to use **all** available

Examples:
  ./SAT51 -a QUINE -t 10 perf.cnf
```

## Tasks

- [x] READMEEEEEE
- [x] Makefile and Architecture
- [ ] Argument Parser
- [ ] File Parser
- [ ] Defining structures for clauses and stuff
- [ ] Quine
- [ ] DPLL
- [ ] CDCL
- [ ] Simple heuristics
- [ ] First testing
- [ ] Threading
- [ ] Advanced heuristics
- [ ] Deep testing

## Developers

* Maël Hostettler - [@maelhos](mailto:maelhos.dev@gmail.com)
* Augustin Perrin - [@maelhos](mailto:maelhos.dev@gmail.com)
* Alexandre jsp - [@maelhos](mailto:maelhos.dev@gmail.com)
