## OS-assignment #1

Author : Vladislav Gladyshev.

Problem Statement : create a pid allocation manager that, at user’s request, assigns unique
process ID ranging from 300 to 5000 and when needed, releases these IDs for later reuse.

Assumptions : we can use a simple array of size 4701 and correlate its indices to pids. That is
index 0 correlates to pid 300 and so on. We can check availability of this pid by looking at the
content at the corresponding index so that 0 would mean it is available for taking, 1 otherwise.
