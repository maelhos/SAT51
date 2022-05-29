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

Windows isn't supported **yet** but very well might be in the future but WSL2 works fine.

## Syntax

SAT51 follows the traditional DIMACS format for input file as well as output (even for the help message...)

## Usage

``` text
usage: ./SAT51 [options] <file>.cnf

Optional arguments:
  -h, --help            
            show this help message and exit
  -a, --algo
            - QUINE (does not use heuristics)
            - DPLL (default)
            - CDCL  --- IN DEV
  -e, --heuristic
            - FS (First literal we find...)
            - RD (Random...)
            - JW (Jeroslow-Wang Heuristic, assign variables with high occurrence in short clauses) default for DPLL
            - VS (VSIDS Branching, CDCL only and default for it) --- IN DEV
            - CS (RDLCS, with Let Cp (Cn) be the number of positive (negative) occurrences, maxiaml Cp + Cn
            - IS (RDLIS, maximal max(Cp, Cn))
  -n, --no-watched-literals  --- IN DEV
            Disable Watched literals and lazy datastructures for DPLL (I don't know why you would do that except for small inputs...)
  -t, --threads  --- IN DEV
            Number of cores to use (default 1), 0 to to use all available
  -s, --seed
            Seed the prng, by default seeded with time(0), (usefull for benchmark)

Example:
  ./SAT51 -a QUINE -t 10 perf.cnf
```

## Tasks

- [x] READMEEEEEE
- [x] Makefile and Architecture
- [x] Argument Parser
- [x] File Parser
- [x] Defining structures for clauses and stuff
- [ ] Better datastructures and watched literal
- [x] Quine
- [x] DPLL
- [ ] CDCL
- [x] Simple heuristics
- [x] First testing
- [ ] Threading...
- [.] Advanced heuristics
- [ ] Deep testing

## Developers

- Maël Hostettler - [@maelhos](https://github.com/maelhos/)
- Augustin Perrin - [@AugustinPERRIN](https://github.com/AugustinPERRIN/)
- Alexandre Romane - [@xelary](https://github.com/xelary/)

## Contributors

- Louis TG - [@lasercata](https://github.com/lasercata/) (official typo corrector)
