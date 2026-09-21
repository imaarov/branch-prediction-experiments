# Branch Prediction Experiment

In pipelined CPUs, new instructions don't wait for the previous instruction to fully finish; instructions are fetched at every stage of the pipline.
However, when execution reaches a branch, the CPU must perform prediction so that the pipeline and throughput do not stall. The CPU can predict a branch, i.e, it guesses whether the branch will be taken or not, and continues execution based on that guess.

if the guess is wrong (a misprediction), the CPU discover the mistake later and must roll back / recovre, costing several cycles until correct execution resumes.


This is what I read several times in the CS:APP book, and this time I wanted to see it in practice with my own runs under several scenarios:

- a scenario that is always correct (fully predictable)
- a scenario for odd/even (about 50% taken, alternating)
- a pseudo random scenario to stress the branch predictor

## How to run

1. Build the binary:

```bash
./run.sh build
```

2. Run the three test patterns (always|alt|rand|-all)
```bash
./run.sh stat rand
./run.sh stat alt
./run.sh stat always
./run.sh stat-all
```
