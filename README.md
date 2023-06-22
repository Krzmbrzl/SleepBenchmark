# SleepBenchmark

Code to benchmark the reliability of various ways to sleep/wait inside a C++ thread.

## Results

### Linux

```
Averaging sleep errors over 20 repetitions
Targeting a sleep of 100ns
  actual: 52us -> error: 52us (52768%)      sleepFor
  actual: 50us -> error: 50us (50782%)      sleepUntil
  actual: 50us -> error: 50us (50190%)      conditionVariableWaitFor
  actual: 52us -> error: 52us (52693%)      conditionVariableWaitUntil
  actual: 52us -> error: 52us (52731%)      osSleep
  actual: 789ns -> error: 689ns (689%)      spinWaitYield
  actual: 148ns -> error: 48ns (48%)      spinWaitBusy
Targeting a sleep of 100us
  actual: 158us -> error: 58us (58%)      sleepFor
  actual: 154us -> error: 54us (54%)      sleepUntil
  actual: 152us -> error: 52us (52%)      conditionVariableWaitFor
  actual: 152us -> error: 52us (52%)      conditionVariableWaitUntil
  actual: 152us -> error: 52us (52%)      osSleep
  actual: 100us -> error: 266ns (0%)      spinWaitYield
  actual: 100us -> error: 54ns (0%)      spinWaitBusy
Targeting a sleep of 1ms
  actual: 1ms -> error: 67us (6%)      sleepFor
  actual: 1ms -> error: 68us (6%)      sleepUntil
  actual: 1ms -> error: 69us (6%)      conditionVariableWaitFor
  actual: 1ms -> error: 66us (6%)      conditionVariableWaitUntil
  actual: 1ms -> error: 66us (6%)      osSleep
  actual: 1ms -> error: 591ns (0%)      spinWaitYield
  actual: 1ms -> error: 67ns (0%)      spinWaitBusy
Targeting a sleep of 10ms
  actual: 10ms -> error: 88us (0%)      sleepFor
  actual: 10ms -> error: 84us (0%)      sleepUntil
  actual: 10ms -> error: 87us (0%)      conditionVariableWaitFor
  actual: 10ms -> error: 81us (0%)      conditionVariableWaitUntil
  actual: 10ms -> error: 76us (0%)      osSleep
  actual: 10ms -> error: 367ns (0%)      spinWaitYield
  actual: 10ms -> error: 84ns (0%)      spinWaitBusy
Targeting a sleep of 100ms
  actual: 100ms -> error: 77us (0%)      sleepFor
  actual: 100ms -> error: 67us (0%)      sleepUntil
  actual: 100ms -> error: 79us (0%)      conditionVariableWaitFor
  actual: 100ms -> error: 76us (0%)      conditionVariableWaitUntil
  actual: 100ms -> error: 77us (0%)      osSleep
  actual: 100ms -> error: 463ns (0%)      spinWaitYield
  actual: 100ms -> error: 163ns (0%)      spinWaitBusy
```

### Windows

```
Averaging sleep errors over 20 repetitions
Targeting a sleep of 100ns
  actual: 1ms -> error: 1ms (1062565%)      sleepFor
  actual: 2ms -> error: 2ms (2962095%)      sleepUntil
  actual: 415ns -> error: 315ns (315%)      conditionVariableWaitFor
  actual: 4us -> error: 4us (4285%)      conditionVariableWaitUntil
  actual: 1us -> error: 1us (1010%)      osSleep
  actual: 515ns -> error: 415ns (415%)      spinWaitYield
  actual: 110ns -> error: 10ns (10%)      spinWaitBusy
Targeting a sleep of 100us
  actual: 14ms -> error: 14ms (14384%)      sleepFor
  actual: 14ms -> error: 14ms (14776%)      sleepUntil
  actual: 14ms -> error: 14ms (14837%)      conditionVariableWaitFor
  actual: 14ms -> error: 14ms (14842%)      conditionVariableWaitUntil
  actual: 340ns -> error: -99660ns (-99%)      osSleep
  actual: 100us -> error: 760ns (0%)      spinWaitYield
  actual: 100us -> error: 35ns (0%)      spinWaitBusy
Targeting a sleep of 1ms
  actual: 14ms -> error: 13ms (1361%)      sleepFor
  actual: 14ms -> error: 13ms (1387%)      sleepUntil
  actual: 14ms -> error: 13ms (1387%)      conditionVariableWaitFor
  actual: 14ms -> error: 13ms (1387%)      conditionVariableWaitUntil
  actual: 14ms -> error: 13ms (1386%)      osSleep
  actual: 1ms -> error: 130ns (0%)      spinWaitYield
  actual: 1ms -> error: 15ns (0%)      spinWaitBusy
Targeting a sleep of 10ms
  actual: 15ms -> error: 5ms (50%)      sleepFor
  actual: 15ms -> error: 5ms (53%)      sleepUntil
  actual: 15ms -> error: 5ms (54%)      conditionVariableWaitFor
  actual: 14ms -> error: 4ms (48%)      conditionVariableWaitUntil
  actual: 15ms -> error: 5ms (52%)      osSleep
  actual: 10ms -> error: 225ns (0%)      spinWaitYield
  actual: 10ms -> error: 1us (0%)      spinWaitBusy
Targeting a sleep of 100ms
  actual: 106ms -> error: 6ms (6%)      sleepFor
  actual: 106ms -> error: 6ms (6%)      sleepUntil
  actual: 105ms -> error: 5ms (5%)      conditionVariableWaitFor
  actual: 105ms -> error: 5ms (5%)      conditionVariableWaitUntil
  actual: 105ms -> error: 5ms (5%)      osSleep
  actual: 100ms -> error: 225ns (0%)      spinWaitYield
  actual: 100ms -> error: 895ns (0%)      spinWaitBusy
```
