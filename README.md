# Assingment III

## Excercise 1

### Questions

- Write the code in C. ✅
- How do you compile it? Which compiler and flags have you used, if any?
  We compile with:
  `cc -o e1.out e1.c`
- How do you run the MPI code on Dardel?
  We use sbatch to run the code, which we use like this:
  `sbatch srun -n 4 -o ./output.txt ./e1.out`
  `

## Excercise 2

### Questions

- Run the ping-pong benchmark for 1) and 2). After that, plot the ping-pong time in function of the message size in 1) and 2).

  1. intra-node communication (2 processes on the same node)

  ![](./e2-1.png)

  2. inter-node communication (2 processes on different nodes)

  ![](./e2-2.png)

- Using best fit (using Matlab, Python, or similar), calculate the bandwidth and latency for 1) and 2).
  Hint: if you obtain a negative number for latency, you can omit the ping-pong times for small message sizes. In fact, the measurements for small messages are quite noisy.`
